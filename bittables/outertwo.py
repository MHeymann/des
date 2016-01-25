#! /usr/bin/python

x = (2**31 + 2 ** 26)

for i in range(4):
    print("#define OUTER_MASK%d\t%d"%(i + 1, x >> (i * 6)))
