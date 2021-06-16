#ifndef GRANIASTOSLUP_HH
#define GRANIASTOSLUP_HH

#include "Bryla_Geometryczna.hh"

/**
 * \brief Klasa modelująca granaiastosłup z sześciokątem w podstawie
 * 
 * Klasa dziedziczy klasę Bryla_Geometryczna.
 * Modelowany graniastosłup jest obiektem składającym się z 14 wierzchołków.
 * Wierzchołki to obiekty klasy wektor, które wskazują położenie wierzchołków względem określonego przez nas środka figury.
 * Klasa dodaje funkcję wczytajBryleWzorcowa wczytującą prostopadłościan z pliku; 14 wektorów zapisanych w pliku zapisanych w następującej kolejności:
 * 
 *     12 - - - 11
 *     /         \
 *    13   14     10
 *    |\         /|
 *    | 8 - - - 9 |
 *    | |       | |
 *    | |5- - -4| |
 *    |/|       |\|
 *    6 |   7   | 3
 *     \|       |/
 *      1 - - - 2
 * 
 */
class Graniastoslup6 : public Bryla_Geometryczna {
  public:
    /**
     * \brief Wczytuje wierzchołki granaiastosłupa z sześciokątem w podstawie z pliku i ustawia kontener przechowujący konfiguracje wierzchołków tworzących poszczególne klasy.
     */
    bool wczytajBryleWzorcowa();

    /**
     * Metoda wirtualna wyświetlająca nazwę klasy
     */
    virtual void wyswietlNazwe() const override;

    /**
     * Metoda wirtualna deformująca prostopadłościan w taki sposób, aby powstała góra z ostrym szczytem
     */
    virtual void deformuj() override;
};

#endif