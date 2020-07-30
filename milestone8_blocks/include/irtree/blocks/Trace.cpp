#include "irtree/blocks/Trace.hpp"


namespace IRT {

Trace::Trace(std::shared_ptr<Block> first, std::shared_ptr<Block> last) 
  : first_{first}, last_{last} {
}

void Trace::PrintTrace(const std::string& filename) const {
  static std::ofstream stream(filename + "_traces");

  stream << "Start trace" << std::endl;
  for (auto it = start_; it != last_; it = GetNext(it)) {
    stream << it->GetLabelName() << " -> ";
  }
  stream << last_->GetLabelName() << std::endl << std::endl;
}

}
