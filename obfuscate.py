#! /usr/bin/env python
import re

def read_c_program(filename):
    with open(filename, 'r') as file:
        return file.read()

def write_c_program(filename, code):
    with open(filename, 'w') as file:
        file.write(code)

# Example usage:
# c_code = read_c_program('input.c')
# write_c_program('output.c', c_code)


def obfuscate_code(code):
    variables = re.findall(r'\bint\s+(\w+)\b', code)
    obfuscated_code = code
    for i, var in enumerate(variables):
        obfuscated_code = obfuscated_code.replace(var, f'var_{i}')
    return obfuscated_code

# Example usage:
# obfuscated_code = obfuscate_code(c_code)


def shape_code(code, shape):
    lines = code.split('\n')
    shaped_code = []
    
    if shape == 'triangle':
        max_width = len(lines)
        for i in range(1, max_width + 1):
            shaped_code.append(' '.join(lines[:i]))
            lines = lines[i:]
            if not lines:
                break
        shaped_code = '\n'.join(shaped_code)
    else:
        shaped_code = '\n'.join(lines)
    
    return shaped_code

# Example usage:
# shaped_code = shape_code(obfuscated_code, 'triangle')


def main(input_file, output_file, shape):
    c_code = read_c_program(input_file)
    obfuscated_code = obfuscate_code(c_code)
    shaped_code = shape_code(obfuscated_code, shape)
    write_c_program(output_file, shaped_code)

if __name__ == '__main__':
    import sys
    if len(sys.argv) != 4:
        print("Usage: python obfuscate.py <input_file> <output_file> <shape>")
    else:
        main(sys.argv[1], sys.argv[2], sys.argv[3])
