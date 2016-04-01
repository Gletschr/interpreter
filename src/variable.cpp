#include "../include/variable.h"

namespace Interpreter {

	//-------------------------------------------------------------------------

	TypeInfo::TypeInfo() : TypeInfo(TypeTemplateVoid()) {}

	//-------------------------------------------------------------------------

	Variable::Variable() {}

	Variable::Variable(const Variable &v) {
		this->data = v.data;
		this->type_info = v.type_info;
		this->use_count = v.use_count;
		grab();
	}

	//-------------------------------------------------------------------------

	const TypeInfo &Variable::getType() const {
		return type_info;
	}

	unsigned int Variable::getUseCount() const {
		return *use_count;
	}

	//-------------------------------------------------------------------------

	void Variable::grab() {
		++(*use_count);
	}

	void Variable::free() {
		if(*use_count > 1) {
			release();
		} else {
			type_info.operators._del(data);
		}
		data = NULL;
		type_info = TypeInfo();
	}

	void Variable::release() {
		--(*use_count);
		use_count = Ptr<unsigned int>(new unsigned int(1));
	}

	//-------------------------------------------------------------------------

	Variable &Variable::operator =(const Variable &v) {
		free();
		this->data = v.data;
		this->type_info = v.type_info;
		this->use_count = v.use_count;
		grab();
	}

	//-------------------------------------------------------------------------

	Variable Variable::operator !() const {
		if(!type_info.operators._not) 
			error("Variable<%s>::operator !(): operator is not defined for this type.", type_info.name.c_str());
		return (this->*type_info.operators._not)();
	}

	Variable Variable::operator +() const {
		if(!type_info.operators._pos) 
			error("Variable<%s>::operator +(): operator is not defined for this type.", type_info.name.c_str());
		return (this->*type_info.operators._pos)();
	}

	Variable Variable::operator -() const {
		if(!type_info.operators._neg) 
			error("Variable<%s>::operator -(): operator is not defined for this type.", type_info.name.c_str());
		return (this->*type_info.operators._neg)();
	}

	Variable Variable::operator ~() const {
		if(!type_info.operators._inv) 
			error("Variable<%s>::operator ~(): operator is not defined for this type.", type_info.name.c_str());
		return (this->*type_info.operators._inv)();
	}

	//-------------------------------------------------------------------------

	Variable Variable::operator ++() const {
		if(!type_info.operators._inc) 
			error("Variable<%s>::operator ++(): operator is not defined for this type.", type_info.name.c_str());
		return (this->*type_info.operators._inc)();
	}

	Variable Variable::operator --() const {
		if(!type_info.operators._dec) 
			error("Variable<%s>::operator --(): operator is not defined for this type.", type_info.name.c_str());
		return (this->*type_info.operators._dec)();
	}

	//-------------------------------------------------------------------------

	Variable Variable::operator =(const Variable &v) const {
		if(!type_info.operators._asg) 
			error("Variable<%s>::operator =(const Variable &): operator is not defined for this type.", type_info.name.c_str());
		return (this->*type_info.operators._asg)(v);
	}

	Variable Variable::operator +(const Variable &v) const {
		if(!type_info.operators._add) 
			error("Variable<%s>::operator +(const Variable &): operator is not defined for this type.", type_info.name.c_str());
		return (this->*type_info.operators._add)(v);
	}

	Variable Variable::operator -(const Variable &v) const {
		if(!type_info.operators._sub) 
			error("Variable<%s>::operator -(const Variable &): operator is not defined for this type.", type_info.name.c_str());
		return (this->*type_info.operators._sub)(v);
	}

	Variable Variable::operator *(const Variable &v) const {
		if(!type_info.operators._mul) 
			error("Variable<%s>::operator *(const Variable &): operator is not defined for this type.", type_info.name.c_str());
		return (this->*type_info.operators._mul)(v);
	}

	Variable Variable::operator /(const Variable &v) const {
		if(!type_info.operators._div) 
			error("Variable<%s>::operator /(const Variable &): operator is not defined for this type.", type_info.name.c_str());
		return (this->*type_info.operators._div)(v);
	}

	Variable Variable::operator %(const Variable &v) const {
		if(!type_info.operators._mod) 
			error("Variable<%s>::operator %(const Variable &): operator is not defined for this type.", type_info.name.c_str());
		return (this->*type_info.operators._mod)(v);
	}

	Variable Variable::operator &(const Variable &v) const {
		if(!type_info.operators._ban) 
			error("Variable<%s>::operator &(const Variable &): operator is not defined for this type.", type_info.name.c_str());
		return (this->*type_info.operators._ban)(v);
	}

	Variable Variable::operator |(const Variable &v) const {
		if(!type_info.operators._bor) 
			error("Variable<%s>::operator |(const Variable &): operator is not defined for this type.", type_info.name.c_str());
		return (this->*type_info.operators._bor)(v);
	}

	Variable Variable::operator ^(const Variable &v) const {
		if(!type_info.operators._xor) 
			error("Variable<%s>::operator ^(const Variable &): operator is not defined for this type.", type_info.name.c_str());
		return (this->*type_info.operators._xor)(v);
	}

	Variable Variable::operator >(const Variable &v) const {
		if(!type_info.operators._gt) 
			error("Variable<%s>::operator >(const Variable &): operator is not defined for this type.", type_info.name.c_str());
		return (this->*type_info.operators._gt)(v);
	}

	Variable Variable::operator <(const Variable &v) const {
		if(!type_info.operators._lt) 
			error("Variable<%s>::operator <(const Variable &): operator is not defined for this type.", type_info.name.c_str());
		return (this->*type_info.operators._lt)(v);
	}

	//-------------------------------------------------------------------------

	Variable Variable::operator ==(const Variable &v) const {
		if(!type_info.operators._eq) 
			error("Variable<%s>::operator ==(const Variable &): operator is not defined for this type.", type_info.name.c_str());
		return (this->*type_info.operators._eq)(v);
	}

	Variable Variable::operator !=(const Variable &v) const {
		if(!type_info.operators._ne) 
			error("Variable<%s>::operator !=(const Variable &): operator is not defined for this type.", type_info.name.c_str());
		return (this->*type_info.operators._ne)(v);
	}

	Variable Variable::operator >=(const Variable &v) const {
		if(!type_info.operators._ge) 
			error("Variable<%s>::operator >=(const Variable &): operator is not defined for this type.", type_info.name.c_str());
		return (this->*type_info.operators._ge)(v);
	}

	Variable Variable::operator <=(const Variable &v) const {
		if(!type_info.operators._le) 
			error("Variable<%s>::operator <=(const Variable &): operator is not defined for this type.", type_info.name.c_str());
		return (this->*type_info.operators._le)(v);
	}

	Variable Variable::operator &&(const Variable &v) const {
		if(!type_info.operators._lan) 
			error("Variable<%s>::operator &&(const Variable &): operator is not defined for this type.", type_info.name.c_str());
		return (this->*type_info.operators._lan)(v);
	}

	Variable Variable::operator ||(const Variable &v) const {
		if(!type_info.operators._lor) 
			error("Variable<%s>::operator ||(const Variable &): operator is not defined for this type.", type_info.name.c_str());
		return (this->*type_info.operators._lor)(v);
	}

	Variable Variable::operator <<(const Variable &v) const {
		if(!type_info.operators._lsh) 
			error("Variable<%s>::operator <<(const Variable &): operator is not defined for this type.", type_info.name.c_str());
		return (this->*type_info.operators._lsh)(v);
	}

	Variable Variable::operator >>(const Variable &v) const {
		if(!type_info.operators._rsh) 
			error("Variable<%s>::operator >>(const Variable &): operator is not defined for this type.", type_info.name.c_str());
		return (this->*type_info.operators._rsh)(v);
	}

	Variable Variable::operator [](const Variable &v) const {
		if(!type_info.operators._sbs) 
			error("Variable<%s>::operator [](const Variable &): operator is not defined for this type.", type_info.name.c_str());
		return (this->*type_info.operators._sbs)(v);
	}

	Variable Variable::operator ()(const Variable &v) const {
		if(!type_info.operators._fcn) 
			error("Variable<%s>::operator ()(const Variable &): operator is not defined for this type.", type_info.name.c_str());
		return (this->*type_info.operators._fcn)(v);
	}

	//-------------------------------------------------------------------------
	
	Variable Variable::operator +=(const Variable &v) const {
		if(!type_info.operators._cmp_add) 
			error("Variable<%s>::operator +=(const Variable &): operator is not defined for this type.", type_info.name.c_str());
		return (this->*type_info.operators._cmp_add)(v);
	}

	Variable Variable::operator -=(const Variable &v) const {
		if(!type_info.operators._cmp_sub) 
			error("Variable<%s>::operator -=(const Variable &): operator is not defined for this type.", type_info.name.c_str());
		return (this->*type_info.operators._cmp_sub)(v);
	}

	Variable Variable::operator *=(const Variable &v) const {
		if(!type_info.operators._cmp_mul) 
			error("Variable<%s>::operator *=(const Variable &): operator is not defined for this type.", type_info.name.c_str());
		return (this->*type_info.operators._cmp_mul)(v);
	}

	Variable Variable::operator /=(const Variable &v) const {
		if(!type_info.operators._cmp_div) 
			error("Variable<%s>::operator /=(const Variable &): operator is not defined for this type.", type_info.name.c_str());
		return (this->*type_info.operators._cmp_div)(v);
	}

	Variable Variable::operator %=(const Variable &v) const {
		if(!type_info.operators._cmp_mod) 
			error("Variable<%s>::operator %=(const Variable &): operator is not defined for this type.", type_info.name.c_str());
		return (this->*type_info.operators._cmp_mod)(v);
	}

	Variable Variable::operator &=(const Variable &v) const {
		if(!type_info.operators._cmp_ban) 
			error("Variable<%s>::operator &=(const Variable &): operator is not defined for this type.", type_info.name.c_str());
		return (this->*type_info.operators._cmp_ban)(v);
	}

	Variable Variable::operator |=(const Variable &v) const {
		if(!type_info.operators._cmp_bor) 
			error("Variable<%s>::operator |=(const Variable &): operator is not defined for this type.", type_info.name.c_str());
		return (this->*type_info.operators._cmp_bor)(v);
	}

	Variable Variable::operator ^=(const Variable &v) const {
		if(!type_info.operators._cmp_xor) 
			error("Variable<%s>::operator ^=(const Variable &): operator is not defined for this type.", type_info.name.c_str());
		return (this->*type_info.operators._cmp_xor)(v);
	}

	//-------------------------------------------------------------------------

}

