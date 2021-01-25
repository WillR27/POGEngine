#include "pgepch.h"
#include "MeshManager.h"

namespace PEngine
{
	MeshManager::MeshManager()
	{
	}

	MeshManager::~MeshManager()
	{
	}

	Shared<Mesh> MeshManager::FindMesh(std::string name)
	{
		try
		{
			return meshes.at(name);
		}
		catch (std::exception ex)
		{
			PG_WARN("Mesh \"{0}\" does not exist!", name);
			return Shared<Mesh>(nullptr);
		}
	}

	Shared<Mesh> MeshManager::CreateMesh()
	{
		return MakeShared<Mesh>();
	}

	Shared<Mesh> MeshManager::CreateAndAddMesh(std::string name)
	{
		Shared<Mesh> mesh = CreateMesh();

		AddMesh(name, mesh);

		return mesh;
	}

	void MeshManager::AddMesh(std::string name, Shared<Mesh> mesh)
	{
		try
		{
			// Check the mesh doesn't already exist
			// If it does, warn the user that it is being replaced
			Shared<Mesh> mesh = meshes.at(name);
			PG_WARN("Replacing mesh \"{0}\"!", name);
		}
		catch (std::exception ex)
		{	
		}

		// Either way set the mesh
		meshes[name] = mesh;
	}

	void MeshManager::RemoveMesh(std::string name)
	{
		size_t numberRemoved = meshes.erase(name);

		PG_VERIFY(numberRemoved > 0, "Tried to remove mesh \"{0}\" from the mesh manager but it did not exist!", name);
	}

	Shared<MeshSet> MeshManager::FindMeshSet(std::string name)
	{
		try
		{
			return meshSets.at(name);
		}
		catch (std::exception ex)
		{
			PG_WARN("Mesh set \"{0}\" does not exist!", name);
			return Shared<MeshSet>(nullptr);
		}
	}

	Shared<MeshSet> MeshManager::CreateMeshSet()
	{
		return MakeShared<MeshSet>();
	}

	Shared<MeshSet> MeshManager::CreateAndAddMeshSet(std::string name)
	{
		Shared<MeshSet> meshSet = CreateMeshSet();

		AddMeshSet(name, meshSet);

		return meshSet;
	}

	void MeshManager::AddMeshSet(std::string name, Shared<MeshSet> meshSet)
	{
		try
		{
			// Check the mesh set doesn't already exist
			// If it does, warn the user that it is being replaced
			Shared<MeshSet> meshSet = meshSets.at(name);
			PG_WARN("Replacing mesh set \"{0}\"!", name);
		}
		catch (std::exception ex)
		{
		}

		// Either way set the mesh set
		meshSets[name] = meshSet;
	}

	void MeshManager::RemoveMeshSet(std::string name)
	{
		size_t numberRemoved = meshSets.erase(name);

		PG_VERIFY(numberRemoved > 0, "Tried to remove mesh set \"{0}\" from the mesh manager but it did not exist!", name);
	}
}