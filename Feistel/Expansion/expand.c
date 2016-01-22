#include <stdio.h>
#include <stdlib.h>

#include "expand.h"
#include "debug.h"


/*** static global variables **************************************************/
int E_Bitselection[] = {
	32, 1,  2,  3,  4,  5,
	4,  5,  6,  7,  8,  9,
	8,  9,  10, 11, 12, 13,
	12, 13, 14, 15, 16, 17,
	16, 17, 18, 19, 20, 21,
	20, 21, 22, 23, 24, 25,
	24, 25, 26, 27, 28, 29,
	28, 29, 30, 31, 32, 1
};


static unsigned long bitmasks[] = {
	0,
	BIT1,
	BIT2,
	BIT3,
	BIT4,
	BIT5,
	BIT6,
	BIT7,
	BIT8,
	BIT9,
	BIT10,
	BIT11,
	BIT12,
	BIT13,
	BIT14,
	BIT15,
	BIT16,
	BIT17,
	BIT18,
	BIT19,
	BIT20,
	BIT21,
	BIT22,
	BIT23,
	BIT24,
	BIT25,
	BIT26,
	BIT27,
	BIT28,
	BIT29,
	BIT30,
	BIT31,
	BIT32
};


static unsigned char char_bitmasks[] = {
	'\0',
	CHAR_BIT1,
	CHAR_BIT2,
	CHAR_BIT3,
	CHAR_BIT4,
	CHAR_BIT5,
	CHAR_BIT6,
	CHAR_BIT7,
	CHAR_BIT8
};

/*
static unsigned long expand_masks[] = {
	4563402753,
	157286400,
	3637248,
	135168,
	2400,
	2147483703
};

static unsigned long expandbit1[] = {
	0, 134217728, 268435456, 402653184, 134217728, 268435456, 402653184, 536870912, 
	268435456, 402653184, 536870912, 671088640, 402653184, 536870912, 671088640, 805306368, 
	536870912, 671088640, 805306368, 939524096, 671088640, 805306368, 939524096, 1073741824, 
	805306368, 939524096, 1073741824, 1207959552, 939524096, 1073741824, 1207959552, 1342177280, 
	1073741824, 1207959552, 1342177280, 1476395008, 1207959552, 1342177280, 1476395008, 1610612736, 
	1342177280, 1476395008, 1610612736, 1744830464, 1476395008, 1610612736, 1744830464, 1879048192, 
	1610612736, 1744830464, 1879048192, 2013265920, 1744830464, 1879048192, 2013265920, 2147483648, 
	1879048192, 2013265920, 2147483648, 2281701376, 2013265920, 2147483648, 2281701376, 2415919104, 
	2147483648, 2281701376, 2415919104, 2550136832, 2281701376, 2415919104, 2550136832, 2684354560, 
	2415919104, 2550136832, 2684354560, 2818572288, 2550136832, 2684354560, 2818572288, 2952790016, 
	2684354560, 2818572288, 2952790016, 3087007744, 2818572288, 2952790016, 3087007744, 3221225472, 
	2952790016, 3087007744, 3221225472, 3355443200, 3087007744, 3221225472, 3355443200, 3489660928, 
	3221225472, 3355443200, 3489660928, 3623878656, 3355443200, 3489660928, 3623878656, 3758096384, 
	3489660928, 3623878656, 3758096384, 3892314112, 3623878656, 3758096384, 3892314112, 4026531840, 
	3758096384, 3892314112, 4026531840, 4160749568, 3892314112, 4026531840, 4160749568, 4294967296, 
	4026531840, 4160749568, 4294967296, 4429185024, 4160749568, 4294967296, 4429185024, 4563402752, 
	1, 134217729, 268435457, 402653185, 134217729, 268435457, 402653185, 536870913, 
	268435457, 402653185, 536870913, 671088641, 402653185, 536870913, 671088641, 805306369, 
	536870913, 671088641, 805306369, 939524097, 671088641, 805306369, 939524097, 1073741825, 
	805306369, 939524097, 1073741825, 1207959553, 939524097, 1073741825, 1207959553, 1342177281, 
	1073741825, 1207959553, 1342177281, 1476395009, 1207959553, 1342177281, 1476395009, 1610612737, 
	1342177281, 1476395009, 1610612737, 1744830465, 1476395009, 1610612737, 1744830465, 1879048193, 
	1610612737, 1744830465, 1879048193, 2013265921, 1744830465, 1879048193, 2013265921, 2147483649, 
	1879048193, 2013265921, 2147483649, 2281701377, 2013265921, 2147483649, 2281701377, 2415919105, 
	2147483649, 2281701377, 2415919105, 2550136833, 2281701377, 2415919105, 2550136833, 2684354561, 
	2415919105, 2550136833, 2684354561, 2818572289, 2550136833, 2684354561, 2818572289, 2952790017, 
	2684354561, 2818572289, 2952790017, 3087007745, 2818572289, 2952790017, 3087007745, 3221225473, 
	2952790017, 3087007745, 3221225473, 3355443201, 3087007745, 3221225473, 3355443201, 3489660929, 
	3221225473, 3355443201, 3489660929, 3623878657, 3355443201, 3489660929, 3623878657, 3758096385, 
	3489660929, 3623878657, 3758096385, 3892314113, 3623878657, 3758096385, 3892314113, 4026531841, 
	3758096385, 3892314113, 4026531841, 4160749569, 3892314113, 4026531841, 4160749569, 4294967297, 
	4026531841, 4160749569, 4294967297, 4429185025, 4160749569, 4294967297, 4429185025, 4563402753
};

static unsigned long expandbit2[] = {
	0, 2097152, 4194304, 6291456, 8388608, 10485760, 12582912, 14680064, 
	16777216, 18874368, 20971520, 23068672, 25165824, 27262976, 29360128, 31457280, 
	8388608, 10485760, 12582912, 14680064, 16777216, 18874368, 20971520, 23068672, 
	25165824, 27262976, 29360128, 31457280, 33554432, 35651584, 37748736, 39845888, 
	16777216, 18874368, 20971520, 23068672, 25165824, 27262976, 29360128, 31457280, 
	33554432, 35651584, 37748736, 39845888, 41943040, 44040192, 46137344, 48234496, 
	25165824, 27262976, 29360128, 31457280, 33554432, 35651584, 37748736, 39845888, 
	41943040, 44040192, 46137344, 48234496, 50331648, 52428800, 54525952, 56623104, 
	33554432, 35651584, 37748736, 39845888, 41943040, 44040192, 46137344, 48234496, 
	50331648, 52428800, 54525952, 56623104, 58720256, 60817408, 62914560, 65011712, 
	41943040, 44040192, 46137344, 48234496, 50331648, 52428800, 54525952, 56623104, 
	58720256, 60817408, 62914560, 65011712, 67108864, 69206016, 71303168, 73400320, 
	50331648, 52428800, 54525952, 56623104, 58720256, 60817408, 62914560, 65011712, 
	67108864, 69206016, 71303168, 73400320, 75497472, 77594624, 79691776, 81788928, 
	58720256, 60817408, 62914560, 65011712, 67108864, 69206016, 71303168, 73400320, 
	75497472, 77594624, 79691776, 81788928, 83886080, 85983232, 88080384, 90177536, 
	67108864, 69206016, 71303168, 73400320, 75497472, 77594624, 79691776, 81788928, 
	83886080, 85983232, 88080384, 90177536, 92274688, 94371840, 96468992, 98566144, 
	75497472, 77594624, 79691776, 81788928, 83886080, 85983232, 88080384, 90177536, 
	92274688, 94371840, 96468992, 98566144, 100663296, 102760448, 104857600, 106954752, 
	83886080, 85983232, 88080384, 90177536, 92274688, 94371840, 96468992, 98566144, 
	100663296, 102760448, 104857600, 106954752, 109051904, 111149056, 113246208, 115343360, 
	92274688, 94371840, 96468992, 98566144, 100663296, 102760448, 104857600, 106954752, 
	109051904, 111149056, 113246208, 115343360, 117440512, 119537664, 121634816, 123731968, 
	100663296, 102760448, 104857600, 106954752, 109051904, 111149056, 113246208, 115343360, 
	117440512, 119537664, 121634816, 123731968, 125829120, 127926272, 130023424, 132120576, 
	109051904, 111149056, 113246208, 115343360, 117440512, 119537664, 121634816, 123731968, 
	125829120, 127926272, 130023424, 132120576, 134217728, 136314880, 138412032, 140509184, 
	117440512, 119537664, 121634816, 123731968, 125829120, 127926272, 130023424, 132120576, 
	134217728, 136314880, 138412032, 140509184, 142606336, 144703488, 146800640, 148897792, 
	125829120, 127926272, 130023424, 132120576, 134217728, 136314880, 138412032, 140509184, 
	142606336, 144703488, 146800640, 148897792, 150994944, 153092096, 155189248, 157286400
};

static unsigned long expandbit3[] = {
	0, 32768, 65536, 98304, 131072, 163840, 196608, 229376, 
	262144, 294912, 327680, 360448, 393216, 425984, 458752, 491520, 
	524288, 557056, 589824, 622592, 655360, 688128, 720896, 753664, 
	786432, 819200, 851968, 884736, 917504, 950272, 983040, 1015808, 
	1048576, 1081344, 1114112, 1146880, 1179648, 1212416, 1245184, 1277952, 
	1310720, 1343488, 1376256, 1409024, 1441792, 1474560, 1507328, 1540096, 
	1572864, 1605632, 1638400, 1671168, 1703936, 1736704, 1769472, 1802240, 
	1835008, 1867776, 1900544, 1933312, 1966080, 1998848, 2031616, 2064384, 
	524288, 557056, 589824, 622592, 655360, 688128, 720896, 753664, 
	786432, 819200, 851968, 884736, 917504, 950272, 983040, 1015808, 
	1048576, 1081344, 1114112, 1146880, 1179648, 1212416, 1245184, 1277952, 
	1310720, 1343488, 1376256, 1409024, 1441792, 1474560, 1507328, 1540096, 
	1572864, 1605632, 1638400, 1671168, 1703936, 1736704, 1769472, 1802240, 
	1835008, 1867776, 1900544, 1933312, 1966080, 1998848, 2031616, 2064384, 
	2097152, 2129920, 2162688, 2195456, 2228224, 2260992, 2293760, 2326528, 
	2359296, 2392064, 2424832, 2457600, 2490368, 2523136, 2555904, 2588672, 
	1048576, 1081344, 1114112, 1146880, 1179648, 1212416, 1245184, 1277952, 
	1310720, 1343488, 1376256, 1409024, 1441792, 1474560, 1507328, 1540096, 
	1572864, 1605632, 1638400, 1671168, 1703936, 1736704, 1769472, 1802240, 
	1835008, 1867776, 1900544, 1933312, 1966080, 1998848, 2031616, 2064384, 
	2097152, 2129920, 2162688, 2195456, 2228224, 2260992, 2293760, 2326528, 
	2359296, 2392064, 2424832, 2457600, 2490368, 2523136, 2555904, 2588672, 
	2621440, 2654208, 2686976, 2719744, 2752512, 2785280, 2818048, 2850816, 
	2883584, 2916352, 2949120, 2981888, 3014656, 3047424, 3080192, 3112960, 
	1572864, 1605632, 1638400, 1671168, 1703936, 1736704, 1769472, 1802240, 
	1835008, 1867776, 1900544, 1933312, 1966080, 1998848, 2031616, 2064384, 
	2097152, 2129920, 2162688, 2195456, 2228224, 2260992, 2293760, 2326528, 
	2359296, 2392064, 2424832, 2457600, 2490368, 2523136, 2555904, 2588672, 
	2621440, 2654208, 2686976, 2719744, 2752512, 2785280, 2818048, 2850816, 
	2883584, 2916352, 2949120, 2981888, 3014656, 3047424, 3080192, 3112960, 
	3145728, 3178496, 3211264, 3244032, 3276800, 3309568, 3342336, 3375104, 
	3407872, 3440640, 3473408, 3506176, 3538944, 3571712, 3604480, 3637248
};

static unsigned long expandbit4[] = {
	0, 2048, 4096, 6144, 2048, 4096, 6144, 8192, 
	4096, 6144, 8192, 10240, 6144, 8192, 10240, 12288, 
	8192, 10240, 12288, 14336, 10240, 12288, 14336, 16384, 
	12288, 14336, 16384, 18432, 14336, 16384, 18432, 20480, 
	16384, 18432, 20480, 22528, 18432, 20480, 22528, 24576, 
	20480, 22528, 24576, 26624, 22528, 24576, 26624, 28672, 
	24576, 26624, 28672, 30720, 26624, 28672, 30720, 32768, 
	28672, 30720, 32768, 34816, 30720, 32768, 34816, 36864, 
	32768, 34816, 36864, 38912, 34816, 36864, 38912, 40960, 
	36864, 38912, 40960, 43008, 38912, 40960, 43008, 45056, 
	40960, 43008, 45056, 47104, 43008, 45056, 47104, 49152, 
	45056, 47104, 49152, 51200, 47104, 49152, 51200, 53248, 
	49152, 51200, 53248, 55296, 51200, 53248, 55296, 57344, 
	53248, 55296, 57344, 59392, 55296, 57344, 59392, 61440, 
	57344, 59392, 61440, 63488, 59392, 61440, 63488, 65536, 
	61440, 63488, 65536, 67584, 63488, 65536, 67584, 69632, 
	65536, 67584, 69632, 71680, 67584, 69632, 71680, 73728, 
	69632, 71680, 73728, 75776, 71680, 73728, 75776, 77824, 
	73728, 75776, 77824, 79872, 75776, 77824, 79872, 81920, 
	77824, 79872, 81920, 83968, 79872, 81920, 83968, 86016, 
	81920, 83968, 86016, 88064, 83968, 86016, 88064, 90112, 
	86016, 88064, 90112, 92160, 88064, 90112, 92160, 94208, 
	90112, 92160, 94208, 96256, 92160, 94208, 96256, 98304, 
	94208, 96256, 98304, 100352, 96256, 98304, 100352, 102400, 
	98304, 100352, 102400, 104448, 100352, 102400, 104448, 106496, 
	102400, 104448, 106496, 108544, 104448, 106496, 108544, 110592, 
	106496, 108544, 110592, 112640, 108544, 110592, 112640, 114688, 
	110592, 112640, 114688, 116736, 112640, 114688, 116736, 118784, 
	114688, 116736, 118784, 120832, 116736, 118784, 120832, 122880, 
	118784, 120832, 122880, 124928, 120832, 122880, 124928, 126976, 
	122880, 124928, 126976, 129024, 124928, 126976, 129024, 131072, 
	126976, 129024, 131072, 133120, 129024, 131072, 133120, 135168
};

static unsigned long expandbit5[] = {
	0, 32, 64, 96, 128, 160, 192, 224, 
	256, 288, 320, 352, 384, 416, 448, 480, 
	128, 160, 192, 224, 256, 288, 320, 352, 
	384, 416, 448, 480, 512, 544, 576, 608, 
	256, 288, 320, 352, 384, 416, 448, 480, 
	512, 544, 576, 608, 640, 672, 704, 736, 
	384, 416, 448, 480, 512, 544, 576, 608, 
	640, 672, 704, 736, 768, 800, 832, 864, 
	512, 544, 576, 608, 640, 672, 704, 736, 
	768, 800, 832, 864, 896, 928, 960, 992, 
	640, 672, 704, 736, 768, 800, 832, 864, 
	896, 928, 960, 992, 1024, 1056, 1088, 1120, 
	768, 800, 832, 864, 896, 928, 960, 992, 
	1024, 1056, 1088, 1120, 1152, 1184, 1216, 1248, 
	896, 928, 960, 992, 1024, 1056, 1088, 1120, 
	1152, 1184, 1216, 1248, 1280, 1312, 1344, 1376, 
	1024, 1056, 1088, 1120, 1152, 1184, 1216, 1248, 
	1280, 1312, 1344, 1376, 1408, 1440, 1472, 1504, 
	1152, 1184, 1216, 1248, 1280, 1312, 1344, 1376, 
	1408, 1440, 1472, 1504, 1536, 1568, 1600, 1632, 
	1280, 1312, 1344, 1376, 1408, 1440, 1472, 1504, 
	1536, 1568, 1600, 1632, 1664, 1696, 1728, 1760, 
	1408, 1440, 1472, 1504, 1536, 1568, 1600, 1632, 
	1664, 1696, 1728, 1760, 1792, 1824, 1856, 1888, 
	1536, 1568, 1600, 1632, 1664, 1696, 1728, 1760, 
	1792, 1824, 1856, 1888, 1920, 1952, 1984, 2016, 
	1664, 1696, 1728, 1760, 1792, 1824, 1856, 1888, 
	1920, 1952, 1984, 2016, 2048, 2080, 2112, 2144, 
	1792, 1824, 1856, 1888, 1920, 1952, 1984, 2016, 
	2048, 2080, 2112, 2144, 2176, 2208, 2240, 2272, 
	1920, 1952, 1984, 2016, 2048, 2080, 2112, 2144, 
	2176, 2208, 2240, 2272, 2304, 2336, 2368, 2400
};

static unsigned long expandbit6[] = {
	0, 2147483648, 1, 2147483649, 2, 2147483650, 3, 2147483651, 
	4, 2147483652, 5, 2147483653, 6, 2147483654, 7, 2147483655, 
	8, 2147483656, 9, 2147483657, 10, 2147483658, 11, 2147483659, 
	12, 2147483660, 13, 2147483661, 14, 2147483662, 15, 2147483663, 
	16, 2147483664, 17, 2147483665, 18, 2147483666, 19, 2147483667, 
	20, 2147483668, 21, 2147483669, 22, 2147483670, 23, 2147483671, 
	24, 2147483672, 25, 2147483673, 26, 2147483674, 27, 2147483675, 
	28, 2147483676, 29, 2147483677, 30, 2147483678, 31, 2147483679, 
	8, 2147483656, 9, 2147483657, 10, 2147483658, 11, 2147483659, 
	12, 2147483660, 13, 2147483661, 14, 2147483662, 15, 2147483663, 
	16, 2147483664, 17, 2147483665, 18, 2147483666, 19, 2147483667, 
	20, 2147483668, 21, 2147483669, 22, 2147483670, 23, 2147483671, 
	24, 2147483672, 25, 2147483673, 26, 2147483674, 27, 2147483675, 
	28, 2147483676, 29, 2147483677, 30, 2147483678, 31, 2147483679, 
	32, 2147483680, 33, 2147483681, 34, 2147483682, 35, 2147483683, 
	36, 2147483684, 37, 2147483685, 38, 2147483686, 39, 2147483687, 
	16, 2147483664, 17, 2147483665, 18, 2147483666, 19, 2147483667, 
	20, 2147483668, 21, 2147483669, 22, 2147483670, 23, 2147483671, 
	24, 2147483672, 25, 2147483673, 26, 2147483674, 27, 2147483675, 
	28, 2147483676, 29, 2147483677, 30, 2147483678, 31, 2147483679, 
	32, 2147483680, 33, 2147483681, 34, 2147483682, 35, 2147483683, 
	36, 2147483684, 37, 2147483685, 38, 2147483686, 39, 2147483687, 
	40, 2147483688, 41, 2147483689, 42, 2147483690, 43, 2147483691, 
	44, 2147483692, 45, 2147483693, 46, 2147483694, 47, 2147483695, 
	24, 2147483672, 25, 2147483673, 26, 2147483674, 27, 2147483675, 
	28, 2147483676, 29, 2147483677, 30, 2147483678, 31, 2147483679, 
	32, 2147483680, 33, 2147483681, 34, 2147483682, 35, 2147483683, 
	36, 2147483684, 37, 2147483685, 38, 2147483686, 39, 2147483687, 
	40, 2147483688, 41, 2147483689, 42, 2147483690, 43, 2147483691, 
	44, 2147483692, 45, 2147483693, 46, 2147483694, 47, 2147483695, 
	48, 2147483696, 49, 2147483697, 50, 2147483698, 51, 2147483699, 
	52, 2147483700, 53, 2147483701, 54, 2147483702, 55, 2147483703
};
	
static unsigned long *lookuptable[] = {
	expandbit1,
	expandbit2,
	expandbit3,
	expandbit4,
	expandbit5,
	expandbit6
};
*/

/*** Helper Functions Prototypes **********************************************/
void get_data_bits(unsigned long *data_bits, void *data32);


/*** Helper function prototypes ***********************************************/
unsigned long *alloc_expand_space()
{
	int i;
	unsigned long *space = NULL;

	space = malloc(sizeof(unsigned long) * 2);
	if (!space) {
		fprintf(stderr, "Memory Error on allocating expand space int expand.c\n");
		return NULL;
	}
	space[0] = 0;
	space[1] = 0;
	return space;
}

void free_expanded_space(unsigned long *space) 
{
	free(space);
}

void print_expanded_bits(unsigned long *data) 
{
	int i;
	char string[49];
	
	for (i = 0; i < 24; i++) {
		if (bitmasks[i + 1] & data[0]) {
			string[i] = '1';
		} else {
			string[i] = '0';
		}
		if (bitmasks[i + 1] & data[1]) {
			string[i + 24] = '1';
		} else {
			string[i + 24] = '0';
		}
	}
	string[48] = '\0';
	printf("%s\n",string);
}


void print_original_bits(void *data32) 
{
	int i;
	char string[33];
	unsigned long data_bits = 0;
	get_data_bits(&data_bits, data32);
	
	for (i = 0; i < 16; i++) {
		if (bitmasks[i + 1] & data_bits) {
			string[i] = '1';
		} else {
			string[i] = '0';
		}
		if (bitmasks[16 + i + 1] & data_bits) {
			string[i + 16] = '1';
		} else {
			string[i + 16] = '0';
		}
	}
	string[32] = '\0';
	printf("%s\n", string);
}


void expand(void *data32, unsigned long *expanded_bits) 
{
	int i, check_bit;
	unsigned long data_bits = 0;

	get_data_bits(&data_bits, data32);
	
	for (i = 0; i < 24; i++) {
		check_bit = E_Bitselection[i];
		if (bitmasks[check_bit] & data_bits) {
			expanded_bits[0] ^= bitmasks[i + 1];
		}
		check_bit = E_Bitselection[i + 24];
		if (bitmasks[check_bit] & data_bits) {
			expanded_bits[1] ^= bitmasks[i + 1];
		}
	}
}

/*
void expand(void *data32, unsigned long *expanded_bits) 
{
	int i;
	unsigned long data_bits = 0;
	unsigned long mask;
	unsigned long test_variable;
	unsigned char c;
	unsigned long template;

	get_data_bits(&data_bits, data32);

	for (i = 0; i < 6; i++) {
		mask = 0;
		mask = expand_masks[i];
		test_variable = mask & data_bits;
		for (c = 0; c < 256; c++) {
			if (test_variable == lookuptable[i][c]) {
				break;
			}
			if (c == 255) {
				fprintf(stderr, "EEEeeeeeh\n");
			}
		}
		template = c;
		template <<= (5 - i);
		printf("%lu   %lu\n", template, *expanded_bits);
		*expanded_bits += template;
		printf("%lu\n\n", *expanded_bits);
	}
}
*/
/*** Helper functions *********************************************************/

void get_data_bits(unsigned long *data_bits, void *data32)
{
	int i;
	unsigned char *datachars = (unsigned char *)data32;
	unsigned char c;
	unsigned long temp;
	for (i = 0; i < 4; i++) {
		c = datachars[i];
		temp = (unsigned long) c;
		temp <<= ((3 - i) * 8);
		*data_bits ^= temp;
	}
}
