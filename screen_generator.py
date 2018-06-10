import sys

def hang():
    sys.stdout.flush()
    while True:
        pass

def main():
    with open('title_screen.txt') as f:
        for line in f.readlines():
            line = line[:-1]
            output_line = '"'
            for char in line:
                output_line += char
            output_line += ' ' * (80 - len(line))
            output_line += '"'
            print(output_line)

if __name__ == '__main__':
    main()
