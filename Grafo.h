#ifndef GRAFO_H_
#define GRAFO_H_

#include <list>
#include <map>
#include <set>
#include<iostream>

using namespace std;

template <typename C> class Grafo
{
public:

    /* SUBCLASE ARCO */

	class Arco
	{
	public:
		Arco(); //
		Arco(int adyacente, const C & costo); //
		int devolver_adyacente() const; //
		const C & devolver_costo() const; //
	private:
		int vertice;
		C costo;
	};

	/* FIN SUBCLASE ARCO */

public:
	// NOTA: Dependiendo de la implementación puede ser necesario incluir otras funciones constructuras
	Grafo(); // constructor
	Grafo(const Grafo & otroGrafo); //

	~Grafo(); //

	Grafo & operator = (const Grafo & otroGrafo); // preguntar

	// Devuelve true si la cantidad de vértices es cero
	bool esta_vacio() const; //

	// Indica la cantidad de vértices del grafo
	int devolver_longitud() const; //

	bool existe_vertice(int vertice) const; //

	bool existe_arco(int origen, int destino) const; //

	// PRE CONDICION: existe_arco(origen, destino)
	const C & costo_arco(int origen, int destino) const; //

	void devolver_vertices(list<int> & vertices) const; //

	void devolver_adyacentes(int origen, list<Arco> & adyacentes) const; //

	void agregar_vertice(int vertice); //

	// POST CONDICION: Para todo vértice v != vertice: !existeArco(v, vertice) && !existeArco(vertice, v)
	void eliminar_vertice(int vertice); //

	// PRE CONDICION: existeArco(origen, destino)
	void modificar_costo_arco(int origen, int destino, const C & costo); //

	// PRE CONDICION: existeVertice(origen) && existeVertice(destino)
	// POST CONDICION: existeArco(origen, destino)
	void agregar_arco(int origen, int destino, const C & costo);

	// POST CONDICION: !existeArco(origen, destino)
	void eliminar_arco(int origen, int destino); //

	void mostrarGrafo(Grafo<C> G);

	void vaciar(); //

private:

	map<int,map<int,C> > grafo;

}; // class Grafo


/* METODOS ARCO */

template <typename C> Grafo<C>::Arco::Arco()
{

}

template <typename C> Grafo<C>::Arco::Arco(int adyacente, const C & costo)
{

    this->vertice = adyacente;
    this->costo = costo;

}

template <typename C> int Grafo<C>::Arco::devolver_adyacente() const
{

    return this->vertice;

}

template <typename C> const C & Grafo<C>::Arco::devolver_costo() const
{

    return this->costo;

}


/*
 * METODOS GRAFO
 */

template <typename C> Grafo<C>::Grafo()
{
}

template <typename C> Grafo<C>::Grafo(const Grafo & otroGrafo)
{

    this->grafo = otroGrafo;

}

template <typename C> Grafo<C>::~Grafo()
{

}

template <typename C> Grafo<C> & Grafo<C>::operator = (const Grafo & otroGrafo)
{

    return *this;
}

template <typename C> bool Grafo<C>::esta_vacio() const
{

    if (this->grafo.empty())
        return true;

    return false;

}

template <typename C> int Grafo<C>::devolver_longitud() const
{

    return this->grafo.size();

}

template <typename C> bool Grafo<C>::existe_vertice(int vertice) const
{

    if (this->grafo.find(vertice) == this->grafo.end())
        return false;

    return true;

}

template <typename C> bool Grafo<C>::existe_arco(int origen, int destino) const
{

    typename map<int,map<int,C> >::const_iterator itO;

    if (grafo.find(origen) != grafo.end()){

        itO=grafo.find(origen);

        typename map<int,C>::const_iterator it;

        it = itO->second.find(destino);

        if (it != itO->second.end())
            return true;

    }

    return false;

    }




template <typename C> const C & Grafo<C>::costo_arco(int origen, int destino) const
{

    typename map<int,map<int,C> >::const_iterator itO;

    if (existe_arco(origen,destino)){

        itO=grafo.find(origen);

        typename map<int,C>::const_iterator it;

        it = itO->second.find(destino);

        return it->second;

    }

}

template <typename C> void Grafo<C>::devolver_vertices(list<int> & vertices) const
{

    typename map<int,map<int,C> >::const_iterator it = grafo.begin();

    while (it != grafo.end()){
        vertices.push_back(it->first);
        it++;
    }

}

template <typename C> void Grafo<C>::devolver_adyacentes(int origen, list<Arco> & adyacentes) const
{
    typename map<int,map<int,C> >::const_iterator it;


    if (existe_vertice(origen)){

        it = grafo.find(origen);

        typename map<int,C>::const_iterator itA;

        itA = it->second.begin();
        while (itA!=it->second.end())
            adyacentes.push_back(Arco(itA->first,itA->second));
    }



}

template <typename C> void Grafo<C>::agregar_vertice(int vertice)
{

    if (grafo.find(vertice) == grafo.end()) //Si no existe ya el vertice
    {
        map<int, C> adyacentes;
        grafo[vertice] = adyacentes; // DUDA[]
    }

}

template <typename C> void Grafo<C>::eliminar_vertice(int vertice)
{
    typename map<int,map<int,C> >::const_iterator it;
    if (existe_vertice(vertice)){
        it=grafo.find(vertice);
        grafo.erase(it);
    }

}

template <typename C> void Grafo<C>::modificar_costo_arco(int origen, int destino, const C & costo)
{
    typename map<int,map<int,C> >::const_iterator itO;

    if (existe_arco(origen,destino)){

        itO=grafo.find(origen);

        typename map<int,C>::const_iterator it;

        it = itO->second.find(destino);

        it->second = costo;

    }

}

template <typename C> void Grafo<C>::agregar_arco(int origen, int destino, const C & costo)
{

    typename map<int,map<int,C> >::iterator itO;

    if (existe_vertice(origen)){
        itO = grafo.find(origen);
        if (existe_arco(origen,destino) != true)
            itO->second[destino]=costo;
    }

}


template <typename C> void Grafo<C>::eliminar_arco(int origen, int destino)
{
    typename map<int,map<int,C> >::const_iterator itO;
    if (existe_arco(origen,destino)){

        itO=grafo.find(origen);

        typename map<int,C>::const_iterator it;

        it = itO->second.find(destino);

        grafo.erase(it);
    }

}

template <typename C> void Grafo<C>::mostrarGrafo(Grafo<C> G)
{
    list<int> Vertices;
    G.devolver_vertices(Vertices);
    list<int>::const_iterator It=Vertices.begin();
    while(It != Vertices.end())
    {
        list<int> Adyacentes;
        list<int>::const_iterator ItA ;
        G.devolver_adyacentes(*It, Adyacentes);
        ItA= Adyacentes.begin();
        cout << *It << " - > "<<endl;
        while (ItA != Adyacentes.end())
        {
            cout << *ItA << " ";
            ItA++;
        }
        It++;
        cout<<endl;
    }
    cout << endl;
}


template <typename C> void Grafo<C>::vaciar()
{
    this->grafo.clear();
}

#endif /* GRAFO_H_ */
