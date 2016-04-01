#pragma once 

#include <sstream>

#include "variable.h"

namespace Interpreter {

	/* The POD type template, provide operators and static casts, between
	   basic C++ types */

	//-------------------------------------------------------------------------

	template <class T>
	class TypeTemplatePOD {

		public:

			typedef T This;

			//-----------------------------------------------------------------

			typedef TypeList<
			int, unsigned int, char, unsigned char, bool, long, unsigned long,
			long long, unsigned long long, float, double, Str> StaticCastList;

			//-----------------------------------------------------------------

			typedef void VtableCastList;

			//-----------------------------------------------------------------

			TypeTemplatePOD() {}
			TypeTemplatePOD(const Variable &v) : instance((T *)v) {}

			//-----------------------------------------------------------------

			void *operator new(size_t) { return new T(0); }
			void *operator new(size_t, T value) { return new T(value); }

			//-----------------------------------------------------------------

			void  operator delete(void *value) { delete (T *)value; }

			//-----------------------------------------------------------------

			template <class P>
			inline operator P  () { return static_cast<P>(*instance); }
			inline operator Str() { return std::to_string(*instance); }

			//-----------------------------------------------------------------

			Variable operator !() { return Variable(!*instance); }
			Variable operator +() { return Variable(+*instance); }
			Variable operator -() { return Variable(-*instance); }
			Variable operator ~() { return Variable(~*instance); }

			//-----------------------------------------------------------------

			Variable operator ++() { return Variable(++*instance); }
			Variable operator --() { return Variable(--*instance); }

			//-----------------------------------------------------------------

			Variable operator =(const Variable &v) { return Variable(*instance = (T &)(v.toType<T>())); }
			Variable operator +(const Variable &v) { return Variable(*instance + (T &)(v.toType<T>())); }
			Variable operator -(const Variable &v) { return Variable(*instance - (T &)(v.toType<T>())); }
			Variable operator *(const Variable &v) { return Variable(*instance * (T &)(v.toType<T>())); }
			Variable operator /(const Variable &v) { return Variable(*instance / (T &)(v.toType<T>())); }
			Variable operator %(const Variable &v) { return Variable(*instance % (T &)(v.toType<T>())); }
			Variable operator &(const Variable &v) { return Variable(*instance & (T &)(v.toType<T>())); }
			Variable operator |(const Variable &v) { return Variable(*instance | (T &)(v.toType<T>())); }
			Variable operator ^(const Variable &v) { return Variable(*instance ^ (T &)(v.toType<T>())); }
			Variable operator >(const Variable &v) { return Variable(*instance > (T &)(v.toType<T>())); }
			Variable operator <(const Variable &v) { return Variable(*instance < (T &)(v.toType<T>())); }

			//-----------------------------------------------------------------

			Variable operator ==(const Variable &v) { return Variable(*instance == (T &)(v.toType<T>())); }
			Variable operator !=(const Variable &v) { return Variable(*instance != (T &)(v.toType<T>())); }
			Variable operator >=(const Variable &v) { return Variable(*instance >= (T &)(v.toType<T>())); }
			Variable operator <=(const Variable &v) { return Variable(*instance <= (T &)(v.toType<T>())); }
			Variable operator &&(const Variable &v) { return Variable(*instance && (T &)(v.toType<T>())); }
			Variable operator ||(const Variable &v) { return Variable(*instance || (T &)(v.toType<T>())); }
			Variable operator <<(const Variable &v) { return Variable(*instance << (T &)(v.toType<T>())); }
			Variable operator >>(const Variable &v) { return Variable(*instance >> (T &)(v.toType<T>())); }

			//-----------------------------------------------------------------
			
			Variable operator +=(const Variable &v) { return Variable(*instance += (T &)(v.toType<T>())); }
			Variable operator -=(const Variable &v) { return Variable(*instance -= (T &)(v.toType<T>())); }
			Variable operator *=(const Variable &v) { return Variable(*instance *= (T &)(v.toType<T>())); }
			Variable operator /=(const Variable &v) { return Variable(*instance /= (T &)(v.toType<T>())); }
			Variable operator %=(const Variable &v) { return Variable(*instance %= (T &)(v.toType<T>())); }
			Variable operator &=(const Variable &v) { return Variable(*instance &= (T &)(v.toType<T>())); }
			Variable operator |=(const Variable &v) { return Variable(*instance |= (T &)(v.toType<T>())); }
			Variable operator ^=(const Variable &v) { return Variable(*instance ^= (T &)(v.toType<T>())); }

		protected:

			T *instance = NULL;			

	};

	/* Custom template for bool */

	//-------------------------------------------------------------------------

	class TypeTemplateBool : public TypeTemplatePOD<bool> {

		public:

			typedef bool This;

			//-----------------------------------------------------------------

			TypeTemplateBool() : TypeTemplatePOD<bool>() {}
			TypeTemplateBool(const Variable &v) : TypeTemplatePOD<bool>(v) {}

			/* Except decrement operator for boolean value */

			//-----------------------------------------------------------------

			Variable operator --() = delete;

			//-----------------------------------------------------------------

			Variable operator =(const Variable &v) { return Variable(*(this->instance) = (This &)(v.toType<This>())); }

	};

	/* Custom template for float */

	//-------------------------------------------------------------------------

	class TypeTemplateFloat : public TypeTemplatePOD<float> {

		public:

			typedef float This;

			//-----------------------------------------------------------------

			TypeTemplateFloat() : TypeTemplatePOD<float>() {}
			TypeTemplateFloat(const Variable &v) : TypeTemplatePOD<float>(v) {}

			/* Except some bitwise and compound operators for float value */

			//-----------------------------------------------------------------

			Variable operator ~() = delete;

			//-----------------------------------------------------------------

			Variable operator %(const Variable &v) = delete;
			Variable operator &(const Variable &v) = delete;
			Variable operator |(const Variable &v) = delete;
			Variable operator ^(const Variable &v) = delete;

			//-----------------------------------------------------------------

			Variable operator <<(const Variable &v) = delete;
			Variable operator >>(const Variable &v) = delete;
			Variable operator %=(const Variable &v) = delete;
			Variable operator &=(const Variable &v) = delete;
			Variable operator |=(const Variable &v) = delete;
			Variable operator ^=(const Variable &v) = delete;

			//-----------------------------------------------------------------

			Variable operator =(const Variable &v) { return Variable(*(this->instance) = (This &)(v.toType<This>())); }

	};

	/* Custom template for double */

	//-------------------------------------------------------------------------

	class TypeTemplateDouble : public TypeTemplatePOD<double> {

		public:

			typedef double This;

			//-----------------------------------------------------------------

			TypeTemplateDouble() : TypeTemplatePOD<double>() {}
			TypeTemplateDouble(const Variable &v) : TypeTemplatePOD<double>(v) {}

			/* Except some bitwise and compound operators for double value */

			//-----------------------------------------------------------------

			Variable operator ~() = delete;

			//-----------------------------------------------------------------

			Variable operator %(const Variable &v) = delete;
			Variable operator &(const Variable &v) = delete;
			Variable operator |(const Variable &v) = delete;
			Variable operator ^(const Variable &v) = delete;

			//-----------------------------------------------------------------

			Variable operator <<(const Variable &v) = delete;
			Variable operator >>(const Variable &v) = delete;
			Variable operator %=(const Variable &v) = delete;
			Variable operator &=(const Variable &v) = delete;
			Variable operator |=(const Variable &v) = delete;
			Variable operator ^=(const Variable &v) = delete;

			//-----------------------------------------------------------------

			Variable operator =(const Variable &v) { return Variable(*(this->instance) = (This &)(v.toType<This>())); }

	};

	/* Custom template for string */

	//-------------------------------------------------------------------------

	class TypeTemplateStr {

		public:

			typedef Str This;

			//-----------------------------------------------------------------

			typedef TypeList<
			int, unsigned int, char, unsigned char, bool, long, unsigned long,
			long long, unsigned long long, float, double, Str> StaticCastList;

			//-----------------------------------------------------------------

			typedef void VtableCastList;

			//-----------------------------------------------------------------

			TypeTemplateStr() {}
			TypeTemplateStr(const Variable &v) : instance((Str *)v) {}

			//-----------------------------------------------------------------

			template <class T>
			inline operator T() {
				T value = 0;
				std::istringstream stream(*instance);
				stream >> value;
				return value;
			}

			inline operator Str() {
				return *instance;
			}

			//-----------------------------------------------------------------

			void *operator new(size_t) { return new Str(); }
			void *operator new(size_t, const Str &value) { return new Str(value); }

			//-----------------------------------------------------------------

			void  operator delete(void *value) { delete (Str *)value; }

			//-----------------------------------------------------------------

			Variable operator =(const Variable &v) { return Variable(*(instance) = (Str &)(v.toType<Str>())); }
			Variable operator +(const Variable &v) { return Variable(*(instance) + (Str &)(v.toType<Str>())); }

			//-----------------------------------------------------------------

			Variable operator +=(const Variable &v) { return Variable(*(instance) += (Str &)(v.toType<Str>())); }
			Variable operator [](const Variable &v) {
				Str &instance = *(this->instance);
				return Variable(instance[(int &)(v.toType<int>())]);
			}

		private:

			Str *instance = NULL;

	};

	//-------------------------------------------------------------------------

	template <>
	struct TypeToTemplate <int> {
		typedef TypeTemplatePOD<int> Template;
	};

	template <>
	struct TypeToTemplate <unsigned int> {
		typedef TypeTemplatePOD<unsigned int> Template;
	};

	template <>
	struct TypeToTemplate <char> {
		typedef TypeTemplatePOD<char> Template;
	};

	template <>
	struct TypeToTemplate <unsigned char> {
		typedef TypeTemplatePOD<unsigned char> Template;
	};

	template <>
	struct TypeToTemplate <bool> {
		typedef TypeTemplateBool Template;
	};

	template <>
	struct TypeToTemplate <long> {
		typedef TypeTemplatePOD<long> Template;
	};

	template <>
	struct TypeToTemplate <unsigned long> {
		typedef TypeTemplatePOD<unsigned long> Template;
	};

	template <>
	struct TypeToTemplate <long long> {
		typedef TypeTemplatePOD<long long> Template;
	};

	template <>
	struct TypeToTemplate <unsigned long long> {
		typedef TypeTemplatePOD<unsigned long long> Template;
	};

	template <>
	struct TypeToTemplate <float> {
		typedef TypeTemplateFloat Template;
	};

	template <>
	struct TypeToTemplate <double> {
		typedef TypeTemplateDouble Template;
	};

	template <>
	struct TypeToTemplate <Str> {
		typedef TypeTemplateStr Template;
	};

	//-------------------------------------------------------------------------

}




