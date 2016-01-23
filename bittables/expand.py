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

bytebits = (
(bit32, bit1, bit2, bit3, bit4, bit5, bit4, bit5),
(bit6, bit7, bit8, bit9, bit8, bit9, bit10, bit11),
(bit12, bit13, bit12, bit13, bit14, bit15, bit16, bit17),
(bit16, bit17, bit18, bit19, bit20, bit21, bit20, bit21), 
(bit22, bit23, bit24, bit25, bit24, bit25, bit26, bit27),
(bit28, bit29, bit28, bit29, bit30, bit31, bit32, bit1)
)

print("static unsigned long expand_masks[] = {")
for i in range(6):
    byte = 0;
    for j in range(8):
        byte |= bytebits[i][j]
    if i == 5:
        print("\t" + str(byte))
    else:
        print("\t" + str(byte) + ",")

print("};\n")

r = range(2)
lookuptable = [
[], 
[], 
[], 
[], 
[], 
[]]

for i in range(6):
    #s = "\t"
    #print("static unsigned long expandbit%d[] = {"%(i + 1))
    for b1 in r:
        for b2 in r:
            for b3 in r:
                for b4 in r:
                    for b5 in r:
                        for b6 in r:
                            for b7 in r:
                                for b8 in r:
                                    number = b1 * charbit1 + b2 * charbit2 + b3 * charbit3 + b4 * charbit4 + b5 * charbit5 + b6 * charbit6 + b7 * charbit7 + b8 * charbit8
                                    total = b1 * bytebits[i][0] | b2 * bytebits[i][1] | b3 * bytebits[i][2] | b4 * bytebits[i][3] | b5 * bytebits[i][4] | b6 * bytebits[i][5] | b7 * bytebits[i][6] | b8 * bytebits[i][7]
                                    lookuptable[i].append([total, number, 1])
                                    #if number == 255:
                                    #    s += (str(total))
                                    #else:
                                    #    s += (str(total) + ", ")
                                    #if ((number + 1) % 8) == 0:
                                    #    print(s)
                                    #    s = "\t"
    #print("};")
    #print("")

temp = 1;
for i in range(6):
    s = "\t"
    count = 0;
    for j in range(len(lookuptable[i])):
        if lookuptable[i][len(lookuptable[i]) - j - 1][2] == 1:
            count += 1
            temp = lookuptable[i][len(lookuptable[i]) - j - 1][0]
            for k in range(len(lookuptable[i]) - j - 1):
                if lookuptable[i][k][0] == temp:
                    lookuptable[i][k][2] = 0
#            if j == len(lookuptable[i]) - 1:
#                s += str(lookuptable[i][len(lookuptable[i]) - j - 1])
#                print(s)
#            else:
#                s += str(lookuptable[i][len(lookuptable[i]) - j - 1]) + ", "
#            if ((count + 1) % 8) == 0:
#                print(s)
#                s = "\t"
#    print("")

interimtable = [[],[],[],[],[],[]]

def less(a, b):
    if a[0] < b[0]:
        return True
    else:
        return False

def merge(A, aux, lo, mid, hi):
    for i in range(hi - lo + 1):
        aux[lo + i] = A[lo + i]
    
    i = lo
    j = mid + 1
    for l in range(hi - lo + 1):
        k = lo + l
        if i > mid:
            A[k] = aux[j]
            j += 1
        elif j > hi:
            A[k] = aux[i]
            i += 1
        elif less(aux[j], aux[i]):
            A[k] = aux[j]
            j += 1
        else:
            A[k] = aux[i]
            i += 1

def _sort(A, aux, lo, hi):
    if hi <= lo:
        return
    mid = lo + (hi - lo) / 2
    _sort(A, aux, lo, mid)
    _sort(A, aux, mid + 1, hi)
    merge(A, aux, lo, mid, hi)

def sort(A):
    aux = []
    for i in range(len(A)):
        aux.append([-1, -1])
    _sort(A, aux, 0, len(A) - 1)

sizes = []
for i in range(6):
    for j in range(len(lookuptable[i])):
        if lookuptable[i][j][2] == 1:
            interimtable[i].append([lookuptable[i][j][0], lookuptable[i][j][1]])
    sort(interimtable[i])
    sizes.append(len(interimtable[i]))

lookuptable = interimtable

for i in range(6):
    s = "\t"
    count = 0
    print("static unsigned long expandbit%d[] = {"%(i + 1))
    for j in range(len(lookuptable[i])):
        #if lookuptable[i][j][2] == 1:
        count += 1
        if j == len(lookuptable[i]) - 1:
            s += str(lookuptable[i][j][0])
            print(s)
            s = "\t"
        else:
            s += str(lookuptable[i][j][0]) + ",   "
            if ((count) % 8) == 0:
                print(s)
                s = "\t"
    print("};\n\n")
    
    print("static unsigned char expandchars%d[] = {"%(i+1))
    for j in range(len(lookuptable[i])):
        #if lookuptable[i][j][2] == 1:
        count += 1
        if j == len(lookuptable[i]) - 1:
            s += str(lookuptable[i][j][1])
            print(s)
            s = "\t"
        else:
            s += str(lookuptable[i][j][1]) + ",   "
            if ((count) % 8) == 0:
                print(s)
                s = "\t"
    print("};\n\n")



print("static unsigned long *lookuptable[] = {")
for i in range(6):
    if i == 5:
        print("\texpandbit%d"%(i + 1))
    else:
        print("\texpandbit%d,"%(i + 1))
print("};\n\n")

print("static unsigned char *lookupchars[] = {")
for i in range(6):
    if i == 5:
        print("\texpandchars%d"%(i + 1))
    else:
        print("\texpandchars%d,"%(i + 1))
print("};\n")


for i in range(6):
    print("#define S_TABLE%d\t%d"%(i+1, sizes[i]))
