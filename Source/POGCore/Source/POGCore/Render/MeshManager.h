#pragma once

#include "POGRender.h"

namespace POG::Core
{
	class MeshManager
	{
	public:
		static void Init();

		static Render::Mesh& GetDefaultMesh(const char* name) { return defaultMeshManager->GetMesh(name); }

		MeshManager();

		virtual ~MeshManager();

		Render::Mesh& CreateMesh(const char* name);
		void DestroyMesh(const char* name);

		Render::Mesh& GetMesh(const char* name) { return *meshes[name]; }

	private:
		static std::unique_ptr<MeshManager> defaultMeshManager;

		std::map<const char*, Render::Mesh*> meshes;
	};
}

