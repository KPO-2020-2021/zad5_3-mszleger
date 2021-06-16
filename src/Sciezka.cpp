#include "Sciezka.hh"

unsigned int Sciezka::iloscUtworzonychObiektow;

std::string Sciezka::generujNazwePliku()
{
  std::string nazwaTmp = "../datasets/tmp_sciezka_";                 // Generowanie unikalnej nazwy pliku dla każdej stworzonej ścieżki
  nazwaTmp += std::to_string(numerSciezki);                          // Dodawanie do nazwy numeru ścieżki
  nazwaTmp += ".dat";
  return nazwaTmp;                                                   // Zwracanie wygenerowanej nazwy pliku
}

Sciezka::Sciezka(PzG::LaczeDoGNUPlota& laczeDoGnuplota): numerSciezki(++iloscUtworzonychObiektow)
{
  if(usunSciezke() == false)                                         // Tworzenie pliku do komunikacji z gnuplotem
    throw(501);                                                      // Zwracanie wyjątku jeśli nie udało się utworzyć pliku
  laczeDoGnuplota.DodajNazwePliku(generujNazwePliku().c_str());      // Dodawanie nazwy pliku do komunikacji z gnuplotem do łącza do gnuplota
}

bool Sciezka::dodajWektor(const Wektor3D& polozenieGlobalneDrona, const Wektor3D& wektor)
{
  if(wektor.modul() == 0) return false;                              // Zwracanie false jeśli moduł wektora jest równy 0
  if(sciezka.size() == 0) poczatek = polozenieGlobalneDrona;         // Jeśli lista z elementami ścieżki jest pusta to ustawiany jest wektor początku ścieżki
  sciezka.push_back(wektor);                                         // Dodawanie wektora do listy przechowywującej wektory ścieżki
  zapiszDoPliku();                                                   // Aktualizowanie danych w pliku do komunikacji z gnuplotem
  return true;                                                       // Zwracanie true
}

bool Sciezka::dodajRuch(const Wektor3D& polozenieGlobalneDrona, const Ruch& ruch)
{
  Wektor3D wektorRuchu;                                              // Tworzenie wersora w równoległego do osi OX
  wektorRuchu[0] = 1;
  wektorRuchu = generujMacierzObrotu(ruch.katObrotu, OZ) * wektorRuchu * ruch.odleglosc; // Tworzenie wektora odpowiadającego przemieszczeniu zapisanemu w zmiennej ruch
  return dodajWektor(polozenieGlobalneDrona, wektorRuchu);           // Wywoływanie metody dodajWektor z wyznaczonym wektorem jako parametr
}

bool Sciezka::zapiszDoPliku()
{
  std::fstream plik;                                                 // Tworzenie uchwytu do pliku
  Wektor3D wektorTmp = poczatek;                                     // Tworzenie wektora przechowywującego współrzędne aktualnie dodawanego do pliku punktu ścieżki 
  plik.open(generujNazwePliku(), std::fstream::out);                 // Otwieranie pliku w trybie do zapisu
  if(plik.is_open() == false) return false;                          // Zwracanie false jeśli nie udało się otworzyć pliku
  for(Wektor3D& wektor: sciezka)
  {
    plik << wektorTmp << std::endl;                                  // Zapisywanie współrzędnych początku odcinka
    wektorTmp += wektor;                                             // Przesówanie wskazywanego punktu o wektor z listy
    plik << wektorTmp << std::endl;                                  // Zapisywanie współrzędnych końca odcinka
    plik << std::endl << std::endl;                                  // Wstawianie dwóch wolnych linii oddzielających odcinek
  }
  if(plik.fail()) {plik.close(); return false;}                      // Zamykanie pliku i zwracanie false jeśli wystąpił błąd zapisu
  plik.close();                                                      // Zamykanie pliku
  return true;                                                       // Zwracanie true
}

bool Sciezka::usunSciezke()
{
  std::fstream plik;                                                 // Tworzenie uchwytu do pliku
  plik.open(generujNazwePliku(), std::fstream::out);                 // Otwieranie pliku w trybie do zapisu
  if(plik.is_open() == false) return false;                          // Zwracanie false jeśli nie udało się otworzyć pliku
  plik.close();                                                      // Zamykanie pliku
  poczatek = Wektor3D();                                             // Ustawianie wektora zerowego jako początek ścieżki
  sciezka.clear();                                                   // Usuwanie wektorów ścieżki z listy
  return true;                                                       // Zwracanie true
}
