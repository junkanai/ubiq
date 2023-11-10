# ubiq

## rep.hpp

The header `ubiq/rep.hpp` offers repeat macros
You can use `rep` and `reps` instead of classic for statements.

```cpp:rep_example.cpp
int a[5] = {1, 2, 3, 4, 5};
int s = 0;
rep(i, 5) {
    s += a[i];
}
/* same as this code:
for ( size_t i = 0; i < 5; i++ ) {
    s += a[i]:
}
*/
print(s);  // sum of 1, 2, 3, 4 and 5
int p = 0;
reps(i, 2, 5) {
    p += a[i];
}
/* same as this code:
for ( size_t i = 2; i < 5; i++ ) {
    s += a[i]:
}
*/
print(p)  // sum of 3, 4 and 5
```

```txt:rep_example_out
15
12
```




## print.hpp

The header `ubiq/print.hpp` offers useful output ways.
The examples below are all under default settings.

* `print();` equals `std::printf("\n");`.

* `print(a);` outputs `a` (any primitive type variable) and `"\n"`.

* `print(a, b);` outputs `a` and `b` with separator ` ` and `"\n"`.
You can put any number of arguments.

* You can change default settings with `print.set_end(end)`, `print.set_sep(sep)` temporarily.
`print = print.set_end(end)` makes the change permanent.

* You can change integer output format with `print.set_int(format)` temporarily.
The format is C's printf style like `"%5d"` (default:`%3d`).

* You can change floating point output format with `print.set_flt(format)` temporarily.
The format is C's printf style like `"%.2f"` (default:`%f`).


## ubiq/ndarray\_ptr.hpp


