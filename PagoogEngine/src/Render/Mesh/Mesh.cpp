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

	void Mesh::Build() // TODO: Mark dirty and rebuild when necessary
	{
		delete[] vertexDataArray;
		char* newVertexDataArray = new char[Size()];

		for (int i = 0; i < numberOfVertices; i++)
		{
			int vertexDataPos = i * NumberOfValuesPerVertex * sizeof(float); // Multiply by sizeof(float) as we are working with a byte array
			int dataPos = i * 3; 
			memcpy(&newVertexDataArray[vertexDataPos], &positionDataAray[dataPos], sizeof(float) * 3);

			vertexDataPos += 3 * sizeof(float);  // Multiply by sizeof(float) as we are working with a byte array
			dataPos = i * 3;
			memcpy(&newVertexDataArray[vertexDataPos], &colourDataArray[dataPos], sizeof(float) * 3);

			//for (int j = 0; j < additionalDataArrays.size(); j++)
			//{
			//	void* additionalDataArray = additionalDataArrays[j];
			//	size_t additionalDataStride = additionalDataStrides[j];

			//	vertexDataPos += ;
			//	dataPos = i * 3;
			//	memcpy(&newVertexDataArray[vertexDataPos], &colourDataArray[dataPos], sizeof(float) * 3);
			//}
		}

		vertexDataArray = newVertexDataArray;
	}

	const void* Mesh::GetVertexData() const
	{
		return vertexDataArray;
	}

	int Mesh::Count() const
	{
		return numberOfVertices;
	}

	int Mesh::Length() const
	{
		return Count() * NumberOfValuesPerVertex;
	}

	size_t Mesh::Size() const
	{
		return Length() * sizeof(float);
	}

	int Mesh::IndexLength() const
	{
		return numberOfIndices;
	}

	size_t Mesh::IndexSize() const
	{
		return IndexLength() * sizeof(unsigned int);
	}

	const float* Mesh::GetPositionData() const
	{
		return positionDataAray;
	}

	void Mesh::SetPositionData(const float* positionDataToBeCopied, size_t size)
	{
		delete[] positionDataAray;
#pragma warning(suppress: 4267) // Ignore warning about loss of data
		int numberOfValues = size / sizeof(*positionDataAray);
		numberOfVertices = numberOfValues / 3; // 3 coords per vertex
		positionDataAray = new float[numberOfValues];
		memcpy(positionDataAray, positionDataToBeCopied, size);
	}

	const float* Mesh::GetColourData() const
	{
		return colourDataArray;
	}

	void Mesh::SetColourData(const float* colourDataToBeCopied, size_t size)
	{
		delete[] colourDataArray;
		colourDataArray = new float[size / sizeof(*colourDataArray)];
		memcpy(colourDataArray, colourDataToBeCopied, size);
	}

	size_t Mesh::GetAdditionalStride(int index) const
	{
		return additionalDataStrides[index];
	}

	const void* Mesh::GetAdditionalData(int index) const
	{
		return additionalDataArrays[index];
	}

	void Mesh::AddAdditionalData(const void* dataToBeCopied, size_t size, size_t stride)
	{
		void* additionalData = new char[size];
		memcpy(additionalData, dataToBeCopied, size);
		additionalDataArrays.push_back(additionalData);
		additionalDataStrides.push_back(stride);
	}

	const unsigned int* Mesh::GetIndexData() const
	{
		return indexDataArray;
	}

	void Mesh::SetIndexData(const unsigned int* indexDataToBeCopied, size_t size)
	{
		delete[] indexDataArray;
#pragma warning(suppress: 4267) // Ignore warning about loss of data
		numberOfIndices = size / sizeof(unsigned int);
		indexDataArray = new unsigned int[numberOfIndices];
		memcpy(indexDataArray, indexDataToBeCopied, size);
	}
}