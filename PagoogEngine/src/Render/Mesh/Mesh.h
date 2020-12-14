#pragma once

#include "Maths/Maths.h"

namespace PEngine
{
	class Mesh
	{
	public:
		Mesh();
		~Mesh();

		void Build();
		const void* GetVertexData() const;

		const float* GetPositionData() const;
		void SetPositionData(const float* positionDataToBeCopied, size_t size);

		const float* GetColourData() const;
		void SetColourData(const float* colourDataToBeCopied, size_t size);

		size_t GetAdditionalStride(int index) const;
		const void* GetAdditionalData(int index) const;
		void AddAdditionalData(const void* dataToBeCopied, size_t size, size_t stride);

		const unsigned int* GetIndexData() const;
		void SetIndexData(const unsigned int* indexDataToBeCopied, size_t size);

		/// <summary>
		/// Returns the number of vertices in the mesh.
		/// </summary>
		int Count() const;
		/// <summary>
		/// Returns the number of values in the vertex array.
		/// </summary>
		int Length() const;
		/// <summary>
		/// Returns the size of the vertex array in bytes.
		/// </summary>
		size_t Size() const;

		/// <summary>
		/// Returns the number of indices in the mesh.
		/// </summary>
		int IndexLength() const;
		/// <summary>
		/// Returns the size of the index array in bytes.
		/// </summary>
		size_t IndexSize() const;

	private:
		const int NumberOfValuesPerVertex = 3 + 3; // TODO: Use data types like Positon, Colour etc. for working out sizes

		int numberOfVertices;
		int numberOfIndices;

		void* vertexDataArray;

		float* positionDataAray;
		float* colourDataArray;

		std::vector<void*> additionalDataArrays;
		std::vector<size_t> additionalDataStrides;

		unsigned int* indexDataArray;
	};
}

