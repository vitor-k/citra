#!/bin/sh -ex

brew update
brew unlink python@2 || true
rm '/usr/local/bin/2to3' || true
brew install p7zip llvm || true
brew install qt5 sdl2 ccache ffmpeg ninja
pip3 install macpack
