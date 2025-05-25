#!/bin/bash

# set -e

DIR=$(pwd)
OUTDIR="$DIR/out"

mkdir -p "$OUTDIR"
rm -rf "$OUTDIR/"*

# Build for Linux x86_64
gcc -Wall -O2 -fPIC -fPIE -pie \
    -o "$OUTDIR/dataset_linux-x86_64" main.c

[ -f "$OUTDIR/dataset_linux-x86_64" ] && echo "Build complete: dataset_linux-x86_64"

# Build for Windows x86_64
gcc -Wall -O2 -fPIC -fPIE -pie \
    -o "$OUTDIR/dataset_windows-x86_64.exe" main.c

[ -f "$OUTDIR/dataset_windows-x86_64.exe" ] && echo "Build complete: dataset_windows-x86_64.exe"
