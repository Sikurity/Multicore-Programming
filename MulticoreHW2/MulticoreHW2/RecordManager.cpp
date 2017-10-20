//
//  RecordManager.cpp
//  MulticoreHW2
//
//  Created by YeongsikLee on 2017. 10. 15..
//  Copyright © 2017년 boostcamp. All rights reserved.
//

#include "RecordManager.hpp"
#include <stdlib.h>

typedef long long LL;

namespace lys {

    RecordManager::RecordManager(int N) {
        
        numberOfRecords = N;
        
        this->records = new LL[numberOfRecords];
        
        for(int i = 0 ; i < N ; i++)
            this->records[i] = 100ll;
    }

    RecordManager::~RecordManager() {
        
        delete[] this->records;
    }

    RandomNumber RecordManager::GetRandomNumber() {
        RandomNumber numbers;
        
        numbers.i = rand() % numberOfRecords;
        numbers.j = rand() % numberOfRecords;
        numbers.k = rand() % numberOfRecords;
        
        return numbers;
    }
    
}
