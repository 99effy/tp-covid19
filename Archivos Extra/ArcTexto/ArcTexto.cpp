

#include <fstream>
#include <iomanip>
using namespace std;

typedef char str20[21];

struct ts {
    int a;
    float b;
    str20 c;
    int d;
    bool e;
};

bool Leer(ifstream &aT, ts &r) {
    aT >> r.a >> r.b;
    aT.ignore();
    aT.get(r.c,21);
    aT >> r.d >> r.e;
    return aT.good();
}

main() {
    ts r;
    ifstream atIn("ArcTexto.Txt");

    while (Leer(atIn,r))
        cout << setw(3) << r.a << ' '
             << setw(4) << r.d << ' '
             << setw(20) << r.c << ' '
             << setw(7) << r.b << ' '
             << boolalpha << r.e << endl;
    atIn.close();
    return 0;
}
