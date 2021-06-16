#pragma once

#include "Bryla_Geometryczna.hh"

class GoraZOstrymSzczytem: public Bryla_Geometryczna {
  public:
    /**
     * Destruktor wirtualny klasy
     */
    virtual ~GoraZOstrymSzczytem() {}

    /**
     * Metoda wirtualna wyświetlająca nazwę klasy
     */
    virtual void wyswietlNazwe() const override;

    /**
     * Metoda wirtualna deformująca prostopadłościan w taki sposób, aby powstała góra z ostrym szczytem
     */
    virtual void deformuj() override;
};