#include "Atlas.h"
#include "PLoc.h"
#include <fstream>
#include <string>
 
using namespace std;

Atlas::Atlas(){
   for(int i=0;i<181;i++){
       vector<PLoc>v1;
       for(int j=0;j<361;j++){
           PLoc Ploctmp;
           v1.push_back(Ploctmp);
       }
       mapa.push_back(v1);
   }
}
Atlas::~Atlas(){
    mapa.clear();
}

Atlas& Atlas::operator=(const Atlas &a){
    if(this!=&a){
        mapa=a.mapa;
    }
    return *this;
}
bool Atlas::setLocalidad(PLoc &f){
 
   char posXdir = f.getLatitud().getDireccion();
   char posYdir = f.getLongitud().getDireccion();
   int posX=-1;
   int posY=-1;
   bool status = false;

    if(!f.esVacia()){
        if(posXdir=='N'){
            posX = 90 + (f.getLatitud().getGrados());
        }
        else if(posXdir=='S'){
            posX = 90 - (f.getLatitud().getGrados());
        }
        if(posYdir=='O'){
             posY = 180 - (f.getLongitud().getGrados());
        }
        else if(posYdir=='E'){
            posY = 180 + (f.getLongitud().getGrados());
        }
        //cout << "verificando pos X "<<posX << " por Y " << posY << mapa[posX][posY].getCiudad() << endl;
        if(mapa[posX][posY].esVacia()){
            //cout<< mapa[posX][posY].getCiudad() <<" vacia as PER MAPA "<<endl;
            mapa[posX][posY] = f;
            status=true;
        }
    }
    //cout << "X=" << posX << " // Y=" << posY<< endl ; 

   return status;
}
//devuelve 5 cadenas 3 de strings 2 de posiciones lat lon
vector<string>split( string separar , char separador ) {   
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
//devuelve 5 cadenas 3 de strings 2 de posiciones lat lon
void Atlas::leeAtlas(string f){

   ifstream fd(f.c_str()); // ifstream es un obj tipo fichero
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
 
            if(setLocalidad(locTemp)){
                //cout<<"Se agrego al ATLAS: "<<locTemp<<endl;
                locNoSort.push_back(locTemp);
            }
            //cout<<"Agregadi datos a mapa: "<<locNoSort[((int)locNoSort.size()-1)]<<endl;

   }
}

vector<PLoc> Atlas::getlocNoSort(){
    return locNoSort;
}

PLoc Atlas::consulta(int f,int c){
    PLoc locTemp;
        if((f<=180&&f>=0)&&(c>=0&&c<=360)){
            locTemp = mapa[f][c];
        }
    return locTemp;
}
vector<PLoc> Atlas::getLocalidades(){
    vector<PLoc>locOcup;
    for(int i=0;i<181;i++){
        for(int j=0;j<361;j++){
            if(!mapa[i][j].esVacia())
            locOcup.push_back(mapa[i][j]);
        }
    }
    return locOcup;
}
string Atlas::consultaAtlas(PLoc &f){
    
        string name="INEXISTENTE";

        PLoc locTemp = f;

        int posX=-1;
        int posY=-1;
        char posXdir = locTemp.getLatitud().getDireccion();
        char posYdir = locTemp.getLongitud().getDireccion();
        
        if(posXdir=='N'){
            posX = 90 + (f.getLatitud().getGrados());
        }
        else if(posXdir=='S'){
            posX = 90 - (f.getLatitud().getGrados());
        }
        if(posYdir=='O'){
             posY = 180 - (f.getLongitud().getGrados());
        }
        else if(posYdir=='E'){
            posY = 180 + (f.getLongitud().getGrados());
        }
        //cout << posX << "   " << posY <<endl;
        if(!mapa[posX][posY].esVacia()){
        name = mapa[posX][posY].getCiudad();
        }
    return name;
}

void Atlas::muestraAtlasParcial(PLoc &f,int n){
        //cout<<"mostrando parcial"<<endl;
        
        bool existent = true;
        int posX=-1;
        int posY=-1;
        char posXdir = f.getLatitud().getDireccion();
        char posYdir = f.getLongitud().getDireccion();
        
        if(posXdir=='N'){
            posX = 90 + (f.getLatitud().getGrados());
        }
        else if(posXdir=='S'){
            posX = 90 - (f.getLatitud().getGrados());
        }
        if(posYdir=='O'){
             posY = 180 - (f.getLongitud().getGrados());
        }
        else if(posYdir=='E'){
            posY = 180 + (f.getLongitud().getGrados());
        }

    //cout<<"mostrando parcial en X "<< posX <<" Y " << posY<<endl;
    if(n<0||posX<0||posX>181||posY<0||posY>361){
        existent = false;
    }

    //cout<<"existe?"<< existent <<endl;
    //int maxX,maxY = (2*n)+1;

    int limiteSupLat = posX+n;
    int limiteInfLat = posX-n;
    int limiteSupLon = posY+n;
    int limiteInfLon = posY-n;

    //cout<<"Limite latarriba "<< limiteInfLat <<" limite latabajo " << limiteSupLat <<endl;
    //cout<<"Limite lonizq "<< limiteInfLon <<" limite londere " << limiteSupLon <<endl;

    if(existent){
        for(int i=limiteInfLat;i<=limiteSupLat;i++){//barrido
            for(int j=limiteInfLon;j<=limiteSupLon;j++){//barrido
                if(i>0||i<181){//en rango X caso 1
                    if(j>0||j<361){//en rango Y caso 1
                        if(!mapa[i][j].esVacia()||mapa[i][j].getCiudad()!="")
                            cout << mapa[i][j].getCiudad()[0];
                        else{
                            cout << ".";
                        }
                    }
                    else{
                        cout <<".";
                    }
                }
                else{
                    cout <<".";
                }
            }
            cout<<endl;
        }
    }
    else{
        cout << "NO ES DE ESTE PLANETA";
    }

}


ostream & operator<<(ostream &o, Atlas &a){
    vector<vector<PLoc> > mapTemp;
    mapTemp=a.mapa;
    for(int i=0;i<181;i++){//barrido
        for(int j=0;j<361;j++){//barrido
                    if(mapTemp[i][j].getCiudad()!=""){
                            cout << mapTemp[i][j].getCiudad()[0];
                    }
                    else{
                            cout << ".";
                        }
            }    cout<<endl;
        }
    return o;
}
