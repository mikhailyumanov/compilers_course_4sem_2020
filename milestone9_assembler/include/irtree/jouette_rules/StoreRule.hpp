#pragma once

#include "irtree/jouette_rules/Rule.hpp"


namespace Jouette {

class StoreRule: public Rule {
 public:
  bool IsSuitable(std::shared_ptr<IRT::BaseElement> element) const override;
};

}
