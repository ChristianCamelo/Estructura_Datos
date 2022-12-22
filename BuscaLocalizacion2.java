import java.lang.reflect.Array;
import java.util.*;

class  BuscaLocalizacion2{

    static public void main(String[]args){

        String name="x";
        double latitud=0;
        double longitud=0;
        double rango=0;
        String pais="x";
        
        if(args.length>0){
            name=args[0];
            Arbol arbol = new Arbol();
            arbol.leeArbol(name);
            if(args.length==4){
                latitud=Double.parseDouble(args[1]);
                longitud=Double.parseDouble(args[2]);
                rango=Double.parseDouble(args[3]);
                ArrayList<PLoc> locs = new ArrayList<>();
                locs = arbol.verificaPosicion(latitud,longitud,rango);
                if(locs.size()!=0){
                    for(int i =0;i<locs.size();i++){
                        locs.get(i).escribeInfoGps();
                    }
                }else{System.out.println("NO HAY SALIDA");}
            } 
            if(args.length==2){
                pais=args[1];
                ArrayList<String>locs = new ArrayList<>();
                locs = arbol.recorridoNiveles(pais);
                System.out.print(pais+" ("+locs.size()+")"+": ");

                String tmp="";
                for(int i =0;i<locs.size();i++){
                    for(int j=1;j<locs.size()-i;j++){
                        if(locs.get(j-1).compareTo(locs.get(j))>0){
                            tmp = locs.get(j);
                            locs.set(j,locs.get(j+1));
                            locs.set(j+1,tmp);
                        }
                    }
                }
                for(int i = 0;i<locs.size();i++){
                    if(i!=locs.size()-1){
                        System.out.print(locs.get(i)+" - ");
                    }
                    else{
                        System.out.println(locs.get(i));
                    }
                }
            }
        }
    }

}