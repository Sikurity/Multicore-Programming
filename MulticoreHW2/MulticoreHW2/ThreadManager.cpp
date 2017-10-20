//
//  ThreadManager.cpp
//  MulticoreHW2
//
//  Created by YeongsikLee on 2017. 10. 15..
//  Copyright © 2017년 boostcamp. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "ThreadManager.hpp"

namespace lys {
    
    int ThreadManager::gloablRecoredMutex;
    int ThreadManager::goalExecutionOrder;
    int ThreadManager::currentExecutionOrder;
    
    /// 스레드 주소공간 모두 반환
    ThreadManager::ThreadManager(int N, int E) {
        
        this->threads = new Thread[N]();
        
        for(int i = 0 ; i < N ; i++)
            this->threads[i].threadNum = i;
        
        goalExecutionOrder = E;
    }
    
    /// 스레드 주소공간 모두 반환
    ThreadManager::~ThreadManager() {
        delete[] this->threads;
    }
}
