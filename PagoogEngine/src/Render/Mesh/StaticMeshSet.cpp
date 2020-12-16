#include "pgepch.h"
#include "StaticMeshSet.h"

#include "Render/Core/Render.h"
#include "Render/Core/CoreRenderingUtil.h"

namespace PEngine
{
	StaticMeshSet::StaticMeshSet()
		: MeshSet::MeshSet()
		, count(0)
		, size(0)
		, indexCount(0)
		, indexSize(0)
		, meshes()
		, counts()
		, sizes()
		, indexCounts()
		, indexSizes()
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

		for (const Mesh* mesh : meshes)
		{
			count += mesh->Count();
			size += mesh->Size();
			indexCount += mesh->IndexCount();
			indexSize += mesh->IndexSize();
		}

		char* combinedVertexDataArray = new char[size];

		int countOffset = 0;
		int sizeOffset = 0;

		for (const Mesh* mesh : meshes)
		{
			counts.push_back(countOffset);
			sizes.push_back(sizeOffset);

			memcpy(&combinedVertexDataArray[sizeOffset], mesh->GetVertexData(), mesh->Size());

			countOffset += mesh->Count();
			sizeOffset += mesh->Size();
		}

		SetVertexData(combinedVertexDataArray, size);
		delete[] combinedVertexDataArray;

		if (indexSize != 0)
		{
			unsigned int* combinedIndexDataArray = new unsigned int[indexCount];

			unsigned int indexCountOffset = 0;
			unsigned int indexSizeOffset = 0;

			for (const Mesh* mesh : meshes)
			{
				indexCounts.push_back(indexCountOffset);
				indexSizes.push_back(indexSizeOffset);

				memcpy(&combinedIndexDataArray[indexCountOffset], mesh->GetIndexData(), mesh->IndexSize());

				indexCountOffset += mesh->IndexCount();
				indexSizeOffset += mesh->IndexSize();
			}

			SetIndexData(combinedIndexDataArray, indexSize);
			delete[] combinedIndexDataArray;
		}
	}

	void StaticMeshSet::AddMesh(Mesh& mesh)
	{
		if (std::count(meshes.begin(), meshes.end(), &mesh) != 0)
		{
			PG_WARN("Mesh not added to mesh set! The mesh was already present in the mesh set.");
			return;
		}

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
			Render::RenderTrianglesFromArrays(counts[index], mesh.Count());
		}
		else
		{
			Render::RenderTrianglesFromElements(indexCounts[index], mesh.IndexCount());
		}
	}

	void StaticMeshSet::SetAttribute(unsigned int index, unsigned int numberOfComponents, unsigned int type, bool clamped, int stride, void* offset)
	{
		GetVAO().SetAttribute(index, numberOfComponents, type, clamped, stride, offset);
	}

	void StaticMeshSet::SetVertexData(const void* vertexData, int size)
	{
		VertexBuffer& vbo = GetVBO();
		vbo.SetVertexData(vertexData, size);
	}

	void StaticMeshSet::SetIndexData(const unsigned int* indexData, int size)
	{
		if (size != 0)
		{
			IndexBuffer& ibo = GetIBO();
			ibo.SetIndexData(indexData, size);
		}
	}
}