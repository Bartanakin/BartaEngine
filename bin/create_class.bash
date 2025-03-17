#!/bin/bash

if [ -z "$1" ]; then
    echo "Usage: $0 <classname>"
    exit 1
fi

classname="$1"
root_path="/home/bartanakin/repos/BartaEngine"
current_path="$(pwd)"

if [[ "$current_path" != "$root_path/include"* ]]; then
    echo "Error: This script must be run within a subdirectory of $root_path."
    exit 1
fi

relative_path="$(echo "$current_path" | sed -n 's|.*\/include/||p')"
rootDirectoryNamespace="Barta::$(echo "$relative_path" | sed 's|/|::|g')"

# Create the header file
header_dir="$root_path/include/$relative_path"
header_file="$header_dir/$classname.h"

mkdir -p "$header_dir"

echo "#pragma once" > "$header_file"
echo "#include <pch.h>" >> "$header_file"
echo "" >> "$header_file"
echo "namespace $rootDirectoryNamespace {" >> "$header_file"
echo "    class $classname {" >> "$header_file"
echo "    };" >> "$header_file"
echo "}" >> "$header_file"

echo "Header file '$header_file' created successfully."

# Create the source directory if it doesn't exist
source_dir="$root_path/lib/$relative_path"
parent_source_dir="$(dirname "$source_dir")"

if [ ! -d "$source_dir" ]; then
    mkdir -p "$source_dir"
    echo "Created directory '$source_dir'"

    # Ensure the parent directory has a CMakeLists.txt
    parent_cmake_file="$parent_source_dir/CMakeLists.txt"
    if [ ! -f "$parent_cmake_file" ]; then
        touch "$parent_cmake_file"
        echo "Created parent CMakeLists.txt at '$parent_cmake_file'"
    fi

    # Add add_subdirectory if not already present
    dir_name="$(basename "$source_dir")"
    if ! grep -q "add_subdirectory($dir_name)" "$parent_cmake_file"; then
        echo "Adding add_subdirectory($dir_name) to $parent_cmake_file..."
        echo "" >> "$parent_cmake_file"
        echo "add_subdirectory($dir_name)" >> "$parent_cmake_file"
    fi
fi

# Define the CMakeLists.txt file path
cmake_file=""
if [ -f "$source_dir/CMakeLists.txt" ]; then
    cmake_file="$source_dir/CMakeLists.txt"
else
    cmake_file="$source_dir/CMakeLists.txt"
    touch "$cmake_file"
    echo "Created empty CMakeLists.txt in '$source_dir'"
fi

# Create the source file
source_file="$source_dir/$classname.cpp"

echo "#include <$relative_path/$classname.h>" > "$source_file"
echo "" >> "$source_file"
echo "namespace $rootDirectoryNamespace {" >> "$source_file"
echo "}" >> "$source_file"

echo "Source file '$source_file' created successfully."

# Ensure the source file is added to target_sources
if ! grep -q "target_sources(\${LIBRARY_NAME} PUBLIC" "$cmake_file"; then
    echo "Adding target_sources block to CMakeLists.txt..."
    echo -e "target_sources(\${LIBRARY_NAME} PUBLIC\n    $classname.cpp\n)" >> "$cmake_file"
else
    # Check if the source file is already in the list
    if ! grep -q "$classname.cpp" "$cmake_file"; then
        echo "Adding $classname.cpp to target_sources..."
        sed -i "/target_sources(\${LIBRARY_NAME} PUBLIC/a \    $classname.cpp" "$cmake_file"
    else
        echo "$classname.cpp is already in CMakeLists.txt."
    fi
fi

echo "CMakeLists.txt updated successfully."
