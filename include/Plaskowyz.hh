#pragma once

#include "Bryla_Geometryczna.hh"

class Plaskowyz: public Bryla_Geometryczna {
  public:
    /**
     * Wirtualny destruktor klasy
     */
    virtual ~Plaskowyz() {}

    /**
     * Metoda wirtualna wyświetlająca nazwę klasy
     */
    virtual void wyswietlNazwe() const override;

    /**
     * Metoda wirtualna deformująca prostopadłościan w taki sposób, aby powstał płaskowyż
     */
    virtual void deformuj() override;
};