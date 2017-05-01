/*
 * Mesh.cpp
 *
 *  Created on: Mar 27, 2017
 *      Author: ravil
 */

#include <sstream>
#include <fstream>
#include <memory>
#include <streambuf>

#include "Mesh.h"

#include "Supplements/FilePosition.h"
#include "Nodes/Node.h"
#include "Nodes/NodeList.h"
#include "Groups/GroupList.h"

#include "Conditions/AbstractCondition.h"
#include "Conditions/SHT_General.h"
#include "Conditions/SHT_BC_FirstType.h"
#include "Conditions/SHT_BC_SecondType.h"
#include "Conditions/SHT_BC_ThirdType.h"



Mesh::Mesh() : m_MeshFileName(),
			   m_InputFileName(),
			   m_TotalNumberOfPhysicalGroups(0),
			   m_TotalNumberOfNodes(0),
			   m_TotalNumberOfElements(0),
			   m_Nodes( new NodeList() ),
			   m_Groups( new GroupList( m_Nodes ) ),
			   m_GlobalStiffnessMatrix( new Matrix(0,0) ),
			   m_MassMatrix( new Matrix(0,0) ),
			   m_RightHandSide( new Vector(0) ) {

	// TODO Auto-generated constructor stub

}

Mesh::Mesh(std::string FileName) : m_MeshFileName( FileName ),
								   m_InputFileName(),
								   m_TotalNumberOfPhysicalGroups(0),
								   m_TotalNumberOfNodes(0),
								   m_TotalNumberOfElements(0),
								   m_Nodes( new NodeList ),
								   m_Groups( new GroupList( m_Nodes ) ),
								   m_GlobalStiffnessMatrix( new Matrix(0,0) ),
								   m_MassMatrix( new Matrix(0,0) ),
								   m_RightHandSide( new Vector(0) ) {
	processFile();
}


Mesh::~Mesh() {
	if ( m_MeshFile.is_open() ) {
		m_MeshFile.close();
	}

	// TODO Auto-generated destructor stub
}

void Mesh::setMeshFileName( std::string FileName ) {
	m_MeshFileName = FileName;
	processFile();
}


void Mesh::setBoudaryConditions(std::string FileName) {
	std::fstream File( FileName, std::fstream::in );

	// If there is some problem with accessing
	// the input file throw the error
	if ( !File.is_open() ) {
		int Error(1);
		throw Error;
	}


	std::string Buffer;

	// Skip the header of the file
	while ( Buffer != "$InputData" ) {
		std::getline( File, Buffer );
	}


	// read the number of entries
	std::getline( File, Buffer );
	unsigned int NumberOfEntries = std::stoi( Buffer );


	// read the certain number of strings specifying by
	// previous line
	std::vector<std::string> ParsedString;
	for ( unsigned int i = 0; i < NumberOfEntries; ++i ) {


		// if there is the end of the file within for-loop
		// it means that the user make a mistake compiling
		// the input file. The process has to be stopped
		if( File.eof()  ) {
			int Error(1);
			throw Error;
		}


		// Read a new line and from the input file
		std::getline( File, Buffer );


		// Parse the new string
		ParsedString = parseStringToStrings( Buffer );

		std::shared_ptr<AbstractCondition> aCondition(0);
		try {
		// Create the appropriate boundary condition object
			aCondition = buildConditionObjectFromParsedString( ParsedString );
		}
		catch( int Error ){
			std::cout << "Catch an error during the condition processing"<< std::endl;
			throw Error;
		}

		// insert the Global Stiffness matrix, Mass matrix
		// and Right-Hand-Side vector into the condition object
		aCondition->setGlobalStiffnessMatrix( m_GlobalStiffnessMatrix );
		aCondition->setMassMatrix( m_MassMatrix );
		aCondition->setRightHandSide( m_RightHandSide );


		// insert the constructed boundary condition object
		// to the appropriate group ( ParsedString[0] - is the name
		// of the group )
		m_Groups->insertCondition( ParsedString[0], aCondition );
	}

	File.close();
}


void Mesh::readLineFromFile() {

	// Initialize the buffer string
	std::string Buffer("");

	// Skip the header
	while( Buffer != "$PhysicalNames" ) {
		std::getline( m_MeshFile, Buffer );
	}


	// Read the number of Physical groups
	std::getline( m_MeshFile, Buffer );
	m_TotalNumberOfPhysicalGroups = std::stoi( Buffer );


	// Set both the start and end positions within the file
	// in order to read the PHYSICAL GROUPS
	m_PhysicalGroupsPosition.setStartPosition( m_MeshFile.tellg() );
	std::getline( m_MeshFile, Buffer );
	while( Buffer != "$EndPhysicalNames" ) {
		std::getline( m_MeshFile, Buffer );
	}
	m_PhysicalGroupsPosition.setEndPosition( m_MeshFile.tellg() );
	std::getline( m_MeshFile, Buffer );


	// Read the number of Nodes
	std::getline( m_MeshFile, Buffer );
	m_TotalNumberOfNodes = std::stoi( Buffer );


	// Set both the start and end positions within the file
	// in order to read the NODES
	m_NodesPosition.setStartPosition( m_MeshFile.tellg() );
	std::getline( m_MeshFile, Buffer );
	while( Buffer != "$EndNodes" ) {
		std::getline( m_MeshFile, Buffer );
	}
	m_NodesPosition.setEndPosition( m_MeshFile.tellg() );
	std::getline( m_MeshFile, Buffer );


	// Read the Number of Elements
	std::getline( m_MeshFile, Buffer );
	m_TotalNumberOfElements = std::stoi( Buffer );



	// Set both the start and end positions within the file
	// in order to read the ELEMENTS
	m_ElementsPosition.setStartPosition( m_MeshFile.tellg() );
	std::getline( m_MeshFile, Buffer );
	while( Buffer != "$EndElements" ) {
		std::getline( m_MeshFile, Buffer );
	}
	m_ElementsPosition.setEndPosition( m_MeshFile.tellg() );

}


void Mesh::getInfo() {
	std::cout << "# Groups: " << m_TotalNumberOfPhysicalGroups << std::endl;
	std::cout << "# Nodes: " << m_TotalNumberOfNodes << std::endl;
	std::cout << "# Elemets: " << m_TotalNumberOfElements << std::endl;

}


void Mesh::setUpPhysicalGroups() {

	// Initialize the buffer string
	std::string Buffer("");


	// Set the appropriate position of the beginning
	// the PHYSICAL-GROUP entry chunk
	m_MeshFile.seekg( m_PhysicalGroupsPosition.getStartPosition() );


	// Set the appropriate position of the end
	// the PHYSICAL-GROUP entry chunk
	std::ios::pos_type EndPosition = m_PhysicalGroupsPosition.getEndPosition();


	// Read the block of NODES within the file
	std::getline( m_MeshFile, Buffer );
	while( EndPosition != m_MeshFile.tellg() ) {


		try{

			// Take a string from the file -> parse it -> create a group
			m_Groups->insertGroup( parseStringToStrings( Buffer ) );

		}
		catch(...) {
			std::cout << " Can't create a physical group " << std::endl;
		}

		std::getline( m_MeshFile, Buffer );
	}
}


void Mesh::setUpNodes() {

	std::string Buffer;

	// Set the appropriate position of the beginning
	// the NODE entry chunk
	m_MeshFile.seekg( m_NodesPosition.getStartPosition() );

	// Set the appropriate position of the end
	// the NODE entry chunk
	std::ios::pos_type EndPosition = m_NodesPosition.getEndPosition();

	// Read the block of NODES within the file
	std::getline( m_MeshFile, Buffer );
	while( EndPosition != m_MeshFile.tellg() ) {

		// Take a string from the file -> parse it -> create a node
		// in the list of nodes
		m_Nodes->setNode( parseStringToDoubles( Buffer ) );

		std::getline( m_MeshFile, Buffer );
	}

}


void Mesh::setUpElements() {

	std::string Buffer("");

	// Set the appropriate position of the beginning
	// the ELEMENTS entry chunk
	m_MeshFile.seekg( m_ElementsPosition.getStartPosition() );

	// Set the appropriate position of the end
	// the ELEMENTS entry chunk
	std::ios::pos_type m_EndPosition = m_ElementsPosition.getEndPosition();

	// Read the block of ELEMENTS within the file
	std::getline( m_MeshFile, Buffer );
	while( m_EndPosition != m_MeshFile.tellg() ) {

		// Take a string from the file -> parse it ->
		// pass it bundle to an appropriate group
		// and create the element
		m_Groups->insertElement( parseStringToIntegers( Buffer ) );

		std::getline( m_MeshFile, Buffer );
	}
}


std::vector<std::string> Mesh::parseStringToStrings(std::string String) {


	// Throw an error if we can see that the string is empty
	if ( String.empty() ) {
		int Error(1);
		throw Error;
	}

	std::vector<std::string> Container;
	std::string Buffer;
	const char DELIMITER = '\t';
	const char SPACE = ' ';

	// Go through all entries of the string
	for ( auto Iterator = String.begin();
		  Iterator != String.end();
		  ++Iterator ) {

		// If the current character of the string
		// is not equal to the "space" symbol then we're going to
		// place it into the string buffer
		if ( (*Iterator != DELIMITER) && ( *Iterator != SPACE ) ) {
			Buffer.push_back( *Iterator );
		}

		// Otherwise we're going to put
		// the result into the container
		else {
			Container.push_back( Buffer );
			Buffer.clear();
		}

	}

	// Process the last element in the string
	Container.push_back( Buffer );

	return Container;
}


std::vector<double> Mesh::parseStringToDoubles( std::string String ) {

	// Parse a string in order to get a vector of its entries
	std::vector<std::string> Container = parseStringToStrings( String );

	// Convert each entry from string type to double one
	std::vector<double> Result;
	for( auto Iterator = Container.begin();
		 Iterator != Container.end();
		 ++Iterator ) {
		Result.push_back( std::stod( *Iterator ) );
	}

	return Result;
}


std::vector<unsigned int> Mesh::parseStringToIntegers(std::string String) {

	// Parse a string in order to get a vector of its entries
	std::vector<std::string> Container = parseStringToStrings( String );

	// Convert each entry from string type to double one
	std::vector<unsigned int> Result;
	for( auto Iterator = Container.begin();
		 Iterator != Container.end();
		 ++Iterator ) {
		Result.push_back( std::stoi( *Iterator ) );
	}

	return Result;
}


void Mesh::getGroupInfo() {
	m_Groups->getInfo();
}


void Mesh::getNodesInfo() {
	m_Nodes->printCoordinatesInfo();
}


void Mesh::getElementInfo() {
}


void Mesh::generateVTKFile(std::string OutputFileName) {

	// Open output vtk-file
	std::ofstream OutputFile;
	OutputFile.open( OutputFileName.c_str(), std::fstream::trunc );

	std::streambuf* OutputFileBuffer(0);
	if ( !OutputFileName.empty() ) {
		OutputFileBuffer = OutputFile.rdbuf();
	}
	else {
		OutputFileBuffer = std::cout.rdbuf();
	}


	// Print the main header of the VTK file
	print("# vtk DataFile Version 3.1", OutputFileBuffer);
	print("FEM", OutputFileBuffer);
	print("ASCII", OutputFileBuffer);
	print("DATASET UNSTRUCTURED_GRID", OutputFileBuffer);


	// Print coordinate point header according to the VTK format
	print(	"POINTS "
			+ std::to_string(m_Nodes->getNumberOfNodes())
			+ " FLOAT",
			OutputFileBuffer );


	// Print the x, y, z coordinates of the nodes
	m_Nodes->printCoordinatesInfo( OutputFileBuffer );


	// Print the header of element chunk
	print(	"CELLS "
			+ std::to_string(m_Groups->getTotalNumberOfElements())
			+ " "
			+ std::to_string(m_Groups->getTotalNumberOfEntries()),
			OutputFileBuffer );


	// Print all elements according VTK format
	m_Groups->printElementsAccordingToVtkFormat( OutputFileBuffer );


	// Print the header of element type chunk
	print(	"CELL_TYPES "
			+ std::to_string(m_Groups->getTotalNumberOfElements()),
			OutputFileBuffer );


	// Print all element types according VTK format
	m_Groups->printElementsTypeAccordingToVtkFormat( OutputFileBuffer );


	// Print the header of data chunk
	print( "POINT_DATA "
			+ std::to_string(m_Nodes->getNumberOfNodes()),
			OutputFileBuffer );


	//Print Temperature data
	m_Nodes->printTemperatureInfo( OutputFileBuffer );


	OutputFile.close();
}


void Mesh::processFile() {

	// open mesh file
	m_MeshFile.open( m_MeshFileName, std::fstream::in );

	// if there is some problem to open the file
	// throw the error
	if ( !m_MeshFile.is_open() ) {
		int Error(1);
		throw Error;
	}

	readLineFromFile();

	// process nodes
	setUpNodes();

	// process physical groups
	setUpPhysicalGroups();

	// process elements
	setUpElements();
}


std::shared_ptr<AbstractCondition>
				Mesh::buildConditionObjectFromParsedString
						( std::vector<std::string> aParsedString ) {

	std::shared_ptr<AbstractCondition> Object(0);

	if ( aParsedString[1] == "SHT_General" ) {
			Object.reset( new SHT_General() );
			return Object;
		}

		else if ( aParsedString[1] == "SHT_BC_FirstType" ) {
			Object.reset( new SHT_BC_FirstType( std::stod( aParsedString[2] ) ) );
			return Object;
		}

		else if ( aParsedString[1] == "SHT_BC_SecondType" ) {
			Object.reset( new SHT_BC_SecondType( std::stod( aParsedString[2] ) ) );
			return Object;
		}

		else if ( aParsedString[1] == "SHT_BC_ThirdType" ) {
			Object.reset( new SHT_BC_ThirdType( std::stod( aParsedString[2] ),
							std::stod( aParsedString[3] ),
							std::stod( aParsedString[4] ) ));

			return Object;
		}

		else {
			// if there is no such boundary condition
			// throw an error
			int Error(1);
			throw Error;
		}


}

void Mesh::updateLinearSystem() {

	m_GlobalStiffnessMatrix.get()->resize( m_TotalNumberOfNodes,
										   m_TotalNumberOfNodes );


	// That block has to be uncommented only when
	// transient FEM problem will be implemented
	//m_MassMatrix.get()->resize( m_TotalNumberOfNodes,
	//							m_TotalNumberOfNodes );


	m_RightHandSide.get()->resize( m_TotalNumberOfNodes );

	m_Groups->updateLinearSystem();
}


std::shared_ptr<const Matrix> Mesh::getGlobalStiffnessMatrix() {
	return m_GlobalStiffnessMatrix;
}


std::shared_ptr<const Matrix> Mesh::getMassMatrix() {
	return m_MassMatrix;
}


std::shared_ptr<const Vector> Mesh::getRightHandSide() {
	return m_RightHandSide;
}

void Mesh::setRightHandSideAsTemperature( const Vector& Temperature ) {

	m_Nodes->setRightHandSideAsTemperature( Temperature );

}
