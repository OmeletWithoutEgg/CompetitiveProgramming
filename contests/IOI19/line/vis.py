import argparse
from matplotlib import lines, pyplot


MAX_SEGMENTS = 1000


parser = argparse.ArgumentParser(description='Visualizator for task line.')
parser.add_argument('input', help='input file')
parser.add_argument('--solution', help='output file')

args = parser.parse_args()


with open(args.input, 'r') as f:
    n = int(f.readline().strip())
    X, Y = [], []
    for _ in range(n):
        (x, y) = tuple(map(int, f.readline().strip().split(' ')))
        X.append(x)
        Y.append(y)

a1, a2 = pyplot.subplots()
pyplot.scatter(X, Y)
pyplot.xlim(-1, max(X)+1)
pyplot.ylim(-1, max(Y)+1)

if args.solution:
    with open(args.solution, 'r') as f:
        sol = int(f.readline().strip())
        cur = (0, 0)
        for _ in range(min(MAX_SEGMENTS, sol)):
            (sx, sy) = tuple(map(int, f.readline().strip().split(' ')))
            a2.add_line(lines.Line2D((cur[0], sx), (cur[1], sy), color='red'))
            cur = (sx, sy)

pyplot.show()
