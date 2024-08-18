#pragma once

#include "constants.h"
#include "string.hpp"
#include "NumberGenerator.hpp"
#include "GeneratorDataSource.hpp"
#include "ArrayDataSource.hpp"
#include "AlternateDataSource.hpp"
#include "FileDataSource.hpp"

string generateRandomString()
{
    const char lowercase_letters[] = "abcdefghijklmnopqrstuvwxyz";

    string str;
    for (size_t i = 0; i < WORD_SIZE; i++)
    {
        str += lowercase_letters[rand() % (sizeof(lowercase_letters) - 1)];
    }

    return str;
}

void generateBinFile(const string &binName, AlternateDataSource<int> &altSource)
{
    std::ofstream binFile(binName.c_str(), std::ios::binary);
    if (!binFile.is_open())
    {
        throw std::runtime_error("Binary file couldn't be opened!");
    }

    for (size_t i = 0; i < BIN_NUMBERS; i++)
    {
        int num;
        altSource >> num;

        binFile.write(reinterpret_cast<const char *>(&num), sizeof(num));
    }

    binFile.close();
}

void convertBinToTxt(const string &binName, const string &txtName)
{
    std::ifstream binFile(binName.c_str(), std::ios::binary);
    if (!binFile.is_open())
    {
        throw std::runtime_error("Binary file couldn't be opened!");
    }

    std::ofstream txtFile(txtName.c_str());
    if (!txtFile.is_open())
    {
        throw std::runtime_error("Text file couldn't be opened!");
    }

    int num;
    while (binFile.read(reinterpret_cast<char *>(&num), sizeof(num)))
    {
        txtFile << num << "\n";
    }

    binFile.close();
    txtFile.close();
}

void generateStrings()
{
    std::cout << "Generating " << WORDS_COUNT << " strings..." << std::endl;

    try
    {
        GeneratorDataSource<string> generator(generateRandomString);
        vector<string> strings = generator.extract(WORDS_COUNT);
        for (size_t i = 0; i < strings.size(); i++)
        {
            std::cout << strings[i].c_str() << std::endl;
        }
    }
    catch (...)
    {
        throw std::runtime_error("Something went wrong while generating strings!");
    }
}

void printTextFileOfNumbers()
{
    GeneratorDataSource<int> primesSource(NumberGenerator::nextPrime);
    GeneratorDataSource<int> integersSource(NumberGenerator::nextRandomInt);
    GeneratorDataSource<int> fibonacciSource(NumberGenerator::nextFibonacci);
    
    vector<int> values = fibonacciSource.extract(FIBONACCI_REQUIRED);
    ArrayDataSource<int> arrSource(values);

    DataSource<int> *arr[] = {&primesSource, &integersSource, &arrSource};
    vector<DataSource<int> *> dataSources(arr, 3);
    AlternateDataSource<int> altSource(dataSources);

    std::cout << "Please insert a file name to put the data into: " << std::endl;
    string fileName;
    std::cin >> fileName;

    string binName = fileName + ".dat";

    std::cout << "Generating data in binary file..." << std::endl;
    generateBinFile(binName, altSource);

    string txtName = fileName + ".txt";

    std::cout << "Transferring data from binary file to text file..." << std::endl;
    convertBinToTxt(binName, txtName);

    std::cout << "Extracting data from the text file..." << std::endl;
    FileDataSource<int> fileSource(txtName.c_str());
    while (fileSource.hasNext())
    {
        std::cout << fileSource() << " ";
    }
}

void run()
{
    generateStrings();
    printTextFileOfNumbers();
}
