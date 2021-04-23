# Haxe Clipboard

This is a native library to read clipboard data from Haxe.
It uses [Ammer](https://github.com/Aurel300/ammer/) to generate bindings.

Note: This is a Windows only library for now!

## TODO

PR welcome :)
- [ ] fix hl
- [ ] add linux
- [ ] add mac
- [ ] write clipboard
- [ ] ship haxelib with dlls

---
 - [Install](#install)
 - [API](#API)
 - [Directory structure](#directory-structure)
 - [Building the native library](#building-the-native-library)
   - [On Windows](#on-windows)
 - [Building the Sample Haxe project](#building-the-sample-haxe-project)
 - [Running](#running)
   - [On Windows](#on-windows-1)
 - [Troubleshooting](#troubleshooting)
 
## Install

`haxelib install native-clipboard`

If you want to use with OpenFl, you just have to add this to your `project.xml`:

`<haxelib name="native-clipboard"/>`

If you want the last version of native-clipboard, you can install with git:

`haxelib git native-clipboard https://github.com/loudoweb/native-clipboard.git`

But you will also have to build the dll by yourself (see [building native library](#building-the-native-library))

## API

```haxe
//example: get an image with openfl
var bytes = Clipboard.get_image();
if(bytes != null && bytes.length > 0)
{
	bd = BitmapData.fromBytes(bytes);
}

//example: get an html text
var htmlstr = Clipboard.get_data(EClipboard.TYPE_HTML);

//example: get a svg
var svgstr = Clipboard.get_data(EClipboard.TYPE_SVG);

//example: get a pdf
var svgstr = Clipboard.get_bytes(EClipboard.TYPE_AI);
```

## Directory structure

 - [`haxe/extension`](haxe/extension)
	- [`Clipboard.hx`](haxe/extension/Clipboard.hx) - `ammer` library definition for the `Clipboard` library. This class essentially maps Haxe types to the C library.
	- [`EClipboard.hx`](haxe/extension/EClipboard.hx) - helper class: some types you may encounter in clipboard.
 - [`Sample.hx`](Sample.hx) - sample using the library in regular Haxe code.
 - [`build-common.hxml`](build-common.hxml) - build configuration common to all targets.
 - [`build-cpp.hxml`](build-cpp.hxml) - build configuration for hxcpp.
 - [`build-hl.hxml`](build-hl.hxml) - build configuration for HashLink. Must be call from VS developer prompt.
 - [`build-cpp.bat`](build-cpp.bat) - executable to build hxcpp.
 - [`build-hl.bat`](build-hl.bat) - executable to build hl. Must be call from VS developer prompt.
 - [`include.xml`](include.xml) - Lime/OpenFl extension
 - [`native`](native) - contains sources to the `clipboard` library.
   - [`clipboard.c`](native/clipboard.c)
   - [`clipboard.h`](native/clipboard.h)
   - [`Makefile.win`](native/Makefile.win) - build script for building the library on Windows (using MSVC). Must be call from x86 VS developer prompt.
   - [`Makefile64.win`](native/Makefile.win) - build script for building the library on Windows (using MSVC). Must be call from x64 VS developer prompt.
   - [`build_windows.bat`](native/build_windows.bat) - executable that call the makefile. Must be call from x86 VS developer prompt.
   - [`build_windows64.bat`](native/build_windows64.bat) - executable that call the makefile. Must be call from x64 VS developer prompt.
 - [`library`](library) - contains dlls in different folder depending on OS/architecture.

## Building the native library

Execute native/Makefile from VS developer prompt.

### On Windows

Assuming [MSVC](https://visualstudio.microsoft.com/downloads/) is set up on the local machine, navigate to the `native` directory in a Visual Studio Developer Command Prompt, then use the provided `Makefile.win`:

```bash
$ cd <path to poc directory>/native
$ nmake /F Makefile.win
```

This should create (among others) the files `clipboard.dll` and `clipboard.lib` in the `native` directory.

If you want to compile dll for 32bit, use the x86 VS developer prompt, and the x64 VS developer prompt to compile for 64 bit.

## Building the Sample Haxe project

Once the native library is built, the Haxe project itself can be compiled. The necessary configuration is already provided in the HXML files. Some targets require additional configuration, which needs to be provided on the command line via a define. See the [target-specific configuration](https://github.com/Aurel300/ammer#target-specifics) section in the main README for more information about these defines.

You can execute the build_{target}.bat.

Note: HL bat needs to be executed from VS developer prompt.

## Running

`ammer` works with dynamic libraries (except on hxcpp on Windows), which must either be distributed alongside with the program or already be present on the system. 


### On Windows

```bash
$ cp native/adder.dll bin/hl
$ cd bin/hl
$ hl sample.hl
```

```bash
$ cd bin/cpp
$ ./Main
```


## Troubleshooting

Due to issue in ammer library, clipboard is not working on hl yet.

#### "hl.h": no such file or directory

This error can occur during the build phase when targeting HashLink. It indicates that the native compiler cannot find the `hl.h` header file. Use the [`ammer.hl.hlInclude`](https://github.com/Aurel300/ammer#ammerhlhlinclude-ammerhlhllibrary-optional) option to point the compiler to a directory containing the `hl.h` file.

 - When using HashLink binary distributions, the directory is `include` in the downloaded folder.
 - When using HashLink built from source, the directory is `src` in the repository root.

#### "stddef.h": no such file or directory

This error can occur during the build phase when using MSVC on Windows. It indicates that the native compiler cannot find header files of the C standard library. To solve this:

 - Either use the "Visual Studio Developer Command Prompt"; or
 - Use a regular command-line prompt, but use the [`vcvars32` script](https://stackoverflow.com/questions/42805662/vsvars32-bat-in-visual-studio-2017) to initialise the environment.

#### Failed to load library clipboard.hdll

This error can occur when testing HashLink for two reasons (possibly both at the same time):

##### 1. `clipboard.hdll` is not in the CWD

The `hl` command will look for `hdll` files in the current working directory as well as the system library directories. Therefore, if `clipboard.hdll` is in the `bin/hl` directory (which is the case if the default configuration of this project is used), invoking `hl` from the `samples/poc` directory will NOT work.

 - Either `cd bin/hl` before invoking `hl`; or
 - Copy `clipboard.hdll` from `bin/hl` into the current working directory.

##### 2. The dynamic library cannot be found

Refer to the next section.

#### Image not found / Library not loaded

This error can occur when the system cannot find the compiled native library (`.dll`, `.dylib`, or `.so` file).

On Windows, the system will look for `dll` files in the current working directory.

 - Copy `clipboard.dll` from the `native` directory into the current working directory.

On OS X and Linux, the dynamic linker needs to be told where to look for additional dynamic libraries with an environment variable.

 - On OS X, prepend `DYLD_LIBRARY_PATH=<path to samples/poc/native>` to the command, e.g. `DYLD_LIBRARY_PATH=../../native hl sample.hl`.
 - On Linux, prepend `LD_LIBRARY_PATH=<path to samples/poc/native>` to the command, e.g. `LD_LIBRARY_PATH=../../native hl sample.hl`.

See also [general notes about dynamic libraries](https://github.com/Aurel300/ammer#general-notes-about-dynamic-libraries) in the main README.
