/*
   Id.Programa: LeerFormato.cpp
   Autor......: Lic. Hugo Cuello
   Fecha......: julio-2020
   Comentario.: Lee archivo de texto con formato
                  y cuenta lineas.
*/

#include <fstream>
#include <iomanip>
using namespace std;

typedef char str20[21];

struct tsDatos {
    int   a;
    float b;
    str20 c;
    int   d;
    bool  e;
};

string replicate(char car, unsigned n) {
  string cad = "";

  for (unsigned i = 1; i <= n; i++)
    cad += car;
  return cad;
} // replicate

bool Leer(ifstream &aT, tsDatos &r) {
    aT >> r.a >> r.b;
    aT.ignore();
    aT.get(r.c,20);
    aT >> r.d >> r.e;
    return aT.good();
} // Leer

main() {
    tsDatos r;
    ifstream atIn("ArcTexto.Txt");
    ofstream atOut("LstDatos.Txt");
    short clineas = 0;

    atOut << "Listado de datos" << endl;
    atOut << replicate('=',39) << endl;
    atOut << "  a  c                         b    c e" << endl;
    atOut << replicate('-',39) << endl;
    while (Leer(atIn,r)) {
        atOut << setw(3) << r.a << ' '
             << setw(20) << r.c << ' '
             << setw(7) << r.b << ' '
             << setw(4) << boolalpha << r.d << ' '
             << r.e << endl;
        ++clineas;
    }
    atOut << replicate('-',39) << endl;
    atOut << "Cant.Lineas: " << clineas << endl;
    atOut << replicate('=',39) << endl;
    atIn.close();
    atOut.close();
    return 0;
}
