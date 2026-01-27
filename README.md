
![Project logo](https://horse64.org/img/spew3dlogo.png)

Welcome to Spew3D
=================

**Note**: this project is extremely unfinished, and will be
refactored soon to be part of the Horse64 project.

You've found **Spew3D**, a one-header file **retro 3D toolkit
for C.**

**Features:**

- Simple API,
- 2D and 3D graphics, image loading, sound, and more,
- Retro-style like PlayStation 1 or Nintendo64,
- Filesystem, multi-byte strings, etc., all unified,
- Wide platform support thanks to [SDL2](https://libsdl.org).

**Do not use if** it disturbs you that Spew3D:

- Can't do modern shader effects,
- Can't do modern realtime shadows,
- Can't handle modern higher poly counts.


Compiling and usage
-------------------

*(Get `spew3d.h` [from here](
https://codeberg.org/Spew3D/Spew3D/releases).)*

**Step 1:** Add `spew3d.h` into your project's code folder, and
put this in all your files where you want to use it from:

```
#include <spew3d.h>
```

**Step 2:** In only a single object file, add this define which
will make it contain the actual implementation code and not just its API:

```
#define SPEW3D_IMPLEMENTATION
#include <spew3d.h>
```

**Step 3:** When you link your final program, make sure to add [SDL2](
https://libsdl.org) to your linked libraries, unless you're using
the [option to not use SDL](https://codeberg.org/Spew3D/Spew3D/src/branch/main/#options).


Documentation
-------------

For now, please refer to the [header files](https://codeberg.org/Spew3D/Spew3D/src/branch/main/./include/) themselves
like [spew3d_init.h](https://codeberg.org/Spew3D/Spew3D/src/branch/main/./include/spew3d_init.h),
[spew3d_texture.h](https://codeberg.org/Spew3D/Spew3D/src/branch/main/./include/spew3d_texture.h), etc.
and the ['examples' folder](https://codeberg.org/Spew3D/Spew3D/src/branch/main/./examples/) for documentation.


Common compilation problems
---------------------------

**Question: Where is `spew3d.h`?**

*Answer: It's generated and not
directly in the repository, [see here](https://codeberg.org/Spew3D/Spew3D/src/branch/main/#compiling-usage).
If you want to get it from the repository,
check the [section on running tests](https://codeberg.org/Spew3D/Spew3D/src/branch/main/#run-tests).*

**Question: I am getting missing definitions for `fseeko64` or
`ftello64` on Linux, what's up with that?**

*Answer: You're likely including `spew3d.h` after something
that already included the `stdio.h` header but without the
flag for 64bit file support which Spew3D needs. To solve this,
either add `-D_FILE_OFFSET_BITS=64 -D_LARGEFILE64_SOURCE` to
your gcc or clang compiler flags for your project, or include
`spew3d.h` before whatever other header that pulls in `stdio.h`.*

**Question: I included this with `extern "C" {` in my C++
program via `g++` (or similar) and got tons of errors!**

*Answer: Currently, C++ is not supported. This is in part due
to some included dependencies like miniz not supporting it, sorry.*


Options
-------

Spew3D has some options which you can use via `-DSPEW3D_OPTION...`
with gcc/mingw, or defining them **before** including `spew3d.h`.
**WARNING: ENSURE THAT EVERY INCLUDE OF `spew3d.h` WILL HAVE
THE SAME OPTIONS DEFINED IN ADVANCE,** or things will break.

Available options:

- `SPEW3D_OPTION_DISABLE_DLLEXPORT`: If defined, Spew3D will
  not mark its functions for shared library symbol export.
  By default, it will.

- `SPEW3D_OPTION_DISABLE_SDL`: If defined, allows compiling
  with no need for SDL2 whatsoever. It will also disable all
  graphical functions and sound output, but all other functionality
  remains available. This includes image loading, audio decoding
  without actual playback, threading and file system helpers,
  the Virtual File System, and so on. Ideal for headless use!

- `SPEW3D_OPTION_DISABLE_SDL_HEADER`: If defined, while Spew3D
  will expect SDL2 to be present and linked, the program using
  and including Spew3D is expected NOT to include and use SDL2
  headers directly. As a consequence, all functions bridging
  SDL2 and Spew3D items, like creating a Spew3D window from an
  SDL2 window, will no longer be present.

- `SPEW3D_DEBUG_OUTPUT`: If defined, Spew3D will print out
  some amount of debug messages for internal diagnostics.


Run tests
---------

Currently, running the tests is only supported on Linux.
This will also generate the `spew3d.h` file if you checked out
the development version of Spew3D at `include/spew3d.h`.

To run the tests, install SDL2 and libcheck (the GNU unit
test library for C) and [valgrind](https://valgrind.org)
system-wide, then use: `make test`


License
-------

Spew3D is free and open-source (other than the logo which isn't
needed to use it), [see here for details](https://codeberg.org/Spew3D/Spew3D/src/branch/main/LICENSE.md).
It includes other projects baked in, see `vendor` folder in this
repository.


Supported platforms and compilers
---------------------------------

These compilers should work: GCC, MinGW, Clang.
**MSVC is unsupported,** use MinGW instead.

For Windows, supported versions are Vista or newer.
Linux with GLIBC is also regularly tested,
FreeBSD and macOS aren't but if issues are found they
should be fixable and pull requests for that are welcome.

It should be possible to get Spew3D running on most Unix systems
supported by SDL2 as well. **3D acceleration is not required.**

