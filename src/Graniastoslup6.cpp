#include "Graniastoslup6.hh"

bool Graniastoslup6::wczytajBryleWzorcowa()
{
  std::fstream plik;                             // Tworzenie uchwytu do pliku
  Wektor3D wektor;
  Sciana sciany[18];
  sciany[ 0].ustaw(0, 6, 1, 6);
  sciany[ 1].ustaw(1, 6, 2, 6);
  sciany[ 2].ustaw(2, 6, 3, 6);
  sciany[ 3].ustaw(3, 6, 4, 6);
  sciany[ 4].ustaw(4, 6, 5, 6);
  sciany[ 5].ustaw(5, 6, 0, 6);
  sciany[ 6].ustaw(7, 13, 8, 13);
  sciany[ 7].ustaw(8, 13, 9, 13);
  sciany[ 8].ustaw(9, 13, 10, 13);
  sciany[ 9].ustaw(10, 13, 11, 13);
  sciany[10].ustaw(11, 13, 12, 13);
  sciany[11].ustaw(12, 13, 7, 13);
  sciany[12].ustaw(0, 1, 7, 8);
  sciany[13].ustaw(1, 2, 8, 9);
  sciany[14].ustaw(2, 3, 9, 10);
  sciany[15].ustaw(3, 4, 10, 11);
  sciany[16].ustaw(4, 5, 11, 12);
  sciany[17].ustaw(5, 0, 12, 7);
  this->czyPoprawnieWczytany = false;            // Resetowanie flagi wskazującej czy udało się poprawnie wczytać obiekt
  plik.open(this->nazwaPliku_BrylaWzorcowa);     // Otwieranie pliku
  if(plik.is_open() == false)                    // Sprawdzanie czy udało się otworzyć plik - zwracanie false jeśli nie
    return false;
  for(unsigned int x = 0; x < 14; ++x)           // Wczytywanie współrzędnych wierzchołków
  {
    plik >> wektor;                              // Wczytywanie wektora
    if(plik.fail())                              // Sprawdzenie czy wystąpił błąd - jeśli tak plik jest zamykany, a funkcja zwraca false
    {
      plik.close();
      return false;
    }
    this->wierzcholki.push_back(wektor);         // Zapisywanie wektorów
  }
  for(unsigned int x = 0; x < 18; ++x)           // Zapisanie konfiguracji wierzchołków w ścianach
    this->sciany.push_back(sciany[x]);
  this->czyPoprawnieWczytany = true;             // Ustawianie flagi poprawnego wczytania na true
  plik.close();                                  // Zamykanie pliku
  return true;                                   // Zwracanie true
}

void Graniastoslup6::wyswietlNazwe() const
{
  std::cout << "Graniastosłup 6";
}

void Graniastoslup6::deformuj()
{

}