#pragma once

#include "DataSource.hpp"
#include <fstream>

template <typename T>
class FileDataSource : public DataSource<T>
{
public:
    FileDataSource(const std::string &fileName) : file(fileName)
    {
        if (!file.is_open())
        {
            throw std::runtime_error("Could not open file " + fileName);
        }
    }

    T extract() override
    {
        T value;
        file >> value;
        return value;
    }

    vector<T> extract(int n) override
    {
        vector<T> values;
        for (size_t i = 0; i < n && file; i++)
        {
            values.push_back(extract());
        }

        return values;
    }

    bool hasNext() const override
    {
        return !file.eof();
    }

    bool reset() override
    {
        file.clear();
        file.seekg(0);
        return true;
    }

private:
    std::ifstream file;
};