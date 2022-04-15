// Tomasz Koczar
// 15.04.2022AD
// Zadanie H
// Kurs "Programowanie 2"

#include "Morfologia.h"

/** Klasa reprezentujaca bitmapy 3D.*/
class BitmapaExt : public Bitmapa{
   /*--------------Pola-----------------*/
   /**Kazdy bit mapy moze przyjmowac jeden z kolorow:
    * Bialy lub Czarny.
    * */
   enum Color{ WHITE = 0, BLACK = 1 };

   /**Pola zawierajace rozmiar bitmapy*/
   unsigned int rangeX,rangeY,rangeZ;

   /**Pole reperzetujace Bitmape.
    * */
   Color* bitmap;

   /*--------------Metody----------------*/
public:
   /**Konstruktor.
    * Przyjmuje rozmar x,y,z, jako parametry.
    * Tworzy biala bitmape.
    * */
    BitmapaExt(unsigned int x, unsigned int y, unsigned int z): rangeX{x},rangeY{y},rangeZ{z}{
        bitmap = new Color[x*y*z]; // Tworzy tablice bitow o rozmiarze x*y*z.
        for(auto i = 0; i<x*y*z; ++i )
            bitmap[i] = WHITE;
    }

    /**Destruktor*/
    ~BitmapaExt(){ delete[] bitmap; }



};
