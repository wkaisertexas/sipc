#pragma once

#include "ASTExpr.h"

/*! \brief Class for getting an array length
 */
class ASTArrayLenExpr : public ASTExpr {
  std::shared_ptr<ASTExpr> PTR;

public:
  std::vector<std::shared_ptr<ASTNode>> getChildren() override;
  ASTArrayLenExpr(std::shared_ptr<ASTExpr> PTR) : PTR(PTR) {}
  ASTExpr *getPtr() const { return PTR.get(); }
  void accept(ASTVisitor *visitor) override;
  llvm::Value *codegen() override;

protected:
  std::ostream &print(std::ostream &out) const override;
};
