#ifndef _C_APP_
#define _C_APP_
//--------------
#include "CUtil.hpp"
#include <iostream>
#include "SDL/SDL.h"
#include "GL/gl.h"
#include "GL/glu.h"
#include "ini/INIReader.h"
#include "CEvent.hpp"
#include "CImage.hpp"
#include "CImageManager.hpp"
#include "IncludesCProcess.hpp"
#include "IncludesCState.hpp"
//--------------
class CApp{
private:
    bool mOK;
    bool mDone;
    SDL_Surface * mScreen;
    const SDL_VideoInfo * mVideoInfo;
    
    int mWindowWidth;
    int mWindowHeight;
    int mVirtualWidth;
    int mVirtualHeight;
    int mBpp;
    std::string mWindowTitle;
    std::string mResFolder;
    std::string mGFXFolder;
    std::string mSFXFolder;
    
    Uint32 mFlags;
    
    bool mIsFull;
    float mAspectRatio;
    
    SDL_Event mEvent;
    // FPS
    Uint32 FRAMES_PER_SECOND;//	= 60;
    Uint32 SKIP_TICKS;//			= 1000 / FRAMES_PER_SECOND;
    Uint32 MAX_FRAMESKIP;//		= 5;

    Uint32 next_game_tick;//		= 0;
    Uint32 loop_tick;//			= 0;
    
public:
    CApp();
    
    bool Init();
    int Execute();
    void Resize();
    void Resource();
    void Event();
    void Loop();
    void Render();
    void Cleanup();
    void Exit();
    Uint32 GetFPS();
    int GetWindowWidth();
    int GetWindowHeight();
    
    //void ShowInformation()
    CImageManager *mImageManager;
    CProcessManager *mProcessManager;
    CEvent * mEventManager;
    CStateManager * mStateManager;
    //--------
    std::string GetGFXPath();
    std::string GetSFXPath();
};
#endif
