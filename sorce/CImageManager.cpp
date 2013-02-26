#include "CImageManager.hpp"
#include "CUtil.hpp"
bool CompareCImage(CImage *A, CImage *B) {
    return A->GetZ() < B->GetZ();
}
CImage *CImageManager::Obj(std::string ID) {
    for ( it = mManager.begin(); it != mManager.end(); ++it ) {
        if( ID == (*it)->GetID() ) {
            return *it;
        }
    }
    return NULL;
}
void CImageManager::Load(std::string ID, std::string FileName, float X, float Y, float Z) {
    mManager.push_back(new CImage());
    mManager.back()->Load(ID, FileName, X, Y, Z);
    mManager.sort(CompareCImage);
}

void CImageManager::Delete(std::string ID) {
    for ( it = mManager.begin(); it != mManager.end(); ++it ) {
        if( Util::StrMask( (*it)->GetID(), ID) ) {
            (*it)->Delete();
            mManager.erase(it); it--;
        }
    }
}

void CImageManager::DeleteAll() {
    for ( it = mManager.begin(); it != mManager.end(); ++it ) {
        (*it)->Delete();
    }
    mManager.clear();
}

void CImageManager::Draw(std::string ID) {
    for ( it = mManager.begin(); it != mManager.end(); ++it ) {
        if( ID ==(*it)->GetID() ) {
            (*it)->Draw();
        }
    }
}
void CImageManager::DrawAll() {
    for ( it = mManager.begin(); it != mManager.end(); ++it ) {
        (*it)->Draw();
    }
}

