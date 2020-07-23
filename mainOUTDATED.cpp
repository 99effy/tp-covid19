#include <iostream>
#include <iomanip>
#include <string>
#include <string.h>
#include <fstream>

#define MAX_PAIS 200
#define MAX_MES 7
#define MAX_DIA 31

using namespace std;

typedef struct {
	char	nomPais[20],
			continente[10];
	int 	cantHabitantes;
} tsPais;

typedef struct {
	char nomPais[20];
	int		hisopados[7],
			infectados[7],
			recuperados[7],
			fallecidos[7];
} tsParDia;

typedef struct {
	char	nomPais[20];
	int		totalHisopados,
			totalInfectados,
			totalRecuperados,
			totalFallecidos;
} tsCalc;

typedef struct {
	char	nomPais[20],
			continente[10];
	int		cantHabitantes,
			hisopados[7],
			infectados[7],
			recuperados[7],
			fallecidos[7],
			totalHisopados,
			totalInfectados,
			totalRecuperados,
			totalFallecidos;
} tvrPais;

tsPais paises[200];
static tvrPais paisCompleto[200];
FILE* archivoPaises;
FILE* archivoParteDiario;

bool Abrir();
bool LeerPaises(FILE *archivoPaisesALeer);
tsParDia *LeerParteDiario(FILE *archivoParteDiarioALeer);
void ProcParteDiario(tsParDia *informeAProcesar);
void OrdxBur(tvrPais v[], short card);
void IntCmb(tvrPais elem1, tvrPais elem2);
void Listado();

int main() {
	
	if ( !Abrir() ) return 0;
	
	LeerPaises(archivoPaises);
	
	tsParDia* informeListo = LeerParteDiario(archivoParteDiario);
	
	ProcParteDiario(informeListo);

	// Listado();

	return 0;
}

bool Abrir() {
	
	archivoPaises = fopen("Paises.txt", "r");
	archivoParteDiario = fopen("ParteDiario.txt", "r");

    if (archivoPaises == NULL) {
       cout << "El archivo Paises no pudo ser abierto\n";
        return false;
    } else if (archivoParteDiario == NULL) {
       cout << "El archivo ParteDiario no pudo ser abierto\n";
        return false;
    }

	return true;
}

bool LeerPaises(FILE *archivoPaisesALeer) {

	char line[300];
	for (short j = 0; j < 200; j++){
		fgets(line, 200,archivoPaisesALeer);
		for (short k = 0; k <= 20; k++){
			paises[j].nomPais[k] = line[k];
			paises[j].nomPais[20] = '\0';
		}
        for (short k = 0; k <=10; k++){
			paises[j].continente[k] = line[k+33];
			paises[j].continente[9] = '\0';
        }
    char arreglo[10];
        for (short k = 0; k < 10; k++) {
                arreglo[k] = line[k+42];
                paises[j].cantHabitantes = atoi(arreglo) ;
                }
		cout << paises[j].nomPais;
        cout << paises[j].continente;
        cout << paises[j].cantHabitantes << endl;
	}
	return true;
}

tsParDia *LeerParteDiario(FILE *archivoParteDiarioALeer) {

	static tsParDia datosDePais[200];
	static tsParDia* pDatosDePais = datosDePais;

	// Saltea la primera linea e inicializa la variable lineLength
	// para determinar cuántos carácteres leer a continuación
	char bufferLine[300];
	fgets(bufferLine, 300, archivoParteDiarioALeer);
	char line[184];

	// TODO: Eliminar variable lineNumber junto a todos sus llamados, luego de
	// terminar el módulo LeerParteDiario
	short lineNumber = 1;

	// Loop principal encargado de asignar los datos del archivo ParteDiario
	// al array de estructuras "datosDePais[200]"
	for (short i = 0; i < MAX_PAIS; i++) {
		
		fgets(line, 184, archivoParteDiarioALeer);

		for (short j = 0; j < 20; j++) {
			datosDePais[i].nomPais[j] = line[j];	
		}
		datosDePais[i].nomPais[19] = '\0';

		short indicarPosHisopados = ( (short)strlen(datosDePais[i].nomPais));
		short indicarPosInfectados = indicarPosHisopados + 49;
		short indicarPosRecuperados = indicarPosInfectados + 42;
		short indicarPosFallecidos = indicarPosRecuperados + 35;

		// TODO: Si es posible, convertir la inicializacion del array, el loop, y 
		// la asignacion del array a su dato de datosDePais correspondiente, en una función

		short j = indicarPosHisopados;
		for (short m = 0; m < 7; m++) {
			char arrayToIntHisopados[7];

			for (short k = 0; k < 7; j++, k++) {
				arrayToIntHisopados[k] = line[j];
			}
			datosDePais[i].hisopados[m] = atoi(arrayToIntHisopados);
		}

		for (short m = 0; m < 7; m++) {
			char arrayToIntInfectados[6];
			
			for (short k = 0; k < 6; k++, j++) {
				arrayToIntInfectados[k] = line[j];
			}
			datosDePais[i].infectados[m] = atoi(arrayToIntInfectados);
		}

		for (short m = 0; m < 7; m++) {
			char arrayToIntRecuperados[5];

			for (short k = 0; k < 5; k++, j++) {
				arrayToIntRecuperados[k] = line[j];
			}
			datosDePais[i].recuperados[m] = atoi(arrayToIntRecuperados);
		}

		for (short m = 0; m < 7; m++) {
			char arrayToIntFallecidos[5];

			for (short k = 0; k < 5; k++, j++) {
				arrayToIntFallecidos[k] = line[j];
			}
			datosDePais[i].fallecidos[m] = atoi(arrayToIntFallecidos);
		}
	}

	return pDatosDePais;
}

// Función que lee los informes de cada país, los computa y almacena 
// en una estructura de datos interna y estática.
void ProcParteDiario(tsParDia informeAProcesar[200]) {

	static tsCalc paisComputado[200];

	for (short i = 0; i < 200; i++) {
		int* pDatoTotal[4] = {&paisComputado[i].totalHisopados, &paisComputado[i].totalInfectados, &paisComputado[i].totalRecuperados,
		&paisComputado[i].totalFallecidos};	
		
		strcpy(paisComputado[i].nomPais, informeAProcesar[i].nomPais);
		strcpy(paisCompleto[i].nomPais, informeAProcesar[i].nomPais);
		strcpy(paisCompleto[i].continente, paises[i].continente);
		paisCompleto[i].cantHabitantes = paises[i].cantHabitantes;
		
		for (short j = 0; j < 7; j++) {
			paisCompleto[i].hisopados[j] = informeAProcesar[i].hisopados[j];
		}
		for (short j = 0; j < 7; j++) {
			paisCompleto[i].infectados[j] = informeAProcesar[i].infectados[j];
		}
		for (short j = 0; j < 7; j++) {
			paisCompleto[i].recuperados[j] = informeAProcesar[i].recuperados[j];
		}
		for (short j = 0; j < 7; j++) {
			paisCompleto[i].fallecidos[j] = informeAProcesar[i].fallecidos[j];
		}

		*pDatoTotal[0] = 0;
		for (short k = 0; k < 7; k++) {
			*pDatoTotal[0] += informeAProcesar[i].hisopados[k];
		}
		
		*pDatoTotal[1] = 0;
		for (short k = 0; k < 7; k++) {
			*pDatoTotal[1] += informeAProcesar[i].infectados[k];
		}
		
		*pDatoTotal[2] = 0;
		for (short k = 0; k < 7; k++) {
			*pDatoTotal[2] += informeAProcesar[i].recuperados[k];
		}

		*pDatoTotal[3] = 0;
		for (short k = 0; k < 7; k++) {
			*pDatoTotal[3] += informeAProcesar[i].fallecidos[k];
		}

		paisCompleto[i].totalHisopados = *pDatoTotal[0];
		paisCompleto[i].totalInfectados = *pDatoTotal[1];
		paisCompleto[i].totalRecuperados = *pDatoTotal[2];
		paisCompleto[i].totalFallecidos = *pDatoTotal[3];


	}

	OrdxBur(paisCompleto, MAX_PAIS);
}

void OrdxBur(tvrPais v[], short card) {
	short contadorOrden;
	
	do {

		contadorOrden = 0;

		for (short i = 0; i < card; i++) {
			if (v[i].totalHisopados < v[i + 1].totalHisopados) {
				IntCmb(v[i], v[i+1]);
				contadorOrden++;
				// cout << v[i].nomPais << " \\ " << i << endl;
			}
			// cout << v[i].nomPais << " \\ " << i << endl;
		}
		
	}
	while (contadorOrden < 1);

	for (short i = 0; i < card; i++) {
		cout << v[i].nomPais << " \\ " << i << endl;
	}
}

void IntCmb(tvrPais elem1, tvrPais elem2) {

	// Por ahora no encuentro una mejor solución para hacer el intercambio de los datos
	// para el ordenamiento por burbuja.
	// Si alguien tiene una mejor idea que no tarde mucho en implementarse 
	// por favor comentela con el grupo.

	char bufferNomPais[20], bufferContinente[10];
	strcpy(bufferNomPais, elem1.nomPais);
	strcpy(elem1.nomPais, elem2.nomPais);
	strcpy(elem2.nomPais, bufferNomPais);

	strcpy(bufferContinente, elem1.continente);
	strcpy(elem1.continente, elem2.continente);
	strcpy(elem2.continente, elem1.continente);

	int bufferCantHabitantes, bufferHisopados[7], bufferInfectados[7], bufferRecuperados[7], bufferFallecidos[7], 
	bufferTotalHisopados, bufferTotalInfectados, bufferTotalRecuperados, bufferTotalFallecidos;
	bufferCantHabitantes = elem1.cantHabitantes;
	elem1.cantHabitantes = elem2.cantHabitantes;
	
	for (short i = 0; i < 7; i++) {
		bufferHisopados[i] = elem1.hisopados[i];
		bufferInfectados[i] = elem1.infectados[i];
		bufferRecuperados[i] = elem1.recuperados[i];
		bufferFallecidos[i] = elem1.fallecidos[i];

		elem1.hisopados[i] = elem2.hisopados[i];
		elem1.infectados[i] = elem2.infectados[i];
		elem1.recuperados[i] = elem2.recuperados[i];
		elem1.fallecidos[i] = elem2.fallecidos[i];

		elem2.hisopados[i] = bufferHisopados[i];
		elem2.infectados[i] = bufferInfectados[i];
		elem2.recuperados[i] = bufferRecuperados[i];
		elem2.fallecidos[i] = bufferFallecidos[i];
	}

	bufferTotalHisopados = elem1.totalHisopados;
	elem1.totalHisopados = elem2.totalHisopados;
	elem2.totalHisopados = bufferTotalHisopados;	

	bufferTotalInfectados = elem1.totalInfectados;
	elem1.totalInfectados = elem2.totalInfectados;
	elem2.totalInfectados = bufferTotalInfectados;

	bufferTotalRecuperados = elem1.totalRecuperados;
	elem1.totalRecuperados = elem2.totalRecuperados;
	elem2.totalRecuperados = bufferTotalRecuperados;

	bufferTotalFallecidos = elem1.totalFallecidos;
	elem1.totalFallecidos = elem2.totalFallecidos;
	elem2.totalFallecidos = bufferTotalFallecidos;			
}

void Listado(){

    ofstream ListadoXxx("ListadoXxx.txt");
    short i = 0;
    while (ListadoXxx.good()) {
        ListadoXxx <<""<< setw(20) << paisCompleto[i].nomPais << endl
                   <<""<< setw(10) << paisCompleto[i].cantHabitantes << endl;

    i++;
    }
}