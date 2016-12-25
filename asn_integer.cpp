#include "asn_integer.hpp"

ASN_Integer:: ASN_Integer(int value): value(value)
{
    tag = 0x02;
    isSet = true;
    setLength();
}

ASN_Integer:: operator int()
{
    return value;
}
ASN_Integer:: operator const int() const
{
    int x = value;
    return x;
}
 void ASN_Integer:: operator=(int value)
{
    isSet = true;
    this->value = value;
    setLength();
}

void ASN_Integer::setLength()
{
    int l = 1;
    int tmp_value = value;
    while(tmp_value = tmp_value / 256)
        l++;
    if (value & (0x01 << 8*l - 1)) // jesli najstarszy bit to 1
    {
        if (value > 0) // i jesli dodatni, to dodatkowy bajt zer
            l++;
    }
    else if (value < 0) // jesli najstarszy bit to 0 i ujemny to dodatkowy bajt potrzebny
        l++;
   length = l;
}


void ASN_Integer::serialize(Byte_vect &buf)
{
    if (!isSet)
        throw(Exception(EMPTY_OBJECT));

    serialize_tag_length(buf);

    if(value & (0x01 << 8*length - 1)) // jesli liczba jest dodatnia i jej najstarszy bit = 1
        if (value > 0)
            buf.push_back(0x00); // to musimy dodac bajt zer

    for(int i = 0; i < length; i++)
    {
        buf.push_back((value & (0xFF << 8*(length - i - 1))) >> 8*(length - i - 1));
    }
}

void ASN_Integer::deserialize(const Byte_vect &buf, int shift)
{
   if (buf[shift] != tag) throw (Exception(WRONG_TAG));
   else
   {
       std::pair <int,int> length_shift = deserialize_length (buf,shift);
       length = length_shift.first; // ile bajtów do odczytu
       int off = length_shift.second; // ile bajtów ominąć (które kodują długość) - 1

       value = 0;
       for(int i = 0; i < length - 1; i++)
            value += buf[shift + (length - i + 1) + off] << 8*i; // dodawanie danego bajtu * jego waga w systemie 256

       // ostatni bajt, zawiera on bit znaku
       BYTE tmp_val = (buf[shift + 2 + off]);
       if (tmp_val & 0x80) // int ujemny
       {
           value += (tmp_val - 0x80) << 8*(length - 1); // dodajemy wartość 7 ostatnich bitów
           value -= (0x80 << 8*(length - 1)); // odejmujemy wagę 1-go bitu
       }
       else // int dodatni, normalna wartość
            value += (tmp_val << 8*(length - 1));
    }
   isSet = true;
}
