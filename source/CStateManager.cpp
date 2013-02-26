#include "CStateManager.hpp"
#include "CApp.hpp"
#include "CState.hpp"
void CStateManager::Change(CState * State, CApp * App) {
    if(!mStateStack.empty()) {
        mStateStack.top()->Exit();
        mStateStack.pop();
    }
    mStateStack.push(State);
    mStateStack.top()->Enter(App);
}
void CStateManager::Push(CState * State, CApp * App) {
    if(!mStateStack.empty()) {
        mStateStack.top()->Sleep();
    }
    mStateStack.push(State);
    mStateStack.top()->Enter(App);
}
void CStateManager::Pop () {
    if(!mStateStack.empty()) {
        mStateStack.top()->Exit();
        mStateStack.pop();
    }
    if(!mStateStack.empty()) {
        mStateStack.top()->Wakeup();
    }
}
void CStateManager::PopAll() {
    while(!mStateStack.empty()) {
        mStateStack.top()->Exit();
        mStateStack.pop();
    }
    std::cout << "State Stack is empty\n";
}
void CStateManager::Handle(SDL_Event * Event) {
    if(!mStateStack.empty()) {
        mStateStack.top()->Handle(Event);
    }
}

void CStateManager::Update() {
    if(!mStateStack.empty()) {
        mStateStack.top()->Update();
    }
}
void CStateManager::Render() {
    if(!mStateStack.empty()) {
        mStateStack.top()->Render();
    }
}

CState * CStateManager::Top() {
    return mStateStack.top();
}
void CStateManager::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode) {
    mStateStack.top()->OnKeyDown(sym, mod, unicode);
}
void CStateManager::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode) {
    mStateStack.top()->OnKeyUp(sym,mod,unicode);
}
void CStateManager::OnMouseMove(int X, int Y, int relX, int relY, bool Left,bool Right,bool Middle) {
    mStateStack.top()->OnMouseMove(X, Y, relX, relY, Left, Right, Middle);
}
void CStateManager::OnMouseWheel(bool Up, bool Down) {
    mStateStack.top()->OnMouseWheel(Up, Down);
}
void CStateManager::OnLButtonDown(int X, int Y) {
    mStateStack.top()->OnLButtonDown(X, Y);
}
void CStateManager::OnLButtonUp(int X, int Y) {
    mStateStack.top()->OnLButtonUp(X, Y);
}
void CStateManager::OnRButtonDown(int X, int Y) {
    mStateStack.top()->OnRButtonDown(X, Y);
}
void CStateManager::OnRButtonUp(int X, int Y) {
    mStateStack.top()->OnRButtonUp(X, Y);
}
void CStateManager::OnMButtonDown(int X, int Y) {
    mStateStack.top()->OnMButtonDown(X, Y);
}
void CStateManager::OnMButtonUp(int X, int Y) {
    mStateStack.top()->OnMButtonUp(X, Y);
}
