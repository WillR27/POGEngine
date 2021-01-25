#include "pgepch.h"
#include "Mesh.h"

#include "MeshSet.h"
#include "Render/Core/Render.h"

namespace PEngine
{
	Mesh::Mesh()
		: stride(0)
		, numberOfVertices(0)
		, numberOfIndices(0)
		, vertexDataArray(nullptr)
		, positionDataAray(nullptr)
		, colourDataArray(nullptr)
		, indexDataArray(nullptr)
		, meshSet(nullptr)
	{
	}

	Mesh::~Mesh()
	{
		delete[] vertexDataArray;
		delete[] positionDataAray;
		delete[] colourDataArray;
		delete[] indexDataArray;

		for (char* additionalDataArray : additionalDataArrays)
		{
			delete[] additionalDataArray;
		}

		if (vertexDataArray == nullptr)
		{
			PG_WARN("Deleted a mesh before any data was used. Are you sure you wanted to do this?");
		}
	}

	void Mesh::Render()
	{
		if (meshSet != nullptr)
		{
			meshSet->RenderMesh(this);
		}
		else
		{
			VertexArray vao; // TODO: Create on build?
			VertexBuffer vbo;
			IndexBuffer ibo;

			vao.Bind();
			vbo.Bind();
			ibo.Bind();

			vbo.SetVertexData(GetVertexData(), Size());

			vao.SetAttribute(0, 3, PG_FLOAT, false, 6 * sizeof(float), (void*)(0));
			vao.SetAttribute(1, 3, PG_FLOAT, false, 6 * sizeof(float), (void*)(3 * sizeof(float)));

			if (IndexCount() == 0)
			{
				Render::RenderTrianglesFromArrays(0, Count());
			}
			else
			{
				ibo.SetIndexData(GetIndexData(), IndexSize());

				Render::RenderTrianglesFromElements(0, IndexCount());
			}
		}
	}

	void Mesh::Build() // TODO: Mark dirty and rebuild when necessary
	{
		delete[] vertexDataArray;
		char* newVertexDataArray = new char[Size()];

		int vertexDataPos = 0;
		int dataPos = 0;

		for (int i = 0; i < numberOfVertices; i++)
		{
			dataPos = i * Position::Count;
			memcpy(&newVertexDataArray[vertexDataPos], &positionDataAray[dataPos], Position::Size);
			vertexDataPos += Position::Size;

			dataPos = i * Colour::Count;
			memcpy(&newVertexDataArray[vertexDataPos], &colourDataArray[dataPos], Colour::Size);
			vertexDataPos += Colour::Size;

			for (int j = 0; j < additionalDataArrays.size(); j++)
			{
				char* additionalDataArray = (char*)additionalDataArrays[j];
				int additionalDataStride = additionalDataStrides[j];

				dataPos = i * additionalDataStride;
				memcpy(&newVertexDataArray[vertexDataPos], &additionalDataArray[dataPos], additionalDataStride);
				vertexDataPos += additionalDataStride;
			}
		}

		vertexDataArray = newVertexDataArray;
	}

	void Mesh::SetPositionData(const Position::ValueType* positionDataToBeCopied, int size)
	{
		if (positionDataAray == nullptr)
		{
			stride += Position::Size;
		}

		delete[] positionDataAray;
		int numberOfValues = size / static_cast<int>(sizeof(Position::ValueType));
		numberOfVertices = numberOfValues / Position::Count; 
		positionDataAray = new Position::ValueType[numberOfValues];
		memcpy(positionDataAray, positionDataToBeCopied, size);
	}

	void Mesh::SetColourData(const Colour::ValueType* colourDataToBeCopied, int size)
	{
		if (colourDataArray == nullptr)
		{
			stride += Colour::Size;
		}

		delete[] colourDataArray;
		colourDataArray = new Colour::ValueType[size / sizeof(Colour::ValueType)];
		memcpy(colourDataArray, colourDataToBeCopied, size);
	}

	void Mesh::AddAdditionalData(const void* dataToBeCopied, int size, int stride)
	{
		this->stride += stride;

		char* additionalData = new char[size];
		memcpy(additionalData, dataToBeCopied, size);
		additionalDataArrays.push_back(additionalData);
		additionalDataStrides.push_back(stride);
	}

	void Mesh::SetIndexData(const unsigned int* indexDataToBeCopied, int size)
	{
		delete[] indexDataArray;
		numberOfIndices = size / static_cast<int>(sizeof(unsigned int));
		indexDataArray = new unsigned int[numberOfIndices];
		memcpy(indexDataArray, indexDataToBeCopied, size);
	}
}