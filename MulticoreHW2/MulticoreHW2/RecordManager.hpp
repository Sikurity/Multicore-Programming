//
//  RecordManager.h
//  MulticoreHW2
//
//  Created by YeongsikLee on 2017. 10. 15..
//  Copyright © 2017년 boostcamp. All rights reserved.
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
    
    typedef struct Record {
        
        LL value;
        
        list<int> requestThreadNum;
        
        Record();
        
    } Record;

    typedef struct RecordManager {

    public:
        static int numberOfRecords;
        static Record *records;
        
        RecordManager(int N);
        ~RecordManager();
        
    } RecordManager;
    
}

#endif /* RecordManager_hpp */
