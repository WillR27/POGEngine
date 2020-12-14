#include "pgepch.h"
#include "Mesh.h"

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

		int vertexDataPos = 0;
		int numberOfValues = 0;
		int dataPos = 0;
		int localSize = 0;

		for (int i = 0; i < numberOfVertices; i++)
		{
			numberOfValues = 3;
			dataPos = i * numberOfValues;
			localSize = sizeof(float) * numberOfValues;
			memcpy(&newVertexDataArray[vertexDataPos], &positionDataAray[dataPos], localSize);
			vertexDataPos += localSize;

			numberOfValues = 3;
			dataPos = i * numberOfValues;
			localSize = sizeof(float) * numberOfValues;
			memcpy(&newVertexDataArray[vertexDataPos], &colourDataArray[dataPos], localSize);
			vertexDataPos += localSize;

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

	const void* Mesh::GetVertexData() const
	{
		return vertexDataArray;
	}

	int Mesh::Count() const
	{
		return numberOfVertices;
	}

	int Mesh::Size() const
	{
		return numberOfVertices * stride;
	}

	int Mesh::IndexCount() const
	{
		return numberOfIndices;
	}

	int Mesh::IndexSize() const
	{
		return IndexCount() * sizeof(unsigned int);
	}

	const float* Mesh::GetPositionData() const
	{
		return positionDataAray;
	}

	void Mesh::SetPositionData(const float* positionDataToBeCopied, int size)
	{
		if (positionDataAray == nullptr)
		{
			stride += sizeof(float) * 3;
		}

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

	void Mesh::SetColourData(const float* colourDataToBeCopied, int size)
	{
		if (colourDataArray == nullptr)
		{
			stride += sizeof(float) * 3;
		}

		delete[] colourDataArray;
		colourDataArray = new float[size / sizeof(*colourDataArray)];
		memcpy(colourDataArray, colourDataToBeCopied, size);
	}

	int Mesh::GetAdditionalStride(int index) const
	{
		return additionalDataStrides[index];
	}

	const void* Mesh::GetAdditionalData(int index) const
	{
		return additionalDataArrays[index];
	}

	void Mesh::AddAdditionalData(const void* dataToBeCopied, int size, int stride)
	{
		this->stride += stride;

		void* additionalData = new char[size];
		memcpy(additionalData, dataToBeCopied, size);
		additionalDataArrays.push_back(additionalData);
		additionalDataStrides.push_back(stride);
	}

	const unsigned int* Mesh::GetIndexData() const
	{
		return indexDataArray;
	}

	void Mesh::SetIndexData(const unsigned int* indexDataToBeCopied, int size)
	{
		delete[] indexDataArray;
#pragma warning(suppress: 4267) // Ignore warning about loss of data
		numberOfIndices = size / sizeof(unsigned int);
		indexDataArray = new unsigned int[numberOfIndices];
		memcpy(indexDataArray, indexDataToBeCopied, size);
	}
}