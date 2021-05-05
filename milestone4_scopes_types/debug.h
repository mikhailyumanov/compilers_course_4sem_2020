#pragma once

#define DEBUG_ON false

#if DEBUG_ON
#define DEBUG_START std::cout
#define DEBUG(expr) << expr << ' '
#define DEBUG_FINISH << std::endl;
#define DEBUG_SINGLE(expr) std::cout << expr << std::endl;
#else
#define DEBUG_START ;
#define DEBUG(expr) ;
#define DEBUG_FINISH ;
#define DEBUG_SINGLE(expr) ;
#endif

