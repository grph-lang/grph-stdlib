#  GRPH Standard Library

This is the repository of the GRPH standard library, which is used by the compiler when using IRGen.

Supports macOS and Linux.

## Install

### Dynamic library

To install it, simply run `make; sudo make install`. This will install it under `/usr/local/lib/libgrph.so` (or .dylib for macOS).

On Linux, make sure `/usr/local/lib` is in your dynamic ld search path (check `/etc/ld.so.conf`)

The compiler will then automatically dynamically link with it when creating executables.

### Static library

If you don't want to install it, you can also build it as a static library. Run `make libgrph.a`.

You will then have to manually link with it :

```bash
grph compile myscript.grph -o myscript.o
clang -o myscript myscript.o -L /path/to/stdlib/directory
```

## Usage

You shouldn't use it directly, it should only be used by GRPH code.
