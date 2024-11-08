#pragma once

#include "TipCons.h"
#include "TipType.h"
#include <string>

/*!
 * \class TipBool
 *
 * \brief A proper type representing a boolean
 */
class TipBool : public TipCons {
public:
  TipBool();

  bool operator==(const TipType &other) const override;
  bool operator!=(const TipType &other) const override;

  void accept(TipTypeVisitor *visitor) override;

protected:
  std::ostream &print(std::ostream &out) const override;
};
