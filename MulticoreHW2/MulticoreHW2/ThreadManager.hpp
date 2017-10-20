//
//  ThreadManager.hpp
//  MulticoreHW2
//
//  Created by YeongsikLee on 2017. 10. 15..
//  Copyright © 2017년 boostcamp. All rights reserved.
//

#ifndef ThreadManager_hpp
#define ThreadManager_hpp

#include <pthread.h>

namespace lys {
    
    typedef struct Thread{
        
    private:
        
        /// Mark: Private Member Variable
        pthread_mutex_t readLock;
        pthread_mutex_t writeLock;
        pthread_t thread;
        
        
        /// Mark: Private Member Method
        static void *transactionMethod(void *);
    
    public:
        
        /// Mark: Public Member Variable
        int threadNum;
        
    } Thread;
    
        
    typedef struct ThreadManager {
    
    private:
    
        /// Mark: Private Static Variable
        static int gloablRecoredMutex;
        static int goalExecutionOrder;
        static int currentExecutionOrder;
        
        
        /// Mark: Private Static Method
        static void *transactionFunc(void *obj);
        
    public:
        
        /// Mark: Public Member Variable
        int numberOfThreads;
        Thread *threads;
        
        /// Mark: Public Member Method
        ThreadManager(int N, int E);
        ~ThreadManager();
        
    } ThreadManager;
}

#endif /* ThreadManager_hpp */
