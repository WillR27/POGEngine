#include "POGCorePCH.h"
#include "MeshManager.h"

namespace POG::Core
{
	std::unique_ptr<MeshManager> MeshManager::defaultMeshManager(nullptr);

	void MeshManager::Init()
	{
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

		Render::Mesh& mesh = defaultMeshManager->CreateMesh("Sprite Mesh");
		mesh.SetNumberOfVerices(4);
		mesh.AddAttribute(spritePositions, sizeof(spritePositions), 3);
		mesh.AddAttribute(spriteTexCoords, sizeof(spriteTexCoords), 2);
		mesh.SetIndexData(spriteIndices, sizeof(spriteIndices));
		mesh.Build();
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
		delete meshes[name];
		meshes.erase(name);
	}
}