#include "ASTTernaryExpr.h"
#include "ASTVisitor.h"

void ASTTernaryExpr::accept(ASTVisitor *visitor) {
  if (visitor->visit(this)) {
    getCondition()->accept(visitor);
    getThen()->accept(visitor);
    getElse()->accept(visitor);
  }
  visitor->endVisit(this);
}

std::ostream &ASTTernaryExpr::print(std::ostream &out) const {
  out << *getCondition() << " ? " << *getThen() << " : " << *getElse();

  return out;
}

std::vector<std::shared_ptr<ASTNode>> ASTTernaryExpr::getChildren() {
  std::vector<std::shared_ptr<ASTNode>> children;

  children.push_back(COND); 
  children.push_back(THEN);
  children.push_back(ELSE);

  return children;
}
