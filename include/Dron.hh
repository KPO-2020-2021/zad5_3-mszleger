#ifndef DRON_HH
#define DRON_HH

#include <vector>
#include <fstream>
#include <cmath>
#include <string.h>
#include <memory>

#include "Wektor3D.hh"
#include "MacierzObrotu.hh"
#include "Bryla_Geometryczna.hh"
#include "Prostopadloscian.hh"
#include "Graniastoslup6.hh"
#include "Ruch.hh"
#include "lacze_do_gnuplota.hh"
#include "Sciezka.hh"

/**
 * Rzuca wyjątkiem nr. 1 jeśli nie uda się wczytać brył tworzących dron
 */

class Dron : public Bryla_Geometryczna {
  private:
    /**
     * \brief Zmienna przechowywująca korpus drona
     */
    Prostopadloscian korpus;

    /**
     * \brief Tablica przechowywująca cztery rotory drona
     */
    Graniastoslup6 rotory[4];

    /**
     * \brief Wskaźnik na obiekt rysujący planowaną ścieżkę przelotu drona
     */
    Sciezka* sciezka;

    /**
     * Zmienna przechowywująca obrót drona wokół osi OZ
     */
    double obrotLokalny;
    
    /**
     * \brief Lista przechowywująca zaplanowane ruchy drona
     */
    std::list <Ruch> zaplanowaneRuchy;

    /**
     * \brief Zmienna przechowywująca prędkość kątową drona
     */
    double predkoscKatowa;

    /**
     * \brief Zmienna przechowywująca prędkość liniową drona
     */
    double predkoscLiniowa;

    /**
     * \brief Zmienna przechowywująca numer identyfikacyjny drona
     */
    int numerIdentyfikacyjny;
  public:
    /**
     * Konstruktor parametryczny inicjujący rysowanie drona w danym łączu do gnuplota
     */
    Dron(PzG::LaczeDoGNUPlota& lacze, int numerDrona);

    /**
     * Konstruktor kopiujący klasę Dron - kopiuje klasę ścieżka (zamiast kopiować wskaźnik)
     */
    Dron(const Dron& dron);

    /**
     * Destruktor klasy Dron - usuwa klasę ścieżka
     */
    ~Dron();

    /**
     * Metoda zwracające wektor przesunięcia drona względem środka układu współrzędnych
     */
    Wektor3D zwrocWektorPrzesuniecia() const;

    /**
     * Metoda przesuwająca drona z jego poprzedniego położenia o zadany wektor
     */
    void przesun(const Wektor3D &wektor);

    /**
     * Metoda przesuwająca drona o zadany wektor z środka układu współrzędnych
     */
    void ustawPrzesuniecie(const Wektor3D &wektor);

    /**
     * Metoda zwracająca kąt obrotu lokalnego drona wokół osi OZ
     */
    double zwrocKatObrotu();

    /**
     * Metoda obracająca drona (zaczynając od jego obecnego obrotu) o zadany kąt
     */
    void obroc(double kat);

    /**
     * Metoda obracająca drona (zaczynając od kąta równego 0) o zadany kąt
     */
    void ustawObrot(double kat);

    /**
     * Metoda dodająca przelot drona po obrocie o zadany kąt na zadaną odległość
     */
    bool dodajPrzelot(double kat, double odleglosc);

    /**
     * Metoda zwracająca prędkość kątową drona
     */
    double zwrocPredkoscKatowa();

    /**
     * Metoda ustawiająca prędkość kątową drona
     */
    bool ustawPredkoscKatowa(double nowaPredkosc);

    /**
     * Metoda zwracająca prędkość liniową drona
     */
    double zwrocPredkoscLiniowa();

    /**
     * Metoda ustawiająca prędkość liniową drona
     */
    bool ustawPredkoscLiniowa(double nowaPredkosc);

    /**
     * Metoda wykonująca pojedynczy krok drona - służy do animowania ruchu drona
     */
    bool wykonajKrok(double fps); // zwraca false gdy już nie ma kroków do wykonania

    /**
     * Metoda animująca lądowanie drona
     */
    bool wykonajKrokLadawania(double fps);

    /**
     * Metoda aktualizuje dane w pliku potrzebne gnuplotowi do narysowania drona
     */
    bool rysuj(PzG::LaczeDoGNUPlota& lacze);

    /**
     * Metoda animująca obrót rotorów podczas przemieszczania się drona
     */
    void animujRotory(double fps);

    /**
     * Metoda zwraca true jeśli obrys drona koliduje z obrysem drona podanym jako parametr.
     * Metoda zwraca false jeśli obrysy dronów ze sobą nie kolidują.
     */
    virtual bool czyKoliduje (const Bryla_Geometryczna& dron2) override;

    /**
     * \brief Metoda wirtualna wyświetlająca nazwę danej klasy
     */
    virtual void wyswietlNazwe() const;

    /**
     * Metoda przedłużająca przelot drona (przesówająca ścieżkę lądowania i dorysowyująca dany ruch)
     */
    bool przedluzPrzelot(double kat, double odleglosc);
};

#endif
