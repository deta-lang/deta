#!/bin/bash

# Disable automatic error handling
set +e

# Personal / Internal
LOG=0

# Directories
SRC_DIR="src"
OBJ_DIR="objects"
OUTPUT="deta"

# Compiler and flags
CC="clang"
CFLAGS="-Wall -Wextra -O2"

# LLVM
LLVM_COMPILE="$(llvm-config --cflags)"
LLVM_LINK="$(llvm-config --ldflags)"
LLVM_LIBS="$(llvm-config --libs)"

# Ensure object directory exists
mkdir -p "$OBJ_DIR"

# Find all .c files and compile only if needed
find "$SRC_DIR" -name "*.c" | while read -r src_file; do
    # Generate object file path with preserved subdirectories
    obj_file="$OBJ_DIR/${src_file#"$SRC_DIR/"}.o"
    obj_dir=$(dirname "$obj_file")  # Get directory part

    # Ensure object subdirectory exists
    mkdir -p "$obj_dir"

    if [[ "$LOG" -eq 1 ]]; then
        echo "$CC $CFLAGS $LLVM_COMPILE -c $src_file -o $obj_file"
    fi

    # Check if .o file is missing or .c is newer
    if [[ ! -f "$obj_file" || "$src_file" -nt "$obj_file" ]]; then
        echo "Compiling $src_file -> $obj_file"
        $CC $LLVM_COMPILE $CFLAGS -c "$src_file" -o "$obj_file"

        # Manual error handling
        if [[ $? -ne 0 ]]; then
            echo "❌ Compilation failed for $src_file"
            exit 1
        fi
    fi
done

# Link all object files into final executable
echo "Linking to $OUTPUT"
OBJS=$(find "$OBJ_DIR" -name "*.o")
$CC $CFLAGS -o "$OUTPUT" $OBJS

if [[ "$LOG" -eq 1 ]]; then
    echo "$CC $CFLAGS -o \"$OUTPUT\" $OBJS"
fi

# Manual error handling for linking
if [[ $? -ne 0 ]]; then
    echo "❌ Linking failed"
    exit 1
fi

echo "✅ Build complete!"