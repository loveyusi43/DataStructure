#ifndef LINEAR_LIST_HPP
#define LINEAR_LIST_HPP

#include <ostream>

template<class T>
class LinearList{
public:
    virtual ~LinearList() {};

    virtual bool Empty() const = 0;

    virtual int Size() const = 0;

    virtual T& Get(int index) const = 0;

    virtual int IndexOf(const T &theElement) const = 0;

    virtual void Erase(int theIndex) = 0;

    virtual void Insert(int theIndex, const T &theElement) = 0;

    virtual void Output(std::ostream &out) const = 0;
};

#endif