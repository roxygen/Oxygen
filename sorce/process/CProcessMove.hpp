#ifndef _C_PROCESS_MOVE_
#define _C_PROCESS_MOVE_
#include <SDL/SDL.h>
#include "../CProcess.hpp"
#include <list>
class CApp;
class CMove : public CProcess {
public:
    CMove(CApp *App, std::string ID, float ToX, float ToY, Uint32 Time);
    CMove() {};
    void Enter ();
    void Exit  ();
    void Sleep () {};
    void Wakeup() {};
    int  Update();
    void End   ();
    int  GetID();
    void SetID(int ID);
private:
    int mID;
    std::string mOID;
    float mToX;
    float mToY;
    float mFromX;
    float mFromY;
    float mA;
    float mSpeed;
    Uint32 mTimeEnd;
    Uint32 mTime;
    bool mFirst;
    std::list<float> mPointList;
    CApp * mApp;
};
#endif
