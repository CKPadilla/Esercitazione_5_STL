#pragma once

#include <iostream>
#include "Eigen/Eigen"

using namespace std;
using namespace Eigen;


namespace PolygonalLibrary {

struct PolygonalMesh
{

    /* Cell0D = punti:
    - Cell0D_num : numero di punti
    - Cell0D_id : vettore degli id dei punti : dim 1 x Cell0D_num 
    - Cell0D_coordinate : matrice di coordinate (x,y) : dim 3 x Cell0D_num
    - Cell0D_markers : mappa<marker, lista dei punti di quel marker>
    */

    unsigned int Cell0D_num = 0;   // quanti Cell0D
    vector<unsigned int> Cell0D_id = {};   // id di vertici   
    MatrixXd Cell0D_coordinate = {};   // coordinate (x,y,z)
    map<unsigned int, list<unsigned int>> Cell0D_markers = {};   // markers 

    /* Cell1D = segmenti:
    - Cell1D_num : numero di segmenti
    - Cell1D_id : vettore degli id dei segmenti : dim 1 x Cell1D_num
    - Cell1D_estremi : matrice degli id (in int) dei punti di estremi : dim 2 x Cell1D_num
    - Cell1D_markers : mappa<marker, lista dei punti di quel marker>
    */

    unsigned int Cell1D_num = 0;   // quanti Cell1D
    vector<unsigned int> Cell1D_id = {};   // id di segmento
    MatrixXi Cell1D_estremi = {};   // id dei punti d'estremi (id1,id2)
    map<unsigned int, list<unsigned int>> Cell1D_markers = {};   // markers

    /* Cell2D = facce:
    - Cell2D_num : numero di facce
    - Cell2D_id : vettore degli id delle facce : dim 1 x Cell2D_num
    - Cell2D_numVertici : vettore dei numeri di vertici di ogni faccia : dim 1 x Cell2D_num
    - Cell2D_vertici : vettore di vettori degli id dei vertici di ciascuna faccia : dim 1 x Cell2D_num
    - Cell2D_numLati : vettore dei numeri di lati di ogni faccia : dim 1 x Cell2D_num
    - Cell2D_lati: vettore di vettori dei lati che compongono ciascuna faccia : dim 1 x CEll2D_num
    */

    unsigned int Cell2D_num = 0;   // quanti Cell2D
    vector<unsigned int> Cell2D_id = {};   // id di faccia
    vector<unsigned int> Cell2D_numVertici = {};   // numeri di vertici di ogni faccia
    vector<vector<unsigned int>> Cell2D_vertici = {};   // id dei vertici 
    vector<unsigned int> Cell2D_numLati = {};   // numeri di lati di ogni faccia
    vector<vector<unsigned int>> Cell2D_lati = {};   // id dei lati
};

}