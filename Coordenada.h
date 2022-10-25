#ifndef Coordenada_H
#define Coordenada_H

#include <iostream>
#include <string>

using namespace std;


class Coordenada{

    friend ostream &operator << (ostream &o,const Coordenada &p);


    private:
        int grados;
        int minutos;
        char direccion;
        double gps;

    public:
        Coordenada();
        Coordenada(int g, int m, char p);
        Coordenada(const Coordenada &);
        ~Coordenada();
        Coordenada &operator = (const Coordenada &t);
        int getGrados();
        int getMinutos();
        char getDireccion();
        double getGps();
};
#endif