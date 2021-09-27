#pragma once

#include <functional>

namespace POG::Util
{
	///////////////////////////////////////////////////////////////////////////////////
	// FUNCTORS

	template<typename>
	class Functor;

	template<typename R, typename... Args>
	class Functor<R(Args...)>
	{
	public:
		virtual ~Functor() = default;

		virtual R operator()(Args... args) = 0;

		virtual bool Equals(const Functor<R(Args...)>& functor) = 0;
	};

	template<typename>
	class LambdaFunctor;

	template<typename R, typename... Args>
	class LambdaFunctor<R(Args...)> final : public Functor<R(Args...)>
	{
	private:
		using Func = std::function<R(Args...)>;

	public:
		LambdaFunctor(Func func)
			: func(func)
		{
		}

		R operator()(Args... args) override
		{
			return func(std::forward<Args>(args)...);
		}

		bool Equals(const Functor<R(Args...)>& functor) override
		{
			return false; // TODO: Any way to compare lambdas? Signature?
		}

	private:
		Func func;
	};

	template<typename>
	class FreeFunctor;

	template<typename R, typename... Args>
	class FreeFunctor<R(Args...)> final : public Functor<R(Args...)>
	{
	private:
		using Func = R(*)(Args...);

	public:
		FreeFunctor(Func func)
			: func(func)
		{
		}

		R operator()(Args... args) override
		{
			return (*func)(std::forward<Args>(args)...);
		}

		bool Equals(const Functor<R(Args...)>& functor) override
		{
			try
			{
				const FreeFunctor& freeFunctor = dynamic_cast<const FreeFunctor&>(functor);

				return &freeFunctor != nullptr && func == freeFunctor.func;
			}
			catch (...)
			{
				return false;
			}
		}

	private:
		Func func;
	};

	template<typename>
	class MemberFunctor;

	template<class T, typename R, typename... Args>
	class MemberFunctor<R(T::*)(Args...)> final : public Functor<R(Args...)>
	{
	private:
		using Func = R(T::*)(Args...);

	public:
		MemberFunctor(Func func, T* obj)
			: func(func)
			, obj(obj)
		{
		}

		R operator()(Args... args) override
		{
			return (obj->*func)(std::forward<Args>(args)...);
		}

		bool Equals(const Functor<R(Args...)>& functor) override
		{
			try
			{
				const MemberFunctor& memberFunctor = dynamic_cast<const MemberFunctor&>(functor);

				return &memberFunctor != nullptr && func == memberFunctor.func && obj == memberFunctor.obj;
			}
			catch (...)
			{
				return false;
			}
		}

	private:
		Func func;
		T* obj;
	};

	// FUNCTORS
	///////////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////////
	// FUNCTION

	class FunctionBase
	{
	public:

	};

	template<typename>
	class Function;

	template<typename R, typename... Args>
	class Function<R(Args...)> final
	{
	public:
		Function()
			: functor(nullptr)
		{
		}

		Function(std::function<R(Args...)> func)
			: functor(nullptr)
		{
			Reset(func);
		}

		Function(R(*func)(Args...))
			: functor(nullptr)
		{
			Reset(func);
		}

		template<class T>
		Function(R(T::*func)(Args...), T* obj)
			: functor(nullptr)
		{
			Reset(func, obj);
		}

		void Reset(std::function<R(Args...)> func)
		{
			functor.reset(new LambdaFunctor<R(Args...)>(func));
		}

		void Reset(R(*func)(Args...))
		{
			functor.reset(new FreeFunctor<R(Args...)>(func));
		}

		template<class T>
		void Reset(R(T::*func)(Args...), T* obj)
		{
			functor.reset(new MemberFunctor<R(T::*)(Args...)>(func, obj));
		}

		R operator()(Args... args)
		{
			return functor->operator()(std::forward<Args>(args)...);
		}

		bool Equals(const Function<R(Args...)>& function)
		{
			Functor<R(Args...)>* self = functor.get();
			Functor<R(Args...)>* target = function.functor.get();

			return (self == nullptr && target == nullptr) || (self->Equals(*target));
		}

	private:
		std::shared_ptr<Functor<R(Args...)>> functor;
	};

	// FUNCTION
	///////////////////////////////////////////////////////////////////////////////////
}