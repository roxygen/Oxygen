#include "CApp.hpp"
CApp::CApp() {
    if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_TIMER)>0) {
        std::cout << "Init SDL failed.\n";
        mOK = false;
    } else {
        mOK = true;
    }
    
    mDone = false;
    mFlags = SDL_HWSURFACE|SDL_OPENGL;
    INIReader gConfig( Util::SPath("sys/main.ini") );
    
    mWindowWidth        = gConfig.GetInteger("Video", "width", 800);
    mWindowHeight       = gConfig.GetInteger("Video", "height", 600);
    mBpp                = gConfig.GetInteger("Video", "bpp", 32);
    mIsFull             = gConfig.GetBoolean("Video", "fullscreen", false);
    mWindowTitle        = gConfig.Get("Video","Title", "CApp");
    FRAMES_PER_SECOND   = gConfig.GetInteger("Video", "fps", 30);
    MAX_FRAMESKIP       = gConfig.GetInteger("Video", "skip", 0);
    mResFolder          = gConfig.Get("Resource", "res", "res");
    mGFXFolder          = gConfig.Get("Resource", "bmp", "gfx");
    mSFXFolder          = gConfig.Get("Resource", "se", "sfx");
    SKIP_TICKS          = 1000 / FRAMES_PER_SECOND;
    next_game_tick      = 0;
    loop_tick           = 0;
    
    mImageManager   = new CImageManager();
    mProcessManager = new CProcessManager();
    mStateManager   = new CStateManager();
    mEventManager   = new CEvent(this);
    
    
    mAspectRatio = (float)mWindowWidth/(float)mWindowHeight;
    
    mVideoInfo = SDL_GetVideoInfo();
    mVirtualWidth = mVideoInfo->current_w;
    mVirtualHeight = mVideoInfo->current_h;
    std::cout << "Window:\n"
              << "  Width:  " << mWindowWidth       << '\n'
              << "  Height: " << mWindowHeight      << '\n'
              << "  BPP:    " << mBpp               << '\n'
              << "  Title:  " << mWindowTitle       << '\n'
              << "  FPS:    " << FRAMES_PER_SECOND  << '\n'
              << "  SkipFPS:" << MAX_FRAMESKIP      << '\n'
              << "  Aspect: " << mAspectRatio       << '\n'
              << "  VirtW:  " << mVirtualWidth      << '\n'
              << "  VirtH:  " << mVirtualHeight     << '\n'
              << "\n----------------\n"
              << gConfig.Get("Test", "script", "print(dummy)")
              << "\n----------------\n";
}
bool CApp::Init() {
    
    if(!mOK) return false;

    mScreen = SDL_SetVideoMode( mWindowWidth, mWindowHeight, mBpp, mFlags );
    
    SDL_WM_SetCaption( mWindowTitle.c_str() , "Test");
    
    SDL_GL_SetAttribute( SDL_GL_RED_SIZE    , 8 );
    SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE  , 8 );
    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE   , 8 );
    SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE  , 8 );
    SDL_GL_SetAttribute( SDL_GL_BUFFER_SIZE , 32);
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
    SDL_GL_SetAttribute( SDL_GL_SWAP_CONTROL, 1 );
    
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0 );
    glViewport  ( 0, 0, mWindowWidth, mWindowHeight );
    
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    
    glOrtho(0.0f, (float)mWindowWidth, (float)mWindowHeight, 0.0f, -1.0f, 1.0f);
    
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    glBlendEquation(GL_FUNC_ADD);
    return true;
}

int CApp::Execute() {
    if(Init() == false) {
        std::cout << "Init unsuccesed\n";
        return -1;
    }
    std::cout << "Init succesed\n";
    mStateManager->Change(CStateIntro::Instance(), this);
    
    while(!mDone) {
        loop_tick = 0;
        while( SDL_GetTicks() > next_game_tick && loop_tick < MAX_FRAMESKIP)
        {
            while( SDL_PollEvent(&mEvent) ) {
                Event();
            }
            Loop();
            next_game_tick += SKIP_TICKS;
            loop_tick++;
        }
        Render();
    }
    
    Cleanup();
    return 0;
}

void CApp::Event() {
    mEventManager->Handle(&mEvent);
}
void CApp::Resource() {
}
void CApp::Loop() {
    mProcessManager->Update();
    mStateManager->Update();
}

void CApp::Render() {

    // Clear Screen
    
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Draw
    mStateManager->Render();
    SDL_GL_SwapBuffers();
}
void CApp::Resize() {
    
    mIsFull = !mIsFull;
    
    float nowWidth, nowHeight;
    if(mIsFull) {
        mFlags=SDL_OPENGL|SDL_FULLSCREEN;
        nowWidth = mVirtualWidth;
        nowHeight= mVirtualHeight;
    } else {
        mFlags=SDL_OPENGL;
        nowWidth = mWindowWidth;
        nowHeight= mWindowHeight;
    }
    mScreen = SDL_SetVideoMode( nowWidth, nowHeight, mBpp, mFlags );
    int viewWidth = nowWidth;
    int viewHeight= nowWidth/mAspectRatio;
    
    if(viewHeight>nowHeight) {
        viewHeight = nowHeight;
        viewWidth  = nowHeight * mAspectRatio;
    }
    
    int vportX = (nowWidth - viewWidth)/2;
    int vportY = (nowHeight - viewHeight)/2;
    
    glViewport( vportX,vportY,viewWidth, viewHeight );
    
    glOrtho(0.0f, (float)nowWidth, (float)nowHeight, 0.0f, -1.0f, 1.0f);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    std::cout << "Screen mode changed:" <<'\n'
              << "  vPort x:     "      << vportX     <<'\n'
              << "  vPort y:     "      << vportY     <<'\n'
              << "  vW     :     "      << viewWidth  <<'\n'
              << "  vH     :     "      << viewHeight <<'\n'
              << "  newW   :     "      << nowWidth   <<'\n'
              << "  newH   :     "      << nowHeight  <<'\n';
    // Тут будет перезагрузка тексутр для винды. 
    // Она теряет OpenGL контекст при ресайзе базовой поверхности.
}
void CApp::Cleanup() {
    mProcessManager->DeleteAll();
    mStateManager->PopAll();
    SDL_Quit();
}
void CApp::Exit() {
    mDone = true;
}
Uint32 CApp::GetFPS() {
    return FRAMES_PER_SECOND;
}
int CApp::GetWindowWidth() {
    return mWindowWidth;
}
int CApp::GetWindowHeight() {
    return mWindowHeight;
}
std::string CApp::GetGFXPath(){
    return (mResFolder + "/" + mGFXFolder + "/");
}
std::string CApp::GetSFXPath(){
    return (mResFolder + "/" + mSFXFolder + "/");
}
