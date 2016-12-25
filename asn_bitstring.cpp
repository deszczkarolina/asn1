#include "asn_bitstring.hpp"

ASN_Bitstring:: ASN_Bitstring() {tag = 0x03;}
ASN_Bitstring:: ASN_Bitstring(int size)
{
    tag = 0x03;
    bits.resize(size);
}
ASN_Bitstring:: ASN_Bitstring(BIT_ARRAY &bits): bits(bits)
{
    tag = 0x03;
    isSet = true;
    setLength();
}
ASN_Bitstring:: ASN_Bitstring(ASN_Bitstring &bstring): bits(bstring.bits) { isSet = true; };
void ASN_Bitstring:: setLength()
{
    length = (bits.size() / 8) + 1 + 1; // + 1 na unused
}

std::vector<bool> :: reference ASN_Bitstring::  operator[] (int i)
{
    if (bits.size() != 0)
        return bits[i];
    else
        throw(Exception(EMPTY_OBJECT));
}

void ASN_Bitstring:: operator = (const BIT_ARRAY& src_bits)
{
    isSet = true;
    bits = src_bits;
    setLength();
}

bool ASN_Bitstring:: operator== (const ASN_Bitstring& rhs) const
{
    return (bits == rhs.bits);
}

int ASN_Bitstring::size() { return bits.size(); };


void ASN_Bitstring::serialize(Byte_vect &buf)
{
    if (bits.size() == 0)
        throw(Exception(EMPTY_OBJECT));

    serialize_tag_length(buf);
    setLength();

    BYTE byte_tmp, bit_tmp;

    int bit_size = bits.size(); // licznik bitów pozostałych do przeróbki
    int unused = 8 - (bit_size % 8); // nieużywane bity na końcu ostatniego bajtu
    int j_limit; // ile bitów zamieniamy na bajt w pętli for z j

    buf.push_back(unused);

    for(uint i = 0; i < length - 1; i++) // i-ty bajt ciągu binarnego
    {
        if (bit_size >= 8)
            j_limit = 8;
        else
            j_limit = bit_size;

        byte_tmp = 0;
        for(uint j=0; j < j_limit; j++)
        {
            bit_tmp = (bits[8*i+j]); // j-ty bit w i-tym bajcie ciągu

            byte_tmp += (int(bit_tmp) << 7-j); // dodajemy go "odwracajac" starszenstwo bitow w bajcie
                                                // ponieważ pozycje w tablicy są w odwrotnej kolejności niż wagi
        }
        bit_size -= j_limit;
        buf.push_back(byte_tmp); // gotowy bajt do paczki
    }
}

void ASN_Bitstring::deserialize(const Byte_vect &buf, int shift)
{
    if (buf[shift] != tag) throw ("Not an ASN BITSTRING");

    std::pair<int,int> length_shift = deserialize_length(buf,shift);
    length = length_shift.first; // ile bajtów do odczytu (wraz z bajtem unused)
    uint off = length_shift.second; // ile bajtów do pominięcia (kodujących długość)

    int unused = buf[shift + 2 + off];

    int j_limit; // ile bitów przerabiamy


    bits.clear();

    BIT bit_tmp;
    BYTE byte_tmp;

    for(int i=0; i < length - 1; i++) // length - 1, bo bez bajtu unused
    {
        byte_tmp = buf[shift + (i+3) + off];


        if (i != length - 2)
            j_limit = 8;
        else
            j_limit = 8 - unused; // ostatnie bity

        for(int j = 0; j < j_limit; j++)
        {
            bits.push_back(byte_tmp & (1 << (7-j))); // j-ty bit w i-tym bajcie bits = (7-j)-ty bit w byte_tmp
        }
    }
    setLength();
    isSet = true;
}
