#pragma once

#include "DataSource.hpp"

template <typename T>
class GeneratorDataSource : public DataSource<T>
{    
public:
    GeneratorDataSource(T (*func)()) : func(func) {}

    T extract() override
    {
        return func();
    }

    vector<T> extract(int n) override
    {
        vector<T> values;
        for (size_t i = 0; i < n; i++)
        {
            values.push_back(func());
        }
        
        return values;
    }

    bool hasNext() const override
    {
        return true;
    }

    bool reset() override
    {
        return false;
    }

private:
    T (*func)();
};