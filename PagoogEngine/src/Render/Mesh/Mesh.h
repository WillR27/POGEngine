#pragma once

#include "MeshDataTypes.h"

namespace PEngine
{
	class MeshSet;

	class Mesh
	{
	public:
		Mesh(MeshSet* meshSet);
		~Mesh();

		void Render();

		void Build();
		const void* GetVertexData() const { return vertexDataArray; }

		const Position::ValueType* GetPositionData() const { return positionDataAray; }
		void SetPositionData(const Position::ValueType* positionDataToBeCopied, int size);

		const Colour::ValueType* GetColourData() const { return colourDataArray; }
		void SetColourData(const Colour::ValueType* colourDataToBeCopied, int size);

		int GetAdditionalStride(int index) const { return additionalDataStrides[index]; }
		const void* GetAdditionalData(int index) const { return additionalDataArrays[index]; }
		void AddAdditionalData(const void* dataToBeCopied, int size, int stride);

		const unsigned int* GetIndexData() const { return indexDataArray; }
		void SetIndexData(const unsigned int* indexDataToBeCopied, int size);

		// Returns the number of vertices in the mesh.
		int Count() const { return numberOfVertices; }
		// Returns the size of the vertex array in bytes.
		int Size() const { return numberOfVertices * stride; }

		// Returns the number of indices in the mesh.
		int IndexCount() const { return numberOfIndices; }
		// Returns the size of the index array in bytes.
		int IndexSize() const { return IndexCount() * sizeof(unsigned int); }

		// Returns whether or not the mesh is currently part of a mesh set.
		bool HasMeshSet() const { return meshSet != nullptr; }

	private:
		// The stride of each vertex in bytes, i.e sizeof(position) + sizeof(colour) + sizeof(...).
		int stride;

		int numberOfVertices;
		int numberOfIndices;

		void* vertexDataArray;

		Position::ValueType* positionDataAray;
		Colour::ValueType* colourDataArray;

		std::vector<char*> additionalDataArrays;
		std::vector<int> additionalDataStrides;

		unsigned int* indexDataArray;

		MeshSet* meshSet;
	};
}

