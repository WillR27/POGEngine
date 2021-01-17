#pragma once

#include <unordered_map>

#include "Core/Core.h"
#include "Debug/Debug.h"
#include "System.h"

namespace PEngine
{
	class SystemManager
	{
	public:
		SystemManager()
			: signatures()
			, systems()
		{
		}

		template<typename T>
		Shared<T> RegisterSystem()
		{
			const char* typeName = typeid(T).name();

			PG_ASSERT(systems.find(typeName) == systems.end(), "Registering system more than once!");

			// Create a pointer to the system and return it so it can be used externally
			auto system = MakeShared<T>();
			systems.insert({ typeName, system });

			return system;
		}

		template<typename T>
		void SetSignature(Signature signature)
		{
			const char* typeName = typeid(T).name();

			PG_ASSERT(systems.find(typeName) != systems.end(), "System used before being registered!");

			// Set the signature for this system
			signatures.insert({ typeName, signature });
		}

		void EntityDestroyed(Entity entity)
		{
			// Erase a destroyed entity from all system lists
			// mEntities is a set so no check needed
			for (auto const& pair : systems)
			{
				auto const& system = pair.second;

				system->entities.erase(entity);
			}
		}

		void EntitySignatureChanged(Entity entity, Signature entitySignature)
		{
			// Notify each system that an entity's signature changed
			for (auto const& pair : systems)
			{
				auto const& type = pair.first;
				auto const& system = pair.second;
				auto const& systemSignature = signatures[type];

				// Entity signature matches system signature - insert into set
				if ((entitySignature & systemSignature) == systemSignature)
				{
					system->entities.insert(entity);
				}
				// Entity signature does not match system signature - erase from set
				else
				{
					system->entities.erase(entity);
				}
			}
		}

	private:
		// Map from system type string pointer to a signature
		std::unordered_map<const char*, Signature> signatures;

		// Map from system type string pointer to a system pointer
		std::unordered_map<const char*, Shared<System>> systems;
	};
}

