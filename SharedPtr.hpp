//
//  SharedPtr.hpp
//  test
//
//  Created by ser-hozero on 2023/01/03.
//

#pragma once

//#ifndef SharedPtr_hpp
//#define SharedPtr_hpp

#include <stdio.h>
#include <iostream>
#include <memory>

#include "EnableSharedFromThis.hpp"
#include "MemoryCheck.h"

template<class T>
class SharedPtr
{
private:
    T*      ptr_;
    int*    refCount_;

private:
    void manageCurPtrs();   // used for Destructor, operator=
    void deletePointers();  // used for manageCurPtrs
    
public:
    // Methods
    void reset();
    int useCount() const;
    
public:
    // Operators
    T& operator*() const;
    T* operator->() const;
    
    SharedPtr& operator= (const SharedPtr& x) noexcept; // copy
    SharedPtr& operator= (SharedPtr&& rx) noexcept;     // move
    
public:
    // Constructors
    SharedPtr(T* ptr = nullptr);
    SharedPtr(const SharedPtr& x);  // copy
    SharedPtr(SharedPtr&& rx);      // move

    
    // Destructor
    ~SharedPtr();
};

template<class T, class... Args>
SharedPtr<T> makeShared(Args&&... args);

//#endif /* SharedPtr_hpp */
