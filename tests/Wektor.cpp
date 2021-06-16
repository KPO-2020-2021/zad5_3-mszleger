#include "./doctest/doctest.h"

#include <sstream>

#include "Wektor.hh"

/**
 * \brief Sprawdzanie poprawnego działania operatora porównania dwóch wektorów.
 */
TEST_CASE("test Operator porównania 1"){
  double parametry[] = {1, 2};
  Wektor<2, double> W1(parametry);
  Wektor<2, double> W2(parametry);
  CHECK(W1 == W2);
}

/**
 * \brief Sprawdzanie poprawnego działania operatora porównania dwóch wektorów.
 */
TEST_CASE("test Operator porównania 2"){
  double parametry1[] = {1, 2};
  double parametry2[] = {3, 2};
  Wektor<2, double> W1(parametry1);
  Wektor<2, double> W2(parametry2);
  CHECK_FALSE(W1 == W2);
}

/**
 * \brief Sprawdzanie poprawnego działania operatora porównania dwóch wektorów.
 */
TEST_CASE("test Operator porównania 3"){
  double parametry[] = {1, 2, 3};
  Wektor<3, double> W1(parametry);
  Wektor<3, double> W2(parametry);
  CHECK(W1 == W2);
}

/**
 * \brief Sprawdzanie poprawnego działania operatora porównania dwóch wektorów.
 */
TEST_CASE("test Operator porównania 4"){
  double parametry1[] = {1, 2, 3};
  double parametry2[] = {0, 2, 3};
  Wektor<3, double> W1(parametry1);
  Wektor<3, double> W2(parametry2);
  CHECK_FALSE(W1 == W2);
}

/**
 * \brief Sprawdzanie poprawnego działania zanegowanego operatora porównania dwóch wektorów.
 */
TEST_CASE("test Operator zanegowanego porównania 1"){
  double parametry[] = {1, 2};
  Wektor<2, double> W1(parametry);
  Wektor<2, double> W2(parametry);
  CHECK_FALSE(W1 != W2);
}

/**
 * \brief Sprawdzanie poprawnego działania zanegowanego operatora porównania dwóch wektorów.
 */
TEST_CASE("test Operator zanegowanego porównania 2"){
  double parametry1[] = {1, 2};
  double parametry2[] = {3, 2};
  Wektor<2, double> W1(parametry1);
  Wektor<2, double> W2(parametry2);
  CHECK(W1 != W2);
}

/**
 * \brief Sprawdzanie poprawnego działania zanegowanego operatora porównania dwóch wektorów.
 */
TEST_CASE("test Operator zanegowanego porównania 3"){
  double parametry[] = {1, 2, 3};
  Wektor<3, double> W1(parametry);
  Wektor<3, double> W2(parametry);
  CHECK_FALSE(W1 != W2);
}

/**
 * \brief Sprawdzanie poprawnego działania zanegowanego operatora porównania dwóch wektorów.
 */
TEST_CASE("test Operator zanegowanego porównania 4"){
  double parametry1[] = {1, 2, 3};
  double parametry2[] = {0, 2, 3};
  Wektor<3, double> W1(parametry1);
  Wektor<3, double> W2(parametry2);
  CHECK(W1 != W2);
}

/**
 * \brief Sprawdzanie poprawnego działania konstruktora bezargumentowego.
 */
TEST_CASE("test Konstruktor bezargumentowy 1"){
  double parametry[] = {0, 0, 0};
  Wektor<3, double> W1(parametry);
  Wektor<3, double> W2;
  CHECK(W1 == W2);
}

/**
 * \brief Sprawdzanie poprawnego działania konstruktora argumentowego i operatora indeksującego.
 */
TEST_CASE("test Konstruktor arguemtnowy i operator indeksujący 1"){
  double parametry[] = {1, 2};
  Wektor<2, double> W1(parametry);
  Wektor<2, double> W2;
  W2[0] = 1;
  W2[1] = 2;
  CHECK(W1 == W2);
}

/**
 * \brief Sprawdzanie poprawnego działania operatora dodwania dwóch wektorów.
 */
TEST_CASE("test Operator dodwania 1"){
  double parametry1[] = {1, 2, 3};
  double parametry2[] = {2, 4, 6};
  double parametry3[] = {3, 6, 9};
  Wektor<3, double> W1(parametry1);
  Wektor<3, double> W2(parametry2);
  Wektor<3, double> W3(parametry3); 
  CHECK((W1 + W2) == W3);
}

/**
 * \brief Sprawdzanie poprawnego działania operatora odejmowania dwóch wektorów.
 */
TEST_CASE("test Operator odejmowania 1"){
  double parametry1[] = {3, 6, 9};
  double parametry2[] = {1, 2, 3};
  double parametry3[] = {2, 4, 6};
  Wektor<3, double> W1(parametry1);
  Wektor<3, double> W2(parametry2);
  Wektor<3, double> W3(parametry3); 
  CHECK((W1 - W2) == W3);
}

/**
 * \brief Sprawdzanie poprawnego działania metody ustawiającej wartości wektora wartościami z tablicy podanej jako argument.
 */
TEST_CASE("test Metoda ustawiająca wartości 1"){
  double parametry1[] = {3, 6, 9};
  double parametry2[] = {1, 2, 3};
  Wektor<3, double> W1(parametry1);
  W1.ustaw(parametry2);
  Wektor<3, double> W2(parametry2); 
  CHECK(W1 == W2);
}

/**
 * \brief Sprawdzanie poprawnego działania metody zwracającej wartość modułu wektora.
 */
TEST_CASE("test Moduł 1"){
  double parametry[] = {3, 4};
  Wektor<2, double> W(parametry); 
  CHECK(W.modul() == 5);
}

/**
 * \brief Sprawdzanie poprawnego działania operatora wpisującego wartości wektora do strumienia.
 */
TEST_CASE("test Operator << 1"){
  std::stringstream strumien;
  double parametry[] = {2, 3};
  std::string oczekiwanyRezultat = "    2.0000000000    3.0000000000";
  Wektor<2, double> W(parametry);
  strumien << W;
  CHECK(strumien.str() == oczekiwanyRezultat);
}