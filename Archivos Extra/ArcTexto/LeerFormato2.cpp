/*
   Id.Programa: LeerFormato2.cpp
   Autor......: Lic. Hugo Cuello
   Fecha......: julio-2020
   Comentario.: Lee archivo de texto con formato
                  y cuenta lineas.
                  Redirecciona archivos cin y cout
                  reemplazando el teclado y la
                  pantalla a archivos de texto,
                  usando la facilidad freopen...
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

bool Leer(tsDatos &r) {
    cin >> r.a >> r.b;
    cin.ignore();
    cin.get(r.c,20);
    cin >> r.d >> r.e;
    return cin.good();
} // Leer

main() {
    tsDatos r;
    short clineas = 0;

    freopen("ArcTexto.Txt","r",stdin);
    freopen("LstDatos.Txt","w",stdout);
    cout << "Listado de datos" << endl;
    cout << replicate('=',39) << endl;
    cout << "  a  c                         b    c e" << endl;
    cout << replicate('-',39) << endl;
    while (Leer(r)) {
        cout << setw(3) << r.a << ' '
             << setw(20) << r.c << ' '
             << setw(7) << r.b << ' '
             << setw(4) << r.d << ' '
             << r.e << endl;
        ++clineas;
    }
    cout << replicate('-',39) << endl;
    cout << "Cant.Lineas: " << clineas << endl;
    cout << replicate('=',39) << endl;
    freopen("CON","r",stdin);
    freopen("CON","w",stdout);
    return 0;
}
