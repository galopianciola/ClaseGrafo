#include "Grafo.h"
#include "iostream"
#include <queue>

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
    list<int> sort_topologico;
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

    int time=0;

    int tree=0,backk=0,cross=0,forwardd=0;

    int* descubierto = new int[grafo.devolver_longitud()];
    int* finalizado = new int[grafo.devolver_longitud()];

    for (int i=1;i<=grafo.devolver_longitud();i++){
        descubierto[i]=0;
        finalizado[i]=0;
    }

    while (it != vertices.end()){
        if (visitados.find(fuente)==visitados.end()){ ///Si el vertice no esta visitado
            DFS_visit(grafo,fuente,visitados,recorrido,time,descubierto,finalizado,tree,backk,cross,forwardd,sort_topologico);
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

    if (backk>1)
        cout<<"El grafo tiene "<<backk<<" arco/s back, por lo tanto, el grafo es ciclico"<<endl;
    else
        cout<<"El grafo no tiene arcos back, por lo tanto, el grafo es aciclico"<<endl;
    if (forwardd>1)
        cout<<"El grafo tiene "<<forwardd<<" arco/s forward"<<endl;
    else
        cout<<"El grafo no tiene arcos forward"<<endl;
    if (cross)
        cout<<"El grafo tiene "<<cross<<" arco/s cross"<<endl;
    else
        cout<<"El grafo no tiene arcos cross"<<endl;
    cout<<"Y el grafo contiene "<<tree<<" arcos tree"<<endl;

    cout<<" "<<endl;
    cout<<" "<<endl;
    cout<<"Sort Topologico: ";
    list<int>::iterator Ist=sort_topologico.begin();
    while (Ist!=sort_topologico.end()){
        cout<<*Ist<<" ";
        Ist++;
    }
    cout<<" "<<endl;
    cout<<" "<<endl;
    cout<<"#############################################"<<endl;
    cout<<" "<<endl;
}

template <typename C> void DFS_visit(const Grafo<C> & grafo, int vertice, set<int> & visitados, list<int> & recorrido,int & time,int descubierto[],int finalizado[],int & tree,int & backk,int & cross,int & forwardd,list<int> & sort_topologico)
{
    time++;

    descubierto[vertice]=time;

    visitados.insert(vertice); //Marco como visitado

    recorrido.push_back(vertice);

    list<typename Grafo<C>::Arco> adyacentes;

    grafo.devolver_adyacentes(vertice,adyacentes); //Obtengo adyacentes al vertice

    typename list<typename Grafo<C>::Arco>::iterator itA=adyacentes.begin();
    typename list<typename Grafo<C>::Arco>::iterator it=adyacentes.begin();

    cout<<"Vertice actual: "<<vertice<<" ["<<descubierto[vertice]<<"],["<<finalizado[vertice]<<"]"<<endl;
    cout<<"Lista de adyacentes a "<<vertice<<": ";
    while (itA != adyacentes.end()){
        cout<<(*itA).devolver_adyacente()<<" ";
        itA++;
    }
    cout<<endl;
    cout<<endl;

    while (it != adyacentes.end()){ //Para todos sus adyacentes
        if (finalizado[(*it).devolver_adyacente()]!=0){
            if (descubierto[vertice]>finalizado[(*it).devolver_adyacente()])
                cross++;
            else
                forwardd++;
        }
        if (visitados.find((*it).devolver_adyacente())==visitados.end()){ // Si no esta visitado
            tree++;
            DFS_visit(grafo,(*it).devolver_adyacente(),visitados,recorrido,time,descubierto,finalizado,tree,backk,cross,forwardd,sort_topologico);
        }
        else
            if (finalizado[(*it).devolver_adyacente()]==0)
                backk++;
        it++;
    }
    time++;
    finalizado[vertice]=time;
    cout<<"Vertice actual: "<<vertice<<" ["<<descubierto[vertice]<<"],["<<finalizado[vertice]<<"]"<<endl;
    cout<<"Vertice finalizado"<<endl;

    sort_topologico.push_back(vertice);

    cout<<endl;

}

template <typename C> void PuntosArticulacion(const Grafo<C> & grafo, int fuente){
    struct nodoLista{
        int vertice;
        list<nodoLista> hijo;

    };
    /*typename list<typename Grafo<C>::Arco>::iterator it=adyacentes.begin();
     while (it != adyacentes.end()){ //Para todos sus adyacentes
        if (finalizado[(*it).devolver_adyacente()]!=0){
            if (descubierto[vertice]>finalizado[(*it).devolver_adyacente()])
                cross++;
            else
                forwardd++;
        }
        if (visitados.find((*it).devolver_adyacente())==visitados.end()){ // Si no esta visitado
            tree++;
            DFS_visit(grafo,(*it).devolver_adyacente(),visitados,recorrido,time,descubierto,finalizado,tree,backk,cross,forwardd,sort_topologico);
        }
        else
            if (finalizado[(*it).devolver_adyacente()]==0)
                backk++;
        it++;
    }*/

}

template <typename C> void BFS(const Grafo<C> & grafo, int fuente){
    ///lista para ir guardando el recorrido final
    list<int> recorrido;

    ///Marcar todos los vertices como no visitados
    set<int> visitados;
    visitados.insert(fuente); ///Marco la fuente como visitada (aun no recorrida en sus adyacentes)

    queue<int> fila; ///Hago fila de pendientes por recorrer sus adyacentes
    fila.push(fuente); ///Agrego fuente a esa fila

    list<typename Grafo<C>::Arco> adyacentesDeU;

    while (!fila.empty()){
        int u = fila.front(); ///obtengo el primero de la fila
        fila.pop(); ///lo borro de ella

        ///Ahora obtengo todos los adyacentes del desencolado u
        grafo.devolver_adyacentes(u,adyacentesDeU);

        ///Para los que no esten visitados, los marco como visitados y los encolo
        typename list<typename Grafo<C>::Arco>::iterator it = adyacentesDeU.begin(); ///iterador para moverme por todos los adyacentes de u
        while (it != adyacentesDeU.end()){
            if (visitados.find((*it).devolver_adyacente())==visitados.end()){ ///si no esta visitado
                visitados.insert((*it).devolver_adyacente());
                fila.push((*it).devolver_adyacente());
            }
            it++;
        }

        recorrido.push_back(u);

    }

    cout<<"Recorrido BFS:"<<endl;
    list<int>::iterator iterador = recorrido.begin();
    while (iterador != recorrido.end()){
        cout<<*iterador<<" ";
        iterador++;
    }

    cout<<""<<endl;

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
