#!/usr/bin/env python3
import argparse
import re
from pathlib import Path
from typing import List, Optional

expand_include_pattern = r"^#include *<(.*)>[ \t]*\/\/ *expand: true$"
pragma_pattern = r"^#pragma[ \t]*once$"


def find_header(header_name: str, search_paths: List[str]) -> Optional[Path]:
    for path in search_paths:
        abs_path = Path(path) / header_name
        if abs_path.is_file():
            return abs_path.absolute()
    return None


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("-I", "--include", action="append", type=str)
    parser.add_argument("-o", "--output", type=str)
    parser.add_argument("file", type=str)
    args = parser.parse_args()

    with open(args.output, "w") as out_file:
        out_file.write("// AUTO GENERATED FILE -- DO NOT EDIT!\n")
        file_stack = [(Path(args.file), int(0))]
        expanded_files = set([Path(args.file)])
        while file_stack:
            filename, offset = file_stack.pop()
            with open(filename) as f:
                f.seek(offset)
                while line := f.readline():
                    pragma_match = re.match(pragma_pattern, line)
                    if pragma_match is not None and not filename.samefile(args.file):
                        out_file.write("// ")

                    regex_match = re.match(expand_include_pattern, line)
                    if regex_match is None:
                        out_file.write(line)
                        continue
                    header_name = regex_match.group(1)
                    abs_path = find_header(header_name, args.include)
                    if abs_path is None:
                        out_file.write(line)
                        continue
                    if abs_path in expanded_files:
                        continue
                    file_stack.append((filename, f.tell()))
                    file_stack.append((abs_path, 0))
                    expanded_files.add(abs_path)
                    break
