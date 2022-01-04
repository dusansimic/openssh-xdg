#!/bin/sh

mkdir build-debian
cd build-debian

../configure --with-xdg-dirs --prefix=$(pwd)/../debian && make && make install

cd ..
dpkg-deb --build debian
mv debian.deb openssh-xdg.deb

rm -r build-debian
