#include "POGCorePCH.h"
#include "Scene.h"

namespace POG::Core
{
    void Scene::PreInit()
    {
        ecsManager.Init();

        ecsManager.RegisterComponent<MeshRenderer>();
        ecsManager.RegisterComponent<Transform>();

        meshRendererSystem = ecsManager.RegisterSystem<MeshRendererSystem>();
        transformSystem = ecsManager.RegisterSystem<TransformSystem>();
    }
}