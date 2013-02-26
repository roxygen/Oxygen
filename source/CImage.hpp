#ifndef _C_IMG_
#define _C_IMG_
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <string>
#include "CUtil.hpp"
enum BLEND_MODE {
	BLEND_NONE = -1,
	BLEND_ALPHA = 0,
	BLEND_ADD,
	BLEND_MULTIPLY,
	BLEND_SRC2DST,
	BLEND_ADDMUL,
	BLEND_ADDALPHA
};
	
class CImage {
private:
    GLuint mTID;
    std::string mID;
    SDL_Surface * mImage;
    float mX;
    float mY;
    float mZ;
    float mCX;
    float mCY;
    float mWidth;
    float mHeight;
    float mAlpha;
    BLEND_MODE mBlendMode;
    SDL_Surface * ResizeN2(SDL_Surface * img);
public:
    CImage() {
        mImage = NULL;
        mX = 0;
        mY = 0;
        mZ = 0;
    }
    ~CImage() {}
    void Load(std::string &ID, std::string &FileName, float X, float Y, float Z);
    void Load(std::string &ID, std::string &FileName);
    void Draw();
    void Delete();
    void SetX(float X);
    void SetY(float Y);
    void SetZ(float Z);
    void SetAlpha(float Alpha);
    void SetBlend(BLEND_MODE BlendMode);
    float GetX();
    float GetY();
    float GetZ();
    float GetAlpha();
    GLuint GetTID();
    std::string & GetID();
};
#endif
