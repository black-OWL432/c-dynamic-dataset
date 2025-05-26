#!/bin/bash

# set -e

DIR=$(pwd)
OUTDIR="$DIR/out"

mkdir -p "$OUTDIR"
rm -rf "$OUTDIR/"*

build_pc() {
    # Build for Linux x86_64
    gcc -Wall -O2 -fPIC -fPIE -pie \
        -o "$OUTDIR/dataset_linux-x86_64" main.c

    [ -f "$OUTDIR/dataset_linux-x86_64" ] && echo "Build complete: dataset_linux-x86_64"

    # Build for Windows x86_64
    # sudo apt-get install mingw-w64
    x86_64-w64-mingw32-gcc -Wall -O2 -s \
        -o "$OUTDIR/dataset_windows-x86_64.exe" main.c

    [ -f "$OUTDIR/dataset_windows-x86_64.exe" ] && echo "Build complete: dataset_windows-x86_64.exe"
}

build_android() {
    # Build for android arm64-v8a
    [ -z "$ANDROID_NDK_HOME" ] && ANDROID_NDK_HOME=/opt/android-ndk
    $ANDROID_NDK_HOME/toolchains/llvm/prebuilt/linux-x86_64/bin/aarch64-linux-android21-clang -Wall -O2 -pie -fPIE -s \
        -o "$OUTDIR/dataset_android-arm64-v8a" main.c

    [ -f "$OUTDIR/dataset_android-arm64-v8a" ] && echo "Build complete: dataset_android-arm64-v8a"
}

case "$1" in
    "pc")
        build_pc
        ;;
    "android")
        shift
        export ANDROID_NDK_HOME="$1"
        build_android
        ;;
    *)
        build_pc
        build_android
        ;;
esac
