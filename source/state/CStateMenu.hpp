#ifndef _C_STATE_GAME_
#define _C_STATE_GAME_
#include "../CState.hpp"
#include "../CEvent.hpp"
#include <iostream>
#include <string>
class CApp;
class CStateMenu: public CState, public CEvent {
public:
    CStateMenu(CApp * App);
    void Enter  ();
    void Exit   ();
    void Sleep  ();
    void Wakeup ();
    void Update ();
    void Handle(SDL_Event * Event);
    void Render ();
    // function reload from CEvent:
    void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);
    void OnRButtonUp(int mX, int mY);
    void Escape();
private:
    CApp * mApp;
};
#endif
