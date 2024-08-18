#pragma once

#include "DataSource.hpp"

template <typename T>
class ArrayDataSource : public DataSource<T>
{
public:
    ArrayDataSource(const vector<T> &arr) : arr(arr), curr(0) {}

    T extract() override
    {
        if (curr >= arr.size())
        {
            throw std::out_of_range("No more elements in array!");
        }
        return arr[curr++];
    }

    vector<T> extract(int n) override
    {
        vector<T> values;
        for (size_t i = 0; i < n && curr < arr.size(); i++)
        {
            values.push_back(extract());
        }
        return values;
    }

    bool hasNext() const override
    {
        return curr < arr.size();
    }

    bool reset() override
    {
        curr = 0;
        return true;
    }

    ArrayDataSource &operator+(const T &element)
    {
        ArrayDataSource<T> newArr = *this;
        newArr.arr.push_back(element);
        return newArr;
    }
    
    ArrayDataSource &operator+=(const T &element)
    {        
        *this = *this + element;
        return *this;
    }

    ArrayDataSource &operator--()
    {
        if (curr > 0)
        {
            --curr;
        }
        return *this;
    }

    ArrayDataSource operator--(int)
    {
        ArrayDataSource tmp = *this;
        --(*this);
        return *tmp;
    }

private:
    vector<T> arr;
    int curr;
};