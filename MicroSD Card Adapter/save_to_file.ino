#include <SPI.h>                                         //dodaj bibliotekę SPI.h
#include <SD.h>                                          //dodaj bilbiotekę SD.h

File plik;

int x = 1;                                               //przypisz zmiennej x początkową wartość 1


void setup()
{

  Serial.begin(9600);                                    //uruchom UART o prędkości 9600 baud


  Serial.println("Gotowy! (1/3)");
  Serial.println("Szukam karte... (2/3");

  if (!SD.begin(4))                                       //sprawdź czy nie ma karty na pinie ChipSelect 4
  {
     Serial.println("Nie wykryto karty(ERR)");            //błąd wykrycia karty
     return;                                              //przerwij program
  }

  Serial.println("Karta Wykryta (3/3))");                 //Karta wykryta


  if (SD.exists("123.txt"))                               //sprawdź czy istnieje plik o nazwie 123.csv
  {

   Serial.println("Plik o podanej nazwie istnieje !");

  }

  else                                                   //jeżeli nie istnieje to
  {

   plik = SD.open("123.txt", FILE_WRITE);                //utwórz plik
   Serial.println("Utworzono plik o nazwie 123.csv");

  }
}


void loop()
{

logger();                                                //wykonaj program zawarty w klasie logger
x = x +1;                                                //dodaj do zmiennej x + 1

}

void logger()
{

plik = SD.open("123.txt", FILE_WRITE);                   //otwórz plik 123.txt
plik.println(x);                                         //zapisz wartość zmiennej x
plik.close();                                            //zamknij/zapisz plik
delay(300);                                              //oczekaj 0,3s
Serial.println("Zapisano !");                            //poinformuj o zapisaniu pliku

}
