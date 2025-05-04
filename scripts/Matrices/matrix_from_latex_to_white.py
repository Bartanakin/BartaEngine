import sys

def convert_matrix(input_str) :
#Split by '\\' to get rows, then split each row by '&' and strip whitespace
    rows = input_str.strip().split('\\\\')
    matrix = []
    for row in rows:
        elements =[elem.strip() for elem in row.strip().split('&')]
        matrix.append(' '.join(elements))

    return '\n'.join(matrix)

if __name__ == "__main__" :
    input_str = sys.stdin.read()
    result = convert_matrix(input_str)
    print(result)