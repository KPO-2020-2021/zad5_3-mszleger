#ifndef MACIERZOBROTU_HH
#define MACIERZOBROTU_HH

#include <cmath>

#include "Wektor3D.hh"
#include "Macierz3x3.hh"

enum Os {OX, OY, OZ};

typedef Macierz3X3 MacierzObrotu;

/**
 * \brief Funkcja geneuje macierz obrotu o zadany kąt względem zadanej osi.
 */
void generujMacierzObrotu(MacierzObrotu &macierz, double kat, Os os);

/**
 * Funkcja zwraca wygenerowaną macierz obrotu o podany kąt wokół danej osi
 */
Macierz3X3 generujMacierzObrotu(double kat, Os os);

#endif