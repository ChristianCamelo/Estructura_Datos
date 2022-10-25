#ifndef Lista_H
#define Lista_H

#include "PLoc.h"
class Lista{

    private:

        class Nodo{
            public:
                PLoc pd;
                Nodo *next;
                Nodo *prev;
                Nodo();
                Nodo(PLoc p);
                PLoc getLocalidad();
                friend ostream &operator<<(ostream &os, Nodo &n);
        }

        Nodo *pr
        Nodo *ul;

    public:


};
#endif