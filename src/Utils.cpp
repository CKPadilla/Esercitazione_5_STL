#include "Utils.hpp"
#include "PolygonalMesh.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
using namespace Eigen;
using namespace PolygonalLibrary;

namespace PolygonalLibrary   //raccolgo tutte le funzioni in questo namespace
{

/*
// Funzione : ImportMesh : legge il file dei dati e li memorizza nello struct PolygonalMesh
// Inputs : 
PolygonalMesh& mesh : reference allo struct PolygonalMesh
const string& inputFile : file da leggere
// Outputs : riempimento dello struct PolygonalMesh
*/

bool ImportMesh(PolygonalMesh& mesh, 
                const string& inFile_0,
                const string& inFile_1,
                const string& inFile_2)
{

    if(!ImportCell0D(mesh, inFile_0))
        return false;

    if(!ImportCell1D(mesh, inFile_1))
        return false;

    if(!ImportCell2D(mesh, inFile_2))
        return false;

    return true;
}




/************************************************/

/*
// Funzione : ImportCell0D : legge il file dei dati e li memorizza nello struct PolygonalMesh
// Inputs : 
PolygonalMesh& mesh : reference allo struct PolygonalMesh
const string& inputFile : file da leggere
// Outputs : riempimento dello struct PolygonalMesh
*/
bool ImportCell0D(PolygonalMesh& mesh, const string& Cell0D_inputFile)
{

    /// LETTURA FILE E SALVATAGGIO DI TUTTE LE RIGHE
    ifstream file(Cell0D_inputFile);

    if(file.fail())   // verifico l'apertura corretta
        return false;

    list<string> listLines;

    string line;
    while (getline(file, line))   // raccolgo nel listLines tutte le righe del file 
        listLines.push_back(line);

    file.close();   // chiusura file

    listLines.pop_front();   // rimuovo l'header (=prima riga)

    
    /// RIEMPIMENTO DELLO STRUCT MESH

    /// Cell0D_num 
    mesh.Cell0D_num = listLines.size();   

    if (mesh.Cell0D_num == 0)
    {
        cerr << "Non ci sono Cell0D." << endl;
        return false;
    }

    /// Cell0D_id , Cell0D_coordinate , Cell0D_markers
    mesh.Cell0D_id.reserve(mesh.Cell0D_num);   // alloco memoria per Cell0D_id
    mesh.Cell0D_coordinate = MatrixXd::Zero(3, mesh.Cell0D_num);  // inizializzo Cell0D_coordinate 

    unsigned int i = 0;   //indicizzatore
    for (const string& line : listLines)   // ogni riga è una Cell0D
    {
        
        istringstream stream_line(line);

        /// Cell0D_id
        string id_string;
        getline(stream_line, id_string, ';');
        unsigned int id = stoi(id_string);   // converto la string in int
        mesh.Cell0D_id.push_back(id);

        /// Cell0D_markers
        string marker_string;
        getline(stream_line, marker_string, ';');
        unsigned int marker = stoi(marker_string);   // converto la string in int

        if(marker != 0)   // se marker=0, non va salvato
        {
            const auto it = mesh.Cell0D_markers.find(marker);   // controllo se il marker è già memorizzato
            if(it == mesh.Cell0D_markers.end())   // aggiungo un nuovo marker col primo elemento
            {
                mesh.Cell0D_markers.insert({marker, {id}});
            }
            else   // aggiungo un elemento al marker
            {
                mesh.Cell0D_markers[marker].push_back(id);
            }
        }

        /// Cell0D_coordinate
        string x_string;
        getline(stream_line, x_string, ';');
        mesh.Cell0D_coordinate(0, i) = stod(x_string);

        string y_string;
        getline(stream_line, y_string, ';');
        mesh.Cell0D_coordinate(1, i) = stod(y_string);

        i++; 
    }

    return true;
}

/************************************************/

/*
// Funzione : ImportCell1D : legge il file dei dati e li memorizza nello struct PolygonalMesh
// Inputs : 
PolygonalMesh& mesh : reference allo struct PolygonalMesh
const string& inputFile : file da leggere
// Outputs : riempimento dello struct PolygonalMesh
*/

bool ImportCell1D(PolygonalMesh& mesh, const string& Cell1D_inputFile)
{

    /// LETTURA FILE E SALVATAGGIO DI TUTTE LE RIGHE
    ifstream file(Cell1D_inputFile);

    if(file.fail())   // verifico apertura file
        return false;

    list<string> listLines;
    string line;
    while (getline(file, line))   // raccolgo nel listLines tutte le righe del file
        listLines.push_back(line);

    file.close();   // chiudo file

    listLines.pop_front();   // tolgo l'header (= prima riga)

    /// RIEMPIMENTO DELLO STRUCT MESH

    /// Cell1D_num
    mesh.Cell1D_num = listLines.size();

    if (mesh.Cell1D_num == 0)
    {
        cerr << "Non ci sono Cell1D." << endl;
        return false;
    }

    /// Cell1D_id , Cell1D_estremi , Cell1D_markers
    mesh.Cell1D_id.reserve(mesh.Cell1D_num);   // alloco memoria per Cell1D_id
    mesh.Cell1D_estremi = MatrixXi::Zero(2, mesh.Cell1D_num);   // inizializzo Cell1D_estremi

    unsigned  int i = 0;   // indicizzatore
    for (const string& line : listLines)   // ogni riga è una Cell1D
    {
        istringstream stream_line(line);

        /// Cell1D_id
        string id_string;
        getline(stream_line, id_string, ';');
        unsigned int id = stoi(id_string);   // id da string a int
        mesh.Cell1D_id.push_back(id);

        /// Cell1D_markers
        string marker_string;
        getline(stream_line, marker_string, ';');
        unsigned int marker = stoi(marker_string);   // marker da string a int

        if(marker != 0)   // se il marker ha senso
        {
            const auto it = mesh.Cell1D_markers.find(marker);  
            if(it == mesh.Cell1D_markers.end())   // se il marker è nuovo, lo aggiungo col primo id
            {
                mesh.Cell1D_markers.insert({marker, {id}});
            }
            else   // se il marker già c'è, vi aggiungo l'id
            {
                mesh.Cell1D_markers[marker].push_back(id);
            }
        }

        /// Cell1D_estremi
        string inizio_string;
        getline(stream_line, inizio_string, ';');
        mesh.Cell1D_estremi(0, i) = stoi(inizio_string);

        string fine_string;
        getline(stream_line, fine_string, ';');
        mesh.Cell1D_estremi(1, i) = stoi(fine_string);

        ++i;
    }

    return true;
}


/************************************************/

/*
// Funzione : ImportCell2D : legge il file dei dati e li memorizza nello struct PolygonalMesh
// Inputs : 
PolygonalMesh& mesh : reference allo struct PolygonalMesh
const string& inputFile : file da leggere
// Outputs : riempimento dello struct PolygonalMesh
*/
bool ImportCell2D(PolygonalMesh& mesh, const string& Cell2D_inputFile)
{

    /// LETTURA FILE E SALVATAGGIO DI TUTTE LE RIGHE
    ifstream file;
    file.open(Cell2D_inputFile);

    if(file.fail())   // verifico apertura file
        return false;

    list<string> listLines;
    string line;
    while (getline(file, line))   // raccolgo tutte le righe nel listLines
        listLines.push_back(line);

    file.close();   // chiudo il file

    listLines.pop_front();   // tolgo l'header (=prima riga)


    /// RIEMPIMENTO DELLO STRUCT MESH

    /// Cell2D_num
    mesh.Cell2D_num = listLines.size();    

    if (mesh.Cell2D_num == 0)
    {
        cerr << "Non ci sono Cell2D." << endl;
        return false;
    }

    /// Cell2D_id , Cell2D_vertici, Cell2D_lati
    mesh.Cell2D_id.reserve(mesh.Cell2D_num);   // alloco memoria
    mesh.Cell2D_vertici.reserve(mesh.Cell2D_num);   // alloco memoria
    mesh.Cell2D_lati.reserve(mesh.Cell2D_num);   // alloco memoria

    
    for (const string& line : listLines)   // ogni riga è una Cell2D
    {
        istringstream stream_line(line);

        /// Cell2D_id 
        string id_string;
        getline(stream_line, id_string, ';');
        unsigned int id = stoi(id_string);   // id da string a int
        mesh.Cell2D_id.push_back(id);   

        /// Cell2D_markers (da ignorare)
        string marker_string;
        getline(stream_line, marker_string, ';');
        
        /// Cell2D_vertici
        string numVertici_string;
        getline(stream_line, numVertici_string, ';');
        unsigned int numVertici = stoi(numVertici_string);   // numVertici da string a int 
        mesh.Cell2D_numVertici.push_back(numVertici); 

        vector<unsigned int> vertici(numVertici);   // vettore degli id dei vertici
        for(unsigned int i = 0; i < numVertici; i++) {
            string vertice_string;
            getline(stream_line, vertice_string, ';');
            vertici[i] = stoi(vertice_string);
        }   

        mesh.Cell2D_vertici.push_back(vertici);   
        

        /// Cell2D_lati
        string numLati_string;
        getline(stream_line, numLati_string, ';');
        unsigned int numLati = stoi(numLati_string);   // numLati da string a int
        mesh.Cell2D_numLati.push_back(numLati);

        vector<unsigned int> lati(numLati);   // vettore degli id dei lati

        for(unsigned int i = 0; i < numLati; i++) {
            string lato_string;
            getline(stream_line, lato_string, ';');
            lati[i] = stoi(lato_string);
        }
        
        mesh.Cell2D_lati.push_back(lati);
    }

    return true;
}

}