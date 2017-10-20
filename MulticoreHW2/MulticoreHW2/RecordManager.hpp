//
//  RecordManager.h
//  MulticoreHW2
//
//  Created by YeongsikLee on 2017. 10. 15..
//  Copyright © 2017년 boostcamp. All rights reserved.
//

#ifndef RecordManager_hpp
#define RecordManager_hpp

typedef long long LL;

namespace lys {
    
    typedef struct RandomNumber {
        
        int i;
        int j;
        int k;
        
    } RandomNumber;

    typedef struct RecordManager {

    public:
        int numberOfRecords;
        LL *records;
        
        RecordManager(int N);
        ~RecordManager();
        
        RandomNumber GetRandomNumber();
        
    } RecordManager;
    
}

#endif /* RecordManager_hpp */
