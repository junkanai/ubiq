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
outputs:
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


## ndarray\_ptr.hpp

The header `ubiq/ndarray_ptr.hpp` offers the wrapper class `ndarray_ptr`.

```cpp:rep_example.cpp
int orig[12] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 8};
ndarray<int, 10> a(orig + 2); // give the start point pointer
print = print.set_sep(", ");
print(a);
print(a[9], a[7]);
print(a.size(), a.max(), a.min(), a.sum(), a.mean<double>());

auto b = a.argsort(ndarray_ptr<size_t, 10>(new size_t[12]).seq());
print(b)
b.del()  // delete b memory data !!! Don't forget freeing allocated memory

print("sort_dsc:", a.sort())
print("sort_asc:", a.sort_asc())

print()

ndarray<int, 2, 3, 2> c(orig);
c.fill(1);
c(1, 2, 0) = 0;
c(0, 1, 1) = 2;
a[0] = 3;  // change using a
c[6] = 4;

print(c);
print(a);
```
outputs:
```txt:rep_example_out
[  4,   1,   5,   9,   2,   6,   5,   3,   5,   8]
  8,  3
 10,  9,  1,  48, 4.8
[  3,   9,   5,   2,   6,   8,   0,   7,   4,   1]
sort_dsc, [  9,   8,   6,   5,   5,   5,   3,   3,   2,   1]
sort_asc, [  1,   2,   3,   3,   5,   5,   5,   6,   8,   9]

[[[1, 1]
  [3, 2]
  [1, 1]]

 [[4, 1]
  [1, 1]
  [0, 1]]]
[  3,   2,   1,   1,   1,   1,   1,   1,   0,   1]
```


