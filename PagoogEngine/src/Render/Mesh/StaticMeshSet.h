#pragma once

#include "MeshSet.h"

namespace PEngine
{
	/// <summary>
	/// An immutable set of meshes with a common vbo, ibo and vao.
	/// </summary>
	class StaticMeshSet : public MeshSet
	{
	public:
		StaticMeshSet();
		~StaticMeshSet();

		virtual void Build() override;

		virtual void RenderMesh(const Mesh& mesh) override;

		void SetAttribute(unsigned int index, unsigned int numberOfComponents, unsigned int type, bool clamped, int stride, void* offset);

	protected:
		virtual void AddMesh(Mesh& mesh) override;

	private:
		int count;
		int size;
		int indexCount;
		int indexSize;

		std::vector<const Mesh*> meshes;
		std::vector<int> counts;
		std::vector<int> sizes;
		std::vector<int> indexCounts;
		std::vector<int> indexSizes;

		void SetVertexData(const void* vertexData, int size);
		void SetIndexData(const unsigned int* indexData, int size);
	};
}

