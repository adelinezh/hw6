#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        std::string currentString = k;
        for (int i = 0; i < currentString.length(); i ++)
        {
          if (currentString[i] >= 'A' && currentString[i] <= 'Z')
          {
            currentString[i] = std::tolower(currentString[i]);
          }
        }

        std::vector<HASH_INDEX_T> w(5,0);
        int chunkIndex = 4;
        int pos = currentString.length();

        while (pos > 0 && chunkIndex >= 0)
        {
          HASH_INDEX_T chunkValue = 0;
          HASH_INDEX_T base = 1;
          for (int i = 0; i < 6; i ++)
          {
            pos --;
            if (pos >= 0)
            {
              HASH_INDEX_T num = letterDigitToNumber(currentString[pos]);
              chunkValue += num * base;
              base *= 36;
            }
            else
            {
              break;
            }
          }
          w[chunkIndex] = chunkValue;
          chunkIndex --;
        }

        HASH_INDEX_T hash = 0;
        for (int i = 0; i < 5; i ++)
        {
          hash += w[i] * rValues[i];
        }
        return hash;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        
        if (letter >= 'a' && letter <= 'z')
        {
          return (letter - 'a');
        }
        else if (letter >= '0' && letter <= '9')
        {
          return 26 + (letter - '0');
        }
        else
        {
          throw std::invalid_argument("Invalid value");
        }

    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
