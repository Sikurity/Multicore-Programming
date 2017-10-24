//
//  main.cpp
//  MulticoreHW2
//
//  Created by YeongsikLee on 2017. 10. 15..
//  Copyright © 2017년 boostcamp. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <string.h>

#include <list>
#include <string>

#include "RecordManager.hpp"
#include "ThreadManager.hpp"

#define MAX_FILENAME_LENGTH 256

using namespace std;



int main(int argc, const char * argv[]) {
    
    int i, j, size;
    int N, R, E;
    
    try {
        
        if (argc != 4)
            throw -1;
        
        size = static_cast<int>(strlen(argv[1]));
        
        for(i = 1 ; i <= 3 ; i++) {
            for(j = 0 ; j < size; j++) {
                if( argv[i][j]  < '0' || '9' < argv[i][j] )
                    break;
            }
            
            if (j != size)
                throw i;
        }
        
    } catch( int error ) {
        
        if (error < 0)
            printf("입력 인자로 숫자 3개(N, R, E)가 필요합니다\n");
        else
            printf("%d번째 값이 숫자가 아닙니다\n", error);
        
        return -1;
    }
    
    N = atoi(argv[1]);
    R = atoi(argv[2]);
    E = atoi(argv[3]);
    
    FILE **files = new FILE *[N];
    for(i = 1 ; i <= N ; i++) {
        char fileName[MAX_FILENAME_LENGTH];
        
        sprintf(fileName, "thread%d", i);
        files[i] = fopen(fileName, "w+");
    }
    
    srand(static_cast<unsigned int>(time(NULL)));
    
    lys::RecordManager recordManager = lys::RecordManager(R);
    lys::ThreadManager threadManager = lys::ThreadManager(N, E);
    
    
    return 0;
}
