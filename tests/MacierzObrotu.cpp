#include "./doctest/doctest.h"
#include "MacierzObrotu.hh"

/**
 * \brief Sprawdzanie poprawnego funkcji generującej macierz obrotu
 */
TEST_CASE("test Generator macierzy obrotu 1"){
  double parametry[] = {1, 0, 0, 0, 1, 0, 0, 0, 1};
  MacierzObrotu M1;
  MacierzObrotu M2;
  MacierzObrotu Wzorzec(parametry);
  generujMacierzObrotu(M1,  50, OX);
  generujMacierzObrotu(M2, -50, OX);
  CHECK((M1 * M2) == Wzorzec);
}

/**
 * \brief Sprawdzanie poprawnego funkcji generującej macierz obrotu
 */
TEST_CASE("test Generator macierzy obrotu 2"){
  double parametry[] = {1, 0, 0, 0, 1, 0, 0, 0, 1};
  MacierzObrotu M1;
  MacierzObrotu M2;
  MacierzObrotu Wzorzec(parametry);
  generujMacierzObrotu(M1,  50, OY);
  generujMacierzObrotu(M2, -50, OY);
  CHECK((M1 * M2) == Wzorzec);
}

/**
 * \brief Sprawdzanie poprawnego funkcji generującej macierz obrotu
 */
TEST_CASE("test Generator macierzy obrotu 3"){
  double parametry[] = {1, 0, 0, 0, 1, 0, 0, 0, 1};
  MacierzObrotu M1;
  MacierzObrotu M2;
  MacierzObrotu Wzorzec(parametry);
  generujMacierzObrotu(M1,  50, OZ);
  generujMacierzObrotu(M2, -50, OZ);
  CHECK((M1 * M2) == Wzorzec);
}