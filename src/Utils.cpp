#include "Utils.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

namespace PolygonalLibrary
{


/// Import the polygonal mesh and test if the mesh is correct
/// (reference) mesh: a PolygonalMesh struct
/// return the result of the reading, true if is success, false otherwise

bool ImportMesh(PolygonalMesh& mesh)
{

    if(!ImportCell0D(mesh))
        return false;

    if(!ImportCell1D(mesh))
        return false;

    if(!ImportCell2D(mesh))
        return false;

    return true;

}

// ***************************************************************************
/// Import the Cell0D properties from Cell0Ds.csv file
/// (reference) mesh: una struct del tipo PolygonalMesh
/// return the result of the reading, true if is success, false otherwise

bool ImportCell0D(PolygonalMesh& mesh)
{

    ifstream file("./Cell0Ds.csv");

    if(file.fail())   // Se il file non viene aperto correttamente
        return false;

    list<string> listLines;

    string line;
    while (getline(file, line))   // raccolgo nel listLines ogni riga del file
        listLines.push_back(line);

    file.close();

    listLines.pop_front();   // rimuovo la prima riga che è la header del file

    // "compilo" ogni "parte" della struct mesh che è stata inizializzata col nullo (= zero o vuoto)

    mesh.NumCell0D = listLines.size();   // Memorizzo il numero di celle (= n. di punti) 

    if (mesh.NumCell0D == 0)
    {
        cerr << "There is no cell 0D" << endl;
        return false;
    }

    mesh.Cell0DId.reserve(mesh.NumCell0D);   // faccio spazio al vettore di id per tutte le celle
    mesh.Cell0DCoordinate = Eigen::MatrixXd::Zero(2, mesh.NumCell0D);  // matrice di coordinate dinamica

    for (const string& line : listLines)
    {
        istringstream converter(line);

        unsigned int id;
        unsigned int marker;

        converter >>  id >> marker >> mesh.Cell0DCoordinate(0, id) >> mesh.Cell0DCoordinate(1, id);   //Memorizzo le coord.

        mesh.Cell0DId.push_back(id);   // Memorizzo l'id

        /// Memorizza i marker
        if(marker != 0)
        {
            const auto it = mesh.MarkerCell0D.find(marker);   // uso "auto" poichè it è un iteratore che non so dove punta 
            if(it == mesh.MarkerCell0D.end())   // aggiungo un nuovo marker
            {
                mesh.MarkerCell0D.insert({marker, {id}});
            }
            else   // aggiungo un elemento al marker
            {
                mesh.MarkerCell0D[marker].push_back(id);
            }
        }

    }

    return true;
}

// ***************************************************************************
/// Import the Cell1D properties from Cell1Ds.csv file
/// (reference) mesh: a PolygonalMesh struct
/// return the result of the reading, true if is success, false otherwise

bool ImportCell1D(PolygonalMesh& mesh)
{
    ifstream file("./Cell1Ds.csv");

    if(file.fail())
        return false;

    list<string> listLines;
    string line;
    while (getline(file, line))
        listLines.push_back(line);

    file.close();

    listLines.pop_front();

    mesh.NumCell1D = listLines.size();

    if (mesh.NumCell1D == 0)
    {
        cerr << "There is no cell 1D" << endl;
        return false;
    }

    mesh.Cell1DId.reserve(mesh.NumCell1D);
    mesh.Cell1DExtrema = Eigen::MatrixXi(2, mesh.NumCell1D);

    for (const string& line : listLines)
    {
        istringstream converter(line);

        unsigned int id;
        unsigned int marker;

        converter >>  id >> marker >>  mesh.Cell1DExtrema(0, id) >>  mesh.Cell1DExtrema(1, id);
        mesh.Cell1DId.push_back(id);

        /// Memorizza i marker
        if(marker != 0)
        {
            const auto it = mesh.MarkerCell1D.find(marker);
            if(it == mesh.MarkerCell1D.end())
            {
                mesh.MarkerCell1D.insert({marker, {id}});
            }
            else
            {
                mesh.MarkerCell1D[marker].push_back(id);
            }
        }
    }

    return true;
}
// ***************************************************************************
/* Solido = Cell2D:
    - NumCell2D : numero di solidi
    - Cell2DId : vettore dell'id di ciascun solido
    - Cell2DNumVertice : numero di vertici di ogni solido
    - Cell2DVertice : vettore di vettori dei vertici di ciascun solido
    - Cell2DNumEdge : numero di lati di ogni solido
    - Cell2DEdge: vettore di vettori dei lati di ciascun solido
    */

bool ImportCell2D(PolygonalMesh& mesh)
{
    ifstream file;
    file.open("./Cell2Ds.csv");

    if(file.fail())
        return false;

    list<string> listLines;
    string line;
    while (getline(file, line))
        listLines.push_back(line);

    file.close();

    listLines.pop_front();

    mesh.NumCell2D = listLines.size();    // numero di celle memorizzato

    if (mesh.NumCell2D == 0)
    {
        cerr << "There is no cell 2D" << endl;
        return false;
    }

    mesh.Cell2DId.reserve(mesh.NumCell2D);
    mesh.Cell2DVertice.reserve(mesh.NumCell2D);
    mesh.Cell2DEdge.reserve(mesh.NumCell2D);

    for (const string& line : listLines)
    {
        istringstream converter(line);

        // memorizzo l'id nel vettore (ignoro il marker perchè qui non importa)
        unsigned int id;
        unsigned int marker;
        converter >>  id >> marker;   // id e marker memorizzati
        mesh.Cell2DId.push_back(id);   // memorizzo l'id nel vettore


        // memorizzo il vettore dei vertici
        converter >> mesh.Cell2DNumVertice;   // numero di vertici memorizzato

        vector<mesh.Cell2DNumVertice> vertice;   // vettore dei vertici

        for(unsigned int i = 0; i < mesh.Cell2DNumVertice; i++)
            converter >> vertice[i];   // memorizzo ogni vertice nel vettore
        mesh.Cell2DVertice.push_back(vertices);   // memorizzo il vettore dei vertici nel vettore 

        // memorizzo il vettore dei lati
        converte >> mesh.Cell2DNumEdge;

        vector<mesh.Cell2DNumEdge> edge;

        for(unsigned int i = 0; i < mesh.Cell2DNumEdge; i++)
            converter >> edge[i];
        mesh.Cell2DEdge.push_back(edges);
    }

    return true;
}

}