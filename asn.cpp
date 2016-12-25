#include "asn.hpp"

int ASNobject:: fullSize()
{
    if (length < 128)
        return 2 + length;  // 1 na tag, 1 na dlugosc, length na bajty zawartosci
    else
    {
        int tmp_length = length;
        BYTE length_of_length = 1; //na ilu bajtach zapisana jest długość
        while(tmp_length = (tmp_length >> 8)) //przesunęcie bitowe o 8bitów w prawo - dzielenie przez 2^8
            length_of_length++;
        return 1 + 1 + length_of_length + length; // 1 na tag, 1 na ile bajtow kodujacych dlugosc, length_of_length na bajty kodujace dlugosc, length na bajty zawartosci
    }
}
void ASNobject:: serialize_tag_length(Byte_vect &buf)
{
    buf.push_back(tag);
    if (length < 128)
        buf.push_back(length);
    else
    {
        int tmp_length = length;
        BYTE length_of_length = 1; // na ilu bajtach zakodowana dlugosc
        while(tmp_length = (tmp_length >> 8))
        length_of_length++;
        // zakladamy ze length_of_length < 128
        buf.push_back(length_of_length | 0x80);  // 0x80 = 128 = 2^7 - najstarszy bit = 1, po operacji OR na tym bicie będzie 1, a na pozostałych bity length of length
        for(int i = 0; i < length_of_length; i++)
        {
            buf.push_back((length & (0xFF << 8*(length_of_length - i - 1))) >> 8*(length_of_length - i - 1));
            // maska poprzez AND z odp przesunietym 0xFF (1111 1111) da dany bajt inta
            // i = 0 -> przesuwamy 0xFF do najstarszego bajtu
            // i = len_of_len - 1 -> 0xFF zostaje, to najmlodszy bajt
            // length & przesuniete 0xFF -> dany bajt inta ktory jeszcze trzeba przesunac na najmlodszy bajt
        }

    }
}
std::pair<int, int> ASNobject:: deserialize_length (const Byte_vect& buf, int shift)
{
    // jednobajtowa
    if (!(buf[shift+1] & 0x80)) //najstarszy bit !1
        return std::make_pair(buf[shift+1], 0);
    // wielobajtowa
    else
    {
        int length_of_length = buf[shift+1] - 0x80; // usuwamy najstarszy bit ktory jest 1
        int length = 0;
        for(int i = 0; i < length_of_length; i++)
            length += buf[shift + (length_of_length - i + 1)] << 8*i; // odczytujemy wartosc z bajtow
        return std::make_pair(length, length_of_length);
    }
}
 void ASNobject:: writeToFile(std::string f_name)
{
    Byte_vect buf;
    serialize(buf);
    buf.writeToFile(f_name);
}

void ASNobject:: readFromFile(std::string f_name)
{
    Byte_vect buf;
    buf.readFromFile(f_name);
    deserialize(buf);
}
