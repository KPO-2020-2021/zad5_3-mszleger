#include "../include/MacierzObrotu.hh"

void generujMacierzObrotu(MacierzObrotu &macierz, double kat, Os os)
{
  kat = kat * M_PI / 180;
  switch (os)
  {
    case OX:
    macierz(0, 0) =  1;
    macierz(1, 0) =  0;
    macierz(2, 0) =  0;
    macierz(0, 1) =  0;
    macierz(1, 1) =  cos(kat);
    macierz(2, 1) = -sin(kat);
    macierz(0, 2) =  0;
    macierz(1, 2) =  sin(kat);
    macierz(2, 2) =  cos(kat);
    break;
      
  case OY:
    macierz(0, 0) =  cos(kat);
    macierz(1, 0) =  0;
    macierz(2, 0) =  sin(kat);
    macierz(0, 1) =  0;
    macierz(1, 1) =  1;
    macierz(2, 1) =  0;
    macierz(0, 2) = -sin(kat);
    macierz(1, 2) =  0;
    macierz(2, 2) =  cos(kat);
    break;

  case OZ:
    macierz(0, 0) =  cos(kat);
    macierz(1, 0) = -sin(kat);
    macierz(2, 0) =  0;
    macierz(0, 1) =  sin(kat);
    macierz(1, 1) =  cos(kat);
    macierz(2, 1) =  0;
    macierz(0, 2) =  0;
    macierz(1, 2) =  0;
    macierz(2, 2) =  1;
    break;
  }
}

Macierz3X3 generujMacierzObrotu(double kat, Os os)
{
  Macierz3X3 macierz;
  generujMacierzObrotu(macierz, kat, os);
  return macierz;
}