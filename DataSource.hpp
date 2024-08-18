#pragma once

#include "vector.hpp"

template <typename T>
class DataSource
{
public:
    virtual ~DataSource() = default;
    virtual T extract() = 0;
    virtual vector<T> extract(int n) = 0;
    virtual bool hasNext() const = 0;
    virtual bool reset() = 0;
    virtual operator bool() const
    {
        return hasNext();
    }
    virtual T operator()()
    {
        return extract();
    }
    virtual DataSource &operator>>(T &output)
    {
        output = extract();
        return *this;
    }
};