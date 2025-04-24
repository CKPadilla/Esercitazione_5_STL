#pragma once

#include <iostream>
#include "Eigen/Eigen"

using namespace std;
using namespace Eigen;


namespace PolygonalLibrary {

struct PolygonalMesh
{

    /* Punto = Cell0D:
    - NumCell0D : numero di punti
    - Cell0DId : vettore dell'id di tutti i punti 
    - Cell0DCoordinate : matrice delle corodinate di ciascun punto
    - MarkerCell0D : marker o colore assegnato a ciascun punti in base alla sua posizione/coordinate
    */

    unsigned int NumCell0D = 0; ///< number of Cell0D
    std::vector<unsigned int> Cell0DId = {}; ///< Cell0D id, size 1 x NumberCell0D
    Eigen::MatrixXd Cell0DCoordinate = {}; ///< Cell0D coordinate, size 2 x NumberCell0D (x,y)
    std::map<unsigned int, list<unsigned int>> MarkerCell0D = {}; ///< Cell0D markers

    /* Segmento = Cell1D:
    - NumCell1D : numero di segmenti
    - Cell1DId : vettore dell'id di ciascun segmento
    - Cell1DExtrema : matrice degli estremi di ciascun segmento
    - MarkerCell1D : marker o colore di ciascun segmento in base alla propria posizione
    */

    unsigned int NumCell1D = 0; ///< number of Cell1D
    std::vector<unsigned int> Cell1DId = {}; ///< Cell1D id, size 1 x NumberCell1D
    Eigen::MatrixXi Cell1DExtrema = {}; ///< Cell1D vertices indices, size 2 x NumberCell1D (fromId,toId)
    std::map<unsigned int, list<unsigned int>> MarkerCell1D = {}; ///< Cell1D markers

    /* Solido = Cell2D:
    - NumCell2D : numero di solidi
    - Cell2DId : vettore dell'id di ciascun solido
    - Cell2DNumVertice : numero di vertici di ogni solido
    - Cell2DVertice : vettore di vettori dei vertici di ciascun solido
    - Cell2DNumEdge :numero di lati di ogni solido
    - Cell2DEdge: vettore di vettori dei lati di ciascun solido
    */

    unsigned int NumCell2D = 0; ///< number of Cell2D
    std::vector<unsigned int> Cell2DId = {}; ///< Cell2D id, size 1 x NumberCell2D
    unsigned int Cell2DNumVertice = 0; ///< Cell2D Vertices Number
    std::vector<vector<unsigned int>> Cell2DVertice = {}; ///< Cell2D Vertices indices, size 1 x NumberCell2D
    unsigned int Cell2DNumEdge = 0; ///< Cell2D Edges Number
    std::vector<vector<unsigned int>> Cell2DEdge = {}; ///< Cell2D Cell1D indices, size 1 x NumberCell2D
};

}