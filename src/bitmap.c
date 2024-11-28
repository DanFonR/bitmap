/* https://en.wikipedia.org/wiki/BMP_file_format */
/* version 0.1.1 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "bitmap.h"

#define DEBUG /* uncomment this line for testing */

#ifdef DEBUG
	static const int32_t  test_offset 	    = FILE_OFFSET(BITMAPINFOHEADER);
	static const uint32_t test_width  		= 2;
	static const uint32_t test_height 		= 2;
	static const uint16_t test_bpp    		= 24;
	static const uint32_t test_header_field = BM;
	static const str	  test_dib_header 	= "default"; /* BITMAPINFOHEADER */

	/* test fills with red white blue green */
	void bmp_test_fill(FILE *img, uint32_t width, uint32_t height);

#endif

/* creates bitmap file with headers */
FILE *bmp_init(str file_name, uint32_t width,
			   uint32_t height, uint16_t bpp,
			   uint32_t header_field, str dib_header);

/* if DIB header option is valid, insert proper BMPFileHeader offset */
void check_dib_header_option(str dib_header, int32_t *offset);

int main(int argc, char *argv[]) {
	uint32_t width, height;
	uint16_t bpp = 24;
	str filename = (argc == 2)? argv[1] : "output.bmp";

	#ifdef DEBUG
		width = test_width, height = test_height;
		bpp = test_bpp;
		
	#else
		printf("insert bitmap dimensions (W x H): ");

		if (scanf("%d %d", &width, &height) != 2) {
			fprintf(stderr, "1 or more invalid inputs\n");
			exit(1);
		}

		printf("insert bits per pixel (1, 4, 8, 16, 24, or 32): ");

		if (scanf("%d", &bpp) != 1)
			fprintf(stderr, "invalid input. defaulting to 24 bpp\n");

		switch (bpp) {
			case 1:
			case 4:
			case 8:
			case 16:
			case 24:
			case 32:
				break;
			default:
				fprintf(stderr, "invalid number of bits\n");
				exit(1);
		}
	#endif


	FILE *bmp = bmp_init(filename, width, height, bpp,
						 BM, test_dib_header);
	
	#ifdef DEBUG
		bmp_test_fill(bmp, width, height);
	#endif
	

	fclose(bmp);
	return 0;
}

FILE *bmp_init(str file_name, uint32_t width,
			   uint32_t height, uint16_t bpp,
			   uint32_t header_field, str dib_header_type) {
	int32_t offset;

	#ifdef DEBUG
		offset = test_offset;
	#else
		check_dib_header_option(dib_header_type, &offset);
	#endif

	FILE *img = fopen(file_name, "wb");

	if (img == NULL) {
		fprintf(stderr, "Unable to create bitmap.\n");
		return NULL;
	}

	BMPFileHeader file_header = {
		.header_type = BM,
		.file_size 	 = test_offset + (width * height * bpp) / 8,
		.reserved 	 = {NONE, NONE},
		.offset 	 = offset
	};

	BITMAPINFOHEADER dib_header = {
		.header_size 		   = sizeof(BITMAPINFOHEADER),
		.bmp_width 			   = width,
		.bmp_height 		   = height,
		.color_planes 		   = COLOR_PLANES,
		.bits_per_pixel 	   = bpp, /* RGB */
		.compression_method    = BI_RGB,
		.img_size 			   = NONE,
		.horizontal_resolution = 2835,
		.vertical_resolution   = 2835,
		.num_colors 		   = DEFAULT_COLOR_PALETTE,
		.important_colors 	   = DEFAULT_IMPORTANT_COLORS
	};

	fwrite(&file_header, sizeof(BMPFileHeader), 1, img);
	fwrite(&dib_header, sizeof(BITMAPINFOHEADER), 1, img);

	return img;
}

void check_dib_header_option(str dib_header, int32_t *offset) {
	if (!strcmp(dib_header, "default"))
		*offset = FILE_OFFSET(BITMAPINFOHEADER);
	else if (!strcmp(dib_header, "core"))
		*offset = FILE_OFFSET(BITMAPCOREHEADER);
	else if (!strcmp(dib_header, "os22x"))
		*offset = FILE_OFFSET(OS22XBITMAPHEADER);
	else {
		fprintf(stderr, "invalid option\n");
		exit(1);
	}
}

#ifdef DEBUG
	void bmp_test_fill(FILE *img, uint32_t width, uint32_t height) {
		if (fseek(img, test_offset, SEEK_SET) != 0)
			return;

		RGBpixel color[] = {{0, 0, 0xff}, {0xff, 0xff, 0xff},
							{0xff, 0, 0}, {0, 0xff, 0}};
		hex_value nils[2] = {0, 0};

		for (int i = 0; i < (test_width * test_height); i++) {
			fwrite(&color[i], sizeof(RGBpixel), 1, img);

			if (i % test_width == 1)
				fwrite(nils, sizeof(nils), 1, img);

		}
	}
#endif
