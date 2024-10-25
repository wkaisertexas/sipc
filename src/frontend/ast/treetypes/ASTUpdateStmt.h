#pragma once

#include "ASTExpr.h"
#include "ASTStmt.h"

/*! \brief Class for local variable declaration statement
 */
class ASTUpdateStmt : public ASTStmt {
  std::shared_ptr<ASTExpr> ARG;
  bool INCREMENT;

public:
  std::vector<std::shared_ptr<ASTNode>> getChildren() override;
  ASTUpdateStmt(std::shared_ptr<ASTExpr> ARG, std::string op) : ASTUpdateStmt(ARG, op == "++") {}
  ASTUpdateStmt(std::shared_ptr<ASTExpr> ARG, bool INCREMENT) : ARG(ARG), INCREMENT(INCREMENT) {}
  bool getIncrement() const { return INCREMENT; }
  ASTExpr *getArg() const { return ARG.get(); }
  void accept(ASTVisitor *visitor) override;
  llvm::Value *codegen() override;

protected:
  std::ostream &print(std::ostream &out) const override;
};