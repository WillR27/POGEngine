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
		const float* GetVertexData() const;

		/// <summary>
		/// Returns the number of vertices in the mesh.
		/// </summary>
		unsigned int Count() const;
		/// <summary>
		/// Returns the number of values in the vertex array.
		/// </summary>
		unsigned int Length() const;
		/// <summary>
		/// Returns the size of the vertex array in bytes.
		/// </summary>
		unsigned int Size() const;

		/// <summary>
		/// Returns the number of indices in the mesh.
		/// </summary>
		unsigned int IndexLength() const;
		/// <summary>
		/// Returns the size of the index array in bytes.
		/// </summary>
		unsigned int IndexSize() const;

		const float* GetPositionData() const;
		void SetPositionData(const float* positionDataToBeCopied, unsigned int size);

		const float* GetColourData() const;
		void SetColourData(const float* colourDataToBeCopied, unsigned int size);

		const unsigned int* GetIndexData() const;
		void SetIndexData(const unsigned int* indexDataToBeCopied, unsigned int size);

	private:
		const int NumberOfValuesPerVertex = 3 + 3; // TODO: Use data types like Positon, Colour etc. for working out sizes

		unsigned int numberOfVertices;
		unsigned int numberOfIndices;

		float* vertexDataArray;

		float* positionDataAray;
		float* colourDataArray;

		unsigned int* indexDataArray;
	};
}

