#include "../CApp.hpp"
#include "CProcessAlpha.hpp"
#include <math.h>

CAlpha::CAlpha(CApp *App, std::string ID, float ToAlpha, Uint32 Time) {
    std::cout << "Alpha Process Begin\n";
    mApp = App;
    mOID = ID;
    mToAlpha = ToAlpha;
    mFromAlpha = mApp->mImageManager->Obj(mOID)->GetAlpha();
    mTime = Time;
    if(mTime == 0) {
        std::cout << " Time == 0: Alpha set to " << mToAlpha << '\n';
        mApp->mImageManager->Obj(mOID)->SetAlpha(mToAlpha);
        return;
    }
    mSpeed = fabs(mFromAlpha - mToAlpha)/((float)Time * mApp->GetFPS()/1000.0);
    std::cout << " mSpeed = " << mSpeed << '\n';
    int sub = 1;
    if(mToAlpha < mFromAlpha)
        sub = -1;
    for(float i = 0.0; i < fabs(mToAlpha - mFromAlpha); i+=mSpeed) {
        mAlphaList.push_back( mFromAlpha + i*sub );
    }
    
    mFirst = true;
}

void CAlpha::Enter() {
}
int CAlpha::Update() {
    if(mFirst) {
        mFirst = false;
    }
    if(!mAlphaList.empty()) {
        mApp->mImageManager->Obj(mOID)->SetAlpha(mAlphaList.front());
        //std::cout << "Now Alpha: " << mAlphaList.front() << '\n';
        mAlphaList.pop_front();
        
        return 0;
    } else {
        std::cout<< "Leave Alpha Update\n";
        return 1;
    }
}

void CAlpha::Exit() {
    mAlphaList.clear();
    
}
void CAlpha::End() {
    mApp->mImageManager->Obj(mOID)->SetAlpha(mAlphaList.back()); mAlphaList.pop_back();
    mAlphaList.clear();
    mTimeEnd = SDL_GetTicks();
}
