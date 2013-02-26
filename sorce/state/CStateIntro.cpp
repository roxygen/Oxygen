#include "../CApp.hpp"
#include "../IncludesCState.hpp"
CStateIntro CStateIntro::mStateIntro;

CStateIntro * CStateIntro::Instance() {
    return &mStateIntro;
}
CStateIntro::CStateIntro() {}

void CStateIntro::Enter  (CApp * App) {
    mApp = App;
    INIReader list(Util::SPath("sys/list.ini"));
    int count = list.GetInteger("setup", "count", 0);
    for(int i = 1; i < count+1; i++) {
        //Маска изображений
        std::string tImg = Util::SFormat("img%04d", i);
        mApp->mImageManager->Load( list.Get(tImg, "name", "dummy")
                           , Util::SPath( mApp->GetGFXPath() + list.Get(tImg, "file", "dummy.png"))
                           , list.GetInteger(tImg, "x", 0)
                           , list.GetInteger(tImg, "y", 0)
                           , list.GetInteger(tImg, "z", 0)
                           );
    }
    std::string action = list.Get("setup", "action", "move");
    mApp->mProcessManager->Create( new CMove(mApp, list.Get(action,"target","guy")
                                           , list.GetInteger(action, "x", 0)
                                           , list.GetInteger(action, "y", 0)
                                           , list.GetInteger(action, "time", 0)));
    mApp->mProcessManager->Create( new CMove (mApp, "girl", 0, 80, 1000) );
    mApp->mProcessManager->Create( new CAlpha(mApp, "girl", 0.5, 2000) );
    mApp->mProcessManager->Create( new CAlpha(mApp, "bg", 0.0, 0) );
    mApp->mProcessManager->Create( new CAlpha(mApp, "bg", 1.0, 2500) );
}
void CStateIntro::Exit   () {
    mApp->mProcessManager->EndAll();
    mApp->mProcessManager->DeleteAll();
    mApp->mImageManager->Delete("g*");
}
void CStateIntro::Sleep  () {
    std::cout << "State::Intro->Sleep\n";
}
void CStateIntro::Wakeup () {
    std::cout << "State::Intro->Wakeup\n";
}
void CStateIntro::Handle(SDL_Event * Event) {
}
void CStateIntro::Update () {
}
void CStateIntro::Render () {
    mApp->mImageManager->DrawAll();
}
void CStateIntro::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode) {
    std::cout << "Intro Key Up!\n";
    switch(sym) {
    default: {
        mApp->mStateManager->Change(CStateTitle::Instance(), mApp);
    } break;
    } //end switch;
}

