#include "../CApp.hpp"
#include "../IncludesCState.hpp"

CStateTitle CStateTitle::mStateTitle;

CStateTitle * CStateTitle::Instance() {
    return &mStateTitle;
}
CStateTitle::CStateTitle() {
    
}
void CStateTitle::Enter  (CApp * App) {
    mApp = App;
    mApp->mImageManager->Load("back", Util::SPath(mApp->GetGFXPath() + "back.png"), 0,0,0);
    mApp->mProcessManager->Create(new CAlpha(mApp, "back", 0, 0));
    mApp->mProcessManager->Create(new CAlpha(mApp, "back", 1, 1000));
}
void CStateTitle::Exit   () {
    mApp->mImageManager->DeleteAll();
}
void CStateTitle::Sleep  () {
    std::cout << "State::Title->Sleep\n";
}
void CStateTitle::Wakeup () {
    std::cout << "State::Title->Wakeup\n";
}
void CStateTitle::Handle(SDL_Event * Event) {
    //CEvent::Handle(Event);
}
void CStateTitle::Update () {
}
void CStateTitle::Render () {
    mApp->mImageManager->DrawAll();
}
/*void CStateTitle::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode) {
    switch(sym) {
    case SDLK_ESCAPE: {
        //
    } break;
    case SDLK_f: {
        mApp->Resize();
    } break;
    case SDLK_F1: {
        mApp->mStateManager->Change(CStateGame::Instance(), mApp);
    } break;
    case SDLK_F2: {
        //mApp->mStateManager->Push(new CStateLoad(mApp));
    } break;
    case SDLK_F3: {
        //mApp->mStateManager->Push(new CStateConfig(mApp));
    } break;
    case SDLK_F4: {
        //mApp->mStateManager->Change(new CStateExtra(mApp));
    } break;
    case SDLK_F6: {
        mApp->Exit();
    } break;
    default: {
    } break;
    } //end switch;
}
void CStateTitle::Escape() {
    mApp->Exit();
}*/
