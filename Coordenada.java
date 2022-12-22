public class Coordenada{
// CHRISTIAN CAMELO ESPINAL AW388156
    private int grados;
    private int minutos;
    private char direccion;
    private double gps;

    public Coordenada(){
        grados =-1;minutos=-1;direccion='x';gps=-1;
    }

    public Coordenada(int g, int m, char p){
        grados=g;minutos=m;direccion=p;
        gps = grados +(minutos/60.0);
        if(direccion=='S'||direccion=='O')gps=gps*-1;
    }

    public int getGrados(){
        //System.out.println("            Devuelvo grados desde Coor "+grados);
        return grados;}
    public int getMinutos(){return minutos;}
    public char getDireccion(){return direccion;}
    public double getGps(){
        //System.out.println("            Devuelvo Gps desde coord"+gps);
        return gps;}
}