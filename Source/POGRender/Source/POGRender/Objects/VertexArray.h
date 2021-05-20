#pragma once

#include "RenderingObject.h"

namespace POG::Render
{
	// A vao, as the name implies, contains all the state necessary to pull vertex data from memory
	// When we call any of the following, the currently bound vbo is remembered so we know what vbo goes with what attribute
	// glVertexAttribPointer, glVertexAttribIPointer, and glVertexAttribLPointer
	// An ibo will be associated with a vao if it's bound after the vao, as this has changed the state
	// When drawing, only the vao should need to be bound

	class VertexArray : public RenderingObject
	{
	public:
		VertexArray();
		VertexArray(const VertexArray&) = delete;
		VertexArray(VertexArray&&) = delete;

		~VertexArray();

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual RenderingObject* GetCurrent() override;

		void SetAttribute(unsigned int index, unsigned int numberOfComponents, unsigned int type, bool clamped, int stride, void* offset);

	private:
		static VertexArray* currentVAO;
	};
}

