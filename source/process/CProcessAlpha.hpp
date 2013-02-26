#ifndef _C_PROCESS_ALPHA_
#define _C_PROCESS_ALPHA_
#include <SDL/SDL.h>
#include "../CProcess.hpp"
#include <list>
class CApp;
class CAlpha : public CProcess {
public:
    CAlpha(CApp *App, std::string ID, float ToAlpha, Uint32 Time);
    CAlpha() {};
    void Enter ();
    void Exit  ();
    void Sleep () {};
    void Wakeup() {};
    int  Update();
    void End   ();
private:
    std::string mOID;
    float mFromAlpha;
    float mToAlpha;
    float mSpeed;
    Uint32 mTimeEnd;
    Uint32 mTime;
    bool mFirst;
    std::list<float> mAlphaList;
    CApp * mApp;
};
#endif
