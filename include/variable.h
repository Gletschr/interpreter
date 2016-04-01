#pragma once 

#include "common.h"

namespace Interpreter {

	//-------------------------------------------------------------------------

	class Variable;

	//-------------------------------------------------------------------------

	template <class T>
	struct TypeToTemplate { typedef void Template; };

	//-------------------------------------------------------------------------

	struct TypeInfo {

		TypeInfo();

		template <class Template>
		explicit TypeInfo(const Template &type);

		Str name;
		bool is_const;
		unsigned int id;

		struct {
			Vector<unsigned int> _traits;
			Vector<Variable (Variable::*)() const> _fcn;
		} stc_cast;

		struct {
			Vector<unsigned int> _traits;
			Vector<Variable (Variable::*)() const> _fcn;
		} vtb_cast;

		struct {

			void *	(*_new)(size_t);
			void	(*_del)(void *);

			//-----------------------------------------------------------------

			Variable (Variable::*_not)() const;
			Variable (Variable::*_pos)() const;
			Variable (Variable::*_neg)() const;
			Variable (Variable::*_inv)() const;
			Variable (Variable::*_inc)() const;
			Variable (Variable::*_dec)() const;

			//-----------------------------------------------------------------

			Variable (Variable::*_gt)(const Variable &) const;
			Variable (Variable::*_lt)(const Variable &) const;
			Variable (Variable::*_eq)(const Variable &) const;
			Variable (Variable::*_ne)(const Variable &) const;
			Variable (Variable::*_ge)(const Variable &) const;
			Variable (Variable::*_le)(const Variable &) const;

			//-----------------------------------------------------------------

			Variable (Variable::*_asg)(const Variable &) const;
			Variable (Variable::*_add)(const Variable &) const;
			Variable (Variable::*_sub)(const Variable &) const;
			Variable (Variable::*_mul)(const Variable &) const;
			Variable (Variable::*_div)(const Variable &) const;
			Variable (Variable::*_mod)(const Variable &) const;
			Variable (Variable::*_ban)(const Variable &) const;
			Variable (Variable::*_bor)(const Variable &) const;
			Variable (Variable::*_xor)(const Variable &) const;
			Variable (Variable::*_lan)(const Variable &) const;
			Variable (Variable::*_lor)(const Variable &) const;
			Variable (Variable::*_lsh)(const Variable &) const;
			Variable (Variable::*_rsh)(const Variable &) const;
			Variable (Variable::*_sbs)(const Variable &) const;
			Variable (Variable::*_fcn)(const Variable &) const;

			//-----------------------------------------------------------------

			Variable (Variable::*_cmp_add)(const Variable &) const;
			Variable (Variable::*_cmp_sub)(const Variable &) const;
			Variable (Variable::*_cmp_mul)(const Variable &) const;
			Variable (Variable::*_cmp_div)(const Variable &) const;
			Variable (Variable::*_cmp_mod)(const Variable &) const;
			Variable (Variable::*_cmp_ban)(const Variable &) const;
			Variable (Variable::*_cmp_bor)(const Variable &) const;
			Variable (Variable::*_cmp_xor)(const Variable &) const;

			//-----------------------------------------------------------------

		} operators;

	};

	//-------------------------------------------------------------------------

	template <class T>
	using Template = typename TypeToTemplate<T>::Template;

	//-------------------------------------------------------------------------

	class Variable {

		public:

			//-----------------------------------------------------------------

			Variable();
			Variable(const Variable &v);

			//-----------------------------------------------------------------

			const TypeInfo &getType() const;
			unsigned int getUseCount() const;

			//-----------------------------------------------------------------

			template <class T>
			Variable(T value);

			//-----------------------------------------------------------------

			template <class T>
			inline Variable toType() const;

			//-----------------------------------------------------------------

			inline operator void *() const;

			//-----------------------------------------------------------------

			template <class T>
			inline operator T &() const;

			template <class T>
			inline operator T *() const;

			template <class T>
			inline operator const T &() const;

			template <class T>
			inline operator const T *() const;

			//-----------------------------------------------------------------

			Variable &operator =(const Variable &v);

			//-----------------------------------------------------------------

			Variable operator !() const;
			Variable operator +() const;
			Variable operator -() const;
			Variable operator ~() const;

			//-----------------------------------------------------------------

			Variable operator ++() const;
			Variable operator --() const;

			//-----------------------------------------------------------------

			Variable operator =(const Variable &v) const;
			Variable operator +(const Variable &v) const;
			Variable operator -(const Variable &v) const;
			Variable operator *(const Variable &v) const;
			Variable operator /(const Variable &v) const;
			Variable operator %(const Variable &v) const;
			Variable operator &(const Variable &v) const;
			Variable operator |(const Variable &v) const;
			Variable operator ^(const Variable &v) const;
			Variable operator >(const Variable &v) const;
			Variable operator <(const Variable &v) const;

			//-----------------------------------------------------------------

			Variable operator ==(const Variable &v) const;
			Variable operator !=(const Variable &v) const;
			Variable operator >=(const Variable &v) const;
			Variable operator <=(const Variable &v) const;
			Variable operator &&(const Variable &v) const;
			Variable operator ||(const Variable &v) const;
			Variable operator <<(const Variable &v) const;
			Variable operator >>(const Variable &v) const;
			Variable operator [](const Variable &v) const;
			Variable operator ()(const Variable &v) const;

			//-----------------------------------------------------------------
			
			Variable operator +=(const Variable &v) const;
			Variable operator -=(const Variable &v) const;
			Variable operator *=(const Variable &v) const;
			Variable operator /=(const Variable &v) const;
			Variable operator %=(const Variable &v) const;
			Variable operator &=(const Variable &v) const;
			Variable operator |=(const Variable &v) const;
			Variable operator ^=(const Variable &v) const;

			//-----------------------------------------------------------------

			template <class T, class D>
			inline Variable toType() const { return Variable(Template<T>(*this).operator D()); }

			template <class... Ts>
			inline Variable operator ()(Ts... args) const {
				InitializerList<Variable> va = { Variable(args)... };
				Variable (Variable::*_fcn)(const Variable &) const = &Variable::operator ();
				return (this->*_fcn)(Variable(va));
			}

			//-----------------------------------------------------------------

			template <class T>
			inline Variable operator !() const { return Template<T>(*this).operator !(); }
			template <class T>
			inline Variable operator +() const { return Template<T>(*this).operator +(); }
			template <class T>
			inline Variable operator -() const { return Template<T>(*this).operator -(); }
			template <class T>
			inline Variable operator ~() const { return Template<T>(*this).operator ~(); }

			//-----------------------------------------------------------------

			template <class T>
			inline Variable operator ++() const { return Template<T>(*this).operator ++(); }
			template <class T>
			inline Variable operator --() const { return Template<T>(*this).operator --(); }

			//-----------------------------------------------------------------

			template <class T>
			inline Variable operator =(const Variable &v) const { return Template<T>(*this).operator =(v); }
			template <class T>
			inline Variable operator +(const Variable &v) const { return Template<T>(*this).operator +(v); }
			template <class T>
			inline Variable operator -(const Variable &v) const { return Template<T>(*this).operator -(v); }
			template <class T>
			inline Variable operator *(const Variable &v) const { return Template<T>(*this).operator *(v); }
			template <class T>
			inline Variable operator /(const Variable &v) const { return Template<T>(*this).operator /(v); }
			template <class T>
			inline Variable operator %(const Variable &v) const { return Template<T>(*this).operator %(v); }
			template <class T>
			inline Variable operator &(const Variable &v) const { return Template<T>(*this).operator &(v); }
			template <class T>
			inline Variable operator |(const Variable &v) const { return Template<T>(*this).operator |(v); }
			template <class T>
			inline Variable operator ^(const Variable &v) const { return Template<T>(*this).operator ^(v); }
			template <class T>
			inline Variable operator >(const Variable &v) const { return Template<T>(*this).operator >(v); }
			template <class T>
			inline Variable operator <(const Variable &v) const { return Template<T>(*this).operator <(v); }

			//-----------------------------------------------------------------

			template <class T>
			inline Variable operator ==(const Variable &v) const { return Template<T>(*this).operator ==(v); }
			template <class T>
			inline Variable operator !=(const Variable &v) const { return Template<T>(*this).operator !=(v); }
			template <class T>
			inline Variable operator >=(const Variable &v) const { return Template<T>(*this).operator >=(v); }
			template <class T>
			inline Variable operator <=(const Variable &v) const { return Template<T>(*this).operator <=(v); }
			template <class T>
			inline Variable operator &&(const Variable &v) const { return Template<T>(*this).operator &&(v); }
			template <class T>
			inline Variable operator ||(const Variable &v) const { return Template<T>(*this).operator ||(v); }
			template <class T>
			inline Variable operator [](const Variable &v) const { return Template<T>(*this).operator [](v); }
			template <class T>
			inline Variable operator ()(const Variable &v) const { return Template<T>(*this).operator ()(v); }
			template <class T>
			inline Variable operator <<(const Variable &v) const { return Template<T>(*this).operator <<(v); }
			template <class T>
			inline Variable operator >>(const Variable &v) const { return Template<T>(*this).operator >>(v); }

			//-----------------------------------------------------------------

			template <class T>
			inline Variable operator +=(const Variable &v) const { return Template<T>(*this).operator +=(v); }
			template <class T>
			inline Variable operator -=(const Variable &v) const { return Template<T>(*this).operator -=(v); }
			template <class T>
			inline Variable operator *=(const Variable &v) const { return Template<T>(*this).operator *=(v); }
			template <class T>
			inline Variable operator /=(const Variable &v) const { return Template<T>(*this).operator /=(v); }
			template <class T>
			inline Variable operator %=(const Variable &v) const { return Template<T>(*this).operator %=(v); }
			template <class T>
			inline Variable operator &=(const Variable &v) const { return Template<T>(*this).operator &=(v); }
			template <class T>
			inline Variable operator |=(const Variable &v) const { return Template<T>(*this).operator |=(v); }
			template <class T>
			inline Variable operator ^=(const Variable &v) const { return Template<T>(*this).operator ^=(v); }

			//-----------------------------------------------------------------

			~Variable() { free(); }

			//-----------------------------------------------------------------

		private:

			//-----------------------------------------------------------------

			void grab();
			void free();
			void release();

			//-----------------------------------------------------------------

		private:

			TypeInfo type_info;
			mutable void *data { NULL };

			//-----------------------------------------------------------------

			Ptr<unsigned int> use_count { new unsigned int(1) };

	};

	//-------------------------------------------------------------------------

	template <class T>
	inline Variable Variable::toType() const {
		if(type_info.id == INTERPRETER_TYPEID(T)) return *this;
		if(std::is_same<typename TypeTraits<T>::NoTraits, Variable>::value) return *this;
		for(unsigned int i = 0; i < type_info.stc_cast._traits.size(); ++ i) {
			if(type_info.stc_cast._traits[i] == INTERPRETER_TYPEID(T)) return (this->*type_info.stc_cast._fcn[i])();
		}
		for(unsigned int i = 0; i < type_info.vtb_cast._traits.size(); ++ i) {
			if(type_info.vtb_cast._traits[i] == INTERPRETER_TYPEID(T)) return (this->*type_info.vtb_cast._fcn[i])();
		}
		error("Variable<%s>::toType<%s>(): cast is not acceptible for this variable.", type_info.name.c_str(), INTERPRETER_TYPENAME(T));
		return Variable();
	}

	//-------------------------------------------------------------------------

	template <class T>
	inline Variable::operator T &() const { 
		if(type_info.id == INTERPRETER_TYPEID(T)) return *(T *)data;
		for(unsigned int i = 0; i < type_info.vtb_cast._traits.size(); ++ i) {
			if(type_info.vtb_cast._traits[i] == INTERPRETER_TYPEID(T)) return *(T *)(this->*type_info.vtb_cast._fcn[i])().data;
		}
		error("Variable<%s>::operator %s(): cast is not acceptible for this variable.", type_info.name.c_str(), INTERPRETER_TYPENAME(T &));
		return *(T *)data;
	}

	template <class T>
	inline Variable::operator T *() const { 
		if(type_info.id == INTERPRETER_TYPEID(T)) return  (T *)data;
		for(unsigned int i = 0; i < type_info.vtb_cast._traits.size(); ++ i) {
			if(type_info.vtb_cast._traits[i] == INTERPRETER_TYPEID(T)) return  (T *)(this->*type_info.vtb_cast._fcn[i])().data;
		}
		error("Variable<%s>::operator %s(): cast is not acceptible for this variable.", type_info.name.c_str(), INTERPRETER_TYPENAME(T *));
		return  (T *)data;
	}

	template <class T>
	inline Variable::operator const T &() const { 
		if(type_info.id == INTERPRETER_TYPEID(T)) return *(T *)data;
		for(unsigned int i = 0; i < type_info.vtb_cast._traits.size(); ++ i) {
			if(type_info.vtb_cast._traits[i] == INTERPRETER_TYPEID(T)) return *(T *)(this->*type_info.vtb_cast._fcn[i])().data;
		}
		error("Variable<%s>::operator %s(): cast is not acceptible for this variable.", type_info.name.c_str(), INTERPRETER_TYPENAME(const T &));
		return *(T *)data;
	}

	template <class T>
	inline Variable::operator const T *() const { 
		if(type_info.id == INTERPRETER_TYPEID(T)) return  (T *)data;
		for(unsigned int i = 0; i < type_info.vtb_cast._traits.size(); ++ i) {
			if(type_info.vtb_cast._traits[i] == INTERPRETER_TYPEID(T)) return  (T *)(this->*type_info.vtb_cast._fcn[i])().data;
		}
		error("Variable<%s>::operator %s(): cast is not acceptible for this variable.", type_info.name.c_str(), INTERPRETER_TYPENAME(const T *));
		return  (T *)data;
	}

	//-------------------------------------------------------------------------

	template <class T, class... Ts>
	struct TypeList {
		typedef T Type;
		typedef TypeList<Ts...> Next;
	};

	template <class T>
	struct TypeList <T> {
		typedef T Type;
		typedef void Next;
	};

	//-------------------------------------------------------------------------

	template <class T, class List>
	struct TemplateToTypeInitializer {
		static void init(Vector<unsigned int> &_traits, Vector<Variable (Variable::*)() const> &_fcn) {
			_traits.push_back(INTERPRETER_TYPEID(typename List::Type));
			_fcn.push_back(&Variable::toType<T, typename List::Type>);
			TemplateToTypeInitializer<T, typename List::Next>::init(_traits, _fcn);
		}
	};

	template <class T>
	struct TemplateToTypeInitializer <T, void> {
		static void init(Vector<unsigned int> &, Vector<Variable (Variable::*)() const> &) {
		}
	};

	template <>
	struct TemplateToTypeInitializer <void, void> {
		static void init(Vector<unsigned int> &, Vector<Variable (Variable::*)() const> &) {
		}
	};

	//-------------------------------------------------------------------------

	template <class Template>
	class TemplateInfo {

			static void sfi_not(...);
			static void sfi_pos(...);
			static void sfi_neg(...);
			static void sfi_inv(...);
			static void sfi_inc(...);
			static void sfi_dec(...);

			//-----------------------------------------------------------------

			static void sfi_gt(...);
			static void sfi_lt(...);
			static void sfi_eq(...);
			static void sfi_ne(...);
			static void sfi_ge(...);
			static void sfi_le(...);

			//-----------------------------------------------------------------

			static void sfi_asg(...);
			static void sfi_add(...);
			static void sfi_sub(...);
			static void sfi_mul(...);
			static void sfi_div(...);
			static void sfi_mod(...);
			static void sfi_ban(...);
			static void sfi_bor(...);
			static void sfi_xor(...);
			static void sfi_lan(...);
			static void sfi_lor(...);
			static void sfi_lsh(...);
			static void sfi_rsh(...);
			static void sfi_sbs(...);
			static void sfi_fcn(...);

			//-----------------------------------------------------------------

			static void sfi_cmp_add(...);
			static void sfi_cmp_sub(...);
			static void sfi_cmp_mul(...);
			static void sfi_cmp_div(...);
			static void sfi_cmp_mod(...);
			static void sfi_cmp_ban(...);
			static void sfi_cmp_bor(...);
			static void sfi_cmp_xor(...);

			//-----------------------------------------------------------------

			template <class T> static decltype(std::declval<T>().operator !()) sfi_not(const T &);
			template <class T> static decltype(std::declval<T>().operator +()) sfi_pos(const T &);
			template <class T> static decltype(std::declval<T>().operator -()) sfi_neg(const T &);
			template <class T> static decltype(std::declval<T>().operator ~()) sfi_inv(const T &);

			//-----------------------------------------------------------------

			template <class T> static decltype(std::declval<T>().operator > (std::declval<Variable>())) sfi_gt(const T &);
			template <class T> static decltype(std::declval<T>().operator < (std::declval<Variable>())) sfi_lt(const T &);
			template <class T> static decltype(std::declval<T>().operator ==(std::declval<Variable>())) sfi_eq(const T &);
			template <class T> static decltype(std::declval<T>().operator !=(std::declval<Variable>())) sfi_ne(const T &);
			template <class T> static decltype(std::declval<T>().operator >=(std::declval<Variable>())) sfi_ge(const T &);
			template <class T> static decltype(std::declval<T>().operator <=(std::declval<Variable>())) sfi_le(const T &);

			//-----------------------------------------------------------------

			template <class T> static decltype(std::declval<T>().operator ++()) sfi_inc(const T &);
			template <class T> static decltype(std::declval<T>().operator --()) sfi_dec(const T &);

			//-----------------------------------------------------------------

			template <class T> static decltype(std::declval<T>().operator =(std::declval<Variable>())) sfi_asg(const T &);
			template <class T> static decltype(std::declval<T>().operator +(std::declval<Variable>())) sfi_add(const T &);
			template <class T> static decltype(std::declval<T>().operator -(std::declval<Variable>())) sfi_sub(const T &);
			template <class T> static decltype(std::declval<T>().operator *(std::declval<Variable>())) sfi_mul(const T &);
			template <class T> static decltype(std::declval<T>().operator /(std::declval<Variable>())) sfi_div(const T &);
			template <class T> static decltype(std::declval<T>().operator %(std::declval<Variable>())) sfi_mod(const T &);
			template <class T> static decltype(std::declval<T>().operator &(std::declval<Variable>())) sfi_ban(const T &);
			template <class T> static decltype(std::declval<T>().operator |(std::declval<Variable>())) sfi_bor(const T &);
			template <class T> static decltype(std::declval<T>().operator ^(std::declval<Variable>())) sfi_xor(const T &);

			//-----------------------------------------------------------------

			template <class T> static decltype(std::declval<T>().operator &&(std::declval<Variable>())) sfi_lan(const T &);
			template <class T> static decltype(std::declval<T>().operator ||(std::declval<Variable>())) sfi_lor(const T &);
			template <class T> static decltype(std::declval<T>().operator <<(std::declval<Variable>())) sfi_lsh(const T &);
			template <class T> static decltype(std::declval<T>().operator >>(std::declval<Variable>())) sfi_rsh(const T &);
			template <class T> static decltype(std::declval<T>().operator [](std::declval<Variable>())) sfi_sbs(const T &);
			template <class T> static decltype(std::declval<T>().operator ()(std::declval<Variable>())) sfi_fcn(const T &);

			//-----------------------------------------------------------------

			template <class T> static decltype(std::declval<T>().operator +=(std::declval<Variable>())) sfi_cmp_add(const T &);
			template <class T> static decltype(std::declval<T>().operator -=(std::declval<Variable>())) sfi_cmp_sub(const T &);
			template <class T> static decltype(std::declval<T>().operator *=(std::declval<Variable>())) sfi_cmp_mul(const T &);
			template <class T> static decltype(std::declval<T>().operator /=(std::declval<Variable>())) sfi_cmp_div(const T &);
			template <class T> static decltype(std::declval<T>().operator %=(std::declval<Variable>())) sfi_cmp_mod(const T &);
			template <class T> static decltype(std::declval<T>().operator &=(std::declval<Variable>())) sfi_cmp_ban(const T &);
			template <class T> static decltype(std::declval<T>().operator |=(std::declval<Variable>())) sfi_cmp_bor(const T &);
			template <class T> static decltype(std::declval<T>().operator ^=(std::declval<Variable>())) sfi_cmp_xor(const T &);

			//-----------------------------------------------------------------

			using Un	= Variable (Variable::*)() const;
			using Bin	= Variable (Variable::*)(const Variable &) const;

			//-----------------------------------------------------------------

			template <class T, bool> struct def_not { static constexpr Un v = (&Variable::operator !<T>); };
			template <class T, bool> struct def_pos { static constexpr Un v = (&Variable::operator +<T>); };
			template <class T, bool> struct def_neg { static constexpr Un v = (&Variable::operator -<T>); };
			template <class T, bool> struct def_inv { static constexpr Un v = (&Variable::operator ~<T>); };

			//-----------------------------------------------------------------

			template <class T, bool> struct def_inc { static constexpr Un v = (&Variable::operator ++<T>); };
			template <class T, bool> struct def_dec { static constexpr Un v = (&Variable::operator --<T>); };

			//-----------------------------------------------------------------

			template <class T, bool> struct def_gt { static constexpr Bin v = (&Variable::operator > <T>); };
			template <class T, bool> struct def_lt { static constexpr Bin v = (&Variable::operator < <T>); };
			template <class T, bool> struct def_eq { static constexpr Bin v = (&Variable::operator ==<T>); };
			template <class T, bool> struct def_ne { static constexpr Bin v = (&Variable::operator !=<T>); };
			template <class T, bool> struct def_ge { static constexpr Bin v = (&Variable::operator >=<T>); };
			template <class T, bool> struct def_le { static constexpr Bin v = (&Variable::operator <=<T>); };

			//-----------------------------------------------------------------

			template <class T, bool> struct def_asg { static constexpr Bin v = (&Variable::operator =<T>); };
			template <class T, bool> struct def_add { static constexpr Bin v = (&Variable::operator +<T>); };
			template <class T, bool> struct def_sub { static constexpr Bin v = (&Variable::operator -<T>); };
			template <class T, bool> struct def_mul { static constexpr Bin v = (&Variable::operator *<T>); };
			template <class T, bool> struct def_div { static constexpr Bin v = (&Variable::operator /<T>); };
			template <class T, bool> struct def_mod { static constexpr Bin v = (&Variable::operator %<T>); };
			template <class T, bool> struct def_ban { static constexpr Bin v = (&Variable::operator &<T>); };
			template <class T, bool> struct def_bor { static constexpr Bin v = (&Variable::operator |<T>); };
			template <class T, bool> struct def_xor { static constexpr Bin v = (&Variable::operator ^<T>); };

			//-----------------------------------------------------------------

			template <class T, bool> struct def_lan { static constexpr Bin v = (&Variable::operator &&<T>); };
			template <class T, bool> struct def_lor { static constexpr Bin v = (&Variable::operator ||<T>); };
			template <class T, bool> struct def_lsh { static constexpr Bin v = (&Variable::operator <<<T>); };
			template <class T, bool> struct def_rsh { static constexpr Bin v = (&Variable::operator >><T>); };
			template <class T, bool> struct def_sbs { static constexpr Bin v = (&Variable::operator []<T>); };
			template <class T, bool> struct def_fcn { static constexpr Bin v = (&Variable::operator ()<T>); };

			//-----------------------------------------------------------------

			template <class T, bool> struct def_cmp_add { static constexpr Bin v = (&Variable::operator +=<T>); };
			template <class T, bool> struct def_cmp_sub { static constexpr Bin v = (&Variable::operator -=<T>); };
			template <class T, bool> struct def_cmp_mul { static constexpr Bin v = (&Variable::operator *=<T>); };
			template <class T, bool> struct def_cmp_div { static constexpr Bin v = (&Variable::operator /=<T>); };
			template <class T, bool> struct def_cmp_mod { static constexpr Bin v = (&Variable::operator %=<T>); };
			template <class T, bool> struct def_cmp_ban { static constexpr Bin v = (&Variable::operator &=<T>); };
			template <class T, bool> struct def_cmp_bor { static constexpr Bin v = (&Variable::operator |=<T>); };
			template <class T, bool> struct def_cmp_xor { static constexpr Bin v = (&Variable::operator ^=<T>); };

			//-----------------------------------------------------------------

			template <class T> struct def_not<T, false> { static constexpr Un v = NULL; };
			template <class T> struct def_pos<T, false> { static constexpr Un v = NULL; };
			template <class T> struct def_neg<T, false> { static constexpr Un v = NULL; };
			template <class T> struct def_inv<T, false> { static constexpr Un v = NULL; };

			//-----------------------------------------------------------------

			template <class T> struct def_inc<T, false> { static constexpr Un v = NULL; };
			template <class T> struct def_dec<T, false> { static constexpr Un v = NULL; };

			//-----------------------------------------------------------------

			template <class T> struct def_gt<T, false> { static constexpr Bin v = NULL; };
			template <class T> struct def_lt<T, false> { static constexpr Bin v = NULL; };
			template <class T> struct def_eq<T, false> { static constexpr Bin v = NULL; };
			template <class T> struct def_ne<T, false> { static constexpr Bin v = NULL; };
			template <class T> struct def_ge<T, false> { static constexpr Bin v = NULL; };
			template <class T> struct def_le<T, false> { static constexpr Bin v = NULL; };

			//-----------------------------------------------------------------

			template <class T> struct def_asg<T, false> { static constexpr Bin v = NULL; };
			template <class T> struct def_add<T, false> { static constexpr Bin v = NULL; };
			template <class T> struct def_sub<T, false> { static constexpr Bin v = NULL; };
			template <class T> struct def_mul<T, false> { static constexpr Bin v = NULL; };
			template <class T> struct def_div<T, false> { static constexpr Bin v = NULL; };
			template <class T> struct def_mod<T, false> { static constexpr Bin v = NULL; };
			template <class T> struct def_ban<T, false> { static constexpr Bin v = NULL; };
			template <class T> struct def_bor<T, false> { static constexpr Bin v = NULL; };
			template <class T> struct def_xor<T, false> { static constexpr Bin v = NULL; };

			//-----------------------------------------------------------------

			template <class T> struct def_lan<T, false> { static constexpr Bin v = NULL; };
			template <class T> struct def_lor<T, false> { static constexpr Bin v = NULL; };
			template <class T> struct def_lsh<T, false> { static constexpr Bin v = NULL; };
			template <class T> struct def_rsh<T, false> { static constexpr Bin v = NULL; };
			template <class T> struct def_sbs<T, false> { static constexpr Bin v = NULL; };
			template <class T> struct def_fcn<T, false> { static constexpr Bin v = NULL; };

			//-----------------------------------------------------------------

			template <class T> struct def_cmp_add<T, false> { static constexpr Bin v = NULL; };
			template <class T> struct def_cmp_sub<T, false> { static constexpr Bin v = NULL; };
			template <class T> struct def_cmp_mul<T, false> { static constexpr Bin v = NULL; };
			template <class T> struct def_cmp_div<T, false> { static constexpr Bin v = NULL; };
			template <class T> struct def_cmp_mod<T, false> { static constexpr Bin v = NULL; };
			template <class T> struct def_cmp_ban<T, false> { static constexpr Bin v = NULL; };
			template <class T> struct def_cmp_bor<T, false> { static constexpr Bin v = NULL; };
			template <class T> struct def_cmp_xor<T, false> { static constexpr Bin v = NULL; };

		public:

			//-----------------------------------------------------------------

			enum { has_not = std::is_same<Variable, decltype(sfi_not(std::declval<Template>()))>::value };
			enum { has_pos = std::is_same<Variable, decltype(sfi_pos(std::declval<Template>()))>::value };
			enum { has_neg = std::is_same<Variable, decltype(sfi_neg(std::declval<Template>()))>::value };
			enum { has_inv = std::is_same<Variable, decltype(sfi_inv(std::declval<Template>()))>::value };
			enum { has_inc = std::is_same<Variable, decltype(sfi_inc(std::declval<Template>()))>::value };
			enum { has_dec = std::is_same<Variable, decltype(sfi_dec(std::declval<Template>()))>::value };

			//-----------------------------------------------------------------

			enum { has_gt = std::is_same<Variable, decltype(sfi_gt(std::declval<Template>()))>::value };
			enum { has_lt = std::is_same<Variable, decltype(sfi_lt(std::declval<Template>()))>::value };
			enum { has_eq = std::is_same<Variable, decltype(sfi_eq(std::declval<Template>()))>::value };
			enum { has_ne = std::is_same<Variable, decltype(sfi_ne(std::declval<Template>()))>::value };
			enum { has_ge = std::is_same<Variable, decltype(sfi_ge(std::declval<Template>()))>::value };
			enum { has_le = std::is_same<Variable, decltype(sfi_le(std::declval<Template>()))>::value };

			//-----------------------------------------------------------------

			enum { has_asg = std::is_same<Variable, decltype(sfi_asg(std::declval<Template>()))>::value };
			enum { has_add = std::is_same<Variable, decltype(sfi_add(std::declval<Template>()))>::value };
			enum { has_sub = std::is_same<Variable, decltype(sfi_sub(std::declval<Template>()))>::value };
			enum { has_mul = std::is_same<Variable, decltype(sfi_mul(std::declval<Template>()))>::value };
			enum { has_div = std::is_same<Variable, decltype(sfi_div(std::declval<Template>()))>::value };
			enum { has_mod = std::is_same<Variable, decltype(sfi_mod(std::declval<Template>()))>::value };
			enum { has_ban = std::is_same<Variable, decltype(sfi_ban(std::declval<Template>()))>::value };
			enum { has_bor = std::is_same<Variable, decltype(sfi_bor(std::declval<Template>()))>::value };
			enum { has_xor = std::is_same<Variable, decltype(sfi_xor(std::declval<Template>()))>::value };
			enum { has_lan = std::is_same<Variable, decltype(sfi_lan(std::declval<Template>()))>::value };
			enum { has_lor = std::is_same<Variable, decltype(sfi_lor(std::declval<Template>()))>::value };
			enum { has_lsh = std::is_same<Variable, decltype(sfi_lsh(std::declval<Template>()))>::value };
			enum { has_rsh = std::is_same<Variable, decltype(sfi_rsh(std::declval<Template>()))>::value };
			enum { has_sbs = std::is_same<Variable, decltype(sfi_sbs(std::declval<Template>()))>::value };
			enum { has_fcn = std::is_same<Variable, decltype(sfi_fcn(std::declval<Template>()))>::value };

			//-----------------------------------------------------------------

			enum { has_cmp_add = std::is_same<Variable, decltype(sfi_cmp_add(std::declval<Template>()))>::value };
			enum { has_cmp_sub = std::is_same<Variable, decltype(sfi_cmp_sub(std::declval<Template>()))>::value };
			enum { has_cmp_mul = std::is_same<Variable, decltype(sfi_cmp_mul(std::declval<Template>()))>::value };
			enum { has_cmp_div = std::is_same<Variable, decltype(sfi_cmp_div(std::declval<Template>()))>::value };
			enum { has_cmp_mod = std::is_same<Variable, decltype(sfi_cmp_mod(std::declval<Template>()))>::value };
			enum { has_cmp_ban = std::is_same<Variable, decltype(sfi_cmp_ban(std::declval<Template>()))>::value };
			enum { has_cmp_bor = std::is_same<Variable, decltype(sfi_cmp_bor(std::declval<Template>()))>::value };
			enum { has_cmp_xor = std::is_same<Variable, decltype(sfi_cmp_xor(std::declval<Template>()))>::value };

			//-----------------------------------------------------------------

			using T = typename Template::This;

			//-----------------------------------------------------------------

			static constexpr Variable (Variable::*_not)() const = def_not<T, has_not>::v;
			static constexpr Variable (Variable::*_pos)() const = def_pos<T, has_pos>::v;
			static constexpr Variable (Variable::*_neg)() const = def_neg<T, has_neg>::v;
			static constexpr Variable (Variable::*_inv)() const = def_inv<T, has_inv>::v;
			static constexpr Variable (Variable::*_inc)() const = def_inc<T, has_inc>::v;
			static constexpr Variable (Variable::*_dec)() const = def_dec<T, has_dec>::v;

			//-----------------------------------------------------------------

			static constexpr Variable (Variable::*_gt)(const Variable &) const = def_gt<T, has_gt>::v;
			static constexpr Variable (Variable::*_lt)(const Variable &) const = def_lt<T, has_lt>::v;
			static constexpr Variable (Variable::*_eq)(const Variable &) const = def_eq<T, has_eq>::v;
			static constexpr Variable (Variable::*_ne)(const Variable &) const = def_ne<T, has_ne>::v;
			static constexpr Variable (Variable::*_ge)(const Variable &) const = def_ge<T, has_ge>::v;
			static constexpr Variable (Variable::*_le)(const Variable &) const = def_le<T, has_le>::v;

			//-----------------------------------------------------------------

			static constexpr Variable (Variable::*_asg)(const Variable &) const = def_asg<T, has_asg>::v;
			static constexpr Variable (Variable::*_add)(const Variable &) const = def_add<T, has_add>::v;
			static constexpr Variable (Variable::*_sub)(const Variable &) const = def_sub<T, has_sub>::v;
			static constexpr Variable (Variable::*_mul)(const Variable &) const = def_mul<T, has_mul>::v;
			static constexpr Variable (Variable::*_div)(const Variable &) const = def_div<T, has_div>::v;
			static constexpr Variable (Variable::*_mod)(const Variable &) const = def_mod<T, has_mod>::v;
			static constexpr Variable (Variable::*_ban)(const Variable &) const = def_ban<T, has_ban>::v;
			static constexpr Variable (Variable::*_bor)(const Variable &) const = def_bor<T, has_bor>::v;
			static constexpr Variable (Variable::*_xor)(const Variable &) const = def_xor<T, has_xor>::v;
			static constexpr Variable (Variable::*_lan)(const Variable &) const = def_lan<T, has_lan>::v;
			static constexpr Variable (Variable::*_lor)(const Variable &) const = def_lor<T, has_lor>::v;
			static constexpr Variable (Variable::*_lsh)(const Variable &) const = def_lsh<T, has_lsh>::v;
			static constexpr Variable (Variable::*_rsh)(const Variable &) const = def_rsh<T, has_rsh>::v;
			static constexpr Variable (Variable::*_sbs)(const Variable &) const = def_sbs<T, has_sbs>::v;
			static constexpr Variable (Variable::*_fcn)(const Variable &) const = def_fcn<T, has_fcn>::v;

			//-----------------------------------------------------------------

			static constexpr Variable (Variable::*_cmp_add)(const Variable &) const = def_cmp_add<T, has_cmp_add>::v;
			static constexpr Variable (Variable::*_cmp_sub)(const Variable &) const = def_cmp_sub<T, has_cmp_sub>::v;
			static constexpr Variable (Variable::*_cmp_mul)(const Variable &) const = def_cmp_mul<T, has_cmp_mul>::v;
			static constexpr Variable (Variable::*_cmp_div)(const Variable &) const = def_cmp_div<T, has_cmp_div>::v;
			static constexpr Variable (Variable::*_cmp_mod)(const Variable &) const = def_cmp_mod<T, has_cmp_mod>::v;
			static constexpr Variable (Variable::*_cmp_ban)(const Variable &) const = def_cmp_ban<T, has_cmp_ban>::v;
			static constexpr Variable (Variable::*_cmp_bor)(const Variable &) const = def_cmp_bor<T, has_cmp_bor>::v;
			static constexpr Variable (Variable::*_cmp_xor)(const Variable &) const = def_cmp_xor<T, has_cmp_xor>::v;

	};

	//-------------------------------------------------------------------------

	template <class Template>
	TypeInfo::TypeInfo(const Template &type) {

		//---------------------------------------------------------------------

		INTERPRETER_UNUSED(type);

		//---------------------------------------------------------------------

		using T = typename Template::This;

		//---------------------------------------------------------------------

		using StaticCastList = typename Template::StaticCastList;
		using VtableCastList = typename Template::VtableCastList;

		//---------------------------------------------------------------------

		id = INTERPRETER_TYPEID(T);

		//---------------------------------------------------------------------

		name = INTERPRETER_TYPENAME(T);

		//---------------------------------------------------------------------

		is_const = TypeTraits<T>::is_const;

		//---------------------------------------------------------------------

		operators._new = &Template::operator new;
		operators._del = &Template::operator delete;

		//---------------------------------------------------------------------

		operators._not = TemplateInfo<Template>::_not;
		operators._pos = TemplateInfo<Template>::_pos;
		operators._neg = TemplateInfo<Template>::_neg;
		operators._inv = TemplateInfo<Template>::_inv;

		//---------------------------------------------------------------------

		operators._gt = TemplateInfo<Template>::_gt;
		operators._lt = TemplateInfo<Template>::_lt;
		operators._eq = TemplateInfo<Template>::_eq;
		operators._ne = TemplateInfo<Template>::_ne;
		operators._ge = TemplateInfo<Template>::_ge;
		operators._le = TemplateInfo<Template>::_le;

		//---------------------------------------------------------------------

		operators._asg = TemplateInfo<Template>::_asg;
		operators._add = TemplateInfo<Template>::_add;
		operators._sub = TemplateInfo<Template>::_sub;
		operators._mul = TemplateInfo<Template>::_mul;
		operators._div = TemplateInfo<Template>::_div;
		operators._mod = TemplateInfo<Template>::_mod;
		operators._ban = TemplateInfo<Template>::_ban;
		operators._bor = TemplateInfo<Template>::_bor;
		operators._xor = TemplateInfo<Template>::_xor;

		//---------------------------------------------------------------------

		operators._inc = TemplateInfo<Template>::_inc;
		operators._dec = TemplateInfo<Template>::_dec;

		//---------------------------------------------------------------------

		operators._lan = TemplateInfo<Template>::_lan;
		operators._lor = TemplateInfo<Template>::_lor;
		operators._lsh = TemplateInfo<Template>::_lsh;
		operators._rsh = TemplateInfo<Template>::_rsh;
		operators._sbs = TemplateInfo<Template>::_sbs;
		operators._fcn = TemplateInfo<Template>::_fcn;

		//---------------------------------------------------------------------

		operators._cmp_add = TemplateInfo<Template>::_cmp_add;
		operators._cmp_sub = TemplateInfo<Template>::_cmp_sub;
		operators._cmp_mul = TemplateInfo<Template>::_cmp_mul;
		operators._cmp_div = TemplateInfo<Template>::_cmp_div;
		operators._cmp_mod = TemplateInfo<Template>::_cmp_mod;
		operators._cmp_ban = TemplateInfo<Template>::_cmp_ban;
		operators._cmp_bor = TemplateInfo<Template>::_cmp_bor;
		operators._cmp_xor = TemplateInfo<Template>::_cmp_xor;

		//---------------------------------------------------------------------

		TemplateToTypeInitializer<T, StaticCastList>::init(stc_cast._traits, stc_cast._fcn);
		TemplateToTypeInitializer<T, VtableCastList>::init(vtb_cast._traits, vtb_cast._fcn);

	}

	//-------------------------------------------------------------------------

	template <class T>
	Variable::Variable(T value) {
		static_assert(!std::is_same<Template<T>, void>::value, "Variable::Variable(): type template is not defined.");
		this->data = Template<T>::operator new(sizeof(T), value);
		this->type_info = TypeInfo(Template<T>());
	}

	//-------------------------------------------------------------------------

	class TypeTemplateVoid {

		public:

			typedef void This;

			//-----------------------------------------------------------------

			typedef void StaticCastList;
			typedef void VtableCastList;

			//-----------------------------------------------------------------

			TypeTemplateVoid() {}
			TypeTemplateVoid(const Variable &) {}

			//-----------------------------------------------------------------

			void *operator new(size_t) { return NULL; }
			void  operator delete(void *) {}

	};

	//-------------------------------------------------------------------------

	template <>
	struct TypeToTemplate <void> {
		typedef TypeTemplateVoid Template;
	};

	//-------------------------------------------------------------------------

	class TypeTemplateInitializerList {

		public:

			typedef InitializerList<Variable> This;

			//-----------------------------------------------------------------

			typedef void StaticCastList;
			typedef void VtableCastList;

			//-----------------------------------------------------------------

			TypeTemplateInitializerList() {}
			TypeTemplateInitializerList(const Variable &v) : instance((This *)v) {}

			//-----------------------------------------------------------------

			void *operator new(size_t) { return new This(); }
			void *operator new(size_t, This value) { return new This(value); }

			//-----------------------------------------------------------------

			void  operator delete(void *value) { delete (This *)value; }

			//-----------------------------------------------------------------

			Variable operator [](const Variable &v) {
				int &index = (int &)(v.toType<int>());
				if(index >= instance->size() || index < 0)
					error("TypeTemplateInitializerList::operator [](const Variable &): index out of range.");
				return *(instance->begin() + index);
			}

			//-----------------------------------------------------------------

			Variable operator =(const Variable &v) { return Variable(*(instance) = (This &)(v.toType<This>())); }

		private:

			This *instance = NULL;

	};

	//-------------------------------------------------------------------------

	template <>
	struct TypeToTemplate <InitializerList<Variable>> {
		typedef TypeTemplateInitializerList Template;
	};

	//-------------------------------------------------------------------------

}














































