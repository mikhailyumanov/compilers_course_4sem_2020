#include "debug.h"

#if DEBUG_ON

#include <fstream>

extern std::ofstream debug_output_stream;

std::ostream& debug_output() {
  return debug_output_stream;
//  return std::cout;
}

#endif
