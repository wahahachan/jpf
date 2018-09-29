#ifndef _JPF_JPF_H_
#define _JPF_JPF_H_

#include <cstdarg>	// variable argument
#include <cstdio>	// our lovely printf-like functions
#include <string>	// c++ string

namespace jpf {

std::string jsnprintf(int n, const char *fmt, ...) {
	va_list arg;
	va_start(arg, fmt);
	std::string result(n, '\0');
	vsnprintf(const_cast<char *>(result.c_str()), n, fmt, arg);
	va_end(arg);
	return result;
}

}	// end of namespace jpf


#endif 	// end of _JPF_JPF_H_
