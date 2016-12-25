#include "asn_enumerated.hpp"

ASN_Enumerated:: ASN_Enumerated() { tag = 0x0A; }

bool ASN_Enumerated:: isCorrect(int value)
{
    for (auto it = value_dict.begin(); it != value_dict.end(); it++)
    {
        if (it->second == value)
        return true;
    }
    return false;
}

 void ASN_Enumerated:: operator=(const std::initializer_list<std::string> il)
{
    int i = 0;
    for (auto it = il.begin(); it != il.end(); it++)
    {
        value_dict.insert({(*it), i});
        i++;
    }
}
void ASN_Enumerated:: operator=(const std::unordered_map<std::string, int> &map)
{
    value_dict = map;
}
void ASN_Enumerated:: operator=(int value)
{
    if (isCorrect(value))
    {
        isSet = true;
        this->value = value;
        setLength();
    }
    else
       throw(Exception(WRONG_ENUM_VALUE));

}
void ASN_Enumerated:: operator=(std::string str)
{
    value = value_dict[str];
    setLength();
}

std::string ASN_Enumerated:: toStr() const
{
    for (auto it = value_dict.begin(); it != value_dict.end(); it++)
    {
        if (it->second == value)
            return it->first;
    }
    throw(Exception(WRONG_ENUM_VALUE));
    return "";
}
ASN_Enumerated::operator std::string() const
{
    return toStr();
}
void ASN_Enumerated::deserialize(const Byte_vect &buf, int shift)
{
   if (buf[shift] != tag) throw(Exception(WRONG_TAG));
   else
   {
       std::pair<int,int> length_shift = deserialize_length(buf,shift);
       length = length_shift.first; // ile bajtów do odczytu
       int off = length_shift.second; // ile bajtów do pominięcia (kodujących długość)

       int tmp_value;

       tmp_value = 0;
       for(int i = 0; i < length; i++)
       {
           tmp_value += buf[shift + (length - i + 1) + off] << 8*i; // zaczynamy od najmłodszego bajtu, kończymy na najstarszym
       }

       if (isCorrect(tmp_value)) // sprawdzamy czy jest w mapie
            value = tmp_value;

       else
          throw(Exception(WRONG_ENUM_VALUE));
   }

   isSet = true;
}
