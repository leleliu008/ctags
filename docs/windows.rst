Building/hacking/using on MS-Windows
-----------------------------------------------------------------------------

:Maintainer: Frank Fesevur <ffes@users.sourceforge.net>

----

This part of the documentation is written by Frank Fesevur, co-maintainer of Universal Ctags and the maintainer of the Windows port of this project. It is still very much a work in progress. Things still need to be written down, tested or even investigated. When building for Windows you should be aware that there are many compilers and build environments available. This is a summary of available options and things that have been tested so far.


Compilers
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

There are many compilers for Windows. Compilers not mentioned here may work but are not tested.


Microsoft Visual Studio
.............................................................................
https://www.visualstudio.com/

Many professional developers targeting Windows use Visual Studio. Visual Studio comes in a couple of different editions. Their Express and Community editions are free to use, but a Microsoft-account is required to download the .iso and when you want to continue using it after a 30-days trial period. Other editions of Visual Studio must be purchased.

Installing Visual Studio will give you the IDE, the command line compilers and the MS-version of make named nmake.

Note that ctags cannot be built with Visual Studio older than 2013 anymore. There is C99 (or C11) coding used that generates syntax errors with VS2012 and older. This could affect compilers from other vendors as well.


GCC
.............................................................................

You can use `MinGW-w64 <https://www.mingw-w64.org/>`_ to build ctags. There are several ways to install MinGW-w64 in Windows.

- MSYS2 https://www.msys2.org/
- MinGW-w64 - for 32 and 64 bit Windows https://sourceforge.net/projects/mingw-w64/
- TDM-GCC https://jmeubank.github.io/tdm-gcc/

If you want to build a full-featured version, use MSYS2 (with Autotools). Otherwise, you can also use the other two distributions.

**History**

MinGW started it all, but development stalled for a while and no x64 was available. Then the MinGW-w64 fork emerged. It started as a 64-bit compiler, but soon they included both a 32-bit and a 64-bit compiler. But the name remained, a bit confusing. MinGW-w64 appears to be the most used flavor of MinGW at this moment. Many well known programs that originate from GNU/Linux use MinGW-w64 to compile their Windows port.

Building ctags from the command line
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Microsoft Visual Studio
.............................................................................

Microsoft Visual Studio provides ``Visual Studio Developer Command Prompt`` for command-line enthusiasts.

There are two ways to setup ``Visual Studio Developer Command Prompt``.

The first way to setup ``Visual Studio Developer Command Prompt`` is by clicking the ``Windows Start Menu``, details please refer to https://learn.microsoft.com/en-us/visualstudio/ide/reference/command-prompt-powershell?view=vs-2019

The second way to setup ``Visual Studio Developer Command Prompt`` is opening ``Command Prompt`` Application and calling ``vcvarsall.bat`` in current ``Command Prompt``.

The location of ``vcvarsall.bat`` is various for different Microsoft Visual Studio versions and editions.

For Microsoft Visual Studio 2022 Enterprise::

        C:\Program Files\Microsoft Visual Studio\2022\Enterprise\VC\Auxiliary\Build\vcvarsall.bat

For Microsoft Visual Studio 2022 Community::

        C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat

For Microsoft Visual Studio 2019 Enterprise::

        C:\Program Files (x86)\Microsoft Visual Studio\2019\Enterprise\VC\Auxiliary\Build\vcvarsall.bat

For Microsoft Visual Studio 2019 Community::

        C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat

Following is an example shows you how to use ``vcvarsall.bat`` to setup ``Visual Studio Developer Command Prompt``::

        call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Enterprise\VC\Auxiliary\Build\vcvarsall.bat" x64

For more details about ``vcvarsall.bat`` please refer to https://learn.microsoft.com/en-us/cpp/build/building-on-the-command-line?view=msvc-160

Once ``Visual Studio Developer Command Prompt`` is setup, you can build ctags with ``NMake`` or ``MSBuild``.

Building ctags with NMake
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

This requires Microsoft Visual Studio 2019 or later.

The simplest build instructions like below::

        nmake -f mk_mvc.mak

If you want to build an iconv enabled version, you must specify ``WITH_ICONV=yes`` and ``ICONV_DIR`` like below::

        nmake -f mk_mvc.mak WITH_ICONV=yes ICONV_DIR=path/to/iconvlib

If you want to build a debug version using ``mk_mvc.mak``, you must specify ``DEBUG=1`` like below::

        nmake -f mk_mvc.mak DEBUG=1

If you want to create PDB files for debugging even for a release version, you must specify ``PDB=1`` like below::

        nmake -f mk_mvc.mak PDB=1

Building ctags with MSBuild
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

This supports only Microsoft Visual Studio 2013.

Before starting to build, you need to copy some files to proper location::

        copy win32\config_mvc.h config.h
        copy win32\gnulib_h\langinfo.h gnulib
        copy win32\gnulib_h\fnmatch.h gnulib

The simplest build instruction like below::

        msbuild win32\ctags_vs2013.sln

If you want to build a release version, run command like below::

        msbuild win32\ctags_vs2013.sln /p:Configuration=Release

MSBuild is what the IDE uses internally and therefore will produce the same files as the IDE.

For more information about MSBuild, please refer to https://learn.microsoft.com/en-us/visualstudio/msbuild/msbuild?view=vs-2019

GCC
.............................................................................

**General**

All the GCC's come with installers or with zipped archives. Install or extract them in a directory without spaces.

GNU Make builds for Win32 are available as well, and sometimes are included with the compilers. Make sure it is in your path, for instance by copying the make.exe in the bin directory of your compiler.

Native win32 versions of the GNU/Linux commands cp, rm and mv can be useful. rm is almost always used in by the ``clean`` target of a makefile.

**MSYS2**

From mingw.org: MSYS is a collection of GNU utilities such as bash, make, gawk and grep to allow building of applications and programs which depend on traditional UNIX tools to be present. It is intended to supplement MinGW and the deficiencies of the cmd shell.

MSYS2 is a more maintained version of MSYS, but specially geared towards MinGW-w64. You can also use Autotools to build ctags.
If you use Autotools you can enable parsers which require jansson, libxml2 or libyaml, and can also do the Units testing with ``make units``.
If you don't need such features, you can still build ctags without using Autotools: ``make -f mk_mingw.mak``.

The following packages are needed to build a full-featured version:

- base-devel (make, autoconf)
- mingw-w64-{i686,x86_64}-toolchain (mingw-w64-{i686,x86_64}-gcc, mingw-w64-{i686,x86_64}-pkg-config)
- mingw-w64-{i686,x86_64}-jansson
- mingw-w64-{i686,x86_64}-libxml2
- mingw-w64-{i686,x86_64}-libyaml
- mingw-w64-{i686,x86_64}-xz

If you want to build a single static-linked binary, you can use the following command:

.. code-block:: bash

        ./autogen.sh
        ./configure --disable-external-sort --enable-static
        make

``--disable-external-sort`` is a recommended option for Windows builds.

**Cygwin**

Cygwin provides ports of many GNU/Linux tools and a POSIX API layer. This is the most complete way to get the GNU/Linux terminal feel under Windows. Cygwin has a setup that helps you install all the tools you need. One drawback of Cygwin is that it has poor performance.

It is easy to build a Cygwin version of ctags using the normal GNU/Linux build steps. This ctags.exe will depend on cygwin1.dll and should only be used within the Cygwin ecosystem.

The following packages are needed to build a full-featured version:

- libiconv-devel
- libjansson-devel
- libxml2-devel
- libyaml-devel

Cygwin has packages with a recent version of MinGW-w64 as well. This way it is easy to cross-compile a native Windows application with ``make -f mk_mingw.mak  CC=i686-w64-mingw32-gcc``.

You can also build a native Windows version using Autotools.

.. code-block:: bash

	./autogen.sh
	./configure --host=i686-w64-mingw32 --disable-external-sort
	make

If you use Autotools you can also do the Units testing with ``make units``.

Some anti-virus software slows down the build and test process significantly, especially when ``./configure`` is running and during the Units tests. In that case it could help to temporarily disable them. But be aware of the risks when you disable your anti-virus software.

**Cross-compile from GNU/Linux**

All major distributions have both MinGW and MinGW-w64 packages. Cross-compiling works the same way as with Cygwin. You cannot do the Windows based Units tests on GNU/Linux.


Building ctags with IDEs
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

I have no idea how things work for the most GNU/Linux developers, but most of Windows developers prefer to use IDE over command prompt, running the debugger from the command line is not a thing a Windows developers would normally do. Many IDEs exist for Windows, I use the two below.

Microsoft Visual Studio
.............................................................................

As already mentioned Microsoft Visual Studio 2013 has the free Express and Community editions. For ctags the Windows Desktop Express Edition is enough to get the job done. The IDE has a proper debugger. Project files for VS2013 can be found in the win32 directory.

Please know that when files are added to the sources.mak, these files need to be added to the .vcxproj and .vcxproj.filters files as well. The XML of these files should not be a problem.

Code::Blocks
.............................................................................
http://www.codeblocks.org/

Code::Blocks is a decent GPL-licensed IDE that has good gcc and gdb integration. The TDM-GCC that can be installed together with Code::Blocks works fine and I can provide a project file. This is an easy way to have a free - free as in beer as well as in speech - solution and to have the debugger within the GUI as well.


Other differences between Microsoft Windows and GNU/Linux
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

There other things where building ctags on Microsoft Windows differs from building on GNU/Linux.

- Filenames on Windows file systems are case-preserving, but not case-sensitive.
- Windows file systems use backslashes ``"\"`` as path separators, but paths with forward slashes ``"/"`` are no problem for a Windows program to recognize, even when a full path (include drive letter) is used.
- The default line-ending on Windows is CRLF. A tags file generated by the Windows build of ctags will contain CRLF.
- The tools used to build ctags do understand Unix-line endings without problems. There is no need to convert the line-ending of existing files in the repository.
- Due to the differences between the GNU/Linux and Windows C runtime library there are some things that need to be added to ctags to make the program as powerful as it is on GNU/Linux. At this moment regex and fnmatch are borrowed from glibc. mkstemp() is taken from MinGW-w64's runtime library. scandir() is taken from `Pacemaker <https://github.com/ClusterLabs/pacemaker/blob/master/replace/scandir.c>`_.
- Units testing needs a decent ``bash`` shell, some unix-like tools (e.g. ``diff``, ``sed``) and Python 3.5 or later. It is only tested using Cygwin or MSYS2.
