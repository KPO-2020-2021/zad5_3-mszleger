#ifndef PROSTOKAT_HH
#define PROSTOKAT_HH

#include "Bryla_Geometryczna.hh"

/**
 * \brief Klasa modelująca prostopadłościan
 * 
 * Klasa dziedziczy klasę Bryla_Geometryczna.
 * Modelowany prostopadłościan jest obiektem składającym się z 8 wierzchołków.
 * Wierzchołki to obiekty klasy wektor, które wskazują położenie wierzchołków względem określonego przez nas środka figury.
 * Klasa dodaje funkcję wczytajBryleWzorcowa wczytującą prostopadłościan z pliku; 8 wektorów zapisanych w pliku zapisanych w następującej kolejności:
 * 
 *    5 - - - 6
 *   /|      /|
 *  7 - - - 8 |
 *  | |     | |
 *  | 3 - - | 4
 *  |/      |/
 *  1 - - - 2
 * 
 */
class Prostopadloscian : public Bryla_Geometryczna{
  public:
    /**
     * \brief Wczytuje wierzchołki prostopadłościanu z pliku i ustawia kontener przechowujący konfiguracje wierzchołków tworzących poszczególne klasy.
     */
    bool wczytajBryleWzorcowa();

    /**
     * Metoda wirtualna wyświetlająca nazwę klasy
     */
    virtual void wyswietlNazwe() const override;

    /**
     * Metoda wirtualna deformująca prostopadłościan w taki sposób, aby powstał prostopadłościan
     */
    virtual void deformuj() override;
};

#endif
