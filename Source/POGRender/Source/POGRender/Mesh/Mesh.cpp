#include "POGRenderPCH.h"
#include "Mesh.h"

#include "POGDebug.h"
#include "POGLog.h"

namespace POG::Render
{
	Mesh::Mesh()
		: vao(nullptr)
		, vbo(nullptr)
		, ibo(nullptr)
		, stride(0)
		, numberOfVertices(0)
		, numberOfIndices(0)
		, vertexDataArray(nullptr)
		, attributeData()
		, attributeCounts()
		, attributeStrides()
		, attributeTypes()
		, attributeDebugNames()
		, indexDataArray(nullptr)
		//, meshSet(nullptr)
	{
	}

	Mesh::~Mesh()
	{
		delete[] vertexDataArray;
		delete[] indexDataArray;

		for (char* data : attributeData)
		{
			delete[] data;
		}

		delete vao;
		delete vbo;
		delete ibo;

		if (vertexDataArray == nullptr)
		{
			POG_WARN("Deleted a mesh before the mesh was built. Are you sure you meant to do this?");
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
			POG_ASSERT(vao != nullptr, "Tried to render a mesh before building!");

			vao->Bind();
			vbo->Bind();
			ibo->Bind();

			if (IndexCount() == 0)
			{
				Render::RenderTrianglesFromArrays(0, VertexCount());
			}
			else
			{
				ibo->SetIndexData(GetIndexData(), IndexSize());

				Render::RenderTrianglesFromElements(0, IndexCount());
			}
		}
	}

	void Mesh::Build() // TODO: Mark dirty and rebuild when necessary
	{
		POG_ASSERT(numberOfVertices != 0, "Number of vertices for mesh has not been set!");

		if (attributeData.empty())
		{
			POG_WARN("Tried to build a mesh with no data. Are you sure meant to do this?");

			return;
		}

		delete[] vertexDataArray;
		char* newVertexDataArray = new char[VertexArraySize()];

		int vertexDataPos = 0;
		int dataPos = 0;

		for (int i = 0; i < numberOfVertices; i++)
		{
			for (int j = 0; j < attributeData.size(); j++)
			{
				int stride = attributeStrides[j];
				dataPos = i * stride;
				memcpy(&newVertexDataArray[vertexDataPos], &(attributeData[j][dataPos]), stride);
				vertexDataPos += stride;
			}
		}

		vertexDataArray = newVertexDataArray;

		delete vao;
		delete vbo;
		delete ibo;

		vao = new VertexArray();
		vbo = new VertexBuffer();
		ibo = new IndexBuffer();

		vao->Bind();
		vbo->Bind();
		ibo->Bind();

		vbo->SetVertexData(GetVertexData(), VertexArraySize());

		long long offset = 0;
		for (int i = 0; i < attributeData.size(); i++)
		{
			vao->SetAttribute(i, attributeCounts[i], attributeTypes[i], false, stride, (void*)(offset));
			offset += attributeStrides[i];
		}
	}

	void Mesh::SetAttributeData(int index, const void* dataToCopy, int size, int count, int stride, const char* debugName)
	{
		// Check if the index is out of range
		if (index >= attributeData.size())
		{
			attributeData.resize(index + 1);
			attributeCounts.resize(index + 1);
			attributeStrides.resize(index + 1);
			attributeTypes.resize(index + 1);
			attributeDebugNames.resize(index + 1);
		}

		// Delete existing data if it exists
		delete[] attributeData[index];

		// Create a new array and copy the data
		attributeData[index] = new char[size];
		memcpy(attributeData[index], dataToCopy, size);

		// Set the count
		attributeCounts[index] = count;

		// Update the total stride
		this->stride -= attributeStrides[index];
		this->stride += stride;
		attributeStrides[index] = stride;

		// Keep track of the debug names
		attributeDebugNames[index] = debugName;
	}

	void Mesh::SetIndexData(const unsigned int* indexDataToBeCopied, int size)
	{
		delete[] indexDataArray;
		numberOfIndices = size / static_cast<int>(sizeof(unsigned int));
		indexDataArray = new unsigned int[numberOfIndices];
		memcpy(indexDataArray, indexDataToBeCopied, size);
	}
}
