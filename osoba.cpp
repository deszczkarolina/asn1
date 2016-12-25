#include "osoba.hpp"

Osoba:: Osoba()
{
    plec = {"kobieta", "mezczyzna"};
    asn_object_p = {&imie, &nazwisko, &wiek, &plec, &zainteresowania};
}

Osoba:: Osoba(std::string name, std::string surname, int age, bool gender, ASN_Bitstring interest): imie(name), nazwisko(surname), wiek(age)
{
    zainteresowania = interest;
    plec = {"kobieta", "mezczyzna"};
    plec = gender;
    asn_object_p = {&imie, &nazwisko, &wiek, &plec, &zainteresowania};
}

void Osoba:: display()
{
    std::cout << "Imię: " << (std::string)imie << std::endl;
    std::cout << "Nazwisko: " << (std::string)nazwisko << std::endl;
    std::cout << "Wiek: "  << wiek << std::endl;
    std::cout << "Płeć: ";
    if (plec == 0)
       std::cout << "kobieta";
    else
       std::cout << "mężczyzna";

    std::cout << std::endl;
    std::cout << "Zainteresowania: ";
    if (zainteresowania[0])   std::cout << "narty, ";
    if (zainteresowania[1])  std::cout << "łyżwy, ";
    if (zainteresowania[2])  std::cout << "książki, ";
    if (zainteresowania[3])  std::cout << "pływanie, ";
    std::cout << std::endl;

}



