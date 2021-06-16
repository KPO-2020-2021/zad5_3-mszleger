#include "GoraZOstrymSzczytem.hh"

void GoraZOstrymSzczytem::wyswietlNazwe() const
{
  std::cout << "Góra z ostrym szczytem";
}

void GoraZOstrymSzczytem::deformuj()
{
  Sciana nowaSciana;
  wierzcholki[5] = wierzcholki[3];
  wierzcholki[6] = wierzcholki[0];
  wierzcholki[7] = wierzcholki[1];
  this->sciany.pop_back();
  nowaSciana.ustaw(4,5,4,7);
  this->sciany.push_back(nowaSciana);
  nowaSciana.ustaw(4,6,4,7);
  this->sciany.push_back(nowaSciana);
}