# check the minimum version
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)


# set all project settings
PROJECT(FEM)
SET(PROJECT_VERSION 0.1)


#set up compiler flags
SET(CMAKE_CXX_STANDARD 11)


# set all requited boost libraries directly
SET(BOOST_ROOT /usr/include/boost)
SET(UBLAS  ${BOOST_ROOT}/numeric/ublas/)
INCLUDE_DIRECTORIES(UBLAS)


# creat the set of all folders
LIST(APPEND FOLDER_NAMES  Conditions
                          Elements 
                          Groups 
                          LinearAlgebra
                          Nodes
                          Supplements )


# Add all includes files and subdirectories
# Declare all necessary lists of variables
foreach(iterator ${FOLDER_NAMES})
    SET(TMP ${CMAKE_SOURCE_DIR}/${iterator}/)
    LIST(APPEND FOLDERS ${TMP})
    LIST(APPEND TARGETS $<TARGET_OBJECTS:${iterator}>)     

    ADD_SUBDIRECTORY(${TMP}) 
    INCLUDE_DIRECTORIES(${TMP})
endforeach()


# Declare anaddition list of *.cpp files
LIST(APPEND ADDITONAL_FILES Mesh.cpp)


#declare executable 
ADD_EXECUTABLE(${PROJECT_NAME}.${PROJECT_VERSION} 
                                                FEM.cpp 
                                                ${ADDITONAL_FILES} 
                                                ${TARGETS})
