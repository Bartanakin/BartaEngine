import sys
from fractions import Fraction

def format_number(x):
    f = float(Fraction(x))
    if f == 0.0:
        return "0"
    # Format to 5 decimal places and strip unnecessary zeros
    formatted = f"{f:.5f}".rstrip('0').rstrip('.')
    return formatted

def convert_to_latex(input_str):
    lines = input_str.strip().splitlines()
    formatted_lines = []

    for i, line in enumerate(lines):
        elements = line.strip().split()
        decimal_elements = [format_number(e) for e in elements]
        formatted_line = ' & '.join(decimal_elements)
        if i < len(lines) - 1:
            formatted_line += r'\\'
        formatted_lines.append(formatted_line)

    return '\n'.join(formatted_lines)

if __name__ == "__main__":
    input_str = sys.stdin.read()
    result = convert_to_latex(input_str)
    print(result)
