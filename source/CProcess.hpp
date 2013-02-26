#ifndef _C_PROCESS_
#define _C_PROCESS_
class CApp;
class CProcess {
public:
    virtual void Enter ()=0;
    virtual void Exit  ()=0;
    virtual void Sleep ()=0;
    virtual void Wakeup()=0;
    virtual int  Update()=0;
    virtual void End   ()=0;
protected:
    CProcess() {}
};
#endif
