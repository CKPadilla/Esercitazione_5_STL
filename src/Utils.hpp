#pragma once

#include <iostream>
#include "PolygonalMesh.hpp"

using namespace std;
using namespace PolygonalLibrary;

namespace PolygonalLibrary
{
bool ImportMesh(PolygonalMesh& mesh, 
                const string& inFile_0,
                const string& inFile_1,
                const string& inFile_2);
                
bool ImportCell0D(PolygonalMesh& mesh, const string& Cell0D_inputFile);

bool ImportCell1D(PolygonalMesh& mesh, const string& Cell1D_inputFile);

bool ImportCell2D(PolygonalMesh& mesh, const string& Cell2D_inputFile);

}
