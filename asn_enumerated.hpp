#ifndef asn_enumerated_h
#define asn_enumerated_h

#include <unordered_map>
#include <initializer_list>
#include <iostream>
#include <cstdio>

#include "asn.hpp"
#include "asn_integer.hpp"

/// \brief Klasa ASN_Bitstring
/// kodowanie: jak ASN_Integer, jednak Enumerated może przybierać tylko określone wartości

class ASN_Enumerated: public ASN_Integer
{
    protected:
        /// mapa dozwolonych wartości i ich nazw
        std::unordered_map<std::string, int> value_dict;

        /// metoda określająca czy dana wartość jest dozwolona
        bool isCorrect(int value);

    public:
        /// deserializacja
        void deserialize(const Byte_vect &buf, int shift = 0);
        /// konstruktor domyślny
        ASN_Enumerated();
        /// metoda przypisująca nazwom domyślne wartości 0,1,2,... w kolejności ich wystąpienia
        void operator=(const std::initializer_list<std::string> il);
        ///  metoda przypisująca nazwom określone wartości
        void operator=(const std::unordered_map<std::string, int> &map);

        void operator=(int value);

        void operator=(std::string str);
        /// konwersja do nazwy tekstowej określającej wartość
        std::string toStr() const;

        operator std::string() const;
};

#endif
