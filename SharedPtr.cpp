//
//  SharedPtr.cpp
//  test
//
//  Created by ser-hozero on 2023/01/03.
//

#include "SharedPtr.hpp"

template <class T>
SharedPtr<T>::SharedPtr(T* ptr)
    : ptr_(ptr)
{
    // detect the presence of an enable_shared_from_this base
    // enableSharedFromThis 상속 받는 객체들
//    if(true == std::is_base_of<EnableSharedFromThis<T>, T>::value)
//    {
//        //if(ptr->weakPtr_.expired() == true)
//        if(nullptr != ptr->refCount)
//        {
//            refCount_ = ptr->refCount;
//            (*refCount_)++;
//        }
//        else
//        {
//            // 맨 처음
//            if(nullptr == ptr_)
//                ptr->refCount = new int(0);
//            else
//                ptr->refCount = new int(1);
//
//            refCount_ = ptr->refCount;
//        }
//    }
//    else
    {
        if(nullptr == ptr_)
            refCount_ = new int(0);
        else
            refCount_ = new int(1);
    }

        
    //std::cout << "default constructor\n";
}

template <class T>
SharedPtr<T>::SharedPtr(const SharedPtr& x) // const !!!
    : ptr_(x.ptr_) //: ptr(x.ptr), refCount(x.refCount)
{
    // l-value
    // copy 되어서 *refCount 증가시킴
    if(nullptr != ptr_)
    {
        refCount_ = x.refCount_;
        (*refCount_) += 1;
    }
    else // ptr == nullptr
    {
        refCount_ = new int(0);
    }
    
    //std::cout << "copy constructor\n";
}

template <class T>
SharedPtr<T>::SharedPtr(SharedPtr&& rx)
    : ptr_(rx.ptr), refCount_(rx.refCount)
{
    // r-value
    // move 되니까 rx 포인터 nullptr
    rx.ptr = nullptr;
    rx.refCount = nullptr;
    
    //std::cout << "move constructor\n";
}



template <class T>
SharedPtr<T>::~SharedPtr()
{
    manageCurPtrs();
    
    ptr_ = nullptr;
    refCount_ = nullptr;
    
    //std::cout << "destructor\n";
}

template <class T>
int SharedPtr<T>::useCount() const
{
    if(nullptr == refCount_)
    {
        assert(0); // refCount_ 가 nullptr 인 경우가 안 나와야 함
        return -1;
    }
    
    return *refCount_;
}

template <class T>
void SharedPtr<T>::reset()
{
    this->~SharedPtr();
}

template <class T>
T& SharedPtr<T>::operator*() const
{
    return *(this->ptr);
}

template <class T>
T* SharedPtr<T>::operator->() const
{
    return this->ptr_;
}

template <class T>
SharedPtr<T>& SharedPtr<T>::operator= (const SharedPtr<T>& x) noexcept
{
    // 1. 기존 ptr, refCount 관리
    manageCurPtrs();
    
    // 2. x의 ptr, refCount로 변경
    ptr_ = x.ptr_;
    refCount_ = x.refCount_;
    
    // x의 refCount == nullptr인 특수 case
    if(nullptr == refCount_)
    {
        assert(0); // refCount 항상 값을 넣어둬서 걸리진 않아야 함.
        refCount_ = new int(0);
    }
    else
        (*refCount_) += 1;
    
    return *this;
}

template <class T>
SharedPtr<T>& SharedPtr<T>::operator= (SharedPtr<T>&& rx) noexcept
{
    // 1. 기존 ptr, refCount 관리
    manageCurPtrs(rx);
    
    // move
    // 2. rx의 ptr, refCount로 변경
    ptr_ = rx.ptr;
    refCount_ = rx.refCount;
    
    // 3. rx 포인터 nullptr 처리
    rx.ptr = nullptr;
    rx.refCount = nullptr;
    
    return *this;
}

template <class T>
void SharedPtr<T>::manageCurPtrs()
{
    // refCount_ 조절 및 deletePointers 에서 delete
    
    // ptr == nullptr or last reference
    if(nullptr == refCount_)
        return;
    
    if(*refCount_ <= 1)
    {
        // delete
        deletePointers();
    }
    else // more refs..
    {
        (*refCount_) -= 1;
    }
}


template <class T>
void SharedPtr<T>::deletePointers()
{
    // delete + deletCnt, memorySize Check
    
    if(nullptr != ptr_)
    {
        //deleteCnt += 1;
        int Size = sizeof(*ptr_);
        if(ptr_ != nullptr)
            delete ptr_;
        
        memorySize -= Size;
        std::cout << "Delete Memory : " << Size << " Memory : " << memorySize << std::endl;
    }
    
    if(nullptr != refCount_)
    {
        //deleteCnt += 1;
        int Size = sizeof(*refCount_);
        
        if(refCount_ != nullptr)
            delete refCount_;
        
        memorySize -= Size;
        std::cout << "Delete Memory : " << Size << " Memory : " << memorySize << std::endl;
    }
}

template<class T, class... Args>
SharedPtr<T> makeShared(Args&&... args)
{
    return SharedPtr<T>(new T(std::forward<Args>(args)...));
    //return new T(std::forward<Args>(args)...);
}
