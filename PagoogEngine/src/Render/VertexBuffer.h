#pragma once

namespace PEngine
{
	class VertexBuffer
	{
	public:
		VertexBuffer();
		~VertexBuffer();

		void Bind();
		void Unbind();

		void SetVertexData(const void* vertexData, unsigned int size);

	private:
		unsigned int vbo;
	};
}

