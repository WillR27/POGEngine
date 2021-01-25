#pragma once

#include <unordered_map>

#include "Mesh.h"
#include "MeshSet.h"

namespace PEngine
{
	class MeshManager
	{
	public:
		MeshManager();
		~MeshManager();

		// Finds the mesh with the given name. If none are found, returns a nullptr.
		Shared<Mesh> FindMesh(std::string name);
		// Creates a new shared pointer to a mesh.
		Shared<Mesh> CreateMesh();
		// Creates a new shared pointer to a mesh and adds it to the mesh manager.
		Shared<Mesh> CreateAndAddMesh(std::string name);
		// Adds the given mesh to the mesh manager.
		void AddMesh(std::string name, Shared<Mesh> mesh);
		// Removes the mesh with the given name from the mesh manager.
		void RemoveMesh(std::string name);

		// Finds the mesh set with the given name. If none are found, returns a nullptr.
		Shared<MeshSet> FindMeshSet(std::string name);
		// Creates a new shared pointer to a mesh set.
		Shared<MeshSet> CreateMeshSet();
		// Creates a new shared pointer to a mesh set and adds it to the mesh manager.
		Shared<MeshSet> CreateAndAddMeshSet(std::string name);
		// Adds the given mesh set to the mesh manager.
		void AddMeshSet(std::string name, Shared<MeshSet> mesh);
		// Removes the mesh set with the given name from the mesh manager.
		void RemoveMeshSet(std::string name);

	private:
		std::unordered_map<std::string, Shared<Mesh>> meshes;
		std::unordered_map<std::string, Shared<MeshSet>> meshSets;
	};
}

