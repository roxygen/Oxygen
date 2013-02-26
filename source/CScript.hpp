#ifndef CSCRIPT_HPP
#define CSCRIPT_HPP
#include <SDL/SDL.h>
#include <lua.hpp>
class CApp;
class CScript {
private:
    lua_State * mL;
public:
    void Do(std::string Scr);
    void Sleep();
    void Wakeup();
};

#endif // CSCRIPT_HPP
