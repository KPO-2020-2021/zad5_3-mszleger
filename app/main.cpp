#include <iostream>
#include <limits>

#include "Scena.hh"

// Wyświtla opcje obsługiwane przez menu
void wyswietlMenu()
{
  std::cout << std::endl;
  std::cout << "a - wybierz aktywnego drona" << std::endl;
  std::cout << "p - zadaj parametry przelotu" << std::endl;
  std::cout << "d - dodaj element powierzchni" << std::endl;
  std::cout << "u - usun element powierzchni" << std::endl;
  std::cout << "z - zmień położenie elementu powierzchni" << std::endl;
  std::cout << "m - wyświetl menu" << std::endl;
  std::cout << "k - koniec działania programu" << std::endl;
}


/**
 * \brief Metoda wyświetlająca informację o ilości stworzonych i obecnie istniejących obiektów typu Wektor
 *//*
static void PokazRaport()
{
//  std::cout << "Aktualna ilosc obiektow Wektor3D: " << iloscIstniejacych << std::endl;
//  std::cout << "  Laczna ilosc obiektow Wektor3D: " << iloscStworzonych << std::endl;
}*/

void wypisztypyElementowPowierzchni()
{
  std::cout << "1 - Gora z ostrym sztytem" << std::endl;
  std::cout << "2 - Gora z grania" << std::endl;
  std::cout << "3 - Plaskowyz" << std::endl;
}

int main()
{
  Scena scena;
   
  Wektor3D wektor;
  wektor[1] = 20;
  scena.dodajPrzeszkode(1, wektor, 0, 1, 1, 5);
  wektor[1] = 40;
  scena.dodajPrzeszkode(2, wektor, 0, 1, 1, 5);
  wektor[1] = 60;
  scena.dodajPrzeszkode(3, wektor, 0, 1, 1, 5);
  wektor[0] = 20;
  scena.dodajPrzeszkode(3, wektor, 0, 1, 1, 5);
  
  scena.wyswietl();
  Ruch nowyRuch;
  char wybor;
  int numerWybranegoTypu = 0;
  int numerWybranegoElementu = 0;
  Wektor3D wektorPrzesuniecia;
  double wektorX = 0;
  double wektorY = 0;
  double katObrotu = 0;
  double skalaOX = 0;
  double skalaOY = 0;
  double skalaOZ = 0;
  int numerAktywnegoDrona = 0;

  wyswietlMenu();

  while(true)
  {
    std::cout << std::endl;
    std::cout << "Polozenie Drona aktywnego (x,y): ";
    scena.gdzieDron(numerAktywnegoDrona);
    std::cout << std::endl << std::endl;
    std::cout << "Twoj wybor, m - menu > ";
    std::cin >> wybor;

    switch (wybor)
    {
    case 'a': /* Wybór aktywnego drona */
      std::cout << std::endl << "Wybor aktywnego drona" << std::endl << std::endl;
      for(int numerDrona = 0; numerDrona < static_cast<int>(scena.drony.size()); ++numerDrona)
      {
        std::cout << numerDrona + 1 << "  - Polozenie (x,y): ";
        scena.gdzieDron(numerDrona);
        if(numerDrona == numerAktywnegoDrona)
          std::cout << " <-- Dron aktywny";
        std::cout << std::endl;
      }
      std::cout << std::endl << "Wprowadz numer aktywnego drona > ";
      std::cin >> numerAktywnegoDrona;
      --numerAktywnegoDrona;
      std::cout << std::endl;
      break;
    case 'p': /* Zadanie przelotu drona */
      std::cout << "Podaj kierunek lotu (kat w stopniach) > ";
      std::cin >> nowyRuch.katObrotu;
      std::cout << "                   Podaj długość lotu > ";
      std::cin >> nowyRuch.odleglosc;
      scena.drony[numerAktywnegoDrona]->dodajPrzelot(nowyRuch.katObrotu, nowyRuch.odleglosc);
      std::cout << "Rysuje zaplanowana sciezke lotu ..." << std::endl;
      std::cout << "Realizacja przelotu ..." << std::endl;
      scena.animuj();
      std::cout << "Dron wyladowal ..." << std::endl;
      break;
    case 'd': /* Dodawanie elementu powierzchni */
      std::cout << "Wybierz rodzaj powierzchniowego elementu" << std::endl;
      wypisztypyElementowPowierzchni();
      while(true)
      {
        std::cout << "Wprowadz numer typu elementu > ";
        std::cin >> numerWybranegoTypu;
        if(std::cin.fail() == false)
        {
          std::cout << "Podaj scale wzdluz kolejnych osi OX, OY, OZ." << std::endl;
          std::cout << "Wprowadz skale: OX OY OZ > ";
          std::cin >> skalaOX >> skalaOY >> skalaOZ;
        }
        if(std::cin.fail() == false)
        {
          std::cout << "Podaj wspolrzedne srodka podstawy x,y." << std::endl;
          std::cout << "Wprowadz wspolrzedne: x y > ";
          std::cin >> wektorX >> wektorY;
        }
        if(std::cin.fail() == false)
        {
          std::cout << "Podaj kąt obrotu elementu > ";
          std::cin >>katObrotu;
        }
        if(std::cin.fail() == false)
        {
          wektorPrzesuniecia[0] = wektorX;
          wektorPrzesuniecia[1] = wektorY;
          wektorPrzesuniecia[2] = 0;
          if(scena.dodajPrzeszkode(numerWybranegoTypu, wektorPrzesuniecia, katObrotu, skalaOX, skalaOY, skalaOZ))
            break;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        std::cout << "Podano niepoprawne parametry!" << std::endl;
      }




      std::cout << std::endl << "Element zostal dodany do sceny." << std::endl;
      scena.wyswietl();
      break;
    case 'u': /* Usuwanie elementu powierzchni */
      std::cout << "Wybierz element powierzchni do usuniecia:" << std::endl;
      scena.wypiszElementyPowierzchni();
      while(true)
      {
        std::cout << "Podaj numer elementu > ";
        std::cin >> numerWybranegoElementu;
        if(std::cin.fail() == false)
          if(scena.usunPrzeszkode(numerWybranegoElementu))
            break;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        std::cout << "Podano niepoprawny numer!" << std::endl;
      }
      std::cout << std::endl << "Element zostal usuniety." << std::endl;
      scena.wyswietl();
      break;
    case 'z': /* Przesówanie elementu powierzchni */
      std::cout << "Wybierz element powierzchni do przesunięcia:" << std::endl;
      scena.wypiszElementyPowierzchni();
      while(true)
      {
        std::cout << "Podaj numer elementu > ";
        std::cin >> numerWybranegoElementu;
        if(std::cin.fail() == false)
        {
          std::cout << "Podaj wektor przesunięcia > ";
          std::cin >> wektorX >> wektorY;
        }
        if(std::cin.fail() == false)
        {
          std::cout << "Podaj kąt obrotu elementu > ";
          std::cin >>katObrotu;
        }
        if(std::cin.fail() == false)
        {
          wektorPrzesuniecia[0] = wektorX;
          wektorPrzesuniecia[1] = wektorY;
          wektorPrzesuniecia[2] = 0;
          if(scena.przesunPrzeszkode(numerWybranegoElementu, wektorPrzesuniecia, katObrotu))
            break;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        std::cout << "Podano niepoprawne parametry!" << std::endl;
      }
      std::cout << std::endl << "Element zostal przesuniety." << std::endl;
      scena.wyswietl();
      break;
    case 'm': /* Wyświetlenie menu */
      wyswietlMenu();
      break;
    case 'k': /* Zakończenie pracy programu */
      return 0;
      break;
    
    default:
      std::cout << "Podano niewłaściwą opcję" << std::endl;
      break;
    }
  }
}
