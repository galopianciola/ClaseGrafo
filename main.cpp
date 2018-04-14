#include "Grafo.h"
#include "iostream"

using namespace std;

template <typename C>
ostream & operator << (ostream & salida, const Grafo<C> & grafo)
{
	// Recorremos todos los vertices
	list<int> vertices;
	grafo.devolver_vertices(vertices);
	list<int>::iterator v = vertices.begin();
	while (v != vertices.end()) {
		salida << "    " << *v << "\n";
		// Recorremos todos los adyacentes de cada vertice
		list<typename Grafo<C>::Arco> adyacentes;
		grafo.devolver_adyacentes(*v, adyacentes);
		typename list<typename Grafo<C>::Arco>::iterator ady = adyacentes.begin();
		while (ady != adyacentes.end()) {
			salida << "    " << *v << "-> " << ady->devolver_adyacente() << " (" << ady->devolver_costo() << ")\n";
			ady++;
		}
		v++;
	}
	return salida;
}


template <typename C> void DFS_forest(const Grafo<C> & grafo, int fuente)
{
    list<int> vertices;
    grafo.devolver_vertices(vertices);

    cout<<"Lista de vertices del grafo:"<<endl;

    list<int>::iterator itA=vertices.begin();

    while (itA != vertices.end()){
        cout<<*itA<<" ";
        itA++;
    }

    cout<<" "<<endl;
    cout<<"#############################################"<<endl;
    cout<<" "<<endl;

    set<int> visitados;

    list<int>::iterator it=vertices.begin();

    list<int> recorrido;

    cout<<"------------"<<endl;
    cout<<endl;

    while (it != vertices.end()){
        if (visitados.find(fuente)==visitados.end()){ //Si el vertice no esta visitado
            DFS_visit(grafo,fuente,visitados,recorrido);
        }
        it++;
    }

    cout<<"Recorrido total DFS: "<<endl;
    list<int>::iterator itR=recorrido.begin();
    while (itR != recorrido.end()){
        cout<<*itR<<" ";
        itR++;
    }

    cout<<" "<<endl;
    cout<<" "<<endl;
    cout<<"#############################################"<<endl;
    cout<<" "<<endl;
}

template <typename C> void DFS_visit(const Grafo<C> & grafo, int vertice, set<int> & visitados, list<int> & recorrido)
{
    visitados.insert(vertice); //Marco como visitado

    cout<<"Vertice actual: "<<vertice<<endl;
    recorrido.push_back(vertice);

    list<typename Grafo<C>::Arco> adyacentes;

    grafo.devolver_adyacentes(vertice,adyacentes); //Obtengo adyacentes al vertice (ACA SE ROMPE)

    typename list<typename Grafo<C>::Arco>::iterator itA=adyacentes.begin();

    cout<<"Lista de adyacentes a "<<vertice<<": ";
    while (itA != adyacentes.end()){
        cout<<(*itA).devolver_adyacente()<<" ";
        itA++;
    }

    cout<<endl;
    cout<<endl;
    cout<<"------------"<<endl;
    cout<<endl;

    typename list<typename Grafo<C>::Arco>::iterator it=adyacentes.begin();

    while (it != adyacentes.end()){ //Para todos sus adyacentes
        if (visitados.find((*it).devolver_adyacente())==visitados.end()){ // Si no esta visitado
            DFS_visit(grafo,(*it).devolver_adyacente(),visitados,recorrido);
        }
        it++;
    }


}


int main(int argc, char **argv)
{
	Grafo<int> grafo;

    grafo.agregar_vertice(1);
    grafo.agregar_vertice(2);
    grafo.agregar_vertice(3);
    grafo.agregar_vertice(4);
    grafo.agregar_vertice(5);
    grafo.agregar_vertice(6);
    grafo.agregar_vertice(7);
    grafo.agregar_vertice(8);
    grafo.agregar_vertice(9);

    grafo.agregar_arco(1,4,14);
    grafo.agregar_arco(1,2,12);
    grafo.agregar_arco(2,3,23);
    grafo.agregar_arco(3,5,35);
    grafo.agregar_arco(4,7,47);
    grafo.agregar_arco(5,3,53);
    grafo.agregar_arco(5,7,57);
    grafo.agregar_arco(6,3,63);
    grafo.agregar_arco(7,6,76);
    grafo.agregar_arco(7,8,78);
    grafo.agregar_arco(8,9,89);
    grafo.agregar_arco(9,3,93);

    DFS_forest(grafo,1);

	return 0;
}
