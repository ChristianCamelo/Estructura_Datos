import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.lang.reflect.Array;
import java.nio.Buffer;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.Queue;
import java.util.TreeSet;
import java.util.Vector;
// CHRISTIAN CAMELO ESPINAL AW388156
import javax.swing.JSpinner.ListEditor;

class Arbol{
    private class Nodo{
        PLoc pd;
        Nodo no,so,ne,se;
        Nodo(){pd=null;no=null;so=null;se=null;ne=null;}
        Nodo(PLoc p){pd=p;no=null;so=null;se=null;ne=null;}
    }
    private Nodo pr;
    public Arbol(){pr=null;}

    public boolean inserta(PLoc p){
        if(p!=null){
            if(pr==null)pr=new Nodo(p);
            else{
                //System.out.println("trato de insertar "+p);
                double ln = p.getLongitud().getGps();
                double lt = p.getLatitud().getGps();
                Nodo tmp = new Nodo(p);
                if(ln<pr.pd.getLongitud().getGps()){
                    if(lt<pr.pd.getLatitud().getGps()){
                        if(pr.so==null){pr.so=new Nodo();pr.so=tmp;}
                        else{insertNode(pr.so, p);}
                    }else{
                        if(pr.no==null){pr.no=new Nodo();pr.no=tmp;}
                        else{insertNode(pr.no, p);}
                    }
                }else{
                    if(lt<pr.pd.getLatitud().getGps()){
                        if(pr.se==null){pr.se=new Nodo();pr.se=tmp;}
                        else{insertNode(pr.se, p);}
                    }else{
                        if(pr.ne==null){pr.ne=new Nodo();pr.ne=tmp;}
                        else{insertNode(pr.ne, p);}
                    }
                }
            }
        }
        return true;
    }
    public boolean insertNode(Nodo n,PLoc p){
        boolean state=false;
        if(p!=null){
            double ln = p.getLongitud().getGps();
            double lt = p.getLatitud().getGps();
            Nodo tmp = new Nodo(p);
            if(ln<n.pd.getLongitud().getGps()){
                    if(lt<n.pd.getLatitud().getGps()){
                        if(n.so==null){n.so=new Nodo();n.so=tmp;}
                        else{insertNode(n.so, p);}
                    }else{
                        if(n.no==null){n.no=new Nodo();n.no=tmp;}
                        else{insertNode(n.no, p);}
                    }
                }else{
                    if(lt<n.pd.getLatitud().getGps()){
                        if(n.se==null){n.se=new Nodo();n.se=tmp;}
                        else{insertNode(n.se, p);}
                    }else{
                        if(n.ne==null){n.ne=new Nodo();n.ne=tmp;}
                        else{insertNode(n.ne, p);}
                    }
                }
        }return state;
    }
    public void leeArbol(String f){
        FileReader file = null;
        BufferedReader bufferedReader = null; 
        try{
            file = new FileReader(f);
            bufferedReader = new BufferedReader(file);
            String line = bufferedReader.readLine();
            while(line!=null){
                String[]info=line.split("#");
                String c = info[0];
                String p = info[1];
                String cd = info[2];

                String[]latitud = info[3].split(" ");
                int latg = Integer.parseInt(latitud[0]);
                int latm = Integer.parseInt(latitud[1]);
                char latd = latitud[2].charAt(0); 
   
                String[]longitud = info[4].split(" ");
                int longg = Integer.parseInt(longitud[0]);
                int lonm = Integer.parseInt(longitud[1]);
                char lond = longitud[2].charAt(0); 

                Coordenada CoordLatTemp = new Coordenada(latg,latm,latd);
                Coordenada CoordLonTemp = new Coordenada(longg,lonm,lond);

                PLoc locTemp = new PLoc(c,p,cd);
                locTemp.setLatitud(CoordLatTemp);
                locTemp.setLongitud(CoordLonTemp);
                if(locTemp!=null){
                    inserta(locTemp);
                }
                line = bufferedReader.readLine();
            }
        }catch(IOException e){
            System.out.println("Error my file.txt");
        }
        
    }

    public boolean esVacio(){
        boolean state = false;
        if(pr==null)state=true;
        return state;
    }

    public boolean ciudadEnArbol(String v){
        boolean state=false;
        ArrayList<String> listedNodes = new ArrayList<>();
        listedNodes = recorridoNiveles();
        for(String city : listedNodes){
            if(city.equalsIgnoreCase(v))state=true;
        }return state;
    }
    
    public ArrayList<String>recorridoNiveles(){
        ArrayList<String> nodos = new ArrayList<>();
        Queue<Nodo>queue = new LinkedList<>();
        if(pr!=null){
            queue.add(pr);
        }
        while(!queue.isEmpty()){
            Nodo tmp = queue.poll();
            nodos.add(tmp.pd.getCiudad());
                if(tmp.ne!=null)queue.offer(tmp.ne);
                if(tmp.no!=null)queue.offer(tmp.no);
                if(tmp.se!=null)queue.offer(tmp.se);
                if(tmp.so!=null)queue.offer(tmp.so);
        }
        return nodos;
    }
    
    public ArrayList<String>recorridoNiveles(String s){
        ArrayList<String> nodos = new ArrayList<>();
        Queue<Nodo>queue = new LinkedList<>();
        if(pr!=null){
            queue.add(pr);
        }
        while(!queue.isEmpty()){
            Nodo tmp = queue.poll();
            if(tmp.pd.getPais().equalsIgnoreCase(s))nodos.add(tmp.pd.getCiudad());
                if(tmp.ne!=null)queue.offer(tmp.ne);
                if(tmp.no!=null)queue.offer(tmp.no);
                if(tmp.se!=null)queue.offer(tmp.se);
                if(tmp.so!=null)queue.offer(tmp.so);
        }
        return nodos;
    }

    public PLoc busquedaPorNiveles(int x, int y){
        PLoc loc = null;
        double disMx = Double.MAX_VALUE;
        Queue<Nodo>queue = new LinkedList<>();
        if(pr!=null){
            queue.add(pr);
        }
        while(!queue.isEmpty()){
            Nodo tmp = queue.poll();
            double tmpDis = (distanceBtw(tmp.pd,x,y));
            
            if(tmpDis<disMx){
                loc = tmp.pd;
                disMx = tmpDis;
            }
                if(tmp.ne!=null)queue.offer(tmp.ne);
                if(tmp.no!=null)queue.offer(tmp.no);
                if(tmp.se!=null)queue.offer(tmp.se);
                if(tmp.so!=null)queue.offer(tmp.so);
        }
        return loc;
    }
    
    public TreeSet<String>getCiudades(PLoc p){
        String pais = p.getPais();
        TreeSet<String> tree = new TreeSet<>();
        ArrayList<String> listedNodes = new ArrayList<>();
        listedNodes = recorridoNiveles(pais);
        for(String cities : listedNodes){
            tree.add(cities);
        }
        return tree;
    }

    public PLoc busquedaLejana(String s){
        PLoc state = null;
        if(s.equalsIgnoreCase("NO")){
            state = busquedaPorNiveles(90, -180);
        }
        if(s.equalsIgnoreCase("NE")){
            state = busquedaPorNiveles(90, 180);
        }
        if(s.equalsIgnoreCase("SE")){
            state = busquedaPorNiveles(-90, 180);
        }
        if(s.equalsIgnoreCase("SO")){
            state = busquedaPorNiveles(-90, -180);
        }
        return state;
    }

    public double distanceBtw(PLoc p, int x, int y){
        double dis = 0;
        double x1 = p.getGps().get(0);
        double y1 = p.getGps().get(1);
        dis = Math.sqrt(Math.pow(x-x1,2)+Math.pow(y-y1,2));
        return dis;
    }

    public ArrayList<String> recorridoInorden(){
        ArrayList <String> cities = new ArrayList<>();
        recorridoInorden(pr,cities);
        return cities;
    }

    public void recorridoInorden(Nodo n,ArrayList<String> list){
        if(n.no!=null){recorridoInorden(n.no,list);}
        if(n.so!=null){recorridoInorden(n.so,list);}
        String city = n.pd.getCiudad();
        list.add(city);
        if(n.ne!=null){recorridoInorden(n.ne,list);}
        if(n.se!=null){recorridoInorden(n.se,list);}
    }

    public TreeSet<String>hojas(){
        TreeSet<String>hs = new TreeSet<>();
        for(String city:verificaHojas()){
            hs.add(city);
        }
        return hs;
    }


    public ArrayList<String> verificaHojas(){
        ArrayList<String> nodos = new ArrayList<>();
        Queue<Nodo>queue = new LinkedList<>();
        if(pr!=null){
            queue.add(pr);
        }
        while(!queue.isEmpty()){
            float hijos=0;
            Nodo tmp = queue.poll();
                if(tmp.ne!=null)hijos++;
                if(tmp.no!=null)hijos++;
                if(tmp.se!=null)hijos++;
                if(tmp.so!=null)hijos++;
                if(hijos==0)nodos.add(tmp.pd.getCiudad());

            if(tmp.ne!=null)queue.offer(tmp.ne);
            if(tmp.no!=null)queue.offer(tmp.no);
            if(tmp.se!=null)queue.offer(tmp.se);
            if(tmp.so!=null)queue.offer(tmp.so);
        }
        return nodos;
    }

    public TreeSet<PLoc> getContinente(String s){
        TreeSet<PLoc>loc = new TreeSet<>();
        for(PLoc city:recorridoNivelesContinente(s)){
            loc.add(city);
        }
        return loc;
    }

    public ArrayList<PLoc>recorridoNivelesContinente(String s){
        ArrayList<PLoc> nodos = new ArrayList<>();
        Queue<Nodo>queue = new LinkedList<>();
        if(pr!=null){
            queue.add(pr);
        }
        while(!queue.isEmpty()){
            Nodo tmp = queue.poll();
            if(tmp.pd.getContinente().equalsIgnoreCase(s))nodos.add(tmp.pd);
                if(tmp.ne!=null)queue.offer(tmp.ne);
                if(tmp.no!=null)queue.offer(tmp.no);
                if(tmp.se!=null)queue.offer(tmp.se);
                if(tmp.so!=null)queue.offer(tmp.so);
        }
        return nodos;
    }

    public ArrayList<PLoc>verificaPosicion(double x,double y,double r){
        double x1,x2,y1,y2;
        x1 = x-r;x2=x+r;y1=y-r;y2=y+r;
        ArrayList<PLoc> locs = new ArrayList<>();
        Queue<Nodo>queue = new LinkedList<>();
        if(pr!=null){
            queue.add(pr);
        }
        while(!queue.isEmpty()){
            Nodo tmp = queue.poll();

            if(tmp.pd.getGps().get(0) >= x1 && tmp.pd.getGps().get(0)<= x2 ){
                if(tmp.pd.getGps().get(1) >= y1 && tmp.pd.getGps().get(1)<= y2 ){          
                    locs.add(tmp.pd);
                }
            }
                if(tmp.ne!=null)queue.offer(tmp.ne);
                if(tmp.no!=null)queue.offer(tmp.no);
                if(tmp.se!=null)queue.offer(tmp.se);
                if(tmp.so!=null)queue.offer(tmp.so);
        }
        locs = ordenaArrayList(locs);
        return locs;
    }

    public ArrayList<PLoc>ordenaArrayList(ArrayList<PLoc>v){
        PLoc tmp = new PLoc();
        for(int i =0;i<v.size();i++){
            for(int j=1;j<v.size()-i;j++){
                if(v.get(j-1).getGps().get(1)<v.get(j).getGps().get(1)){
                    tmp = v.get(j);
                    v.set(j,v.get(j+1));
                    v.set(j+1,tmp);
                }
                if(v.get(j-1).getGps().get(1)==v.get(j).getGps().get(1)){
                    if(v.get(j-1).getCiudad().compareTo(v.get(j).getCiudad())>0){
                        tmp = v.get(j);
                        v.set(j,v.get(j+1));
                        v.set(j+1,tmp);
                    }
                }
            }
        }
        return v;
    }

}
//no so NODO ne se