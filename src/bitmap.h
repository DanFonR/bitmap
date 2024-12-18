#ifndef _BITMAP_H

#define _BITMAP_H

#include <stdint.h>

#define FILENAME_SIZE 128

#define FILE_OFFSET(dib_header)  sizeof(BMPFileHeader) + sizeof(dib_header)
#define DEFAULT_RESOLUTION_UNIT  0 /* pixels per meter (OS22XBITMAPHEADER) */
#define COLOR_PLANES             1
#define DEFAULT_COLOR_PALETTE    0 /* 2^n */
#define DEFAULT_IMPORTANT_COLORS 0 /* all colors important */
#define NONE                     0
#define DEFAULT_FILL_DIRECTION   0 /* from lower-left corner to upper-right */
#define DEFAULT_COLOR_ENCODING   0 /* for RGB */

/* string types */

typedef char      file_name[FILENAME_SIZE];
typedef char      dib_header[9];   /* longest option is 8 chars + 1 null char */
typedef char *    help_string;

typedef uint8_t   hex_value;
typedef hex_value RGBpixel[3];     /* written as BGR */
typedef hex_value RGBApixel[4];    /* written as ABGR */

typedef struct {
	file_name filename;
	int32_t   width;
	int32_t   height;
	int16_t   bpp;
    int16_t   mode;
} basic_info;

enum header_field_values { /* reversed, header field must be little-endian */
    BM = 0x4D42, /* Windows 3.1x and later, this one will be used */
    BA = 0x4142, /* OS/2 struct bmp array */
    CI = 0x4943, /* OS/2 struct color icon */
    CP = 0x5043, /* OS/2 const color pointer */
    IC = 0x4349, /* OS/2 struct icon */
    PT = 0x5450  /* OS/2 pointer */
};

enum compression_method {
    BI_RGB            = 0,  /* no compression, most common */
    BI_RLE8           = 1,  /* run-length encoding, 8 bits per pixel */
    BI_RLE4           = 2,  /* RLE, 4 bits per pixel */
    BI_BITFIELDS      = 3,  /* Huffman 1D */
    BI_JPEG           = 4,  /* RLE, 24 bits per pixel, JPEG */
    BI_PNG            = 5,  /* PNG */
    BI_ALPHABITFIELDS = 6,  /* RGBA bit field masks, only Windows CE */
    BI_CMYK           = 11, /* only Windows Metafile CMYK */
    BI_CMYKRLE8       = 12, /* same as above, RLE-8 */
    BI_CMYKRLE4       = 13  /* same as above, RLE-4 */
};

enum halftoning_algorithms { /* P1 = parameter 1; P2 = parameter 2 */
    NO_HALFTONING   = NONE,  /* most common */
    ERROR_DIFFUSION = 1,     /* P1: 0 ERR not diffused, 100 no ERR damping */
    PANDA           = 2,     /* P1 = X, P2 = Y: halftoning pattern */
    SUPER_CIRCLE    = 3      /* P1 = X, P2 = Y: halftoning pattern */
};

/* #pragma pack(1) to disable padding, required for some structs */

#pragma pack(1)
/* this header identifies the file as bitmap */
typedef struct {
	int16_t header_type; /* generally BM for Windows NT and others */
	int32_t file_size;   /* 14 bytes + DIB header size + pixel data */
	int16_t reserved[2]; /* 2 reserved spaces, both 0 if created manually */
	int32_t offset;      /* where pixels are */
} BMPFileHeader;
#pragma pack(0)

/* DIB headers */

#pragma pack(1)
/* Windows 2.x version, bare-bones */
typedef struct {
    int32_t  header_size;    /* 12 bytes */
    int16_t  bmp_width;      /* image width in pixels */
    int16_t  bmp_height;     /* image width in pixels */
    int16_t  color_planes;   /* must be 1 */
    int16_t  bits_per_pixel; /* normally 1, 4, 8, 16, 24, or 32 */
} BITMAPCOREHEADER;
#pragma pack(0)

/* most used header, common Windows format */
typedef struct {
	uint32_t header_size;           /* 40 bytes */
	int32_t  bmp_width;             /* image width in pixels */
	int32_t  bmp_height;            /* image width in pixels */
	uint16_t color_planes;          /* must be 1 */
	uint16_t bits_per_pixel;        /* normally 1, 4, 8, 16, 24, or 32 */
	uint32_t compression_method;    /* BI_RGB for no compression */
	uint32_t img_size;              /* can be 0 for BI_RGB */
	int32_t  horizontal_resolution; /* in pixels per meter (ppm) */
	int32_t  vertical_resolution;   /* in pixels per meter (ppm) */
	uint32_t num_colors;            /* number of colors in palette */
	uint32_t important_colors;      /* 0 when every color is important */
} BITMAPINFOHEADER;

typedef struct {
    BITMAPINFOHEADER bmpinfo;              /* same info as previous */
    uint16_t         resolution_unit;      /* only ppm is defined */
    uint16_t         padding;              /* ignored, should be 0 */
    uint16_t         bit_fill_direction;   /* only lower-left is defined */
    uint16_t         halftoning;           /* algorithm for rendering image */
    uint32_t         halftoning_params[2]; /* parameters for algorithm */
    uint32_t         color_encoding;       /* only RGB is defined */
    uint32_t         identifier;           /* application defined */

} OS22XBITMAPHEADER;

/*
 * typedef struct {} OS22XBITMAPHEADERVAR  // 1st 16 B of OS22XBITMAPHEADER
 * typedef struct {} BITMAPV2INFOHEADER    // sides now 4 bytes, 16/32 bpp, RL
 * typedef struct {} BITMAPV3INFOHEADER    // RGB bit masks
 * typedef struct {} BITMAPV4HEADER        // color space type, gamma correct
 * typedef struct {} BITMAPV5HEADER        // ICC color profiles
*/

#endif
