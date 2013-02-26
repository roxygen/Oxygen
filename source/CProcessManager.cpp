#include "CProcessManager.hpp"
#include "CProcess.hpp"
void CProcessManager::Create (CProcess* Process) {
    std::cout<< "Create Process ...\n" ;
    mProcessList.push_back(Process);
    std::cout<< "Cancel Create Process.\n";
}
CProcess * CProcessManager::Obj() {
    return mProcessList.back();
}
void CProcessManager::Delete () {
    /*for(mIt = mProcessList.begin(); mIt !=mProcessList.end(); mIt++) {
        if(mIt->GetID() == ID) {
            (*mIt)->Exit();
            mProcessList.erase(mIt);
            mIt--;
        }
    }*/
}
void CProcessManager::DeleteAll() {
    while(!mProcessList.empty()) {
        mProcessList.back()->Exit();
        mProcessList.pop_back();
    }
}
void CProcessManager::Sleep  () {
    for(mIt = mProcessList.begin(); mIt != mProcessList.end(); mIt ++) {
        (*mIt)->Sleep();
    }
}
void CProcessManager::Wakeup () {
    for(mIt = mProcessList.begin(); mIt != mProcessList.end(); mIt ++) {
        (*mIt)->Wakeup();
    }
}
void CProcessManager::Update () {
    //std::cout<< "Begin Prcess Manager Update\n";
    int result;
    for(mIt = mProcessList.begin(); mIt != mProcessList.end(); mIt ++) {
        result = (*mIt)->Update();
        if(result) {
            (*mIt)->Exit();
            mProcessList.erase(mIt);
            return;
        }
    }
}
void CProcessManager::End    () {
    /*for(mIt = mProcessList.begin(); mIt !=mProcessList.end(); mIt++) {
        if((*mIt)->GetID() == ID) {
            (*mIt)->End();
            (*mIt)->Exit();
            mProcessList.erase(mIt);
            mIt--;
        }
    }*/
}
void CProcessManager::EndAll () {
    for(mIt = mProcessList.begin(); mIt != mProcessList.end(); mIt ++) {
        (*mIt)->End();
    }
}
