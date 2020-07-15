#pragma once

#define DEBUG_ON true

#if DEBUG_ON

#include <fstream>
extern std::ofstream debug_output;
#define DEBUG_START debug_output
#define DEBUG(expr) << expr << ' '
#define DEBUG_FINISH << std::endl;
#define DEBUG_SINGLE(expr) debug_output << expr << std::endl;

#else

#define DEBUG_START ;
#define DEBUG(expr) ;
#define DEBUG_FINISH ;
#define DEBUG_SINGLE(expr) ;

#endif

