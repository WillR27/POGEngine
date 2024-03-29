#pragma once

namespace POG::Common
{
	class Disposable
	{
	public:
		virtual void Dispose() = 0;
	};

	class SharedObject
	{
	public:
		SharedObject();
		SharedObject(const SharedObject& sharedObject);
		SharedObject(SharedObject&&) = delete;

		virtual ~SharedObject();

		SharedObject& operator=(const SharedObject& sharedObject);

		int GetRefCount() const { return *refCount; }

	private:
		int* refCount;
	};
}