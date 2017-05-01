# check the minimum version
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)


# find all *.cpp files
FILE(GLOB SOURCES ./*.cpp )


# make an object file by all *.cpp files existing
# in the current folder
ADD_LIBRARY( Supplements OBJECT ${SOURCES} ) 
