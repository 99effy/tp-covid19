/*
Trabajo Práctico COVID-19
ID Archivo: TP1.cpp
Docente: Hugo Cuello
Curso: K1045 Turno Tarde
Fecha: Julio, 2020
Autores: Adriel Aran, Emanuel Andres Sánchez, Esteban Padilla, Evelyn Denisse Saadjian, 
Facundo García Pergañeda, Julian Gabriel Novoa, Lourdes María de Lucas
Comentario:
El programa debe obtener los datos correspondientes a la cantidad de hisopados, 
infectados, recuperados y fallecidos identificados en cada día de los primeros 
7 meses del año.
Luego de esto, debe computar sus totales y el porcentaje de hisopados, infectados,
recuperados y fallecidos en relación con la cantidad total de habitantes por país.
Finalizadas estos procesos, el programa imprime los resultados de forma ordenada 
en un archivo de tipo Txt.
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdio.h>
#include <string.h>

#define MAX_PAIS 200

using namespace std;

typedef struct {
	char	nomPais[20],
			continente[10];
	int 	cantHabitantes;
} tsPais;

typedef struct {
	char    nomPais[20];
	int		hisopados[8][32],
			infectados[8][32],
			recuperados[8][32],
			fallecidos[8][32];
} tsParDia;

typedef struct {
	char	nomPais[20];
	int		totalHisopadosMes[8],
			totalInfectadosMes[8],
			totalRecuperadosMes[8],
			totalFallecidosMes[8];
} tsCalc;

typedef struct {
    char    nomPais[20];
    int		cantHabitantes,
            totalhisopados,
			totalinfectados,
			totalrecuperados,
			totalfallecidos,
            totalHisopadosMes[8],
			totalInfectadosMes[8],
			totalRecuperadosMes[8],
			totalFallecidosMes[8];
} tvrPais;

ifstream archivoPaises;
ifstream archivoParteDiario;
static int  contParDiaPaises,
            contPaisesPaises;
static tsPais paises[MAX_PAIS];
static tsParDia datosPaises[2800];
static tsCalc totalPaises[MAX_PAIS];
static tvrPais paisFinal[MAX_PAIS];

void Abrir();
void Cerrar();
bool LeerPaises(ifstream &archivoALeerPaises);
bool LeerParteDiario(ifstream &archivoProcParDia);
string replicate(char car, unsigned short n);
void Listado ();
void borrarEspaciosDeStr(char* string);
bool IntCmb(tsParDia &elem1, tsParDia &elem2);
bool IntCmb(tsPais &elem1, tsPais &elem2);
bool OrdxBur(tsParDia v[], short card);
bool OrdxBur(tsPais v[], short card);
short BusBinVec (tsCalc datosASumar[], short primPos, short ultPos, char* arrayNomPais);
short BusBinVec (tsPais vConNumHab[], short primPos, short ultPos, char* arrayNomPais);
void ProcesarParteDiario (tsCalc totalPaises[], tsParDia datosAMas[]);
bool verifInstanciaPrevNom(tsCalc arregloCalc[], char* nomEnParDia);

//////////////////////////// MAIN ////////////////////////////

int main() {
    Abrir();
    ProcesarParteDiario(totalPaises, datosPaises);
    Listado();
    Cerrar();
    return 0;
} // Actualizar el main del diagrama de flujo

void Abrir() {
    archivoPaises.open("Paises.txt");
    if (!archivoPaises.is_open()) {cout << "El archivo Paises no pudo ser abierto.\n";
    return;}

    archivoParteDiario.open("ParteDiario.txt");
    if (!archivoParteDiario.is_open()) {cout << "El archivo ParteDiario no pudo ser abierto.\n";
    return;}

    if (LeerPaises(archivoPaises)) {
        cout << "El archivo Paises fue leido correctamente.\n";
    } else {
        cout << "El archivo Paises no pudo ser leido.\n";
        return;
    }

    if (LeerParteDiario(archivoParteDiario)) {
        cout << "El archivo ParteDiario fue leido correctamente.\n";
    } else {
        cout << "El archivo ParteDiario no pudo ser leido.\n";
        return;
    }

} // Abrir

void Cerrar() {
    archivoPaises.close();
    archivoParteDiario.close();
} // Cerrar

string replicate (char car, unsigned short n){

	string str="";

	for (int i=0; i<n ; i++)
		str+=car;

	return str;
} // replicate

void Listado() {

    int     totalDatosPaisesCalc,
            totalHabitPaisesCalc;
    double  porcentajeFinal;

   ofstream OutPD1 ("ListadoHisopados.txt");
    OutPD1   << replicate('-',57) <<"Listado de Hisopados" << replicate('-',44) << endl
             << replicate('=',123) << endl
             << "Nro.  Nom." << setw(29) << "Cant.Hab. " << setw(13) << replicate('-', 13) << " Cantidades de Hisopados por mes " << setw(13) << replicate('-', 20) << " Cant.   Porcentaje\n"
             << replicate('-',123) << endl
             << "Ord.  País                                Ene     Feb     Mar     Abr     May     Jun     Jul              Tot."<< endl
             << replicate('-',123) << endl;
    for (short i = 0; i < 30 ; i++ ) {
      OutPD1 << setw(3) <<  i+1 << setw (23) << paisFinal[i].nomPais
             << setw(11)<< paisFinal[i].cantHabitantes;
             for(short j = 1; j < 8; j++){
             OutPD1 << setw(8) << paisFinal[i].totalHisopadosMes[j];
             }
      OutPD1 << setw(16)<< paisFinal[i].totalhisopados << setw(13) << setprecision(4)
      << ((double)paisFinal[i].totalhisopados * 100) / (double)paisFinal[i].cantHabitantes << "%" << endl;

    }
    OutPD1 << endl;

    for (short i = 0; i < 30; i++) {
        totalHabitPaisesCalc += paisFinal[i].cantHabitantes;
        totalDatosPaisesCalc += paisFinal[i].totalhisopados;
    }
    porcentajeFinal = ((double)totalDatosPaisesCalc * 100) / (double)totalHabitPaisesCalc;

    OutPD1
    << "\t" << replicate('-',87) << endl
    << "\t" << "CANTIDAD TOTAL DE HISOPADOS: " << totalDatosPaisesCalc << endl
    << "\t" << replicate('-',87) << endl
    << "\t" << "PORCENTAJE TOTAL EN RELACION HABITANTES/HISOPADOS: " << totalDatosPaisesCalc << " * " << 100 << " \\ "
    << totalHabitPaisesCalc << " = " << std::fixed << setprecision(4) << porcentajeFinal << "%" << endl
    << "\t" << replicate('-',87) << endl;


    ofstream OutPD2 ("ListadoInfectados.txt");
    OutPD2   << replicate('-',57) <<"Listado de Infectados" << replicate('-',44) << endl
             << replicate('=',123) << endl
             << "Nro.  Nom." << setw(29) << "Cant.Hab. " << setw(13) << replicate('-', 13) << " Cantidades de Infectados por mes " << setw(13) << replicate('-', 20) << " Cant.   Porcentaje\n"
             << replicate('-',123) << endl
              << "Ord.  País                                Ene     Feb     Mar     Abr     May     Jun     Jul               Tot."<< endl
             << replicate('-',123) << endl;
     for (short i = 0; i < 30 ; i++ ) {
      OutPD2 << setw(3) <<  i+1 << setw (23) << paisFinal[i].nomPais
             << setw(11)<< paisFinal[i].cantHabitantes;
             for(short j = 1; j < 8; j++){
             OutPD2 << setw(8) << paisFinal[i].totalInfectadosMes[j];
             }
      OutPD2 << setw(16)<< paisFinal[i].totalinfectados << setw(13) << setprecision(4)
      << ((double)paisFinal[i].totalinfectados * 100) / (double)paisFinal[i].cantHabitantes << "%" << endl;
    }
    OutPD2 << endl;

    totalDatosPaisesCalc = 0;
    totalHabitPaisesCalc = 0;

    for (short i = 0; i < 30; i++) {
        totalHabitPaisesCalc += paisFinal[i].cantHabitantes;
        totalDatosPaisesCalc += paisFinal[i].totalinfectados;
    }
    porcentajeFinal = ((double)totalDatosPaisesCalc * 100) / (double)totalHabitPaisesCalc;

    OutPD2
    << "\t" << replicate('-',87) << endl
    << "\t" << "CANTIDAD TOTAL DE INFECTADOS: " << totalDatosPaisesCalc << endl
    << "\t" << replicate('-',87) << endl
    << "\t" << "PORCENTAJE TOTAL EN RELACION HABITANTES/INFECTADOS: " << totalDatosPaisesCalc << " * " << 100 << " \\ "
    << totalHabitPaisesCalc << " = " << std::fixed << setprecision(4) << porcentajeFinal << "%" << endl
    << "\t" << replicate('-',87) << endl;

    ofstream OutPD3 ("ListadoRecuperados.txt");
    OutPD3   << replicate('-',57) <<"Listado de Recuperados" << replicate('-',44) << endl
             << replicate('=',123) << endl
             << "Nro.  Nom." << setw(27) << "Cant.Hab. " << setw(13) << replicate('-', 13) << " Cantidades de Recuperados por mes " << setw(13) << replicate('-', 20) << " Cant.   Porcentaje\n"
             << replicate('-',123) << endl
             << "Ord.  País                                Ene     Feb     Mar     Abr     May     Jun     Jul             Tot."<< endl
             << replicate('-',123) << endl;
        for (short i = 0; i < 30 ; i++ ) {
      OutPD3 << setw(3) <<  i+1 << setw (23) << paisFinal[i].nomPais
             << setw(11)<< paisFinal[i].cantHabitantes;
             for(short j = 1; j < 8; j++){
             OutPD3 << setw(8) << paisFinal[i].totalRecuperadosMes[j];
             }
      OutPD3 << setw(16)<< paisFinal[i].totalrecuperados << setw(13) << setprecision(4)
      << ((double)paisFinal[i].totalrecuperados * 100) / (double)paisFinal[i].cantHabitantes << "%" << endl;
    }
    OutPD3 << endl;

    totalDatosPaisesCalc = 0;
    totalHabitPaisesCalc = 0;

    for (short i = 0; i < 30; i++) {
        totalHabitPaisesCalc += paisFinal[i].cantHabitantes;
        totalDatosPaisesCalc += paisFinal[i].totalrecuperados;
    }
    porcentajeFinal = ((double)totalDatosPaisesCalc * 100) / (double)totalHabitPaisesCalc;

    OutPD3
    << "\t" << replicate('-',87) << endl
    << "\t" << "CANTIDAD TOTAL DE RECUPERADOS: " << totalDatosPaisesCalc << endl
    << "\t" << replicate('-',87) << endl
    << "\t" << "PORCENTAJE TOTAL EN RELACION HABITANTES/RECUPERADOS: " << totalDatosPaisesCalc << " * " << 100 << " \\ "
    << totalHabitPaisesCalc << " = " << std::fixed << setprecision(4) << porcentajeFinal << "%" << endl
    << "\t" << replicate('-',87) << endl;

       ofstream OutPD4 ("ListadoFallecidos.txt");
     OutPD4  << replicate('-',57) <<"Listado de Fallecidos" << replicate('-',44) << endl
             << replicate('=',123) << endl
             << "Nro.  Nom." << setw(27) << "Cant.Hab. " << setw(13) << replicate('-', 13) << " Cantidades de Fallecidos por mes " << setw(13) << replicate('-', 20) << " Cant.   Porcentaje\n"
             << replicate('-',123) << endl
             << "Ord.  País                                Ene     Feb     Mar     Abr     May     Jun     Jul             Tot."<< endl
             << replicate('-',123) << endl;
        for (short i = 0; i < 30 ; i++ ) {
      OutPD4 << setw(3) <<  i+1 << setw (23) << paisFinal[i].nomPais
            << setw(11)<< paisFinal[i].cantHabitantes;
            for(short j = 1; j < 8; j++){
            OutPD4 << setw(8) << paisFinal[i].totalFallecidosMes[j];
            }
      OutPD4 << setw(16)<< paisFinal[i].totalfallecidos << setw(13) << setprecision(4)
      << ((double)paisFinal[i].totalfallecidos * 100) / (double)paisFinal[i].cantHabitantes << "%" << endl;
    }
    OutPD4 << endl;

    totalDatosPaisesCalc = 0;
    totalHabitPaisesCalc = 0;

    for (short i = 0; i < 30; i++) {
        totalHabitPaisesCalc += paisFinal[i].cantHabitantes;
        totalDatosPaisesCalc += paisFinal[i].totalfallecidos;
    }
    porcentajeFinal = ((double)totalDatosPaisesCalc * 100) / (double)totalHabitPaisesCalc;
    OutPD4
    << "\t" << replicate('-',87) << endl
    << "\t "<< "CANTIDAD TOTAL DE FALLECIDOS: "<< totalDatosPaisesCalc << endl
    << "\t" << replicate('-',87) << endl
    << "\t" << "PORCENTAJE TOTAL EN RELACION HABITANTES/FALLECIDOS: " << totalDatosPaisesCalc << " * " << 100 << " \\ "
    << totalHabitPaisesCalc << " = " << std::fixed << setprecision(4) << porcentajeFinal << "%" << endl
    << "\t" << replicate('-',87) << endl;

} // Listado

bool LeerPaises(ifstream &archivoALeerPaises) {

    short i = 0;
    while ( archivoALeerPaises.good() * (i < MAX_PAIS) ) {

        char cantHabitantesToInt[15];
        archivoALeerPaises.get(paises[i].nomPais, 19);
        borrarEspaciosDeStr(paises[i].nomPais);
        archivoALeerPaises.ignore();
        archivoALeerPaises >> paises[i].continente;
        archivoALeerPaises.ignore();
        archivoALeerPaises.get(cantHabitantesToInt, 20, '\n');
        archivoALeerPaises.ignore();
        paises[i].cantHabitantes = atoi(cantHabitantesToInt);

     i++;
     contPaisesPaises++;
    }

    OrdxBur(paises, contPaisesPaises);

    return true;
} // LeerPaises

bool LeerParteDiario(ifstream &archivoALeerParDia) {

    short i = 0;
    bool error;
    char    cantDatoToInt[15],
            buffer[20],
            nomPais[20];
    while (archivoALeerParDia.good() && (i < 2800)) {

        short   mesReg,
                diaReg,
                hisopadosReg,
                infectadosReg,
                recuperadosReg,
                fallecidosReg;

        archivoALeerParDia.get(nomPais, 19);
        borrarEspaciosDeStr(nomPais);
        archivoALeerParDia.ignore();
        archivoALeerParDia >> mesReg;
        archivoALeerParDia >> diaReg;
        archivoALeerParDia >> hisopadosReg;
        archivoALeerParDia >> infectadosReg;
        archivoALeerParDia >> recuperadosReg;
        archivoALeerParDia >> fallecidosReg;
        archivoALeerParDia.ignore();

        for (short j = 0; j < MAX_PAIS; j++){

            if (!strcmp(nomPais, paises[j].nomPais)) {

                strcpy(datosPaises[i].nomPais, nomPais);

                contParDiaPaises ++;

                switch (mesReg) {
                case 1:
                case 3:
                case 5:
                case 7:
                case 8:
                case 10:
                case 12:
                    if ( (diaReg >= 1) && (diaReg <= 31) ) {
                        datosPaises[i].hisopados[mesReg][diaReg] = hisopadosReg;
                        datosPaises[i].infectados[mesReg][diaReg] = infectadosReg;
                        datosPaises[i].recuperados[mesReg][diaReg] = recuperadosReg;
                        datosPaises[i].fallecidos[mesReg][diaReg] = fallecidosReg;
                    }
                    else {
                        error = true;
                        break;
                    }
                case 4:
                case 6:
                case 9:
                case 11:
                    if ( (diaReg >= 1) && (diaReg <= 30) ) {
                        datosPaises[i].hisopados[mesReg][diaReg] = hisopadosReg;
                        datosPaises[i].infectados[mesReg][diaReg] = infectadosReg;
                        datosPaises[i].recuperados[mesReg][diaReg] = recuperadosReg;
                        datosPaises[i].fallecidos[mesReg][diaReg] = fallecidosReg;
                    } else {
                        error = true;
                        break;
                    }
                case 2:
                    if ( (diaReg >= 1) && (diaReg <= 29) ) {
                        datosPaises[i].hisopados[mesReg][diaReg] = hisopadosReg;
                        datosPaises[i].infectados[mesReg][diaReg] = infectadosReg;
                        datosPaises[i].recuperados[mesReg][diaReg] = recuperadosReg;
                        datosPaises[i].fallecidos[mesReg][diaReg] = fallecidosReg;
                    } else {
                        error = true;
                        break;
                    }
                default:
                    break;
                }
            }
        }
        if (error == true) {
            cout << "Uno de los días o meses tiene un valor invalido!\n";
            return false;
        }

        i++;
   }

    OrdxBur(datosPaises, i + 1);

    return true;
} // LeerParteDiario

void borrarEspaciosDeStr(char* string){
    short counter = 0;
    for (short i = 0; string[i]; i++) {
        if (string[i] != ' ') string[counter++] = string[i];
        else
        string[counter] = '\0';
    }
} // borrarEspaciosDeStr

// uso totalPaises y datosPaises

void ProcesarParteDiario (tsCalc totalPaises[], tsParDia datosAMas[]){
    short contTotPaises = 0;
    short posRetornada;

    for (short i = 0; i < contParDiaPaises; i++) {

        if ( !verifInstanciaPrevNom(totalPaises, datosAMas[i].nomPais) ) {
            strcpy(totalPaises[contTotPaises].nomPais, datosAMas[i].nomPais);
            contTotPaises++;
        }

        posRetornada = BusBinVec(totalPaises, 0, contTotPaises, datosAMas[i].nomPais);

        if ( posRetornada == -1 ) {

            cout << "Error en posicion: " << contTotPaises << " al leer pais \"" << totalPaises[contTotPaises].nomPais << "\"\n";
            return;

        } else {

            for (short k = 1; k < 8; k++) {
                for (short j = 1; j < 31; j++) {
                    totalPaises[posRetornada].totalHisopadosMes[k] += datosAMas[i].hisopados[k][j];
                    totalPaises[posRetornada].totalInfectadosMes[k] += datosAMas[i].infectados[k][j];
                    totalPaises[posRetornada].totalRecuperadosMes[k] += datosAMas[i].recuperados[k][j];
                    totalPaises[posRetornada].totalFallecidosMes[k] += datosAMas[i].fallecidos[k][j];
                }
            }

        }

    }

    short posNomPaisEnVector;

    for (short i = 0; i < contTotPaises; i++) {
        strcpy(paisFinal[i].nomPais, totalPaises[i].nomPais);

        posNomPaisEnVector = BusBinVec(paises, 0, contPaisesPaises, paisFinal[i].nomPais);

        if (posNomPaisEnVector == -1) {
            cout << "Error en función ProcesarParteDiario! No se encontró el país dentro del vector \"tsPais paises[MAX_PAIS]\"\n";
            return;
        }
        paisFinal[i].cantHabitantes = paises[posNomPaisEnVector].cantHabitantes;

        for (short j = 1; j < 8; j++) {
            paisFinal[i].totalhisopados += totalPaises[i].totalHisopadosMes[j];
            paisFinal[i].totalinfectados += totalPaises[i].totalInfectadosMes[j];
            paisFinal[i].totalrecuperados += totalPaises[i].totalRecuperadosMes[j];
            paisFinal[i].totalfallecidos += totalPaises[i].totalFallecidosMes[j];
            paisFinal[i].totalHisopadosMes[j] += totalPaises[i].totalHisopadosMes[j];
            paisFinal[i].totalInfectadosMes[j] += totalPaises[i].totalInfectadosMes[j];
            paisFinal[i].totalRecuperadosMes[j] += totalPaises[i].totalRecuperadosMes[j];
            paisFinal[i].totalFallecidosMes[j] += totalPaises[i].totalFallecidosMes[j];
        }
    }

} // ProcesarParteDiario

bool OrdxBur(tsParDia v[], short card) {
    short k = 0;
    bool swap;

    do {
        k++;
        swap = false;
        for (short i = 0; i < card - k - 1; i++){
            if (strcmp(v[i].nomPais, v[i+1].nomPais) > 0){
                IntCmb(v[i], v[i+1]);
                swap = true;
            }
        }
    } while (swap);

    return true;
} // OrdxBur

bool OrdxBur(tsPais v[], short card) {
    short k = 0;
    bool swap;

    do {
        k++;
        swap = false;
        for (short i = 0; i < card - k - 1; i++) {
            if (strcmp(v[i].nomPais, v[i+1].nomPais) > 0 ){
                IntCmb(v[i], v[i+1]);
                swap = true;
            }
        }
    } while (swap);

    return true;
} // OrdxBur

bool IntCmb(tsParDia &elem1, tsParDia &elem2) {
    tsParDia aux = elem1;
    elem1 = elem2;
    elem2 = aux;
    return true;
} // IntCmb

bool IntCmb(tsPais &elem1, tsPais &elem2) {
    tsPais aux = elem1;
    elem1 = elem2;
    elem2 = aux;
    return true;
} // IntCmb

short BusBinVec (tsCalc datosASumar[], short primPos, short ultPos, char* arrayNomPais){
    short medPos;

    while (primPos < ultPos) {
        medPos = (primPos + ultPos) / 2;

        if (strcmp(arrayNomPais, datosASumar[medPos].nomPais) == 0) {
            return medPos;
        }
        if (strcmp(datosASumar[medPos].nomPais, arrayNomPais) < 0 ) {
            primPos = medPos + 1;
        } else {
            ultPos = medPos - 1;
        }
    }

    return -1;
} // BusBinVec

short BusBinVec (tsPais vConNumHab[], short primPos, short ultPos, char* arrayNomPais) {
    short medPos;

    while (primPos < ultPos) {
        medPos = (primPos + ultPos) / 2;

        if (strcmp(arrayNomPais, vConNumHab[medPos].nomPais) == 0) {
            return medPos;
        }
        if (strcmp(vConNumHab[medPos].nomPais, arrayNomPais) < 0) {
            primPos = medPos + 1;
        } else {
            ultPos = medPos - 1;
        }
    }

     if (strcmp(arrayNomPais, vConNumHab[ultPos].nomPais) == 0) {
         return ultPos;
     }

    return -1;
} // BusBinVec

bool verifInstanciaPrevNom(tsCalc arregloCalc[], char* nomEnParDia) {
    for (short i = 0; i < contParDiaPaises; i++) {
        if (strcmp(nomEnParDia, arregloCalc[i].nomPais) == 0) return true;
    }
    return false;
} // verifInstanciaPrevNom
