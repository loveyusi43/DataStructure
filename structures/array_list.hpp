#ifndef ARRAY_LIST_HPP
#define ARRAY_LIST_HPP

#include <stdexcept>

#include "linear_list.hpp"
#include "common.hpp"

template<class T>
class ArrayList : public LinearList<T> {

    void CheckIndex(int theIndex) const {
        if (theIndex < 0 || theIndex >= list_size_) {
            throw std::range_error("index out of bounds");
        }
    }

public:
    ArrayList(int InittialCapacity = 10) :array_length_(InittialCapacity), list_size_(0) {element_ = new T[array_length_];}

    ArrayList(const ArrayList<T>& theList) :array_length_(theList.array_length_), list_size_(theList.list_size_) {
        element_ = new T[array_length_];
        std::copy(theList.element_, theList.element_+list_size_, element_);
    }

    ~ArrayList() {delete []element_;}

    int Capacity() const {return array_length_;}

    virtual bool Empty() const {return list_size_ == 0;}

    virtual int Size() const {return list_size_;}

    virtual T& Get(int index) const {
        CheckIndex(index);

        return element_[index];
    }

    virtual int IndexOf(const T &theElement) const {
        for (int i = 0; i < list_size_; ++i) {
            if (element_[i] == theElement) {
                return i;
            }
        }
        return -1;
    }

    virtual void Erase(int theIndex) {
        CheckIndex(theIndex);

        for (int i = theIndex; i < list_size_-1; ++i) {
            element_[i] = element_[i+1];
        }
        --list_size_;
    }

    virtual void Insert(int theIndex, const T &theElement) {
        if (theIndex < 0 || theIndex > list_size_) {
            std::range_error("index out of bounds");
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

    virtual void Output(std::ostream &out) const {
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