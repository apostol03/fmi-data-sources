#pragma once

#include "DataSource.hpp"

template <typename T>
class AlternateDataSource : public DataSource<T>
{
public:
    AlternateDataSource(vector<DataSource<T> *> sources) : sources(sources), currSource(0) {}

    T extract() override
    {
        if (sources.empty())
        {
            throw std::out_of_range("No sources available!");
        }

        for (size_t i = 0; i < sources.size(); i++)
        {
            DataSource<T> *current = sources[currSource];
            if (current != nullptr && current->hasNext())
            {
                T value = current->extract();
                currSource = (currSource + 1) % sources.size();
                return value;
            }
            currSource = (currSource + 1) % sources.size();
        }

        throw std::out_of_range("No more elements available in the sources!");
    }

    vector<T> extract(int n) override
    {
        vector<T> values;
        for (size_t i = 0; i < n; i++)
        {
            values.push_back(extract());
        }
        return values;
    }

    bool hasNext() const override
    {
        for (size_t i = 0; i < sources.size(); i++)
        {
            if (!sources[i]->hasNext())
            {
                return false;
            }
        }

        return true;
    }

    bool reset() override
    {        
        for (size_t i = 0; i < sources.size(); i++)
        {
            sources[i]->reset();
        }
        
        return true;
    }

private:
    const vector<DataSource<T> *> sources;
    int currSource;
};