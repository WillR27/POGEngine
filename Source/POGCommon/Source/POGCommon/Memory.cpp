#include "POGCommonPCH.h"
#include "Memory.h"

namespace POG::Common
{
	SharedObject::SharedObject()
		: refCount(new int(1))
	{
	}

	SharedObject::SharedObject(const SharedObject& sharedObject)
		: refCount(sharedObject.refCount)
	{
		(*refCount)++;
	}

	SharedObject::~SharedObject()
	{
		(*refCount)--;

		if (*refCount == 0)
		{
			delete refCount;
		}
	}

	SharedObject& SharedObject::operator=(const SharedObject& sharedObject)
	{
		(*refCount)--;

		if (*refCount == 0)
		{
			delete refCount;
		}

		refCount = sharedObject.refCount;

		(*refCount)++;

		return *this;
	}
}