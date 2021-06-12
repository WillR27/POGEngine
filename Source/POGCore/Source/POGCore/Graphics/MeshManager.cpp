#include "POGCorePCH.h"
#include "MeshManager.h"

namespace POG::Core
{
	std::unique_ptr<MeshManager> MeshManager::globalMeshManager(nullptr);
	std::unique_ptr<MeshManager> MeshManager::defaultMeshManager(nullptr);

	void MeshManager::Init()
	{
		globalMeshManager = std::make_unique<MeshManager>();
		defaultMeshManager = std::make_unique<MeshManager>();

		Graphics::Mesh& spriteMesh = defaultMeshManager->CreateMesh("Sprite Mesh");
		spriteMesh.SetNumberOfVerices(4);
		spriteMesh.AddAttribute(Graphics::Square::Positions, sizeof(Graphics::Square::Positions), 3);
		spriteMesh.AddAttribute(Graphics::Square::TexCoords, sizeof(Graphics::Square::TexCoords), 2);
		spriteMesh.SetIndexData(Graphics::Square::Indices, sizeof(Graphics::Square::Indices));
		spriteMesh.Build();

		Graphics::Mesh& wireframeMesh = defaultMeshManager->CreateMesh("Wireframe Mesh");
		wireframeMesh.SetNumberOfVerices(4);
		wireframeMesh.AddAttribute(Graphics::Square::Positions, sizeof(Graphics::Square::Positions), 3);
		wireframeMesh.SetIndexData(Graphics::Square::Indices, sizeof(Graphics::Square::Indices));
		wireframeMesh.Build();
	}

	MeshManager::MeshManager()
		: meshes()
	{
	}

	MeshManager::~MeshManager()
	{
		for (auto& pair : meshes)
		{
			delete pair.second;
		}

		meshes.clear();
	}

	Graphics::Mesh& MeshManager::CreateMesh(const char* name)
	{
		Graphics::Mesh* newMesh = new Graphics::Mesh();
		meshes[name] = newMesh;

		return *newMesh;
	}

	void MeshManager::DestroyMesh(const char* name)
	{
		if (meshes.find(name) != meshes.end())
		{
			delete meshes[name];
			meshes.erase(name);
		}
		else
		{
			POG_WARN("Tried to destroy mesh \"{0}\" that didn't exist.", name);
		}
	}
}