#include "Mesh.h"

#include "Shader.h"

Mesh::Mesh(std::string name)
	:mName(name)
{
}


Mesh::~Mesh()
{
}

bool Mesh::loadMesh(std::string meshPath)
{
	Assimp::Importer mImporter;
	const aiScene *mAiScene = mImporter.ReadFile(meshPath.c_str(), aiProcessPreset_TargetRealtime_Fast);

	if (!mAiScene)
	{
		FE_LOG(FE_LOG::ERR, "Assimp couldn't laod the mesh. " + std::string(mImporter.GetErrorString()));
		return false;
	}

	//Process all the submeshes
	for (unsigned int i = 0; i < mAiScene->mNumMeshes; ++i)
	{
		aiMesh* loadedMesh = mAiScene->mMeshes[i];

		tMeshComponentsStruct newSubMesh;
		generateMeshComponentsBuffers(newSubMesh);

		newSubMesh.mVertexVector.reserve(loadedMesh->mNumVertices * 3);
		newSubMesh.mNormalsVector.reserve(loadedMesh->mNumVertices * 3);
		newSubMesh.mTexCoordsVector.reserve(loadedMesh->mNumVertices * 2);
		newSubMesh.mIndexVector.reserve(loadedMesh->mNumFaces * 3);

		for (unsigned int j = 0; j < loadedMesh->mNumVertices; ++j)
		{
			//create vertex array
			const aiVector3D* vertex = &loadedMesh->mVertices[j]; //copy the vertices
			const aiVector3D* normal = &loadedMesh->mNormals[j]; //copy the vertices
			const aiVector3D* texCoord = &loadedMesh->mTextureCoords[0][j];

			if (loadedMesh->HasPositions())
			{
				newSubMesh.mVertexVector.push_back(vertex->x);
				newSubMesh.mVertexVector.push_back(vertex->y);
				newSubMesh.mVertexVector.push_back(vertex->z);
			}

			if (loadedMesh->HasNormals())
			{
				newSubMesh.mNormalsVector.push_back(normal->x);
				newSubMesh.mNormalsVector.push_back(normal->y);
				newSubMesh.mNormalsVector.push_back(normal->z);
			}

			if (loadedMesh->HasTextureCoords(0))
			{
				newSubMesh.mTexCoordsVector.push_back(texCoord->x);
				newSubMesh.mTexCoordsVector.push_back(texCoord->y);
			}
		}

		for (unsigned int j = 0; j < loadedMesh->mNumFaces; ++j)
		{
			//create index array
			const aiFace* face = &loadedMesh->mFaces[j];

			assert(face->mNumIndices == 3);

			newSubMesh.mIndexVector.push_back(face->mIndices[0]);
			newSubMesh.mIndexVector.push_back(face->mIndices[1]);
			newSubMesh.mIndexVector.push_back(face->mIndices[2]);
		}

		glBindVertexArray(newSubMesh.vertexArrayObject);

		//Fill buffers
		//vertices
		if (loadedMesh->HasPositions())
		{
			glBindBuffer(GL_ARRAY_BUFFER, newSubMesh.vertexBuffer);
			glBufferData(GL_ARRAY_BUFFER, newSubMesh.mVertexVector.size() * sizeof(GLfloat), &newSubMesh.mVertexVector[0], GL_STATIC_DRAW);
			glVertexAttribPointer(Shader::VERTEXPOSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL); //write vertices position to the shader
			glEnableVertexAttribArray(Shader::VERTEXPOSITION);
		}
		//normals
		if (loadedMesh->HasNormals())
		{
			glBindBuffer(GL_ARRAY_BUFFER, newSubMesh.normalBuffer);
			glBufferData(GL_ARRAY_BUFFER, newSubMesh.mNormalsVector.size() * sizeof(GLfloat), &newSubMesh.mNormalsVector[0], GL_STATIC_DRAW);
			glVertexAttribPointer(Shader::VERTEXNORMALS, 3, GL_FLOAT, GL_FALSE, 0, NULL); //write normals position to the shader
			glEnableVertexAttribArray(Shader::VERTEXNORMALS);
		}
		//UV coords
		if (loadedMesh->HasTextureCoords(0))
		{
			glBindBuffer(GL_ARRAY_BUFFER, newSubMesh.texCoordsBuffer);
			glBufferData(GL_ARRAY_BUFFER, newSubMesh.mTexCoordsVector.size() * sizeof(GLfloat), &newSubMesh.mTexCoordsVector[0], GL_STATIC_DRAW);
			glVertexAttribPointer(Shader::VERTEXTEXCOORD, 2, GL_FLOAT, GL_FALSE, 0, NULL); //write normals position to the shader
			glEnableVertexAttribArray(Shader::VERTEXTEXCOORD);
		}

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, newSubMesh.indexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, newSubMesh.mIndexVector.size() * sizeof(GLuint), &newSubMesh.mIndexVector[0], GL_STATIC_DRAW);

		//Save the new mesh
		mSubMeshesComponentsList.push_back(newSubMesh);
	}

	// unbind buffers
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	return true;
}

void Mesh::generateMeshComponentsBuffers(tMeshComponentsStruct& mMeshComp)
{
	glGenVertexArrays(1, &mMeshComp.vertexArrayObject);
	glGenBuffers(1, &mMeshComp.vertexBuffer);
	glGenBuffers(1, &mMeshComp.normalBuffer);
	glGenBuffers(1, &mMeshComp.texCoordsBuffer);
	glGenBuffers(1, &mMeshComp.indexBuffer);
}

void Mesh::renderAllSubMeshes()
{
	//For each submesh renders its vertex array to the buffer
	foreach(subMesh, mSubMeshesComponentsList)
	{
		glBindVertexArray(subMesh->vertexArrayObject);

		glDrawElements(GL_TRIANGLES, subMesh->mIndexVector.size(), GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);
	}
}