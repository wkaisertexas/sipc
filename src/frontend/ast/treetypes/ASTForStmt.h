#pragma once

#include "ASTExpr.h"
#include "ASTStmt.h"

/*! \brief Class for a for loop.
 */
class ASTForStmt : public ASTStmt {
  std::shared_ptr<ASTExpr> ITEM;
  std::shared_ptr<ASTExpr> ITERATOR;
  std::shared_ptr<ASTStmt> BODY;
  std::shared_ptr<ASTExpr> RANGE_START;
  std::shared_ptr<ASTExpr> RANGE_END;
  std::shared_ptr<ASTExpr> INCREMENT;

public:
  std::vector<std::shared_ptr<ASTNode>> getChildren() override;
  ASTForStmt(
    std::shared_ptr<ASTExpr> ITEM, 
    std::shared_ptr<ASTExpr> ITERATOR,  
    std::shared_ptr<ASTExpr> RANGE_START,  
    std::shared_ptr<ASTExpr> RANGE_END,  
    std::shared_ptr<ASTExpr> INCREMENT,  
    std::shared_ptr<ASTStmt> BODY
  ): ITEM(ITEM), ITERATOR(ITERATOR), RANGE_START(RANGE_START), RANGE_END(RANGE_END), INCREMENT(INCREMENT), BODY(BODY)
  {}
  ASTExpr *getItem() const { return ITEM.get(); }
  ASTExpr *getIterator() const { return ITERATOR.get(); }
  ASTExpr *getRangeStart() const { return RANGE_START.get(); }
  ASTExpr *getRangeEnd() const { return RANGE_END.get(); }
  ASTExpr *getIncrement() const { return INCREMENT.get(); }
  ASTStmt *getBody() const { return BODY.get(); }
  void accept(ASTVisitor *visitor) override;
  llvm::Value *codegen() override;

protected:
  std::ostream &print(std::ostream &out) const override;
};
