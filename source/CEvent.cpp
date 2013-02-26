#include "CEvent.hpp"
#include "CApp.hpp"
CEvent::CEvent(CApp * App) {
    mApp = App;
}
void CEvent::Handle(SDL_Event * Event) {
    switch(Event->type) {
        case SDL_ACTIVEEVENT: {
            switch(Event->active.state) {
                case SDL_APPMOUSEFOCUS: {
                    if ( Event->active.gain )
                        OnMouseFocus();
                    else
                        OnMouseBlur();
                    break;
                }
                case SDL_APPINPUTFOCUS: {
                    if ( Event->active.gain )
                        OnInputFocus();
                    else
            OnInputBlur();
                    break;
                }
                case SDL_APPACTIVE:    {
                    if ( Event->active.gain )
                        OnRestore();
                    else
                        OnMinimize();
                    break;
                }
            }
            break;
        }
 
        case SDL_KEYDOWN: {
            OnKeyDown(Event->key.keysym.sym,Event->key.keysym.mod,Event->key.keysym.unicode);
            break;
        }
 
        case SDL_KEYUP: {
            OnKeyUp(Event->key.keysym.sym,Event->key.keysym.mod,Event->key.keysym.unicode);
            break;
        }
 
        case SDL_MOUSEMOTION: {
            OnMouseMove(Event->motion.x,Event->motion.y,Event->motion.xrel,Event->motion.yrel,(Event->motion.state&SDL_BUTTON(SDL_BUTTON_LEFT))!=0,(Event->motion.state&SDL_BUTTON(SDL_BUTTON_RIGHT))!=0,(Event->motion.state&SDL_BUTTON(SDL_BUTTON_MIDDLE))!=0);
            break;
        }
 
        case SDL_MOUSEBUTTONDOWN: {
            switch(Event->button.button) {
                case SDL_BUTTON_LEFT: {
                    OnLButtonDown(Event->button.x,Event->button.y);
                    break;
                }
                case SDL_BUTTON_RIGHT: {
                    OnRButtonDown(Event->button.x,Event->button.y);
                    break;
                }
                case SDL_BUTTON_MIDDLE: {
                    OnMButtonDown(Event->button.x,Event->button.y);
                    break;
                }
            }
            break;
        }
 
        case SDL_MOUSEBUTTONUP:    {
            switch(Event->button.button) {
                case SDL_BUTTON_LEFT: {
                    OnLButtonUp(Event->button.x,Event->button.y);
                    break;
                }
                case SDL_BUTTON_RIGHT: {
                    OnRButtonUp(Event->button.x,Event->button.y);
                    break;
                }
                case SDL_BUTTON_MIDDLE: {
                    OnMButtonUp(Event->button.x,Event->button.y);
                    break;
                }
            }
            break;
        }
 
        case SDL_JOYAXISMOTION: {
            OnJoyAxis(Event->jaxis.which,Event->jaxis.axis,Event->jaxis.value);
            break;
        }
 
        case SDL_JOYBALLMOTION: {
            OnJoyBall(Event->jball.which,Event->jball.ball,Event->jball.xrel,Event->jball.yrel);
            break;
        }
 
        case SDL_JOYHATMOTION: {
            OnJoyHat(Event->jhat.which,Event->jhat.hat,Event->jhat.value);
            break;
        }
        case SDL_JOYBUTTONDOWN: {
            OnJoyButtonDown(Event->jbutton.which,Event->jbutton.button);
            break;
        }
 
        case SDL_JOYBUTTONUP: {
            OnJoyButtonUp(Event->jbutton.which,Event->jbutton.button);
            break;
        }
 
        case SDL_QUIT: {
            mApp->Exit();
            break;
        }
 
        case SDL_SYSWMEVENT: {
            //Ignore
            break;
        }
 
        case SDL_VIDEORESIZE: {
            OnResize(Event->resize.w,Event->resize.h);
            break;
        }
 
        case SDL_VIDEOEXPOSE: {
            OnExpose();
            break;
        }
 
        default: {
            OnUser(Event->user.type,Event->user.code,Event->user.data1,Event->user.data2);
            break;
        }
    }
}
 
void CEvent::OnInputFocus() {}
void CEvent::OnInputBlur() {}
void CEvent::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode) {}
void CEvent::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode) {
    switch(sym) {
    case SDLK_f: {
        mApp->Resize();
        break;
    }
    default: {
        mApp->mStateManager->OnKeyUp(sym, mod, unicode);
    }break;
    }
}
void CEvent::OnMouseFocus() {}
void CEvent::OnMouseBlur() {}
void CEvent::OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle) {
    mApp->mStateManager->OnMouseMove(mX, mY, relX, relY, Left, Right, Middle);
}
void CEvent::OnMouseWheel(bool Up, bool Down) {
    mApp->mStateManager->OnMouseWheel(Up, Down);
}
void CEvent::OnLButtonDown(int mX, int mY) {
     mApp->mStateManager->OnLButtonDown(mX,mY);
}
void CEvent::OnLButtonUp(int mX, int mY) {
    //mApp->mGUIManager->OnLButtonUp(mX,mY);
    mApp->mStateManager->OnLButtonUp(mX,mY);
}
void CEvent::OnRButtonDown(int mX, int mY) {
    //mApp->mGUIManager->OnRButtonDown(mX,mY);
    mApp->mStateManager->OnRButtonDown(mX,mY);
}
void CEvent::OnRButtonUp(int mX, int mY) {
    mApp->mStateManager->OnRButtonUp(mX, mY);
}
void CEvent::OnMButtonDown(int mX, int mY) {
    mApp->mStateManager->OnMButtonDown(mX, mY);
}
void CEvent::OnMButtonUp(int mX, int mY) {
    mApp->mStateManager->OnMButtonUp(mX, mY);
}
void CEvent::OnJoyAxis(Uint8 which,Uint8 axis,Sint16 value) {}
void CEvent::OnJoyButtonDown(Uint8 which,Uint8 button) {}
void CEvent::OnJoyButtonUp(Uint8 which,Uint8 button) {}
void CEvent::OnJoyHat(Uint8 which,Uint8 hat,Uint8 value) {}
void CEvent::OnJoyBall(Uint8 which,Uint8 ball,Sint16 xrel,Sint16 yrel) {}
void CEvent::OnMinimize() {}
void CEvent::OnRestore() {}
void CEvent::OnResize(int w,int h) {}
void CEvent::OnExpose() {}
void CEvent::OnUser(Uint8 type, int code, void* data1, void* data2) {}
