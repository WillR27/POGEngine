#include "POGCorePCH.h"
#include "Scene.h"

namespace POG::Core
{
    std::shared_ptr<Scene> Scene::ActiveScene = std::make_shared<Scene>();

    Scene& Scene::GetActiveScene()
    {
        return *ActiveScene;
    }

    void Scene::SetActiveScene(std::shared_ptr<Scene> scene)
    {
        ActiveScene = scene;
    }

    void Scene::PreInit()
    {
        ecsManager.Init();

        ecsManager.RegisterComponent<AttachedCamera>();
        ecsManager.RegisterComponent<MeshRenderer>();
        ecsManager.RegisterComponent<RigidBody>();
        ecsManager.RegisterComponent<Sprite>();
        ecsManager.RegisterComponent<Transform>();

        // Colliders
        ecsManager.RegisterComponent<BoxCollider2D>();
        ecsManager.RegisterComponent<RectCollider>();

        cameraUpdateViewSystem = ecsManager.RegisterSystem<CameraUpdateViewSystem>();
        meshRendererSystem = ecsManager.RegisterSystem<MeshRendererSystem>();
        physicsSystem = ecsManager.RegisterSystem<PhysicsSystem>();
        spriteRectColliderRendererSystem = ecsManager.RegisterSystem<SpriteRectColliderRendererSystem>();
        spriteRendererSystem = ecsManager.RegisterSystem<SpriteRendererSystem>();
        transformSystem = ecsManager.RegisterSystem<TransformSystem>();
    }

    void Scene::Init()
    {
    }

    void Scene::PostInit()
    {
    }

    void Scene::Exit()
    {
    }

    void Scene::Input(InputPackage& inputPackage, float dt)
    {
        // Leave empty
    }

    void Scene::PreUpdate(float dt)
    {
    }

    void Scene::Update(float dt)
    {
        // Leave empty
    }

    void Scene::PostUpdate(float dt)
    {
        GetPhysicsSystem().Update(dt);
        GetTransformSystem().Update(dt);
        GetCameraUpdateViewSystem().UpdateView();
    }

    void Scene::PreFrame(float alpha)
    {
    }

    void Scene::Frame(float alpha)
    {
        // Leave empty
    }

    void Scene::PostFrame(float alpha)
    {
        GetMeshRendererSystem().Frame(alpha);
        GetSpriteRendererSystem().Frame(alpha);
        GetSpriteRectColliderRendererSystem().Frame(alpha);
    }
}