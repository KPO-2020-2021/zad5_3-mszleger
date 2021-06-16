#include "Bryla_Geometryczna.hh"

void Sciana::ustaw(unsigned int x1, unsigned int x2, unsigned int x3, unsigned int x4)
{
  wierzcholki[0] = x1;
  wierzcholki[1] = x2;
  wierzcholki[2] = x3;
  wierzcholki[3] = x4;
}

Bryla_Geometryczna::Bryla_Geometryczna()
{
  czyPoprawnieWczytany = false;
  double macierzJednostkowa[] = {1, 0, 0, 0, 1, 0, 0, 0, 1};
  (this->obrotWzgledemLokalnegoUkladu).ustaw(macierzJednostkowa);
}

Bryla_Geometryczna::Bryla_Geometryczna(const std::string &nazwaPlikuBrylaWzorcowa, const std::string &nazwaPlikuBrylaFinalna)
{
  czyPoprawnieWczytany = false;
  double macierzJednostkowa[] = {1, 0, 0, 0, 1, 0, 0, 0, 1};
  (this->obrotWzgledemLokalnegoUkladu).ustaw(macierzJednostkowa);
  this->ustawNazwePlikuBrylaWzorcowa(nazwaPlikuBrylaWzorcowa);
  this->ustawNazwePlikuBrylaWzorcowa(nazwaPlikuBrylaFinalna);
}

bool Bryla_Geometryczna::ustawNazwePlikuBrylaWzorcowa(const std::string &nowaNazwa)
{
  std::fstream plik;                             // Tworzenie uchwytu do pliku
  plik.open(nowaNazwa);                          // Otwieranie pliku
  if(plik.is_open() == false)                    // Sprawdzanie czy udało się otworzyć plik - zwracanie false jeśli nie
    return false;
  plik.close();                                  // Zamykanie pliku
  this->nazwaPliku_BrylaWzorcowa = nowaNazwa;    // Zmienianie przechowywanej w strukturze nazwy pliku przechowującej bryłę wzorcową
  return true;                                   // Zwracanie true
}

const std::string& Bryla_Geometryczna::zwrocNazwePlikuBrylaWzorcowa()
{
  return nazwaPliku_BrylaWzorcowa;
}

bool Bryla_Geometryczna::ustawNazwePlikuBrylaFinalna(const std::string &nowaNazwa)
{
  std::fstream plik;                             // Tworzenie uchwytu do pliku
  plik.open(nowaNazwa, std::fstream::out);       // Otwieranie pliku
  if(plik.is_open() == false)                    // Sprawdzanie czy udało się otworzyć plik - zwracanie false jeśli nie
    return false;
  plik.close();                                  // Zamykanie pliku
  this->nazwaPliku_BrylaFinalna = nowaNazwa;     // Zmienianie przechowywanej w strukturze nazwy pliku przechowującej bryłę wzorcową
  return true;                                   // Zwracanie true
}

const std::string& Bryla_Geometryczna::zwrocNazwePlikuBrylaFinalna()
{
  return nazwaPliku_BrylaFinalna;
}

bool Bryla_Geometryczna::wczytajBryleWzorcowa()
{
  std::fstream plik;                             // Tworzenie uchwytu do pliku
  char znak;
  Wektor3D wektor;
  Sciana sciana;
  this->czyPoprawnieWczytany = false;            // Resetowanie flagi wskazującej czy udało się poprawnie wczytać obiekt
  plik.open(this->nazwaPliku_BrylaWzorcowa);     // Otwieranie pliku
  if(plik.is_open() == false)                    // Sprawdzanie czy udało się otworzyć plik - zwracanie false jeśli nie
    return false;
  while(true)                                    // Wczytywanie współrzędnych wierzchołków
  {
    plik >> znak;
    if(plik.fail())                              // Sprawdzenie czy wystąpił błąd - jeśli tak plik jest zamykany, a funkcja zwraca false
    {
      plik.close();
      return false;
    }
    if(znak != 'W')                              // Kończenie wczytywania wierzchołków jeśli kod jest inny od 'W'
    {
      if(znak == 'K')                            // Sprawdzanie czy poprawnie oznaczono koniec wprowadzania wierzchołków
        break;
      else                                       // Jeśli nie to plik jest zamykany i zwracana jest wartość false
      {
        plik.close();
        return false;
      }
    }
    plik >> wektor;                              // Wczytywanie wektora
    if(plik.fail())                              // Sprawdzenie czy wystąpił błąd - jeśli tak plik jest zamykany, a funkcja zwraca false
    {
      plik.close();
      return false;
    }
    this->wierzcholki.push_back(wektor);
  }
  while(true)                                    // Wczytywanie konfiguracji scian
  {
    plik >> znak;
    if(plik.fail())                              // Sprawdzenie czy wystąpił błąd - jeśli tak plik jest zamykany, a funkcja zwraca false
    {
      plik.close();
      return false;
    }
    if(znak != 'S')                              // Kończenie wczytywania wierzchołków jeśli kod jest inny od 'W'
    {
      if(znak == 'K')                            // Sprawdzanie czy poprawnie oznaczono koniec wprowadzania wierzchołków
        break;
      else                                       // Jeśli nie to plik jest zamykany i zwracana jest wartość false
      {
        plik.close();
        return false;
      }
    }
    for(unsigned int x = 0; x < 4; ++x)          // Wczytywanie wszystkich 4 wartości reprezentujących wierzchołki danej ściany
    {
      plik >> sciana.wierzcholki[x];             // Wczytywanie numeru wierzchołka
      if(plik.fail())                            // Sprawdzenie czy wystąpił błąd - jeśli tak plik jest zamykany, a funkcja zwraca false
      {
        plik.close();
        return false;
      }
      if(sciana.wierzcholki[x] >= this->wierzcholki.size())  // Sprawdzanie czy wprowadzono numer wierzchołka odpowiadającego wczytanemu wierzchołkowi
      {
        plik.close();
        return false;
      }
    }
    this->sciany.push_back(sciana);
  }
  this->czyPoprawnieWczytany = true;             // Ustawianie flagi poprawnego wczytania na true
  plik.close();                                  // Zamykanie pliku
  return true;                                   // Zwracanie true
}

bool Bryla_Geometryczna::wyczyscWspolrzedneDoWyswietlenia()
{
  std::fstream plik;                                                 // Tworzenie uchwytu do pliku
  plik.open(this->nazwaPliku_BrylaFinalna, std::fstream::out);       // Otwieranie pliku
  if(plik.is_open() == false)                                        // Sprawdzanie czy udało się otworzyć plik - zwracanie false jeśli nie
    return false;
  plik.close();                                                      // Zamykanie pliku
  return true;                                                       // Zwracanie true
}

bool Bryla_Geometryczna::zapiszWspolrzedneDoWyswietlenia(const MacierzObrotu &obrotUkladuRodzicaWzgledemUkladuGlobalnego, const Wektor3D &przesuniecieUkladuRodzicaWzgledemUkladuGlobalnego)
{
  if(czyPoprawnieWczytany == false)                                  // Zwracanie false jeśli spróbowano wyświetlić obiekt nieprawidłowo wczytany
    return false;
  std::fstream plik;                                                 // Tworzenie uchwytu do pliku
  plik.open(this->nazwaPliku_BrylaFinalna, std::fstream::out);       // Otwieranie pliku
  if(plik.is_open() == false)                                        // Sprawdzanie czy udało się otworzyć plik - zwracanie false jeśli nie
    return false;
  for(unsigned int numerSciany = 0; numerSciany < this->sciany.size(); ++numerSciany)    // Przechodzenie pomiędzy ścianami
  {
    for(unsigned int numerWierzcholka = 0; numerWierzcholka < 4; ++numerWierzcholka)     // Przechodzenie pomiędzy wierzchołkami danej ściany
    {                                                                // Zapisywanie współrzędnych danego wierzchołka względem układu globalnego
      plik << obrotUkladuRodzicaWzgledemUkladuGlobalnego * ((this->obrotWzgledemLokalnegoUkladu * this->wierzcholki[this->sciany[numerSciany].wierzcholki[numerWierzcholka]]) + this->przesuniecieWzgledemUkladuRodzica) + przesuniecieUkladuRodzicaWzgledemUkladuGlobalnego << std::endl;
      if(numerWierzcholka == 1)                                      // Wstawianie znaku nowej linii pomiędzy opisem dwóch krawędzi ściany
        plik << std::endl;
    }
    plik << std::endl << std::endl;                                  // Wstawianie dwóch nowych linii pomiędzy opisami ścian
  }
  if(plik.fail())                                                    // Sprawdzanie czy wystąpił błąd podczas zapisywania
  {
    plik.close();                                                    // Zamykanie pliku
    return false;                                                    // Zwracanie false
  }
  plik.close();                                                      // Zamykanie pliku
  return true;                                                       // Zwracanie true
}

bool Bryla_Geometryczna::obrocWzgledemLokalnegoUkladu(const MacierzObrotu &macierz)
{
  this->obrotWzgledemLokalnegoUkladu = this->obrotWzgledemLokalnegoUkladu * macierz;
  return true;
}

const MacierzObrotu& Bryla_Geometryczna::zwrocMacierzObrotuWzgledemLokalnegoUkladu()
{
  return this->obrotWzgledemLokalnegoUkladu;
}

bool Bryla_Geometryczna::przesunWzgledemUkladuRodzica(const Wektor3D &wektorTranslacji)
{
  if(wektorTranslacji.modul() == 0)
    return false;
  this->przesuniecieWzgledemUkladuRodzica = this->przesuniecieWzgledemUkladuRodzica + wektorTranslacji;
  return true;
}

const Wektor3D& Bryla_Geometryczna::zwrocWektorTranslacjiWzgledemUkladuRodzica()
{
  return this->przesuniecieWzgledemUkladuRodzica;
}

void Bryla_Geometryczna::skaluj(double skalaOX, double skalaOY, double skalaOZ)
{
  for(Wektor3D &wierzcholek : wierzcholki)
  {
    wierzcholek[0] *= skalaOX;
    wierzcholek[1] *= skalaOY;
    wierzcholek[2] *= skalaOZ;
  }
}

void Bryla_Geometryczna::wyswietlNazwe() const
{
  std::cout << "Bryła geometryczna";
}
    
void Bryla_Geometryczna::deformuj()
{
  
}