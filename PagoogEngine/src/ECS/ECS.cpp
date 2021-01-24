#include "pgepch.h"
#include "ECS.h"

#include "Scene/Scene.h"

namespace PEngine
{
    MeshManager& Entity::GetMeshManager()
    {
        return GetScene().GetMeshManager(); 
    }

    MaterialManager& Entity::GetMaterialManager()
    {
        return GetScene().GetMaterialManager();
    }

    ShaderManager& Entity::GetShaderManager()
    {
        return GetScene().GetShaderManager();
    }
}