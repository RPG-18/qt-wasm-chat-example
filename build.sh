#!/bin/bash

pushd frontend
mkdir build
pushd build
qmake CONFIG+=release ..
make

mv chat.html ../../ui
mv chat.js ../../ui
mv chat.wasm ../../ui
mv qtloader.js ../../ui
mv qtlogo.svg ../../ui

popd
popd

GOOS=linux GOARCH=amd64 go build -o chat.linux.amd64
rice append --exec chat.linux.amd64

GOOS=darwin GOARCH=amd64 go build -o chat.darwin.amd64
rice append --exec chat.darwin.amd64

GOOS=windows GOARCH=amd64  go build -o chat.windows.amd64
rice append --exec chat.windows.amd64
