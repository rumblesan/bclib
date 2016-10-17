FROM debian:8.6

MAINTAINER Guy John <guy@rumblesan.com>

RUN apt-get update
RUN apt-get install -y clang cmake make

ENV CC /usr/bin/clang

COPY . /opt/bclib

WORKDIR /opt/bclib/build

RUN cmake ..; make; make test; make install

CMD ["true"]
