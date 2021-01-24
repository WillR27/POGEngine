#pragma once

#include "Material.h"

namespace PEngine
{
	class MaterialManager
	{
	public:
		MaterialManager();
		~MaterialManager();

		Shared<Material> FindMaterial(std::string name);
		Shared<Material> CreateMaterial();
		Shared<Material> CreateAndAddMaterial(std::string name);
		void AddMaterial(std::string name, Shared<Material> material);

	private:
		std::unordered_map<std::string, Shared<Material>> materials;
	};
}

