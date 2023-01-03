#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <math.h>
const double E=0.0001;
class Sat {
  int sati, minute, sekunde;
  static const int dan = 86400; // broj sekundi
public:
  Sat();
  Sat(int sati, int minute, int sekunde);
  void Postavi(int sati, int minute, int sekunde) {
  int temp = sati * 3600 + minute * 60 + sekunde;
  this->sati = temp / 3600;
  this->minute = (temp % 3600) / 60;
  this->sekunde = temp % 60;
}
  void PostaviNormalizirano(int sati, int minute, int sekunde);
  int DajSate() const;
  int DajMinute() const;
  int DajSekunde() const;
  friend int operator-(const Sat &sat1, const Sat &sat2);
  void Ispisi() const {
  std::cout << std::setfill('0') << std::setw(2) << DajSate() << ":" << std::setw(2)
            << DajMinute() << ":" << std::setw(2) << DajSekunde();
}
};

void Sat::PostaviNormalizirano(int sati, int minute, int sekunde) {
  int temp = sati * 3600 + minute * 60 + sekunde;
  if (temp >= dan)
    temp = temp % dan; // ako smo 'prekoracili' dan
  if (temp < 0)
    temp = dan + temp % dan; // u slucaju da imamo negativan pomak (vrijeme)
  this->sati = temp / 3600;
  this->minute = (temp % 3600) / 60;
  this->sekunde = temp % 60;
}
Sat::Sat() : sati(0), minute(0), sekunde(0) {}
Sat::Sat(int sati, int minute, int sekunde)
    : sati(sati), minute(minute), sekunde(sekunde) {
  PostaviNormalizirano(sati, minute, sekunde);
}
int Sat::DajSate() const { return sati; }
int Sat::DajMinute() const { return minute; }
int Sat::DajSekunde() const { return sekunde; }

int operator-(const Sat &sat1, const Sat &sat2) {
 int vrijeme1= sat1.DajSate()*3600 + sat1.DajMinute()*60 ;
  int vrijeme2= sat2.DajSate()*3600 + sat2.DajMinute()*60 ;
  return vrijeme1-vrijeme2;
}


int main() {
    // VERZIJA PROGRAMA 1.0.
    ponovo:
    system("CLS");

    // Ucitavanje iz datoteke
    std::cout<<"---------------------"<<std::endl;
    std::cout<<"WORK TIME TRACKER"<<std::endl;

    // Ispis trenutnog stanja
    std::ifstream ulaz("time.dat", std::ios::binary);
  if(!ulaz){
        std::cout<<"File time.dat has not been found!"<<std::endl;
        return 0;
    }
  std::cout<<"---------------"<<std::endl;
  std::cout << "Current state of your work"<<std::endl;
  double sati;
    ulaz.read(reinterpret_cast<char*>(&sati), sizeof sati);
    std::cout << "Hours: " <<sati<<std::endl;
    ulaz.seekg(1 * sizeof(double));
    double minute;
    ulaz.read(reinterpret_cast<char*>(&minute), sizeof minute);
    ulaz.close();
    std::cout << "Minutes: " <<minute<<std::endl;
    std::cout<<"---------------"<<std::endl;


    char dan=0;
    while(!(dan=='c'||dan=='c'||dan=='n'||dan=='N')){
        std::cout<<"Pick current (c) or new (n) day: ";
    std::cin>>dan;
    }

    // Brisanje sadrzaja - novi dan
    if(dan=='n'||dan=='N'){
        std::ofstream izlaz("time.dat", std::ios::binary);
        if(!izlaz){
        std::cout<<"File time.dat has not been found!"<<std::endl;
        return 0;
    }
  double niz[2] = {0,0};
  izlaz.write(reinterpret_cast<char*>(niz), sizeof niz);
  izlaz.close();
  sati=0;minute=0;
    }

    // Unos vremena
    std::cout<<"Enter start of work (hours minutes): ";
    int enter_h1, enter_m1;
    int enter_h2, enter_m2;
    std::cin>>enter_h1>>enter_m1;
    std::cout<<"Enter end of work (hours minutes): ";
    std::cin>>enter_h2>>enter_m2;

    // Spremanje vremena
  Sat s1(enter_h1, enter_m1, 0);
  Sat s2(enter_h2, enter_m2, 0);
  double from_before=sati*3600+minute*60;
  if(s2-s1<0)
        s2.Postavi(s2.DajSate(), s2.DajMinute(), 24*3600);
  double h=(from_before+(s2-s1))/3600.;
  double m=(h-int(h))*60;
  if(fabs(h-int(h))<E)h=round(h);
  else h=floor(h);
  if(fabs(m-int(m))>E)m=round(m);
  else m=floor(m);
  double from_before_h=(s2-s1)/3600.;
  double from_before_m=(from_before_h-int(from_before_h))*60.0;
  if(fabs(from_before_h-int(from_before_h))<E)from_before_h=round(from_before_h);
  else from_before_h=floor(from_before_h);
  if(fabs(from_before_m-int(from_before_m))>E)from_before_m=round(from_before_m);
  else from_before_m=floor(from_before_m);
  if(s2-s1)
  std::cout<<"You have worked for ";
  else {
    std::cout<<"You have not worked.";
    return 0;
  }


  if(from_before_h>1||fabs(from_before_h-1)<E){
    std::cout<<from_before_h;
    if(fabs(from_before_h-1)<E)std::cout<<" hour";
    if(fabs(from_before_h-2)<E||fabs(from_before_h-3)<E||fabs(from_before_h-4)<E)std::cout<<" hours";
    if(from_before_h>5||fabs(from_before_h-5)<E)std::cout<<" hours";
  }
  if((from_before_h>1||fabs(from_before_h-1)<E)&&from_before_m)
    std::cout<<" and ";
  if(from_before_m){

    std::cout<<from_before_m;
    if(fabs(from_before_m-1)<E)std::cout<<" minute";
    if(fabs(from_before_m-2)<E||fabs(from_before_m-3)<E||fabs(from_before_m-4)<E)std::cout<<" minutes";
    if(from_before_m>5||fabs(from_before_m-5)<E)std::cout<<" minutes";
  }

  // Spasavanje podataka u datoteku
  std::ofstream izlaz("time.dat", std::ios::binary);
  if(!izlaz){
        std::cout<<"File time.dat has not been found!!"<<std::endl;
        return 0;
    }
  double niz[2]={h,m};
  izlaz.write(reinterpret_cast<char*>(niz), sizeof niz);
  izlaz.close();
  std::cout<<std::endl<<"Time has been added to the tracker"<<std::endl;

// Ispis azuriranog vremena
      std::cout<<"---------------"<<std::endl;
  std::cout << "Updated time of your work"<<std::endl;
     std::ifstream ulaz_again("time.dat", std::ios::binary);
    ulaz_again.read(reinterpret_cast<char*>(&sati), sizeof sati);
    std::cout << "Hours: " <<sati<<std::endl;
    ulaz_again.seekg(1 * sizeof(double));
    ulaz_again.read(reinterpret_cast<char*>(&minute), sizeof minute);
    ulaz_again.close();
    std::cout << "Minutes: " <<minute<<std::endl;
    std::cout<<"---------------"<<std::endl;

  // Ponovno pokretanje
   std::cout<<"Restart program y/n: ";
   char znak;
  std::cin>>znak;
  if(znak=='y'||znak=='Y'){
        std::cout<<"\n";
     goto ponovo;
  }

    return 0;
    }
