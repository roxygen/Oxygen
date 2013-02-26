#include "../CApp.hpp"
#include "CProcessMove.hpp"
#include <math.h>
CMove::CMove(CApp *App, std::string OID, float ToX, float ToY, Uint32 Time) {
    mApp = App;
    mOID = OID;
    mToX = ToX;
    mToY = ToY;
    mFromX = mApp->mImageManager->Obj(mOID)->GetX();
    mFromY = mApp->mImageManager->Obj(mOID)->GetY();
    mTime = Time;
    if(mTime == 0) {
        mApp->mImageManager->Obj(mOID)->SetX(mToX);
        mApp->mImageManager->Obj(mOID)->SetY(mToY);
        return;
    }
    // Шаг в процентах.
    mSpeed = fabs(mFromX - mToX)/((float)Time * mApp->GetFPS()/1000.0);
    std::cout << " mSpeed = " << mSpeed << '\n';
    if(mToX == mFromX) {
        mA = 1.0;
    } else {
        mA = (mToY - mFromY) / (mToX - mFromX);
    }
     std::cout << " mA = " << mA << '\n';
    float newX, newY;
    for(float i = 0.0; i < fabs(mToX - mFromX); i+=mSpeed) {
        if( mToX>=mFromX && !(mToY < mFromY && mToX == mFromX) ) {
            newX = mFromX + i;
        } else {
            newX = mFromX - i;
        }
        newY = mA*(newX - mFromX) + mFromY;
        mPointList.push_back(newX);
        //std::cout   << " X = " << newX;
        mPointList.push_back(newY);
        
        //std::cout   << " Y = " << newY << '\n';
    }
    
    mFirst = true;
}
void CMove::Enter () {
}
int CMove::Update() {
    if(mFirst) {
        mFirst = false;
    }
    if(!mPointList.empty()) {
        mApp->mImageManager->Obj(mOID)->SetX(mPointList.front()); mPointList.pop_front();
        mApp->mImageManager->Obj(mOID)->SetY(mPointList.front()); mPointList.pop_front();
        return 0;
    } else {
        std::cout<< "Leave Move Update\n";
        return 1;
    }
}
void CMove::Exit() {
    mPointList.clear();
    
}
void CMove::End() {
    if(!mPointList.empty()) {
        mApp->mImageManager->Obj(mOID)->SetY(mPointList.back()); mPointList.pop_back();
        mApp->mImageManager->Obj(mOID)->SetX(mPointList.back()); mPointList.pop_back();
    }
    mPointList.clear();
}
int CMove::GetID() {
    return mID;
}
void CMove::SetID(int ID) {
    mID = ID;
}
