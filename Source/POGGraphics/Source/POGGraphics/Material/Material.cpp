#include "POGGraphicsPCH.h"
#include "Material.h"

#include "POGLog.h"

namespace POG::Graphics
{
	Material::Material()
		: shader(nullptr)
		, colours()
	{
	}

	Material::~Material()
	{
	}

	void Material::UpdateShaderUniforms()
	{
		for (auto const& pair : GetColours())
		{
			GetShader().Set4f(pair.first.c_str(), pair.second.r, pair.second.g, pair.second.b, pair.second.a);
		}
	}

	void Material::SetShader(std::shared_ptr<Shader> shader)
	{
		this->shader = shader;
	}

	void Material::AddColour(std::string name, Maths::Vec4 colour)
	{
		std::map<std::string, Maths::Vec4>::iterator it = colours.find(name);

		if (it != colours.end())
		{
			POG_WARN("Colour not added!. Already added the colour \"{0}\" to the material \"{1}\".", name, this->name);
			return;
		}

		colours.emplace(name, colour);
	}

	void Material::SetColour(std::string name, Maths::Vec4 colour)
	{
		try
		{
			colours.at(name) = colour;
		}
		catch (std::exception ex)
		{
			POG_WARN("Colour not set! The colour \"{0}\" does not exist for the material \"{1}\".", name, this->name);
		}
	}
}
