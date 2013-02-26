#ifndef _C_STATE_GAME_
#define _C_STATE_GAME_
#include "../CState.hpp"
#include <iostream>
#include <string>
class CApp;
class CStateGame: public CState {
public:
    CStateGame ();
    void Enter  (CApp * App);
    void Exit   ();
    void Sleep  ();
    void Wakeup ();
    void Handle(SDL_Event * Event);
    void Update ();
    void Render ();
    // function reload from CEvent:
    //void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);
    //void OnRButtonUp(int mX, int mY);
    //void Escape();
    static CStateGame * Instance();
private:
    static CStateGame mStateGame;
    CApp * mApp;
    
};
#endif
