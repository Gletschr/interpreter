#include "../include/tests.h"

#include <QElapsedTimer>


class Var {

	public:

	enum {
		INT,
		CHAR,
		BOOL
	};

	Var() {}
	Var(const Var &v) : type(v.type), data(v.data) {}
	Var(int v) : type(INT), data(new int(v)) {}
	Var(char v) : type(CHAR), data(new char(v)) {}
	Var(bool v) : type(BOOL), data(new bool(v)) {}

	inline operator int() const {
		switch(type) {
		case INT: return *(int *)data;
		case CHAR: return static_cast<int>(*(char *)data);
		case BOOL: return static_cast<int>(*(bool *)data);
		}
	}

	inline operator char() const {
		switch(type) {
		case INT: return static_cast<char>(*(int *)data);
		case CHAR: return *(char *)data;
		case BOOL: return static_cast<char>(*(bool *)data);
		}
	}

	inline operator bool() const {
		switch(type) {
		case INT: return static_cast<bool>(*(int *)data);
		case CHAR: return static_cast<bool>(*(char *)data);
		case BOOL: return *(bool *)data;
		}
	}

	inline Var operator <(const Var &v) const {
		switch(type) {
			case INT: return *(int *)data < (int)v;
			case CHAR: return *(char *)data < (char)v;
			case BOOL: return *(bool *)data < (bool)v;
		}
	}

	inline Var &operator ++() {
		switch(type) {
			case INT: ++*(int *)data; break;
			case CHAR: ++*(char *)data; break;
			case BOOL: ++*(bool *)data; break;
		}
		return *this;
	}

	private:

		unsigned int type;
		mutable void *data = NULL;

};

namespace Interpreter {

	//-------------------------------------------------------------------------

	bool benchmark() {

		try {

//			QElapsedTimer timer;

//			timer.start();
//			for(int i = 0; i < 500000; ++ i) {}
//			quint64 time = timer.elapsed();
//			qDebug() << "C++: " << time;

//			Variable size(500000);

//			timer.start();
//			for(Variable it = Variable(0); (bool &)(it < size); ++it) {}
//			time = timer.elapsed();
//			qDebug() << "Interpreter: " << time;

//			Var vs(500000);
//			timer.start();
//			for(Var it = Var(0); (bool)(it < vs); ++it) {}
//			time = timer.elapsed();
//			qDebug() << "Var: " << time;

		return true;

		} catch(const char *ex) {
			qDebug() << ex;
		}

		return false;
	}

	//-------------------------------------------------------------------------

}
