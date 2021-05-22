#include "POGCorePCH.h"
#include "Scene.h"

namespace POG::Core
{
    void Scene::PreInit()
    {
        ecsManager.Init();

        ecsManager.RegisterComponent<AttachedCamera>();
        ecsManager.RegisterComponent<MeshRenderer>();
        ecsManager.RegisterComponent<Transform>();

        cameraUpdateViewSystem = ecsManager.RegisterSystem<CameraUpdateViewSystem>();
        meshRendererSystem = ecsManager.RegisterSystem<MeshRendererSystem>();
        transformSystem = ecsManager.RegisterSystem<TransformSystem>();
    }
}