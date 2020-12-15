#include "pgepch.h"
#include "Material.h"

namespace PEngine
{
	Material::Material(std::string name)
		: name(name)
		, shader(nullptr)
		, colours()
	{
	}

	Material::~Material()
	{
	}

	void Material::UpdateShaderUniforms()
	{
		GetShader().Use();

		for (auto const& pair : GetColours())
		{
			GetShader().Set4f(pair.first.c_str(), pair.second.r, pair.second.g, pair.second.b, pair.second.a);
		}
	}

	Shader& Material::GetShader() const
	{
		return *shader;
	}

	void Material::SetShader(Shader& shader)
	{
		this->shader = &shader;
	}

	const std::map<std::string, Vec4> Material::GetColours() const
	{
		return colours;
	}

	void Material::AddColour(std::string name, Vec4 colour)
	{
		std::map<std::string, Vec4>::iterator it = colours.find(name);

		if (it != colours.end())
		{
			PG_WARN("Colour not added!. Already added the colour \"{0}\" to the material \"{1}\".", name, this->name);
			return;
		}

		colours.emplace(name, colour);
	}

	void Material::SetColour(std::string name, Vec4 colour)
	{
		try
		{
			colours.at(name) = colour;
		}
		catch (std::exception ex)
		{
			PG_WARN("Colour not set! The colour \"{0}\" does not exist for the material \"{1}\".", name, this->name);
		}
	}
}