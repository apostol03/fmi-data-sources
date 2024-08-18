#pragma once

#include "DataSource.hpp"

template <typename T>
class DefaultDataSource : public DataSource<T> 
{
    T extract() override 
    {
        return T();
    }

    std::vector<T> extract(int n) override
    {
        return vector<T>(n, T());
    }

    bool hasNext() const override 
    {
        return true;
    }

    bool reset() override 
    {
        return true;
    }
};