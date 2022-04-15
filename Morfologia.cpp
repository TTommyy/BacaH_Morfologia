// Tomasz Koczar
// 15.04.2022AD
// Zadanie H
// Kurs "Programowanie 2"

#ifndef __MORFOLOGIA_CPP__
#define __MORFOLOGIA_CPP__

#include "Morfologia.h"
#include <ostream>
#include <cstring>



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
        for(unsigned i = 0; i<x*y*z; ++i )
            bitmap[i] = false;//Ustawiamy kolor kazdego na bialy
    }

    /**Konstruktor kopujacy*/
    BitmapaExt( BitmapaExt& bm):rangeX{bm.rangeX} ,rangeY{bm.rangeY},rangeZ{bm.rangeZ}{
        bitmap = new bool[rangeX*rangeY*rangeZ];
        memcpy(bitmap,bm.bitmap,sizeof(bool)*(rangeX*rangeY*rangeZ));
    }

    /**Operator przypisania*/
    BitmapaExt& operator=(const BitmapaExt& bm){
        if(this!=&bm){
            delete[] bitmap;
            rangeX=bm.rangeX ;rangeY=bm.rangeY;rangeZ=bm.rangeZ;//nowy rozmiar
            bitmap = new bool[rangeX*rangeY*rangeZ];
            memcpy(bitmap,bm.bitmap,sizeof(bool)*(rangeX*rangeY*rangeZ));//kopijujemy
        }
        return *this;
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

/**Operator wyjscia dla klasy  BitMapa*/
std::ostream &operator <<( std::ostream& ostream, const  BitmapaExt& bitmapa) {
    ostream << "{\n";
    for( unsigned rX = 0; rX < bitmapa.sx(); rX++ ){// wypisujemy dwuwymiarowe bloki
        ostream << "{\n";
        for( unsigned rY = 0; rY < bitmapa.sy(); rY++ ){//wypsujemy wiersze w blokach
            ostream << "{";
            for(unsigned rZ = 0; rZ < bitmapa.sz(); rZ++ ){
                ostream << bitmapa(rX,rY,rZ);
                if(rZ+1<bitmapa.sz()) ostream << ",";
            }
            ostream << "}\n";
        }
        ostream << "}\n";
    }
    ostream << "}";
    return ostream;
}

#endif