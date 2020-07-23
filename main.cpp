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

static int contParDiaPaises;
static tvrPais paisFinal[200];
static tsPais paises[200];
static tsParDia datosPaises[200];
static tsCalc totalPaises[200];

void Abrir();
void Cerrar();
bool LeerPaises(ifstream &archivoALeerPaises);
bool LeerParteDiario(ifstream &archivoProcParDia);
string replicate(char car, unsigned short n);
void Listado ();
void borrarEspaciosDeStr(char* string);
bool IntCmbLPD(tsParDia &elem1, tsParDia &elem2);
bool OrdxBurLPD(tsParDia v[], short card);
short BusBinVecPPD (tsCalc datosASumar[], short primPos, short ultPos, char* arrayNomPais);
void ProcesarParteDiario (tsCalc totalPaises[], tsParDia datosAMas[]);
bool verifInstanciaPrevNom(tsCalc arregloCalc[], char* nomEnParDia);

//////////////////////////// MAIN ////////////////////////////

int main() {
    Abrir();
    Listado();
    ProcesarParteDiario(totalPaises, datosPaises);
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

}

void Cerrar() {
    archivoPaises.close();
    archivoParteDiario.close();
}

string replicate (char car, unsigned short n){

	string str="";

	for (int i=0; i<n ; i++)
		str+=car;

	return str;
}

void Listado() {

    ofstream OutPD1 ("ListadoHisopados.txt");
    OutPD1   << setw(82) <<"Listado de Hisopados" << endl
             << replicate('=',123) << endl
             << "Nro.  Nom.                 Cant.Hab.    ------------- Cantidades de Hisopados por mes ------------   Cant.   Porcentajes" << endl
             << replicate('-',123) << endl
             << "Ord.  País                               Ene      Feb     Mar      Abr     May      Jun       Jul     Tot.                "<< endl
             << replicate('-',123) << endl;
    for (short i = 0; i < 30 ; i++ ) {
      OutPD1 << setw(3) <<  i+1 << setw (20) << datosPaises[i].nomPais << ' '
             << paises[i].cantHabitantes
             << "\t" <<  "teatrfag"  << ' ' << endl; //datosPaises[i].hisopados[2][15]
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
             << "\t" << "datosPaises.infectados" << ' ' << endl;//datosPaises[i].infectados[2][15]
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
             << "\t" <<  "da" << ' ' << endl;// datosPaises[i].recuperados[2][15]
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
             << "\t" <<  "teatrfag"  << ' ' << endl;//datosPaises[i].fallecidos[2][15]
    }
}

bool LeerPaises(ifstream &archivoALeerPaises) {

    short i = 0;
    while ( archivoALeerPaises.good() * (i < MAX_PAIS) ) {



        char cantHabitantesToInt[15];
        archivoALeerPaises.get(paises[i].nomPais, 20);
        paises[i].nomPais[19] = '\0';
        borrarEspaciosDeStr(paises[i].nomPais);
        archivoALeerPaises.ignore();
        archivoALeerPaises >> paises[i].continente;
        archivoALeerPaises.ignore();
        archivoALeerPaises.get(cantHabitantesToInt, 20, '\n');
        archivoALeerPaises.ignore();
        paises[i].cantHabitantes = atoi(cantHabitantesToInt);

        // Descomentar debajo para probar función
        // cout << i << " \\ " << paises[i].nomPais << " \\ " << paises[i].continente << " \\ " << paises[i].cantHabitantes << endl;
     i++;
     }
    return true;
}

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
        archivoALeerParDia.ignore();
        archivoALeerParDia >> hisopadosReg;
        archivoALeerParDia.ignore();
        archivoALeerParDia >> infectadosReg;
        archivoALeerParDia.ignore();
        archivoALeerParDia >> recuperadosReg;
        archivoALeerParDia.ignore();
        archivoALeerParDia >> fallecidosReg;
        archivoALeerParDia.ignore();

        /*
        cout << nomPais << " \\ " << "Linea numero " << i << endl;
        cout << mesReg << endl;
        cout << diaReg << endl;
        cout << hisopadosReg << endl;
        cout << infectadosReg << endl;
        cout << recuperadosReg << endl;
        cout << fallecidosReg << endl;
        */

        for (short j = 0; j < MAX_PAIS; j++){

            if (!strcmp(nomPais, paises[j].nomPais)) {

                strcpy(datosPaises[i].nomPais, nomPais);

                contParDiaPaises ++;

                // Descomentar debajo para probar función
                // cout << "Pais encontrado en linea: " << j << endl;

                switch (mesReg) {
                case 1:
                case 3:
                case 5:
                case 7:
                case 8:
                case 10:
                case 12:
                    if ( (diaReg >= 1) || (diaReg <= 31) ) {

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
                    if ( (diaReg >= 1) || (diaReg <= 30) ) {

                        datosPaises[i].hisopados[mesReg][diaReg] = hisopadosReg;
                        datosPaises[i].infectados[mesReg][diaReg] = infectadosReg;
                        datosPaises[i].recuperados[mesReg][diaReg] = recuperadosReg;
                        datosPaises[i].fallecidos[mesReg][diaReg] = fallecidosReg;
                    } else {
                        error = true;
                        break;
                    }
                case 2:
                    if ( (diaReg >= 1) || (diaReg <= 29) ) {

                        datosPaises[i].hisopados[mesReg][diaReg] = hisopadosReg;
                        datosPaises[i].infectados[mesReg][diaReg] = infectadosReg;
                        datosPaises[i].recuperados[mesReg][diaReg] = recuperadosReg;
                        datosPaises[i].fallecidos[mesReg][diaReg] = fallecidosReg;

                        for (short i = 0; i < contParDiaPaises; i++){
                        
                        /*
                        cout << datosPaises[i].nomPais << "\\" << datosPaises[i].hisopados[mesReg][diaReg]<< "\\" << mesReg << "\\" << diaReg <<"en linea: "<< i << endl;
                        cout << datosPaises[i].nomPais << "\\" << datosPaises[i].infectados[mesReg][diaReg] << "\\" << mesReg << "\\" << diaReg <<"en linea: "<< i << endl;
                        cout << datosPaises[i].nomPais << "\\" << datosPaises[i].recuperados[mesReg][diaReg] << "\\" << mesReg << "\\" << diaReg <<"en linea: "<< i << endl;
                        cout << datosPaises[i].nomPais << "\\" << datosPaises[i].fallecidos[mesReg][diaReg] << "\\" << mesReg << "\\" << diaReg <<"en linea: "<< i << endl;
                        */
                       }
                       // cout << datosPaises[17].hisopados[3][21] << endl;
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

    OrdxBurLPD(datosPaises, i + 1);

    //cout << datosPaises[0].hisopados[3][21] << endl;

    return true;
}

void borrarEspaciosDeStr(char* string){
    short counter = 0;
    for (short i = 0; string[i]; i++) {
        if (string[i] != ' ') string[counter++] = string[i];
        else
        string[counter] = '\0';
    }
} // borrarEspaciosDeStr

bool OrdxBurLPD(tsParDia v[], short card) {
    short k = 0;
    bool swap;

    do{
        k++;
        swap = false;
        for (short i = 0; i < card - k - 1; i++){
            if (strcmp(v[i].nomPais, v[i+1].nomPais) > 0){
                IntCmbLPD(v[i], v[i+1]);
                swap = true;
            }
        }
    } while (swap);

    return true;
} // OrdxBur
bool IntCmbLPD(tsParDia &elem1, tsParDia &elem2) {
    tsParDia aux = elem1;
    elem1 = elem2;
    elem2 = aux;
    return true;
} // IntCmb

// uso totalPaises y datosPaises

void ProcesarParteDiario (tsCalc totalPaises[], tsParDia datosAMas[]){
    short posicionRetornada;
    int numeroChistoso = 0;

    for ( short i = 0; i < contParDiaPaises ; i++ ){

        // TODO:    Verificar antes del strcpy si existe un pais en el arreglo de "nomPais" de totalPaises
        //          Que strcpy solo corra si no existe el pais en el arreglo.

        cout << totalPaises[i].nomPais << " \\ " << datosAMas[i].nomPais << endl;

        if ( !verifInstanciaPrevNom(totalPaises, datosAMas[i].nomPais) ) {   
            strcpy(totalPaises[i].nomPais, datosAMas[i].nomPais);
        }

        posicionRetornada = BusBinVecPPD(totalPaises, 0, contParDiaPaises, datosAMas[i].nomPais);

        cout << totalPaises[posicionRetornada].nomPais << " found at: " << posicionRetornada 
        << " \\ " << datosAMas[i].nomPais << endl;
        //cout << posicionRetornada << endl;
        if (posicionRetornada != -1) {
            for ( short k = 1 ; k < 8 ; k++ ){
                for ( short j = 1; j < 31 ; j++ ) {
                    if (datosPaises[posicionRetornada].hisopados[k][j] != 0) {
                        totalPaises[posicionRetornada].totalHisopadosMes[k] += datosPaises[i].hisopados[k][j];
                        // cout << totalPaises[posicionRetornada].nomPais << " \\ " 
                        // << totalPaises[posicionRetornada].totalHisopadosMes[k] << endl;
                        numeroChistoso += datosPaises[posicionRetornada].hisopados[k][j];
                    }
                }
                // cout << "numeroChistoso = " << numeroChistoso << endl;
            }
        }
    }
} // ProcesarParteDiario

short BusBinVecPPD (tsCalc datosASumar[], short primPos, short ultPos, char* arrayNomPais){

    while (primPos < ultPos) {
        short medPos = (primPos + ultPos) / 2;

        if (strcmp(datosASumar[medPos].nomPais, arrayNomPais) == 0) {
            return medPos;
        }
        if (strcmp(datosASumar[medPos].nomPais, arrayNomPais) < 0 ) {
            primPos = medPos + 1;
        } else {
             ultPos = medPos - 1;
        }
    }
    return -1;
} // BusBinVecPPD

bool verifInstanciaPrevNom(tsCalc arregloCalc[], char* nomEnParDia) {
    for (short i = 0; i < contParDiaPaises; i++) {
        if (strcmp(arregloCalc[i].nomPais, nomEnParDia) == 0) return true;
    }
    return false;
}