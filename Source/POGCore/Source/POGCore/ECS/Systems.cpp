#include "POGCorePCH.h"
#include "Systems.h"

namespace POG::Core
{
	Signature CameraUpdateViewSystem::GetSignature(ECSManager& ecsManager)
	{
		Signature signature;
		signature.set(ecsManager.GetComponentTypeId<Transform>());
		signature.set(ecsManager.GetComponentTypeId<AttachedCamera>());
		return signature;
	}

	void CameraUpdateViewSystem::UpdateView()
	{
		for (EntityId entityId : entityIds)
		{
			auto& transform = ecsManager.GetComponent<Transform>(entityId);
			auto& camera = ecsManager.GetComponent<AttachedCamera>(entityId);

			camera.camera->UpdateView(transform.position, transform.orientation);
		}
	}


	Signature MeshRendererSystem::GetSignature(ECSManager& ecsManager)
	{
		Signature signature;
		signature.set(ecsManager.GetComponentTypeId<Transform>());
		signature.set(ecsManager.GetComponentTypeId<MeshRenderer>());
		return signature;
	}

	void MeshRendererSystem::Frame(float alpha)
	{
		for (EntityId entityId : entityIds)
		{
			auto& meshRenderer = ecsManager.GetComponent<MeshRenderer>(entityId);
			auto& transform = ecsManager.GetComponent<Transform>(entityId);

			Render::Material& material = *meshRenderer.material;
			material.GetShader().Use();
			material.UpdateShaderUniforms();

			Maths::Vec3 position = Maths::Lerp(transform.prevPosition, transform.position, alpha);
			Maths::Quat orientation = Maths::Lerp(transform.prevOrientation, transform.orientation, alpha);
			Maths::Vec3 scale = Maths::Lerp(transform.prevScale, transform.scale, alpha);
			orientation.w *= -1.0f; // Invert model matrix rotation axes

			Render::Shader& shader = material.GetShader();
			shader.SetMatrix4fv("view", 1, false, Maths::ToData(Render::Camera::MainCamera->GetView()));
			shader.SetMatrix4fv("projection", 1, false, Maths::ToData(Render::Camera::MainCamera->GetProjection()));
			shader.SetMatrix4fv("model", 1, false, Maths::ToData(Maths::ToModelMatrix(position, orientation, scale)));

			meshRenderer.mesh->Render();
		}
	}

	Signature PhysicsSystem::GetSignature(ECSManager& ecsManager)
	{
		Signature signature;
		signature.set(ecsManager.GetComponentTypeId<Transform>());
		signature.set(ecsManager.GetComponentTypeId<RigidBody>());
		return signature;
	}

	void PhysicsSystem::Update(float dt)
	{
		for (EntityId entityId : entityIds)
		{
			auto& transform = ecsManager.GetComponent<Transform>(entityId);
			auto& rigidBody = ecsManager.GetComponent<RigidBody>(entityId);

			Maths::Vec3 drag = rigidBody.dragCoef * Maths::Vec3MultiplyPreserveSigns(rigidBody.velocity, rigidBody.velocity);
			Maths::Vec3 acceleration = (rigidBody.force - drag) / rigidBody.mass;

			rigidBody.velocity += acceleration * dt;
			rigidBody.velocity.y = abs(rigidBody.velocity.y) > 0.001f ? rigidBody.velocity.y : 0.0f;
			rigidBody.velocity.z = abs(rigidBody.velocity.z) > 0.001f ? rigidBody.velocity.z : 0.0f;
			rigidBody.velocity.x = abs(rigidBody.velocity.x) > 0.001f ? rigidBody.velocity.x : 0.0f;

			transform.position += rigidBody.velocity * dt;
		}
	}

	Signature SpriteRendererSystem::GetSignature(ECSManager& ecsManager)
	{
		Signature signature;
		signature.set(ecsManager.GetComponentTypeId<Sprite>());
		signature.set(ecsManager.GetComponentTypeId<Transform>());
		return signature;
	}

	void SpriteRendererSystem::Frame(float alpha)
	{
		for (EntityId entityId : entityIds)
		{
			auto& sprite = ecsManager.GetComponent<Sprite>(entityId);
			auto& transform = ecsManager.GetComponent<Transform>(entityId);

			float width = sprite.texture->GetWidth() / 100.0f;
			float height = sprite.texture->GetHeight() / 100.0f;

			const float spritePositions[] =
			{
				0.5f,  0.5f, 0.0f,
				0.5f, -0.5f, 0.0f,
				-0.5f, -0.5f, 0.0f,
				-0.5f,  0.5f, 0.0f
			};

			float spriteColours[] =
			{
				0.0f, 0.0f, 1.0f,
				1.0f, 0.0f, 1.0f,
				0.0f, 1.0f, 0.0f,
				1.0f, 1.0f, 1.0f
			};

			float spriteTexCoords[] =
			{
				1.0f, 1.0f,
				1.0f, 0.0f,
				0.0f, 0.0f,
				0.0f, 1.0f,
			};

			const unsigned int spriteIndices[] =
			{
				0, 1, 3,
				1, 2, 3
			};

			Render::Mesh mesh;
			mesh.SetNumberOfVerices(4);
			mesh.AddAttribute<float>(spritePositions, sizeof(spritePositions), 3);
			mesh.AddAttribute<float>(spriteColours, sizeof(spriteColours), 3);
			mesh.AddAttribute<float>(spriteTexCoords, sizeof(spriteTexCoords), 2);
			mesh.SetIndexData(spriteIndices, sizeof(spriteIndices));
			mesh.Build();

			Render::Shader shader = Render::Shader();
			const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColour;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 colour;
out vec2 texCoord;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
	colour  = aColour;
	texCoord = aTexCoord;
}
)";

			const char* fragmentShaderSource = R"(
#version 330 core
in vec3 colour;
in vec2 texCoord;

uniform sampler2D textureSample;

out vec4 FragColor;

void main()
{
	FragColor = texture(textureSample, texCoord);
} 
)";
			shader.Init(vertexShaderSource, fragmentShaderSource);

			Maths::Vec3 position = Maths::Lerp(transform.prevPosition, transform.position, alpha);
			Maths::Quat orientation = Maths::Lerp(transform.prevOrientation, transform.orientation, alpha);
			Maths::Vec3 scale = Maths::Lerp(transform.prevScale, transform.scale, alpha);
			orientation.w *= -1.0f; // Invert model matrix rotation axes

			sprite.texture->Bind();
			shader.Use();
			shader.SetMatrix4fv("view", 1, false, Maths::ToData(Render::Camera::MainCamera->GetView()));
			shader.SetMatrix4fv("projection", 1, false, Maths::ToData(Render::Camera::MainCamera->GetProjection()));
			shader.SetMatrix4fv("model", 1, false, Maths::ToData(Maths::ToModelMatrix(position, orientation, scale)));

			mesh.Render();
		}
	}

	Signature TransformSystem::GetSignature(ECSManager& ecsManager)
	{
		Signature signature;
		signature.set(ecsManager.GetComponentTypeId<Transform>());
		return signature;
	}

	void TransformSystem::Update(float dt)
	{
		for (EntityId entityId : entityIds)
		{
			Transform& transform = ecsManager.GetComponent<Transform>(entityId);
			transform.prevPosition = transform.position;
			transform.prevOrientation = transform.orientation;
			transform.prevScale = transform.scale;
		}
	}
}