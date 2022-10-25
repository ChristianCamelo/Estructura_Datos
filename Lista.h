#ifndef Lista_H
#define Lista_H

#include "PLoc.h"

using namespace std;

class Lista{

    private:

        class Nodo{
            public:
                PLoc pd;
                Nodo *next;
                Nodo *prev;
                Nodo(){
                    next = NULL;
                    prev = NULL;
                    
                }
                Nodo(PLoc p){
                        pd=p;
                        next=NULL;
                        prev=NULL;
                }
                PLoc getLocalidad(){
                    return pd;
                }
                friend ostream &operator<<(ostream &os, Nodo &n){
                    cout<<n.pd<<endl;
                    return os;
                }
        };

        Nodo *pr;
        Nodo *ul;

    public:
        //      **canonicos**
        Lista();
        //Lista(Nodo &n); <-- no lo requiere
        Lista(const Lista &l);
        ~Lista();
        Lista & operator=(const Lista &l);
        //      **metodos de instancia**
        bool esVacia();
        void leeLista(string f);
        void insertaCabeza(PLoc p);
        void insertaCOla(PLoc p);
        void insertaVectorPLoc(vector<PLoc>&v);
        void inserta(PLoc v,int i);
        bool borraCabeza();
        bool borraCola();
        bool borraCiudad(string v);
        bool borraPais(string s);
        int ciudadEnLista(string v);
        vector<PLoc> pais(string p);
        void ordenaLista();
        friend ostream &operator <<(ostream &, const Lista &);
        void escribeListaPais(string p);
};
#endif
