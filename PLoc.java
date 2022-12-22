import java.text.DecimalFormat;
import java.text.DecimalFormatSymbols;
import java.util.ArrayList;
import java.util.Locale;
// CHRISTIAN CAMELO ESPINAL AW388156
public class PLoc implements Comparable<PLoc>{

    private String continente,pais,ciudad;
    private Coordenada latitud;
    private Coordenada longitud;
    private ArrayList<Double>gps;

    public PLoc(){
        continente=null;
        pais=null;
        ciudad=null;
        latitud=null;
        longitud=null;
        //System.out.println("        nuevo Ploc sin parametros lon =  "+ longitud);
        gps=new ArrayList<>();
        gps.add(null);
        gps.add(null);

    }

    public PLoc(String c,String p,String l){
        continente=c;pais=p;ciudad=l;
        latitud=null;longitud=null;
        //System.out.println("        nuevo Ploc con parametros lon =  "+ longitud+this);;
        gps=new ArrayList<>();
        gps.add(null);
        gps.add(null);
    }

    public boolean esVacia(){
        boolean a = false;
        if((continente == "" && ciudad == "" && pais =="")||
        (latitud.getMinutos()==-1)||
        (longitud.getMinutos()==-1)||
        (latitud.getGrados()==-1)||
        (longitud.getGrados()==-1)){
            a =  true;//cadena nula
    }
    return a; 
    }

    public boolean setLatitud(Coordenada p){
        boolean a = false;
        if(p.getGrados()<91 && p.getGrados()>=0){
            if(p.getMinutos()<60 && p.getMinutos()>=0){
             if(p.getDireccion()=='N'||p.getDireccion()=='S'){
                if(latitud==null){
                    a = true;
                    latitud = p;
                    gps.set(0, p.getGps());
                    }    
                }
            }
        }
        return a;
    }

    public boolean setLongitud(Coordenada p){
        boolean a = false;
        //System.out.println("        compararemos Ploc con "+p+" para guardar una longitud"+this);
        if((p.getGrados()<181 && p.getGrados()>=0)&&
            (p.getMinutos()<60 && p.getMinutos()>=0)&&
             (p.getDireccion()=='O'||p.getDireccion()=='E')){
                if(longitud==null){
                    a = true;
                    longitud = p;
                    //System.out.println("        la longitud desde Ploc es ahora  "+ longitud+this);
                    gps.set(1, p.getGps());
                }
        }else{
            //System.out.println("    Imposible modificar"+this+" no es valido "+p);
        }
        return a;
    }
    
    public int compareTo(PLoc o) {
       int state=10;
        if(!o.esVacia()){
            Coordenada readedLon = new Coordenada();
            readedLon = o.getLongitud();
            if(longitud.getGps()<readedLon.getGps()){state=-1;}
            if(longitud.getGps()>readedLon.getGps()){state=1;}
            else{
                int dis = ciudad.compareToIgnoreCase(o.ciudad);
                if(dis<0){state=-1;}
                if(dis>0){state=1;}
                else{state=0;}
            }
       }
        return state;
    }

    public String getContinente(){return continente;}
    public String getPais(){return pais;}
    public String getCiudad(){return ciudad;}
    public Coordenada getLatitud(){return latitud;}
    public Coordenada getLongitud(){
        //System.out.println("    Devuelvo desde PLoc "+ longitud+this);
        return longitud;}
    public ArrayList<Double>getGps(){return gps;}

    public void escribeInfoGrados(){
        String c,p,d;
        if(continente==null){c="x";}else{c=continente;}
        if(ciudad==null){d="x";}else{d=ciudad;}
        if(pais==null){p="x";}else{p=pais;}
        System.out.println(c+" - "+p+" - "+d+" - "+
        latitud.getGrados()+" "+latitud.getMinutos()+" "+latitud.getDireccion()+" - "+
        longitud.getGrados()+" "+longitud.getMinutos()+" "+longitud.getDireccion());
    }

    private String toFormat(double a){
        Locale formato = new Locale("en");
        DecimalFormatSymbols chars=new DecimalFormatSymbols(formato);
        DecimalFormat formatoNew=new DecimalFormat("0.00",chars);
        return formatoNew.format(a);
    }

    public void escribeInfoGps(){
        String c,p,d;
        if(continente==null){c="x";}else{c=continente;}
        if(ciudad==null){d="x";}else{d=ciudad;}
        if(pais==null){p="x";}else{p=pais;}
        System.out.println(c+" - "+p+" - "+d+" - "+
        toFormat(latitud.getGps())+" - "+
        toFormat(longitud.getGps()));
    }



}