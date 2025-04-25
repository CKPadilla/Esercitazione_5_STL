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

    /// "compilo" ogni "parte" della struct mesh che è stata inizializzata col nullo (= zero o vuoto)

    mesh.NumCell0D = listLines.size();   // Memorizzo il numero di celle (= n. di punti) 

    if (mesh.NumCell0D == 0)
    {
        cerr << "There is no cell 0D" << endl;
        return false;
    }

    mesh.Cell0DId.reserve(mesh.NumCell0D);   // faccio spazio al vettore di id per tutte le celle
    mesh.Cell0DCoordinate = Eigen::MatrixXd::Zero(3, mesh.NumCell0D);  // matrice di coordinate in double

    unsigned int idx = 0;
    for (const string& line : listLines)
    {
        istringstream converter(line);

        /// memorizzo l'id
        string id_string;
        getline(converter, id_string, ';');
        unsigned int id = stoi(id_string);
        mesh.Cell0DId.push_back(id);

        /// memorizzo il marker
        string marker_string;
        getline(converter, marker_string, ';');
        unsigned int marker = stoi(marker_string);

        if(marker != 0)   // vedo se il marker c'è già o no
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
        /// memorizzo le coordinate
        string x_string;
        getline(converter, x_string, ';');
        mesh.Cell0DCoordinate(0, idx) = stod(x_string);

        string y_string;
        getline(converter, y_string, ';');
        mesh.Cell0DCoordinate(1, idx) = stod(y_string);

        ++idx;
        
        

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

    unsigned  int idx = 0;   // indicizzatore

    for (const string& line : listLines)
    {
        istringstream converter(line);

        /// Memorizzo l'id
        string id_string;
        getline(converter, id_string, ';');
        unsigned int id = stoi(id_string);
        mesh.Cell1DId.push_back(id);

        /// Memorizzo il marker
        string marker_string;
        getline(converter, marker_string, ';');
        unsigned int marker = stoi(marker_string);

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
        /// Memorizzo gli estremi del segmento
        string extrema_iniziale;
        getline(converter, extrema_iniziale, ';');
        mesh.Cell1DExtrema(0, idx) = stoi(extrema_iniziale);

        string extrema_finale;
        getline(converter, extrema_finale, ';');
        mesh.Cell1DExtrema(1, idx) = stoi(extrema_finale);

        ++idx;
    
        
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

        // Memorizzo l'id nel vettore 
        string id_string;
        getline(converter, id_string, ';');
        unsigned int id = stoi(id_string);
        mesh.Cell2DId.push_back(id);   // memorizzo l'id nel vettore

        // Memorizzo il marker che poi ignorerò perchè tanto è tutto zero
        string marker_string;
        getline(converter, marker_string, ';');
        
        // Memorizzo il vettore dei vertici
        string NumVer_string;
        getline(converter, NumVer_string, ';');
        mesh.Cell2DNumVertice = stoi(NumVer_string);   //numero dei vertici memorizzato

        vector<unsigned int> vertice(mesh.Cell2DNumVertice);   // vettore dei vertici
        for(unsigned int i = 0; i < mesh.Cell2DNumVertice; i++) {
            string vertice_string;
            getline(converter, vertice_string, ';');
            vertice[i] = stoi(vertice_string);
        }   
        mesh.Cell2DVertice.push_back(vertice);   // memorizzo il vettore dei vertici nel vettore 
        

        // memorizzo il vettore dei lati
        string NumEdge_string;
        getline(converter, NumEdge_string, ';');
        mesh.Cell2DNumEdge = stoi(NumEdge_string);

        vector<unsigned int> edge(mesh.Cell2DNumEdge);

        for(unsigned int i = 0; i < mesh.Cell2DNumEdge; i++) {
            string edge_string;
        getline(converter, edge_string, ';');
        edge[i] = stoi(edge_string);
        }
        
        mesh.Cell2DEdge.push_back(edge);
    }

    return true;
}

}