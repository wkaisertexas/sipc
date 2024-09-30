#include "ASTUpdateStmt.h"
#include "ASTVisitor.h"

void ASTUpdateStmt::accept(ASTVisitor *visitor) {
  if (visitor->visit(this)) {
    getArg()->accept(visitor);
  }
  visitor->endVisit(this);
}

std::ostream &ASTUpdateStmt::print(std::ostream &out) const {
  if(getOp()) {
    out << *getArg() << "++;";
  } else {
    out << *getArg() << "--;";
  }
  
  return out;
}

std::vector<std::shared_ptr<ASTNode>> ASTUpdateStmt::getChildren() {
  std::vector<std::shared_ptr<ASTNode>> children;
  children.push_back(ARG);
  return children;
}
