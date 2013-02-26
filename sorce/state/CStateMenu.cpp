#include "../CApp.hpp"
#include "CStateMenu.hpp"
#include "../CUtil.hpp"
CStateGame::CStateMenu(CApp * App) {
    mApp = App;
}
void CStateMenu::Enter  () {
    std::cout
        << "State::GAME\n"
        << "    ESC     -   RETURN\n"
        << "    RMOUSE  -   RETURN\n"
        << "    F       -   FULLSCREEN\n"
        << "    F1      -   SAVE\n"
        << "    F2      -   LOAD\n"
        << "    F3      -   CONFIG\n"
        << "    F4      -   TITLE\n";
}
void CStateMenu::Exit   () {
    mApp->mImageManager->DeleteAll();
}
void CStateMenu::Sleep  () {
    std::cout << "State::Menu->Sleep\n";
}
void CStateMenu::Wakeup () {
    std::cout << "State::Menu->Wakeup\n";
}
void CStateMenu::Handle(SDL_Event * Event) {
    CEvent::Handle(Event);
}
void CStateMenu::Update () {
}
void CStateMenu::Render () {
    mApp->mImageManager->DrawAll();
}
void CStateMenu::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode) {
    switch(sym) {
    case SDLK_ESCAPE: {
        mApp->mStateManager->Pop();
    } break;
    case SDLK_f: {
        mApp->Resize();
    } break;
    case SDLK_F1: {
        //mApp->mStateManager->Push(new CStateSave(mApp));
    } break;
    case SDLK_F2: {
        //mApp->mStateManager->Push(new CStateLoad(mApp));
    } break;
    case SDLK_F3: {
        //mApp->mStateManager->Push(new CStateConfig(mApp));
    } break;
    case SDLK_F4: {
        mApp->mStateManager->Change(new CStateTitle(mApp));
    } break;
    default: {
    } break;
    } //end switch;
}
void CStateMenu::OnRButtonUp(int mX, int mY) {
    mApp->mStateManager->Pop();
}
void CStateMenu::Escape() {
    mApp->Exit();
}
