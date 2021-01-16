#pragma once

namespace PEngine
{
	class ISafe
	{
	public:
		template <typename T>
		friend class Safe;

		ISafe()
			: exists(new bool(false))
			, refCount(new int(1))
		{
		}

		virtual ~ISafe()
		{
			(*refCount)--;
			if ((*refCount) == 0)
			{
				delete exists;
				delete refCount;
			}
		}

	protected:
		bool* exists;
		int* refCount;
	};

	template <typename T>
	class Safe
	{
		typedef typename std::enable_if<std::is_base_of<ISafe, T>::value>::type check;

	public:
		template <typename U>
		friend class Safe;

		Safe(T* iSafe = nullptr)
			: iSafe(iSafe)
			, exists(nullptr)
			, refCount(nullptr)
		{
			if (iSafe != nullptr)
			{
				exists = iSafe->exists;
				refCount = iSafe->refCount;
				(*refCount)++;
			}
			else
			{
				exists = nullptr;
				refCount = nullptr;
			}
		}

		Safe(Safe<T>& safe)
			: iSafe(safe.iSafe)
			, exists(safe.exists)
			, refCount(safe.refCount)
		{
			if (refCount != nullptr)
			{
				(*refCount)++;
			}
		}

		template <typename U>
		Safe(Safe<U>& safe)
			: iSafe(static_cast<T*>(safe.iSafe))
			, exists(safe.exists)
			, refCount(safe.refCount)
		{
			if (refCount != nullptr)
			{
				(*refCount)++;
			}
		}

		~Safe()
		{
			TryShrink();
		}

		Safe<T>& operator=(Safe<T>& safe)
		{
			TryShrink();

			iSafe = safe.iSafe;
			exists = safe.exists;
			refCount = safe.refCount;

			if (refCount != nullptr)
			{
				(*refCount)++;
			}

			return *this;
		}

		template <typename U>
		Safe<T>& operator=(Safe<U>& safe)
		{
			TryShrink();

			iSafe = static_cast<T*>(safe.iSafe);
			exists = safe.exists;
			refCount = safe.refCount;

			if (refCount != nullptr)
			{
				(*refCount)++;
			}

			return *this;
		}

		T& operator*()
		{
			return *iSafe;
		}

		T* operator->()
		{
			return iSafe;
		}

		bool Exists()
		{
			return exists != nullptr && *exists;
		}

	private:
		void TryShrink()
		{
			if (refCount != nullptr)
			{
				(*refCount)--;
				if ((*refCount) == 0)
				{
					delete exists;
					delete refCount;
				}
			}
		}

		T* iSafe;
		bool* exists;
		int* refCount;
	};
}
