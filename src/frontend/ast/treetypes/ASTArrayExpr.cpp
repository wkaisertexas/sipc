#include "ASTArrayExpr.h"
#include "ASTExpr.h"
#include "ASTVisitor.h"

#include <iostream>

void ASTArrayExpr::accept(ASTVisitor *visitor) {
  if(visitor->visit(this)) {
    for(std::shared_ptr<ASTExpr> element : this->ELEMENTS) {
      element->accept(visitor);
    }
  }
  visitor->endVisit(this);
}

std::ostream &ASTArrayExpr::print(std::ostream &out) const {
  out << "[";
  for(int i = 0; i < this->ELEMENTS.size(); i++) {
    out << *this->ELEMENTS[i];
    if(i != this->ELEMENTS.size() - 1) {
      out << ", ";
    }
  }
  out << "]";

  return out;
}
