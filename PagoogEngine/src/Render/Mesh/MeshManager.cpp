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
}