# Compiler paths
CC	?= gcc
NDKCC	?= aarch64-linux-android29-clang
ifeq ($(OS),Windows_NT)
WINCC	?= gcc
else
WINCC	?= x86_64-w64-mingw32-gcc
endif

# Compiler flags
CFLAGS	:= -Wall -O2 -s
LDFLAGS	:=

# Output directory
O := out

# Targets
TARGET_LINUX	:= $(O)/table_linux-x86_64
TARGET_WINDOWS	:= $(O)/table_windows-x86_64.exe
TARGET_ANDROID	:= $(O)/table_android-linux-arm64-v8a

# Source files
SRCS	:= src/main.c src/stack.c src/file.c src/prompt.c

.PHONY: all linux windows android clean mkdir_out

all: linux windows android

linux: $(TARGET_LINUX)
windows: $(TARGET_WINDOWS)
android: $(TARGET_ANDROID)

# Ensure /out exists
ifeq ($(OS),Windows_NT)
mkdir_out:
	@if not exist "$(O)" mkdir "$(O)"
else
mkdir_out:
	@mkdir -p "$(O)"
endif

# Linux build
$(TARGET_LINUX): $(SRCS) | mkdir_out
	$(CC) $(CFLAGS) $(SRCS) -o $@ $(LDFLAGS)

# Windows build
$(TARGET_WINDOWS): $(SRCS) | mkdir_out
	$(WINCC) $(CFLAGS) $(SRCS) -o $@ $(LDFLAGS)

# Android build
$(TARGET_ANDROID): $(SRCS) | mkdir_out
	$(NDKCC) $(CFLAGS) $(SRCS) -o $@ $(LDFLAGS)

ifeq ($(OS),Windows_NT)
clean:
	@if exist "out" ( rd /s /q "out" )
else
clean:
	@rm -rf out/*
endif
