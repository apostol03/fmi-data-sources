#pragma once

#include <cstring>
#include <iostream> 

class string
{
public:
    string() : sz(0)
    {
        str = new char[1];
        str[0] = '\0';
    }

    string(const string &other)
    {
        copy(other);
    }

    string &operator=(const string &other)
    {
        if (this != &other)
        {
            erase();
            copy(other);
        }

        return *this;
    }

    ~string()
    {
        erase();
    }

public:
    size_t size() const 
    {
        return sz;
    }

    char * c_str() const
    {
        return str;
    }

    friend std::istream &operator>>(std::istream &in, string &str)
    {
        str.erase();

        char buffer[1024];
        in >> buffer;
        str.sz = strlen(buffer);
        str.str = new char[str.sz + 1];
        strcpy(str.str, buffer);

        return in;
    }

    string operator+(const string &other) const
    {
        string result;
        result.sz = sz + other.sz;
        result.str = new char[result.sz + 1];

        strcpy(result.str, str);
        strcpy(result.c_str() + strlen(result.c_str()), str);
        return result;
    }

    string operator+(const char* other) const {
        string result;
        size_t otherLen = std::strlen(other);
        result.sz = sz + otherLen;
        result.str = new char[result.sz + 1];

        strcpy(result.str, str);
        strcpy(result.c_str() + sz, other);

        return result;
    }

    string operator+(const char &other) const {
        string result;
        result.sz = sz + 1;
        result.str = new char[result.sz + 1];

        for (size_t i = 0; i < sz; i++) {
            result.str[i] = str[i];
        }

        result.str[sz] = other;
        result.str[result.sz] = '\0';

        return result;
    }

    string &operator+=(const char &other) 
    {
        *this = *this + other;
        return *this;
    }

    string &operator+=(const string &other) 
    {
        *this = *this + other;
        return *this;
    }

private:
    void copy(const string &other)
    {
        str = new char[other.sz + 1];
        sz = other.sz;
        for (size_t i = 0; i < sz; i++)
        {
            str[i] = other.str[i];
        }
        str[sz] = '\0';
    }

    void erase()
    {
        delete[] str;
    }

private:
    char * str;
    size_t sz;
};