#ifndef ARRAY_LIST_HPP
#define ARRAY_LIST_HPP

#include <stdexcept>
#include <cassert>
#include <initializer_list>

#include "linear_list.hpp"
#include "common.hpp"

template<class T>
class ArrayList : public LinearList<T> {

    void CheckIndex(int theIndex) const {
        if (theIndex < 0 || theIndex >= list_size_) {
            //throw std::range_error("index out of bounds");
            assert(false);
        }
    }

public:
    explicit ArrayList(int InitialCapacity = 1) :array_length_(InitialCapacity), list_size_(0)
    {
        assert(InitialCapacity > 0);
        element_ = new T[array_length_];
    }

    ArrayList(const ArrayList<T>& theList) :array_length_(theList.array_length_), list_size_(theList.list_size_) {
        element_ = new T[array_length_];
        // 原生类型的原生指针可以充当迭代器
        std::copy(theList.element_, theList.element_+list_size_, element_);
    }

    ArrayList(std::initializer_list<T> list) :ArrayList()
    {
        // 遍历初始化列表
        for (const T &e : list)
        {
            // 如果空间满了就扩容
            if (list_size_ == array_length_)
            {
                ChangeLength1D(element_, array_length_, 2 * array_length_);
                array_length_ *= 2;
            }
            element_[list_size_++] = e;
        }
    }

    ArrayList<T>& operator=(const ArrayList<T> theList)
    {
        ArrayList<T> temp;
        Swap(temp, theList);
        return temp;
    }

    ArrayList<T>& operator=(std::initializer_list<T> theList)
    {
        list_size_ = 0;
        for (const T &e : theList)
        {
            Insert(list_size_, e);
        }
        return *this;
    }

    ~ArrayList() override {delete []element_;}

    void Swap(ArrayList<T>& theList)
    {
        element_ = theList.element_;
        array_length_ = theList.array_length_;
        list_size_ = theList.list_size_;
    }

    int Capacity() const {return array_length_;}

    virtual bool Empty() const override {return list_size_ == 0;}

    virtual int Size() const override {return list_size_;}

    virtual T& Get(int index) const override {
        CheckIndex(index);

        return element_[index];
    }

    virtual int IndexOf(const T &theElement) const override {
        for (int i = 0; i < list_size_; ++i) {
            if (element_[i] == theElement) {
                return i;
            }
        }
        return -1;
    }

    virtual void Erase(int theIndex) override {
        CheckIndex(theIndex);

        for (int i = theIndex; i < list_size_-1; ++i) {
            element_[i] = element_[i+1];
        }
        --list_size_;
    }

    virtual void Insert(int theIndex, const T &theElement) override {
        if (theIndex < 0 || theIndex > list_size_) {
            throw std::range_error("index out of bounds");
            //assert(false);
        }

        if (list_size_ == array_length_) {
            ChangeLength1D(element_, array_length_, 2*array_length_);
            array_length_ *= 2;
        }

        for (int i = list_size_-1; i >= theIndex; --i) {
            element_[i+1] = element_[i];
        }
        element_[theIndex] = theElement;
        ++list_size_;
    }

    virtual void Output(std::ostream &out) const override {
        for (int i = 0; i < list_size_; ++i) {
            out << element_[i] << ' ';
        }
    }

private:
    T *element_;
    int array_length_;
    int list_size_;
};

#endif