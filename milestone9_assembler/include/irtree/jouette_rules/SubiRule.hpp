#pragma once

#include "irtree/jouette_rules/Rule.hpp"


namespace Jouette {

class SubiRule: public Rule {
 public:
  bool IsSuitable(std::shared_ptr<IRT::BaseElement> element) const override;
};

}
