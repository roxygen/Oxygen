#ifndef _C_STATE_
#define _C_STATE_
#include <SDL/SDL.h>
class CApp;
class CState {
public:
    virtual void Enter  (CApp * App)=0;
    virtual void Exit   ()=0;
    virtual void Sleep  ()=0;
    virtual void Wakeup ()=0;
    virtual void Update ()=0;
    virtual void Handle (SDL_Event * Event)=0;
    virtual void Render ()=0;
    virtual void OnKeyDown      (SDLKey sym, SDLMod mod, Uint16 unicode);
	virtual void OnKeyUp        (SDLKey sym, SDLMod mod, Uint16 unicode);
    virtual void OnMouseMove    (int X, int Y, int relX, int relY, bool Left,bool Right,bool Middle);
	virtual void OnMouseWheel   (bool Up, bool Down);
	virtual void OnLButtonDown  (int X, int Y);
	virtual void OnLButtonUp    (int X, int Y);
	virtual void OnRButtonDown  (int X, int Y);
	virtual void OnRButtonUp    (int X, int Y);
	virtual void OnMButtonDown  (int X, int Y);
	virtual void OnMButtonUp    (int X, int Y);
protected:
    CState() {}
};
#endif
