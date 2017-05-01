/*
 * Mesh.h
 *
 *  Created on: Mar 27, 2017
 *      Author: ravil
 */

#include <fstream>

#include "Supplements/FilePosition.h"
#include "Groups/GroupList.h"
#include "Nodes/NodeList.h"
#include "Supplements/Printable.h"


#include "LinearAlgebra/Matrix.h"
#include "LinearAlgebra/Vector.h"



#ifndef MESH_H_
#define MESH_H_

class Mesh : private Printable {
public:
	Mesh();
	Mesh( std::string FileName );
	virtual ~Mesh();

	void setMeshFileName( std::string FileName );
	void setBoudaryConditions( std::string FileName );
	void setRightHandSideAsTemperature( const Vector& aVector );


	void getInfo();
	void getGroupInfo();
	void getNodesInfo();
	void getElementInfo();


	void generateVTKFile( std::string OutputFileName = "" );

	void updateLinearSystem();


	std::shared_ptr<const Matrix>  getGlobalStiffnessMatrix();
	std::shared_ptr<const Matrix> getMassMatrix();
	std::shared_ptr<const Vector> getRightHandSide();

private:
	void processFile();
	void readLineFromFile();
	void setUpPhysicalGroups();
	void setUpNodes();
	void setUpElements();



	std::vector<std::string> parseStringToStrings( std::string );
	std::vector<unsigned int> parseStringToIntegers( std::string );
	std::vector<double> parseStringToDoubles( std::string );

	std::shared_ptr<AbstractCondition>
			buildConditionObjectFromParsedString
									( std::vector<std::string> );


	std::ifstream m_MeshFile;
	std::string m_MeshFileName;
	std::string m_InputFileName;


	unsigned int m_TotalNumberOfPhysicalGroups;
	unsigned int m_TotalNumberOfNodes;
	unsigned int m_TotalNumberOfElements;


	std::shared_ptr<NodeList> m_Nodes;
	std::shared_ptr<GroupList> m_Groups;


	std::shared_ptr<Matrix> m_GlobalStiffnessMatrix;
	std::shared_ptr<Matrix> m_MassMatrix;
	std::shared_ptr<Vector> m_RightHandSide;


	FilePosition m_PhysicalGroupsPosition;
	FilePosition m_NodesPosition;
	FilePosition m_ElementsPosition;

};

#endif /* MESH_H_ */
