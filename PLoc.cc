#include "PLoc.h"
#include <string>
#include <iostream>
#include <iomanip>
#include "Coordenada.h"

using namespace std;
//Christian Camelo AW388156
PLoc::PLoc(){
    continente ="";
    pais = "";
    ciudad="";
}

PLoc::PLoc(string c,string p,string l){
    continente=c;
    pais=p;
    ciudad=l;
}

PLoc::PLoc(const PLoc &p){
        continente=p.continente;
        ciudad=p.ciudad;
        pais=p.pais;
        latitud = p.latitud;
        longitud = p.longitud;
}

PLoc::~PLoc(){
    continente = pais = ciudad="";
}

PLoc& PLoc::operator =(const PLoc &p){
    if(this!=&p){
        continente=p.continente;
        ciudad=p.ciudad;
        pais=p.pais;
        latitud = p.latitud;
        longitud = p.longitud;
    }
    return *this;
}

void PLoc::setContinente(string s){
    continente = s;
}

bool PLoc::esVacia(){
    bool a = false;
    if( (continente == "" && ciudad == "" && pais =="")||
    (latitud.getMinutos()==-1)||
    (longitud.getMinutos()==-1)||
    (latitud.getGrados()==-1)||
    (longitud.getGrados()==-1)      ){
        //cout << "Esta PLoc es vacia"<< continente << " " << ciudad << " " << pais << " //  Lat " << latitud.getGrados() << " // Lon" << longitud.getGrados() << endl;
        a =  true;//cadena nula
    }
    //cout << "Es Vacia? "<< ciudad <<" = " <<a <<endl;
    return a; 
}

bool PLoc::setLatitud(Coordenada p){
    
    bool a = false;
    
    if(p.getGrados()<91 && p.getGrados()>=0){
        if(p.getMinutos()<60 && p.getMinutos()>=0){
         if(p.getDireccion()=='N'||p.getDireccion()=='S'){
                a = true;
                latitud = p;
            }
        }
    }

    return a;
}

bool PLoc::setLongitud(Coordenada p){
    
    bool a = false;
    
    if(p.getGrados()<=180 && p.getGrados()>=0){
        if(p.getMinutos()<60 && p.getMinutos()>=0){
         if(p.getDireccion()=='O'||p.getDireccion()=='E'){
                a = true;
                longitud = p;
            }
        }
    }

    return a;
}

string PLoc::getContinente(){
    return continente;
}
string PLoc::getPais(){
    return pais;
}
string PLoc::getCiudad(){
    return ciudad;
}
Coordenada PLoc::getLatitud(){
    return latitud;
}
Coordenada PLoc::getLongitud(){
    return longitud;
}
vector<double> PLoc::getGps(){
    vector<double>a;
    a.push_back(latitud.getGps());
    a.push_back(longitud.getGps());
    //cout<<" x: "<<a[0]<< " y: "<<a[1];
    return a;
}
void PLoc::escribeInfoGps(){

    string c,p,d;
    if(continente==""){
        c="x";
    }else{
        c=continente;
    }
    if(ciudad==""){
        d="x";
    }else{
        d=ciudad;
    }
    if(pais==""){
        p="x";
    }else{
        p=pais;
    }
/*
    if(continente!=""){
        c = continente;
    }
        if(pais!=""){
        p = pais;
    }
        if(ciudad!=""){
        d = ciudad;
    }*/

    cout << c << " - " << p << " - " << d << " - " << latitud.getGps() << " - " << longitud.getGps()<<endl;
}

ostream &operator <<(ostream &os, const PLoc &p){
    string c,ps,d;
    //cout<<"escribiendo info amiga";
    if(p.continente==""){
        c="x";
    }else{
        c=p.continente;
    }
    if(p.ciudad==""){
        d="x";
    }else{
        d=p.ciudad;
    }
    if(p.pais==""){
        ps="x";
    }else{
        ps=p.pais;
    }
    cout<< c << " - " << ps << " - " << d << " - " << p.latitud << " - " << p.longitud<<endl;
    return os;
}

