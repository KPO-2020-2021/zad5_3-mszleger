#pragma once

#include <string>
#include <list>
#include <fstream>
#include "Wektor3D.hh"
#include "MacierzObrotu.hh"
#include "Ruch.hh"
#include "lacze_do_gnuplota.hh"

/**
 * Klasa modeluje obiekt ścieżki planowanego przelotu drona.
 */
class Sciezka 
{
  private:
    /**
     * Zmienna statyczna przechowywująca ilość utworzonych elementów danego typu
     */
	  static unsigned int iloscUtworzonychObiektow;
    /**
     * Zmienna przechowywująca numer ścieżki
     */
	  const unsigned int numerSciezki;
    /**
     * Zmienna przechowywująca przesunięcie początku ścieżki względem środka układu współrzędnych
     */
	  Wektor3D poczatek;
    /**
     * Lista przechowywująca wektory tworzące ścieżkę
     */
	  std::list <Wektor3D> sciezka;
    /**
     * Metoda zwraca nazwę pliku do komunikacji z gnuplotem danej ścieżki.
     */
    std::string generujNazwePliku();
  public:
	  /** 
     * Konstruktor inicjuje wartość zmiennej przechowywującej numer ścieżki numerem utworzonego obiektu (++iloscUtworzonychObiektow).
     * Konstruktor tworzy plik do komunikacji z gnuplotem za pomocą metody usunLamana, (która utworzy pusty plik do komunikacji) i doda nazwę pliku do łącza z gnuplotem.
     * Jeśli nie uda się utworzyć pliku zwrócony zostanie wyjątek 501.
     */
	  Sciezka (PzG::LaczeDoGNUPlota& laczeDoGnuplota);
	  /**
     * Metoda dodaje wektor do listy wektorów tworzących ścieżkę.
     * Zwraca true i dodaje wektor do listy jeśli moduł wektora jest różny od 0.
     * W przeciwnym razie metoda zwraca false i nie dodaje wektora do listy.
     */
	  bool dodajWektor (const Wektor3D& polozenieGlobalneDrona,
	                    const Wektor3D& wektor);
	  /**
     * Metoda przekształca informacje zawarte w zmiennej ruch na wektor i wywołuje metodę dodajWektor.
     * Metoda zwraca wartość zwracaną przez metodę dodajWektor.
     */
	  bool dodajRuch (const Wektor3D& polozenieGlobalneDrona,
	                  const Ruch& ruch);
	  /**
     * Metoda zapisuje dane potrzebne do narysowania ścieżki przez gnuplota.
     * Zwraca true jeśli uda się zapisać.
     * Zwraca false jeśli nie uda się zapisać.
     */
	  bool zapiszDoPliku ();
	  /**
     * \brief Metoda usuwa łamaną.
     * 
     * Usuwa zapamiętane wektory ścieżki, zeruje wektor przesunięcia początku łamanej i usuwa współrzędne zapisane w pliku dla gnuplota.
     * Zwraca true jeśli udało się poprawnie wyczyścić zawartość pliku do komunikacji z gnuplotem.
     * Zwraca false jeśli nie udało się wyczyścić zawartości pliku do komunikacji z gnuplotem.
     */
	  bool usunSciezke ();
};
