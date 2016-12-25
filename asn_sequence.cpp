#include "asn_sequence.hpp"

void ASN_Sequence:: setLength()
{
    length = 0;
    for (auto it = asn_object_p.begin(); it != asn_object_p.end(); it++)
        length += (*it)->fullSize(); // pelne dlugosci obiektow
}

ASN_Sequence:: ASN_Sequence() { tag = 0x30;}

void ASN_Sequence::serialize(Byte_vect &buf)
{
    setLength();
    serialize_tag_length(buf);

    for (auto it = asn_object_p.begin(); it != asn_object_p.end(); it++)
        (*it)->serialize(buf);
}

void ASN_Sequence::deserialize(const Byte_vect &buf, int shift)
{
    if (buf[shift] != tag)
        throw(Exception(WRONG_TAG));

    std::pair<int,int> length_shift = deserialize_length(buf,shift);
    length = length_shift.first; // ile bajtów do odczytu
    int off_seq = length_shift.second; // ile bajtów do pominięcia (kodujących długość)
    int count = shift + 2 + off_seq; // licznik przerobionych bajtów, z wartośćią początkową tam gdzie rozpoczynamy odczyt
    for (auto it = asn_object_p.begin(); it != asn_object_p.end(); it++)
    {
        if (count == length)
            break; // odczytaliśmy length bajtów, koniec
        (*it)->deserialize(buf, count); // count -  gdzie zaczyna się kolejny obiekt
        count += (*it)->fullSize();
    }
}
