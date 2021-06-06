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

		const float spritePositions[] =
		{
			0.5f,  0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			-0.5f, -0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		float spriteTexCoords[] =
		{
			1.0f, 1.0f,
			1.0f, 0.0f,
			0.0f, 0.0f,
			0.0f, 1.0f,
		};

		const unsigned int spriteIndices[] =
		{
			0, 1, 3,
			1, 2, 3
		};

		Render::Mesh& spriteMesh = defaultMeshManager->CreateMesh("Sprite Mesh");
		spriteMesh.SetNumberOfVerices(4);
		spriteMesh.AddAttribute(spritePositions, sizeof(spritePositions), 3);
		spriteMesh.AddAttribute(spriteTexCoords, sizeof(spriteTexCoords), 2);
		spriteMesh.SetIndexData(spriteIndices, sizeof(spriteIndices));
		spriteMesh.Build();

		Render::Mesh& wireframeMesh = defaultMeshManager->CreateMesh("Wireframe Mesh");
		wireframeMesh.SetNumberOfVerices(4);
		wireframeMesh.AddAttribute(spritePositions, sizeof(spritePositions), 3);
		wireframeMesh.SetIndexData(spriteIndices, sizeof(spriteIndices));
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

	Render::Mesh& MeshManager::CreateMesh(const char* name)
	{
		Render::Mesh* newMesh = new Render::Mesh();
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