//
//  ThreadManager.hpp
//  MulticoreHW2
//
//  Created by YeongsikLee on 2017. 10. 15..
//  Copyright © 2017년 Hanyang Osori. All rights reserved.
//

#ifndef ThreadManager_hpp
#define ThreadManager_hpp

#include <pthread.h>

namespace lys {
    
    typedef struct Thread {
        
    private:
        
        /// Mark: Private Member Variable
        pthread_t thread;
        pthread_cond_t cond;
        
        /// Mark: Private Member Method
        static void *transactionMethodWrapper(void *);
        void transactionMethod();
    
    public:
        
        /// Mark: Public Member Variable
        int threadNum;
        
        /// Mark: Public Member Method
        
        Thread();
        
    } Thread;
    
    
    typedef struct ThreadManager {
        
    public:
        
        /// Mark: Public Member Variable
        
        static int goalExecutionOrder;
        static int currentExecutionOrder;
        static pthread_mutex_t gloablRecoredMutex;
        
        static int numberOfThreads;
        static Thread *threads;
        
        /// Mark: Public Member Method
        ThreadManager(int N, int E);
        ~ThreadManager();
        
    } ThreadManager;
}

#endif /* ThreadManager_hpp */
