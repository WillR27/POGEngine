#include "pgepch.h"
#include "MaterialManager.h"

namespace PEngine
{
	MaterialManager::MaterialManager()
	{
	}

	MaterialManager::~MaterialManager()
	{
	}

	Shared<Material> MaterialManager::FindMaterial(std::string name)
	{
		try
		{
			return materials.at(name);
		}
		catch (std::exception ex)
		{
			PG_WARN("Material \"{0}\" does not exist!", name);
			return Shared<Material>(nullptr);
		}
	}

	Shared<Material> MaterialManager::CreateMaterial()
	{
		return MakeShared<Material>();
	}

	Shared<Material> MaterialManager::CreateAndAddMaterial(std::string name)
	{
		Shared<Material> material = CreateMaterial();

		AddMaterial(name, material);

		return material;
	}

	void MaterialManager::AddMaterial(std::string name, Shared<Material> material)
	{
		try
		{
			// Check the material doesn't already exist
			// If it does, warn the user that it is being replaced
			Shared<Material> mesh = materials.at(name);
			PG_WARN("Replacing material \"{0}\"!", name);
		}
		catch (std::exception ex)
		{
		}

		// Either way set the material
		materials[name] = material;
	}
}