#ifndef asn_sequence_h
#define asn_sequence_h

#include "asn.hpp"

 /// \brief klasa ASN_Sequence - jako wektor wskaźników na obiekty ASN w sekwencji
class ASN_Sequence: public ASNobject
{
    protected:
        /// wektor wskaźników na obiekty ASN w sekwencji
        std::vector<ASNobject*> asn_object_p;
        /// metoda ustawiająca wartość pola lenght
        void setLength();

    public:
        /// konstruktor domyślny
        ASN_Sequence();
        ///serializacja
        void serialize(Byte_vect &buf);
        /// deserializacja
        void deserialize(const Byte_vect &buf, int shift = 0);

};
#endif
