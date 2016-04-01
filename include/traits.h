#pragma once

namespace Interpreter {

	//-------------------------------------------------------------------------
	// The only one truthful type traits in the world
	//-------------------------------------------------------------------------

	#define INTERPRETER_TYPE_TRAITS_IMPL(T) \
	typedef T NoTraits; \
	typedef T &Ref; \
	typedef T *Ptr; \
	typedef const T Const; \
	typedef const T &ConstRef; \
	typedef const T *ConstPtr;

	template <class T>
	struct TypeTraits {
		INTERPRETER_TYPE_TRAITS_IMPL(T)
		enum { is_no_traits = 1 };
		enum { is_const 	= 0 };
		enum { is_reference = 0 };
		enum { is_pointer 	= 0 };
	};

	template <class T>
	struct TypeTraits <T &> {
		INTERPRETER_TYPE_TRAITS_IMPL(T)
		enum { is_no_traits = 0 };
		enum { is_const 	= 0 };
		enum { is_reference = 1 };
		enum { is_pointer 	= 0 };
	};

	template <class T>
	struct TypeTraits <T *> {
		INTERPRETER_TYPE_TRAITS_IMPL(T)
		enum { is_no_traits = 0 };
		enum { is_const 	= 0 };
		enum { is_reference = 0 };
		enum { is_pointer 	= 1 };
	};

	template <class T>
	struct TypeTraits <const T> {
		INTERPRETER_TYPE_TRAITS_IMPL(T)
		enum { is_no_traits = 0 };
		enum { is_const 	= 1 };
		enum { is_reference = 0 };
		enum { is_pointer 	= 0 };
	};

	template <class T>
	struct TypeTraits <const T &> {
		INTERPRETER_TYPE_TRAITS_IMPL(T)
		enum { is_no_traits = 0 };
		enum { is_const 	= 1 };
		enum { is_reference = 1 };
		enum { is_pointer 	= 0 };
	};

	template <class T>
	struct TypeTraits <const T *> {
		INTERPRETER_TYPE_TRAITS_IMPL(T)
		enum { is_no_traits = 0 };
		enum { is_const 	= 1 };
		enum { is_reference = 0 };
		enum { is_pointer 	= 1 };
	};

	template <>
	struct TypeTraits <void> {
		typedef void NoTraits;
		typedef void *Ptr;
		typedef const void *ConstPtr;
		enum { is_no_traits = 1 };
		enum { is_const 	= 0 };
		enum { is_reference = 0 };
		enum { is_pointer 	= 0 };
	};

	template <>
	struct TypeTraits <void *> {
		typedef void NoTraits;
		typedef void *Ptr;
		typedef const void *ConstPtr;
		enum { is_no_traits = 0 };
		enum { is_const 	= 0 };
		enum { is_reference = 0 };
		enum { is_pointer 	= 1 };
	};

	template <>
	struct TypeTraits <const void *> {
		typedef void NoTraits;
		typedef void *Ptr;
		typedef const void *ConstPtr;
		enum { is_no_traits = 0 };
		enum { is_const 	= 1 };
		enum { is_reference = 0 };
		enum { is_pointer 	= 1 };
	};

	//-------------------------------------------------------------------------

}
