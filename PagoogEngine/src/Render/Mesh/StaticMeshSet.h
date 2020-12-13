#pragma once

#include "MeshSet.h"

namespace PEngine
{
	class StaticMeshSet : public MeshSet
	{
	public:
		StaticMeshSet();
		~StaticMeshSet();

		virtual void Build() override;

		virtual void AddMesh(const Mesh& mesh) override;

		virtual void RenderMesh(const Mesh& mesh) override;

	private:
		unsigned int count;
		unsigned int length;
		unsigned int size;
		unsigned int indexLength;
		unsigned int indexSize;

		std::vector<const Mesh*> meshes;
		std::vector<unsigned int> countOffsets;
		std::vector<unsigned int> lengthOffsets;
		std::vector<unsigned int> sizeOffsets;
		std::vector<unsigned int> indexLengthOffsets;
		std::vector<unsigned int> indexSizeOffsets;

		void SetVertexData(const float* vertexData, unsigned int size);
		void SetIndexData(const unsigned int* indexData, unsigned int size);
	};
}

