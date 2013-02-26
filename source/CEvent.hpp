#ifndef _C_EVENT_
#define _C_EVENT_
#include <SDL/SDL.h>
class CApp;
class CEvent {
public:
    CEvent(CApp * App);
    void Handle(SDL_Event* Event);
	void OnInputFocus();
	void OnInputBlur();
	void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
	void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);
	void OnMouseFocus();
	void OnMouseBlur();
	void OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle);
	void OnMouseWheel(bool Up, bool Down);
	void OnLButtonDown(int mX, int mY);
	void OnLButtonUp(int mX, int mY);
	void OnRButtonDown(int mX, int mY);
	void OnRButtonUp(int mX, int mY);
	void OnMButtonDown(int mX, int mY);
	void OnMButtonUp(int mX, int mY);
	void OnJoyAxis(Uint8 which, Uint8 axis, Sint16 value);
	void OnJoyButtonDown(Uint8 which, Uint8 button);
	void OnJoyButtonUp(Uint8 which, Uint8 button);
    void OnJoyHat(Uint8 which, Uint8 hat, Uint8 value);
    void OnJoyBall(Uint8 which, Uint8 ball, Sint16 xrel, Sint16 yrel);
    void OnMinimize();
    void OnRestore();
    void OnResize(int w,int h);
    void OnExpose();
    void OnUser(Uint8 type, int code, void* data1, void* data2);
protected:
    //virtual ~CEvent();
private:
    CApp * mApp;
};
#endif
