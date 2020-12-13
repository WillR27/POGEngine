#pragma once

namespace PEngine
{
	class Layer
	{
	public:
		Layer(const char* name);
		virtual ~Layer() = default;

		virtual void Init() = 0;
		virtual void Update() = 0;

		const char* GetName() const;

	protected:
		const char* name;
	};
}

