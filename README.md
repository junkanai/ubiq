# ubiq

## ubiq/rep.hpp

`#define rep(i, n) for ( size_t i = 0; i < (size_t)(n); ++i )`
`#define reps(i, s, n) for ( size_t i = (s); i < (size_t)(n); ++i )`

## ubiq/print.hpp

The header `print.hpp` offers useful output ways.
The examples below are all under default settings.

* `print();` equals `std::printf("\n");`.

* `print(a);` outputs `a` (any primitive type variable) and `"\n"`.

* `print(a, b);` outputs separator ` ` between `a` and `b` and `"\n"`.
You can put any number of arguments.

* You can change default settings with `print.set_end(end)`, `print.set_sep(sep)` temporarily.
`print = print.set_end(end)` makes the change permanently.

* You can change integer output format with `print.set_int(format)` temporarily.
The format is C's printf style like `"%5d"` (default:`%3d`).

* You can change floating point output format with `print.set_flt(format)` temporarily.
The format is C's printf style like `"%.2f"` (default:`%f`).


## ubiq/ndarray\_ptr.hpp


