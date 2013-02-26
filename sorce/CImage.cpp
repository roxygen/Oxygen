#include "CImage.hpp"

void CImage::Load(std::string &ID, std::string &FileName, float X, float Y, float Z) {
    mID = ID;
    mX = X;
    mY = Y;
    mZ = Z;
    mAlpha = 1.0;
    mBlendMode = BLEND_ALPHA;
	GLenum texture_format;
	GLint  bpp;
	
    mImage = IMG_Load(FileName.c_str());
    if(mImage == NULL)
		std::cout << "ImgLoad " <<FileName.c_str() << " Fail.\n";
	else
		std::cout << "ImgLoad Done.\n";
    bpp = mImage->format->BytesPerPixel;
    std::cout << "Img BPP in ->" << bpp <<'\n';
    if( bpp == 4) {
        mImage = SDL_DisplayFormatAlpha(mImage);
        SDL_SetAlpha(mImage, 0, 0);
    } else {
        mImage = SDL_DisplayFormatAlpha(mImage);
        SDL_SetAlpha(mImage, 0, 255);
        //mBlendMode = BLEND_NONE;
    }
    bpp = mImage->format->BytesPerPixel;
    std::cout << "Img BPP out ->" << bpp <<'\n';
    std::cout << "Img Disply Format Done.\n";
    
    bool w_flag = false,
          h_flag = false;
          
    if (mImage->format->Rmask == 0x000000ff) {
        texture_format = GL_RGBA;
    } else {
        texture_format = GL_BGRA;
    }
    std::cout << "Texture Format Done.\n";
    mCX = 1.0;
    mCY = 1.0;
    if((mImage->w & (mImage->w -1)) != 0 ) {
        w_flag = true;
        mWidth = mImage->w;
    }
    if((mImage->h & (mImage->h -1)) != 0 ) {
        h_flag = true;
        mHeight = mImage->h;
    }

    if(w_flag || h_flag) {
        mImage = ResizeN2(mImage);
        std::cout << "Img was resized Done.\n";
    }
    if(w_flag) {
        mCX = mWidth/(float)mImage->w;
	}
    if(h_flag) {
        mCY = mHeight/(float)mImage->h;
	}
    
    glGenTextures( 1, &mTID );

    glBindTexture( GL_TEXTURE_2D, mTID );

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    glTexImage2D( GL_TEXTURE_2D, 0, 4, mImage->w, mImage->h, 0,
                      texture_format, GL_UNSIGNED_BYTE, mImage->pixels );
        
    glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    std::cout << "Texture Generate Done.\n";
    SDL_FreeSurface(mImage);
}

void CImage::Load(std::string &ID, std::string &FileName) {
    mImage = SDL_LoadBMP(FileName.c_str());
    if(mImage->format->BytesPerPixel == 4) {
        SDL_SetAlpha(mImage, SDL_SRCALPHA, 0);
        mImage = SDL_DisplayFormatAlpha(mImage);
    } else {
        mImage = SDL_DisplayFormat(mImage);
    }
}

void CImage::Draw() {
    glEnable(GL_BLEND);
    glEnable(GL_TEXTURE_2D);
    switch (mBlendMode) {
		case BLEND_NONE:        glBlendFunc(GL_ONE, GL_ZERO);                       break;
		case BLEND_ALPHA:       glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  break;
		case BLEND_ADD:         glBlendFunc(GL_ONE, GL_ONE);                        break;
		case BLEND_MULTIPLY:    glBlendFunc(GL_DST_COLOR, GL_ZERO);                 break;
		case BLEND_SRC2DST:     glBlendFunc(GL_SRC_COLOR, GL_ONE);                  break;
        case BLEND_ADDMUL:      glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ONE);        break;
        case BLEND_ADDALPHA:    glBlendFunc(GL_SRC_ALPHA, GL_ONE);                  break;
	}
    glBindTexture( GL_TEXTURE_2D, mTID );
    glPushMatrix();
    glBegin(GL_QUADS);
        glColor4f(1.0, 1.0, 1.0, mAlpha);
        // Top-left vertex (corner)
        glTexCoord2f(0.0, 0.0);
        glVertex3f(mX, mY, 0.0);

        // Bottom-left vertex (corner)
        glTexCoord2f(0.0, mCY);
        glVertex3f(mX, mY + mHeight,0.0);

        // Bottom-right vertex (corner)
        glTexCoord2f(mCX, mCY);
        glVertex3f(mX + mWidth, mY + mHeight,0.0);

        // Top-right vertex (corner)
        glTexCoord2f(mCX, 0.0);
        glVertex3f(mX + mWidth, mY, 0.0);
    glPopMatrix();
    glEnd();
    glDisable(GL_BLEND);
}

void CImage::Delete() {
    glDeleteTextures(1, &mTID);
    //SDL_FreeSurface(mImage);
}
void CImage::SetX(float X) {
    this->mX = X;
}

void CImage::SetY(float Y) {
    mY = Y;
}
void CImage::SetZ(float Z) {
    mZ = Z;
}
void CImage::SetAlpha(float Alpha) {
    mAlpha = Alpha;
}
float CImage::GetX() {
    return mX;
}
float CImage::GetY() {
    return mY;
}

float CImage::GetZ() {
    return mZ;
}
float CImage::GetAlpha() {
    return mAlpha;
}
void CImage::SetBlend(BLEND_MODE BlendMode) {
	mBlendMode = BlendMode;
}
std::string& CImage::GetID() {
    return this->mID;
}
GLuint CImage::GetTID() {
    return mTID;
}
SDL_Surface * CImage::ResizeN2(SDL_Surface * img) {
    int w, h;
    for(w = img->w; (w & (w - 1)) !=0; w++);
    for(h = img->h; (h & (h - 1)) !=0; h++);

    SDL_Surface * tmp = SDL_CreateRGBSurface(SDL_HWSURFACE|SDL_SRCALPHA, w, h,
                                             img->format->BitsPerPixel,
                                             img->format->Rmask, img->format->Gmask,
                                             img->format->Bmask, img->format->Amask);
    SDL_FillRect(tmp, 0, SDL_MapRGBA(img->format, 0, 0, 0, 0));
    SDL_BlitSurface(img, 0, tmp, 0);
    SDL_FreeSurface(img);

    return tmp;
}
