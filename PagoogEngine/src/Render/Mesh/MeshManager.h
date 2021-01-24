#pragma once

#include <unordered_map>

#include "Mesh.h"
#include "MeshSet.h"
#include "StaticMeshSet.h"

namespace PEngine
{
	class MeshManager
	{
	public:
		MeshManager();
		~MeshManager();

		Shared<Mesh> FindMesh(std::string name);
		Shared<Mesh> CreateMesh();
		Shared<Mesh> CreateAndAddMesh(std::string name);
		void AddMesh(std::string name, Shared<Mesh> mesh);

	private:
		std::unordered_map<std::string, Shared<Mesh>> meshes;
	};
}

