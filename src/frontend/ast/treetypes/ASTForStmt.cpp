#include "ASTForStmt.h"
#include "ASTVisitor.h"
#include <sstream>

void ASTForStmt::accept(ASTVisitor *visitor) {
  if (visitor->visit(this)) {
    getItem()->accept(visitor);
    if(ITERATOR) getIterator()->accept(visitor);
    if(RANGE_START) getRangeStart()->accept(visitor);
    if(RANGE_END) getRangeEnd()->accept(visitor);
    if(INCREMENT) getIncrement()->accept(visitor);
    getBody()->accept(visitor);
  }
  visitor->endVisit(this);
}

std::ostream &ASTForStmt::print(std::ostream &out) const {
  std::stringstream iter;
  if(getIterator()) {
    iter << *getIterator();
  } else {
    iter << *getRangeStart() << ".." << *getRangeEnd();
  }
  std::stringstream incr;
  if(getIncrement()) {
    incr << " by " << *getIncrement();
  }

  out << "for (" << *getItem() << " : " << iter .str() << incr.str() << ") " << *getBody();
  
  return out;
}

std::vector<std::shared_ptr<ASTNode>> ASTForStmt::getChildren() {
  std::vector<std::shared_ptr<ASTNode>> children;
  children.push_back(ITEM);
  if(ITERATOR) children.push_back(ITERATOR);
  if(RANGE_START) children.push_back(RANGE_START);
  if(RANGE_END) children.push_back(RANGE_END);
  if(INCREMENT) children.push_back(INCREMENT);
  children.push_back(BODY);
  return children;
}
