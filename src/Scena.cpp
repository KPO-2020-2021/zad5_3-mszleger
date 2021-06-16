#include "../include/Scena.hh"

Scena::Scena()
{
  this->minx = -100;
  this->maxx =  100;
  this->miny = -100;
  this->maxy =  100;
  this->minz =  -10;
  this->maxz =  120;
  lacze.ZmienTrybRys(PzG::TR_3D);
  lacze.UstawZakresX(minx,maxx);
  lacze.UstawZakresY(miny,maxy);
  lacze.UstawZakresZ(minz,maxz);
  double wspolrzedne0[] = { 10,0,0};
  double wspolrzedne1[] = {-10,0,0};
  Wektor3D przesuniecie0(wspolrzedne0);
  Wektor3D przesuniecie1(wspolrzedne1);
  drony.push_back(std::make_shared<Dron>(lacze, this->drony.size()));
  drony.push_back(std::make_shared<Dron>(lacze, this->drony.size()));
  drony[0]->ustawPrzesuniecie(przesuniecie0);
  drony[1]->ustawPrzesuniecie(przesuniecie1);
  this->rysujPodloze();
}

bool Scena::rysujPodloze()
{
  std::fstream plik;                                                 // Tworzenie uchwytu do pliku
  plik.open("../datasets/tmp_podloze.dat", std::fstream::out);       // Otwieranie pliku
  if(plik.is_open() == false)                                        // Sprawdzanie czy udało się otworzyć plik - zwracanie false jeśli nie
    return false;
  // Rysowanie linii równoległych do osi OX
  for(int x = 0; x <= ((maxx-minx) / 10); ++x)
  {
    plik << minx + (x * 10) << " " << miny << " " << 0 << std::endl;
    plik << minx + (x * 10) << " " << maxy << " " << 0 << std::endl;
    plik << std::endl << std::endl;
  }

  // Rysowanie linii równoległych do osi OY
  for(int y = 0; y <= ((maxy-miny) / 10); ++y)
  {
    plik << minx << " " << miny + (y * 10) << " " << 0 << std::endl;
    plik << maxx << " " << miny + (y * 10) << " " << 0 << std::endl;
    plik << std::endl << std::endl;
  }


  if(plik.fail())                                                    // Sprawdzanie czy wystąpił błąd podczas zapisywania
  {
    plik.close();                                                    // Zamykanie pliku
    return false;                                                    // Zwracanie false
  }
  plik.close();                                                      // Zamykanie pliku
  this->lacze.DodajNazwePliku("../datasets/tmp_podloze.dat");        // Dodawanie nazwy pliku przechowywującego rysunek podłoża do pliku
  return true;                                                       // Zwracanie true
}

void Scena::animuj()
{
  bool czyZankonczonoRysowanie = false;
  while(!czyZankonczonoRysowanie)
  {
    czyZankonczonoRysowanie = true;
    for(std::shared_ptr<Dron>& dron : drony)
    {
      if(dron->wykonajKrok(20) == true)
        czyZankonczonoRysowanie = false;
    }
    this->wyswietl();
    std::this_thread::sleep_for (std::chrono::milliseconds(50)); // Odczekanie 50ms
  }
}

bool Scena::wyswietl()
{
  for(std::shared_ptr<Dron>& dron : this->drony)
    dron->rysuj(lacze);
  lacze.Rysuj();
  return true;
}

void Scena::gdzieDron(int numerDrona)
{
  Wektor3D wektorPrzesuniecia = this->drony[numerDrona]->zwrocWektorPrzesuniecia();
  if((wektorPrzesuniecia[0] < 0.001) && (wektorPrzesuniecia[0] > -0.001))
    wektorPrzesuniecia[0] = 0;
  if((wektorPrzesuniecia[1] < 0.001) && (wektorPrzesuniecia[1] > -0.001))
    wektorPrzesuniecia[1] = 0;
  std::cout << wektorPrzesuniecia[0] << " " << wektorPrzesuniecia[1];
}

bool Scena::dodajPrzeszkode(unsigned int typPrzeszkody, const Wektor3D& przesuniecie, double kat, double skalaOX, double skalaOY, double skalaOZ)
{
  std::string nazwaPliku = "../datasets/tmp_przeszkoda_" + std::to_string(przeszkody.size() + 1) + ".dat"; // Tworzenie nazwy pliku przechowywującego dane potrzebne do rysowania
  switch (typPrzeszkody)
  {
  case 1:
    przeszkody.push_back(std::make_shared <GoraZOstrymSzczytem>());     // Dodawanie nowej przeszkody do listy przeszkód - Góry z ostrym szczytem
    break;
  case 2:
    przeszkody.push_back(std::make_shared <GoraZGrania>());     // Dodawanie nowej przeszkody do listy przeszkód - Góry z granią
    break;
  case 3:
    przeszkody.push_back(std::make_shared <Plaskowyz>());     // Dodawanie nowej przeszkody do listy przeszkód - Płaskowyżu
    break;
  default:
    return false;
    break;
  }
  polozeniePrzeszkod.push_back(przesuniecie);                        // Zapisywanie wektora położenia nowej figury
  przeszkody.back()->ustawNazwePlikuBrylaWzorcowa("../datasets/prostopadloscian.dat"); // Wczytywanie bryły wzorcowej
  przeszkody.back()->ustawNazwePlikuBrylaFinalna(nazwaPliku);        // Podawanie nazwy pliku roboczego bryły
  if(przeszkody.back()->wczytajBryleWzorcowa() == false) return false; // Wczytywanie bryły wzorcowej - zwracanie false jeśli się nie udało
  przeszkody.back()->skaluj(skalaOX, skalaOY, skalaOZ);              // Skalowanie byryły przed dodaniem
  przeszkody.back()->deformuj();                                     // Deformowanie nowoutworzonej figury
  if(przeszkody.back()->zapiszWspolrzedneDoWyswietlenia(generujMacierzObrotu(kat, OZ), przesuniecie) == false) return false; // Zapisywanie danych do wyświetlenia
  lacze.DodajNazwePliku(nazwaPliku.c_str());                         // Dodawanie nazwy pliku roboczego do gnuplota
  return true;                                                       // Zwracanie true jeśli udało się dodać przeszkodę
}

bool Scena::przesunPrzeszkode(unsigned int numerPrzeszkody, const Wektor3D& przesuniecie, double kat)
{
  if((numerPrzeszkody > przeszkody.size()) && (numerPrzeszkody != 0)) return false;        // Zwracanie false jeśli wykonano próbę usunięcia nieistniejącej przeszkody
  std::list<std::shared_ptr <Bryla_Geometryczna>>::iterator iterator = przeszkody.begin(); // Tworzenie wskaźnika na dany element przeszkody
  std::advance(iterator, --numerPrzeszkody);
  iterator->get()->zapiszWspolrzedneDoWyswietlenia(generujMacierzObrotu(kat, OZ), przesuniecie); // Zapisywanie figury w nowej pozycji
  std::list<Wektor3D>::iterator iteratorWektoraPolozenia = polozeniePrzeszkod.begin();     // Tworzenie iteratora na listę wektorów położenia danej figury
  std::advance(iteratorWektoraPolozenia, numerPrzeszkody);                                 // Przesunięcie iteratora na wektor położenia obecnie przesuwanej figury
  *iteratorWektoraPolozenia = przesuniecie;                                                // Zapisywanie nowego wektora położenia
  return true;                                                                             // Zwracanie true
}

bool Scena::usunPrzeszkode(unsigned int numerPrzeszkody)
{
  if((numerPrzeszkody > przeszkody.size()) && (numerPrzeszkody != 0)) return false;        // Zwracanie false jeśli wykonano próbę usunięcia nieistniejącej przeszkody
  std::list<std::shared_ptr <Bryla_Geometryczna>>::iterator iterator = przeszkody.begin(); // Tworzenie wskaźnika na dany element przeszkody
  std::advance(iterator, --numerPrzeszkody);
  iterator->get()->wyczyscWspolrzedneDoWyswietlenia();                                     // Usuwanie danych do wyświetlania, żeby gnuplot nie wyświetlał więcej pliku
  przeszkody.erase(iterator);                                                              // Usuwanie danej przeszkody
  std::list<Wektor3D>::iterator iteratorWektoraPolozenia = polozeniePrzeszkod.begin();     // Tworzenie iteratora na listę wektorów położenia danej figury
  std::advance(iteratorWektoraPolozenia, numerPrzeszkody);                                 // Przesunięcie iteratora na wektor położenia obecnie usuwanej figury
  polozeniePrzeszkod.erase(iteratorWektoraPolozenia);                                      // Usuwanie wektora położenia
  return true;                                                                             // Zwracanie true
}

void Scena::wypiszElementyPowierzchni()
{
  unsigned int numer = 0;
  std::list<Wektor3D>::iterator iteratorWektoraPolozenia = polozeniePrzeszkod.begin();     // Tworzenie iteratora na listę wektorów położenia danej figury
  for(const std::shared_ptr<Bryla_Geometryczna>& bryla : przeszkody)
  {
    std::cout << ++numer << " - (" << *(iteratorWektoraPolozenia++) << ") ";
    bryla->wyswietlNazwe();
    std::cout << std::endl;
  }
}
