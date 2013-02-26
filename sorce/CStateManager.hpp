#ifndef _C_STATE_MANAGER_
#define _C_STATE_MANAGER_
#include <SDL/SDL.h>
#include <stack>
#include <string>
#include <iostream>
class CApp;
class CState;
class CStateManager {
private:
    std::stack<CState*> mStateStack;
public:
    CStateManager() {}
    void Change(CState * State, CApp * App);
    void Push(CState * State, CApp * App);
    void Pop ();
    void PopAll();
    void Handle(SDL_Event * Event);
    void Update();
    void Render();
    
    CState * Top();
    
    //----------------- EVENT SYSTEM --------
    void OnKeyDown      (SDLKey sym, SDLMod mod, Uint16 unicode);
	void OnKeyUp        (SDLKey sym, SDLMod mod, Uint16 unicode);
    void OnMouseMove    (int X, int Y, int relX, int relY, bool Left,bool Right,bool Middle);
	void OnMouseWheel   (bool Up, bool Down);
	void OnLButtonDown  (int X, int Y);
	void OnLButtonUp    (int X, int Y);
	void OnRButtonDown  (int X, int Y);
	void OnRButtonUp    (int X, int Y);
	void OnMButtonDown  (int X, int Y);
	void OnMButtonUp    (int X, int Y);
};
#endif
