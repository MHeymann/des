#!/usr/bin/python

for i in range(32):
    print("#define BIT%d\t%d"%(i+1, 2**(31 - i)))
