/*
   Id.Programa: LeerLinea.cpp
   Autor......: Lic. Hugo Cuello
   Fecha......: julio-2020
   Comentario.: Lee archivo de texto linea completa
                  y cuenta lineas.
*/

#include <fstream>
#include <iomanip>
using namespace std;

main() {
    char cad[100];
    ifstream atIn("ArcTexto.Txt");
    short clineas = 0;

    atIn.getline(cad,100);
    while (atIn.good()) {
        cout << cad << endl;
        ++clineas;
        atIn.getline(cad,100);
    }
    cout << "Cant.Lineas: " << clineas;
    atIn.close();
    return 0;
}
