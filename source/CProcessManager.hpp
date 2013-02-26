#ifndef _C_PROCESS_MANAGER_
#define _C_PROCESS_MANAGER_
#include <SDL/SDL.h>
#include <list>
#include <string>
#include <iostream>
//#include "CProcess.hpp"
class CProcess;
class CApp;
class CProcessManager {
private:
    std::list<CProcess*> mProcessList;
    std::list<CProcess*>::iterator mIt;
    Uint32 mWaitTime;
public:
    CProcessManager() {}
    void Create (CProcess* Process);
    CProcess * Obj();
    void Delete ();
    void DeleteAll();
    void Sleep  ();
    void Wakeup ();
    void Update ();
    void End    ();
    void EndAll ();
protected:
    
};
#endif
