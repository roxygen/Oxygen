#ifndef _C_IMG_MAN_
#define _C_IMG_MAN_
#include "CImage.hpp"
#include <list>

class CImageManager {
public:
    CImageManager() {}
    ~CImageManager() {}
    CImage *Obj(std::string ID);
    void Load(std::string ID, std::string FileName, float X, float Y, float Z);
    void Delete(std::string ID);
    void DeleteAll();
    void Draw(std::string ID);
    void DrawAll();
private:
    std::list<CImage*> mManager;
    std::list<CImage*>::iterator it;
};
#endif
