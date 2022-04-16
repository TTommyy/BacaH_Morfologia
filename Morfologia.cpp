// Tomasz Koczar
// 15.04.2022AD
// Zadanie H
// Kurs "Programowanie 2"

#ifndef __MORFOLOGIA_CPP__
#define __MORFOLOGIA_CPP__

#include "Morfologia.h"
#include <iostream>
#include <cstring>

/*Do reprezentowania wsplrzednych*/
class Trojka{
    
public:
    unsigned x,y,z;
    Trojka(){};
    Trojka(unsigned x, unsigned y, unsigned z): x{x},y{y},z{z}{}
    //Trojka operator =(Trojka t){ x = t.x; y = t.y; z = t.z; return *this; }
};

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

    /**Operatory przypisania*/
    BitmapaExt& operator=(const Bitmapa& bm){
        if(this!=&bm){
            delete[] bitmap;
            rangeX=bm.sx() ;rangeY=bm.sy();rangeZ=bm.sy();//nowy rozmiar
            bitmap = new bool[rangeX*rangeY*rangeZ];
            for(unsigned x = 0; x < rangeX; x++)
                for(unsigned y = 0; y<rangeY; y++)
                    for(unsigned z = 0; z < rangeZ; z++)
                        (*this)(x,y,z) = bm(x,y,z);
        }
        return *this;
    }

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

/*Znajduje sasiadow bitu, ich liczbe przkazuje w parametrze*/
    void otoczenie(const Bitmapa& bm,unsigned x , unsigned y , unsigned z,int& liczbaSasaidow,Trojka* otoczenie){
        liczbaSasaidow = 0;
        //std::cout<< "Punkt" << "x: " << x << " y: " << y << " z: " << z << "\n";
        if(x>0){
            otoczenie[liczbaSasaidow++] = Trojka(x-1,y,z); 
            //std::cout<< "SasiadAdd: " << "x: " << x-1 << " y: " << y << " z: " << z << "\n";
        }
            
        if(x+1<bm.sx()) { 
            otoczenie[liczbaSasaidow++] = Trojka(x+1,y,z); 
            //std::cout<< "SasiadAdd: " << "x: " << x+1 << " y: " << y << " z: " << z << "\n";
        }
        if(y>0){
            otoczenie[liczbaSasaidow++] = Trojka(x,y-1,z);
            //std::cout<< "SasiadAdd: " << "x: " << x << " y: " << y-1 << " z: " << z << "\n";
        } 
        if(y+1<bm.sy()) {
            otoczenie[liczbaSasaidow++] = Trojka(x,y+1,z);
            //std::cout<< "SasiadAdd: " << "x: " << x << " y: " << y+1 << " z: " << z << "\n";
        } 
        
        if(z>0) {
            otoczenie[liczbaSasaidow++] = Trojka(x,y,z-1);
            //std::cout<< "SasiadAdd: " << "x: " << x << " y: " << y << " z: " << z-1 << "\n";
        }

        if(z+1<bm.sz()){
            otoczenie[liczbaSasaidow++] = Trojka(x,y,z+1);
            //std::cout<< "SasiadAdd: " << "x: " << x << " y: " << y << " z: " << z+1 << "\n";
        }

    } 


/**Operator wyjscia dla klasy  BitMapa*/
std::ostream &operator <<( std::ostream& ostream, const  BitmapaExt& bitmapa) {
    ostream << "{\n";
    for( unsigned rX = 0; rX < bitmapa.sx(); rX++ ){// wypisujemy dwuwymiarowe bloki
        ostream << " {\n";
        for( unsigned rY = 0; rY < bitmapa.sy(); rY++ ){//wypsujemy wiersze w blokach
            ostream << "  {";
            for(unsigned rZ = 0; rZ < bitmapa.sz(); rZ++ ){
                ostream << bitmapa(rX,rY,rZ);
                if(rZ+1<bitmapa.sz()) ostream << ",";
            }
            ostream << "}";
            if(rY+1<bitmapa.sy()) ostream << ",";
            ostream <<"\n";
        }
        ostream << " }";
        if(rX+1<bitmapa.sx()) ostream << ",";
        ostream <<"\n";
    }
    ostream << "}";
    return ostream;
}

/*Kopiowanie bitampy*/
BitmapaExt copy(const Bitmapa& bm){
    BitmapaExt copy(bm.sx(),bm.sy(),bm.sz());
    copy = bm;
    return copy;
}


/*-----------------------Potomkowie klasy Przeksztalecnie-----------------*/

/**Zamiana pikseli czarnych na biale i viceversa*/
class Inwersja:public Przeksztalcenie{
public:
    Inwersja(){};

    //funkcja przeksztalcajaca
    void przeksztalc(Bitmapa& bm) override{
        for(unsigned long long i = 0; i < (bm.sx()*bm.sy()*bm.sx()); i++ ) // dla kazdego piksela
            bm(0,0,i) = !bm(0,0,i);// zamina koloru.
    }

    //dekstruktor
    ~Inwersja(){}
};

/**Przez piksel brzegowy obrazu rozumiemy piksel czarny, którego jednym z sąsiadów jest piksel biały. Operacja erozji polega na tym, że najpierw 
 * lokalizowane są wszystkie piksele brzegowe w danym obrazie, a następnie ich kolor jest ustawiany na biały.*/
class Erozja:public Przeksztalcenie{
public:
    Erozja(){};

    //funkcja przeksztalcajaca
    void przeksztalc(Bitmapa& bm) override{
       /*Znajdumemy punkty podantne na erozje*/
        Trojka* doDylatacji = new Trojka[bm.sx()*bm.sy()*bm.sz()];
        unsigned long long ilosDoErozji = 0;
        Trojka sasiedzi[6];
        int liczbaSasiadow ;
        int sX,sY,sZ;
        for(unsigned x=0; x<bm.sx() ;x++){//dla kazdego punktu
            for(unsigned y=0; y<bm.sy(); y++){
                for(unsigned z=0; z<bm.sz(); z++){
                    //std::cout<< "Punkt" << "x: " << x << " y: " << y << " z: " << z << "\n";
                    if(bm(x,y,z)==1){//jesli czarny
                        otoczenie(bm,x,y,z,liczbaSasiadow,sasiedzi);//znajedumy sasiadow
                        for(int sasiad = 0; sasiad < liczbaSasiadow; sasiad++){//dla kazdego sasiada
                            sX = sasiedzi[sasiad].x; sY = sasiedzi[sasiad].y; sZ = sasiedzi[sasiad].z;
                            //std::cout<< "Punkt" << "x: " << x << " y: " << y << " z: " << z << "\n";
                            //std::cout<< "Sasiad" << "x: " << sX << " y: " << sY << " z: " << sZ << "\n";
                            if(bm(sX,sY,sZ)==0){//jesli jakis sasiad bialy
                                doDylatacji[ilosDoErozji++] = Trojka(x,y,z);//to do erozji
                                break;//idzemy dalej
                            }
                        }
                    }
                }
            }
        }
        for(unsigned long long i =0; i<ilosDoErozji; i++){//dla kazdego punktu do erozji

            sX = doDylatacji[i].x; sY = doDylatacji[i].y; sZ = doDylatacji[i].z;
            //std::cout<< "Erozja x: " << sX << " y: " << sY << " z: " << sZ << "\n";
            bm(sX,sY,sZ) = false;//zmien kolor na bialy
        }
        delete[] doDylatacji;//zwalniamy pamiec

    }
};

class Dylatacja:public Przeksztalcenie{
public:
    Dylatacja(){};

    //funkcja przeksztalcajaca
    void przeksztalc(Bitmapa& bm) override{
       /*Znajdumemy punkty podantne na erozje*/
        Trojka* doDylatacji = new Trojka[bm.sx()*bm.sy()*bm.sz()];
        unsigned long long ilosDoDylatacji = 0;
        Trojka sasiedzi[6];
        int liczbaSasiadow ;
        int sX,sY,sZ;
        for(unsigned x=0; x<bm.sx() ;x++){//dla kazdego punktu
            for(unsigned y=0; y<bm.sy(); y++){
                for(unsigned z=0; z<bm.sz(); z++){
                    //std::cout<< "Punkt" << "x: " << x << " y: " << y << " z: " << z << "\n";
                    if(bm(x,y,z)==0){//jesli bialy
                        otoczenie(bm,x,y,z,liczbaSasiadow,sasiedzi);//znajedumy sasiadow
                        for(int sasiad = 0; sasiad < liczbaSasiadow; sasiad++){//dla kazdego sasiada
                            sX = sasiedzi[sasiad].x; sY = sasiedzi[sasiad].y; sZ = sasiedzi[sasiad].z;
                            //std::cout<< "Punkt" << "x: " << x << " y: " << y << " z: " << z << "\n";
                            //std::cout<< "Sasiad" << "x: " << sX << " y: " << sY << " z: " << sZ << "\n";
                            if(bm(sX,sY,sZ)==1){//jesli jakis sasiad czarny
                                doDylatacji[ilosDoDylatacji++] = Trojka(x,y,z);//to do dylatacji
                                break;//idzemy dalej
                            }
                        }
                    }
                }
            }
        }
        for(unsigned long long i =0; i<ilosDoDylatacji; i++){//dla kazdego punktu do dylatacji

            sX = doDylatacji[i].x; sY = doDylatacji[i].y; sZ = doDylatacji[i].z;
            //std::cout<< "Erozja x: " << sX << " y: " << sY << " z: " << sZ << "\n";
            bm(sX,sY,sZ) = true;//zmien kolor na czatny
        }
        delete[] doDylatacji;//zwalniamy pamiec

    }
};


/**Operacja odwrotna do erozji*/



#endif