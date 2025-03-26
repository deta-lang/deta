#!/bin/bash

# Disable automatic error handling
set +e

# Logging
LOG=0

# Directories
SRC_DIR="src"
OBJ_DIR="objects"
OUTPUT="deta"

# Compiler and flags (for C++)
CXX="clang++"
CXXFLAGS="-Wall -Wextra -O0 -g -fexceptions -std=c++17"

# LLVM
LLVM_COMPILE="$(llvm-config --cxxflags)"
LLVM_LINK="$(llvm-config --ldflags)"
LLVM_LIBS="$(llvm-config --libs)"

COMPILE_FLAGS="$CXXFLAGS"
LINK_LLVM=""

# Ensure object directory exists
mkdir -p "$OBJ_DIR"

# Find all .cpp files and compile only if needed
find "$SRC_DIR" -name "*.cpp" | while read -r src_file; do
    # Generate object file path with preserved subdirectories
    obj_file="$OBJ_DIR/${src_file#"$SRC_DIR/"}.o"
    obj_dir=$(dirname "$obj_file")  # Get directory part

    # Ensure object subdirectory exists
    mkdir -p "$obj_dir"

    if [[ "$LOG" -eq 1 ]]; then
        echo "$CXX $COMPILE_FLAGS -c $src_file -o $obj_file"
    fi

    # Check if .o file is missing or .cpp is newer
    if [[ ! -f "$obj_file" || "$src_file" -nt "$obj_file" ]]; then
        echo "Compiling $src_file -> $obj_file"
        $CXX $COMPILE_FLAGS -c "$src_file" -o "$obj_file"

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
$CXX $CXXFLAGS -o "$OUTPUT" $OBJS $LINK_LLVM

if [[ "$LOG" -eq 1 ]]; then
    echo "$CXX $CXXFLAGS -o \"$OUTPUT\" $OBJS $LINK_LLVM"
fi

# Manual error handling for linking
if [[ $? -ne 0 ]]; then
    echo "❌ Linking failed"
    exit 1
fi

echo "✅ Build complete!"