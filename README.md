# BCLib

A library of general purpose C stuff


## Description

Plenty of it pulled from Zed Shaw's "Learn C the Hard Way"


Building
--------

```bash
cd build
cmake ..
make
make test
```

Installing
----------

Everything should be setup to 'just work', with CMake handling installing the lib and headers to the right place.
```bash
make install
```

## Docker

The docker image is to test building and installing on linux.

``` bash
docker build . -t bclib
```

## Contact

Drop me an email at guy@rumblesan.com


## License

BSD License.

