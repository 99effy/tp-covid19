/*
   Id.Programa: LeerCar.cpp
   Autor......: Lic. Hugo Cuello
   Fecha......: julio-2020
   Comentario.: Lee archivo de texto car. x car
                  y cuenta lineas.
*/

#include <fstream>
#include <iomanip>
using namespace std;

main() {
    char car;
    ifstream atIn("ArcTexto.Txt");
    short clineas = 0;

    atIn.get(car);
    while (atIn.good()) {
        cout << car;
        if(car == '\n')
            ++clineas;
        atIn.get(car);
    }
    cout << "Cant.Lineas: " << clineas;
    atIn.close();
    return 0;
}
