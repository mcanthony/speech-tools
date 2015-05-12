/*************************************************************************/
/*                                                                       */
/* Copyright (c) 1997-98 Richard Tobin, Language Technology Group, HCRC, */
/* University of Edinburgh.                                              */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED ``AS IS'', WITHOUT WARRANTY OF ANY KIND,     */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHOR OR THE UNIVERSITY OF EDINBURGH BE LIABLE */
/* FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF    */
/* CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION    */
/* WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.       */
/*                                                                       */
/*************************************************************************/
#include <stdio.h>
#include <stdlib.h>

#ifdef FOR_LT

#include "lt-memory.h"

#define Malloc salloc

#else

#include "system.h"

#endif

#include "charset.h"
#include "string16.h"

int iso_to_unicode[8][256];		/* latin-2 ... latin-9 */
int iso_max_val[8];
char8 *unicode_to_iso[8];

/* This table is used to initialise the above arrays */

static int latin_table[8][96] = {

/* latin2 */
{
0x00a0, 0x0104, 0x02d8, 0x0141, 0x00a4, 0x013d, 0x015a, 0x00a7,
0x00a8, 0x0160, 0x015e, 0x0164, 0x0179, 0x00ad, 0x017d, 0x017b,
0x00b0, 0x0105, 0x02db, 0x0142, 0x00b4, 0x013e, 0x015b, 0x02c7,
0x00b8, 0x0161, 0x015f, 0x0165, 0x017a, 0x02dd, 0x017e, 0x017c,
0x0154, 0x00c1, 0x00c2, 0x0102, 0x00c4, 0x0139, 0x0106, 0x00c7,
0x010c, 0x00c9, 0x0118, 0x00cb, 0x011a, 0x00cd, 0x00ce, 0x010e,
0x0110, 0x0143, 0x0147, 0x00d3, 0x00d4, 0x0150, 0x00d6, 0x00d7,
0x0158, 0x016e, 0x00da, 0x0170, 0x00dc, 0x00dd, 0x0162, 0x00df,
0x0155, 0x00e1, 0x00e2, 0x0103, 0x00e4, 0x013a, 0x0107, 0x00e7,
0x010d, 0x00e9, 0x0119, 0x00eb, 0x011b, 0x00ed, 0x00ee, 0x010f,
0x0111, 0x0144, 0x0148, 0x00f3, 0x00f4, 0x0151, 0x00f6, 0x00f7,
0x0159, 0x016f, 0x00fa, 0x0171, 0x00fc, 0x00fd, 0x0163, 0x02d9,
},

/* latin3 */
{
0x00a0, 0x0126, 0x02d8, 0x00a3, 0x00a4, -00001, 0x0124, 0x00a7,
0x00a8, 0x0130, 0x015e, 0x011e, 0x0134, 0x00ad, -00001, 0x017b,
0x00b0, 0x0127, 0x00b2, 0x00b3, 0x00b4, 0x00b5, 0x0125, 0x00b7,
0x00b8, 0x0131, 0x015f, 0x011f, 0x0135, 0x00bd, -00001, 0x017c,
0x00c0, 0x00c1, 0x00c2, -00001, 0x00c4, 0x010a, 0x0108, 0x00c7,
0x00c8, 0x00c9, 0x00ca, 0x00cb, 0x00cc, 0x00cd, 0x00ce, 0x00cf,
-00001, 0x00d1, 0x00d2, 0x00d3, 0x00d4, 0x0120, 0x00d6, 0x00d7,
0x011c, 0x00d9, 0x00da, 0x00db, 0x00dc, 0x016c, 0x015c, 0x00df,
0x00e0, 0x00e1, 0x00e2, -00001, 0x00e4, 0x010b, 0x0109, 0x00e7,
0x00e8, 0x00e9, 0x00ea, 0x00eb, 0x00ec, 0x00ed, 0x00ee, 0x00ef,
-00001, 0x00f1, 0x00f2, 0x00f3, 0x00f4, 0x0121, 0x00f6, 0x00f7,
0x011d, 0x00f9, 0x00fa, 0x00fb, 0x00fc, 0x016d, 0x015d, 0x02d9,
},

/* latin4 */
{
0x00a0, 0x0104, 0x0138, 0x0156, 0x00a4, 0x0128, 0x013b, 0x00a7,
0x00a8, 0x0160, 0x0112, 0x0122, 0x0166, 0x00ad, 0x017d, 0x00af,
0x00b0, 0x0105, 0x02db, 0x0157, 0x00b4, 0x0129, 0x013c, 0x02c7,
0x00b8, 0x0161, 0x0113, 0x0123, 0x0167, 0x014a, 0x017e, 0x014b,
0x0100, 0x00c1, 0x00c2, 0x00c3, 0x00c4, 0x00c5, 0x00c6, 0x012e,
0x010c, 0x00c9, 0x0118, 0x00cb, 0x0116, 0x00cd, 0x00ce, 0x012a,
0x0110, 0x0145, 0x014c, 0x0136, 0x00d4, 0x00d5, 0x00d6, 0x00d7,
0x00d8, 0x0172, 0x00da, 0x00db, 0x00dc, 0x0168, 0x016a, 0x00df,
0x0101, 0x00e1, 0x00e2, 0x00e3, 0x00e4, 0x00e5, 0x00e6, 0x012f,
0x010d, 0x00e9, 0x0119, 0x00eb, 0x0117, 0x00ed, 0x00ee, 0x012b,
0x0111, 0x0146, 0x014d, 0x0137, 0x00f4, 0x00f5, 0x00f6, 0x00f7,
0x00f8, 0x0173, 0x00fa, 0x00fb, 0x00fc, 0x0169, 0x016b, 0x02d9,
},

/* latin5 */
{
0x00a0, 0x0401, 0x0402, 0x0403, 0x0404, 0x0405, 0x0406, 0x0407,
0x0408, 0x0409, 0x040a, 0x040b, 0x040c, 0x00ad, 0x040e, 0x040f,
0x0410, 0x0411, 0x0412, 0x0413, 0x0414, 0x0415, 0x0416, 0x0417,
0x0418, 0x0419, 0x041a, 0x041b, 0x041c, 0x041d, 0x041e, 0x041f,
0x0420, 0x0421, 0x0422, 0x0423, 0x0424, 0x0425, 0x0426, 0x0427,
0x0428, 0x0429, 0x042a, 0x042b, 0x042c, 0x042d, 0x042e, 0x042f,
0x0430, 0x0431, 0x0432, 0x0433, 0x0434, 0x0435, 0x0436, 0x0437,
0x0438, 0x0439, 0x043a, 0x043b, 0x043c, 0x043d, 0x043e, 0x043f,
0x0440, 0x0441, 0x0442, 0x0443, 0x0444, 0x0445, 0x0446, 0x0447,
0x0448, 0x0449, 0x044a, 0x044b, 0x044c, 0x044d, 0x044e, 0x044f,
0x2116, 0x0451, 0x0452, 0x0453, 0x0454, 0x0455, 0x0456, 0x0457,
0x0458, 0x0459, 0x045a, 0x045b, 0x045c, 0x00a7, 0x045e, 0x045f,
},

/* latin6 */
{
0x00a0, -00001, -00001, -00001, 0x00a4, -00001, -00001, -00001,
-00001, -00001, -00001, -00001, 0x060c, 0x00ad, -00001, -00001,
-00001, -00001, -00001, -00001, -00001, -00001, -00001, -00001,
-00001, -00001, -00001, 0x061b, -00001, -00001, -00001, 0x061f,
-00001, 0x0621, 0x0622, 0x0623, 0x0624, 0x0625, 0x0626, 0x0627,
0x0628, 0x0629, 0x062a, 0x062b, 0x062c, 0x062d, 0x062e, 0x062f,
0x0630, 0x0631, 0x0632, 0x0633, 0x0634, 0x0635, 0x0636, 0x0637,
0x0638, 0x0639, 0x063a, -00001, -00001, -00001, -00001, -00001,
0x0640, 0x0641, 0x0642, 0x0643, 0x0644, 0x0645, 0x0646, 0x0647,
0x0648, 0x0649, 0x064a, 0x064b, 0x064c, 0x064d, 0x064e, 0x064f,
0x0650, 0x0651, 0x0652, -00001, -00001, -00001, -00001, -00001,
-00001, -00001, -00001, -00001, -00001, -00001, -00001, -00001,
},

/* latin7 */
{
0x00a0, 0x02bd, 0x02bc, 0x00a3, -00001, -00001, 0x00a6, 0x00a7,
0x00a8, 0x00a9, -00001, 0x00ab, 0x00ac, 0x00ad, -00001, 0x2015,
0x00b0, 0x00b1, 0x00b2, 0x00b3, 0x0384, 0x0385, 0x0386, 0x00b7,
0x0388, 0x0389, 0x038a, 0x00bb, 0x038c, 0x00bd, 0x038e, 0x038f,
0x0390, 0x0391, 0x0392, 0x0393, 0x0394, 0x0395, 0x0396, 0x0397,
0x0398, 0x0399, 0x039a, 0x039b, 0x039c, 0x039d, 0x039e, 0x039f,
0x03a0, 0x03a1, -00001, 0x03a3, 0x03a4, 0x03a5, 0x03a6, 0x03a7,
0x03a8, 0x03a9, 0x03aa, 0x03ab, 0x03ac, 0x03ad, 0x03ae, 0x03af,
0x03b0, 0x03b1, 0x03b2, 0x03b3, 0x03b4, 0x03b5, 0x03b6, 0x03b7,
0x03b8, 0x03b9, 0x03ba, 0x03bb, 0x03bc, 0x03bd, 0x03be, 0x03bf,
0x03c0, 0x03c1, 0x03c2, 0x03c3, 0x03c4, 0x03c5, 0x03c6, 0x03c7,
0x03c8, 0x03c9, 0x03ca, 0x03cb, 0x03cc, 0x03cd, 0x03ce, -00001,
},

/* latin8 */
{
0x00a0, -00001, 0x00a2, 0x00a3, 0x00a4, 0x00a5, 0x00a6, 0x00a7,
0x00a8, 0x00a9, 0x00d7, 0x00ab, 0x00ac, 0x00ad, 0x00ae, 0x203e,
0x00b0, 0x00b1, 0x00b2, 0x00b3, 0x00b4, 0x00b5, 0x00b6, 0x00b7,
0x00b8, 0x00b9, 0x00f7, 0x00bb, 0x00bc, 0x00bd, 0x00be, -00001,
-00001, -00001, -00001, -00001, -00001, -00001, -00001, -00001,
-00001, -00001, -00001, -00001, -00001, -00001, -00001, -00001,
-00001, -00001, -00001, -00001, -00001, -00001, -00001, -00001,
-00001, -00001, -00001, -00001, -00001, -00001, -00001, 0x2017,
0x05d0, 0x05d1, 0x05d2, 0x05d3, 0x05d4, 0x05d5, 0x05d6, 0x05d7,
0x05d8, 0x05d9, 0x05da, 0x05db, 0x05dc, 0x05dd, 0x05de, 0x05df,
0x05e0, 0x05e1, 0x05e2, 0x05e3, 0x05e4, 0x05e5, 0x05e6, 0x05e7,
0x05e8, 0x05e9, 0x05ea, -00001, -00001, -00001, -00001, -00001,
},

/* latin9 */
{
0x00a0, 0x00a1, 0x00a2, 0x00a3, 0x00a4, 0x00a5, 0x00a6, 0x00a7,
0x00a8, 0x00a9, 0x00aa, 0x00ab, 0x00ac, 0x00ad, 0x00ae, 0x00af,
0x00b0, 0x00b1, 0x00b2, 0x00b3, 0x00b4, 0x00b5, 0x00b6, 0x00b7,
0x00b8, 0x00b9, 0x00ba, 0x00bb, 0x00bc, 0x00bd, 0x00be, 0x00bf,
0x00c0, 0x00c1, 0x00c2, 0x00c3, 0x00c4, 0x00c5, 0x00c6, 0x00c7,
0x00c8, 0x00c9, 0x00ca, 0x00cb, 0x00cc, 0x00cd, 0x00ce, 0x00cf,
0x011e, 0x00d1, 0x00d2, 0x00d3, 0x00d4, 0x00d5, 0x00d6, 0x00d7,
0x00d8, 0x00d9, 0x00da, 0x00db, 0x00dc, 0x0130, 0x015e, 0x00df,
0x00e0, 0x00e1, 0x00e2, 0x00e3, 0x00e4, 0x00e5, 0x00e6, 0x00e7,
0x00e8, 0x00e9, 0x00ea, 0x00eb, 0x00ec, 0x00ed, 0x00ee, 0x00ef,
0x011f, 0x00f1, 0x00f2, 0x00f3, 0x00f4, 0x00f5, 0x00f6, 0x00f7,
0x00f8, 0x00f9, 0x00fa, 0x00fb, 0x00fc, 0x0131, 0x015f, 0x00ff,
}
};

const char8 *CharacterEncodingName[CE_enum_count] = {
    "unknown",
    "unspecified-ascii-superset",

    "UTF-8",
    "ISO-646",

    "ISO-8859-1",
    "ISO-8859-2",
    "ISO-8859-3",
    "ISO-8859-4",
    "ISO-8859-5",
    "ISO-8859-6",
    "ISO-8859-7",
    "ISO-8859-8",
    "ISO-8859-9",

    "UTF-16",
    "UTF-16",
    "ISO-10646-UCS-2",
    "ISO-10646-UCS-2",
};

const char8 *CharacterEncodingNameAndByteOrder[CE_enum_count] = {
    "unknown",
    "unspecified_ascii_superset",

    "UTF-8",
    "ISO-646",

    "ISO-8859-1",
    "ISO-8859-2",
    "ISO-8859-3",
    "ISO-8859-4",
    "ISO-8859-5",
    "ISO-8859-6",
    "ISO-8859-7",
    "ISO-8859-8",
    "ISO-8859-9",

    "UTF-16-B",
    "UTF-16-L",
    "ISO-10646-UCS-2-B",
    "ISO-10646-UCS-2-L",
};

struct character_encoding_alias CharacterEncodingAlias[] = {
    {"ASCII", CE_ISO_646},
    {"ISO-Latin-1", CE_ISO_8859_1},
    {"ISO-Latin-2", CE_ISO_8859_2},
    {"ISO-Latin-3", CE_ISO_8859_3},
    {"ISO-Latin-4", CE_ISO_8859_4},
    {"ISO-Latin-5", CE_ISO_8859_5},
    {"ISO-Latin-6", CE_ISO_8859_6},
    {"ISO-Latin-7", CE_ISO_8859_7},
    {"ISO-Latin-8", CE_ISO_8859_8},
    {"UCS-2", CE_ISO_10646_UCS_2B},
};
const int CE_alias_count =
    sizeof(CharacterEncodingAlias)/sizeof(CharacterEncodingAlias[0]);

CharacterEncoding InternalCharacterEncoding;

void init_charset(void)
{
    int i, j;

    /* Determine internal encoding */

#if CHAR_SIZE == 8
    InternalCharacterEncoding = CE_unspecified_ascii_superset;
#else
    union {char b[2]; short s;} bytes;
    bytes.s = 1;
    InternalCharacterEncoding = (bytes.b[0] == 0) ? CE_UTF_16B : CE_UTF_16L;
#endif

    /* Make ISO-Latin-N tables */

    for(i=0; i<8; i++)
    {
	int max = 0x9f;

	for(j=0; j<0xa0; j++)
	    iso_to_unicode[i][j] = j;
	for(j=0xa0; j<0x100; j++)
	{
	    int code = latin_table[i][j-0xa0];
	    iso_to_unicode[i][j] = code;
	    if(code > max) max = code;
	}

	iso_max_val[i] = max;

	if(!(unicode_to_iso[i] = Malloc(max+1)))
	{
	    fprintf(stderr, "Malloc failed in charset initialisation\n");
	    exit(1);
	}

	for(j=0; j<0xa0; j++)
	    unicode_to_iso[i][j] = j;
	for(j=0xa0; j<=max; j++)
	    unicode_to_iso[i][j] = '?';
	for(j=0xa0; j<0x100; j++)
	{
	    int code = latin_table[i][j-0xa0];
	    if(code != -1)
		unicode_to_iso[i][code] = j;
	}
    }
}

/* Return true if the encoding has 8-bit input units and is the same
   as ascii for characters <= 127 */

int EncodingIsAsciiSuperset(CharacterEncoding enc)
{
    return enc >= CE_unspecified_ascii_superset && enc <= CE_ISO_8859_9;
}

/* 
 * Return true if enc1 and enc2 have the same size input units, and are
 * the same for Unicode <= 127.
 * If so, *enc3 is set to enc2 modified to have the same byte order as enc1.
 */

int EncodingsCompatible(CharacterEncoding enc1, CharacterEncoding enc2,
			CharacterEncoding *enc3)
{
    if(EncodingIsAsciiSuperset(enc1))
    {
	if(EncodingIsAsciiSuperset(enc2))
	{
	    *enc3 = enc2;
	    return 1;
	}
	return 0;
    }

    if(enc1 == CE_UTF_16B || enc1 == CE_ISO_10646_UCS_2B)
    {
	if(enc2 == CE_UTF_16B || enc2 == CE_UTF_16L)
	    *enc3 = CE_UTF_16B;
	else if(enc2 == CE_ISO_10646_UCS_2B || enc2 == CE_ISO_10646_UCS_2L)
	    *enc3 = CE_ISO_10646_UCS_2B;
	else
	    return 0;
	return 1;
    }

    if(enc1 == CE_UTF_16L || enc1 == CE_ISO_10646_UCS_2L)
    {
	if(enc2 == CE_UTF_16B || enc2 == CE_UTF_16L)
	    *enc3 = CE_UTF_16L;
	else if(enc2 == CE_ISO_10646_UCS_2B || enc2 == CE_ISO_10646_UCS_2L)
	    *enc3 = CE_ISO_10646_UCS_2L;
	else
	    return 0;
	return 1;
    }

    return 0;
}

CharacterEncoding FindEncoding(char8 *name)
{
    int i;

    for(i=0; i<CE_enum_count; i++)
	if(strcasecmp8(name, CharacterEncodingNameAndByteOrder[i]) == 0)
	    return (CharacterEncoding)i;

    for(i=0; i<CE_enum_count; i++)
	if(strcasecmp8(name, CharacterEncodingName[i]) == 0)
	    return (CharacterEncoding)i;

    for(i=0; i<CE_alias_count; i++)
	if(strcasecmp8(name, CharacterEncodingAlias[i].name) == 0)
	    return CharacterEncodingAlias[i].enc;

    return CE_unknown;
}

