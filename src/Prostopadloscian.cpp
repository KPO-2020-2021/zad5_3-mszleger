#include "Prostopadloscian.hh"

bool Prostopadloscian::wczytajBryleWzorcowa()
{
  std::fstream plik;                             // Tworzenie uchwytu do pliku
  Wektor3D wektor;
  Sciana sciany[6];
  sciany[0].ustaw(0, 1, 2, 3);
  sciany[1].ustaw(2, 3, 4, 5);
  sciany[2].ustaw(4, 5, 6, 7);
  sciany[3].ustaw(6, 7, 0, 1);
  sciany[4].ustaw(1, 3, 7, 5);
  sciany[5].ustaw(0, 2, 6, 4);
  this->czyPoprawnieWczytany = false;            // Resetowanie flagi wskazującej czy udało się poprawnie wczytać obiekt
  plik.open(this->nazwaPliku_BrylaWzorcowa);     // Otwieranie pliku
  if(plik.is_open() == false)                    // Sprawdzanie czy udało się otworzyć plik - zwracanie false jeśli nie
    return false;
  for(unsigned int x = 0; x < 8; ++x)            // Wczytywanie współrzędnych wierzchołków
  {
    plik >> wektor;                              // Wczytywanie wektora
    if(plik.fail())                              // Sprawdzenie czy wystąpił błąd - jeśli tak plik jest zamykany, a funkcja zwraca false
    {
      plik.close();
      return false;
    }
    this->wierzcholki.push_back(wektor);         // Zapisywanie wektorów
  }
  for(unsigned int x = 0; x < 6; ++x)            // Zapisanie konfiguracji wierzchołków w ścianach
    this->sciany.push_back(sciany[x]);
  this->czyPoprawnieWczytany = true;             // Ustawianie flagi poprawnego wczytania na true
  plik.close();                                  // Zamykanie pliku
  return true;                                   // Zwracanie true
}

void Prostopadloscian::wyswietlNazwe() const
{
  std::cout << "Prostopadłościan";
}

void Prostopadloscian::deformuj()
{

}