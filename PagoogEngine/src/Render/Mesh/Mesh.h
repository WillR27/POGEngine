#pragma once

#include "MeshDataTypes.h"

namespace PEngine
{
	class MeshSet;

	class Mesh
	{
	public:
		Mesh(MeshSet& meshSet);
		~Mesh();

		void Render();

		void Build();
		const void* GetVertexData() const;

		const Position::ValueType* GetPositionData() const;
		void SetPositionData(const Position::ValueType* positionDataToBeCopied, int size);

		const Colour::ValueType* GetColourData() const;
		void SetColourData(const Colour::ValueType* colourDataToBeCopied, int size);

		int GetAdditionalStride(int index) const;
		const void* GetAdditionalData(int index) const;
		void AddAdditionalData(const void* dataToBeCopied, int size, int stride);

		const unsigned int* GetIndexData() const;
		void SetIndexData(const unsigned int* indexDataToBeCopied, int size);

		/// <summary>
		/// Returns the number of vertices in the mesh.
		/// </summary>
		int Count() const;
		/// <summary>
		/// Returns the size of the vertex array in bytes.
		/// </summary>
		int Size() const;

		/// <summary>
		/// Returns the number of indices in the mesh.
		/// </summary>
		int IndexCount() const;
		/// <summary>
		/// Returns the size of the index array in bytes.
		/// </summary>
		int IndexSize() const;

		/// <summary>
		/// Returns whether or not the mesh is currently part of a mesh set.
		/// </summary>
		bool HasMeshSet() const;

	private:
		/// <summary>
		/// The stride of each vertex in bytes, i.e sizeof(position) + sizeof(colour) + sizeof(...).
		/// </summary>
		int stride;

		int numberOfVertices;
		int numberOfIndices;

		void* vertexDataArray;

		float* positionDataAray;
		float* colourDataArray;

		std::vector<char*> additionalDataArrays;
		std::vector<int> additionalDataStrides;

		unsigned int* indexDataArray;

		MeshSet* meshSet;
	};
}

