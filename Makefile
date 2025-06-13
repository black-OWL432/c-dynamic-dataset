# Compiler paths
CC		?= gcc
WINCC	?= x86_64-w64-mingw32-gcc
NDKCC	?= aarch64-linux-android29-clang

# Compiler flags
CFLAGS	:= -Wall -O2 -pie -fPIE -s
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
mkdir_out:
	@mkdir -p $(O)

# Linux build
$(TARGET_LINUX): $(SRCS) | mkdir_out
	$(CC) $(CFLAGS) $(SRCS) -o $@ $(LDFLAGS)

# Windows build
$(TARGET_WINDOWS): $(SRCS) | mkdir_out
	$(WINCC) $(CFLAGS) $(SRCS) -o $@ $(LDFLAGS)

# Android build
$(TARGET_ANDROID): $(SRCS) | mkdir_out
	$(NDKCC) $(CFLAGS) $(SRCS) -o $@ $(LDFLAGS)

clean:
	rm -rf $(O)/*
