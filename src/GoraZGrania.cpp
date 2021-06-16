#include "GoraZGrania.hh"

void GoraZGrania::wyswietlNazwe() const
{
  std::cout << "Góra z granią";
}

void GoraZGrania::deformuj()
{
  wierzcholki[6] = wierzcholki[0];
  wierzcholki[7] = wierzcholki[1];
}