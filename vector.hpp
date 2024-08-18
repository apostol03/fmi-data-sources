#pragma once

#include <iostream>

template <typename T>
class vector
{
public:
    vector() : sz(0), capacity(8)
    {
        data = new T[capacity];
    }

    vector(T *elements, size_t sz) : capacity(8)
    {
        if (sz <= 0 || sz >= capacity)
        {
            throw std::invalid_argument("Invalid vector size provided: " + sz);
        }

        this->sz = sz;
        data = new T[capacity];
        for (size_t i = 0; i < sz; i++)
        {
            data[i] = elements[i];
        }
    }

    vector(const vector &other)
    {
        copy(other);
    }

    vector &operator=(const vector &other)
    {
        if (this != &other)
        {
            erase();
            copy(other);
        }

        return *this;
    }

    ~vector()
    {
        erase();
    }

public:
    void push_back(const T &element)
    {
        if (sz == capacity)
        {
            resize();
        }

        data[sz++] = element;
    }

    T &operator[](int index) const
    {
        if (index < 0 || index >= sz)
        {
            throw std::out_of_range("Index is out of bounds!");
        }

        return data[index];
    }

    bool empty() const
    {
        return sz == 0;
    }

    const size_t size() const
    {
        return sz;
    }

    void print()
    {
        for (size_t i = 0; i < sz; ++i)
        {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }

private:
    void resize()
    {
        try
        {
            capacity *= 2;
            T *buffer = new T[capacity];

            for (size_t i = 0; i < sz; i++)
            {
                buffer[i] = data[i];
            }

            delete[] data;
            data = buffer;
        }
        catch (const std::bad_alloc &e)
        {
            std::cerr << "Memory allocation failed during resize: " << e.what() << std::endl;
            throw;
        }
    }

    void copy(const vector &other)
    {
        try
        {
            sz = other.sz;
            capacity = other.capacity;
            data = new T[capacity];
            for (size_t i = 0; i < sz; i++)
            {
                data[i] = other.data[i];
            }
        }
        catch (const std::bad_alloc &e)
        {
            std::cerr << "Memory allocation failed during copy: " << e.what() << std::endl;
            throw;
        }
    }

    void erase()
    {
        delete[] data;
        data = nullptr;
        sz = 0;
        capacity = 0;
    }

private:
    T *data;
    size_t sz;
    size_t capacity;
};