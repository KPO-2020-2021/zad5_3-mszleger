#pragma once

#include "Bryla_Geometryczna.hh"

class GoraZGrania: public Bryla_Geometryczna {
  public:
    /**
     * Wirtualny destruktor klasy
     */
    virtual ~GoraZGrania() {}

    /**
     * Metoda wirtualna wyświetlająca nazwę klasy
     */
    virtual void wyswietlNazwe() const override;

    /**
     * Metoda wirtualna deformująca prostopadłościan w taki sposób, aby powstała góra z granią
     */
    virtual void deformuj() override;
};