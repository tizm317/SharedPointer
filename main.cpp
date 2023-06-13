//
//  main.cpp
//  test
//
//  Created by ser-hozero on 2023/01/03.
//

#include <iostream>
#include <vector>
#include <memory> // shared_ptr

#include "SharedPtr.hpp"
#include "SHaredPtr.cpp"

#include "EnableSharedFromThis.hpp"

struct TestStruct : public std::enable_shared_from_this<TestStruct>
{
    int a;
    int b;
    
public:
    int testFunc()
    {
        shared_from_this();
        
        return 0;
    }
    
};

class Book : public EnableSharedFromThis<Book>
{
private:
    std::string title_;
public:
    // Constructors
    Book(){}
    
    Book(std::string title)
        : title_(title)
    {}
    
    Book(const Book& book)
    {
        this->title_ = book.title_;
    }
    
    
    // Destructor
    ~Book(){}
    
    std::string getTitle()
    {
        return title_;
    }
    
    SharedPtr<Book> getPtr()
    {
        return SharedFromThis();
        //return shared_from_this();
        //return SharedPtr<Book>(this);
    }
};

class Library
{
private:
    SharedPtr<Book> bookArr[10];
    int count_;
    
public:
    // Consturctors
    Library()
        : count_(0)
    {}
    
    Library(SharedPtr<Book> book)
    {
        count_ = 0;
        bookArr[count_++] = book;
        
        std::cout << "added book title : " << bookArr[count_-1]->getTitle() << std::endl;
    }
    
    // Destructor
    ~Library()
    {}
    
    // Methods
    void addBooks(SharedPtr<Book> newBook)
    {
        bookArr[count_++] = newBook;
        
        std::cout << "added book title : " << bookArr[count_-1]->getTitle() << std::endl;
    }
};

template <typename T>
class TestClass
{
private:
    T* ptr_;
    long long* refCount_;
    
public:
    TestClass() {}
    TestClass(TestClass& x){}
};

class TestClass2
{
private:
    int value_;
    
public:
    TestClass2() {}
    TestClass2(const TestClass2& x) :value_(x.value_) {}
    TestClass2(TestClass2&& x) :value_(x.value_) {}
};


class Card
{
private:
    std::string name;
    int count;
public:
    Card(std::string n = "", int m = 0)
        : name(n), count(m)
    {
    }
};


int main(int argc, const char * argv[])
{
    std::shared_ptr<TestStruct> testStructPtr = std::make_shared<TestStruct>();
    
    
    // Shared From This
    {
        // case 1 :
        int* p = new int;
        
        SharedPtr<int> ptr1(p);
        std::cout << ptr1.useCount() << std::endl;
        SharedPtr<int> ptr2 = ptr1;
        std::cout << ptr1.useCount() << std::endl;
        
        
        // case 2 :
//        Book* p = new Book;
//
//        SharedPtr<Book> ptr1(p);
//        std::cout << ptr1.useCount() << std::endl;
//        SharedPtr<Book> ptr2 = ptr1->getPtr();
//        std::cout << ptr1.useCount() << std::endl;
        
        SharedPtr<Card> sp = makeShared<Card>("RareCard", 100);

    }
    
    std::cout << "New Cnt : " << newCnt << std::endl;
    std::cout << "Delete Cnt : " << deleteCnt << std::endl;
    
    return 0;
}
