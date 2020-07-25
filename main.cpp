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
	int		hisopados[7][31],
			infectados[7][31],
			recuperados[7][31],
			fallecidos[7][31];
} tsParDia;

typedef struct {
	char	nomPais[20];
	int		totalHisopadosMes[7],
			totalInfectadosMes[7],
			totalRecuperadosMes[7],
			totalFallecidosMes[7];
} tsCalc;

typedef struct {
    char    nomPais[20];
    int		cantHabitantes,
            totalhisopados,
			totalinfectados,
			totalrecuperados,
			totalfallecidos,
            totalHisopadosMes[7],
			totalInfectadosMes[7],
			totalRecuperadosMes[7],
			totalFallecidosMes[7];
} tvrPais;

ifstream archivoPaises;
ifstream archivoParteDiario;
static int  contParDiaPaises,
            contPaisesPaises;
static tsPais paises[200];
static tsParDia datosPaises[200];
static tsCalc totalPaises[200];
static tvrPais paisFinal[200];

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

    ofstream OutPD1 ("ListadoHisopados.txt");
    OutPD1   << setw(82) <<"Listado de Hisopados" << endl
             << replicate('=',123) << endl
             << "Nro.  Nom." << setw(35) << "Cant.Hab. " << setw(13) << replicate('-', 13) << " Cantidades de Hisopados por mes " << setw(13) << replicate('-', 13) << " Cant.   Porcentajes\n"
             << replicate('-',123) << endl
             << "Ord.  País                               Ene      Feb     Mar      Abr     May      Jun       Jul     Tot.                "<< endl
             << replicate('-',123) << endl;
    for (short i = 0; i < 30 ; i++ ) {
      OutPD1 << setw(3) <<  i+1 << setw (20) << datosPaises[i].nomPais << ' '
             << paises[i].cantHabitantes
             << "\t" <<  "teatrfag"  << ' ' << endl;
    }


    ofstream OutPD2 ("ListadoInfectados.txt");
    OutPD2   << setw(82) <<"Listado de Infectados" << endl
             << replicate('=',123) << endl
             << "Nro.  Nom.                 Cant.Hab.     ------------- Cantidades de Infectados por mes ------------   Cant.   Porcentajes" << endl
             << replicate('-',123) << endl
             << "Ord.  País                                Ene      Feb     Mar      Abr     May      Jun       Jul     Tot.                "<< endl
             << replicate('-',123) << endl;
     for  (short i = 0; i < 30 ; i++ ) {
     OutPD2  << setw(3) <<  i+1 << setw (20) << datosPaises[i].nomPais << ' '
             << paises[i].cantHabitantes
             << "\t" << "datosPaises.infectados" << ' ' << endl;
    }

    ofstream OutPD3 ("ListadoRecuperados.txt");
    OutPD3   << setw(82) <<"Listado de Recuperados" << endl
             << replicate('=',123) << endl
             << "Nro.  Nom.                 Cant.Hab.     ------------- Cantidades de Recuperados por mes ------------   Cant.   Porcentajes" << endl
             << replicate('-',123) << endl
             << "Ord.  País                                Ene      Feb     Mar      Abr     May      Jun       Jul     Tot.                "<< endl
             << replicate('-',123) << endl;
     for (short i = 0; i < 30 ; i++ ) {
      OutPD3 << setw(3) <<  i+1 << setw (20) << datosPaises[i].nomPais << ' '
             << paises[i].cantHabitantes
             << "\t" <<  "da" << ' ' << endl;
    }

       ofstream OutPD4 ("ListadoFallecidos.txt");
     OutPD4   << setw(82) << "Listado de Fallecidos" << endl
             << replicate('=',123) << endl
             << "Nro.  Nom.                 Cant.Hab.     ------------- Cantidades de Fallecidos por mes ------------   Cant.   Porcentajes" << endl
             << replicate('-',123) << endl
             << "Ord.  País                                Ene      Feb     Mar      Abr     May      Jun       Jul     Tot.                "<< endl
             << replicate('-',123) << endl;
     for (short i = 0; i < 30 ; i++ ) {
      OutPD4 << setw(3) <<  i+1 << setw (20) << datosPaises[i].nomPais << ' '
             << "\t" <<  "teatrfag"  << ' ' << endl;
    }
} // Listado

bool LeerPaises(ifstream &archivoALeerPaises) {

    short i = 0;
    while ( archivoALeerPaises.good() * (i < MAX_PAIS) ) {

        char cantHabitantesToInt[15];
        archivoALeerPaises.get(paises[i].nomPais, 20);
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

    for (short i = 0; i < contPaisesPaises; i++) {
        cout << paises[i].nomPais << " en posicion: " << i << endl;
    }

    OrdxBur(paises, contPaisesPaises);

    return true;
} // LeerPaises

bool LeerParteDiario(ifstream &archivoALeerParDia) {

    short i = 0;
    bool paisCoincide;
    bool error;
    char    cantDatoToInt[15];
    char    buffer[20],
            nomPais[20];
    while (archivoALeerParDia.good() && (i < MAX_PAIS)) {

        short   loopCounter,
                mesReg,
                diaReg,
                hisopadosReg,
                infectadosReg,
                recuperadosReg,
                fallecidosReg;

        archivoALeerParDia.get(nomPais, 20);
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
                }
                for (short j = 1; j < 31; j++) {
                    totalPaises[posRetornada].totalInfectadosMes[k] += datosAMas[i].infectados[k][j];
                }
                for (short j = 1; j < 31; j++) {
                    totalPaises[posRetornada].totalRecuperadosMes[k] += datosAMas[i].recuperados[k][j];
                }
                for (short j = 1; j < 31; j++) {
                    totalPaises[posRetornada].totalFallecidosMes[k] += datosAMas[i].fallecidos[k][j];
                }
            }

        }

    }

    /*
    typedef struct {
    char    nomPais[20];
    int		cantHabitantes,
            totalhisopados,
			totalinfectados,
			totalrecuperados,
			totalfallecidos,
            totalHisopadosMes[7],
			totalInfectadosMes[7],
			totalRecuperadosMes[7],
			totalFallecidosMes[7];
} tvrPais;
    */
    short posNomPaisEnVector;

    for (short i = 0; i < contParDiaPaises; i++) {
        strcpy(paisFinal[i].nomPais, totalPaises[i].nomPais);

        cout << "Se busca el pais: " << paisFinal[i].nomPais << endl;
        
        posNomPaisEnVector = BusBinVec(paises, 0, contPaisesPaises, paisFinal[i].nomPais);

        if (posNomPaisEnVector == -1) {
            cout << "Error en función ProcesarParteDiario! No se encontró el país dentro del vector \"tsPais paises[MAX_PAIS]\"\n";
            return;
        }
        paisFinal[i].cantHabitantes = paises[posNomPaisEnVector].cantHabitantes;
        
        cout << totalPaises[i].nomPais << " \\ " << paisFinal[i].nomPais << endl;

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
            ultPos = medPos -1;
        }
    }

    return -1;
} // BusBinVec

bool verifInstanciaPrevNom(tsCalc arregloCalc[], char* nomEnParDia) {
    for (short i = 0; i < contParDiaPaises; i++) {
        if (strcmp(nomEnParDia, arregloCalc[i].nomPais) == 0) return true;
    }
    return false;
} // verifInstanciaPrevNom