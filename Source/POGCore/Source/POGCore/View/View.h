#pragma once

namespace POG::Core
{
	class View
	{
	public:
		View(int width = 1200, int height = 800);

		~View() = default;

		int GetWidth() const { return width; }
		void SetWidth(int width) { this->width = width; }

		int GetHeight() const { return height; }
		void SetHeight(int height) { this->height = height; }

		void SetDimensions(int width, int height) { SetWidth(width); SetHeight(height); }

	private:
		int width, height;
	};
}
