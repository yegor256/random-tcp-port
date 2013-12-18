Reserve a random TCP port on POSIX-compatible system (Linux, Mac OS, Windows, etc). First, compile
it using `make`:

> make clean && make

Then, run without arguments:

> ./reserve

You should get a random TCP port number in standard output.

The tool first tries to allocate a random port in 5000-5099 interval. If
none of them are available, it will try to allocate a random in 1024-65535
interval. If after 400 attempts no ports are available it will exit
with a non-zero code (255) and print an error to stderr.

None of these parameters are configurable at the moment. You're welcome
to submit a pull request :)

## License

Licensed under the Apache License, Version 2.0.
