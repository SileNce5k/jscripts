#!/usr/bin/env bash


CXX=${CXX:-g++}
CC=${CC:-gcc}
CFLAGS=${CFLAGS:-}
CXXFLAGS=${CXXFLAGS:-}

compile_c_files() {
    local strict=$1
    for file in *.c; do
        if [[ -f "$file" ]]; then
            filename=$(basename "$file")
            extension="${filename##*.}"
            filename="${filename%.*}"
            executable="c_$filename"
            if [[ "$file" -nt "$executable" ]]; then
                if $CC $CFLAGS $strict -o "$executable" "$file"; then
                    if [[ "$OSTYPE" == "msys" ]]; then
                        executable="$executable.exe"
                    fi
                    echo "Compiled $file to $executable"
                else
                    echo -e "\e[31mCompilation failed for $file\e[0m"
                fi
            else
                echo "$file is up to date"
            fi
        fi
    done
}

compile_cpp_files() {
    local strict=$1
    for file in *.cpp; do
        if [[ -f "$file" ]]; then
            filename=$(basename "$file")
            extension="${filename##*.}"
            filename="${filename%.*}"
            executable="cpp_$filename"
            if [[ "$file" -nt "$executable" ]]; then
                if $CXX $CXXFLAGS $strict -o "$executable" "$file"; then
                    if [[ "$OSTYPE" == "msys" ]]; then
                        executable="$executable.exe"
                    fi
                    echo "Compiled $file to $executable"
                else
                    echo -e "\e[31mCompilation failed for $file\e[0m"
                fi
            else
                echo "$file is up to date"
            fi
        fi
    done
}


if [[ "$1" == "--strict" ]]; then
    strict="-pedantic -Werror -Wall -Wextra"
else
    strict=""
fi


compile_c_files "$strict"


compile_cpp_files "$strict"
