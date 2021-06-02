#include "POGRenderPCH.h"
#include "Mesh.h"

#include "POGRender/Render.h"
#include "POGRender/Objects/VertexArray.h"
#include "POGRender/Objects/VertexBuffer.h"
#include "POGRender/Objects/IndexBuffer.h"

#include "POGDebug.h"
#include "POGLog.h"

namespace POG::Render
{
	Mesh::Mesh()
		: stride(0)
		, numberOfVertices(0)
		, numberOfIndices(0)
		, vertexDataArray(nullptr)
		, positionDataAray(nullptr)
		, colourDataArray(nullptr)
		, texCoordsDataArray(nullptr)
		, indexDataArray(nullptr)
		//, meshSet(nullptr)
	{
	}

	Mesh::~Mesh()
	{
		delete[] vertexDataArray;
		delete[] positionDataAray;
		delete[] colourDataArray;
		delete[] texCoordsDataArray;
		delete[] indexDataArray;

		for (char* additionalDataArray : additionalDataArrays)
		{
			delete[] additionalDataArray;
		}

		if (vertexDataArray == nullptr)
		{
			POG_WARN("Deleted a mesh before any data was used. Are you sure you wanted to do this?");
		}
	}

	void Mesh::Render()
	{
		/*if (meshSet != nullptr)
		{
			meshSet->RenderMesh(this);
		}
		else*/
		{
			VertexArray vao; // TODO: Create on build?
			VertexBuffer vbo;
			IndexBuffer ibo;

			vao.Bind();
			vbo.Bind();
			ibo.Bind();

			vbo.SetVertexData(GetVertexData(), Size());

			vao.SetAttribute(0, 3, POG_FLOAT, false, 8 * sizeof(float), (void*)(0));
			vao.SetAttribute(1, 3, POG_FLOAT, false, 8 * sizeof(float), (void*)(3 * sizeof(float)));
			vao.SetAttribute(2, 2, POG_FLOAT, false, 8 * sizeof(float), (void*)(6 * sizeof(float)));

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
			dataPos = i * Vertex::Position::Count;
			memcpy(&newVertexDataArray[vertexDataPos], &positionDataAray[dataPos], Vertex::Position::Size);
			vertexDataPos += Vertex::Position::Size;

			dataPos = i * Vertex::Colour::Count;
			memcpy(&newVertexDataArray[vertexDataPos], &colourDataArray[dataPos], Vertex::Colour::Size);
			vertexDataPos += Vertex::Colour::Size;

			dataPos = i * Vertex::TexCoords::Count;
			memcpy(&newVertexDataArray[vertexDataPos], &texCoordsDataArray[dataPos], Vertex::TexCoords::Size);
			vertexDataPos += Vertex::TexCoords::Size;

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

	void Mesh::SetPositionData(const Vertex::Position::ValueType* positionDataToBeCopied, int size)
	{
		if (positionDataAray == nullptr)
		{
			stride += Vertex::Position::Size;
		}

		delete[] positionDataAray;
		int numberOfValues = size / static_cast<int>(sizeof(Vertex::Position::ValueType));
		numberOfVertices = numberOfValues / Vertex::Position::Count;
		positionDataAray = new Vertex::Position::ValueType[numberOfValues];
		memcpy(positionDataAray, positionDataToBeCopied, size);
	}

	void Mesh::SetColourData(const Vertex::Colour::ValueType* colourDataToBeCopied, int size)
	{
		if (colourDataArray == nullptr)
		{
			stride += Vertex::Colour::Size;
		}

		delete[] colourDataArray;
		colourDataArray = new Vertex::Colour::ValueType[size / sizeof(Vertex::Colour::ValueType)];
		memcpy(colourDataArray, colourDataToBeCopied, size);
	}

	void Mesh::SetTexCoordsData(const Vertex::TexCoords::ValueType* texCoordsToBeCopied, int size)
	{
		if (texCoordsDataArray == nullptr)
		{
			stride += Vertex::TexCoords::Size;
		}

		delete[] texCoordsDataArray;
		texCoordsDataArray = new Vertex::TexCoords::ValueType[size / sizeof(Vertex::TexCoords::ValueType)];
		memcpy(texCoordsDataArray, texCoordsToBeCopied, size);
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
