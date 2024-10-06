#include "ASTBoolExpr.h"
#include "ASTVisitor.h"

#include <iostream>

void ASTBoolExpr::accept(ASTVisitor *visitor) {
  visitor->visit(this);
  visitor->endVisit(this);
}

std::ostream &ASTBoolExpr::print(std::ostream &out) const {
  out << getValue() ? "true" : "false";
  return out;
}
