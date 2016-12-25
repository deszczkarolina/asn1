#ifndef OSOBA_H
#define OSOBA_H

#include <iostream>
#include "asn.hpp"
#include "asn_integer.hpp"
#include "asn_bitstring.hpp"
#include "asn_enumerated.hpp"
#include "asn_utf8string.hpp"
#include "asn_sequence.hpp"

/// zainteresowania
enum interests {NARTY, LYZWY, KSIAZKI, PLYWANIE};

/// klasa Osoba
class Osoba: public ASN_Sequence, public IDisplayable
{
    public:
        ASN_Utf8string imie;
        ASN_Utf8string nazwisko;
        ASN_Integer wiek;
        ASN_Enumerated plec;
        ASN_Bitstring zainteresowania;

        ///konstruktor domyślny
        Osoba();
        /// konstruktor tworzący "konkretną" osobę
        Osoba(std::string name, std::string surname, int age, bool gender, ASN_Bitstring interest);
        /// wyświetlanie
        void display();
};
#endif
