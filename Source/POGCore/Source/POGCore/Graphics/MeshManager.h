#pragma once

#include "POGGraphics.h"

namespace POG::Core
{
	class MeshManager
	{
	public:
		static void Init();

		static Graphics::Mesh& CreateGlobalMesh(const char* name) { return globalMeshManager->CreateMesh(name); }
		static void DestroyGlobalMesh(const char* name) { globalMeshManager->DestroyMesh(name); }

		static Graphics::Mesh& GetGlobalMesh(const char* name) { return globalMeshManager->GetMesh(name); }

		static Graphics::Mesh& GetDefaultMesh(const char* name) { return defaultMeshManager->GetMesh(name); }

		MeshManager();

		virtual ~MeshManager();

		Graphics::Mesh& CreateMesh(const char* name);
		void DestroyMesh(const char* name);

		Graphics::Mesh& GetMesh(const char* name) { return *meshes[name]; }

	private:
		static std::unique_ptr<MeshManager> globalMeshManager;
		static std::unique_ptr<MeshManager> defaultMeshManager;

		std::map<const char*, Graphics::Mesh*> meshes;
	};
}

