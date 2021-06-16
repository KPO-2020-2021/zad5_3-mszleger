#include "./doctest/doctest.h"

#include <sstream>

#include "Macierz.hh"

/**
 * \brief Sprawdzanie poprawnego działania operatora porównania dwóch macierzy.
 */
TEST_CASE("test Operator porównania 1"){
  double parametry[] = {1, 2, 3, 4};
  Macierz<2, double> M1(parametry);
  Macierz<2, double> M2(parametry);
  CHECK(M1 == M2);
}

/**
 * \brief Sprawdzanie poprawnego działania operatora porównania dwóch macierzy.
 */
TEST_CASE("test Operator porównania 2"){
  double parametry1[] = {1, 2, 3, 4};
  double parametry2[] = {0, 2, 3, 4};
  Macierz<2, double> M1(parametry1);
  Macierz<2, double> M2(parametry2);
  CHECK_FALSE(M1 == M2);
}

/**
 * \brief Sprawdzanie poprawnego działania operatora porównania dwóch macierzy.
 */
TEST_CASE("test Operator porównania 3"){
  double parametry[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  Macierz<3, double> M1(parametry);
  Macierz<3, double> M2(parametry);
  CHECK(M1 == M2);
}

/**
 * \brief Sprawdzanie poprawnego działania operatora porównania dwóch macierzy.
 */
TEST_CASE("test Operator porównania 4"){
  double parametry1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  double parametry2[] = {0, 2, 3, 4, 5, 6, 7, 8, 9};
  Macierz<3, double> M1(parametry1);
  Macierz<3, double> M2(parametry2);
  CHECK_FALSE(M1 == M2);
}

/**
 * \brief Sprawdzanie poprawnego działania zanegowanego operatora porównania dwóch macierzy.
 */
TEST_CASE("test Operator zanegowanego porównania 1"){
  double parametry[] = {1, 2, 3, 4};
  Macierz<2, double> M1(parametry);
  Macierz<2, double> M2(parametry);
  CHECK_FALSE(M1 != M2);
}

/**
 * \brief Sprawdzanie poprawnego działania zanegowanego operatora porównania dwóch macierzy.
 */
TEST_CASE("test Operator zanegowanego porównania 2"){
  double parametry1[] = {1, 2, 3, 4};
  double parametry2[] = {0, 2, 3, 4};
  Macierz<2, double> M1(parametry1);
  Macierz<2, double> M2(parametry2);
  CHECK(M1 != M2);
}

/**
 * \brief Sprawdzanie poprawnego działania zanegowanego operatora porównania dwóch macierzy.
 */
TEST_CASE("test Operator zanegowanego porównania 3"){
  double parametry[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  Macierz<3, double> M1(parametry);
  Macierz<3, double> M2(parametry);
  CHECK_FALSE(M1 != M2);
}

/**
 * \brief Sprawdzanie poprawnego działania zanegowanego operatora porównania dwóch macierzy.
 */
TEST_CASE("test Operator zanegowanego porównania 4"){
  double parametry1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  double parametry2[] = {0, 2, 3, 4, 5, 6, 7, 8, 9};
  Macierz<3, double> M1(parametry1);
  Macierz<3, double> M2(parametry2);
  CHECK(M1 != M2);
}

/**
 * \brief Sprawdzanie poprawnego działania konstruktora bezargumentowego.
 */
TEST_CASE("test Konstruktor bezargumentowy 1"){
  double parametry[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
  Macierz<3, double> M1(parametry);
  Macierz<3, double> M2;
  CHECK(M1 == M2);
}

/**
 * \brief Sprawdzanie poprawnego działania konstruktora argumentowego i operatora indeksującego.
 */
TEST_CASE("test Konstruktor arguemtnowy i operator indeksujący 1"){
  double parametry[] = {1, 2, 3, 4};
  Macierz<2, double> M1(parametry);
  Macierz<2, double> M2;
  M2(0, 0) = 1;
  M2(1, 0) = 2;
  M2(0, 1) = 3;
  M2(1, 1) = 4;
  CHECK(M1 == M2);
}

/**
 * \brief Sprawdzanie poprawnego działania metody ustawiającej wartości macierzy wartościami z tablicy podanej jako argument.
 */
TEST_CASE("test Metoda ustawiająca wartości 1"){
  double parametry1[] = {3, 6, 9, 12, 15, 18, 21, 24, 27};
  double parametry2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  Macierz<3, double> M1(parametry1);
  M1.ustaw(parametry2);
  Macierz<3, double> M2(parametry2); 
  CHECK(M1 == M2);
}

/**
 * \brief Sprawdzanie poprawnego działania operatora wpisującego wartości wektora do strumienia.
 */
TEST_CASE("test Operator << 1"){
  std::stringstream strumien;
  double parametry[] = {2, 3, 4, 5};
  std::string oczekiwanyRezultat = "    2.0000000000    3.0000000000\n\
    4.0000000000    5.0000000000\n";
  Macierz<2, double> M(parametry);
  strumien << M;
  CHECK(strumien.str() == oczekiwanyRezultat);
}

/**
 * \brief Sprawdzanie poprawnego działania metody obliczającej wyznacznik macierzy
 */
TEST_CASE("test Metoda obliczająca wyznacznik macierzy 1"){
  double parametry[] = {3, 8, 5, 12, 15, 18, 6, 24, 27};
  double wzorcowyWyznacznik = -819;
  Macierz<3, double> M(parametry);
  CHECK(M.obliczWyznacznik() == wzorcowyWyznacznik);
}

/**
 * \brief Sprawdzanie poprawnego działania metody obliczającej wyznacznik macierzy
 */
TEST_CASE("test Metoda obliczająca wyznacznik macierzy 2"){
  double parametry[] = {3, 6, 9, 1, 15, 18, 21, 4, 27};
  double wzorcowyWyznacznik = 306;
  Macierz<3, double> M(parametry);
  CHECK(M.obliczWyznacznik() == wzorcowyWyznacznik);
}

/**
 * \brief Sprawdzanie poprawnego działania operatora mnożenia macierzy razy wektor
 */
TEST_CASE("test Metoda obliczająca wyznacznik macierzy 2"){
  double parametryM[] = {3, 6, 9, 12, 15, 18, 21, 24, 27};
  double parametryW[] = {1, 2, 3};
  double parametryWzorcowe[] = {42, 96, 150};
  Macierz<3,double> M(parametryM);
  Wektor<3,double> W(parametryW);
  Wektor<3,double> Wzorzec(parametryWzorcowe);
  CHECK((M * W) == Wzorzec);
}

/**
 * \brief Sprawdzanie poprawnego działania operatora mnożenia macierzy razy macierz
 */
TEST_CASE("test Metoda obliczająca wyznacznik macierzy 2"){
  double parametryM1[] = {3, 6, 9, 12, 15, 18, 21, 24, 27};
  double parametryM2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  double parametryWzorcowe[] = {90, 108, 126, 198, 243, 288, 306, 378, 450};
  Macierz<3,double> M1(parametryM1);
  Macierz<3,double> M2(parametryM2);
  Macierz<3,double> Wzorzec(parametryWzorcowe);
  CHECK((M1 * M2) == Wzorzec);
}