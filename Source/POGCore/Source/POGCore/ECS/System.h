#pragma once

#include "Common.h"

namespace POG::Core
{
	class ECSManager;

	class System
	{
	public:
		System(ECSManager& ecsManager)
			: ecsManager(ecsManager)
		{
		}

		// The set of entity ids that this system relates to
		std::set<EntityId> entityIds;

	protected:
		// A reference to the ecs manager this system is a part of
		ECSManager& ecsManager;
	};

	class SystemManager
	{
	public:
		template <typename T, typename... Args>
		std::shared_ptr<T> RegisterSystem(ECSManager& ecsManager, Args&&... args)
		{
			// Create a new instance of the system
			std::shared_ptr<T> system = std::make_shared<T>(ecsManager, std::forward<Args>(args)...);

			// Add this new system to the vector of active systems
			systems.push_back(system);

			// Add the signature to the vector of signatures
			systemSignatures.push_back(T::GetSignature(ecsManager));

			// Return the instance of the system back to the user
			return system;
		}

		void OnEntityDestroyed(EntityId entityId)
		{
			for (std::shared_ptr<System> system : systems)
			{
				system->entityIds.erase(entityId);
			}
		}

		void OnEntitySignatureChanged(EntityId entityId, Signature entitySignature)
		{
			// For each system/signature
			for (int i = 0; i < systems.size(); i++)
			{
				std::shared_ptr<System> system = systems[i];
				Signature& systemSignature = systemSignatures[i];

				// If the signatures match, add the entity id
				if ((systemSignature & entitySignature) == systemSignature)
				{
					system->entityIds.insert(entityId);
				}
				// Otherwise, remove the entity id
				else
				{
					system->entityIds.erase(entityId);
				}
			}
		}

	private:
		// Vector containing all active systems
		std::vector<std::shared_ptr<System>> systems;

		// Vector containing the corresponding system signatures
		std::vector<Signature> systemSignatures;
	};
}