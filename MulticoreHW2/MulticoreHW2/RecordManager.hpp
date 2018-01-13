//
//  RecordManager.h
//  MulticoreHW2
//
//  Created by YeongsikLee on 2017. 10. 15..
//  Copyright © 2017년 Hanyang Osori. All rights reserved.
//
#include <pthread.h>
#include <list>

#ifndef RecordManager_hpp
#define RecordManager_hpp

#ifndef LL_TYPE_DEFINED

typedef long long LL;

#define LL_TYPE_DEFINED

#endif

using namespace std;

namespace lys {
    
    enum RequestType {
        READ = 1,
        WRITE = 2
    };
    
    typedef struct ResourceRequest {
        
        RequestType rw;
        int threadNum;
        
    } ResourceRequest;
    
    typedef struct Record {
        
        LL value;
        
        list<ResourceRequest> requestThreadNum;
        
        Record();
        
        void wakeUpWaitingThreads();
        
    } Record;

    typedef struct RecordManager {

    public:
        static int numberOfRecords;
        static Record *records;
        
        bool isFirstRequestTypeRead();
        
        RecordManager(int N);
        ~RecordManager();
        
    } RecordManager;
    
}

#endif /* RecordManager_hpp */
