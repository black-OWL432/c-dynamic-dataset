#!/bin/bash

# set -e

DIR="${0%/*}"
OUTDIR="$DIR/out"

mkdir -p "$OUTDIR"
rm -rf "$OUTDIR/"*

build_pc() {
    # Build for Linux x86_64
    gcc -Wall -O2 -fPIC -fPIE -pie \
        -o "$OUTDIR/table_linux-x86_64" "$DIR"/main.c

    [ -f "$OUTDIR/table_linux-x86_64" ] && echo "Build complete: table_linux-x86_64"

    # Build for Windows x86_64
    # sudo apt-get install mingw-w64
    x86_64-w64-mingw32-gcc -Wall -O2 -s \
        -o "$OUTDIR/table_windows-x86_64.exe" "$DIR"/main.c

    [ -f "$OUTDIR/table_windows-x86_64.exe" ] && echo "Build complete: table_windows-x86_64.exe"
}

build_android() {
    # Build for android arm64-v8a
    [ -z "$ANDROID_NDK_HOME" ] && ANDROID_NDK_HOME=/opt/android-ndk
    $ANDROID_NDK_HOME/toolchains/llvm/prebuilt/linux-x86_64/bin/aarch64-linux-android21-clang -Wall -O2 -pie -fPIE -s \
        -o "$OUTDIR/table_android-arm64-v8a" "$DIR"/main.c

    [ -f "$OUTDIR/table_android-arm64-v8a" ] && echo "Build complete: table_android-arm64-v8a"
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
