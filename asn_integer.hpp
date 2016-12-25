#ifndef asn_integer
#define asn_integer
#include "asn.hpp"

/// \brief klasa ASN_Integer
/// kodowanie: [tag][długość (1 lub więcej bajtów)][wartość zapisana w kodzie U2]

class ASN_Integer: public ASNobject
{
    protected:
        /// wartość
        int value;
        /// metoda ustawiająca długość
        void setLength();

    public:

        ///serializacja
		void serialize(Byte_vect &buf);
        ///deserializacja
        void deserialize(const Byte_vect &buf, int shift = 0);
        ///konstruktor domyślny
		ASN_Integer(): value(0) {tag = 0x02;}
        /// konstruktor wywoływany dla konkretnej wartości
        ASN_Integer(int value);

        operator int();
        operator const int() const;
        void operator=(int value);

};
#endif // asn_integer

