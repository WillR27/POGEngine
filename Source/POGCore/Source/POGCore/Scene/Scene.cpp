#include "POGCorePCH.h"
#include "Scene.h"

namespace POG::Core
{
    void Scene::PreInit()
    {
        ecsManager.Init();

        ecsManager.RegisterComponent<Transform>();

        transformSystem = ecsManager.RegisterSystem<TransformSystem>();
    }
}