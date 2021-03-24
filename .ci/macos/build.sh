#!/bin/bash -ex

set -o pipefail

export Qt5_DIR=$(brew --prefix)/opt/qt5
export PATH="/usr/local/opt/ccache/libexec:/usr/local/opt/llvm/bin:$PATH"
# ccache configurations
export CCACHE_CPP2=yes
export CCACHE_SLOPPINESS=time_macros

# export CC="ccache clang"
# export CXX="ccache clang++"
# export LDFLAGS="-L/usr/local/opt/llvm/lib"
# export CPPFLAGS="-I/usr/local/opt/llvm/include"

ccache -s

mkdir build && cd build
cmake .. -DCMAKE_OSX_ARCHITECTURES="arm64" -DCMAKE_OSX_DEPLOYMENT_TARGET="11" -DCMAKE_BUILD_TYPE=Release -DENABLE_QT_TRANSLATION=ON -DENABLE_WEB_SERVICE=OFF -DCITRA_ENABLE_COMPATIBILITY_REPORTING=${ENABLE_COMPATIBILITY_REPORTING:-"OFF"} -DENABLE_COMPATIBILITY_LIST_DOWNLOAD=ON -DUSE_DISCORD_PRESENCE=ON -DENABLE_FFMPEG_AUDIO_DECODER=OFF -DENABLE_FFMPEG_VIDEO_DUMPER=OFF -GNinja
ninja

ccache -s

ctest -VV -C Release
