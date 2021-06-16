#ifndef WEKTOR_HH
#define WEKTOR_HH

#include <iostream>
#include <iomanip>
#include <cmath>

/**
 * \brief Parametr ustawiający dokładność porównywania ze sobą dwóch wektorów.
 * 
 * Parametr określa numer miejsca po przecinku, do którego porównywane będą wartości przechowywane przez wektory.
 * Przykład dla wektora trójwymiarowego dla wartości parametru ustawionej na 3:
 * Wektor1: [1.0011, 1.001, 1.001]
 * Wektor2: [1.0012, 1.001, 1.001]
 * Operacja Wektor1 == Wektor2 zwróci wartość true, ponieważ wartości różnią się dopiero na 4 miejsu po przecinku.
 * 
 * Wartości przed porównaniem są zaokrąglane do danego miejsca po przecinku.
 * Przykład dla wektora trójwymiarowego dla wartości parametru ustawionej na 3:
 * Wektor1: [1.0011, 1.001, 1.001]
 * Wektor2: [1.0016, 1.001, 1.001]
 * Operacja Wektor1 == Wektor2 zwróci wartość false, ponieważ po zaokrągleniu otrzymamy nierówne sobie wartości:
 * Wektor1: [1.001, 1.001, 1.001]
 * Wektor2: [1.002, 1.001, 1.001]
 */
#define PRECYZJA_WEKTOR 10

/**
 * \brief Klasa modelująca wektor o zadanym rozmiarze i zadanym typie przechowywanych wartości.
 * 
 * Parametrami szablonu są <rozmiar wektora, typ wartości>, gdzie:
 * -rozmiar wektora oznacza ilość wartości przechowywanych przez dany wektor (np. dla wektora w przestrzenia 2D wartość 2),
 * -typ wartości oznacza typ zmiennych, które mają być przechowywane przez dany wektor (np. double dla liczb zmiennoprzecinkowych).
 * 
 * Kody wyjątków rzucanych przez klasę:
 * 100 - jako argument operatora indeksującego podano wartość wykraczającą poza zakres [0, rozmiar wektora - 1],
 */
template <unsigned int rozmiar_wektora, class typ_wartosci>
class Wektor {
  private:

    /**
     * Tablica przechowywująca wartości wektora.
     */
    typ_wartosci wartosci[rozmiar_wektora];
  
  public:

    /**
     * Zmienna przechowywująca ilość stworzonych obiektów typu Wektor
     */
//    static int iloscStworzonych;

    /**
     * Zmienna przechowywująca ilość obecnie istniejących obiektów typu Wektor
     */
//    static int iloscIstniejacych;

    /**
     * \brief Konstruktor bezarguemtowy
     * 
     * Konstruktor ustawiający wszystkie przechowywane przez wektor wartości na 0.
     */
    Wektor()
    {
//      iloscIstniejacych += 1;                        // Zliczanie nowo stworzonego obiektu
//      iloscStworzonych += 1;
      for(typ_wartosci &wartosc : wartosci)                // Ustawianie wszystkich wartości przechowywanych przez wektor na 0
        wartosc = 0;
    }

    /**
     * \brief Konstruktor parametryczny
     * 
     * Konstruktor ustawiający wartości wektora wartościami podanymi w tablicy jako argument.
     */
    Wektor(typ_wartosci wartosciPoczatkowe[rozmiar_wektora])
    {
//      iloscIstniejacych += 1;                        // Zliczanie nowo stworzonego obiektu
//      iloscStworzonych += 1;
      for(unsigned int numerWartosci = 0; numerWartosci < rozmiar_wektora; ++numerWartosci)
        wartosci[numerWartosci] = wartosciPoczatkowe[numerWartosci];
    }

    /**
     * \brief Konstruktor kopiujący
     */
    Wektor(const Wektor <rozmiar_wektora, typ_wartosci> &wektor)
    {
//      iloscIstniejacych += 1;                        // Zliczanie nowo stworzonego obiektu
//      iloscStworzonych += 1;
      for(unsigned int x = 0; x < rozmiar_wektora; ++x)
        this->wartosci[x] = wektor.wartosci[x];
    }

    /**
     * \brief Destruktor klasy Wektor
     */
    ~Wektor()
    {
//      iloscIstniejacych -= 1;
    }

    /**
     * \brief Metoda ustawiająca wartości wektora
     * 
     * Metoda ustawiająca wartości wektora wartościami podanymi w tablicy jako argument.
     */
    void ustaw(typ_wartosci wartosciPoczatkowe[rozmiar_wektora])
    {
      for(unsigned int numerWartosci = 0; numerWartosci < rozmiar_wektora; ++numerWartosci)
        wartosci[numerWartosci] = wartosciPoczatkowe[numerWartosci];
    }

    /**
     * \brief Metoda zwracająca moduł wektora.
     * 
     * Metoda oblicza sumę kwadratów wartości wektora i zwraca pierwiastek kwadratowy tej wartości.
     */
    double modul() const
    {
      double modul2 = 0;                                   // Zmienna pomocnicza przechowywująca sumę kwadratów wartości wektora
      for(const typ_wartosci &wartosc : wartosci)                // Sumowanie kwadratów wartości wektora
        modul2 += wartosc * wartosc;
      return sqrt(modul2);                                 // Zwracanie pierwiastka kwadratowego z sumy kwadratów wartości wektora
    }

    /**
     * \brief Przeciążenie operatora indeksującego do odczytu wartości wektora o danym indeksie
     * 
     * Jeśli jako argument operatora indeksującego podano wartość większą lub równą od wielkości wektora, to metoda rzuca wyjątkiem o kodie 100.
     */
    typ_wartosci  operator [] (unsigned int indeks) const
    {
      if(indeks >= rozmiar_wektora)                        // Sprawdzanie czy wartość indeksu nie wychodzi poza dopuszczalny zakres
        throw(100);                                        // Rzucanie wyjątkiem o kodzie 100 jeśli wartość indeksu jest nieprawidłowa
      return wartosci[indeks];                             // Zwracanie wartości wektora o danym indeksie
    }

    /**
     * \brief Przeciążenie operatora indeksującego do zapisu nowej wartości wektora o danym indeksie
     * 
     * Jeśli jako argument operatora indeksującego podano wartość większą lub równą od wielkości wektora, to metoda rzuca wyjątkiem o kodie 100.
     */
    typ_wartosci& operator [] (unsigned int indeks)
    {
      if(indeks >= rozmiar_wektora)                        // Sprawdzanie czy wartość indeksu nie wychodzi poza dopuszczalny zakres
        throw(100);                                        // Rzucanie wyjątkiem o kodzie 100 jeśli wartość indeksu jest nieprawidłowa
      return wartosci[indeks];                             // Zwracanie rekurencji na wartość wektora o danym indeksie
    }

    /**
     * \brief Przeciążenie operatora dodającego do siebie dwa wektory
     * 
     * Operator dodaje do siebie wartości o tym samym indeksie obu wektorów i zwraca strukturę z otrzymanymi wartościami.
     */
    Wektor <rozmiar_wektora, typ_wartosci> operator + (const Wektor <rozmiar_wektora, typ_wartosci> &wektor2) const
    {
      Wektor <rozmiar_wektora, typ_wartosci> wynik;        // Zmienna pomocnicza przechowywująca wynik operacji dodawania dwóch wektorów
      for(unsigned int x = 0; x < rozmiar_wektora; x++)             // Dodawanie do siebie wartości o tym samym indeksie obu wektorów i zapisywanie wyniku w zmiennej pomocniczej
        wynik[x] = this->wartosci[x] + wektor2[x];
      return wynik;                                        // Zwracanie wyniku operacji dodawania
    }

    /**
     * \brief Przeciążenie operatora dodającego do siebie dwa wektory i przypisującego wynik do pierwszego z nich
     * 
     * Operator dodaje do siebie wartości o tym samym indeksie obu wektorów i zwraca strukturę z otrzymanymi wartościami.
     * Operator przypisuje wynik operacji do pierwszego z wektorów.
     */
    Wektor <rozmiar_wektora, typ_wartosci>& operator += (const Wektor <rozmiar_wektora, typ_wartosci> &wektor2)
    {
      *this = *this + wektor2;
      return *this;
    }

    /**
     * \brief Przeciążenie operatora odejmującego od siebie dwa wektory
     * 
     * Operator odejmuje wektor drugi (z prawej strony) od pierwszego wektora (z lewej strony).
     * Operator odejmuje do siebie wartości o tym samym indeksie obu wektorów i zwraca strukturę z otrzymanymi wartościami.
     */
    Wektor <rozmiar_wektora, typ_wartosci> operator - (const Wektor <rozmiar_wektora, typ_wartosci> &wektor2) const
    {
      Wektor <rozmiar_wektora, typ_wartosci> wynik;        // Zmienna pomocnicza przechowywująca wynik operacji odejmowania dwóch wektorów
      for(unsigned int x = 0; x < rozmiar_wektora; x++)             // Odejmowanie od siebie wartości o tym samym indeksie obu wektorów i zapisywanie wyniku w zmiennej pomocniczej
        wynik[x] = this->wartosci[x] - wektor2[x];
      return wynik;                                        // Zwracanie wyniku operacji odejmowania
    }

    /**
     * \brief Przeciążenie operatora mnożenia wektora razy skalar
     */
    Wektor <rozmiar_wektora, typ_wartosci> operator * (const double skladnik) const
    {
      Wektor <rozmiar_wektora, typ_wartosci> wynik;
      for(unsigned int x = 0; x < rozmiar_wektora; ++x)
        wynik[x] = this->wartosci[x] * skladnik;
      return wynik;
    }

    /**
     * \brief Przeciążenie operatora porównującego ze sobą dwa wektory
     * 
     * Jeśli wszystkie wartości obu wektorów są sobie parami równe zwracana jest wartość true, w przeciwnym razie zwracana jest wartość false.
     * Dokładny sposób działania porównywania z zadaną dokładkością został opisany w opisie zmiennej pozornej "PRECYZJA_WEKTOR".
     */
    bool operator == (const Wektor <rozmiar_wektora, typ_wartosci> &wektor2) const
    {
      for(unsigned int x = 0; x < rozmiar_wektora; x++)             // Porównywanie ze sobą wszystkich par zaokrąglonych wartości obu wektorów
        if(round(this->wartosci[x] * pow(10, PRECYZJA_WEKTOR)) != round(wektor2.wartosci[x] * pow(10, PRECYZJA_WEKTOR)))
          return false;                                    // Zwracanie false, jeśli dana para zaokrąglonych liczb nie jest sobie równa
      return true;                                         // Zwracanie true, jeśli wszystkie wartości są parami równe
    }

    /**
     * \brief Przeciążenie zanegowanego operatora porównującego ze sobą dwa wektory
     * 
     * Jeśli wszystkie wartości obu wektorów są sobie parami równe zwracana jest wartość false, w przeciwnym razie zwracana jest wartość true.
     * Dokładny sposób działania porównywania z zadaną dokładkością został opisany w opisie zmiennej pozornej "PRECYZJA_WEKTOR".
     */
    bool operator != (const Wektor <rozmiar_wektora, typ_wartosci> &wektor2) const
    {
      return !(*this == wektor2);                          // Zwracanie zanegowanego wyniku operatora porównywania danych wektorów
    }
};

/**
 * \brief Przeciążenie operatora wczytującego wektor ze strumienia
 * 
 * Parametrami szablonu są <rozmiar wektora, typ wartości>, gdzie:
 * -rozmiar wektora oznacza ilość wartości przechowywanych przez dany wektor (np. dla wektora w przestrzenia 2D wartość 2),
 * -typ wartości oznacza typ zmiennych, które mają być przechowywane przez dany wektor (np. double dla liczb zmiennoprzecinkowych).
 */
template <unsigned int rozmiar_wektora, class typ_wartosci>
std::istream& operator >> (std::istream &Strm, Wektor <rozmiar_wektora, typ_wartosci> &Wek)
{
  for(unsigned int x = 0; x < rozmiar_wektora; x++)                 // Pobieranie kolejnych wartości wektora
    Strm >> Wek[x];
  return Strm;                                             // Zwracanie rekurencji na strumień
}

/**
 * \brief Przeciążenie operatora wypisującego wektor do strumienia
 * 
 * Parametrami szablonu są <rozmiar wektora, typ wartości>, gdzie:
 * -rozmiar wektora oznacza ilość wartości przechowywanych przez dany wektor (np. dla wektora w przestrzenia 2D wartość 2),
 * -typ wartości oznacza typ zmiennych, które mają być przechowywane przez dany wektor (np. double dla liczb zmiennoprzecinkowych).
 * Funkcja ustawia dokładność wyświetlania liczb zmiennoprzecinkowych na 10 miejsc po przecinku.
 * Funkcja ustawia stałą szerokość wyświetlania liczb na 15 znaków szerokości.
 */
template <unsigned int rozmiar_wektora, class typ_wartosci>
std::ostream& operator << (std::ostream &Strm, const Wektor <rozmiar_wektora, typ_wartosci> &Wek)
{
  for(unsigned int x = 0; x < rozmiar_wektora; x++)                 // Wypisywanie kolejnych wartości wektora
    Strm << " " << std::setw(15) << std::fixed << std::setprecision(10) << Wek[x];
  return Strm;                                             // Zwracanie rekurencji na strumień
}

#endif
