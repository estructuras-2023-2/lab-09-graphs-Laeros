#include <string>
#include <map>

using namespace std;

class GestionadorConectividadCiudades {
private:
    map<string, string> representante;
    map<string, int> rango;

public:
    void crearConjunto(const string& s) {
        representante[s] = s;
        rango[s] = 0;
    }

    string encontrar(const string& s) {
        if (representante[s] != s)
            representante[s] = encontrar(representante[s]);
        return representante[s];
    }

    bool unirConjuntos(const string& a, const string& b) {
        string raizA = encontrar(a);
        string raizB = encontrar(b);

        if (raizA == raizB)
            return false;

        if (rango[raizA] < rango[raizB])
            representante[raizA] = raizB;
        else if (rango[raizA] > rango[raizB])
            representante[raizB] = raizA;
        else {
            representante[raizB] = raizA;
            rango[raizA]++;
        }

        return true;
    }
};
