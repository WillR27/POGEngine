#include "pgepch.h"
#include "MeshSet.h"

#include "Render/Core/CoreRenderingUtil.h"
#include "Render/Core/Render.h"

namespace PEngine
{
	MeshSet::MeshSet()
		: vbo() // TODO: Construct inside build as we may not want an ibo
		, ibo()
		, vao()
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

	MeshSet::~MeshSet()
	{
		for (Shared<Mesh> mesh : meshes)
		{
			mesh->meshSet = nullptr;
		}
	}

	void MeshSet::Build()
	{
		vao.Bind();
		vbo.Bind();
		ibo.Bind();

		for (Shared<Mesh> mesh : meshes)
		{
			count += mesh->Count();
			size += mesh->Size();
			indexCount += mesh->IndexCount();
			indexSize += mesh->IndexSize();
		}

		char* combinedVertexDataArray = new char[size];

		int countOffset = 0;
		int sizeOffset = 0;

		for (Shared<Mesh> mesh : meshes)
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

			int indexCountOffset = 0;
			int indexSizeOffset = 0;
			unsigned int indexNumberOffset = 0;

			for (Shared<Mesh> mesh : meshes)
			{
				indexCounts.push_back(indexCountOffset);
				indexSizes.push_back(indexSizeOffset);

				unsigned int* updatedIndexDataArray = new unsigned int[mesh->IndexCount()];
				for (int i = 0; i < mesh->IndexCount(); i++)
				{
#pragma warning(suppress: 6386) // Ignore warning about buffer overrun
					updatedIndexDataArray[i] = (mesh->GetIndexData()[i] + indexNumberOffset);
				}

				memcpy(&combinedIndexDataArray[indexCountOffset], updatedIndexDataArray, mesh->IndexSize());

				delete[] updatedIndexDataArray;

				indexCountOffset += mesh->IndexCount();
				indexSizeOffset += mesh->IndexSize();
				indexNumberOffset += mesh->Count();
			}

			SetIndexData(combinedIndexDataArray, indexSize);
			delete[] combinedIndexDataArray;
		}
	}

	void MeshSet::AddMesh(Shared<Mesh> mesh)
	{
		if (std::count(meshes.begin(), meshes.end(), mesh) != 0)
		{
			PG_WARN("Mesh not added to mesh set! The mesh was already present in the mesh set.");
			return;
		}

		// Let the mesh know what mesh set contains it
		mesh->meshSet = this;

		// Add the mesh to the vector of meshes
		meshes.push_back(mesh);
	}

	void MeshSet::RenderMesh(Mesh* mesh)
	{
		int index = 0;
		for (Shared<Mesh> storedMesh : meshes)
		{
			if (&(*storedMesh) == mesh)
			{
				break;
			}

			index++;
		}

		if (index == meshes.size())
		{
			PG_ERROR("No matching mesh found!");
		}

		vao.Bind();

		if (mesh->IndexCount() == 0)
		{
			Render::RenderTrianglesFromArrays(counts[index], mesh->Count());
		}
		else
		{
			Render::RenderTrianglesFromElements(indexCounts[index], mesh->IndexCount());
		}
	}

	void MeshSet::SetAttribute(unsigned int index, unsigned int numberOfComponents, unsigned int type, bool clamped, int stride, void* offset)
	{
		vao.SetAttribute(index, numberOfComponents, type, clamped, stride, offset);
	}

	void MeshSet::SetVertexData(const void* vertexData, int size)
	{
		vbo.SetVertexData(vertexData, size);
	}

	void MeshSet::SetIndexData(const unsigned int* indexData, int size)
	{
		if (size != 0)
		{
			ibo.SetIndexData(indexData, size);
		}
	}
}