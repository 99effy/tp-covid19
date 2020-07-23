#include <iostream>
#include <fstream>
#include <iomanip>
#include <string.h>

using namespace std;

#define MAX_PAIS 200

typedef struct {
	char	nomPais[20],
			continente[10];
	int 	cantHabitantes;
} tsPais;

typedef struct {
	char nomPais[20];
	int		hisopados[7][31],
			infectados[7][31],
			recuperados[7][31],
			fallecidos[7][31];
} tsParDia;

typedef struct {
	char	nomPais[20];
	int		totalHisopados,
			totalInfectados,
			totalRecuperados,
			totalFallecidos;
} tsCalc;

ifstream archivoPaises;
ifstream archivoParteDiario;
static tsPais   paises[200];
static tsParDia datosPaises[200];
static tsCalc   totalPaises[200];

void Abrir();
void Cerrar();
bool LeerPaises(ifstream &archivoALeerPaises);
bool LeerParteDiario(ifstream &archivoProcParDia);
string replicate(char car, unsigned short n);
bool checkBufferEqualsContinente(char* buffer);
void borrarEspaciosDeStr(char* string);
bool OrdxBur (int v [], short card);
bool IntCmb (int &elem1, int &elem2);
// BusBinVecPD (tvCodInc vCI , char clv[5], byte ult);

//////////////////////////// MAIN ////////////////////////////

int main() {
    Abrir();

    Cerrar();
    return 0;
}

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

bool LeerPaises(ifstream &archivoALeerPaises) {

    short i = 0;
    while ( archivoALeerPaises.good() * (i < MAX_PAIS) ) {
        
        i++;

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
    }
    return true;
}

bool LeerParteDiario(ifstream &archivoALeerParDia) {
    
    short i = 0;
    bool error;
    char   nomPais[20];

    while (archivoALeerParDia.good() && (i < MAX_PAIS)) {
        
        short   mesReg,
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

        // Descomentar debajo para probar función
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
                
                // Descomentar debajo para probar función
                cout << "Pais encontrado en linea: " << j << endl;

                switch (mesReg) {
                case 1:
                case 3:
                case 5:
                case 7:
                case 8:
                case 10:
                case 12:
                    if ( (diaReg >= 0) || (diaReg <= 31) ) {
                        
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
                    if ( (diaReg >= 0) || (diaReg <= 30) ) {
                        
                        datosPaises[i].hisopados[mesReg][diaReg] = hisopadosReg;
                        datosPaises[i].infectados[mesReg][diaReg] = infectadosReg;
                        datosPaises[i].recuperados[mesReg][diaReg] = recuperadosReg;
                        datosPaises[i].fallecidos[mesReg][diaReg] = fallecidosReg;
                    } else {
                        error = true;
                        break;
                    }
                case 2:
                    if ( (diaReg >= 0) || (diaReg <= 29) ) {
                        
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
    return true;
}

void borrarEspaciosDeStr(char* string){ 
    short counter = 0;
    for (short i = 0; string[i]; i++) {
        if (string[i] != ' ') string[counter++] = string[i];
        else
        string[counter] = '\0';
    }
}

/*bool BusBinVecPD (tvCodInc vCI , char clv[5], byte ult){ //Tenemos que definir tipo:vectores?
    byte pri = 0
         med;
    while (pri <= ult) {
         med = (pri + ult) / 2;
         if (vCI[med] == clv)
            return med;
         else
            if (vCI[med] < clv)
             pri = med + 1;
             else
             ult = med - 1;
    }
    return true;
}/* FIXME: Este es la estructura, todavia faltan los argumentos
(tienen que ser tipo vextores [tv CodInc vCI, por ejemplo])*/

bool OrdxBur (int v [], short card) {
    short k = 1;
    bool ordenado;

    do{
        k++;
        for (short i = 0; i < card - k; i++){
            cout << i << "*";
            if (v[i] < v[i+1]){
                IntCmb (v[i], v[i+1]);
                ordenado = false;
            }
        }
        for (short i = 0; i < card; i++)
            cout << i << " " << v[i] << endl;
        getchar();
    }
    while (!ordenado);
    return true;
} // OrdxBur

bool IntCmb (int &elem1, int &elem2) {
    int aux = elem1;
    elem1 = elem2;
    elem2 = aux;
    return true;
} // IntCmb