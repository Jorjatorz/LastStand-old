#pragma once

#include "FEngine.h"

//ASSIMP
#include <assimp\Importer.hpp>
#include <assimp\postprocess.h>
#include <assimp\scene.h>
#include <assimp\types.h>
#include <assimp\vector3.h>

class Mesh
{
	//Struct with all the information need for opengl to render it (a mesh is made of several submeshes, each submesh hast one associated meshstruct)
	typedef struct
	{
		//Vertices info
		std::vector<GLfloat> mVertexVector;
		std::vector<GLfloat> mNormalsVector;
		std::vector<GLfloat> mTexCoordsVector;
		std::vector<GLuint> mIndexVector;

		//openGL buffers
		GLuint vertexBuffer, normalBuffer, texCoordsBuffer, indexBuffer, vertexArrayObject;
	} tMeshComponentsStruct;
	//List containing all the cubmeshes components structs
	std::list<tMeshComponentsStruct> mSubMeshesComponentsList;

	//Generates all the opengl buffers given a meshComponentstruct
	void generateMeshComponentsBuffers(tMeshComponentsStruct& mMeshComp);

public:
	Mesh(std::string name);
	~Mesh();

	//Load the mesh (vertices, normals, etc) from a file
	bool loadMesh(std::string meshPath);

	//Renders all the submeshes into the buffer
	void renderAllSubMeshes();

private:
	std::string mName;
};

