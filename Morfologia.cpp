// Tomasz Koczar
// 15.04.2022AD
// Zadanie H
// Kurs "Programowanie 2"

#include "Morfologia.h"

/** Klasa reprezentujaca bitmapy 3D.*/
class BitmapaExt : public Bitmapa{
   /*--------------Pola-----------------*/

   /**Pola zawierajace rozmiar bitmapy*/
   unsigned rangeX,rangeY,rangeZ;

   /**Pole reperzetujace Bitmape.
    * Kazdy bit moze byc bialy = false = 0.
    * Badz czarny = true != 0*/
   bool* bitmap;

   /*--------------Metody----------------*/
public:
   /**Konstruktor.
    * Przyjmuje rozmar x,y,z, jako parametry.
    * Tworzy biala bitmape.
    * */
    BitmapaExt(unsigned x, unsigned y, unsigned z): rangeX{x},rangeY{y},rangeZ{z}{
        bitmap = new bool[x*y*z]; // Tworzy tablice bitow o rozmiarze x*y*z.
        for(auto i = 0; i<x*y*z; ++i )
            bitmap[i] = false;//Ustawiamy kolor kazdego na bialy
    }

    /**Destruktor*/
    ~BitmapaExt() override{ delete[] bitmap; }

    /**Getery dla rozmiaru*/
    unsigned sx() const override{
        return rangeX;
    }

    unsigned sy() const override{
        return rangeY;
    }

    unsigned sz() const override{
        return rangeZ;
    }

    /*Akcesory*/
    /**Akcesor do referencji*/
    bool& operator()(unsigned x, unsigned y, unsigned z) override{
        return bitmap[x*(rangeY*rangeZ)+(y*rangeZ)+z];
    }
    /**Akcesor do kopi*/
    bool operator()(unsigned x, unsigned y, unsigned z)const override{
        return bitmap[x*(rangeY*rangeZ)+(y*rangeZ)+z];
    }


};
