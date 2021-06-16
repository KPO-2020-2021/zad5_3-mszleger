#ifndef MACIERZ_HH
#define MACIERZ_HH

#include <iostream>
#include <iomanip>
#include <cmath>
#include "Wektor.hh"

/**
 * \brief Parametr ustawiający dokładność porównywania ze sobą dwóch macierzy.
 * 
 * Parametr określa numer miejsca po przecinku, do którego porównywane będą wartości przechowywane przez macierze.
 * Przykład dla macierzy 2x2 dla wartości parametru ustawionej na 3:
 * Macierz1: [1.0011, 1.001, 1.001, 1.001]
 * Macierz2: [1.0012, 1.001, 1.001, 1.001]
 * Operacja Macierz1 == Macierz2 zwróci wartość true, ponieważ wartości różnią się dopiero na 4 miejsu po przecinku.
 * 
 * Wartości przed porównaniem są zaokrąglane do danego miejsca po przecinku.
 * Przykład dla macierzy 2x2 dla wartości parametru ustawionej na 3:
 * Macierz1: [1.0011, 1.001, 1.001, 1.001]
 * Macierz2: [1.0016, 1.001, 1.001, 1.001]
 * Operacja Macierz1 == Macierz2 zwróci wartość false, ponieważ po zaokrągleniu otrzymamy nierówne sobie wartości:
 * Macierz1: [1.001, 1.001, 1.001, 1.001]
 * Macierz2: [1.002, 1.001, 1.001, 1.001]
 */
#define PRECYZJA_MACIERZ 10

/**
 * \brief Klasa modelująca macierz kwadratową o zadanym rozmiarze i zadanym typie przechowywanych wartości.
 * 
 * Parametrami szablonu są <rozmiar macierzy, typ wartości>, gdzie:
 * -rozmiar macierzy oznacza ilość wierszy i kolumn wartości przechowywanych przez daną macierz (np. dla macierzy 2x2 wartość 2),
 * -typ wartości oznacza typ zmiennych, które mają być przechowywane przez daną macierz (np. double dla liczb zmiennoprzecinkowych).
 * 
 * Kody wyjątków rzucanych przez klasę:
 * 200 - jako argument operatora funkcyjnego podano wartość wykraczającą poza zakres [0, rozmiar macierzy - 1],
 * 201 - na przekątnej macierzy znajduje się wartość 0; nie można obliczyć wartości wyznacznika macierzy,
 */
template <unsigned int rozmiar_macierzy, class typ_wartosci>
class Macierz {
  private:

    /**
     * Tablica przechowywująca wartości macierzy, w przyjętej konwencji: [kolumna][wiersz].
     */
    typ_wartosci wartosc[rozmiar_macierzy][rozmiar_macierzy];

  public:

    /**
     * \brief Konstruktor bezarguemtowy
     * 
     * Konstruktor ustawiający wszystkie przechowywane przez macierz wartości na 0.
     */
    Macierz()
    {
      for(unsigned int x = 0; x < rozmiar_macierzy; x++)
        for(unsigned int y = 0; y < rozmiar_macierzy; y++)
          this->wartosc[x][y] = 0;
    }

    /**
     * \brief Konstruktor parametryczny
     * 
     * Konstruktor ustawiający wartości macierzy wartościami podanymi w tablicy jako argument.
     * Elementy w tablicy powinny po koleni odpowiadać każdemu wierszowi macierzy od lewej do prawej.
     */
    Macierz(typ_wartosci wartosciPoczatkowe[rozmiar_macierzy * rozmiar_macierzy])
    {
      for(unsigned int numerWiersza = 0; numerWiersza < rozmiar_macierzy; ++numerWiersza)
        for(unsigned int numerKolumny = 0; numerKolumny < rozmiar_macierzy; ++numerKolumny)
          wartosc[numerKolumny][numerWiersza] = wartosciPoczatkowe[(rozmiar_macierzy*numerWiersza + numerKolumny)];
    }

    /**
     * \brief Metoda ustawiająca wartości macierzy
     * 
     * Metoda ustawiająca wartości macierzy wartościami podanymi w tablicy jako argument.
     * Elementy w tablicy powinny po koleni odpowiadać każdemu wierszowi macierzy od lewej do prawej.
     */
    void ustaw(typ_wartosci wartosciPoczatkowe[rozmiar_macierzy * rozmiar_macierzy])
    {
      for(unsigned int numerWiersza = 0; numerWiersza < rozmiar_macierzy; ++numerWiersza)
        for(unsigned int numerKolumny = 0; numerKolumny < rozmiar_macierzy; ++numerKolumny)
          wartosc[numerKolumny][numerWiersza] = wartosciPoczatkowe[(rozmiar_macierzy*numerWiersza + numerKolumny)];
    }

    /**
     * \brief Metoda zwracająca wartość wyznacznika macierzy.
     * 
     * Metoda oblicza wyznacznik tworząc za pomocą operacji na wierszach macierz górnotrójkątną, a następnie licząc iloczyn wartości na przekątnej macierzy.
     */
    double obliczWyznacznik() const
    {
      Macierz <rozmiar_macierzy, typ_wartosci> kopia = *this;        // Tworzenie kopii macierzy
      double wspolczynnik = 0;                                       // Zmienna pomocnicza przechowująca mnożnik razy który będzie odejmowana wiersz od wiersza
      double wyznacznik = 1;                                         // Zmienna pomocnicza przechowująca wartość wyznacznika poczas obliczania iloczynu
      for(unsigned int x = 0; x < rozmiar_macierzy; x++)             // Tworzenie macierzy górno trójkątnej - Pętla przechodząca przez każdy wiersz
      {
        if(kopia.wartosc[x][x] == 0)                                 // Rzucanie wyjątku o kodzie 201 jeśli na przekątnej macierzy znajduje się liczba 0
          throw(201);
        for(unsigned int y = x+1; y < rozmiar_macierzy; y++)         // Zerowanie wartości poniżej obecnie sprawdzanej wartości na przekątnej
        {
          wspolczynnik = kopia.wartosc[x][y] / kopia.wartosc[x][x];  // Obliczanie współczynnika, z jakim musi zostać odjęty wiersz x od wiersza y
          for(unsigned int z = x; z < rozmiar_macierzy; z++)         // Odjemowanie wiersza x pomnożonego o dany współczynnik od wiersza y
            kopia.wartosc[z][y] -= (kopia.wartosc[z][x] * wspolczynnik);
        }
      }
      for(unsigned int x = 0; x < rozmiar_macierzy; x++)             // Obliczanie iloczynu elementów znajdujących się na przekątnej macierzy
        wyznacznik *= kopia.wartosc[x][x];
      return wyznacznik;                                             // Zwracanie wartości wyznacznika macierzy
    }

    /**
     * \brief Przeciążenie operatora mnożącego macierz razy wektor
     * 
     * Operator mnoży macierz razy wektor i tworzy w ten sposób wektor.
     * Ilość wartości w każdym wektorze, ilość wierszy i kolumn w macierzy są sobie równe.
     */
    Wektor <rozmiar_macierzy, typ_wartosci> operator * (const Wektor <rozmiar_macierzy, typ_wartosci> &wektor) const
    {
      Wektor <rozmiar_macierzy, typ_wartosci> wynik;                 // Wektor przechowujący wyniki obliczeń
      for(unsigned int x = 0; x < rozmiar_macierzy; x++)             // Przewijanie między wartościami wektora wynikowego
        for(unsigned int y = 0; y < rozmiar_macierzy; y++)           // Przewijanie między wartościami wektora początkowego
          wynik[x] += wektor[y] * wartosc[y][x];
      return wynik;                                                  // Zwracanie wyniku obliczeń
    }
    
    /**
     * \brief Przeciążenie operatora mnożącego macierz razy macierz
     * 
     * Operator mnoży macierz razy macierz i tworzy w ten sposób macierz.
     * Ilość wierszy i kolumn w macierzach są sobie równe.
     */
    Macierz operator * (const Macierz <rozmiar_macierzy, typ_wartosci> &macierz) const
    {
      Macierz <rozmiar_macierzy, typ_wartosci> wynik;                  // Macierz przechowująca wyniki obliczeń
      for(unsigned int x = 0; x < rozmiar_macierzy; x++)               // Przewijanie między wierszami pierwszej macierzy
        for(unsigned int y = 0; y < rozmiar_macierzy; y++)             // Przewijanie między kolumny drugiej macierzy
          for(unsigned int z = 0; z < rozmiar_macierzy; z++)           // Przewijanie pomiędzy elementami w wierszu pierwszej macierzy i kolumnie drugiej macierzy                
            wynik.wartosc[y][x] += (this->wartosc[z][x] * macierz.wartosc[y][z]); // Sumowanie poszczególnych iloczynów
      return wynik;                                                    // Zwracanie wyniku obliczeń
    }
    
    /**
     * \brief Przeciążenie operatora funkcyjnego do odczytu wartości macierzy o danych indeksach
     * 
     * Jeśli jako argument operatora funkcyjnego podano wartość większą lub równą od wielkości macierzy, to metoda rzuca wyjątkiem o kodie 200.
     */
    double operator () (unsigned int wiersz, unsigned int kolumna) const
    {
      if((wiersz >= rozmiar_macierzy) || (kolumna >= rozmiar_macierzy))
        throw(200);
      return this->wartosc[wiersz][kolumna];
    }

    /**
     * \brief Przeciążenie operatora funkcyjnego do zapisu wartości macierzy o danych indeksach
     * 
     * Jeśli jako argument operatora funkcyjnego podano wartość większą lub równą od wielkości macierzy, to metoda rzuca wyjątkiem o kodie 200.
     */
    double& operator () (unsigned int wiersz, unsigned int kolumna)
    {
      if((wiersz >= rozmiar_macierzy) || (kolumna >= rozmiar_macierzy))
        throw(200);
      return this->wartosc[wiersz][kolumna];
    }

    /**
     * \brief Przeciążenie operatora porównującego ze sobą dwie macierze
     * 
     * Jeśli wszystkie wartości obu macierzy są sobie parami równe zwracana jest wartość true, w przeciwnym razie zwracana jest wartość false.
     * Dokładny sposób działania porównywania z zadaną dokładkością został opisany w opisie zmiennej pozornej "PRECYZJA_MACIERZ".
     */
    bool operator == (const Macierz <rozmiar_macierzy, typ_wartosci> &macierz) const
    {
      for(unsigned int x = 0; x < rozmiar_macierzy; x++)
          for(unsigned int y = 0; y < rozmiar_macierzy; y++)
              if(round(this->wartosc[x][y] * pow(10, PRECYZJA_MACIERZ)) != round(macierz.wartosc[x][y] * pow(10, PRECYZJA_MACIERZ)))
                  return false;
      return true;
    }

    /**
     * \brief Przeciążenie zanegowanego operatora porównującego ze sobą dwie macierze
     * 
     * Jeśli wszystkie wartości obu macierzy są sobie parami równe zwracana jest wartość false, w przeciwnym razie zwracana jest wartość true.
     * Dokładny sposób działania porównywania z zadaną dokładkością został opisany w opisie zmiennej pozornej "PRECYZJA_MACIERZ".
     */
    bool operator != (const Macierz <rozmiar_macierzy, typ_wartosci> &macierz) const
    {
      return !(*this == macierz);
    }
};

/**
 * \brief Przeciążenie operatora wypisującego macierz do strumienia
 * 
 * Parametrami szablonu są <rozmiar macierzy, typ wartości>, gdzie:
 * -rozmiar macierzy oznacza ilość wierszy i kolumn wartości przechowywanych przez daną macierz (np. dla macierzy 2x2 wartość 2),
 * -typ wartości oznacza typ zmiennych, które mają być przechowywane przez daną macierz (np. double dla liczb zmiennoprzecinkowych).
 * Funkcja ustawia dokładność wyświetlania liczb zmiennoprzecinkowych na 10 miejsc po przecinku.
 * Funkcja ustawia stałą szerokość wyświetlania liczb na 15 znaków szerokości.
 */
template <unsigned int rozmiar_macierzy, class typ_wartosci>
std::ostream& operator << (std::ostream &Strm, const Macierz <rozmiar_macierzy, typ_wartosci> &Mac)
{
  for(unsigned int x = 0; x < rozmiar_macierzy; x++)                 // Przewijanie wierszy macierzy
  {
    for(unsigned int y = 0; y < rozmiar_macierzy; y++)               // Przewijanie kolumn macierzy
      Strm << " " << std::setw(15) << std::fixed << std::setprecision(10) << Mac(y, x); // Wypisywanie danej wartości macierzy
    Strm << std::endl;                                               // Przechodzenie do następnego wiersza
  }
  return Strm;                                                       // Zwracanie strumienia
}

#endif
