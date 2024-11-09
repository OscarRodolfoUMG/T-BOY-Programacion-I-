#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <cstring>
using namespace std;
#define ARRIBA 72
#define IZQUIERDA 75
#define DERECHA 77
#define ABAJO 80
#define ENTER 13
#define SALTOD 'd'
#define SALTOI 'a'
#define BUSCAR 's'

//VARIABLES GLOBALES
                    //VARIABLES JUGADOR 1
char jugador1_1[]={' ','@',' ',0};
char jugador1_2[]={'#','H','#',0};
char jugador1_3[]={' ','H',' ',0};
char jugador1_4[]={'#',' ','#',0};

char explocion_l1[]={' ','x',' ',0};
char explocion_l2[]={'x','x','x',0};
char explocion_l3[]={'X','x','X',0};
char explocion_l4[]={' ','x',' ',0};

char explocion_r1[]={'x',' ','x',0};
char explocion_r2[]={' ',' ',' ',0};
char explocion_r3[]={' ',' ',' ',0};
char explocion_r4[]={'x',' ','x',0};

char explocion_s1[]={' ',' ',' ',0};
char explocion_s2[]={' ',' ',' ',0};
char explocion_s3[]={' ','x',' ',0};
char explocion_s4[]={'x','x','x',0};

char borrar_jugador1[]={' ',' ',' ',0};

                    //VARIABLES ENEMIGOS
char enemigo_l1[]={' ','@',' ',0};
char enemigo_l2[]={'@','@','@',0};
char enemigo_l3[]={' ','@',' ',0};

char romper_enemigo_l1[]={' ','#',' ',0};
char romper_enemigo_l2[]={'#','#','#',0};
char romper_enemigo_l3[]={' ','#',' ',0};

char romper_enemigo_r1[]={'#',' ','#',0};
char romper_enemigo_r2[]={' ',' ',' ',0};
char romper_enemigo_r3[]={'#',' ','#',0};

char eliminar_enemigo[]={' ',' ',' ',0};

        //VARIABLES GENERALES
int Num_vidas_p1=3;             //DEFINE NUMERO DE VIDAS
int Corazones_p1=3;             //DEFINE CANTIDAD DE SALUD
int puntuacion_p1=0;            //DEFINE INICIO DE LA PUNTUACION DEL JUGADOR 1
int x_p1=9;                     //VARIABLES POR DEFECTO PARA JUGADOR 1; x=9,y=49 INICIO DEL RECORRIDO
int y_p1=49;
bool Activo=false;              //CAIDA DEL JUGADOR ENTRE PISOS
int f=10;                       //DURACION CAIDA DEL JUGADOR ENTRE PISOS
bool saltod_on=false;           //SALTO A LA DERECHA DESACTIVADO
bool saltoi_on=false;           //SALTO A LA IZQUIERDA DESACTIVADO
int cs1=0,cs2=0,cs3=0;          //DIRECCION DE SALTO APLICADO EN AMBOS CASOS
bool unico=false;

int cc=1,xr,yr;                 //UBICACION ALEATORIA DE PUERTA SECRETA

int x_b1=65,y_b1=10;            //VARIABLES ENEMIGOS BARRILES
int x_b2=65,y_b2=10;
int x_b3=65,y_b3=10;
int x_b4=65,y_b4=10;
int x_b5=65,y_b5=10;
int t=0;                       //VELOCIDAD DEL BARRIL

int x_mm=81,y_mm=5;         //UBICACION DEL MONSTRUO
bool mover_mm=false;        //MOVIMIENTO DEL MONSTRUO
bool mover_mm2=false;

int x_rabbit=67;            //UBICACION CONEJO
int y_rabbit=6;

bool finA=false;            //BOOLEANO FINAL RECORRIDO BARRIL
bool finB=false;
bool finC=false;
bool finD=false;
bool finE=false;
bool inicioA=false;         //BOOLEANO INICIO RECORRIDO BARRIL
bool inicioB=false;
bool inicioC=false;
bool inicioD=false;
bool inicioE=false;
bool dw1=true;              //BOOLEANOS BARRIL DESCIENDE
bool dg1=true;
bool dw2=true;
bool dg2=true;
bool dw3=true;
bool dg3=true;
bool dw4=true;
bool dg4=true;
bool dw5=true;
bool dg5=true;

//FUNCIONES GLOBALES
void gotoxy(int x,int y);
void mover_enemigo1();
void pintar_plataforma();
void mostrar_escalera();
void mostrar_salud();
void Score(int x,int y);
int prototipo(int &x, int &y, bool &dw, bool &dg, bool &fin);
int impacto(int &x,int &y,bool &dw,bool &dg);

struct Partida{             //ESTRUTURA DE DATOS USUARIO
    char nombre[20];
    int puntaje;
    int vidas;
    int salud;
}partidas[2];

//FUNCIONES ALAMACENAMIENTO DE DATOS
int eleccion(const char titulo[], const char *opciones[], int n);   //DIRIGE FLECHA MENU
void mennu();                                                       //MENU DE OPCIONES
void Nueva_partida();                                               //MENU DE NUEVA PARTIDA
void Newprofile();                                                  //NUEVO JUEGO
void Continuar();                                                   //CONTINUAR PARTIDA

void escritura(int x,int ubicacion, int &dato);                     //INSERTAR ALMACENAMIENTO
void cargardatos(int x,int ubicacion, int &dato);                   //CARGAR VARIABLES DEL SISTEMA
void Puntuaciones();                                                //MENU PUNTUACIONES
void limpiar(int x,int y);                                          //LIMPIA MENU
int slot=0;                                                         //CASILLA PARA GUARDAR
bool nuevaentrada=false;                                            //BOOLEANO PARA INGRESAR AL JUEGO
bool startg=true;                                                   //BOOLEANO SALIR DEL MENU
bool salir_del_juego=false;                                         //BOOLEANO SALIR DEL JUEGO

bool game_over=false;               //FIN DEL JUEGO
bool game_start=false;              //EJECUCION DEL JUEGO
bool level_complete=false;          //NIVEL COMPLETADO
int Nivel=1;                        //NUMERO DE NIVEL
int j=1;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void pintar_rabbit()                                        //FUNCION PARA DIBUJAR AL CONEJO
{
    gotoxy(x_rabbit,y_rabbit);  printf("X  X");
    gotoxy(x_rabbit,y_rabbit+1);printf("(..)");
    gotoxy(x_rabbit,y_rabbit+2);printf("()()");
}
void borrar_rabbit()                                        //FUNCION PARA BORRAR EL CUERPO DEL CONEJO
{
    gotoxy(x_rabbit,y_rabbit);  printf("    ");
    gotoxy(x_rabbit,y_rabbit+1);printf("    ");
    gotoxy(x_rabbit,y_rabbit+2);printf("    ");
}
void pintar_jugador1(void){                                 //FUNCION PARA DIBUJAR AL JUGADOR 1
        gotoxy(x_p1,y_p1);puts(jugador1_1);
        gotoxy(x_p1,y_p1+1);puts(jugador1_2);
        gotoxy(x_p1,y_p1+2);puts(jugador1_3);
        gotoxy(x_p1,y_p1+3);puts(jugador1_4);
}
void eliminar_jugador(void){                                //BORRA CUERPO DEL JUGADOR 1
        gotoxy(x_p1,y_p1);puts(borrar_jugador1);
        gotoxy(x_p1,y_p1+1);puts(borrar_jugador1);
        gotoxy(x_p1,y_p1+2);puts(borrar_jugador1);
        gotoxy(x_p1,y_p1+3);puts(borrar_jugador1);
}
void Explotar()                                             //ANIMACION EXPLOSION CUERPO JUGADOR 1
{
        gotoxy(x_p1,y_p1);puts(explocion_l1);
        gotoxy(x_p1,y_p1+1);puts(explocion_l2);
        gotoxy(x_p1,y_p1+2);puts(explocion_l3);
        gotoxy(x_p1,y_p1+3);puts(explocion_l4);
        Sleep(60);

        gotoxy(x_p1,y_p1);puts(explocion_r1);
        gotoxy(x_p1,y_p1+1);puts(explocion_r2);
        gotoxy(x_p1,y_p1+2);puts(explocion_r3);
        gotoxy(x_p1,y_p1+3);puts(explocion_r4);
        Sleep(60);

        gotoxy(x_p1,y_p1);puts(explocion_s1);
        gotoxy(x_p1,y_p1+1);puts(explocion_s2);
        gotoxy(x_p1,y_p1+2);puts(explocion_s3);
        gotoxy(x_p1,y_p1+3);puts(explocion_s4);
        Sleep(60);

        pintar_jugador1();
        f=10;
}
void pintar_enemigo3(int x, int y){                         //PINTAR CUERPO DE BARRIL
        gotoxy(x,y);  puts(enemigo_l1);
        gotoxy(x,y+1);puts(enemigo_l2);
        gotoxy(x,y+2);puts(enemigo_l3);
}
void borrar_enemigo3(int x, int y){                         //BORRA CUERPO BARRIL
        gotoxy(x,y);  puts(eliminar_enemigo);
        gotoxy(x,y+1);puts(eliminar_enemigo);
        gotoxy(x,y+2);puts(eliminar_enemigo);
}
void choque_enemigo3(int x,int y,bool &dw,bool &dg)         //ANIMACION CHOQUE BARRIL
{
        gotoxy(x,y);  puts(romper_enemigo_l1);
        gotoxy(x,y+1);puts(romper_enemigo_l2);
        gotoxy(x,y+2);puts(romper_enemigo_l3);
        Sleep(60);

        gotoxy(x,y);  puts(romper_enemigo_r1);
        gotoxy(x,y+1);puts(romper_enemigo_r2);
        gotoxy(x,y+2);puts(romper_enemigo_r3);
        Sleep(60);

        borrar_enemigo3(x,y);
        dw=true;dg=true;
}
void mostrar_salud(){                                       //FUNCION QUE MUESTRA VIDA Y SALUD DEL PERSONAKE
    gotoxy(62,1);printf("VIDAS  x%d",Num_vidas_p1);         //MUESTRA "VIDAS x3" POR EJEMPLO

    gotoxy(74,1);printf("SALUD");                           //MUESTRA LA PALABRA SALUD
    gotoxy(80,1);printf("     ");                           //BORRA LOS CORAZONES
    for(int i=0;i<Corazones_p1;i++){
        gotoxy(80+i,1);printf("%c",3);                      //PINTA EL CARACTER DEL CORAZON
    }
    gotoxy(37,1);printf("NIVEL  %d",Nivel);

    if(startg==true && salir_del_juego==false)              //CONDICION PARA MOSTRAR EL NOMBRE DEL USUARIO
    {
    }else{
    ifstream fentrada("caset.bin",ios::in | ios::binary);
    fentrada.read(reinterpret_cast<char *>(&partidas[slot]),sizeof(Partida));
    gotoxy(37,3);cout<<partidas[slot].nombre;
    fentrada.close();
    }
}
void pintar_monstruo()                                                  //DIBUJA AL MONSTRUO DE LA ULTIMA PLATAFORMA
{                                                                       //CUERPO HACIA LA DERECHA
    gotoxy(x_mm,y_mm);  printf("%c%c%c%c%c%c%c", 32,219,219,219,219, 32, 32);  //CUERPO MOUNSTRO PLATAFORMA #4
    gotoxy(x_mm,y_mm+1);printf("%c%c%c%c%c%c%c",219,219,219,219,219,219, 32);
    gotoxy(x_mm,y_mm+2);printf("%c%c%c%c%c%c%c", 32,219,219,219,219,219, 32);
    gotoxy(x_mm,y_mm+3);printf("%c%c%c%c%c%c%c", 32, 32,219,219,219, 32, 32);
    gotoxy(x_mm,y_mm+4);printf("%c%c%c%c%c%c%c",219,219,219,219, 32, 32,219);
    gotoxy(x_mm,y_mm+5);printf("%c%c%c%c%c%c%c", 32,219,219,219, 32, 32,219);
    gotoxy(x_mm,y_mm+6);printf("%c%c%c%c%c%c%c", 32,219,219,219, 32,219, 32);
    gotoxy(x_mm,y_mm+7);printf("%c%c%c%c%c%c%c",219,219,219,219,219, 32, 32);
}
void pintar_monstruo2()                                                 //DIBUJA AL MONSTRUO DE LA ULTIMA PLATAFORMA
{                                                                       //CUERPO HACIA LA IZQUIERDA
    gotoxy(x_mm,y_mm);  printf("%c%c%c%c%c%c%c", 32, 32,219,219,219,219, 32);  //CUERPO MOUNSTRO PLATAFORMA #4
    gotoxy(x_mm,y_mm+1);printf("%c%c%c%c%c%c%c", 32,219,219,219,219,219,219);
    gotoxy(x_mm,y_mm+2);printf("%c%c%c%c%c%c%c", 32,219,219,219,219,219, 32);
    gotoxy(x_mm,y_mm+3);printf("%c%c%c%c%c%c%c", 32, 32,219,219,219, 32, 32);
    gotoxy(x_mm,y_mm+4);printf("%c%c%c%c%c%c%c",219, 32, 32,219,219,219,219);
    gotoxy(x_mm,y_mm+5);printf("%c%c%c%c%c%c%c",219, 32, 32,219,219,219, 32);
    gotoxy(x_mm,y_mm+6);printf("%c%c%c%c%c%c%c", 32,219, 32,219,219,219, 32);
    gotoxy(x_mm,y_mm+7);printf("%c%c%c%c%c%c%c", 32, 32,219,219,219,219,219);
}
void borrar_monstruo()                                                  //BORRA CUERPO DEL MONSTRUO
{
    gotoxy(x_mm,y_mm);  printf("       ");
    gotoxy(x_mm,y_mm+1);printf("       ");
    gotoxy(x_mm,y_mm+2);printf("       ");
    gotoxy(x_mm,y_mm+3);printf("       ");
    gotoxy(x_mm,y_mm+4);printf("       ");
    gotoxy(x_mm,y_mm+5);printf("       ");
    gotoxy(x_mm,y_mm+6);printf("       ");
    gotoxy(x_mm,y_mm+7);printf("       ");
}
void explotar_monstruo()                                                //ANIMACION EXPLOSION DEL MONSTRUO
{
        gotoxy(x_mm,y_mm);  printf("   +   ");
        gotoxy(x_mm,y_mm+1);printf("   +   ");
        gotoxy(x_mm,y_mm+2);printf("  +++  ");
        gotoxy(x_mm,y_mm+3);printf(" +++++ ");
        gotoxy(x_mm,y_mm+4);printf(" +++++ ");
        gotoxy(x_mm,y_mm+5);printf("  +++  ");
        gotoxy(x_mm,y_mm+6);printf("   +   ");
        gotoxy(x_mm,y_mm+7);printf("   +   ");
        Sleep(80);

        gotoxy(x_mm,y_mm);  printf("   +   ");
        gotoxy(x_mm,y_mm+1);printf("   +   ");
        gotoxy(x_mm,y_mm+2);printf(" +   + ");
        gotoxy(x_mm,y_mm+3);printf("++   ++");
        gotoxy(x_mm,y_mm+4);printf("++   ++");
        gotoxy(x_mm,y_mm+5);printf(" +   + ");
        gotoxy(x_mm,y_mm+6);printf("   +   ");
        gotoxy(x_mm,y_mm+7);printf("   +   ");
        Sleep(80);

        gotoxy(x_mm,y_mm);  printf("   +   ");
        gotoxy(x_mm,y_mm+1);printf(" +   + ");
        gotoxy(x_mm,y_mm+2);printf("+     +");
        gotoxy(x_mm,y_mm+3);printf("+     +");
        gotoxy(x_mm,y_mm+4);printf("+     +");
        gotoxy(x_mm,y_mm+5);printf("+     +");
        gotoxy(x_mm,y_mm+6);printf(" +   + ");
        gotoxy(x_mm,y_mm+7);printf("   +   ");

        Sleep(80);
}
void gotoxy(int x,int y){                          //FUNCION GOTOXY DIRIGUE EL CURSOR A UNA COORDENADA EN PANTALLA
    HANDLE hcon;
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X=x;
    dwPos.Y=y;
    SetConsoleCursorPosition(hcon,dwPos);
}
void ocultarcursor(){                              //OCULTA EL CURSOR DE ESCRITURA EN DURANTE LA EJECUCION
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = 100;
    cci.bVisible = FALSE;
    SetConsoleCursorInfo(hCon,&cci);
}
void escenario(){                                  //DIBUJA LIMITES, TITULO Y SALUD EN PANTALLA
    for(int i=3;i<=96;i++)                      //LIMITES HORIZONTALES
    {
        gotoxy(i,4);printf("%c",205);           //  ==============
        gotoxy(i,53);printf("%c",205);          //  =============
    }
    for(int i=5;i<=52;i++)                      //LIMITES VERTICALES
    {
        gotoxy(2,i);printf("%c",186);           //      ||
        gotoxy(96,i);printf("%c",186);          //      ||
    }
    gotoxy( 2, 4);printf("%c",201);             //ESQUINAS DEL MARCO LIMITES
    gotoxy(96, 4);printf("%c",187);
    gotoxy( 2,53);printf("%c",200);
    gotoxy(96,53);printf("%c",188);
                                                //TITULO T-B ESQUINA SUPERIOR IZQUIERDA
    gotoxy(3,0);printf("%c%c%c%c%c %c%c ",223,223,219,223,223, 32, 32);gotoxy(12,0);printf("%c%c%c%c",219,223,223,220);
    gotoxy(3,1);printf("%c%c%c%c%c %c%c ", 32, 32,219, 32, 32, 32, 32);gotoxy(12,1);printf("%c%c%c%c",219, 32,220,223);
    gotoxy(3,2);printf("%c%c%c%c%c %c%c ", 32, 32,219, 32, 32,223,223);gotoxy(12,2);printf("%c%c%c%c",219, 32,223,220);
    gotoxy(3,3);printf("%c%c%c%c%c %c%c ", 32, 32,219, 32, 32, 32, 32);gotoxy(12,3);printf("%c%c%c%c",219,220,220,223);

    mostrar_salud();                            //MUESTRA SALUD AL INICIO DE LA EJECUCION
}
void findeljuego(){                                //MUESTRA TITULO GAME OVER! AL TERMINAR EL JUEGO
    gotoxy(30,25);printf("%c%c%c %c%c%c %c%c%c%c%c %c%c%c   %c%c%c %c%c%c %c%c%c %c%c%c %c",178,178,178,  178,178,178,  178, 32, 32, 32,178,   178,178,178,   178,178,178,   178, 32,178,   178,178,178,   178,178,178,  178);
    gotoxy(30,26);printf("%c%c%c %c%c%c %c%c%c%c%c %c%c%c   %c%c%c %c%c%c %c%c%c %c%c%c %c",178, 32,178,  178, 32,178,  178,178, 32,178,178,   178, 32, 32,   178, 32,178,   178, 32,178,   178, 32, 32,   178, 32,178,  178);
    gotoxy(30,27);printf("%c%c%c %c%c%c %c%c%c%c%c %c%c%c   %c%c%c %c%c%c %c%c%c %c%c%c %c",178,178,178,  178,178,178,  178, 32,178, 32,178,   178,178,178,   178, 32,178,   178, 32,178,   178,178,178,   178,178,178,  178);
    gotoxy(30,28);printf("%c%c%c %c%c%c %c%c%c%c%c %c%c%c   %c%c%c %c%c%c %c%c%c %c%c%c %c", 32, 32,178,  178, 32,178,  178, 32, 32, 32,178,   178, 32, 32,   178, 32,178,   178, 32,178,   178, 32, 32,   178,178, 32,   32);
    gotoxy(30,29);printf("%c%c%c %c%c%c %c%c%c%c%c %c%c%c   %c%c%c %c%c%c %c%c%c %c%c%c %c",178,178,178,  178, 32,178,  178, 32, 32, 32,178,   178,178,178,   178,178,178,    32,178, 32,   178,178,178,   178, 32,178,  178);
}
void cubocuadrado(int x,int y)                     //DIBUJA BLOQUES DONDE EL PERSONAJE PUEDE SUBIRSE
{
    gotoxy(x,y)  ;printf("%c%c%c%c",177,223,223,177);
    gotoxy(x,y+1);printf("%c%c%c%c",177,206,206,177);
    gotoxy(x,y+2);printf("%c%c%c%c",177,220,220,177);
}
void bloqueplataforma(int x,int y)                 //DIBUJA PLATAFORMA A LAS CUALES ACCEDE EL PERSOJANE MEDIANTE LAS ESCALERAS
{                                                  //ESQUINAS DE LA PLATAFORMA
    gotoxy(x,y);     printf("%c",201);                  //SUPERIOR IZQUIERDA
    gotoxy(x+74,y);  printf("%c",187);                  //SUPERIOR DERECHA
    gotoxy(x,y+1);   printf("%c",200);                  //INFERIOR DERECHA
    gotoxy(x+74,y+1);printf("%c",188);                  //INFERIOR IZQUIERDA

    for(int i=x+1;i<=x+73;i++){                         //LINEAS HORIZONTALES
        gotoxy(i,y);  printf("%c",205);                 //    ============
        gotoxy(i,y+1);printf("%c",205);                 //    ============
    }
}
void pintar_plataforma(){                          //FUNCION PARA PINTAR PLATAFORMAS, BLOQUES, CONEJO Y MONSTRUO
    escenario();
    bloqueplataforma( 3,43);                            //PRIMERA PLATAFORMA
    bloqueplataforma(21,33);                            //SEGUNDA PLATAFORMA
    bloqueplataforma( 3,23);                            //TERCERA PLATAFORMA
    bloqueplataforma(21,13);                            //CUARTA PLATAFORMA
    cubocuadrado(92,50);                                //BUFF BLOQUE #1 EN PISO
    cubocuadrado( 3,40);                                //BUFF BLOQUE #2 PLATAFORMA #1
    cubocuadrado(92,30);                                //BUFF BLOQUE #3 PLATAFORMA #2
    cubocuadrado( 3,20);                                //BUFF BLOQUE #4 PLATAFORMA #3
    cubocuadrado(92,10);                                //CUBOS DETRAS DEL MONSTRUO
    cubocuadrado(88,10);
    cubocuadrado(90, 7);
    for(int i=55;i<=70;i++){                            //PLATAFORMA DEL CONEJO Y META DEL NIVEL
        gotoxy(i,9);  printf("%c",223);}
    pintar_rabbit();                                    //PINTAR CONEJO
    gotoxy( 3,45);printf("%c%c%c%c", 32,177, 32,177);
    gotoxy( 3,46);printf("%c%c%c%c",177, 32,177, 32);
    gotoxy( 3,47);printf("%c%c%c%c", 32,177, 32,177);
    gotoxy( 3,48);printf("%c%c%c%c",177, 32,177, 32);   //BLOQUE GRANDE EN EL INICIO
    gotoxy( 3,49);printf("%c%c%c%c", 32,177, 32,177);
    gotoxy( 3,50);printf("%c%c%c%c",177, 32,177, 32);
    gotoxy( 3,51);printf("%c%c%c%c", 32,177, 32,177);
    gotoxy( 3,52);printf("%c%c%c%c",177, 32,177, 32);
    pintar_monstruo();                                  //PINTAR MONSTRUO
}
void bloqueescalera(int x, int y)                  //CUERPO DE UNA ESCALERA
{
    gotoxy(x,y);printf("%c%c%c%c%c",195,196,196,196,180);
    gotoxy(x,y+1);printf("%c%c%c%c%c",195,196,196,196,180);
    gotoxy(x,y+2);printf("%c%c%c%c%c",195,196,196,196,180);
    gotoxy(x,y+3);printf("%c%c%c%c%c",195,196,196,196,180);
    gotoxy(x,y+4);printf("%c%c%c%c%c",195,196,196,196,180);
    gotoxy(x,y+5);printf("%c%c%c%c%c",195,196,196,196,180);
    gotoxy(x,y+6);printf("%c%c%c%c%c",195,196,196,196,180);
    gotoxy(x,y+7);printf("%c%c%c%c%c",195,196,196,196,180);
    gotoxy(x,y+8);printf("%c%c%c%c%c",195,196,196,196,180);
}
void mostrar_escalera(){                           //IMPRIME ESCALERA---IMPRIME ESCALERA---IMPRIME ESCALERA---IMPRIME ESCALERA---

    bloqueescalera(70,44);          //INSTANCIA DE UNA ESCALERA
    bloqueescalera(24,34);          //INSTANCIA DE UNA ESCALERA
    bloqueescalera(70,24);          //INSTANCIA DE UNA ESCALERA
    bloqueescalera(24,14);          //INSTANCIA DE UNA ESCALERA

    gotoxy(50, 9);printf("%c%c%c%c%c",195,196,196,196,180);     //ESCALERA DEL CONEJO
    gotoxy(50,10);printf("%c%c%c%c%c",195,196,196,196,180);
    gotoxy(50,11);printf("%c%c%c%c%c",195,196,196,196,180);
    gotoxy(50,12);printf("%c%c%c%c%c",195,196,196,196,180);

    if((x_p1==71 && y_p1==39)||(x_p1==71 && y_p1==44))          //EVITA QUE EL JUGADOR BORRE LA PLATAFORMA
    {
            gotoxy(71,43);printf("%c%c%c",205,205,205);
    }
    if((x_p1==25 && y_p1==29)||(x_p1==25 && y_p1==34))
    {
            gotoxy(25,33);printf("%c%c%c",205,205,205);
    }
    if((x_p1==71 && y_p1==19)||(x_p1==71 && y_p1==24))
    {
            gotoxy(71,23);printf("%c%c%c",205,205,205);
    }
    if((x_p1==25 && y_p1==9)||(x_p1==25 && y_p1==14))
    {
            gotoxy(25,13);printf("%c%c%c",205,205,205);
    }
    pintar_jugador1();
}
void saltar_derecha()                              //FUNCION PARA SALTAR A LA DERECHA
{
    if(cs1<3 && saltod_on==true)                        //ASCIENDE 3 POSICIONES EN DIAGONAL
    {
        eliminar_jugador();
        x_p1++;y_p1--;cs1++;
    }
    if((cs2>=3 && cs2<7) && saltod_on==true)            //AVANZA 4 POSICIONES EN LINEA RECTA
    {
        eliminar_jugador();
        x_p1++;cs1++;
        if(
                ((x_p1>=88 && x_p1<=95) && cs2==5)      //EN EL CASO DE ESTAR CERCA DE UN BLOQUE BUFF SE QUEDARA
           )                                            //SOBRE EL BLOQUE
        {
            saltod_on=false;                            //DETIENE Y RESTAURA SALTO DEL PERSONAJE
            cs1=0,cs2=0,cs3=0;
        }
    }
    if((cs3>=7 && cs3<=9) && saltod_on==true)           //DESCIENDE 3 POSCIONES EN DIAGONAL
    {
        eliminar_jugador();
        x_p1++;y_p1++;cs1++;
    }
    if(                                                 //CONDICIONA DONDE PUEDE SALTAR EL JUGADOR
         (((x_p1>= 3 && x_p1<=79) || (x_p1>=83 && x_p1<=87)) && (y_p1==49)) ||
          ((x_p1>= 6 && x_p1<=79) && (y_p1==39)) ||
         (((x_p1>= 6 && x_p1<=79) || (x_p1>=83 && x_p1<=87)) && (y_p1==29)) ||
          ((x_p1>= 6 && x_p1<=79) && (y_p1==19)) ||
          ((x_p1>= 6 && x_p1<=41) && (y_p1== 9)) || (saltod_on==true)
    )
    {
        saltod_on=true;                                 //ACTIVA FUNCION SALTO DERECHA
    }
    cs2=cs1;                                            //ASIGNACION DE VALORES
    cs3=cs1;
    if(cs3==10)                                         //DETIENE Y RESTAURA SALTO DEL PERSONAJE
    {
        saltod_on=false;
        cs1=0,cs2=0,cs3=0;
    }
    pintar_jugador1();
}
void saltar_izquierda()                            //FUNCION PARA SALTAR A LA IZQUIERDA
{
    if(cs1<3 && saltoi_on==true)                        //ASCIENDE 3 POSICIONES EN DIAGONAL
    {
        eliminar_jugador();
        x_p1--;y_p1--;cs1++;
    }
    if((cs2>=3 && cs2<7) && saltoi_on==true)            //AVANZA 4 POSICIONES EN LINEA RECTA
    {
        eliminar_jugador();
        x_p1--;cs1++;
        if(
                ((x_p1>= 1 && x_p1<= 8) && cs2==5)      //EN EL CASO DE ESTAR CERCA DE UN BLOQUE BUFF SE QUEDARA
           )                                            //SOBRE EL BLOQUE
        {
            saltoi_on=false;                            //DETIENE Y RESTAURA SALTO DEL PERSONAJE
            cs1=0,cs2=0,cs3=0;
        }
    }
    if((cs3>=7 && cs3<=9) && saltoi_on==true)           //DESCIENDE 3 POSCIONES EN DIAGONAL
    {
        eliminar_jugador();
        x_p1--;y_p1++;cs1++;
    }
    if(                                                 //CONDICIONA DONDE PUEDE SALTAR EL JUGADOR
          ((x_p1>=17 && x_p1<=89) && (y_p1==49)) ||
         (((x_p1>=17 && x_p1<=79) || (x_p1>= 9 && x_p1<=13)) && (y_p1==39)) ||
          ((x_p1>= 6 && x_p1<=89) && (y_p1==29)) ||
         (((x_p1>=17 && x_p1<=79) || (x_p1>= 9 && x_p1<=13)) && (y_p1==19)) ||
          ((x_p1>= 6 && x_p1<=93) && (y_p1== 9)) || (saltoi_on==true)
    )
    {
        saltoi_on=true;                                 //ACTIVA FUNCION SALTO IZQUIERDA
    }
    cs2=cs1;                                            //ASIGNACION DE VALORES
    cs3=cs1;
    if(cs3==10)                                         //DETIENE Y RESTAURA SALTO DEL PERSONAJE
    {
        saltoi_on=false;
        cs1=0,cs2=0,cs3=0;
    }
    pintar_jugador1();
}
void mover_monstruo()                              //FUNCION PARA MOVER AL MONSTRUO
{
    if(mover_mm==true && x_mm>72)                   //MOVIMIENTO A LA DERECHA
    {
        borrar_monstruo();
        x_mm--;
        pintar_monstruo();
    }
    if(mover_mm2==true && x_mm<81)                  //MOVIMIENTO A LA IZQUIERDA
    {
        borrar_monstruo();
        x_mm++;
        pintar_monstruo2();
    }
}
void caer()                                         //BAJA UN ESPACIO AL JUGADOR
{
    eliminar_jugador();
    y_p1++;
    pintar_jugador1();
}
void muerte_caida()                                //ANIMACION CAIDA DEL PERSONAJE DESDE UNA PLATAFORMA
{
    if(    ((x_p1>=78 && x_p1<=93) && (y_p1==39)) ||      //CONDICIONAL PARA PERDER UNA VIDA AL CAER DEL PISO
           ((x_p1>= 3 && x_p1<=17) && (y_p1==29)) ||
           ((x_p1>=78 && x_p1<=93) && (y_p1==19)) ||
           ((x_p1>= 3 && x_p1<=17) && (y_p1== 9))
       ){
            Activo=true;
       }
       if(f==0 && Activo==true)                         //CONDICION PARA DETENER LA CAIDA
            {
                Activo=false;
                Explotar();
                Num_vidas_p1--;
                Corazones_p1=3;
                mostrar_salud();
            }
       if(Activo==true)                                 //ACTIVA CAIDA DEL PERSONAJE
            {
                f--;
                caer();
            }

    if(Corazones_p1==0)                                 //DEVUELVE SALUD DEL PERSONAJE AL PERDER UNA VIDA
    {
        Num_vidas_p1--;
        Explotar();
        Corazones_p1=3;
        mostrar_salud();
    }
}
int prototipo(int &x, int &y, bool &dw, bool &dg, bool &fin)      //FUNCION RECORRIDO DEL BARRIL
{
    int t=0;
    borrar_enemigo3(x,y);
    if(y==20||y==30||y==40||y==50){             //BAJA EL BARRIL ENTRE PLATAFORMAS
            dw=true;
            dg=true;
        }
    if(x>17 && y==10){                                //MOVIENTO EN PLATAFORMA #4
        x--;                                             //HACIA IZQUIERDA
    }
    if(x<79 && y==20){                                //MOVIENTO EN PLATAFORMA #3
            x++;                                         //HACIA DERECHA
    }
    if((x==17 && y==10)||(x==17 && y==30)){     //CONDICION PARA ACTIVAR EL DESENSO BARRIL IZQUIERDA
        dw=false;
    }
    if((x==79 && y==20)||(x==79 && y==40)){     //CONDICION PARA ACTIVAR EL DESENSO BARRIL DERECHA
        dg=false;
    }
    if(x>17 && y==30){                            //MOVIENTO EN PLATAFORMA #2
            x--;                                     //HACIA IZQUIERDA
    }
    if(x<79 && y==40){                            //MOVIENTO EN PLATAFORMA #1
            x++;                                     //HACIA DERECHA
    }
    if(x>7 && y==50){                             //MOVIENTO EN PISO
            x--;                                     //HACIA IZQUIERDA
    }
    if(x==7 && y==50 && fin==FALSE){             //LUGAR CUANDO EL BARRIL LLEGA AL FINAL DEL RECORRIDO
        choque_enemigo3(x,y,dw,dg);                              //EXPLOTA
        fin=true;
    }
    if(dw==false){
            y++;x--;                      //DESCENDER HACIA LA IZQUIERDA
        }
    if(dg==false){
            y++;x++;                      //DESCENDER HACIA LA IZQUIERDA
        }
    if(fin==true)                              //DETECTA FIN DEL RECCORRIDO BARRIL 1
    {
        x=69;y=10;
        fin=false;
    }
    pintar_enemigo3(x,y);
    Sleep(t);
}
void enemigos()                                    //FUNCION PARA EL MOVIMIENTO DE ENEMIGOS
{
    if(game_start==true)                        //INCIAR CUANDO EL JUEGO ESTE EN EJECUCION
    {
    prototipo(x_b1,y_b1,dw1,dg1,finA);
    //--------------
    if(x_b1==28 && y_b1==20)                    //CONDICION PARA ACTIVAR EL RECORRIDO BARRIL 2
    {
        inicioB=true;
    }
    if(inicioB==true)                           //INICIAR RECORRIDO BARRIL 2
    {
        prototipo(x_b2,y_b2,dw2,dg2,finB);
    }
    //--------------
    if(x_b2==30 && y_b2==20)                    //CONDICION PARA ACTIVAR EL RECORRIDO BARRIL 3
    {
        inicioC=true;
    }
    if(inicioC==true)                           //INICIAR RECORRIDO BARRIL 3
    {
        prototipo(x_b3,y_b3,dw3,dg3,finC);
    }
    //--------------
    if(x_b3==30 && y_b3==20)                    //CONDICION PARA ACTIVAR EL RECORRIDO BARRIL 4
    {
        inicioD=true;
    }
    if(inicioD==true)                           //INICIAR RECORRIDO BARRIL 4
    {
        prototipo(x_b4,y_b4,dw4,dg4,finD);
    }
    //--------------
    if(x_b4==30 && y_b4==20)                    //CONDICION PARA ACTIVAR EL RECORRIDO BARRIL 5
    {
        inicioE=true;
    }
    if(inicioE==true)                           //INICIAR RECORRIDO BARRIL 5
    {
        prototipo(x_b5,y_b5,dw5,dg5,finE);
    }
    Score(x_b1,y_b1);
    if( (dw1==true)||(dg1==true)){             //BAJA EL BARRIL ENTRE PLATAFORMAS
            mover_mm=false;
            mover_mm2=false;
        }
    if((x_b1==30 && y_b1==10)||(x_b1==30 && y_b1==30)){
        mover_mm=true;
    }
    if((x_b1==50 && y_b1==20)||(x_b1==50 && y_b1==40)){
        mover_mm2=true;
    }
    Score(x_b2,y_b2);
    Score(x_b3,y_b3);
    Score(x_b4,y_b4);
    Score(x_b5,y_b5);
    impacto(x_b1,y_b1,dw1,dg1);
    impacto(x_b2,y_b2,dw2,dg2);
    impacto(x_b3,y_b3,dw3,dg3);
    impacto(x_b4,y_b4,dw4,dg4);
    impacto(x_b5,y_b5,dw5,dg5);
    }
}
int impacto(int &x,int &y,bool &dw,bool &dg)
{
    if(                                         //CONJUNTO DE CONDICIONES PARA EL CHOQUE BARRIL JUGADOR
        (((y_p1+2)==(y) || (y_p1+2)==(y+1) || (y_p1+2)==(y+2)) &&
             ((x==x_p1) || (x+1 == x_p1+1) || (x   == x_p1+2)  || (x==x_p1+3)))  ||
        (((y_p1+3)==(y) || (y_p1+2)==(y+1) || (y_p1+2)==(y+2)) &&
         ((x+1==x_p1) || (x+1 == x_p1+1) || (x+1 == x_p1+2)  || (x+1==x_p1+3)))
       )
    {
        choque_enemigo3(x,y,dw,dg);
        Explotar();
        Corazones_p1--;
        mostrar_salud();
        Beep(260,200);
        x=65,y=10;
    }
}
void bajar()                                        //DESCIENDE AL PERSONAJE DE LOS BLOQUES BUFF
{
    if( (x_p1==47 && y_p1==5) )
    {
        unico=true;
    }
    if(
       ((x_p1==89 && (y_p1>45 && y_p1<49) && saltod_on==false) ||
       (x_p1== 7 && (y_p1>34 && y_p1<39) && saltoi_on==false) ||
       (x_p1==89 && (y_p1>25 && y_p1<29) && saltod_on==false) ||
       (x_p1== 7 && (y_p1>14 && y_p1<19) && saltoi_on==false) &&(saltod_on==false ||saltoi_on==false)) ||
       ((x_p1==47 && (y_p1> 4 && y_p1< 9) && unico==true))
       )
    {
        eliminar_jugador();
        y_p1++;
        pintar_jugador1();
    }
    if( (x_p1==47 && y_p1==9) )
    {
        unico=false;
    }
}
void buff_puerta_escudo()                           //BUFF PUERTA SECRETA Y ESCUDO
{
    if(Corazones_p1==1 && cc==1)                //CONDICION PARA MOSTRAR UBICACION DE LA PUERTA SECRETA
    {
            xr=(rand()%70)+7;                   //OBTENER DIRECCION ALEATORIA
        if(xr>10 && xr<19){                     //SE ENCARGA DE UBICARLA EN LA POSICION Y
            yr=9;
        }else if(xr>20 && xr<29){
            yr=19;
        }else if(xr>30 && xr<39){
            yr=29;
        }else if(xr>40 && xr<49){
            yr=39;
        }else if(xr>50 && xr<59){
            yr=49;
        }else{
            yr=19;
        }
        gotoxy(xr,yr);printf("+");              //PINTA LA UBICACION PUERTA SECRETA
        Sleep(150);
        gotoxy(xr,yr);printf(" ");              //BORRA UBICACION PUERTA SECRETA
        cc=0;
    }
    if(Corazones_p1==3){                        //RESET PARA OBTENER PISTA NUEVAMENTE
        cc=1;
    }
}
void Score(int x,int y)                             //FUNCION PARA MARCAR LA PUNTUACION
{
    gotoxy(85,1);printf("SCORE   %d",puntuacion_p1);                      //UBICAR PUNTUACION EN LA PANTALLA
    if(
        (((y_p1+4)==(y) || (y_p1+5)==(y+1) || (y_p1+6)==(y+2)) &&  //MARCA SALTO SOBRE BARRIL
         ((x==x_p1)   || (x==x_p1+1))) && (saltod_on==true || saltoi_on==true)
       )
       {
           puntuacion_p1+=100;                                              //SUMA 100 PUNTOS AL MARCADOR
           Beep(500,200);
       }
}
void presentacion()                                 //PANTALLA INICIO DE JUEGO
{
    escenario();
    gotoxy(85,1);printf("SCORE   %d",puntuacion_p1);
    gotoxy(37,20);printf("%c%c%c%c%c %c%c %c%c%c%c %c%c%c%c %c%c%c%c%c",223,223,219,223,223, 32, 32,219,223,223,220,220,223,223,220,219, 32, 32, 32,219);
    gotoxy(37,21);printf("%c%c%c%c%c %c%c %c%c%c%c %c%c%c%c %c%c%c%c%c", 32, 32,219, 32, 32, 32, 32,219, 32,220,223,219, 32, 32,219, 32,219, 32,219, 32);
    gotoxy(37,22);printf("%c%c%c%c%c %c%c %c%c%c%c %c%c%c%c %c%c%c%c%c", 32, 32,219, 32, 32,223,223,219, 32,223,220,219, 32, 32,219, 32, 32,219, 32, 32);
    gotoxy(37,23);printf("%c%c%c%c%c %c%c %c%c%c%c %c%c%c%c %c%c%c%c%c", 32, 32,219, 32, 32, 32, 32,219,220,220,223,223,220,220,223, 32, 32,219, 32, 32);

    gotoxy(48,27);puts(jugador1_1);
    gotoxy(48,28);puts(jugador1_2);
    gotoxy(48,29);puts(jugador1_3);
    gotoxy(48,30);puts(jugador1_4);

    Sleep(5000);
    system("cls");
}
void presentacion2()                                //PANTALLA AL COMPLETAR EL JUEGO
{
    escenario();
    gotoxy(85,1);printf("SCORE   %d",puntuacion_p1);
    gotoxy(37,20);printf("%c%c%c%c%c %c%c %c%c%c%c %c%c%c%c %c%c%c%c%c",223,223,219,223,223, 32, 32,219,223,223,220,220,223,223,220,219, 32, 32, 32,219);
    gotoxy(37,21);printf("%c%c%c%c%c %c%c %c%c%c%c %c%c%c%c %c%c%c%c%c", 32, 32,219, 32, 32, 32, 32,219, 32,220,223,219, 32, 32,219, 32,219, 32,219, 32);
    gotoxy(37,22);printf("%c%c%c%c%c %c%c %c%c%c%c %c%c%c%c %c%c%c%c%c", 32, 32,219, 32, 32,223,223,219, 32,223,220,219, 32, 32,219, 32, 32,219, 32, 32);
    gotoxy(37,23);printf("%c%c%c%c%c %c%c %c%c%c%c %c%c%c%c %c%c%c%c%c", 32, 32,219, 32, 32, 32, 32,219,220,220,223,223,220,220,223, 32, 32,219, 32, 32);

    gotoxy(46,27);puts(jugador1_1);
    gotoxy(46,28);puts(jugador1_2);
    gotoxy(46,29);puts(jugador1_3);
    gotoxy(46,30);puts(jugador1_4);

    x_rabbit=50,y_rabbit=28;pintar_rabbit();

    Sleep(5000);
    system("cls");
}
void interseccion()                                 //ANIMACION AL PASAR DEL NIVEL 1 AL 2 Y DEL NIVEL 2 AL NIVEL 3
{
    game_start==false;
    Sleep(1000);
    for(int i=1;i<10;i++)                               //MUEVE AL MONSTRUO A LA POSCISION DEL CONEJO
    {
    if(x_mm>72){borrar_monstruo();x_mm--;pintar_monstruo();Sleep(100);}
    }
    for(int j=1;j<18;j++)                               //MUEVE AL MONSTRUO A LA IZQUIERDA ARRASTRANDO AL CONEJO :(
    {
    if(x_mm<97){borrar_monstruo();x_mm++;pintar_monstruo2();Sleep(0);}
    if(x_rabbit<97){borrar_rabbit();x_rabbit++;pintar_rabbit();Sleep(100);}
    }
    borrar_monstruo();borrar_rabbit();
    system("cls");Nivel++;escenario();
    presentacion();                                     //MUESTRA PANTALLA DE TRANSCICION
    x_rabbit=67;y_rabbit=6;x_mm=81;y_mm=5;
    x_p1=9;y_p1=49;
    x_b1=60;y_b1=10;dg1=true;dw1=true;
    x_b2=60;y_b2=10;dg2=true;dw2=true;inicioB=false;
    x_b3=60;y_b3=10;dg3=true;dw3=true;inicioC=false;
    x_b4=60;y_b4=10;dg4=true;dw4=true;inicioE=false;
    x_b5=60;y_b5=10;dg5=true;dw5=true;inicioD=false;

    t-=0;
    game_start=true;
}
void felicidades()                                  //ANIMACION AL GANAR EL JUEGO
{
    game_start==false;
    Sleep(1000);
    gotoxy(x_mm-1,y_mm+8);printf("         ");          //ELIMINA PISO DEBAJO DEL MONSTRUO
    gotoxy(x_mm-1,y_mm+9);printf("         ");
    Sleep(500);
    for(int i=1;i<41;i++)                               //CAIDA DEL MONSTRUO HASTA PISO
    {
    if(y_mm<60){borrar_monstruo();y_mm++;pintar_monstruo();Sleep(100);}
    }
    borrar_monstruo();
    explotar_monstruo();                                //EXPLOSION DEL MONSTRUO :)
    system("cls");
    presentacion2();                                    //PANTALLA AL COMPLETAR EL JUEGO
}
void mennu()                                        //OPCIONES DE USUARIO
{
    gotoxy(37,20);printf("%c%c%c%c%c %c%c %c%c%c%c %c%c%c%c %c%c%c%c%c",223,223,219,223,223, 32, 32,219,223,223,220,220,223,223,220,219, 32, 32, 32,219);
    gotoxy(37,21);printf("%c%c%c%c%c %c%c %c%c%c%c %c%c%c%c %c%c%c%c%c", 32, 32,219, 32, 32, 32, 32,219, 32,220,223,219, 32, 32,219, 32,219, 32,219, 32);
    gotoxy(37,22);printf("%c%c%c%c%c %c%c %c%c%c%c %c%c%c%c %c%c%c%c%c", 32, 32,219, 32, 32,223,223,219, 32,223,220,219, 32, 32,219, 32, 32,219, 32, 32);
    gotoxy(37,23);printf("%c%c%c%c%c %c%c %c%c%c%c %c%c%c%c %c%c%c%c%c", 32, 32,219, 32, 32, 32, 32,219,220,220,223,223,220,220,223, 32, 32,219, 32, 32);

    bool repite=true;
    int opcion;

    const char *titulo="MENU DE INICIO";
    const char *opciones[]={"Nuevo Juego","Continuar","Puntuacion","Salir"};
    int n = 4;

    do {
        limpiar(41,25);
        opcion = eleccion(titulo,opciones,n);
        switch (opcion) {
            case 1:
                Nueva_partida();
                break;
            case 2:
                Continuar();
                break;
            case 3:
                Puntuaciones();
                break;
            case 4:
                game_over=true;
                salir_del_juego=true;
                startg=false;
                repite = false;
                break;
      }
      if(startg==false)
      {
          break;
      }
   } while(repite);
   limpiar(41,25);
}   //!FIN VOID mennu
void Nueva_partida()                                //MUESTRA LAS ESPACION DE PARTIDAS
{
    bool repite=true;
    int opcion;

    ifstream fentrada("caset.bin",ios::in | ios::binary);
    fentrada.read(reinterpret_cast<char *>(&partidas[0]),sizeof(Partida));
    fentrada.read(reinterpret_cast<char *>(&partidas[1]),sizeof(Partida));

    const char *titulo="Nueva Partida....?   ";
    const char *opciones[]={partidas[0].nombre,partidas[1].nombre,"Regresar"};
    int n = 3;

    fentrada.close();
    do {
        opcion = eleccion(titulo,opciones,n);
        switch (opcion) {
            case 1:
                slot=0;
                Newprofile();
                break;
            case 2:
                slot=1;
                Newprofile();
                break;
            case 3:
                repite = false;
                break;
      }
      if(startg==false)
      {
          break;
      }
   } while(repite);
}
void Newprofile()                                   //ELIMINA LA CASILLA DE REGISTRO PARA INGRESAR UNO NUEVO
{
    gotoxy(41,25);cout<<"Cual es tu nombre?";

    gotoxy(41,28);cout<<"> ";
    if(slot==0)
    {
        ofstream fsalida("caset.bin",ios::out | ios::binary);
        cin>>partidas[0].nombre;
        partidas[0].puntaje=0;
        partidas[0].vidas=3;
        partidas[0].salud=3;

        fsalida.write(reinterpret_cast<char *>(&partidas[0]),sizeof(Partida));
        fsalida.write(reinterpret_cast<char *>(&partidas[1]),sizeof(Partida));
        fsalida.close();
    }
    if(slot==1)
    {
        ofstream fsalida("caset.bin",ios::out | ios::binary);
        cin>>partidas[1].nombre;
        partidas[1].puntaje=0;
        partidas[1].vidas=3;
        partidas[1].salud=3;

        fsalida.write(reinterpret_cast<char *>(&partidas[0]),sizeof(Partida));
        fsalida.write(reinterpret_cast<char *>(&partidas[1]),sizeof(Partida));
        fsalida.close();
    }
    startg=false;
    nuevaentrada=true;
}
void Continuar()                                    //INICIA NUEVA PARTIDAS CON DATOS PREVIAMENTE JUGADOS
{
    bool repite=true;
    int opcion;

    const char *titulo="Continuar....?   ";
    const char *opciones[]={partidas[0].nombre,partidas[1].nombre,"Regresar"};
    int n = 3;

    do {
        opcion = eleccion(titulo,opciones,n);
        switch (opcion) {
            case 1:
                slot=0;

                repite=false;
                break;
            case 2:
                slot=1;

                repite=false;
                break;
            case 3:
                repite = false;
                break;
      }
   } while(repite);
}
void Puntuaciones()                                 //MUESTRA NOMBRES Y PUNTAJES DE LAS PARTIDAS GUARDADAS
{
    bool repite=true;
    int opcion;
    ifstream fentrada("caset.bin",ios::in | ios::binary);
    fentrada.read(reinterpret_cast<char *>(&partidas[0]),sizeof(Partida));
    fentrada.read(reinterpret_cast<char *>(&partidas[1]),sizeof(Partida));

    const char *titulo="Continuar....?   ";
    const char *opciones[]={partidas[0].nombre,partidas[1].nombre,"Regresar"};
    int n = 3;
    fentrada.close();
    do {
        opcion = eleccion(titulo,opciones,n);
        gotoxy(60,27);cout<<partidas[0].puntaje;
        gotoxy(60,28);cout<<partidas[1].puntaje;
        switch (opcion) {
            case 3:
                repite = false;
                break;
      }
   } while(repite);
}
int eleccion(const char titulo[], const char *opciones[], int n)    //SELECIONA UTILIZANDO UNA FLECHA COMO PUNTERO
{
   int opcionSeleccionada = 1;
   int tecla;
   bool repite = true;

   gotoxy(41,27);printf("                   ");
   gotoxy(41,28);printf("                   ");
   gotoxy(41,29);printf("                   ");
   gotoxy(41,30);printf("                   ");

   do{
        gotoxy(37, 26 + opcionSeleccionada); cout << "==>" << endl;
        gotoxy(41,25); cout << titulo;

        for (int i = 0; i < n; ++i) {
            gotoxy(41,27 + i); cout << i + 1 << ") " << opciones[i];
        }
        do {
            tecla = getch();
        } while (tecla != ARRIBA && tecla != ABAJO && tecla != ENTER);

        switch (tecla) {
            case ARRIBA:
                gotoxy(37, 26 + opcionSeleccionada); cout << "   " << endl;
                opcionSeleccionada--;
                if (opcionSeleccionada < 1) {
                opcionSeleccionada = n;
                }
                break;
            case ABAJO:
                gotoxy(37, 26 + opcionSeleccionada); cout << "   " << endl;
                    opcionSeleccionada++;
                if (opcionSeleccionada > n) {
                    opcionSeleccionada = 1;
                    }
                break;
            case ENTER:
                gotoxy(37, 26 + opcionSeleccionada); cout << "   " << endl;
                repite = false;
                limpiar(41,25);
                break;
        }
    }while (repite);
   return opcionSeleccionada;
}
void guardardatos()                                 //CARGA LOS DATOS DEL ARCHIVO A LA CONSOLA
{
    if(nuevaentrada==true)
    {
        puntuacion_p1=0;
        Num_vidas_p1=3;
        Corazones_p1=3;
    }
    if(slot==0)
    {
        ofstream fsalida("caset.bin",ios::out | ios::binary);
            puntuacion_p1=partidas[0].puntaje;
            Corazones_p1=partidas[0].salud;
            fsalida.write(reinterpret_cast<char *>(&partidas[0]),sizeof(Partida));
            fsalida.write(reinterpret_cast<char *>(&partidas[1]),sizeof(Partida));
            fsalida.close();
    }
    if(slot==1)
    {
            ofstream fsalida("caset.bin",ios::out | ios::binary);
            puntuacion_p1=partidas[1].puntaje;
            Corazones_p1=partidas[1].salud;
            fsalida.write(reinterpret_cast<char *>(&partidas[0]),sizeof(Partida));
            fsalida.write(reinterpret_cast<char *>(&partidas[1]),sizeof(Partida));
        fsalida.close();
    }
}
void asignardatos()                                 //GUARDA DATOS JUGADOS DURANTE LA PARTIDA
{
        if(slot==0)
        {
            ofstream fsalida("caset.bin",ios::out | ios::binary);
            partidas[0].puntaje=puntuacion_p1;
            partidas[0].salud=Corazones_p1;
            fsalida.write(reinterpret_cast<char *>(&partidas[0]),sizeof(Partida));
            fsalida.write(reinterpret_cast<char *>(&partidas[1]),sizeof(Partida));
            fsalida.close();
        }
        if(slot==1)
        {
            ofstream fsalida("caset.bin",ios::out | ios::binary);
            partidas[1].puntaje=puntuacion_p1;
            partidas[1].salud=Corazones_p1;
            fsalida.write(reinterpret_cast<char *>(&partidas[0]),sizeof(Partida));
            fsalida.write(reinterpret_cast<char *>(&partidas[1]),sizeof(Partida));
            fsalida.close();
        }

}
void limpiar(int x,int y)                           //BORRA LA PANTALLA DE MENU
{
    gotoxy(x,y);  cout<<"                         ";
    gotoxy(x,y+2);cout<<"                         ";
    gotoxy(x,y+3);cout<<"                         ";
    gotoxy(x,y+4);cout<<"                         ";
    gotoxy(x,y+5);cout<<"                         ";
    gotoxy(x,y+6);cout<<"                         ";
}
void jugar(void)                                        //FUNCION ENCARGADA DE CORRER EL JUEGO Y CARGAR FUNCIONES
{
    game_start=true;                                    //ACTIVA EJECUCION DEL JUEGO
    if(kbhit())                                         //CONTROLES DE MOVIMIENTO DEL JUGADOR 1
    {
        unsigned char tecla = getch();
        switch(tecla)
        {
        case IZQUIERDA:                                 //MOVIMIENTO A LA IZQUIERDA SOBRE PLATAFORMAS O BUFF
            if(
                ((x_p1>=8 && x_p1<=93) && (y_p1==49)) || ((x_p1>=91 && x_p1<=93) && (y_p1==46)) ||
                ((x_p1>=8 && x_p1<=93) && (y_p1==39)) || ((x_p1>= 4 && x_p1<= 6) && (y_p1==36)) ||
                ((x_p1>=4 && x_p1<=93) && (y_p1==29)) || ((x_p1>=91 && x_p1<=93) && (y_p1==26)) ||
                ((x_p1>=8 && x_p1<=93) && (y_p1==19)) || ((x_p1>= 4 && x_p1<= 6) && (y_p1==16)) ||
                ((x_p1>=4 && x_p1<=93) && (y_p1==9))  ||
                ((x_p1>=42 && x_p1<=63) && (y_p1==5))
               )
            {
                eliminar_jugador();
                x_p1-=2;   //ix=ix-2 es lo mismo
                pintar_jugador1();
            }
            break;
        case DERECHA:                   //MOVIMIENTO A LA DERECHA SOBRE PLATAFORMAS O BUFF
            if(
                ((x_p1>=3 && x_p1<=88) && (y_p1==49)) || ((x_p1>=88 && x_p1<=92) && (y_p1==46)) ||
                ((x_p1>=3 && x_p1<=88) && (y_p1==39)) || ((x_p1>= 3 && x_p1<= 6) && (y_p1==36)) ||
                ((x_p1>=3 && x_p1<=88) && (y_p1==29)) || ((x_p1>=88 && x_p1<=92) && (y_p1==26)) ||
                ((x_p1>=3 && x_p1<=88) && (y_p1==19)) || ((x_p1>= 3 && x_p1<= 6) && (y_p1==16)) ||
                ((x_p1>=3 && x_p1<=50) && (y_p1==9))  ||
                ((x_p1>=3 && x_p1<=62) && (y_p1==5))
               )
            {
                eliminar_jugador();
                x_p1+=2;   //ix=ix-2 es lo mismo
                pintar_jugador1();
            }
            break;
        case ARRIBA:                    //MOVIMIENTO HACIA ARRIBA PARA SUBIR EN LAS EN LAS ESCALERAS
            if(
                ((y_p1>39 && y_p1<50) && (x_p1==71)) ||
                ((y_p1>29 && y_p1<40) && (x_p1==25)) ||
                ((y_p1>19 && y_p1<30) && (x_p1==71)) ||
                ((y_p1> 9 && y_p1<20) && (x_p1==25)) ||
                ((y_p1> 5 && y_p1<10) && (x_p1==51))
               )
            {
                eliminar_jugador();
                y_p1-=1;   //ix=ix-2 es lo mismo
                pintar_jugador1();
            }
            break;
        case ABAJO:                     //MOVIMIENTO HACIA ABAJO PARA DESCENDER EN LAS EN LAS ESCALERAS
            if(
                ((y_p1>37 && y_p1<49) && (x_p1==71)) ||
                ((y_p1>27 && y_p1<39) && (x_p1==25)) ||
                ((y_p1>17 && y_p1<29) && (x_p1==71)) ||
                ((y_p1> 7 && y_p1<19) && (x_p1==25)) ||
                ((y_p1> 4 && y_p1< 9) && (x_p1==51))
               )
            {
                eliminar_jugador();
                y_p1+=1;   //ix=ix+1 es lo mismo
                pintar_jugador1();
            }
            break;
        case SALTOD:                    //SALTO DERECHA
                saltar_derecha();
                break;
        case SALTOI:                    //SALTO IZQUIERDA
                saltar_izquierda();
                break;
        case ('r'):                     //PRUEBA DE VIDAS
            mostrar_salud();
            break;
        case ('t'):                     //PRUEBA DE SALUD
            mostrar_salud();
            game_over=true;
            break;
        case (' '):
            Sleep(0);
            break;
        case BUSCAR:                    //BUSCA ENTRADA A PUERTA SECRETA
            if(
                (tecla == BUSCAR && ((x_p1==xr || x_p1==xr+1) && y_p1==yr))
               )
            {
               eliminar_jugador();x_p1=51,y_p1=5;pintar_jugador1();
            }
        }//fin Switch
    }//fin if
    if(saltod_on==true)         //MANTIENE SALTO DERECHA CUANDO ESTE ESTA ACTIVADO
        {
            saltar_derecha();
        }
    if(saltoi_on==true)         //MANTIENE SALTO IZQUIERDA CUANDO ESTE ESTA ACTIVADO
        {
            saltar_izquierda();
        }
    if(Num_vidas_p1==0)         //ACTIVA FIN DEL JUEGO CUANDO LAS VIDAS DEL JUGADOR DISMUNUYEN A 0
    {
        game_over=true;
    }
    if(x_p1==55 && y_p1==5 && (Nivel==1 || Nivel==2))       //ACTIVA TRANSCISION DE NIVEL 1 AL NIVEL 2 O DEL 2 AL 3
    {
        interseccion();
        escenario();
        pintar_plataforma();
        mostrar_escalera();
        pintar_jugador1();
    }
    if(x_p1==61 && y_p1==5 && Nivel==3)                     //ACTIVA PANTALLA AL COMPLETAR EL JUEGO
    {
        felicidades();
        game_over=true;
    }
}
bool AjustarVentana(int Ancho, int Alto) {
	_COORD Coordenada;
	Coordenada.X = Ancho;
	Coordenada.Y = Alto;

	_SMALL_RECT Rect;
	Rect.Top = 0;
	Rect.Left = 0;
	Rect.Right = Ancho - 1;
	Rect.Bottom = Alto - 1;

	// Obtener el handle de la consola
	HANDLE hConsola = GetStdHandle(STD_OUTPUT_HANDLE);

	// Ajustar el buffer al nuevo tamaño
	SetConsoleScreenBufferSize(hConsola, Coordenada);

	// Cambiar tamaño de consola a lo especificado en el buffer
	SetConsoleWindowInfo(hConsola, TRUE, &Rect);
	return TRUE;
}

int main(){
    AjustarVentana(99,55);                                 //FUNCION PRINCIPAL
    system("color 79");                     //CAMBIA EL COLOR DEL ESCENARIO (DESACTIVADA TEMPORALMENTE)
    ocultarcursor();                        //EJECUTA OCULTAR CURSOR
    srand(time(NULL));                      //OBTIENE VALOR ALEATORIO DEPENDIENDO DEL TIEMPO DEL ORDENADOR
    escenario();
    mennu();
    if(salir_del_juego==false)              //CONDICIONA LA RESPUESTA DEL MENU DE INICIO
    {
    game_over=false;                        //ASEGURA LA EJECUCION DEL PROGRAMA
    guardardatos();
    presentacion();
    pintar_plataforma();
    mostrar_escalera();
    pintar_jugador1();

    while(game_over!=true){                  //REPITE HASTA QUE LA VIDA LLEGA A CERO "0" O SE COMPLETA EL JUEGO
        bajar();
        buff_puerta_escudo();
        muerte_caida();
        mover_monstruo();
        jugar();
        enemigos();
        mostrar_escalera();

    }
    system("cls");
    asignardatos();
    }
    escenario();
    findeljuego();
    gotoxy(0,53);
    getch();
    return 0;
    }
