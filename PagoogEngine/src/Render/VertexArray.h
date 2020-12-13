#pragma once

namespace PEngine
{
	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();

		void Bind();
		void Unbind();

		void SetAttribute(int index, int numberOfComponents, unsigned int type, bool clamped, int stride, void* offset);

	private:
		unsigned int vao;
	};
}

