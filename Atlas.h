#ifndef Atlas_H
#define Atlas_H

#include "PLoc.h"
#include <vector>

using namespace std;

class Atlas{
    
    friend ostream & operator << (ostream &, Atlas &);

    private:
        vector<vector<PLoc> > mapa;
        vector<PLoc> locNoSort;

    public:
        Atlas();
        ~Atlas();
        Atlas &operator = (const Atlas &a);
        bool setLocalidad(PLoc &p);
        void leeAtlas(string f);
        PLoc consulta(int f, int c);
        vector<PLoc> getLocalidades();
        vector<PLoc> getlocNoSort();
        string consultaAtlas(PLoc &f);
        void muestraAtlasParcial(PLoc &f, int n);
};

#endif