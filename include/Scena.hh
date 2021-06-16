#ifndef SCENA_HH
#define SCENA_HH

#include <vector>
#include <fstream>
#include <chrono>
#include <thread>
#include <pthread.h>

#include "Wektor3D.hh"
#include "MacierzObrotu.hh"
#include "Bryla_Geometryczna.hh"
#include "Prostopadloscian.hh"
#include "Graniastoslup6.hh"
#include "lacze_do_gnuplota.hh"
#include "Dron.hh"
#include "GoraZOstrymSzczytem.hh"
#include "GoraZGrania.hh"
#include "Plaskowyz.hh"

/**
 * \brief Klasa opisuje przestrzeń, w której znajdują się dane obiekty
 * 
 * Klasa umożliwia wczytywanie obiektów, manipulowanie nimi w przestrzeni i wyświetlanie położenia obiektów w przestrzeni za pomocą programu gnuplot.
 * Klasa rzuca wyjątek o kodzie 400, jeśli operacje (np. obrotu lub translacji) zostaną wywołane dla nieistniejącego obiektu.
 */
class Scena {
  private:
    /**
     * Struktura za pomocą której odbywa się komunikacja z programem gnuplot
     */
    PzG::LaczeDoGNUPlota  lacze;

    /**
     * Zmienne przechowywujące rozmiary sceny w danych osiach
     */
    int minx;
    int maxx;
    int miny;
    int maxy;
    int minz;
    int maxz;

    /**
     * Lista przechowywująca wektory położenia elementów podłoża
     */
    std::list <Wektor3D> polozeniePrzeszkod;

    /**
     * Lista przechowywująca elementy podłoża
     */
    std::list <std::shared_ptr <Bryla_Geometryczna>> przeszkody;
  public:

    /**
     * Lista przechowywująca drone znajdujące się na scenie
     */
    std::vector <std::shared_ptr <Dron>> drony;

    /**
     * \brief Konstruktor bezparametryczny
     * 
     * Inicjuje pracę gnuplota.
     */
    Scena();

    /**
     * Metoda rysująca siatkę stanowiącą podłoże sceny
     */
    bool rysujPodloze();

    /**
     * \brief Metoda aktualizuje wyświetlany obraz obiektów
     * 
     * Metoda jest wywoływana po operacjach obrotu lub translacji, aby umieścić obiekty w odpowiednich nowych położeniach.
     */
    void animuj();

    /**
     * Metoda odświerzająca wyświetlanie sceny
     */
    bool wyswietl();

    /**
     * Metoda wypisująca na standardowym wyjściu współrzędne położenia drona o danym numrze
     */
    void gdzieDron(int numerDrona);

    /**
     * Metoda dodająca przeszkodę danego typu do sceny
     */
    bool dodajPrzeszkode(unsigned int typPrzeszkody, const Wektor3D& przesuniecie, double kat = 0, double skalaOX = 1, double skalaOY = 1, double skalaOZ = 1);
    
    /**
     * Metoda przesówająca i obracająca już istniejącą przeszkodę o danym numerze
     */
    bool przesunPrzeszkode(unsigned int numerPrzeszkody, const Wektor3D& przesuniecie, double kat);

    /**
     * Metoda usuwająca przeszkodę o danym numerze
     */
    bool usunPrzeszkode(unsigned int numerPrzeszkody);

    /**
     * Metoda wypisująca na standardowym wyjściu elementy powierzchni: ich numer, położenie, typ
     */
    void wypiszElementyPowierzchni();
};

#endif