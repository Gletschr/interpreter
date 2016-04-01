#pragma once

#include <vector>
#include <string>
#include <assert.h>
#include <memory>
#include <stack>
#include <map>
#include <typeinfo>

#include "traits.h"

#include <QDebug>

namespace Interpreter {

	//-------------------------------------------------------------------------

	template <class T>
	using Ptr = std::shared_ptr<T>;
	using Str = std::string;
	template <class K, class V>
	using Map = std::map<K, V>;

	template <class T>
	using Stack = std::stack<T>;

	template <class T>
	using Vector = std::vector<T>;

	//-------------------------------------------------------------------------

	template <class T>
	using InitializerList = std::initializer_list<T>;

	//-------------------------------------------------------------------------
	
	void error(const char *format, ...);

	//-------------------------------------------------------------------------

	#define INTERPRETER_UNUSED(V) (void)V

	//-------------------------------------------------------------------------
	
	#define INTERPRETER_NOTRAITS(T) typename TypeTraits<T>::NoTraits

	//-------------------------------------------------------------------------

	#define INTERPRETER_TYPEID(T) typeid(INTERPRETER_NOTRAITS(T)).hash_code()

	//-------------------------------------------------------------------------

	#ifdef __MINGW32__
	
	Str mingw32_und_name(bool is_const, bool is_ref, bool is_ptr, const char *name);

	#define INTERPRETER_TYPENAME(T) \
	mingw32_und_name(TypeTraits<T>::is_const, \
				TypeTraits<T>::is_reference,\
				TypeTraits<T>::is_pointer,\
				typeid(INTERPRETER_NOTRAITS(T)).name()).c_str()

	#else
	#define INTERPRETER_TYPENAME(T) typeid(T).name()
	#endif

	//-------------------------------------------------------------------------

	unsigned int hash(const Str &str);

	//-------------------------------------------------------------------------

}
