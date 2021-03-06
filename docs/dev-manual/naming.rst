Naming conventions
==================

The conventions here should be applied to all new code, and with common sense
when modifying existing code.  For example, renaming a widely used, existing
function to follow these conventions may not be justified unless the whole code
is getting a rework.

Currently, this only documents the present state of the code: no particular
attempt has been made to consolidate the naming.

Files
-----

* C++ source files have a ``.cpp`` extension, C source files ``.c``, and
  headers for both use ``.h``.
* For source file :file:`{file}.c`/:file:`{file}.cpp`, declarations that are
  visible outside the source file should go into a correspondingly named
  header: :file:`{file}.h`.  Some code may deviate from this rule to improve
  readability and/or usability of the API, but this should then be clearly
  documented.

  There can also be a :file:`{file}_impl.h` file that declares classes or
  functions that are not accessible outside the module.  If the whole file only
  declares symbols internal to the module, then the :file:`_impl.h` suffix is
  omitted.

  In most cases, declarations that are not used outside a single source file
  are in the source file.
* Use suffix :file:`-doc.h` for files that contain only Doxygen documentation
  for some module or such, for cases where there is no natural single header
  for putting the documentation.
* For C++ files, prefer naming the file the same as the (main) class it
  contains.  Currently all file names are all-lowercase, even though class
  names contain capital letters.
  It is OK to use commonly known abbreviations, and/or omit the name of the
  containing directory if that would cause unnecessary repetition (e.g., as a
  common prefix to every file name in the directory) and the remaining part of
  the name is unique enough.
* Avoid having multiple files with the same name in different places within
  the same library.  In addition to making things harder to find, C++ source
  files with the same name can cause obscure problems with some compilers.
  Currently, unit tests are an exception to the rule (there is only one
  particular compiler that had problems with this, and a workaround is
  possible if/when that starts to affect more than a few of the test files).

Common guidelines for C and C++ code
------------------------------------

* Preprocessor macros should be all upper-case.  Do not use leading
  underscores, as all such names are reserved according to the C/C++ standard.
* Name include guards like ``GMX_DIRNAME_HEADERNAME_H``.
* Avoid abbreviations that are not obvious to a general reader.
* If you use acronyms (e.g., PME, DD) in names, follow the Microsoft policy on
  casing: two letters is uppercase (DD), three or more is lowercase (Pme).
  If the first letter would be lowercase in the context where it is used
  (e.g., at the beginning of a function name, or anywhere in a C function
  name), it is clearest to use all-lowercase acronym.

C code
------

* All function and variable names are lowercase, with underscores as word
  separators where needed for clarity.
* All functions that are part of the public API should start with ``gmx_``.
  Preferably, other functions should as well.
  Some parts of the code use a ``_gmx_`` prefix for internal functions, but
  strictly speaking, these are reserved names, so, e.g., a trailing underscore
  would be better.
* Old C code and changes to it can still use the hungarian notation for
  booleans and enumerated variable names, as well as enum values, where they
  are prefixed with ``b`` and ``e`` respectively, or you can gradually move
  to the C++ practice below. Whatever you choose, avoid complex abbreviations.

C++ code
--------

* Use CamelCase for all names.  Start types (such as classes, structs,
  typedefs and enum values) with a capital letter, other names (functions,
  variables) with a lowercase letter.
  You may use an all-lowercase name with underscores if your class closely
  resembles an external construct (e.g., a standard library construct) named
  that way.
* C++ interfaces are named with an ``I`` prefix, such as in ICommandLineModule.
  This keeps interfaces identifiable, without introducing too much clutter
  (as the interface is typically used quite widely, spelling out
  ``Interface`` would make many of the names unnecessarily long).
* Abstract base classes are typically named with an ``Abstract`` prefix.
* Member variables are named with a trailing underscore.
* Accessors for a variable ``foo_`` are named ``foo()`` and ``setFoo()``.
* Global variables are named with a ``g_`` prefix.
* Static class variables are named with a ``s_`` prefix.
* Global constants are often named with a ``c_`` prefix.
* If the main responsibility of a file is to implement a particular class,
  then the name of the file should match that class, except for possible
  abbreviations to avoid repetition in file names (e.g., if all classes within
  a module start with the module name, omitting or abbreviating the module
  name is OK).  Currently, all source file names are lowercase, but this
  casing difference should be the only difference.
* For new C++ code, avoid using the hungarian notation that is a descendant
  from the C code (i.e., the practice of using a ``b`` prefix for boolean
  variables and an ``e`` prefix for enumerated variables and/or values).
  Instead, make the names long with a good description of what they control,
  typically including a verb for boolean variables, like ``foundAtom``.
* Prefer class enums over regular ones, so that unexpected conversions to
  int do not happen.
* When using a non-class enum, prefer to include the name of the enumeration type
  as a base in the name of enum values, e.g., ``HelpOutputFormat_Console``,
  in particular for settings exposed to other modules.
* Prefer to use enumerated types and values instead of booleans as control
  parameters to functions. It is reasonably easy to understand what the
  argument ``HelpOutputFormat_Console`` is controlling, while it is almost
  impossible to decipher ``TRUE`` in the same place without checking the
  documentation for the role of the parameter.

The rationale for the trailing underscore and the global/static prefixes is
that it is immediately clear whether a variable referenced in a method is local
to the function or has wider scope, improving the readability of the code.

Code for GPUs
-------------

Rationale: on GPUs, using the right memory space is often performance critical.

* In CUDA device code ``sm_``, ``gm_``, and ``cm_`` prefixes are used for
  shared, global and constant memory. The absence of a prefix indicates
  register space. Same prefixes are used in OpenCL code, where ``sm_``
  indicates local memory and no prefixes are added to variables in private
  address space.
* Data transferred to and from host has to live in both CPU and GPU memory
  spaces. Therefore it is typical to have a pointer or container (in CUDA), or
  memory buffer (in OpenCL) in host memory that has a device-based counterpart.
  To easily distinguish these, the variables names for such objects are
  prefixed ``h_`` and ``d_`` and have identical names otherwise. Example:
  ``h_masses``, and ``d_masses``.
* In all other cases, pointers to host memory are not required to have the
  prefix ``h_`` (even in parts of the host code, where both host and device
  pointers are present). The device pointers should always have the prefix
  ``d_`` or ``gm_``.
* In case GPU kernel arguments are combined into a structure, it is preferred
  that all device memory pointers within the structure have the prefix ``d_``
  (i.e. ``kernelArgs.d_data`` is preferred to ``d_kernelArgs.data``,
  whereas both ``d_kernelArgs.d_data`` and ``kernelArgs.data`` are not
  acceptable).
* Note that the same pointer can have the prefix ``d_`` in the host code,
  and ``gm_`` in the device code. For example, if ``d_data`` is passed to
  the kernel as an argument, it should be aliased to ``gm_data`` in the
  kernel arguments list. In case a device pointer is a field of a passed
  structure, it can be used directly or aliased to a pointer with ``gm_``
  prefix (i.e. ``kernelArgs.d_data`` can be used as is or aliased to
  ``gm_data`` inside the kernel).
* Avoid using uninformative names for CUDA warp, thread, block indexes and
  their OpenCL analogs (i.e. ``threadIndex`` is preferred to ``i`` or
  ``atomIndex``).

Unit tests
----------

* Test fixtures (the first parameter to ``TEST``/``TEST_F``) are named with a
  ``Test`` suffix.
* Classes meant as base classes for test fixtures (or as names to be typedefed
  to be fixtures) are named with a ``TestBase`` or ``Fixture`` suffix.
* The CTest test is named with CamelCase, ending with ``Tests`` (e.g.,
  ``OptionsUnitTests``).
* The test binary is named with the name of the module and a ``-test`` suffix.
