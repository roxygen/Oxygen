#include "CUtil.hpp"
namespace Util{
const char * CPath(std::string filename) {
    char * buffer = new char[1024];
    ssize_t _strlen= readlink("/proc/self/exe", buffer, 1024);
    buffer[_strlen] = 0;
    std::string path;
    for(int i = 0;i < _strlen; i++)
        path.push_back(buffer[i]);
    delete [] buffer;
    path.erase(path.begin()+path.rfind('/')+1, path.end() );
    std::cout << path + filename <<'\n';
    return (path + filename).c_str();
}

std::string SPath(std::string filename) {
    char * buffer = new char[1024];
    ssize_t _strlen= readlink("/proc/self/exe", buffer, 1024);
    buffer[_strlen] = 0;
    std::string path;
    for(int i = 0;i < _strlen; i++)
        path.push_back(buffer[i]);
    delete [] buffer;
    path.erase(path.begin()+path.rfind('/')+1, path.end() );
    std::cout << path + filename <<'\n';
    return path + filename;
}
std::string SFormat( const char* frmt, ... ) {
    static char buf[ 4096 ];
    buf[ 0 ] = 0;

    va_list args;
    va_start( args, frmt );
    vsnprintf( buf, 4096, frmt, args );
    va_end( args );

    return std::string( buf );
}
int cstrmask(const char *a, const char *m) {
    for(;;a++,m++)
        switch(*m) {
            case 0:
                return !*a;
        
            case '?':
                if(!*a)
                    return 0;
                continue;
            case '*':
                for(m++;;a++) {
                    if(cstrmask(a,m))
                        return 1;
                    if(!*a)
                        return !*m;
                }
            default:
                if(*a!=*m)
                    return 0;
                if(!*a)
                    return !*m;
        }
}
int StrMask(std::string &src, std::string & mask) {
    return cstrmask(src.c_str(), mask.c_str());
}
} // namespace Util
