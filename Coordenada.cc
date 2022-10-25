#include "Coordenada.h"

using namespace std;

Coordenada::Coordenada(){
    grados=-1;
    minutos=-1;
    direccion='X';
    gps=0;
}

Coordenada::Coordenada(int g,int m,char p){
    grados=g;
    minutos=m;
    direccion=p;
    gps=grados+(minutos/60);
    if(direccion=='S'||direccion=='O'){
        gps=gps*-1;
    }
}

Coordenada::Coordenada(const Coordenada &p){
    
    if(this!=&p){
            grados=p.grados;
            minutos=p.minutos;
            direccion=p.direccion;
            gps=p.gps;
    }
}

Coordenada::~Coordenada(){
    grados=-1;
    minutos=-1;
    direccion='X';
    gps=0;
}

Coordenada& Coordenada::operator =(const Coordenada& t){
    if(this!=&t){
            grados=t.grados;
            minutos=t.minutos;
            direccion=t.direccion;
            gps=t.gps;
    }
    return *this;
}

int Coordenada::getGrados(){
    return grados;
}
int Coordenada::getMinutos(){
    return minutos;
}
char Coordenada::getDireccion(){
    return direccion;
}
double Coordenada::getGps(){
    return gps;
}

ostream & operator <<(ostream &os, const Coordenada &c){
    os << c.grados << " " <<c.minutos<<" "<<c.direccion;
    return os;
}