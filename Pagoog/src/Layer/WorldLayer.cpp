#include "pgpch.h"
#include "WorldLayer.h"

#include "Game/Camera.h"
#include "Render/Mesh/StaticMeshSet.h"
#include "Render/Mesh/Primitives/Primitives.h"

namespace Pagoog
{
	WorldLayer::WorldLayer()
		: Layer::Layer("World")
		, mesh()
		, mesh2()
		, mesh3()
		, mesh4()
		, meshSet()
		, meshSet2()
		, meshSet3()
		, meshSet4()
		, material1("Material1")
		, block()
	{
	}

	WorldLayer::~WorldLayer()
	{
	}

	void WorldLayer::Init()
	{
		Render::SetPolygonMode(PG_FRONT_AND_BACK, PG_FILL);

		mesh.SetPositionData(squarePositions, sizeof(squarePositions));
		mesh.SetColourData(squareColours, sizeof(squareColours));
		mesh.Build();

		mesh2.SetPositionData(cubePositions2, sizeof(cubePositions2));
		mesh2.SetColourData(cubeColours2, sizeof(cubeColours2));
		mesh2.Build();

		mesh3.SetPositionData(squarePositions2, sizeof(squarePositions2));
		mesh3.SetColourData(squareColours2, sizeof(squareColours2));
		mesh3.SetIndexData(squareIndices2, sizeof(squareIndices2));
		mesh3.Build();

		mesh4.SetPositionData(cubePositions3, sizeof(cubePositions3));
		mesh4.SetColourData(cubeColours3, sizeof(cubeColours3));
		mesh4.SetIndexData(cubeIndices3, sizeof(cubeIndices3));
		mesh4.Build();

		meshSet.AddMesh(mesh);
		meshSet.Build();
		meshSet.SetAttribute(0, 3, PG_FLOAT, false, 6 * sizeof(float), (void*)(0));
		meshSet.SetAttribute(1, 3, PG_FLOAT, false, 6 * sizeof(float), (void*)(3 * sizeof(float)));

		meshSet2.AddMesh(mesh2);
		meshSet2.Build();
		meshSet2.SetAttribute(0, 3, PG_FLOAT, false, 6 * sizeof(float), (void*)(0));
		meshSet2.SetAttribute(1, 3, PG_FLOAT, false, 6 * sizeof(float), (void*)(3 * sizeof(float)));

		meshSet3.AddMesh(mesh3);
		meshSet3.Build();
		meshSet3.SetAttribute(0, 3, PG_FLOAT, false, 6 * sizeof(float), (void*)(0));
		meshSet3.SetAttribute(1, 3, PG_FLOAT, false, 6 * sizeof(float), (void*)(3 * sizeof(float)));

		meshSet4.AddMesh(mesh4);
		meshSet4.Build();
		meshSet4.SetAttribute(0, 3, PG_FLOAT, false, 6 * sizeof(float), (void*)(0));
		meshSet4.SetAttribute(1, 3, PG_FLOAT, false, 6 * sizeof(float), (void*)(3 * sizeof(float)));

		const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColour;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec4 colourIn;

out vec3 colour;

void main()
{
	colour = vec3(colourIn.r, colourIn.g, colourIn.b);
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
)";

		const char* fragmentShaderSource = R"(
#version 330 core
in vec3 colour;

out vec4 FragColor;

void main()
{
    FragColor = vec4(colour, 1.0);
} 
)";

		shader.Init(vertexShaderSource, fragmentShaderSource);

		material1.AddColour("colourIn", Vec4(1.0f, 0.0f, 0.0f, 1.0f));
		material1.SetShader(shader);

		Camera camera(Vec3(0.0f, 0.0f, 5.0f));
		material1.GetShader().Use();
		material1.GetShader().SetMatrix4fv("view", 1, false, camera.GetView());
		material1.GetShader().SetMatrix4fv("projection", 1, false, camera.GetProjection());
		
		block.Translate(Vec3(-2.0f, -2.0f, 0.0f));
	}

	void WorldLayer::Update()
	{
		Render::EnableDepthTest(true);

		block.RotateAround(Vec3(0.0f, 0.0f, 0.0f), Quaternion(Vec3(0.0001f, 0.0002f, 0.0003f)));
		block.Rotate(Quaternion(Vec3(0.0001f, 0.0002f, 0.0003f)));

		material1.SetColour("colourIn", Vec4((float)sin(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())), 1.0f, 0.0f, 1.0f));
		material1.UpdateShaderUniforms();

		Mat4 model = Mat4(1.0f);
		model = Maths::Translate(model, block.GetPosition());
		model = Maths::Rotate(model, block.GetRotationMatrix());
		material1.GetShader().SetMatrix4fv("model", 1, false, model);

		meshSet.RenderMesh(mesh);
		//meshSet2.RenderMesh(mesh2);
		//meshSet3.RenderMesh(mesh3);
		//meshSet4.RenderMesh(mesh4);
	}
}