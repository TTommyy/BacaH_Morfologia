// Tomasz Koczar
// 15.04.2022AD
// Zadanie H
// Kurs "Programowanie 2"

#include "Morfologia.h"


/** Klasa reprezentujaca bitmapy 3D.*/
class BitmapaExt : public Bitmapa{
   /*--------------Pola-----------------*/
   /**Kazdy bit mapy moze przyjmowac jeden z kolorow:
    * Bialy lub Czarny. */
   enum Color{ WHITE, BLACK };

   /**Pola zawierajace rozmiar bitmapy*/
   unsigned int rangeX,rangeY,rangeZ;

   /**Pole reperzetujace Bitmape.
    * Dostep: bitmap[x][y][z]*/
   Color** bitmap;

   /*--------------Metody----------------*/

};
