#ifndef _C_STATE_TITLE_
#define _C_STATE_TITLE_
#include "../CState.hpp"
#include "../CEvent.hpp"
#include <iostream>
#include <string>
class CApp;
class CStateTitle: public CState {
public:
    CStateTitle ();
    void Enter  (CApp * App);
    void Exit   ();
    void Sleep  ();
    void Wakeup ();
    void Handle(SDL_Event * Event);
    void Update ();
    void Render ();
    // function reload from CEvent:
    //void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);
    //void Escape();
    static CStateTitle * Instance();
private:
    CApp * mApp;
    static CStateTitle mStateTitle;
};
#endif
