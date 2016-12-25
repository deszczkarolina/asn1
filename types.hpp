#ifndef types_h
#define types_h
#include <vector>
#include <iostream>
#include <fstream>
#include "exception.hpp"

typedef unsigned char BYTE;
typedef bool BIT;
typedef std::vector<BIT> BIT_ARRAY;

/// interfejs zapisywania do pliku
class IStorable
{
	public:
		virtual void writeToFile(std::string f_name) = 0;
};

/// interfejs wyświetlania
class IDisplayable
{
	public:
		virtual void display() = 0;
};


/// bufor bajtów
class Byte_vect: public std::vector<BYTE>, public IStorable
{
    public:
        void writeToFile(std::string f_name)
        {
            std::ofstream file;
            file.open(f_name, std::ios::out | std::ios::binary);

            if (file.is_open())
            {
                file.write((char*)data(), (int)size());
                file.close();
            }
            else
            {
                throw(Exception(FILE_NOT_OPEN));
            }
        }

        void readFromFile(std::string f_name)
        {
            std::ifstream file;
            file.open(f_name, std::ios::in | std::ios::binary | std::ios::ate);
            if (file.is_open())
            {
                int size = file.tellg();
                resize(size);

                file.seekg (0, std::ios::beg);
                file.read((char*)data(), size);
                file.close();
            }
            else
            {
               throw(Exception(FILE_NOT_OPEN));
            }
        }
};
#endif
