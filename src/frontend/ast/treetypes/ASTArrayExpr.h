#pragma once

#include "ASTExpr.h"

/*! \brief Class for array literals.
 */
class ASTArrayExpr : public ASTExpr {
  std::vector<std::shared_ptr<ASTExpr>> ELEMENTS;

public:
  std::vector<std::shared_ptr<ASTNode>> getChildren() override;
  ASTArrayExpr(std::vector<std::shared_ptr<ASTExpr>> ELEMENTS) : ELEMENTS(ELEMENTS) {}
  std::vector<std::shared_ptr<ASTExpr>> getElements() const { return ELEMENTS; }
  void accept(ASTVisitor *visitor) override;
  llvm::Value *codegen() override;

protected:
  std::ostream &print(std::ostream &out) const override;
};
