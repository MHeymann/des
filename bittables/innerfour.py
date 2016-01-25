#! /usr/bin/python

x = (2**30 + 2**29 + 2**28 + 2**27)

#print x

for i in range(4):
    print("#define INNER_MASK%d\t%d"%(i + 1, x >> (i * 6)))
