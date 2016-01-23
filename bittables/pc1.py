bit1 = 2147483648
bit2 = 1073741824
bit3 = 536870912
bit4 = 268435456
bit5 = 134217728
bit6 = 67108864
bit7 = 33554432
bit8 = 16777216
bit9 = 8388608
bit10 = 4194304
bit11 = 2097152
bit12 = 1048576
bit13 = 524288
bit14 = 262144
bit15 = 131072
bit16 = 65536
bit17 = 32768
bit18 = 16384
bit19 = 8192
bit20 = 4096
bit21 = 2048
bit22 = 1024
bit23 = 512
bit24 = 256
bit25 = 128
bit26 = 64
bit27 = 32
bit28 = 16
bit29 = 8
bit30 = 4
bit31 = 2
bit32 = 1

charbit1 = 128
charbit2 = 64
charbit3 = 32
charbit4 = 16
charbit5 = 8
charbit6 = 4
charbit7 = 2
charbit8 = 1

bitmasks = [
0,
bit1,  
bit2, 
bit3,
bit4,
bit5,
bit6,
bit7,
bit8,
bit9,
bit10,
bit11,
bit12,
bit13, 
bit14,
bit15,
bit16,
bit17,
bit18,
bit19,
bit20,
bit21,
bit22,
bit23,
bit24,
bit25,
bit26,
bit27,
bit28,
bit29,
bit30,
bit31,
bit32
]

r = range(2)

print("static unsigned long PC_1_bitwise[] = {")
print("\t" + str(bit57 + bit49 + bit43 + bit33 + bit25 + bit17 + bit9 + bit1) + ",")
print("\t" + str(bit58 + bit50 + bit42 + bit34 + bit26 + bit18 + bit10 + bit2) + ",")
print("\t" + str(bit59 + bit51 + bit43 + bit35 + bit27 + bit19 + bit11 + bit3) + ",")
print("\t" + str(bit60 + bit52 + bit44 + bit36 + bit63 + bit55 + bit47 + bit39) + ",")
print("\t" + str(bit31 + bit23 + bit15 + bit7 + bit62 + bit54 + bit46 + bit38) + ",")
print("\t" + str(bit30 + bit22 + bit14 + bit6 + bit61 + bit53 + bit45 + bit37) + ",")
print("\t" + str(bit29 + bit21 + bit13 + bit5 + bit28 + bit20 + bit12 + bit4))
print("};\n")

s = ""

print("static int pc1row1[] = {")
for b1 in r:
    for b2 in r:
        for b3 in r:
            for b4 in r:
                for b5 in r:
                    for b6 in r:
                        for b7 in r:
                            for b8 in r:
                                number = b1 * charbit1 + b2 * charbit2 + b3 * charbit3 + b4 * charbit4 + b5 * charbit5 + b6 * charbit6 + b7 * charbit7 + b8 * charbit8
                                if (number % 8) == 0:
                                    print(s)
                                    s = ""
                                total = b1 * bit1 + b2 * bit2 + b3 * bit3 + b4 * bit4 + b5 * bit5 + b6 * bit6 + b7 * bit7 + b8 * bit8
                                s += (str(total) + ", ")

