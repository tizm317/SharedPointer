//
//  EnableSharedFromThis.hpp
//  test
//
//  Created by ser-hozero on 2023/01/06.
//

#pragma once
#include "SharedPtr.hpp"

#include <stdio.h>

//template<class T>
//class WeakPtr
//{
//private:
//    T* ptr_;
//public:
//    WeakPtr(){}
//    WeakPtr(const WeakPtr& wp){}
//    WeakPtr(WeakPtr&& wp){}
//    ~WeakPtr(){}
//    
//    bool expired() const {}        // 소유권 만료(참조된 개체 삭제) 여부 체크
//    SharedPtr<T> lock() const {}   // 소유권 공유하는 값 가져옴***
//    void reset();
//    int use_count() const;
//    
//};

template<class T> class SharedPtr;

template<class T>
class EnableSharedFromThis
{
private:
    int* refCount;
    //EnableSharedFromThis* weakThis_;
    
public:
    EnableSharedFromThis()
    {
        //weakThis_ = this;
    }
    EnableSharedFromThis(EnableSharedFromThis const&) {}
    EnableSharedFromThis& operator=(EnableSharedFromThis const&)
    {
        return  *this;
    }
    ~EnableSharedFromThis() {}

    
public:
    SharedPtr<T> SharedFromThis()
    {
        T* ptr = (T*)this;
        return SharedPtr<T>(ptr);
    }
    
    
    
    template <class U> friend class SharedPtr;
};

