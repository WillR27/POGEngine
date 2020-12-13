#include "pgepch.h"
#include "Mesh.h"

namespace PEngine
{
	Mesh::Mesh()
		: numberOfVertices(0)
		, numberOfIndices(0)
		, vertexDataArray(nullptr)
		, positionDataAray(nullptr)
		, colourDataArray(nullptr)
		, indexDataArray(nullptr)
	{
	}

	Mesh::~Mesh()
	{
		delete[] vertexDataArray;
		delete[] positionDataAray;
		delete[] colourDataArray;
		delete[] indexDataArray;

		PG_ASSERT(vertexDataArray, "Deleted a mesh before any data was used. Are you sure you wanted to do this?");
		PG_ASSERT(positionDataAray, "Deleted a mesh before any data was set. Are you sure you wanted to do this?");
	}

	void Mesh::Build()
	{
		delete[] vertexDataArray;
		unsigned int lengthOfVertexArray = numberOfVertices * NumberOfValuesPerVertex;
		vertexDataArray = new float[lengthOfVertexArray];

		for (unsigned int i = 0; i < numberOfVertices; i++)
		{
			unsigned int vertexDataPos = i * NumberOfValuesPerVertex;

			unsigned int positionDataPos = i * 3;
			vertexDataArray[vertexDataPos + 0] = positionDataAray[positionDataPos + 0];
			vertexDataArray[vertexDataPos + 1] = positionDataAray[positionDataPos + 1];
			vertexDataArray[vertexDataPos + 2] = positionDataAray[positionDataPos + 2];

			vertexDataPos += 3;
			unsigned int colourDataPos = i * 3;
			vertexDataArray[vertexDataPos + 0] = colourDataArray[colourDataPos + 0];
			vertexDataArray[vertexDataPos + 1] = colourDataArray[colourDataPos + 1];
			vertexDataArray[vertexDataPos + 2] = colourDataArray[colourDataPos + 2];
		}
	}

	const float* Mesh::GetVertexData() const
	{
		return vertexDataArray;
	}

	unsigned int Mesh::Count() const
	{
		return numberOfVertices;
	}

	unsigned int Mesh::Length() const
	{
		return Count() * NumberOfValuesPerVertex;
	}

	unsigned int Mesh::Size() const
	{
		return Length() * sizeof(float);
	}

	unsigned int Mesh::IndexLength() const
	{
		return numberOfIndices;
	}

	unsigned int Mesh::IndexSize() const
	{
		return IndexLength() * sizeof(unsigned int);
	}

	const float* Mesh::GetPositionData() const
	{
		return positionDataAray;
	}

	void Mesh::SetPositionData(const float* positionDataToBeCopied, unsigned int size)
	{
		delete[] positionDataAray;
		int numberOfValues = size / sizeof(*positionDataAray);
		numberOfVertices = numberOfValues / 3; // 3 coords per vertex
		positionDataAray = new float[numberOfValues];
		memcpy(positionDataAray, positionDataToBeCopied, size);
	}

	const float* Mesh::GetColourData() const
	{
		return colourDataArray;
	}

	void Mesh::SetColourData(const float* colourDataToBeCopied, unsigned int size)
	{
		delete[] colourDataArray;
		colourDataArray = new float[size / sizeof(*colourDataArray)];
		memcpy(colourDataArray, colourDataToBeCopied, size);
	}

	const unsigned int* Mesh::GetIndexData() const
	{
		return indexDataArray;
	}

	void Mesh::SetIndexData(const unsigned int* indexDataToBeCopied, unsigned int size)
	{
		delete[] indexDataArray;
		numberOfIndices = size / sizeof(unsigned int);
		indexDataArray = new unsigned int[numberOfIndices];
		memcpy(indexDataArray, indexDataToBeCopied, size);
	}
}