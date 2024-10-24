#include "ASTIndexingExpr.h"
#include "ASTVisitor.h"

void ASTIndexingExpr::accept(ASTVisitor *visitor) {
  if (visitor->visit(this)) {
    getArr()->accept(visitor);
    getIdx()->accept(visitor);
  }
  visitor->endVisit(this);
}

std::ostream &ASTIndexingExpr::print(std::ostream &out) const {
  out << *getArr() << "[" << *getIdx() << "]";
  return out;
}

std::vector<std::shared_ptr<ASTNode>> ASTIndexingExpr::getChildren() {
  std::vector<std::shared_ptr<ASTNode>> children;

  children.push_back(ARR);
  children.push_back(IDX);

  return children;
}
