from __future__ import print_function

import os
import sys
import subprocess

def main(inp, out, is_output):
    with open(inp, 'r') as f:
        rows = [c.strip() for c in f.read().split('\n') if c != ''][1:]
        if is_output:
            roots = rows[0]
            content = rows[1:]
        else:
            content = rows

    
    arrows = [' -> '.join(a.split(' ')) for a in content]

    with open(".graph", 'w') as f:
        f.write("digraph G {\n")
        if is_output:
            for r in roots.strip().split(' '):
                f.write('\t{};\n'.format(r))

        for a in arrows:
            f.write('\t' + a + ';\n')
        f.write("}")

    command = ["dot", "-Tsvg", ".graph", "-o", out]
    ret = subprocess.call(command)
    os.remove('.graph')
    return ret
    

if __name__ == '__main__':
    if len(sys.argv) not in [3, 4]:
        print("usage: {} [input] [output] [o]".format(sys.argv[0]))
        sys.exit(1)
    inp, out, = sys.argv[1], sys.argv[2]
    is_output = False
    if len(sys.argv) == 4:
        is_output = (sys.argv[3] == "o")
    ret = main(inp, out, is_output)
    if ret != 0:
        print("error processing file " + inp + ", output was not generated, error code was: " + str(ret))

    sys.exit(ret)

