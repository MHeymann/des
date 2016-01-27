/*** Library Headers **********************************************************/
#include <stdio.h>
#include <stdlib.h>


/*** Local Headers ************************************************************/
#include "expand.h"


/*** Macros *******************************************************************/
#define S_TABLE1	64
#define S_TABLE2	64
#define S_TABLE3	64
#define S_TABLE4	64
#define S_TABLE5	64
#define S_TABLE6	64


/*** static global variables **************************************************/
/*
 * table used to generate different mask tables
 */
/*
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
*/

/*
 * sizes of the tables that followed
 */
static int sizes[] = {
	S_TABLE1, 
	S_TABLE2, 
	S_TABLE3, 
	S_TABLE4, 
	S_TABLE5, 
	S_TABLE6 
};

/*
 * bitmasks used to address different bits
 */
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

/*
 * bitmasks used to address bits in unsigned characters
 */
/*
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
*/

/*
 * Masks used to check bits for expanding the different groups of four bits
 * to groups of six bits
 */
static unsigned long expand_masks[] = {
	4160749569,
	132120576,
	2064384,
	129024,
	2016,
	2147483679
};

static unsigned long expandbyte1[] = {
	0,   1,   134217728,   134217729,   268435456,   268435457,   402653184,   402653185,   
	536870912,   536870913,   671088640,   671088641,   805306368,   805306369,   939524096,   939524097,   
	1073741824,   1073741825,   1207959552,   1207959553,   1342177280,   1342177281,   1476395008,   1476395009,   
	1610612736,   1610612737,   1744830464,   1744830465,   1879048192,   1879048193,   2013265920,   2013265921,   
	2147483648,   2147483649,   2281701376,   2281701377,   2415919104,   2415919105,   2550136832,   2550136833,   
	2684354560,   2684354561,   2818572288,   2818572289,   2952790016,   2952790017,   3087007744,   3087007745,   
	3221225472,   3221225473,   3355443200,   3355443201,   3489660928,   3489660929,   3623878656,   3623878657,   
	3758096384,   3758096385,   3892314112,   3892314113,   4026531840,   4026531841,   4160749568,   4160749569
};


static unsigned char expandchars1[] = {
	0,   128,   5,   133,   10,   138,   15,   143,   
	16,   144,   21,   149,   26,   154,   31,   159,   
	32,   160,   37,   165,   42,   170,   47,   175,   
	48,   176,   53,   181,   58,   186,   63,   191,   
	64,   192,   69,   197,   74,   202,   79,   207,   
	80,   208,   85,   213,   90,   218,   95,   223,   
	96,   224,   101,   229,   106,   234,   111,   239,   
	112,   240,   117,   245,   122,   250,   127,   255
};


static unsigned long expandbyte2[] = {
	0,   2097152,   4194304,   6291456,   8388608,   10485760,   12582912,   14680064,   
	16777216,   18874368,   20971520,   23068672,   25165824,   27262976,   29360128,   31457280,   
	33554432,   35651584,   37748736,   39845888,   41943040,   44040192,   46137344,   48234496,   
	50331648,   52428800,   54525952,   56623104,   58720256,   60817408,   62914560,   65011712,   
	67108864,   69206016,   71303168,   73400320,   75497472,   77594624,   79691776,   81788928,   
	83886080,   85983232,   88080384,   90177536,   92274688,   94371840,   96468992,   98566144,   
	100663296,   102760448,   104857600,   106954752,   109051904,   111149056,   113246208,   115343360,   
	117440512,   119537664,   121634816,   123731968,   125829120,   127926272,   130023424,   132120576
};


static unsigned char expandchars2[] = {
	0,   1,   2,   3,   20,   21,   22,   23,   
	40,   41,   42,   43,   60,   61,   62,   63,   
	64,   65,   66,   67,   84,   85,   86,   87,   
	104,   105,   106,   107,   124,   125,   126,   127,   
	128,   129,   130,   131,   148,   149,   150,   151,   
	168,   169,   170,   171,   188,   189,   190,   191,   
	192,   193,   194,   195,   212,   213,   214,   215,   
	232,   233,   234,   235,   252,   253,   254,   255
};


static unsigned long expandbyte3[] = {
	0,   32768,   65536,   98304,   131072,   163840,   196608,   229376,   
	262144,   294912,   327680,   360448,   393216,   425984,   458752,   491520,   
	524288,   557056,   589824,   622592,   655360,   688128,   720896,   753664,   
	786432,   819200,   851968,   884736,   917504,   950272,   983040,   1015808,   
	1048576,   1081344,   1114112,   1146880,   1179648,   1212416,   1245184,   1277952,   
	1310720,   1343488,   1376256,   1409024,   1441792,   1474560,   1507328,   1540096,   
	1572864,   1605632,   1638400,   1671168,   1703936,   1736704,   1769472,   1802240,   
	1835008,   1867776,   1900544,   1933312,   1966080,   1998848,   2031616,   2064384
};


static unsigned char expandchars3[] = {
	0,   1,   2,   3,   4,   5,   6,   7,   
	8,   9,   10,   11,   12,   13,   14,   15,   
	80,   81,   82,   83,   84,   85,   86,   87,   
	88,   89,   90,   91,   92,   93,   94,   95,   
	160,   161,   162,   163,   164,   165,   166,   167,   
	168,   169,   170,   171,   172,   173,   174,   175,   
	240,   241,   242,   243,   244,   245,   246,   247,   
	248,   249,   250,   251,   252,   253,   254,   255
};


static unsigned long expandbyte4[] = {
	0,   2048,   4096,   6144,   8192,   10240,   12288,   14336,   
	16384,   18432,   20480,   22528,   24576,   26624,   28672,   30720,   
	32768,   34816,   36864,   38912,   40960,   43008,   45056,   47104,   
	49152,   51200,   53248,   55296,   57344,   59392,   61440,   63488,   
	65536,   67584,   69632,   71680,   73728,   75776,   77824,   79872,   
	81920,   83968,   86016,   88064,   90112,   92160,   94208,   96256,   
	98304,   100352,   102400,   104448,   106496,   108544,   110592,   112640,   
	114688,   116736,   118784,   120832,   122880,   124928,   126976,   129024
};


static unsigned char expandchars4[] = {
	0,   5,   10,   15,   16,   21,   26,   31,   
	32,   37,   42,   47,   48,   53,   58,   63,   
	64,   69,   74,   79,   80,   85,   90,   95,   
	96,   101,   106,   111,   112,   117,   122,   127,   
	128,   133,   138,   143,   144,   149,   154,   159,   
	160,   165,   170,   175,   176,   181,   186,   191,   
	192,   197,   202,   207,   208,   213,   218,   223,   
	224,   229,   234,   239,   240,   245,   250,   255
};


static unsigned long expandbyte5[] = {
	0,   32,   64,   96,   128,   160,   192,   224,   
	256,   288,   320,   352,   384,   416,   448,   480,   
	512,   544,   576,   608,   640,   672,   704,   736,   
	768,   800,   832,   864,   896,   928,   960,   992,   
	1024,   1056,   1088,   1120,   1152,   1184,   1216,   1248,   
	1280,   1312,   1344,   1376,   1408,   1440,   1472,   1504,   
	1536,   1568,   1600,   1632,   1664,   1696,   1728,   1760,   
	1792,   1824,   1856,   1888,   1920,   1952,   1984,   2016
};


static unsigned char expandchars5[] = {
	0,   1,   2,   3,   20,   21,   22,   23,   
	40,   41,   42,   43,   60,   61,   62,   63,   
	64,   65,   66,   67,   84,   85,   86,   87,   
	104,   105,   106,   107,   124,   125,   126,   127,   
	128,   129,   130,   131,   148,   149,   150,   151,   
	168,   169,   170,   171,   188,   189,   190,   191,   
	192,   193,   194,   195,   212,   213,   214,   215,   
	232,   233,   234,   235,   252,   253,   254,   255
};


static unsigned long expandbyte6[] = {
	0,   1,   2,   3,   4,   5,   6,   7,   
	8,   9,   10,   11,   12,   13,   14,   15,   
	16,   17,   18,   19,   20,   21,   22,   23,   
	24,   25,   26,   27,   28,   29,   30,   31,   
	2147483648,   2147483649,   2147483650,   2147483651,   2147483652,   2147483653,   2147483654,   2147483655,   
	2147483656,   2147483657,   2147483658,   2147483659,   2147483660,   2147483661,   2147483662,   2147483663,   
	2147483664,   2147483665,   2147483666,   2147483667,   2147483668,   2147483669,   2147483670,   2147483671,   
	2147483672,   2147483673,   2147483674,   2147483675,   2147483676,   2147483677,   2147483678,   2147483679
};


static unsigned char expandchars6[] = {
	0,   2,   4,   6,   8,   10,   12,   14,   
	80,   82,   84,   86,   88,   90,   92,   94,   
	160,   162,   164,   166,   168,   170,   172,   174,   
	240,   242,   244,   246,   248,   250,   252,   254,   
	1,   3,   5,   7,   9,   11,   13,   15,   
	81,   83,   85,   87,   89,   91,   93,   95,   
	161,   163,   165,   167,   169,   171,   173,   175,   
	241,   243,   245,   247,   249,   251,   253,   255
};

/*
 * the different translation tables taken together in a single data structure
 */
static unsigned long *lookuptable[] = {
	expandbyte1,
	expandbyte2,
	expandbyte3,
	expandbyte4,
	expandbyte5,
	expandbyte6
};

/*
 * the tables for char values in a single data structure
 */
static unsigned char *lookupchars[] = {
	expandchars1,
	expandchars2,
	expandchars3,
	expandchars4,
	expandchars5,
	expandchars6
};


/*** Helper Functions Prototypes **********************************************/

unsigned char get_char_mask(unsigned long bits_present, int char_no);


/*** Helper function prototypes ***********************************************/
/**
 * Expand the 32 data_bits into 48 bits.
 */
void expand(unsigned long *data_bits, unsigned long *expanded_bits) 
{
	int i;
	unsigned long mask;
	unsigned long bits_present;
	unsigned long template;

	for (i = 0; i < 6; i++) {
		mask = expand_masks[i];
		bits_present = mask & *data_bits;
		template = get_char_mask(bits_present, i);
		if (i < 3) {
			template <<= ((4 - i - 1) * 8);
			expanded_bits[0] += template;
		} else {
			template <<= ((4 - (i - 3) - 1) * 8);
			expanded_bits[1] += template;
		}
	}
}

/**
 * Allocate space into which to put the databits.
 */
unsigned long *alloc_expand_space()
{
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

/**
 * Free the space allocated for expanding bits.
 */
void free_expanded_space(unsigned long *space) 
{
	free(space);
}

/**
 * Print the 48 bits resulting from the expand function in this library
 */
void print_expanded_bits(unsigned long *data, char *string) 
{
	int i;
	char *localstring;
	char s[49];

	if (!string) {
		localstring = (char *)s;
	} else {
		localstring = string;
	}

	for (i = 0; i < 24; i++) {
		if (bitmasks[i + 1] & data[0]) {
			localstring[i] = '1';
		} else {
			localstring[i] = '0';
		}
		if (bitmasks[i + 1] & data[1]) {
			localstring[i + 24] = '1';
		} else {
			localstring[i + 24] = '0';
		}
	}
	localstring[48] = '\0';
	for (i = 0; i < 48; i++) {
		if (localstring[i]) {
			printf("%c", localstring[i]);
		}
		if (((i + 1) % 6) == 0) {
			printf(" ");
		}
	}

}

/**
 * Print the bits of the 32 bit data piece.
 */
void print_original_bits(unsigned long *data_bits, char *s) 
{
	int i;
	char *string;
	char localstring[33];

	if (!s) {
		string = localstring;
	} else {
		string = s;
	}
	
	printf(" ");
	for (i = 0; i < 16; i++) {
		if (bitmasks[i + 1] & *data_bits) {
			string[i] = '1';
		} else {
			string[i] = '0';
		}
		if (bitmasks[16 + i + 1] & *data_bits) {
			string[i + 16] = '1';
		} else {
			string[i + 16] = '0';
		}
	}
	string[32] = '\0';
	for (i = 0; i < 32; i++) {
		printf("%c", string[i]);
		if (((i + 1) % 4) == 0) {
			printf("   ");
		}
	}
}


/*** Helper functions *********************************************************/
/**
 * Get the unsigned chars from the lookup table for byte number char_no in 
 * the expanded data piece.  
 */
unsigned char get_char_mask(unsigned long bits_present, int char_no)
{
	int hi = sizes[char_no] - 1;
	int lo = 0;
	int mid;
	int count = 0;

	mid = ((hi + lo) / 2);
	while (lo < hi) {
		count++;

		if (!(lookuptable[char_no][mid] ^ bits_present)) {
			/* found it */
			break;
		} else if (lookuptable[char_no][mid] < bits_present) {
			lo = mid + 1;
		} else {
			hi = mid - 1;
		}
		mid = ((hi + lo) / 2);
	}

	if (lookuptable[char_no][mid] != bits_present) {
		fprintf(stderr, "\n\n\tAaaaaaaaah!!!!!!!!!!!\n\n");
	}
	return lookupchars[char_no][mid];
}


