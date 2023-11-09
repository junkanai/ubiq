#ifndef JUNKANAI_NDARRAY_PTR_HEADER

#define JUNKANAI_NDARRAY_PTR_HEADER

#include <cstddef>   /* for using size_t */
#include <algorithm>

#include "rep.hpp"


#define JUNKANAI_NDARRAY_PTR_ARGUMENTS_ASSERT static_assert((I > 1) && (J > 0) && (K > 0) && (L > 0), "invalid arguments: I, J, K, L of ndarray_ptr.")

template<class T, size_t I, size_t J = 1, size_t K = 1, size_t L = 1>
class ndarray_ptr {
private:
	using Self = ndarray_ptr<T, I, J, K, L>;
	static constexpr size_t D = L > 1 ? 4 : K > 1 ? 3 : J > 1 ? 2 : 1;  /* dimention */
	static constexpr size_t N = I*J*K*L;  /* size of this ndarray_ptr */
	T *data_;

public:
	/* constructor */
	ndarray_ptr() : data_(nullptr) { JUNKANAI_NDARRAY_PTR_ARGUMENTS_ASSERT; }
	ndarray_ptr(T* t) : data_(t) { JUNKANAI_NDARRAY_PTR_ARGUMENTS_ASSERT; }
	template<size_t I2, size_t J2, size_t K2, size_t L2>
	ndarray_ptr(ndarray_ptr<T, I2, J2, K2, L2>& other) : data_(other.begin()) { JUNKANAI_NDARRAY_PTR_ARGUMENTS_ASSERT; }

	/* delete memory */
	void del() { delete data_; data_ = nullptr; }

	void operator=(T* t) { data_ = t; }
	template<size_t I2, size_t J2, size_t K2, size_t L2>
	void operator=(ndarray_ptr<T, I2, J2, K2, L2>& other) { data_ = other.begin(); }

	void fill(T t = 0) noexcept { rep(n, N) data_[n] = t; }

	void seq(T step = 0, T start = 0) noexcept {
		rep(n, N) {
			data_[n] = start;
			start += step;
		}
	}

	T *const begin() noexcept { return data_; }
	const T *const begin() const noexcept { return data_; }
	T *const end() noexcept { return data_+N; }
	const T *const end() const noexcept { return data_+N; }
	T *const data() noexcept { return data_; }
	const T *const data() const noexcept { return data_; }
	T *const data(ptrdiff_t diff) noexcept { return data_+diff; }
	const T *const data(ptrdiff_t diff) const noexcept { return data_+diff; }

	T&       operator[](size_t i) noexcept { return data_[i]; }
	const T& operator[](size_t i) const noexcept { return data_[i]; }

	T& operator()(size_t i = 0, size_t j = 0, size_t k = 0, size_t l = 0) noexcept {
		if constexpr ( D == 4 ) return data_[i*(J*K*L) + j*(K*L) + k*L + l];
		if constexpr ( D == 3 ) return data_[i*(J*K) + j*K + k];
		if constexpr ( D == 2 ) return data_[i*J + j];
		if constexpr ( D == 1 ) return data_[i];
	}

	const T& operator()(size_t i = 0, size_t j = 0, size_t k = 0, size_t l = 0) const noexcept {
		if constexpr ( D == 4 ) return data_[i*(J*K*L) + j*(K*L) + k*L + l];
		if constexpr ( D == 3 ) return data_[i*(J*K) + j*K + k];
		if constexpr ( D == 2 ) return data_[i*J + j];
		if constexpr ( D == 1 ) return data_[i];
	}

	static constexpr size_t dim() { return D; }
	static constexpr size_t size() { return N; }
	static constexpr size_t xsize() { return D == 4 ? L : D == 3 ? K : D == 2 ? J : I; }
	static constexpr size_t ysize() { return D == 4 ? K : D == 3 ? J : D == 2 ? I : 1; }
	static constexpr size_t zsize() { return D == 4 ? J : D == 3 ? I : 1; }
	static constexpr size_t wsize() { return D == 4 ? I : 1; }

	T max() const { return *std::max_element(begin(), end()); }
	T min() const { return *std::min_element(begin(), end()); }
	size_t argmax() const { return std::distance(begin(), std::max_element(begin(), end())); }
	size_t argmin() const { return std::distance(begin(), std::min_element(begin(), end())); }

	template<class U = T>
	U sum() const noexcept {
		U rtn = 0;
		rep(n, N) rtn += data_[n];
		return rtn;
	}

	template<class U = T> U mean() const noexcept { return sum<U>() / N; }
	Self& reverse() { std::reverse(begin(), end()); return *this; }

	/* sort */
	Self& sort() { std::sort(data_, data_+N, std::greater<T>()); return *this; } // dsc
	Self& sort_asc() { std::sort(begin(), end()); return *this; } // asc

	ndarray_ptr<size_t, I, J, K, L> argsort(ndarray_ptr<size_t, I, J, K, L>& indices) const {  // dsc
		rep(n, N) indices[n] = n;
		std::sort(indices.begin(), indices.end(),
				[this](T left, T right) -> bool { return data_[left] > data_[right]; });
		return indices;
	}

	ndarray_ptr<size_t, I, J, K, L> argsort_asc(ndarray_ptr<size_t, I, J, K, L>& indices) const {  // asc
		rep(n, N) indices[n] = n;
		std::sort(indices.begin(), indices.end(),
				[this](T left, T right) -> bool { return data_[left] < data_[right]; });
		return indices;
	}

	Self& operator+=(T t) noexcept { rep(n, N) data_[n] += t; return *this; }
	Self& operator+=(const Self& s) noexcept { rep(n, N) data_[n] += s.data_[n]; return *this; }
	Self& operator-=(T t) noexcept { rep(n, N) data_[n] -= t; return *this; }
	Self& operator-=(const Self& s) noexcept { rep(n, N) data_[n] -= s.data_[n]; return *this; }
	Self& operator*=(T t) noexcept { rep(n, N) data_[n] *= t; return *this; }
	Self& operator*=(const Self& s) noexcept { rep(n, N) data_[n] *= s.data_[n]; return *this; }
	Self& operator/=(T t) { rep(n, N) data_[n] /= t; return *this; }
	Self& operator/=(const Self& s) { rep(n, N) data_[n] /= s.data_[n]; return *this; }

};




#endif  /* JUNKANAI_NDARRAY_PTR_HEADER */



#ifdef JUNKANAI_PRINT_HEADER
template<class P, class T, size_t I, size_t J, size_t K, size_t L>
void prints(const P& p, const ndarray_ptr<T, I, J, K, L>& t) {
	if constexpr ( ndarray_ptr<T, I, J, K, L>::dim() == 4 ) {
		std::cout << "[";
		rep(i, I) {
			if ( i != 0 ) std::cout << "\n\n\n ";
			std::cout << "[";
			rep(j, J) {
				if ( j != 0 ) std::cout << "\n\n  ";
				std::cout << "[";
				rep(k, K) {
					if ( k != 0 ) std::cout << "\n   ";
					std::cout << "[";
					rep(l, L) {
						if ( l != 0 ) std::cout << p.get_sep();
						prints(p, t(i, j, k, l));
					}
					std::cout << "]";
				}
				std::cout << "]";
			}
			std::cout << "]";
		}
		std::cout << "]";
	} else if constexpr ( ndarray_ptr<T, I, J, K, L>::dim() == 3 ) {
		std::cout << "[";
		rep(i, I) {
			if ( i != 0 ) std::cout << "\n\n ";
			std::cout << "[";
			rep(j, J) {
				if ( j != 0 ) std::cout << "\n  ";
				std::cout << "[";
				rep(k, K) {
					if ( k != 0 ) std::cout << p.get_sep();
					prints(p, t(i, j, k));
				}
				std::cout << "]";
			}
			std::cout << "]";
		}
		std::cout << "]";
	} else if constexpr ( ndarray_ptr<T, I, J, K, L>::dim() == 2 ) {
		std::cout << "[";
		rep(i, I) {
			if ( i != 0 ) std::cout << "\n ";
			std::cout << "[";
			rep(j, J) {
				if ( j != 0 ) std::cout << p.get_sep();
				prints(p, t(i, j));
			}
			std::cout << "]";
		}
		std::cout << "]";
	} else {
		std::cout << "[";
		rep(i, I) {
			if ( i != 0 ) std::cout << p.get_sep();
			prints(p, t(i));
		}
		std::cout << "]";
	}
}

#endif /* JUNKANAI_PRINT_HEADER */
