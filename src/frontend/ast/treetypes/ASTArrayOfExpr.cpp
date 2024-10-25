#include "ASTArrayOfExpr.h"
#include "ASTExpr.h"
#include "ASTVisitor.h"

#include <iostream>

void ASTArrayOfExpr::accept(ASTVisitor *visitor) {
  if(visitor->visit(this)) {
    getE1()->accept(visitor);
    getE2()->accept(visitor);
  }
  visitor->endVisit(this);
}

std::ostream &ASTArrayOfExpr::print(std::ostream &out) const {
  out << "[" << *this->E1 << " of " << *this->E2 << "]";
  return out;
}
