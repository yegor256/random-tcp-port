[![Build Status](https://travis-ci.org/yegor256/random-tcp-port.svg?branch=master)](https://travis-ci.org/yegor256/random-tcp-port)

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

## Static Analysis

Even though this tool is really small, it uses all possible open source
static analysis tools I managed to find on the market, including:

 * [cpplint](http://en.wikipedia.org/wiki/Cpplint)
 * [cppcheck](http://cppcheck.sourceforge.net/)

If you know any others, feel free to submit a pull request.

## License

Licensed under the Apache License, Version 2.0.


[![Bitdeli Badge](https://d2weczhvl823v0.cloudfront.net/yegor256/random-tcp-port/trend.png)](https://bitdeli.com/free "Bitdeli Badge")

