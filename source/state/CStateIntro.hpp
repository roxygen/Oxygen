#ifndef _C_STATE_INTRO_
#define _C_STATE_INTRO_
#include "../CState.hpp"
#include "../CEvent.hpp"
#include <iostream>
#include <string>
class CApp;
class CStateIntro: public CState {
public:
    CStateIntro ();
    static CStateIntro * Instance();
    void Enter  (CApp * App);
    void Exit   ();
    void Sleep  ();
    void Wakeup ();
    void Handle(SDL_Event * Event);
    void Update ();
    void Render ();
    // function reload from CEvent:
    void OnKeyUp (SDLKey sym, SDLMod mod, Uint16 unicode);
    
private:
    CApp * mApp;
    static CStateIntro mStateIntro;
};
#endif
