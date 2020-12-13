#pragma once

namespace PEngine
{
	class IndexBuffer
	{
	public:
		IndexBuffer();
		~IndexBuffer();

		void Bind();
		void Unbind();

		void SetIndexData(const void* indexData, int size);

	private:
		unsigned int ibo;
	};
}

