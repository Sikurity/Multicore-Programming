//
//  ThreadManager.cpp
//  MulticoreHW2
//
//  Created by YeongsikLee on 2017. 10. 15..
//  Copyright © 2017년 Hanyang Osori. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "RecordManager.hpp"
#include "ThreadManager.hpp"

namespace lys {
    
    bool isFirstRequestTypeRead() {
        
        return true;
    }
    
    bool checkDeadLock() {
        
        return false;
    }
    
    void rollBack(int stage) {
        
        return;
    }
    
    pthread_mutex_t ThreadManager::gloablRecoredMutex;
    
    int ThreadManager::goalExecutionOrder;
    int ThreadManager::currentExecutionOrder;
    
    int ThreadManager::numberOfThreads;
    Thread *ThreadManager::threads;
    
    /// 스레드 주소공간 모두 반환
    ThreadManager::ThreadManager(int N, int E) {
        
        ThreadManager::threads = new Thread[N]();
        
        for(int i = 0 ; i < N ; i++)
            ThreadManager::threads[i].threadNum = i;
        
        numberOfThreads = N;
        goalExecutionOrder = E;
        
        gloablRecoredMutex = PTHREAD_MUTEX_INITIALIZER;
    }
    
    /// 스레드 주소공간 모두 반환
    ThreadManager::~ThreadManager() {
        delete[] this->threads;
    }
    
    /******************************************************************/
    
    Thread::Thread() {
        cond = PTHREAD_COND_INITIALIZER;
    }
    
    void *Thread::transactionMethodWrapper(void *arg) {
        
        int result = 0;
        
        try {
            Thread *self = (Thread *)arg;
            
            self->transactionMethod();
        } catch(int errono) {
            
            result = -1;
        }
        
        return reinterpret_cast<void *>(result);
    }
    
    void Thread::transactionMethod() {
        
        int i, j, k;
        int commit_id = -1;
        
        LL record_i, record_j, record_k;
        LL prev_j, prev_k;
        
        
        while(commit_id <= ThreadManager::goalExecutionOrder) {
            
            i = rand() % RecordManager::numberOfRecords;
            
            do {
                j = rand() % RecordManager::numberOfRecords;
            } while(i == j);
            
            do {
                k = rand() % RecordManager::numberOfRecords;
            } while(i == k || j == k);
            
            
            
            pthread_mutex_lock(&ThreadManager::gloablRecoredMutex);
            
            list<ResourceRequest> &waitingList_i = RecordManager::records[i].requestThreadNum;
            
            if( waitingList_i.empty() || waitingList_i.begin()->rw == READ) {
                
                pthread_mutex_unlock(&ThreadManager::gloablRecoredMutex);
                record_i = RecordManager::records[i].value;
            } else {
                bool isDeadLock = checkDeadLock();
                
                if( isDeadLock ) {
                    pthread_mutex_unlock(&ThreadManager::gloablRecoredMutex);
                    continue;
                } else {
                    // list에 어떻게 넣을 것인가...
                    pthread_cond_wait(&cond, &ThreadManager::gloablRecoredMutex);
                    
                    pthread_mutex_unlock(&ThreadManager::gloablRecoredMutex);
                    
                    record_i = RecordManager::records[i].value;
                }
            }
            
            
            
            pthread_mutex_lock(&ThreadManager::gloablRecoredMutex);
            
            list<ResourceRequest> &waitingList_j = RecordManager::records[j].requestThreadNum;
            
            if( waitingList_j.empty()) {
                
                pthread_mutex_unlock(&ThreadManager::gloablRecoredMutex);
                
                prev_j = RecordManager::records[j].value;
                RecordManager::records[j].value = record_i + 1;
                record_j = RecordManager::records[j].value;
            } else {
                bool isDeadLock = checkDeadLock();
                
                if( isDeadLock ) {
                    rollBack(1);
                    pthread_mutex_unlock(&ThreadManager::gloablRecoredMutex);
                    continue;
                } else {
                    // 그냥 list 맨 뒤에 넣자
                    pthread_cond_wait(&cond, &ThreadManager::gloablRecoredMutex);
                    
                    pthread_mutex_unlock(&ThreadManager::gloablRecoredMutex);
                    
                    prev_j = RecordManager::records[j].value;
                    RecordManager::records[j].value = record_i + 1;
                    record_j = RecordManager::records[j].value;
                }
            }
            
            
            
            pthread_mutex_lock(&ThreadManager::gloablRecoredMutex);
            
            list<ResourceRequest> &waitingList_k = RecordManager::records[j].requestThreadNum;
            
            if( waitingList_k.empty()) {
                
                pthread_mutex_unlock(&ThreadManager::gloablRecoredMutex);
                
                prev_k = RecordManager::records[k].value;
                RecordManager::records[k].value -= record_i;
                record_k = RecordManager::records[k].value;
            } else {
                bool isDeadLock = checkDeadLock();
                
                if( isDeadLock ) {
                    rollBack(2);
                    pthread_mutex_unlock(&ThreadManager::gloablRecoredMutex);
                    continue;
                } else {
                    // 그냥 list 맨 뒤에 넣자
                    pthread_cond_wait(&cond, &ThreadManager::gloablRecoredMutex);
                    
                    pthread_mutex_unlock(&ThreadManager::gloablRecoredMutex);
                    
                    prev_k = RecordManager::records[k].value;
                    RecordManager::records[k].value -= record_i;
                    record_k = RecordManager::records[k].value;
                }
            }
            
            pthread_mutex_lock(&ThreadManager::gloablRecoredMutex);
            
            // RecordManager::records[i].wakeUpWaitingThreads();
            // RecordManager::records[j].wakeUpWaitingThreads();
            // RecordManager::records[k].wakeUpWaitingThreads();
            
            commit_id = ++ThreadManager::currentExecutionOrder;
            if (commit_id > ThreadManager::goalExecutionOrder) {
                rollBack(3);
                pthread_mutex_unlock(&ThreadManager::gloablRecoredMutex);
                break;
            } else {
                printf("%d %d %d %d %lld %lld %lld", commit_id, i, j, k, record_i, record_j, record_k);
                pthread_mutex_unlock(&ThreadManager::gloablRecoredMutex);
            }
        }
    }
        
}
