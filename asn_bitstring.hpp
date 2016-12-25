#ifndef asn_bitstring
#define asn_bitstring

#include "asn.hpp"
#include <vector>


/// \brief Klasa ASN_Bitstring
/// kodowanie: [tag][długość(1 lub więcej bajtów)][liczba nieużywanych bitów][bajty ciągu binarnego]

class ASN_Bitstring: public ASNobject
{
    private:
       /// zawartość
        BIT_ARRAY bits;
        /// metoda ustawiająca pole length
        void setLength();

    public:
        /// konstruktor domyślny
        ASN_Bitstring();
        /// konstruktor wywołany dla określonego rozmiaru
        ASN_Bitstring(int size);
        /// konstruktor wywołany dla określonego ciągu bitów
        ASN_Bitstring(BIT_ARRAY &bits);
        ASN_Bitstring(ASN_Bitstring &bstring);

        ///serializacja
        void serialize(Byte_vect &buf);
        ///deserializacja
        void deserialize(const Byte_vect &buf, int shift = 0);
        /// metoda zwracająca długość ciągu binarnego
        int size();
        std::vector<bool>::reference operator[] (int i);
        void operator = (const BIT_ARRAY& src_bits);
        bool operator == (const ASN_Bitstring& rhs) const;

};
#endif
