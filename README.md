# walk

Walk a directory tree and print the name of every regular file.

Description
-----------

Walk traverses a directory hierarchy starting at `path`, which
defaults to the current directory, and prints the name of every
regular file.

It doesn't print the names of directories, and it skips directories
and files whose names start with a dot.

Installation
------------

Install walk into `/usr/local/bin` with the following command:

```console
$ make install
```

You can use `make PREFIX=/some/other/directory install` if you wish
to use a different destination. If you want to remove walk from
your system, use `make uninstall`.

Motivation
----------

While you can accomplish the same with `find`, `walk` is faster
because it does less work by focusing on one common use case. I
wrote it so that I could traverse deep file hierarchies in a fraction
of the time it takes `find` to complete.

Contributing
------------

If you find a bug, please create an issue detailing the ways to
reproduce it. If you have a suggestion, create an issue detailing
the use case.
