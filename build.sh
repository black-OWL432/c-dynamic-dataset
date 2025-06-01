#!/bin/bash

build_pc() {
    # Build for Linux x86_64
    make linux

    # Build for Windows x86_64
    # sudo apt-get install mingw-w64
    make windows
}

build_android() {
    # Build for android arm64-v8a
    [ -z "$ANDROID_NDK_HOME" ] && ANDROID_NDK_HOME=/opt/android-ndk
    export PATH="$ANDROID_NDK_HOME/toolchains/llvm/prebuilt/linux-x86_64/bin:$PATH"
    make android
}

case "$1" in
    "pc")
        build_pc
        ;;
    "android")
        shift
        ANDROID_NDK_HOME="$1"
        build_android
        ;;
    "clean")
        make clean
        ;;
    *)
        build_pc
        build_android
        ;;
esac
