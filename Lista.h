#ifndef Lista_H
#define Lista_H
//                                      Por Christian Camelo Espinal
#include "PLoc.h"

using namespace std;

class Lista{
    
    friend ostream &operator <<(ostream &, const Lista &);
    private:

        class Nodo{
            public:
                PLoc pd;
                Nodo *next;
                Nodo *prev;
                ~Nodo(){
                    delete this;
                }
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
                    PLoc p = n.getLocalidad();
                    os<<p.getContinente()<<" "<<p.getPais()<<" "<<p.getCiudad()<<" "<< p.getGps()[0] << " " << p.getGps()[1] << endl;
                    return os;
                }
        };

        Nodo *pr;
        Nodo *ul;

    public:
        //      **canonicos**
        Lista();
        //Lista(Nodo &n); <-- no lo requiere
        Lista(Lista const &l);
        ~Lista();
        Lista & operator=(const Lista &l);
        //      **metodos de instancia**
        bool esVacia();
        void leeLista(string f);
        void insertaCabeza(PLoc p);
        void insertaCola(PLoc p);
        void insertaVectorPLoc(vector<PLoc>&v);
        void inserta(PLoc v,int i);
        bool borraCabeza();
        bool borraCola();
        bool borraCiudad(string v);
        bool borraPais(string s);
        PLoc operator[](int pos);
        int ciudadEnLista(string v);
        vector<PLoc> pais(string p);
        void ordenaLista();
        void escribeListaPais(string p);
        void buscaCercana(double ,double);
};
#endif