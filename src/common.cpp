#include "../include/common.h"

#ifdef __MINGW32__
#include <cxxabi.h>
#endif

namespace Interpreter {

	//-------------------------------------------------------------------------
	
	void error(const char *format, ...) {
		static char buffer[1024];
		va_list va;
		va_start(va, format);
		vsnprintf(buffer, sizeof(buffer), format, va);
		va_end(va);
		throw(buffer);
	}

	//-------------------------------------------------------------------------

	unsigned int hash(const Str &str) { return std::hash<Str>()(str); }
	
	//-------------------------------------------------------------------------

	#ifdef __MINGW32__

	Str mingw32_und_name(bool is_const, bool is_ref, bool is_ptr, const char *name) {
	    int status = -4;
	    std::unique_ptr<char, void(*)(void*)> undec_name {
	        abi::__cxa_demangle(name, NULL, NULL, &status),
	        std::free
	    };
	    if(status != 0) return name;
	    Str result = is_const ? "const " : "";
	    result += undec_name.get();
	    result += is_ref ? " &" : is_ptr ? " *" : "";
	    return result;
	}

	#endif

}
