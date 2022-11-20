#include "Lista.h"
#include "PLoc.h"
#include <math.h>
#include <fstream>
#include <array>
#include <iomanip>
#include <iostream>
//                                      Por Christian Camelo Espinal

using namespace std;

Lista::Lista(){
    pr = NULL;
    ul = NULL;
}

Lista::Lista(Lista const &l){
    ul = l.ul;
    pr = l.pr;
}

Lista::~Lista(){
    Nodo *aux =(*pr).next;
    while(aux!=NULL){
        delete (*aux).prev;
        if((*aux).next!=NULL){
                    aux->~Nodo();
        }
    }
}
Lista & Lista::operator=(const Lista &l){
    if(this!=&l){
        pr = l.pr;
        ul = l.ul;
    }
    return *this;
}
bool Lista::esVacia(){
    if(pr==NULL||ul==NULL){
        return true;
    }
    else{
        return false; 
    } 
}
vector<string>split( string separar , char separador ){   
   int inicio=0;
   int encontrado=0;
   string subcadena="";
   vector <string> elems;
   while ( encontrado >= 0) {
       encontrado = separar . find ( separador , inicio ) ;
       subcadena = separar . substr ( inicio , encontrado - inicio );
       inicio = encontrado +1;
       elems . push_back ( subcadena ) ;
   }
    return elems ;
}
void Lista::leeLista(string s){
    
 ifstream fd(s.c_str()); // ifstream es un obj tipo fichero
   string readed;
   vector<string> info;
   
   while(getline(fd,readed)){//salto de linea getline

       vector <string> info = split(readed,'#');
       
            int latg = 0;
            int latm = 0;
            char latd = 'x';
            int longg = 0;
            int lonm = 0;
            char lond = 'x'; 

            vector<string> latitud = split(info[3],' ');
            latg = stoi(latitud[0]);
            latm = stoi(latitud[1]);
            latd = latitud[2][0];

            vector<string> longitud = split(info[4],' ');
             longg = stoi(longitud[0]);
             lonm = stoi(longitud[1]);
             lond = longitud[2][0]; 

            Coordenada CoordLatTemp(latg,latm,latd);
            Coordenada CoordLonTemp(longg,lonm,lond);

            PLoc locTemp(info[0],info[1],info[2]);
            locTemp.setLatitud(CoordLatTemp);
            locTemp.setLongitud(CoordLonTemp);
            //cout<<"Agregadi datos a mapa: "<<locNoSort[((int)locNoSort.size()-1)]<<endl;
        if(!locTemp.esVacia()){
            insertaCabeza(locTemp);
        }
   }
}

void Lista::insertaCabeza(PLoc p){
    Nodo *newNode;
    if(!p.esVacia()){
        if(pr==NULL){
            newNode = new Nodo(p);
            pr = ul = newNode;
        }
        else{
            newNode = new Nodo(p);
            pr->prev=newNode;
            (*newNode).next = pr;//(*aux).pd
            pr = newNode;
        }    
    }
}

void Lista::insertaCola(PLoc p){
    Nodo *newNode;
    if(!p.esVacia()){
        if(pr==NULL){
            newNode = new Nodo(p);
            pr = ul = newNode;
        }
        else{
            newNode = new Nodo(p);
            (*ul).next = newNode;
            (*newNode).prev = ul;//(*aux).pd
            ul = newNode;
        }    
    }
}

void Lista::insertaVectorPLoc(vector<PLoc>&v){
    for(int i=0;i<(int)v.size();i++){
        insertaCola(v[i]);
    }
}
void Lista::inserta(PLoc v, int i){ 
    Nodo *newNode;
    Nodo *aux;
    bool valid = true;
    if(!esVacia())
        aux=pr;//pos en 1
    if(!v.esVacia()){//no es vaacia
        for(int j=0;j<i;j++){//movemos hasta i
            if((*aux).next!=NULL){//si hay elementos despues
                aux=(*aux).next;//nos movemos al siguiente
            }
            else{
                valid=false;//no existe la posicion
                break;
            }
        }
        if(valid==true){//llegamos
            newNode = new Nodo(v);//nuevo nodo
            Nodo *aux2 = (*aux).next;//nodo aux2 es el siguiente
            (*newNode).prev = aux;//el anterior al nuevo nodo es el aux
            if(ul!=aux){//si el auxiliar no es el ultimo
                (*newNode).next=(*aux).next;//siguiente nodo es el siguiente del anterior
                (*aux2).prev = newNode;//el anterior al siguiente es el nuevo
            }
            else if(ul==aux){//si estasmos en el ultimo
                ul=newNode;//ul es el nuevo nodo
            }
            (*aux).next = newNode;
        }
        
    }
}

bool Lista::borraCabeza(){
    Nodo *aux = pr;
    if(aux!=NULL){
        pr = (*pr).next;
        if(pr==NULL){
            ul=NULL;
        }
        delete aux;
        return true;
    }
    else {
        return false;
    }
}

bool Lista::borraCola(){
    Nodo *aux = ul;//pos en ul
    if(pr!=NULL){//si hay elementos
        ul = (*ul).prev;//ul es ul.prev
        if(ul==NULL){//si no hay elementos
            pr=NULL;//no hay lista
        }
        delete aux;//borramos el ul
        return true;
    }else{
        return false;
    }
}

bool Lista::borraCiudad(string v){
    Nodo *aux=pr; //pos en 1
    bool valid=false;
    while(aux!=NULL){
        if((*aux).getLocalidad().getCiudad()==v){//encontrado
            valid = true;//encontrado
            if(pr==aux){//si es el primero
                pr=(*aux).next;//el primero es el segundo
                delete aux;//borramos el aux
            }
            else if(ul==aux){//si es el ultimo
                ul=(*aux).prev;//el ultimo es el anterior
                delete aux;//borramos aux
            }
            else{
                Nodo *auxsig=(*aux).next;//el anterior
                Nodo *auxprev=(*aux).prev;//el sig
                (*auxsig).prev = auxprev;//previo al siguiente es anterior
                (*auxprev).next = auxsig;//siguiente al previo es siguiente
                delete aux;
            }
        }aux=(*aux).next;//pasamos al siguiente
    }
    return valid;
}

bool Lista::borraPais(string v){
    
    Nodo *aux=pr; //pos en 1
    bool valid = false;//no encntrado
    while(aux!=NULL){//mientras no sea vacia
        if((*aux).getLocalidad().getPais()==v){//encontrado
        valid=true;
            if(pr==aux){//si es el primero
                pr=(*aux).next;//el primero es el segundo
                delete aux;//borramos el aux
            }
            else if(ul==aux){//si es el ultimo
                ul=(*aux).prev;//el ultimo es el anterior
                delete aux;//borramos aux
            }
            else{
                Nodo *auxsig=(*aux).next;//el anterior
                Nodo *auxprev=(*aux).prev;//el sig
                (*auxsig).prev = auxprev;//previo al siguiente es anterior
                (*auxprev).next = auxsig;//siguiente al previo es siguiente
                delete aux;
            }
        }aux=(*aux).next;//pasamos al siguiente
    }
    return valid;
}

int Lista::ciudadEnLista(string v){
    int pos=0;
    int posr=0;
    Nodo *aux=pr;
    bool valid=false;
    while(aux!=NULL){
        if((*aux).getLocalidad().getCiudad()==v){//encontrado
            valid = true;
            posr = pos;
        }
        pos++;
        aux=(*aux).next;//pasamos al siguiente
    }
    if(valid==false){
        posr= -1;
    }
    return posr;
}

PLoc Lista::operator[](int pos){
        Nodo *aux=pr;
        bool valid = true;
        PLoc a = PLoc();
        for(int j=0;j<pos;j++){//movemos hasta i
            if((*aux).next!=NULL){//si hay elementos despues
                aux=(*aux).next;//nos movemos al siguiente
            }
            else{
                valid=false;
                break;}
        }
        if(valid==true){
            a = (*aux).getLocalidad();
        }
        return a;
}
vector<PLoc> Lista::pais(string p){
    Nodo *aux = pr;
    vector<PLoc> v;
    while(aux!=NULL){
        if(aux->getLocalidad().getPais()==p){
            v.push_back(PLoc((*aux).getLocalidad()));
        }
    }
    return v;
}
void Lista::ordenaLista(){//

    Nodo *aux = pr;
    Nodo *sig = (*aux).next;
    int tam=0;
    while(aux!=NULL){
        aux = (*aux).next;
        tam++;
    }
    /*
    if(sig!=NULL){
        if((*aux).getLocalidad().getGps()[1]>(*sig).getLocalidad().getGps()[1]){
            Nodo *tempS = (*sig).next;
            Nodo *tempA = (*aux).prev;
            
            (*sig).next = aux;
            (*sig).prev = tempA;
            (*tempS).prev = aux;
            (*aux).next = tempS;
            (*aux).prev = sig;
            (*tempA).next = sig;
        }
        else{
            *aux = (*aux).prev;
        }
    }
    */
    for(int i=0;i<tam-2;i++){
        for(int j = 0;j<tam-i-2;j++){
            if((*aux).getLocalidad().getGps()[1]>(*sig).getLocalidad().getGps()[1]){
            
            Nodo *tempS = (*sig).next;
            Nodo *tempA = (*aux).prev;
            
            (*sig).next = aux;
            (*sig).prev = tempA;
            (*tempS).prev = aux;
            (*aux).next = tempS;
            (*aux).prev = sig;
            (*tempA).next = sig;
            }
        }
    }
}

ostream &operator <<(ostream &os, const Lista&l){
    Lista::Nodo *aux = l.pr;
    int tam=0;
    while(aux!=NULL){
        os<<fixed<<setprecision(2)<<"nodo "<<tam<<": "<<aux->getLocalidad().getContinente()<<" - "
        <<aux->getLocalidad().getPais()<<" - "<<aux->getLocalidad().getCiudad()<<" - "
        <<(*aux).getLocalidad().getGps()[0]<<" - "<<(*aux).getLocalidad().getGps()[1]<<endl;
        aux = (*aux).next;
        tam++;
    }
    return os;
}
void Lista::buscaCercana(double r, double l){
    Nodo *aux=pr;
    PLoc retP=PLoc();
    double disMAX = 1000000;

    if(r==0){
        while(aux!=NULL){
            double dis = ((*aux).getLocalidad().getLongitud().getMinutos())-l;//distancia es actual menos longitud
            if(sqrt(pow(dis,2))<disMAX){//la diferencia absoluta de distancias es menor a la maxima
                disMAX = sqrt(pow(dis,2));
                retP=(*aux).getLocalidad();//actualiza la maxima
            }
        }aux=(*aux).next;
        retP.escribeInfoGps();
    }
    if(r<0){
        cout<<"EL VALOR DEL RANGO ES INCORRECTO"<<endl;
    }
    if(r>0){
        vector<PLoc>locs;
        while(aux!=NULL){
            if((*aux).getLocalidad().getLongitud().getMinutos()<r){
                locs.push_back((*aux).getLocalidad());
            }
            aux=(*aux).next;
        }//termina de almacenar las PLocs
        if(locs.size()>0){
            for(int i=0;i<(int)locs.size();i++){
                for(int j=0;j<(int)locs.size()-i-2;j++){
                    double dis1 = sqrt(pow((locs[j].getLongitud().getMinutos()-l),2));
                    double dis2 = sqrt(pow((locs[j+1].getLongitud().getMinutos()-l),2));
                    if(dis1>dis2){
                        PLoc temp = locs[j];
                        locs[j] = locs[j+1];
                        locs[j+1]=temp;
                    }
                }
            }
        }
    }
}

