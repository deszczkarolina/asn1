#ifndef asn_utf8string_h
#define asn_utf8string_h

#include "asn.hpp"


/// \brief Klasa ASN_Utf8string
/// kodowanie: [tag][długość][ciąg charów]

class ASN_Utf8string: public ASNobject
{
    private:

        std::string utf8string;
        /// metoda ustawiająca wartość pola length
        void setLength();

    public:
        ///deserializacja
        void deserialize(const Byte_vect &buf, int shift = 0);
        ///serializacja
        void serialize(Byte_vect &buf);
        ///konstruktor domyślny
        ASN_Utf8string();
         ///konstruktor
        ASN_Utf8string(const std::string &string);
        ///konstruktor
        ASN_Utf8string(const char* utf8c);


        operator std::string ();
        const char& operator[] (int i) const;
        bool operator==(const ASN_Utf8string& rhs) const;

};
#endif // asn_utf8string_h
