#pragma once

#include <iostream>
#include "PolygonalMesh.hpp"

using namespace std;

namespace PolygonalLibrary
{
/// Import the polygonal mesh and test if the mesh is correct
/// (reference) mesh: a PolygonalMesh struct
/// return the result of the reading, true if is success, false otherwise
bool ImportMesh(PolygonalMesh& mesh);   

/// Import the Cell0D properties from Cell0Ds.csv file
/// (reference) mesh: a PolygonalMesh struct
/// return the result of the reading, true if is success, false otherwise
bool ImportCell0D(PolygonalMesh& mesh);

/// Import the Cell1D properties from Cell1Ds.csv file
/// (reference) mesh: a PolygonalMesh struct
/// return the result of the reading, true if is success, false otherwise
bool ImportCell1D(PolygonalMesh& mesh);

/// Import the Cell2D properties from Cell2Ds.csv file
/// (reference) mesh: a PolygonalMesh struct
/// return the result of the reading, true if is success, false otherwise
bool ImportCell2D(PolygonalMesh& mesh);

}
