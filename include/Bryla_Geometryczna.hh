#ifndef BRYLA_GEOMETRYCZNA_HH
#define BRYLA_GEOMETRYCZNA_HH

#include <string>
#include <vector>
#include <fstream>

#include "Wektor3D.hh"
#include "MacierzObrotu.hh"

/**
 * \brief Klasa modelująca ścianę bryły - klasa zawiera numery wierzchołków tworzących daną ścianę
 */
class Sciana {
  public:
    unsigned int wierzcholki[4];
    Sciana() {for(unsigned int &wierzcholek : wierzcholki) wierzcholek = 0;}
    void ustaw(unsigned int x1, unsigned int x2, unsigned int x3, unsigned int x4);
};

/**
 * \brief Klasa modelująca bryłę geometryczną o dowolnym kształcie
 */
class Bryla_Geometryczna {
  protected:
    /**
    * \brief Flaga przechowująca informację o tym czy udało się prawidłowo wczytać figurę z pliku
    */
    bool czyPoprawnieWczytany;

    /**
    * \brief Zmienna przechowująca nazwę pliku, w którym znajdują się dane opisujące wzorcową figurę geometryczną
    */
    std::string nazwaPliku_BrylaWzorcowa;
    /**
    * \brief Zmienna przechowująca nazwę pliku, w którym zapisywany jest opis bryły, wykorzystywany przez gnuplot do rysowania
    */
    std::string nazwaPliku_BrylaFinalna;

    /**
    * \brief Kontener przechowujący wektory opisujące przejście z środka bryły do wierzchołka o danym numerze
    */
    std::vector <Wektor3D> wierzcholki;
    /**
    * \brief Kontener przechowujący opis łączenia wierzchołków w celu tworzenia poszczególnych ścian
    * 
    * Kontener przechowuje tablice cztero-elementowe przechowujące numery wierzchołków tworzących daną ścianę.
    * Numery wierzchołków należy podawać w następującej kolejności:
    * 
    * [2] - - - [3]
    *  |         |
    *  |         |
    * [0] - - - [1]
    * 
    */
    std::vector <Sciana> sciany;

    /**
    * \brief Zmienna typu macierz obrotu przechowująca macierz obrotu bryły wokół jej lokalnego układu współrzędnych
    */
    MacierzObrotu obrotWzgledemLokalnegoUkladu;

    /**
    * \brief Zmienna typu wektor3D przechowująca wektor przesunięcia lokalnego układu współrzędnych bryły względem lokalnego układu współrzędnych jej rodzica
    */
    Wektor3D przesuniecieWzgledemUkladuRodzica;
  public:
    /**
     * \brief Konstruktor bezparametryczny inicjujący wartości macierzy obrotu jako macierze jednostkowe oraz flagi czyPoprawnieWczytany
     */
    Bryla_Geometryczna();

    /**
     * \brief Konstruktor parametryczny wykonujący te operacje co konstruktor bezparametryczny i ustawiający nazwy plików z bryłą wzorcową i z danymi dla gnuplota
     */
    Bryla_Geometryczna(const std::string &nazwaPlikuBrylaWzorcowa, const std::string &nazwaPlikuBrylaFinalna);

    /**
     * \brief Metoda ustawiająca wartość zmiennej przechowującej nazwę pliku wykorzystywanego przez gnuplota do rysowania bryły
     * 
     * Przed zmianą wartości metoda sprawdza czy jest w stanie otworzyć plik o danej nazwie.
     */
    bool ustawNazwePlikuBrylaWzorcowa(const std::string &nowaNazwa);

    /**
     * \brief Metoda zwracająca wartość zmiennej przechowującej nazwę pliku przechowującego opis bryły wzorcowej
     */
    const std::string& zwrocNazwePlikuBrylaWzorcowa();

    /**
     * \brief Metoda ustawiająca wartość zmiennej przechowującej nazwę pliku wykorzystywanego przez gnuplota do rysowania bryły
     * 
     * Przed zmianą wartości metoda sprawdza czy jest w stanie zmodyfikować plik o danej nazwie.
     */
    bool ustawNazwePlikuBrylaFinalna(const std::string &nowaNazwa);

    /**
     * \brief Metoda zwracająca wartość zmiennej przechowującej nazwę pliku wykorzystywanego przez gnuplota do rysowania bryły
     */
    const std::string& zwrocNazwePlikuBrylaFinalna();

    /**
     * \brief Metoda wczytująca z pliku wzorcową bryłę geometryczną
     * 
     * Sposób zapisu brył geometrycznych w pliku:
     * W 'wektor 0'
     * W 'wektor 1'
     * .
     * .
     * .
     * K
     * S 'opis sciany 0'
     * S 'opis sciany 1'
     * .
     * .
     * .
     * K
     */
    bool wczytajBryleWzorcowa();

    /**
     * \brief Metoda usuwająca waszystkie dane z pliku wykorzystywanego przez gnuplota do rysowania danej bryły; ukrywa figurę
     */
    bool wyczyscWspolrzedneDoWyswietlenia();

    /**
     * \brief Zapisuje w danym pliku opis bryły wykorzystywany przez gnuplota do narysowania danej bryły
     */
    bool zapiszWspolrzedneDoWyswietlenia(const MacierzObrotu &obrotUkladuRodzicaWzgledemUkladuGlobalnego, const Wektor3D &przesuniecieUkladuRodzicaWzgledemUkladuGlobalnego);

    /**
     * \brief Metoda obracająca środek lokalnego układu współrzędny bryły o daną macierz obrotu
     */
    bool obrocWzgledemLokalnegoUkladu(const MacierzObrotu &macierz);

    /**
     * \brief Metoda zwracająca macierz obrotu lokalnego układu współrzędnych bryły
     */
    const MacierzObrotu& zwrocMacierzObrotuWzgledemLokalnegoUkladu();

    /**
     * \brief Metoda przesuwająca środek lokalnego układu współrzędny bryły o dany wektor względem lokalnego układu współrzędnych jej rodzica
     */
    bool przesunWzgledemUkladuRodzica(const Wektor3D &wektorTranslacji);

    /**
     * \brief Metoda zwracająca wektor translacji lokalnego układu współrzędnych bryły względem lokalnego układu współrzędnych jej rodzica
     */
    const Wektor3D& zwrocWektorTranslacjiWzgledemUkladuRodzica();

    /**
    * \brief Przeciążenie operatora indeksującego zwracającego wektor danego wierzchołka względem układu lokalnego
    */
    Wektor3D operator [] (unsigned int indeks) const {return this->wierzcholki[indeks];}

    /**
     * Metoda skaluje figurę w poszczególnych osiach danymi parametrami
     */
    void skaluj(double skalaOX, double skalaOY, double skalaOZ);

    /**
     * \brief Metoda wirtualna wyświetlająca nazwę danej klasy
     */
    virtual void wyswietlNazwe() const;
    
    /**
     * \brief Metoda wirtualna deformująca w odpowiedni sposób prostopadłościan tak, aby otrzymać rządany obiekt np. górę z ostrym szczytem
     */
    virtual void deformuj();
};

#endif