#include "asn_utf8string.hpp"

void ASN_Utf8string:: setLength() {length = utf8string.size(); }
ASN_Utf8string:: ASN_Utf8string() {tag = 0x0C;}
ASN_Utf8string:: ASN_Utf8string (const std::string &string): utf8string(string)
{
    tag = 0x0C;
    isSet = true;
    setLength();
}

ASN_Utf8string:: ASN_Utf8string(const char* utf8c)
{
    tag = 0x0C;
    isSet = true;
    for (int i = 0; utf8c[i] != 0; i++)
        utf8string.push_back(utf8c[i]);
    setLength();
}

ASN_Utf8string:: operator std::string ()  { return utf8string;}

const char& ASN_Utf8string:: operator[] (int i) const
{
    if (i >= utf8string.size())
      throw ("wrong index");
    return utf8string[i];
}

bool ASN_Utf8string:: operator==(const ASN_Utf8string& rhs) const
{
    return (utf8string == rhs.utf8string);
}

void ASN_Utf8string::deserialize(const Byte_vect &buf, int shift)
{
    if (buf[shift] != tag)
      throw(Exception(WRONG_TAG));

    std::pair<int,int> length_shift = deserialize_length(buf,shift);
    length = length_shift.first; // ile bajtów do odczytu
    int off = length_shift.second; // ile bajtów do pominięcia (kodujących długość)
    utf8string.clear();

    for (int i = 0; i < length; i++)
        utf8string.push_back(buf[shift + (i+2) + off]);

    isSet = true;
}
void ASN_Utf8string::serialize(Byte_vect &buf)
{
    if (!isSet)
       throw(Exception(EMPTY_OBJECT));

    serialize_tag_length(buf);

    for (auto it = utf8string.begin(); it != utf8string.end(); it++)
        buf.push_back(*it);

}
