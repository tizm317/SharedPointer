//
//  MemoryCheck.h
//  test
//
//  Created by ser-hozero on 2023/01/04.
//

#pragma once

extern int memorySize;
extern int newCnt;
extern int deleteCnt;

extern void * operator new(size_t size);
extern void operator delete(void* p);

