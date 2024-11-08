#include "TipArray.h"
#include "TipTypeVisitor.h"

#include <sstream>

TipArray::TipArray(std::shared_ptr<TipType> of)
    : TipCons(std::move(std::vector<std::shared_ptr<TipType>>{of})) {}

bool TipArray::operator==(const TipType &other) const {
  auto otherTipArray = dynamic_cast<const TipArray *>(&other);
  if (!otherTipArray) {
    return false;
  }

  return *arguments.front() == *otherTipArray->getType();
}

bool TipArray::operator!=(const TipType &other) const {
  return !(*this == other);
}

std::ostream &TipArray::print(std::ostream &out) const {
  out << "[" << *arguments.front() << "]";
  return out;
}

std::shared_ptr<TipType> TipArray::getType() const {
  return arguments.front();
}

void TipArray::accept(TipTypeVisitor *visitor) {
  if (visitor->visit(this)) {
    for (auto a : arguments) {
      a->accept(visitor);
    }
  }
  visitor->endVisit(this);
}
