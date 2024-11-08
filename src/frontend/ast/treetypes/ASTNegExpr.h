#pragma once

#include "ASTExpr.h"

/*! \brief Class for not expressions..
 */
class ASTNegExpr : public ASTExpr {
  std::shared_ptr<ASTExpr> ARG;

public:
  std::vector<std::shared_ptr<ASTNode>> getChildren() override;
  ASTNegExpr(std::shared_ptr<ASTExpr> ARG) : ARG(ARG) {}
  ASTExpr *getArg() const { return ARG.get(); }
  void accept(ASTVisitor *visitor) override;
  llvm::Value *codegen() override;

protected:
  std::ostream &print(std::ostream &out) const override;
};
