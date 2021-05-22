#pragma once

#include "MeshDataTypes.h"

namespace POG::Render
{
	class Mesh
	{
		friend class MeshSet;

	public:
		Mesh();
		Mesh(const Mesh&) = delete;
		Mesh(Mesh&&) = delete;

		~Mesh();

		//void* operator new(size_t size) { return ::new Mesh(); }
		//void* operator new[](size_t size) = delete;
		//void operator delete(void* mesh) { ::delete mesh; }
		//void operator delete[](void* mesh) = delete;

		void Render();

		void Build();
		const void* GetVertexData() const { return vertexDataArray; }

		const Vertex::Position::ValueType* GetPositionData() const { return positionDataAray; }
		void SetPositionData(const Vertex::Position::ValueType* positionDataToBeCopied, int size);

		const Vertex::Colour::ValueType* GetColourData() const { return colourDataArray; }
		void SetColourData(const Vertex::Colour::ValueType* colourDataToBeCopied, int size);

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
		//bool HasMeshSet() const { return meshSet != nullptr; }

	private:
		// The stride of each vertex in bytes, i.e sizeof(position) + sizeof(colour) + sizeof(...).
		int stride;

		int numberOfVertices;
		int numberOfIndices;

		void* vertexDataArray;

		Vertex::Position::ValueType* positionDataAray;
		Vertex::Colour::ValueType* colourDataArray;

		std::vector<char*> additionalDataArrays;
		std::vector<int> additionalDataStrides;

		unsigned int* indexDataArray;

		//MeshSet* meshSet;
	};
}