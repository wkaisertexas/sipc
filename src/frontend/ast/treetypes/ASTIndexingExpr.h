#pragma once

#include "ASTExpr.h"

/*! \brief Class for getting the value of an array index
 */
class ASTIndexingExpr : public ASTExpr {
  std::shared_ptr<ASTExpr> ARR;
  std::shared_ptr<ASTExpr> IDX;

public:
  std::vector<std::shared_ptr<ASTNode>> getChildren() override;
  ASTIndexingExpr(std::shared_ptr<ASTExpr> ARR, std::shared_ptr<ASTExpr> IDX) : ARR(ARR), IDX(IDX) {}
  ASTExpr *getArr() const { return ARR.get(); }
  ASTExpr *getIdx() const { return IDX.get(); }
  void accept(ASTVisitor *visitor) override;
  llvm::Value *codegen() override;

protected:
  std::ostream &print(std::ostream &out) const override;
};
