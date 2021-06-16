#include "Dron.hh"

Dron::Dron(PzG::LaczeDoGNUPlota& lacze, int numerDrona)
{
  numerIdentyfikacyjny = numerDrona;
  std::string bufor; // Zmienna przechowywująca nazwy plików podczas tworzenia
  if(this->korpus.ustawNazwePlikuBrylaWzorcowa("../datasets/korpus.dat") == false)
    throw(1);
  bufor = "";
  bufor += "../datasets/tmp_korpus_";
  bufor += std::to_string(numerDrona);
  bufor += ".dat";
  if(this->korpus.ustawNazwePlikuBrylaFinalna(bufor) == false)
    throw(1);
  lacze.DodajNazwePliku(bufor.c_str());
  if(this->korpus.wczytajBryleWzorcowa() == false)
    throw(1);
  if(this->rotory[0].ustawNazwePlikuBrylaWzorcowa("../datasets/rotor.dat") == false)
    throw(1);
  bufor = "";
  bufor += "../datasets/tmp_rotor_0_";
  bufor += std::to_string(numerDrona);
  bufor += ".dat";
  if(this->rotory[0].ustawNazwePlikuBrylaFinalna(bufor) == false)
    throw(1);
  lacze.DodajNazwePliku(bufor.c_str());
  if(this->rotory[0].wczytajBryleWzorcowa() == false)
    throw(1);
  if(this->rotory[1].ustawNazwePlikuBrylaWzorcowa("../datasets/rotor.dat") == false)
    throw(1);
  bufor = "";
  bufor += "../datasets/tmp_rotor_1_";
  bufor += std::to_string(numerDrona);
  bufor += ".dat";
  if(this->rotory[1].ustawNazwePlikuBrylaFinalna(bufor) == false)
    throw(1);
  lacze.DodajNazwePliku(bufor.c_str());
  if(this->rotory[1].wczytajBryleWzorcowa() == false)
    throw(1);
  if(this->rotory[2].ustawNazwePlikuBrylaWzorcowa("../datasets/rotor.dat") == false)
    throw(1);
  bufor = "";
  bufor += "../datasets/tmp_rotor_2_";
  bufor += std::to_string(numerDrona);
  bufor += ".dat";
  if(this->rotory[2].ustawNazwePlikuBrylaFinalna(bufor) == false)
    throw(1);
  lacze.DodajNazwePliku(bufor.c_str());
  if(this->rotory[2].wczytajBryleWzorcowa() == false)
    throw(1);
  if(this->rotory[3].ustawNazwePlikuBrylaWzorcowa("../datasets/rotor.dat") == false)
    throw(1);
  bufor = "";
  bufor += "../datasets/tmp_rotor_3_";
  bufor += std::to_string(numerDrona);
  bufor += ".dat";
  if(this->rotory[3].ustawNazwePlikuBrylaFinalna(bufor) == false)
    throw(1);
  lacze.DodajNazwePliku(bufor.c_str());
  if(this->rotory[3].wczytajBryleWzorcowa() == false)
    throw(1);
  this->rotory[0].przesunWzgledemUkladuRodzica(this->korpus[4]);
  this->rotory[1].przesunWzgledemUkladuRodzica(this->korpus[5]);
  this->rotory[2].przesunWzgledemUkladuRodzica(this->korpus[6]);
  this->rotory[3].przesunWzgledemUkladuRodzica(this->korpus[7]);
  this->predkoscKatowa = 180;
  this->predkoscLiniowa = 100;
  this->sciezka = new Sciezka(lacze);
}

Dron::~Dron()
{
  delete this->sciezka;
}

Wektor3D Dron::zwrocWektorPrzesuniecia()
{
  return this->przesuniecieGlobalne;
}

void Dron::przesun(const Wektor3D &wektor)
{
  this->przesuniecieGlobalne = this->przesuniecieGlobalne + wektor;
}

void Dron::ustawPrzesuniecie(const Wektor3D &wektor)
{
  this->przesuniecieGlobalne = wektor;
}

double Dron::zwrocKatObrotu()
{
  return this->obrotLokalny;
}

void Dron::obroc(double kat)
{
  this->obrotLokalny = this->obrotLokalny + kat;
}

void Dron::ustawObrot(double kat)
{
  this->obrotLokalny = kat;
}

bool Dron::dodajPrzelot(double kat, double odleglosc)
{
  Ruch nowyRuch;
  Wektor3D wzniesienie;
  Wektor3D ladowanie;
  wzniesienie[2] = 100;
  ladowanie[2] = -100;
  if(odleglosc < 0)                              // Zwrócenie false jeśli długość przelotu jest ujemna
    return false;
  nowyRuch.katObrotu = kat;
  nowyRuch.odleglosc = odleglosc;
  this->zaplanowaneRuchy.push_back(nowyRuch);    // Dodawanie ruchu na koniec listy zaplanowanych ruchów
  nowyRuch.katObrotu += this->obrotLokalny;                                    // Dodawanie do kąta obrotu ścieżki kąt obrotu lokalnego drona
  this->sciezka->dodajWektor(this->przesuniecieGlobalne, wzniesienie);         // Tworzenie ścieżki reprezentującej wznoszenie się drona
  this->sciezka->dodajRuch(this->przesuniecieGlobalne, nowyRuch);              // Tworzenie ścieżki reprezentującej przelot drona
  this->sciezka->dodajWektor(this->przesuniecieGlobalne, ladowanie);           // Tworzenie ścieżki reprezentującej lądowanie drona
  return true;
}

double Dron::zwrocPredkoscKatowa()
{
  return this->predkoscKatowa;
}

bool Dron::ustawPredkoscKatowa(double nowaPredkosc)
{
  if(nowaPredkosc <= 0)
    return false;
  this->predkoscKatowa = nowaPredkosc;
  return true;
}

double Dron::zwrocPredkoscLiniowa()
{
  return this->predkoscLiniowa;    
}

bool Dron::ustawPredkoscLiniowa(double nowaPredkosc)
{
  if(nowaPredkosc <= 0)
    return false;
  this->predkoscLiniowa = nowaPredkosc;
  return true;
}

bool Dron::wykonajKrok(double fps)
{
  double ruch = 0; // Zmienna pomocnicza przechowująca kąt obecnego obrotu lub odległość obecnego przesunięcia
  MacierzObrotu macierzObrotu;
  Wektor3D wektor;
  double wartosciDomslneWektora[] = {1,0,0};

  if(this->zaplanowaneRuchy.size() == 0)         // Sprawdzanie czy zaplanowano ruchy do wykonania
  {
    if(this->przesuniecieGlobalne[2] != 0) // Sprawdzanie czy dron jeszcze nie wylądował
    {
      ruch = predkoscLiniowa / fps; // Obliczanie maksymalnego kątu obrotu, który można wykonać w jednym kroku
      if(ruch <= przesuniecieGlobalne[2]) // Maksymalne przesunięcie jest mniejsze lub równe wysokości
      {
        przesuniecieGlobalne[2] -= ruch;
      }else{ // Maksymalne przesunięcie jest większe od wysokości
        przesuniecieGlobalne[2] = 0;
      }
      return true;
    }
    this->sciezka->usunSciezke();
    return false;
  }

  std::list<Ruch>::iterator iterator = zaplanowaneRuchy.begin();     // Tworzenie wskaźnika na pierwszy element listy
  
  if((iterator->katObrotu == 0) && (iterator->odleglosc == 0))       // Sprawdzanie czy wykonano wszystkie zaplanowane ruchy z pierwszego ruchu na liście
  {
    zaplanowaneRuchy.pop_front();      // Usuwanie ruchu jeśli został wykoanany
    return true;
  }

  if(this->przesuniecieGlobalne[2] != 100) // Sprawdzanie czy dron wzbił się na wymaganą wysokość
  {
    ruch = predkoscLiniowa / fps; // Obliczanie maksymalnego kątu obrotu, który można wykonać w jednym kroku
    if(ruch <= 100 - przesuniecieGlobalne[2]) // Maksymalne przesunięcie jest mniejsze lub równe wysokości do pokonania
    {
      przesuniecieGlobalne[2] += ruch;
    }else{ // Maksymalne przesunięcie jest większe od wysokości do pokonania
      przesuniecieGlobalne[2] = 100;
    }
    return true;
  }

  if(iterator->katObrotu != 0) // Sprawdzanie czy wykoano obrót z pierszego ruchu na liście
  {      // Wykonywanie obrotu jeśli nie został w pełni wykonany
    ruch = predkoscKatowa / fps; // Obliczanie maksymalnego kątu obrotu, który można wykonać w jednym kroku
    if(ruch <= std::abs(iterator->katObrotu)) // Maksymalny obrót jest mniejszy lub równy od docelowego obrotu do wykonania
    {
      this->obroc(ruch * (std::abs(iterator->katObrotu)/iterator->katObrotu));
      iterator->katObrotu -= (ruch * (std::abs(iterator->katObrotu)/iterator->katObrotu));
    }else{ // Maksymalny obrót jest większy od docelowego obrotu do wykonania
      this->obroc(iterator->katObrotu);
      iterator->katObrotu = 0;
    }
  }else{ // Wykonywanie ruchu liniowego jeśli obrót został wykonany
    ruch = predkoscLiniowa / fps; // Obliczanie maksymalnego kątu obrotu, który można wykonać w jednym kroku
    generujMacierzObrotu(macierzObrotu, this->zwrocKatObrotu(), OZ);
    wektor.ustaw(wartosciDomslneWektora); // Dron domyślnie jest skierowany zgodnie z kierunkiem wektora [1,0,0]
    if(ruch <= iterator->odleglosc) // Maksymalna odległość przesunięcia jest mniejsza lub równa od docelowego przesunięcia do wykonania
    {
      this->przesun(macierzObrotu*(wektor*ruch));
      iterator->odleglosc -= ruch;
    }else{ // Maksymalna odległość przesunięcia jest większa od docelowego przesunięcia do wykonania
      this->przesun(macierzObrotu*(wektor*iterator->odleglosc));
      iterator->odleglosc = 0;
    }
  }
  return true;
}

bool Dron::rysuj(PzG::LaczeDoGNUPlota& lacze)
{
  // Generowanie macierzy obrotu drona wokół jego lokalnego układu współrzędnych
  MacierzObrotu macierzObrotu;
  generujMacierzObrotu(macierzObrotu, this->zwrocKatObrotu(), OZ);
  // Rysowanie korpusu
  if(this->korpus.zapiszWspolrzedneDoWyswietlenia(macierzObrotu, this->przesuniecieGlobalne) == false)
    return false;
  // Rysowanie rotorów
  if(this->rotory[0].zapiszWspolrzedneDoWyswietlenia(macierzObrotu, this->przesuniecieGlobalne) == false)
    return false;
  if(this->rotory[1].zapiszWspolrzedneDoWyswietlenia(macierzObrotu, this->przesuniecieGlobalne) == false)
    return false;
  if(this->rotory[2].zapiszWspolrzedneDoWyswietlenia(macierzObrotu, this->przesuniecieGlobalne) == false)
    return false;
  if(this->rotory[3].zapiszWspolrzedneDoWyswietlenia(macierzObrotu, this->przesuniecieGlobalne) == false)
    return false;
  lacze.Rysuj();
  return true;
}
