#pragma once

#include "ASTExpr.h"

/*! \brief Class for array of expressions.
 */
class ASTArrayOfExpr : public ASTExpr {
  std::shared_ptr<ASTExpr> E1;
  std::shared_ptr<ASTExpr> E2;

public:
  ASTArrayOfExpr(std::shared_ptr<ASTExpr> E1, std::shared_ptr<ASTExpr> E2) : E1(E1), E2(E2) {}
  
  std::shared_ptr<ASTExpr> getE1() const { return E1; }
  std::shared_ptr<ASTExpr> getE2() const { return E2; }

  void accept(ASTVisitor *visitor) override;
  llvm::Value *codegen() override;

protected:
  std::ostream &print(std::ostream &out) const override;
};
