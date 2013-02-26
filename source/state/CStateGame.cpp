#include "../CApp.hpp"
#include "../IncludesCState.hpp"
#include "CStateGame.hpp"
CStateGame CStateGame::mStateGame;

CStateGame * CStateGame::Instance() {
    return &mStateGame;
}
CStateGame::CStateGame() {}
void CStateGame::Enter  (CApp * App) {
    mApp = App;
    std::cout
        << "State::GAME\n"
        << "    ESC     -   MENU\n"
        << "    RMOUSE  -   MENU\n"
        << "    F       -   FULLSCREEN\n"
        << "    S       -   SAVE\n"
        << "    L       -   LOAD\n"
        << "    C       -   CONFIG\n";
}
void CStateGame::Exit   () {
    mApp->mImageManager->DeleteAll();
}
void CStateGame::Sleep  () {
    std::cout << "State::Game->Sleep\n";
}
void CStateGame::Wakeup () {
    std::cout << "State::Game->Wakeup\n";
}
void CStateGame::Handle(SDL_Event * Event) {
    //CEvent::Handle(Event);
}
void CStateGame::Update () {
}
void CStateGame::Render () {
    mApp->mImageManager->DrawAll();
}
/*void CStateGame::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode) {
    switch(sym) {
    case SDLK_ESCAPE: {
        //mApp->mStateManager->Push(new CStateMenu(mApp));
    } break;
    case SDLK_f: {
        mApp->Resize();
    } break;
    case SDLK_s: {
        //mApp->mStateManager->Push(new CStateSave(mApp));
    } break;
    case SDLK_l: {
        //mApp->mStateManager->Push(new CStateLoad(mApp));
    } break;
    case SDLK_c: {
        //mApp->mStateManager->Push(new CStateConfig(mApp));
    } break;
    default: {
    } break;
    } //end switch;
}
void CStateGame::OnRButtonUp(int mX, int mY) {
    //mApp->mStateManager->Push(new CStateMenu(mApp));
}
void CStateGame::Escape() {
    mApp->Exit();
}*/
