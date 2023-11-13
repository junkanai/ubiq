#pragma once

template<class T = double>
T rnd(T from = -1.0, T to = 1.0) noexcept {
	static uint32_t x = 123456789;
	static uint32_t y = 362436069;
	static uint32_t z = 521288629;
	static uint32_t w = 88675123;

	uint32_t t = x ^ (x << 11);
	x = y; y = z; z = w;
	w ^= t ^ (t >> 8) ^ (w >> 19);

	return (T)(w) * (to - from) / UINT32_MAX + from;
}

template<class T = int>
T rndi(T to) noexcept {
	static uint32_t x = 123456789;
	static uint32_t y = 362436069;
	static uint32_t z = 521288629;
	static uint32_t w = 88675123;

	uint32_t t = x ^ (x << 11);
	x = y; y = z; z = w;
	w ^= t ^ (t >> 8) ^ (w >> 19);

	return (T)w % to;
}

bool rndb(float rate = 0.5) noexcept {
	static uint32_t x = 123456789;
	static uint32_t y = 362436069;
	static uint32_t z = 521288629;
	static uint32_t w = 88675123;

	uint32_t t = x ^ (x << 11);
	x = y; y = z; z = w;
	w ^= t ^ (t >> 8) ^ (w >> 19);

	return (rate * UINT32_MAX) > w;
}

