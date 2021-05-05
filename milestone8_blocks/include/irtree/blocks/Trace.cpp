#include "irtree/blocks/Trace.hpp"
#include "irtree/blocks/NodeAdapter.hpp"


namespace IRT {

Trace::Trace(std::vector<std::shared_ptr<Block>> trace)
  : trace_{trace} {
}

void Trace::PrintTrace(const std::string& filename) const {
  static std::ofstream stream(filename);

  for (auto&& it : trace_) {
    stream << it->GetLabelName() << " -> ";
  }
  stream << std::endl;
}

}
