#include "ASTBuilder.h"

#include "picosha2.h"

#include "loguru.hpp"
#include <functional>
#include <vector>

using namespace antlrcpp;

ASTBuilder::ASTBuilder(TIPParser *p) : parser{p} {}

std::string ASTBuilder::opString(int op) {
  std::string opStr;
  switch (op) {
  case TIPParser::MUL:
    opStr = "*";
    break;
  case TIPParser::DIV:
    opStr = "/";
    break;
  case TIPParser::ADD:
    opStr = "+";
    break;
  case TIPParser::SUB:
    opStr = "-";
    break;
  case TIPParser::MM:
    opStr = "--";
    break;
  case TIPParser::PP:
    opStr = "++";
    break;
  case TIPParser::MOD:
    opStr = "%";
    break;
  case TIPParser::GT:
    opStr = ">";
    break;
  case TIPParser::GTE:
    opStr = ">=";
    break;
  case TIPParser::LT:
    opStr = "<";
    break;
  case TIPParser::LTE:
    opStr = "<=";
    break;
  case TIPParser::EQ:
    opStr = "==";
    break;
  case TIPParser::NE:
    opStr = "!=";
    break;
  case TIPParser::KAND:
    opStr = "and";
    break;
  case TIPParser::KOR:
    opStr = "or";
    break;
  default:
    throw std::runtime_error(
        "unknown operator :" +
        std::string(ASTBuilder::parser->getVocabulary().getLiteralName(op)));
  }
  return opStr;
}

/*
 * Globals for communicating information up from visited subtrees
 * These are overwritten by every visit call.
 * We use multiple variables here to avoid downcasting of shared smart pointers.
 */
static std::shared_ptr<ASTStmt> visitedStmt = nullptr;
static std::shared_ptr<ASTDeclNode> visitedDeclNode = nullptr;
static std::shared_ptr<ASTDeclStmt> visitedDeclStmt = nullptr;
static std::shared_ptr<ASTExpr> visitedExpr = nullptr;
static std::shared_ptr<ASTFieldExpr> visitedFieldExpr = nullptr;
static std::shared_ptr<ASTFunction> visitedFunction = nullptr;

/**********************************************************************
 * These methods override selected methods in the TIPBaseVisitor.
 *
 * For each rule name in an ANTLR4 grammar a visit method and a
 * "context" class is generated.  The visit methods are defined in
 * TIPBaseVisitor.h and the context classes in TIPParser.h
 *
 * Only the methods for grammar rules that "directly" contain
 * content that must be processed need to be overridden.  For example,
 * for strings that match "program" you need to process the list of
 * functions.
 *
 * If you are new to visitors, it is very important to understand
 * that since you are selectively overriding methods you cannot
 * rely on the call stack to return values (since the values will
 * be lost by the methods you don't override).  Instead you must create
 * your own structure that is local to the visitor to communicate between
 * the calls during the visit.  In the case of this visitor it is the
 * visitedX variables above.
 *
 * Note that the visit methods are required to return a value, but
 * we make no use of that value, so we simply return the empty string ("")
 * since we cannot return a nullptr (leads to a crash in the visitor).
 *
 * Consult context class definitions to understand the type definitions
 * of the fields that contain the program elements captured during the parse.
 * You will access these from the method overrides in your visitor.
 */

std::shared_ptr<ASTProgram> ASTBuilder::build(TIPParser::ProgramContext *ctx) {
  std::vector<std::shared_ptr<ASTFunction>> pFunctions;
  for (auto fn : ctx->function()) {
    visit(fn);
    pFunctions.push_back(visitedFunction);
  }

  auto prog = std::make_shared<ASTProgram>(pFunctions);
  prog->setName(generateSHA256(ctx->getText()));
  return prog;
}

Any ASTBuilder::visitFunction(TIPParser::FunctionContext *ctx) {
  std::shared_ptr<ASTDeclNode> fName;
  std::vector<std::shared_ptr<ASTDeclNode>> fParams;
  std::vector<std::shared_ptr<ASTDeclStmt>> fDecls;
  std::vector<std::shared_ptr<ASTStmt>> fBody;

  bool firstId = true;
  for (auto decl : ctx->nameDeclaration()) {
    visit(decl);
    if (firstId) {
      firstId = !firstId;
      fName = visitedDeclNode;
    } else {
      fParams.push_back(visitedDeclNode);
    }
  }

  bool isPoly = ctx->KPOLY() != nullptr;

  for (auto decl : ctx->declaration()) {
    visit(decl);
    fDecls.push_back(visitedDeclStmt);
  }

  for (auto stmt : ctx->statement()) {
    visit(stmt);
    fBody.push_back(visitedStmt);
  }

  // return statement is always the last statement in a TIP function body
  visit(ctx->returnStmt());
  fBody.push_back(visitedStmt);

  visitedFunction =
      std::make_shared<ASTFunction>(fName, fParams, fDecls, fBody, isPoly);

  LOG_S(1) << "Built AST node for function " << *visitedFunction;

  // Set source location
  visitedFunction->setLocation(ctx->getStart()->getLine(),
                               ctx->getStart()->getCharPositionInLine());
  return "";
}

Any ASTBuilder::visitNegNumber(TIPParser::NegNumberContext *ctx) {
  int val = std::stoi(ctx->NUMBER()->getText());
  val = -val;
  visitedExpr = std::make_shared<ASTNumberExpr>(val);

  LOG_S(1) << "Built AST node " << *visitedExpr;

  // Set source location
  visitedExpr->setLocation(ctx->getStart()->getLine(),
                           ctx->getStart()->getCharPositionInLine());
  return "";
} // LCOV_EXCL_LINE

/*
 * Unfortunately, the context types for binary expressions generated
 * by ANTLR are not organized into a sub-type hierarchy.  If they were
 * we could have a single method to construct binary expression nodes,
 * but as it stands we have some repetitive code to handle the different
 * context types.
 *
 * This might be improved by restructuring the grammar, but then another
 * mechanism for handling operator precedence would be needed.
 */
template <typename T>
void ASTBuilder::visitBinaryExpr(T *ctx, const std::string &op) {
  visit(ctx->expr(0));
  auto lhs = visitedExpr;

  visit(ctx->expr(1));
  auto rhs = visitedExpr;

  visitedExpr = std::make_shared<ASTBinaryExpr>(op, lhs, rhs);

  LOG_S(1) << "Built AST node " << *visitedExpr;

  // Set source location
  visitedExpr->setLocation(ctx->getStart()->getLine(),
                           ctx->getStart()->getCharPositionInLine());
}

Any ASTBuilder::visitAdditiveExpr(TIPParser::AdditiveExprContext *ctx) {
  visitBinaryExpr(ctx, opString(ctx->op->getType()));
  return "";
} // LCOV_EXCL_LINE

Any ASTBuilder::visitRelationalExpr(TIPParser::RelationalExprContext *ctx) {
  visitBinaryExpr(ctx, opString(ctx->op->getType()));
  return "";
} // LCOV_EXCL_LINE

Any ASTBuilder::visitMultiplicativeExpr(
    TIPParser::MultiplicativeExprContext *ctx) {
  visitBinaryExpr(ctx, opString(ctx->op->getType()));
  return "";
} // LCOV_EXCL_LINE

Any ASTBuilder::visitEqualityExpr(TIPParser::EqualityExprContext *ctx) {
  visitBinaryExpr(ctx, opString(ctx->op->getType()));
  return "";
} // LCOV_EXCL_LINE

Any ASTBuilder::visitBoolOps(TIPParser::BoolOpsContext *ctx) {
  visitBinaryExpr(ctx, opString(ctx->op->getType()));
  return "";
} // LCOV_EXCL_LINE


Any ASTBuilder::visitParenExpr(TIPParser::ParenExprContext *ctx) {
  visit(ctx->expr());
  // leave visitedExpr from expr unchanged
  return "";
} // LCOV_EXCL_LINE

Any ASTBuilder::visitNumExpr(TIPParser::NumExprContext *ctx) {
  int val = std::stoi(ctx->NUMBER()->getText());
  visitedExpr = std::make_shared<ASTNumberExpr>(val);

  LOG_S(1) << "Built AST node " << *visitedExpr;

  // Set source location
  visitedExpr->setLocation(ctx->getStart()->getLine(),
                           ctx->getStart()->getCharPositionInLine());
  return "";
} // LCOV_EXCL_LINE

Any ASTBuilder::visitBoolExpr(TIPParser::BoolExprContext *ctx) {
  bool val = ctx->op->getText() == "true"; 
  visitedExpr = std::make_shared<ASTBoolExpr>(val);

  LOG_S(1) << "Built AST node " << *visitedExpr;

  // Set source location
  visitedExpr->setLocation(ctx->getStart()->getLine(),
                           ctx->getStart()->getCharPositionInLine());
  return "";
} // LCOV_EXCL_LINEs

Any ASTBuilder::visitArrayIndexingExpr(TIPParser::ArrayIndexingExprContext *ctx) {
  visit(ctx->expr(0));
  auto arr = visitedExpr;

  visit(ctx->expr(1));
  auto idx = visitedExpr;

  visitedExpr = std::make_shared<ASTIndexingExpr>(arr, idx);

  LOG_S(1) << "Built AST node " << *visitedExpr;

  // Set source location
  visitedExpr->setLocation(ctx->getStart()->getLine(),
                           ctx->getStart()->getCharPositionInLine());
  return "";
} // LCOV_EXCL_LINE// LCOV_EXCL_LINE

Any ASTBuilder::visitVarExpr(TIPParser::VarExprContext *ctx) {
  std::string name = ctx->IDENTIFIER()->getText();
  visitedExpr = std::make_shared<ASTVariableExpr>(name);

  LOG_S(1) << "Built AST node " << *visitedExpr;

  // Set source location
  visitedExpr->setLocation(ctx->getStart()->getLine(),
                           ctx->getStart()->getCharPositionInLine());
  return "";
} // LCOV_EXCL_LINE

Any ASTBuilder::visitInputExpr(TIPParser::InputExprContext *ctx) {
  visitedExpr = std::make_shared<ASTInputExpr>();

  LOG_S(1) << "Built AST node " << *visitedExpr;

  // Set source location
  visitedExpr->setLocation(ctx->getStart()->getLine(),
                           ctx->getStart()->getCharPositionInLine());
  return "";
} // LCOV_EXCL_LINE

Any ASTBuilder::visitFunAppExpr(TIPParser::FunAppExprContext *ctx) {
  std::shared_ptr<ASTExpr> fExpr = nullptr;
  std::vector<std::shared_ptr<ASTExpr>> fArgs;

  // First expression is the function, the rest are the args
  bool first = true;
  for (auto e : ctx->expr()) {
    visit(e);
    if (first) {
      fExpr = visitedExpr;
      first = false;
    } else {
      fArgs.push_back(visitedExpr);
    }
  }

  visitedExpr = std::make_shared<ASTFunAppExpr>(fExpr, fArgs);

  LOG_S(1) << "Built AST node " << *visitedExpr;

  // Set source location
  visitedExpr->setLocation(ctx->getStart()->getLine(),
                           ctx->getStart()->getCharPositionInLine());
  return "";
} // LCOV_EXCL_LINE

Any ASTBuilder::visitAllocExpr(TIPParser::AllocExprContext *ctx) {
  visit(ctx->expr());
  visitedExpr = std::make_shared<ASTAllocExpr>(visitedExpr);

  LOG_S(1) << "Built AST node " << *visitedExpr;

  // Set source location
  visitedExpr->setLocation(ctx->getStart()->getLine(),
                           ctx->getStart()->getCharPositionInLine());
  return "";
} // LCOV_EXCL_LINE

Any ASTBuilder::visitRefExpr(TIPParser::RefExprContext *ctx) {
  visit(ctx->expr());
  visitedExpr = std::make_shared<ASTRefExpr>(visitedExpr);

  LOG_S(1) << "Built AST node " << *visitedExpr;

  // Set source location
  visitedExpr->setLocation(ctx->getStart()->getLine(),
                           ctx->getStart()->getCharPositionInLine());
  return "";
} // LCOV_EXCL_LINE

Any ASTBuilder::visitDeRefExpr(TIPParser::DeRefExprContext *ctx) {
  visit(ctx->expr());
  visitedExpr = std::make_shared<ASTDeRefExpr>(visitedExpr);

  LOG_S(1) << "Built AST node " << *visitedExpr;

  // Set source location
  visitedExpr->setLocation(ctx->getStart()->getLine(),
                           ctx->getStart()->getCharPositionInLine());
  return "";
} // LCOV_EXCL_LINE

Any ASTBuilder::visitNullExpr(TIPParser::NullExprContext *ctx) {
  visitedExpr = std::make_shared<ASTNullExpr>();

  LOG_S(1) << "Built AST node " << *visitedExpr;

  // Set source location
  visitedExpr->setLocation(ctx->getStart()->getLine(),
                           ctx->getStart()->getCharPositionInLine());
  return "";
} // LCOV_EXCL_LINE

Any ASTBuilder::visitRecordExpr(TIPParser::RecordExprContext *ctx) {
  std::vector<std::shared_ptr<ASTFieldExpr>> rFields;
  for (auto fn : ctx->fieldExpr()) {
    visit(fn);
    rFields.push_back(visitedFieldExpr);
  }

  visitedExpr = std::make_shared<ASTRecordExpr>(rFields);

  LOG_S(1) << "Built AST node " << *visitedExpr;

  // Set source location
  visitedExpr->setLocation(ctx->getStart()->getLine(),
                           ctx->getStart()->getCharPositionInLine());
  return "";
}

Any ASTBuilder::visitArrayLiteral(TIPParser::ArrayLiteralContext *ctx) {
  std::vector<std::shared_ptr<ASTExpr>> elements;
  for(int i = 0; i < ctx->expr().size(); i++) {
    visit(ctx->expr(i));
    elements.push_back(visitedExpr);
  }

  visitedExpr = std::make_shared<ASTArrayExpr>(elements);

  LOG_S(1) << "Built AST node " << *visitedExpr;

  // Set source location
  visitedExpr->setLocation(ctx->getStart()->getLine(),
                           ctx->getStart()->getCharPositionInLine());
  return "";
}

Any ASTBuilder::visitArrayOfExpr(TIPParser::ArrayOfExprContext *ctx) {
  visit(ctx->expr(0));
  auto first = visitedExpr;
  visit(ctx->expr(1));
  auto second = visitedExpr;

  visitedExpr = std::make_shared<ASTArrayOfExpr>(first, second);

  LOG_S(1) << "Built AST node " << *visitedExpr;

  // Set source location
  visitedExpr->setLocation(ctx->getStart()->getLine(),
                           ctx->getStart()->getCharPositionInLine());
  return "";
}

Any ASTBuilder::visitArrayLenExpr(TIPParser::ArrayLenExprContext *ctx) {
  visit(ctx->expr());
  visitedExpr = std::make_shared<ASTArrayLenExpr>(visitedExpr);

  LOG_S(1) << "Built AST node " << *visitedExpr;

  // Set source location
  visitedExpr->setLocation(ctx->getStart()->getLine(),
                           ctx->getStart()->getCharPositionInLine());
  return "";
} // LCOV_EXCL_LINE

Any ASTBuilder::visitTernaryExpr(TIPParser::TernaryExprContext *ctx) {
  visit(ctx->expr(0));
  auto cond = visitedExpr;
  visit(ctx->expr(1));
  auto thenExpr = visitedExpr;
  visit(ctx->expr(2));
  auto elseExpr = visitedExpr;

  visitedExpr = std::make_shared<ASTTernaryExpr>(cond, thenExpr, elseExpr);

  LOG_S(1) << "Built AST node " << *visitedExpr;

  // Set source location
  visitedExpr->setLocation(ctx->getStart()->getLine(),
                           ctx->getStart()->getCharPositionInLine());
  return "";
}

Any ASTBuilder::visitFieldExpr(TIPParser::FieldExprContext *ctx) {
  std::string fName = ctx->IDENTIFIER()->getText();
  visit(ctx->expr());
  visitedFieldExpr = std::make_shared<ASTFieldExpr>(fName, visitedExpr);

  LOG_S(1) << "Built AST node " << *visitedExpr;

  // Set source location
  visitedFieldExpr->setLocation(ctx->getStart()->getLine(),
                                ctx->getStart()->getCharPositionInLine());
  return "";
}

Any ASTBuilder::visitAccessExpr(TIPParser::AccessExprContext *ctx) {
  std::string fName = ctx->IDENTIFIER()->getText();

  visit(ctx->expr());
  auto rExpr = visitedExpr;

  visitedExpr = std::make_shared<ASTAccessExpr>(rExpr, fName);

  LOG_S(1) << "Built AST node " << *visitedExpr;

  // Set source location
  visitedExpr->setLocation(ctx->getStart()->getLine(),
                           ctx->getStart()->getCharPositionInLine());
  return "";
}

Any ASTBuilder::visitDeclaration(TIPParser::DeclarationContext *ctx) {
  std::vector<std::shared_ptr<ASTDeclNode>> dVars;
  for (auto decl : ctx->nameDeclaration()) {
    visit(decl);
    dVars.push_back(visitedDeclNode);
  }
  visitedDeclStmt = std::make_shared<ASTDeclStmt>(dVars);

  LOG_S(1) << "Built AST node " << *visitedDeclStmt;

  // Set source location
  visitedDeclStmt->setLocation(ctx->getStart()->getLine(),
                               ctx->getStart()->getCharPositionInLine());
  return "";
}

Any ASTBuilder::visitNameDeclaration(TIPParser::NameDeclarationContext *ctx) {
  std::string name = ctx->IDENTIFIER()->getText();
  visitedDeclNode = std::make_shared<ASTDeclNode>(name);

  LOG_S(1) << "Built AST node " << *visitedDeclNode;

  // Set source location
  visitedDeclNode->setLocation(ctx->getStart()->getLine(),
                               ctx->getStart()->getCharPositionInLine());
  return "";
}

Any ASTBuilder::visitBlockStmt(TIPParser::BlockStmtContext *ctx) {
  std::vector<std::shared_ptr<ASTStmt>> bStmts;
  for (auto s : ctx->statement()) {
    visit(s);
    bStmts.push_back(visitedStmt);
  }
  visitedStmt = std::make_shared<ASTBlockStmt>(bStmts);

  LOG_S(1) << "Built AST node " << *visitedStmt;

  // Set source location
  visitedStmt->setLocation(ctx->getStart()->getLine(),
                           ctx->getStart()->getCharPositionInLine());
  return "";
}

Any ASTBuilder::visitWhileStmt(TIPParser::WhileStmtContext *ctx) {
  visit(ctx->expr());
  auto cond = visitedExpr;
  visit(ctx->statement());
  auto body = visitedStmt;
  visitedStmt = std::make_shared<ASTWhileStmt>(cond, body);

  LOG_S(1) << "Built AST node " << *visitedStmt;

  // Set source location
  visitedStmt->setLocation(ctx->getStart()->getLine(),
                           ctx->getStart()->getCharPositionInLine());
  return "";
}

Any ASTBuilder::visitForStmt(TIPParser::ForStmtContext *ctx) {
  visit(ctx->expr(0));
  auto item = visitedExpr;
  
  std::shared_ptr<ASTExpr> iterator = nullptr;
  std::shared_ptr<ASTExpr> range_start = nullptr;
  std::shared_ptr<ASTExpr> range_end = nullptr;
  std::shared_ptr<ASTExpr> increment = nullptr;

  if(ctx->expr().size() == 2) {
    visit(ctx->expr(1));
    iterator = visitedExpr;
  } else {
    visit(ctx->expr(1));
    range_start = visitedExpr;
    visit(ctx->expr(2));
    range_end = visitedExpr;

    if(ctx->expr().size() == 4) {
      visit(ctx->expr(3));
      increment = visitedExpr;
    }
  }

  visit(ctx->statement());
  auto body = visitedStmt;

  visitedStmt = std::make_shared<ASTForStmt>(item, iterator, range_start, range_end, increment, body);

  LOG_S(1) << "Built AST node " << *visitedStmt;

  // Set source location
  visitedStmt->setLocation(ctx->getStart()->getLine(),
                           ctx->getStart()->getCharPositionInLine());
  return "";
}


Any ASTBuilder::visitIfStmt(TIPParser::IfStmtContext *ctx) {
  visit(ctx->expr());
  auto cond = visitedExpr;
  visit(ctx->statement(0));
  auto thenBody = visitedStmt;

  // else is optional
  std::shared_ptr<ASTStmt> elseBody = nullptr;
  if (ctx->statement().size() == 2) {
    visit(ctx->statement(1));
    elseBody = visitedStmt;
  }

  visitedStmt = std::make_shared<ASTIfStmt>(cond, thenBody, elseBody);

  LOG_S(1) << "Built AST node " << *visitedStmt;

  // Set source location
  visitedStmt->setLocation(ctx->getStart()->getLine(),
                           ctx->getStart()->getCharPositionInLine());
  return "";
}
 
Any ASTBuilder::visitUpdateStmt(TIPParser::UpdateStmtContext *ctx) {
  visit(ctx->expr());
  visitedStmt = std::make_shared<ASTUpdateStmt>(visitedExpr, opString(ctx->op->getType()));

  LOG_S(1) << "Built AST node " << *visitedStmt;

  // Set source location
  visitedStmt->setLocation(ctx->getStart()->getLine(),
                           ctx->getStart()->getCharPositionInLine());
  return "";
} // LCOV_EXCL_LINE

Any ASTBuilder::visitOutputStmt(TIPParser::OutputStmtContext *ctx) {
  visit(ctx->expr());
  visitedStmt = std::make_shared<ASTOutputStmt>(visitedExpr);

  LOG_S(1) << "Built AST node " << *visitedStmt;

  // Set source location
  visitedStmt->setLocation(ctx->getStart()->getLine(),
                           ctx->getStart()->getCharPositionInLine());
  return "";
} // LCOV_EXCL_LINE

Any ASTBuilder::visitErrorStmt(TIPParser::ErrorStmtContext *ctx) {
  visit(ctx->expr());
  visitedStmt = std::make_shared<ASTErrorStmt>(visitedExpr);

  LOG_S(1) << "Built AST node " << *visitedStmt;

  // Set source location
  visitedStmt->setLocation(ctx->getStart()->getLine(),
                           ctx->getStart()->getCharPositionInLine());
  return "";
} // LCOV_EXCL_LINE

Any ASTBuilder::visitReturnStmt(TIPParser::ReturnStmtContext *ctx) {
  visit(ctx->expr());
  visitedStmt = std::make_shared<ASTReturnStmt>(visitedExpr);

  LOG_S(1) << "Built AST node " << *visitedStmt;

  // Set source location
  visitedStmt->setLocation(ctx->getStart()->getLine(),
                           ctx->getStart()->getCharPositionInLine());
  return "";
} // LCOV_EXCL_LINE

Any ASTBuilder::visitAssignStmt(TIPParser::AssignStmtContext *ctx) {
  visit(ctx->expr(0));
  auto lhs = visitedExpr;
  visit(ctx->expr(1));
  auto rhs = visitedExpr;
  visitedStmt = std::make_shared<ASTAssignStmt>(lhs, rhs);

  LOG_S(1) << "Built AST node " << *visitedStmt;

  // Set source location
  visitedStmt->setLocation(ctx->getStart()->getLine(),
                           ctx->getStart()->getCharPositionInLine());
  return "";
}

Any ASTBuilder::visitNotExpr(TIPParser::NotExprContext *ctx) {
  visit(ctx->expr());
  visitedExpr = std::make_shared<ASTNotExpr>(visitedExpr);

  LOG_S(1) << "Built AST node " << *visitedExpr;

  // Set source location
  visitedExpr->setLocation(ctx->getStart()->getLine(),
                           ctx->getStart()->getCharPositionInLine());
  return "";
} // LCOV_EXCL_LINE

Any ASTBuilder::visitNegExpr(TIPParser::NegExprContext *ctx) {
  visit(ctx->expr());
  visitedExpr = std::make_shared<ASTNegExpr>(visitedExpr);

  LOG_S(1) << "Built AST node " << *visitedExpr;

  // Set source location
  visitedExpr->setLocation(ctx->getStart()->getLine(),
                           ctx->getStart()->getCharPositionInLine());
  return "";
} // LCOV_EXCL_LINE


std::string ASTBuilder::generateSHA256(std::string tohash) {
  std::vector<unsigned char> hash(picosha2::k_digest_size);
  picosha2::hash256(tohash.begin(), tohash.end(), hash.begin(), hash.end());
  return picosha2::bytes_to_hex_string(hash.begin(), hash.end());
}
