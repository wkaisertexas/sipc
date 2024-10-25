#pragma once

#include "ASTExpr.h"

/*! \brief Class for boolean literals.
 */
class ASTBoolExpr : public ASTExpr {
  bool VAL;

public:
  ASTBoolExpr(bool VAL) : VAL(VAL) {}
  int getValue() const { return VAL; }
  void accept(ASTVisitor *visitor) override;
  llvm::Value *codegen() override;

protected:
  std::ostream &print(std::ostream &out) const override;
};
