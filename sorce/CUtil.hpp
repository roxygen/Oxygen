#ifndef _C_UTIL_
#define _C_UTIL_
#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <stdarg.h>
typedef struct FPoint {
    float x;
    float y;
} FPoint;
namespace Util {
    const char * CPath(std::string filename);
    std::string SPath(std::string filename);
    std::string SFormat( const char* frmt, ... );
    int cstrmask(char*a, char*m);
    int StrMask(std::string &src, std::string &mask);
}
#endif
