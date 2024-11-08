#include "ASTNegExpr.h"
#include "ASTVisitor.h"

void ASTNegExpr::accept(ASTVisitor *visitor) {
  if (visitor->visit(this)) {
    getArg()->accept(visitor);
  }
  visitor->endVisit(this);
}

std::ostream &ASTNegExpr::print(std::ostream &out) const {
  out << "-(" << *getArg() << ")";
  return out;
}

std::vector<std::shared_ptr<ASTNode>> ASTNegExpr::getChildren() {
  std::vector<std::shared_ptr<ASTNode>> children;
  children.push_back(ARG);
  return children;
} // LCOV_EXCL_LINE
