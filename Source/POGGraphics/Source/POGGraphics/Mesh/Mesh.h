#pragma once

#include "POGDebug.h"
#include "POGLog.h"

#include "POGGraphics/Graphics.h"
#include "POGGraphics/Objects/IndexBuffer.h"
#include "POGGraphics/Objects/VertexArray.h"
#include "POGGraphics/Objects/VertexBuffer.h"

#include "MeshDataTypes.h"

namespace POG::Graphics
{
	class Mesh
	{
		friend class MeshSet;

	public:
		Mesh();
		Mesh(const Mesh&) = delete;
		Mesh(Mesh&&) = delete;

		~Mesh();

		//void* operator new(size_t size) { return ::new Mesh(); }
		//void* operator new[](size_t size) = delete;
		//void operator delete(void* mesh) { ::delete mesh; }
		//void operator delete[](void* mesh) = delete;

		void Render();

		void Build();
		const void* GetVertexData() const { return vertexDataArray; }

		void SetAttributeData(int index, const void* dataToCopy, int size, int count, int stride, const char* debugName);

		template<typename T>
		void AddAttribute(const T* dataToCopy, int size, int count, const char* debugName = "")
		{
			SetAttribute(static_cast<int>(attributeData.size()), dataToCopy, size, count, debugName);
		}

		template<typename T>
		void SetAttribute(int index, const T* dataToCopy, int size, int count, const char* debugName = "")
		{
			POG_ERROR("The type specified is not supported for meshes.");
		}

		template<>
		void SetAttribute<float>(int index, const float* dataToCopy, int size, int count, const char* debugName)
		{
			SetAttributeData(index, dataToCopy, size, count, sizeof(float) * count, debugName);

			attributeTypes[index] = POG_FLOAT;
		}

		template<>
		void SetAttribute<unsigned int>(int index, const unsigned int* dataToCopy, int size, int count, const char* debugName)
		{
			SetAttributeData(index, dataToCopy, size, count, sizeof(unsigned int) * count, debugName);

			attributeTypes[index] = POG_UNSIGNED_INT_10F_11F_11F_REV;
		}

		const unsigned int* GetIndexData() const { return indexDataArray; }
		void SetIndexData(const unsigned int* indexDataToBeCopied, int size);

		void SetNumberOfVerices(int numberOfVertices) { this->numberOfVertices = numberOfVertices; }

		// Returns the number of vertices in the mesh.
		int VertexCount() const { return numberOfVertices; }
		// Returns the size of the vertex array in bytes.
		int VertexArraySize() const { return numberOfVertices * stride; }

		// Returns the number of indices in the mesh.
		int IndexCount() const { return numberOfIndices; }
		// Returns the size of the index array in bytes.
		int IndexSize() const { return IndexCount() * sizeof(unsigned int); }

		// Returns whether or not the mesh is currently part of a mesh set.
		//bool HasMeshSet() const { return meshSet != nullptr; }

	private:
		VertexArray* vao;
		VertexBuffer* vbo;
		IndexBuffer* ibo;

		// The stride of each vertex in bytes, i.e sizeof(position) + sizeof(colour) + sizeof(...).
		int stride;

		int numberOfVertices;
		int numberOfIndices;

		void* vertexDataArray;

		std::vector<char*> attributeData;
		std::vector<int> attributeCounts;
		std::vector<int> attributeStrides;
		std::vector<unsigned int> attributeTypes;
		std::vector<const char*> attributeDebugNames;

		unsigned int* indexDataArray;

		//MeshSet* meshSet;

		// TODO: Replace with something that isn't this
		static constexpr int SizeOf(unsigned int type)
		{
			switch (type)
			{
			case POG_FLOAT:
				return sizeof(float);
				break;
			case POG_UNSIGNED_INT_2_10_10_10_REV:
				return sizeof(unsigned int);
				break;
			default:
				break;
			}
		}
	};
}