//===========================================================================
// Name        : MeshTrial.cpp
// Author      : 
// Version     :
// Copyright   :
// Description : FEM in C++
//============================================================================

#include <iostream>
#include <vector>
#include <memory>

#include "Conditions/SHT_BC_SecondType.h"
#include "Groups/GroupList.h"
#include "Groups/GroupOfPoints.h"
#include "Groups/GroupOfLines.h"
#include "Groups/GroupOfTriangles.h"
#include "Nodes/NodeList.h"
#include "Mesh.h"


// there have to be three input parameters, namely:
// 1) the file containing computational mesh ( *.msh )
// 2) the file containing initial value parameters ( *.fem )
// 3) the name of the output file (*.vtk)
// Example: ./FEM Mesh.msh Input.fem Output.vtk

int main( int argc, char** argv ) {

	const unsigned int NUMBER_OF_INPUT_PARAMETERS = 4;

	try {

		// If there is more or less than four input parameters
		// than throw an error
		if ( argc != NUMBER_OF_INPUT_PARAMETERS ) {
			int Error(1);
			throw Error;
		}


		// Create the computational mesh
		// the first input parameter is the name of the mesh file
		Mesh aMesh( argv[1] );


		// Set initial values of the problem
		// the second input parameter is the name of the mesh file
		aMesh.setBoudaryConditions( argv[2] );
		aMesh.updateLinearSystem();


		// get Data from the mesh
		std::shared_ptr<const Matrix> StiffnessMatrix
								= aMesh.getGlobalStiffnessMatrix();

		std::shared_ptr<const Vector> RightHandSide
										= aMesh.getRightHandSide();


		// Compute inverse of the stiffness matrix
		Matrix InverseStiffnessMatrix( (*StiffnessMatrix).getNumberOfRows(),
									   (*StiffnessMatrix).getNumberOfStrings() );


		InverseStiffnessMatrix = (*StiffnessMatrix).getInverseMatrix();
		std::cout << "the inverse matrix was computed" << std::endl;


		Vector Result;
		Result.resize( (*RightHandSide).getSize() );


		// Solve Linear System
		Result = InverseStiffnessMatrix * (*RightHandSide);
		InverseStiffnessMatrix * (*RightHandSide);
		std::cout << "Linear system has been solved" << std::endl;


		// Assign the result of computation to the nodes
		aMesh.setRightHandSideAsTemperature( Result );
		std::cout << "Backward assignment was done" << std::endl;


		// Generate VTK result file
		// the third input parameter is the name of the output file
		aMesh.generateVTKFile( argv[3] );
		std::cout << "The VTK file was generated" << std::endl;

	}
	catch(...) {
		std::cout << "Some kind of error" << std::endl;
	}



	return 0;


}
