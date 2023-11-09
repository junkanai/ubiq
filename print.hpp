#ifndef JUNKANAI_PRINT_HEADER

#define JUNKANAI_PRINT_HEADER

#include <iostream>

#include "rep.hpp"


template<class P, class T>
void prints(const P& p, const T& t) {
	if constexpr ( std::is_integral<T>() ) {
		std::printf(p.get_int().c_str(), t);
	} else if constexpr ( std::is_floating_point<T>() ) {
		std::printf(p.get_flt().c_str(), t);
	} else {
		std::cout << t;
	}
}


class Print {
private:
	std::string int_format = "%3d";
	std::string flt_format = "%f";
	std::string end_with = "\n";
	std::string sep_with = " ";

public:
	Print() {}
	void operator()() const { std::printf("\n"); }

	template<class T, class... U>
	void operator()(const T& t, const U&... u) const {
		prints(*this, t);
		std::cout << sep_with;
		operator()(u...);
	}

	template<class T>
	void operator()(const T& t) const {
		prints(*this, t);
		std::cout << end_with;
	}

	Print set_int(const std::string& format) const {
		Print rtn = *this;
		rtn.int_format = format;
		return rtn;
	}

	const std::string& get_int() const { return int_format; }

	Print set_flt(const std::string& format) const {
		Print rtn = *this;
		rtn.flt_format = format;
		return rtn;
	}
	
	const std::string& get_flt() const { return flt_format; }

	Print set_end(const std::string& end) const
	{
		Print rtn = *this;
		rtn.end_with = end;
		return rtn;
	}

	const std::string& get_end() const { return end_with; }

	Print set_sep(const std::string& sep) const
	{
		Print rtn = *this;
		rtn.sep_with = sep;
		return rtn;
	}

	const std::string& get_sep() const { return sep_with; }
};

Print print;

#endif /* JUNKANAI_PRINT_HEADER */


#ifdef JUNKANAI_NDARRAY_PTR_HEADER
#include "ndarray_ptr.hpp"
#endif /* JUNKANAI_NDARRAY_HEADER */
