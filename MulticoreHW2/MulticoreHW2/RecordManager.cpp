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
    
    Record::Record() {
        value = 100ll;
    };
    
    int RecordManager::numberOfRecords;
    Record *RecordManager::records;

    RecordManager::RecordManager(int R) {
        
        numberOfRecords = R;
        
        this->records = new Record[numberOfRecords];
    }

    RecordManager::~RecordManager() {
        
        delete[] this->records;
    }
}
