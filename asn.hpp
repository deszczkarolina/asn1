#ifndef asn_h
#define asn_h

#include "types.hpp"

/// \brief klasa ASNobject
class ASNobject: public IStorable
{
    protected:
        BYTE tag;
        int length;
        /// informacja czy obiekt ma ustawioną wartość
        bool isSet = false;

	public:
        /// zwraca całkowity rozmiar obiektu w bajtach po serializacji
        int fullSize();
        /// serializacja
		virtual void serialize(Byte_vect &buf) = 0;
        /// deserializacja
		virtual void deserialize(const Byte_vect &buf, int shift = 0) = 0;

        ///  metoda zapisu tagu i długości do bufora
        void serialize_tag_length (Byte_vect &buf);

        /// \brief metoda odczytująca długość zakodowaną jako 1 lub więcej bajtów z bufora bajtów
        /// Zwraca parę intów (a,b) gdzie a - odczytana długość b - ile bajtów zajęła długość
        std::pair<int, int> deserialize_length(const Byte_vect& buf, int shift = 0);

        /// zapis do pliku
        void writeToFile(std::string f_name);
        /// odczyt z pliku
        void readFromFile(std::string f_name);

};
#endif // asn_h
