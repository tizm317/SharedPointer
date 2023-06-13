//
//  MemoryCheck.cpp
//  test
//
//  Created by ser-hozero on 2023/01/05.
//

#include <stdio.h>
#include <iostream>
#include "MemoryCheck.h"


int memorySize = 0;
int newCnt = 0;
int deleteCnt = 0;

void * operator new(size_t size)
{
    newCnt += 1;
    memorySize += size;
    std::cout << "New Memory : " << size << " Memory : " << memorySize << std::endl;
    
    void * p = malloc(size);
    return p;
}

void operator delete(void * p)
{
    deleteCnt += 1;

    int size = sizeof(p);
    free(p);

//    memorySize -= size;
//    std::cout << "Delete Memory : " << size << " Memory : " << memorySize << std::endl;
}
