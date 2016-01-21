#! /usr/bin/python

print("static unsigned long[] = {")
print("\t0,")

for i in range(32):
    print("\tBIT%d,"%(i + 1))
print("}")
