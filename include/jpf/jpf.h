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
	int used = vsnprintf(const_cast<char *>(result.c_str()), n, fmt, arg);
	va_end(arg);
	result.erase(used);
#if __cplusplus >= 201103L || (defined(_MSC_VER) && _MSC_VER >= 1900)
	result.shrink_to_fit();
#else
	if (n > used) {
		try {
			result.reserve(0);
		}
		catch (...) {}
	}
#endif
	return result;
}

}	// end of namespace jpf


#endif 	// end of _JPF_JPF_H_
