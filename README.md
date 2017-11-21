# PrPr - Projekt 2

Projekt na Proceduralne programovanie

 * Zadanie: [stiahnut](resources/zadanie.pdf)
 * Auta: [stiahnut](resources/auta.txt)
 * Vstupy: [stiahnut](resources/vstupy.txt)
 * Vystupy: [stiahnut](resources/vystupy.txt)


Posledny uspesny build: [stiahnut](https://github.com/dodancs/PrPr-Projekt2/releases) | [changelog](https://github.com/dodancs/PrPr-Projekt2/blob/master/CHANGELOG.md) | [source](https://github.com/dodancs/PrPr-Projekt2/blob/master/sources/sources/Source.c)
Development build: [stiahnut](https://github.com/dodancs/PrPr-Projekt2/releases) | [changelog](https://github.com/dodancs/PrPr-Projekt2/blob/develop/CHANGELOG.md) | [source](https://github.com/dodancs/PrPr-Projekt2/blob/develop/sources/sources/Source.c)

Potrebny software:

 * Windows/Linux/Mac (x86/x64)
 * C compiler


#### Ako pouzivat program?

##### 1. Nacitanie dat zo suboru

```
C\> prpr.exe
    n <- precita "auta.txt" a ulozi vsetky zaznamy do pamate, potom vypise pocet zaznamov
    Nacitalo sa %d zaznamov
```
##### 2. Vypis dat z pamate
```
C\> prpr.exe
    v <- vypise vsetky zaznamy z pamate ak boli nacitane predtym prikazom 'n' alebo pridane prikazom 'p'
      1.
      kategoria: %s
      znacka: %s
      predajca: %s
      cena: %d
      rok_vyroby: %d
      stav_vozidla: %s
```
##### 3. Pridanie noveho zaznamu
```
C\> prpr.exe
    p %d <- prida novy zaznam na danu poziciu namiesto existujuceho zaznamu, ak na pozicii zaznam neexistuje, prida sa na koniec zaznamu
      %s
      %s
      %s
      %d
      %d
      %s
```
##### 4. Zmazanie zaznamu
```
C\> prpr.exe
    z %s <- zmaze zaznam/zaznamy zo struktury, ktore obsahuju nacitany retazec v znacke
      Vymazalo sa %d zaznamov
```
##### 5. Vypisanie zaznamov z cenou nizsou alebo rovnou danej cene
```
C\> prpr.exe
    h %d <- vypise vsetky zaznamy s cenou nizsou alebo rovnou zadanej cene
      1.
      kategoria: %s
      znacka: %s
      predajca: %s
      cena: (%d <= %d)
      rok_vyroby: %d
      stav_vozidla: %s

    <- inak vypise danu spravu:
      V ponuke su len auta s vyssou cenou
```
##### 6. Upravenie zaznamov, ktore maju urcitu cenu a znacku
```
C\> prpr.exe
    a %s %d <- nacita nove udaje a aktualizuje existujuce zaznamy, ktore presli kriteriami
      %s
      %s
      %s
      %d
      %d
      %s
      Aktualizovalo sa %d zaznamov
```

#### Kontakt

 * dodancs@moow.info
 * [Osobny web](https://dodancs.moow.info)
 * [Blog](https://dodancs.moow.info/blog)
