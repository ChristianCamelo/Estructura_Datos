#ifndef PLoc_H
#define PLoc_H

#include <string>
#include <vector>
#include "Coordenada.h"
  

using namespace std;

class PLoc{

    friend ostream& operator<<(ostream &os, const PLoc &p);

    private:
        string continente;
        string pais;
        string ciudad;
        Coordenada latitud;
        Coordenada longitud;

    public:
        PLoc();
        PLoc(string c,string p,string l);
        PLoc(const PLoc&);
        ~PLoc();
        PLoc &operator = (const PLoc &p);
        bool esVacia();
        bool setLatitud(Coordenada p);
        bool setLongitud(Coordenada p);
        string getContinente();
        string getPais();
        string getCiudad();
        Coordenada getLatitud();
        Coordenada getLongitud();
        vector<double> getGps();
        void escribeInfoGps();
        void setContinente(string s);

};
#endif