
1
2
3
4
5
6
7
8
9
10
11
12
13
14
15
16
17
18
19
20
21
22
23
24
25
26
27
28
29
30
31
32
33
34
35
36
37
38
39
40
41
42
43
44
45
46
47
48
49
50
51
52
53
54
55
56
57
58
59
60
61
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
