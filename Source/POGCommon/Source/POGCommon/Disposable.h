#pragma once

namespace POG::Common
{
	class Disposable
	{
	public:
		virtual void Dispose() = 0;

		bool ShouldDispose() const { return shouldDispose; } // Should the object dispose on destruction
		void SetShouldDispose(bool dispose) { this->shouldDispose = dispose; } // Set whether the object should dispose on destruction

	protected:
		bool shouldDispose = true; // Should the object dispose on destruction
	};
}