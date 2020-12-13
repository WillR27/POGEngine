#include "pgepch.h"
#include "StaticMeshSet.h"

#include "Render/Core/Render.h"
#include "Render/Core/CoreRenderingUtil.h"

namespace PEngine
{
	StaticMeshSet::StaticMeshSet()
		: MeshSet::MeshSet()
		, count(0)
		, length(0)
		, size(0)
		, indexLength(0)
		, indexSize(0)
		, meshes()
		, countOffsets()
		, lengthOffsets()
		, sizeOffsets()
		, indexLengthOffsets()
		, indexSizeOffsets()
	{
	}

	StaticMeshSet::~StaticMeshSet()
	{
	}

	void StaticMeshSet::Build()
	{
		GetVAO().Bind();
		GetVBO().Bind();
		GetIBO().Bind();

		float* combinedVertexDataArray = new float[length];

		unsigned int countOffset = 0;
		unsigned int lengthOffset = 0;
		unsigned int sizeOffset = 0;

		for (const Mesh* mesh : meshes)
		{
			countOffsets.push_back(countOffset);
			lengthOffsets.push_back(lengthOffset);
			sizeOffsets.push_back(sizeOffset);

			memcpy(&combinedVertexDataArray[lengthOffset], mesh->GetVertexData(), mesh->Size());

			countOffset += mesh->Count();
			lengthOffset += mesh->Length();
			sizeOffset += mesh->Size();
		}

		SetVertexData(combinedVertexDataArray, size);
		delete[] combinedVertexDataArray;

		if (indexSize != 0)
		{
			unsigned int* combinedIndexDataArray = new unsigned int[indexLength];

			unsigned int indexLengthOffset = 0;
			unsigned int indexSizeOffset = 0;

			for (const Mesh* mesh : meshes)
			{
				indexLengthOffsets.push_back(indexLengthOffset);
				indexSizeOffsets.push_back(indexSizeOffset);

				memcpy(&combinedIndexDataArray[indexLengthOffset], mesh->GetIndexData(), mesh->IndexSize());

				indexLengthOffset += mesh->IndexLength();
				indexSizeOffset += mesh->IndexSize();
			}

			SetIndexData(combinedIndexDataArray, indexSize);
			delete[] combinedIndexDataArray;
		}
	}

	void StaticMeshSet::AddMesh(const Mesh& mesh)
	{
		count += mesh.Count();
		length += mesh.Length();
		size += mesh.Size();
		indexLength += mesh.IndexLength();
		indexSize += mesh.IndexSize();
		meshes.push_back(&mesh);
	}

	void StaticMeshSet::RenderMesh(const Mesh& mesh)
	{
		std::vector<const Mesh*>::iterator it = std::find(meshes.begin(), meshes.end(), &mesh); // TODO: Replace with func/macro
		
		if (it == meshes.end())
		{
			PG_ERROR("No matching mesh found!");
		}

		ScopedBind bind(GetVAO());

		long long index = std::distance(meshes.begin(), it);
		
		if (indexSize == 0)
		{
			Render::RenderTrianglesFromArrays(countOffsets[index], mesh.Count());
		}
		else
		{
			Render::RenderTrianglesFromElements(indexLengthOffsets[index], mesh.IndexLength());
		}
	}

	void StaticMeshSet::SetAttribute(unsigned int index, unsigned int numberOfComponents, unsigned int type, bool clamped, int stride, void* offset)
	{
		GetVAO().SetAttribute(index, numberOfComponents, type, clamped, stride, offset);
	}

	void StaticMeshSet::SetVertexData(const float* vertexData, unsigned int size)
	{
		VertexBuffer& vbo = GetVBO();
		vbo.SetVertexData(vertexData, size);
	}

	void StaticMeshSet::SetIndexData(const unsigned int* indexData, unsigned int size)
	{
		if (size != 0)
		{
			IndexBuffer& ibo = GetIBO();
			ibo.SetIndexData(indexData, size);
		}
	}
}