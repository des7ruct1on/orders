#!/bin/bash

function replace_in_makefiles() {
    local dir="$1"

    for file in "$dir"/Makefile*; do
        if [[ -f "$file" ]]; then
            echo "Replacing in file: $file"
            sed -i 's#\\#/#g' "$file"
        fi
    done

    for subdir in "$dir"/*; do
        if [[ -d "$subdir" ]]; then
            replace_in_makefiles "$subdir"
        fi
    done
}

if [[ $# -eq 0 ]]; then
    echo "Usage: $0 <directory>"
    exit 1
fi

directory="$1"

if [[ ! -d "$directory" ]]; then
    echo "Error: '$directory' is not a directory."
    exit 1
fi

replace_in_makefiles "$directory"
