#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <set>
#include <algorithm>

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

class Carretera {
public:
    string id;
    string ciudad1;
    string ciudad2;
    int costo;

    Carretera(string i, string c1, string c2, int co = 0) : id(i), ciudad1(c1), ciudad2(c2), costo(co) {}
};

string reconstruye(vector<string> carreteras) {
    vector<Carretera> carreterasDanadas;
    GestionadorConectividadCiudades gestionadorConectividad;
    set<string> ciudades;
    set<string> carreterasSeleccionadas;

    // Inicialización de conjuntos y ciudades
    for (const auto& carreteraStr : carreteras) {
        stringstream ss(carreteraStr);
        string id, ciudad1, ciudad2;
        ss >> id >> ciudad1 >> ciudad2;
        gestionadorConectividad.crearConjunto(ciudad1);
        gestionadorConectividad.crearConjunto(ciudad2);
        ciudades.insert(ciudad1);
        ciudades.insert(ciudad2);
    }
    
    // Procesamiento de carreteras
    for (const auto& carreteraStr : carreteras) {
        stringstream ss(carreteraStr);
        string id, ciudad1, ciudad2;
        int costo = 0;
        ss >> id >> ciudad1 >> ciudad2;
        if (!(ss >> costo)) {
            gestionadorConectividad.unirConjuntos(ciudad1, ciudad2);
        } else {
            carreterasDanadas.emplace_back(id, ciudad1, ciudad2, costo);
        }
    }
    
    // Ordenamiento de carreteras dañadas
    sort(carreterasDanadas.begin(), carreterasDanadas.end(), [](const Carretera& a, const Carretera& b) {
        return (a.costo != b.costo) ? (a.costo < b.costo) : (a.id < b.id);
    });

    // Selección de carreteras para reconstrucción
    for (const auto& carretera : carreterasDanadas) {
        if (gestionadorConectividad.encontrar(carretera.ciudad1) != gestionadorConectividad.encontrar(carretera.ciudad2)) {
            gestionadorConectividad.unirConjuntos(carretera.ciudad1, carretera.ciudad2);
            carreterasSeleccionadas.insert(carretera.id);
        }
    }
    
    // Verificación de la conectividad de ciudades
    string raiz = gestionadorConectividad.encontrar(*ciudades.begin());
    for (const auto& ciudad : ciudades) {
        if (gestionadorConectividad.encontrar(ciudad) != raiz) {
            return "IMPOSIBLE";
        }
    }

    // Generación del resultado
    string resultado;
    for (const auto& id : carreterasSeleccionadas) {
        resultado += id + " ";
    }

    return resultado.empty() ? "" : resultado.substr(0, resultado.length() - 1);
}
