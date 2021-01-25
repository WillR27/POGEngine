#pragma once

#include "Mesh.h"
#include "Render/Core/Objects/IndexBuffer.h"
#include "Render/Core/Objects/VertexArray.h"
#include "Render/Core/Objects/VertexBuffer.h"

namespace PEngine
{
	// An immutable set of meshes with a common vbo, ibo and vao.
	class MeshSet
	{
		friend class Mesh;

	public:
		MeshSet();
		~MeshSet();

		void Build();

		void SetAttribute(unsigned int index, unsigned int numberOfComponents, unsigned int type, bool clamped, int stride, void* offset);

		void AddMesh(Shared<Mesh> mesh);

	private:
		int count;
		int size;
		int indexCount;
		int indexSize;

		std::vector<Shared<Mesh>> meshes;
		std::vector<int> counts;
		std::vector<int> sizes;
		std::vector<int> indexCounts;
		std::vector<int> indexSizes;

		VertexBuffer vbo;
		IndexBuffer ibo;
		VertexArray vao;

		void RenderMesh(Mesh* mesh);

		void SetVertexData(const void* vertexData, int size);
		void SetIndexData(const unsigned int* indexData, int size);
	};
}

