/* https://en.wikipedia.org/wiki/BMP_file_format */
/* version 0.2.0 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "bitmap.h"

enum basic_info_modes {
	EXAMPLE1_MODE = 'E',
	EXAMPLE2_MODE = 'e',
	BASIC_MODE 	 = 'B',
	ADVANCED_MODE = 'A'
};

/* Example 1 From Wikipedia */
void bmp_example1_fill(FILE *img, basic_info base);

/* Example 2 From Wikipedia */
void bmp_example2_fill(FILE *img, basic_info base);

/* creates bitmap file with headers */
FILE *bmp_init(basic_info base,
			   int32_t header_field, str dib_header_type);

/* if DIB header option is valid, insert proper BMPFileHeader offset */
void check_dib_header_option(str dib_header, int32_t *offset);

void check_main_args(int argc, char *argv[], basic_info *base);

void show_help();

int main(int argc, char *argv[]) {
	basic_info base = {
		.filename = "",
		.bpp 	  = 0,
		.width 	  = 0,
		.height   = 0,
		.mode 	  = 0
	};
	FILE *bmp;

	check_main_args(argc, argv, &base);

	if (base.mode == EXAMPLE1_MODE) {
		bmp = bmp_init(base, BM, "default");
		bmp_example1_fill(bmp, base);
	}
	/*
	else if (base.mode == EXAMPLE2_MODE) {
		bmp = bmp_init(base, BM, "v4");
		bmp_test_fill(bmp, base);
	}
	*/
/*
	printf("insert bitmap dimensions (W x H): ");

	if (scanf("%d %d", &width, &height) != 2) {
		fprintf(stderr, "1 or more invalid inputs\n");
		exit(1);
	}

	printf("insert bits per pixel (1, 4, 8, 16, 24 (default), or 32): ");

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
*/
	fclose(bmp);

	return 0;
}

FILE *bmp_init(basic_info base,
			   int32_t header_field, str dib_header_type) {
	int32_t offset;

	check_dib_header_option(dib_header_type, &offset);

	FILE *img = fopen(base.filename, "wb");

	if (img == NULL) {
		fprintf(stderr, "Unable to create bitmap.\n");
		return NULL;
	}

	BMPFileHeader file_header = {
		.header_type = BM,
		.file_size 	 = offset + (base.width * base.height * base.bpp) / 8,
		.reserved 	 = {NONE, NONE},
		.offset 	 = offset
	};

	BITMAPINFOHEADER dib_header = {
		.header_size 		   = sizeof(BITMAPINFOHEADER),
		.bmp_width 			   = base.width,
		.bmp_height 		   = base.height,
		.color_planes 		   = COLOR_PLANES,
		.bits_per_pixel 	   = base.bpp, /* RGB */
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
	/*
	else if (!strcmp(dib_header, "os22xvar"))
		*offset = FILE_OFFSET(OS22XBITMAPHEADER);
	else if (!strcmp(dib_header, "v2"))
		*offset = FILE_OFFSET(BITMAPV2INFOHEADER);
	else if (!strcmp(dib_header, "v3"))
		*offset = FILE_OFFSET(BITMAPV3INFOHEADER);
	else if (!strcmp(dib_header, "v4"))
		*offset = FILE_OFFSET(BITMAPV4HEADER);
	else if (!strcmp(dib_header, "v5"))
		*offset = FILE_OFFSET(BITMAPV5HEADER);
	*/
	else {
		fprintf(stderr, "invalid option\n");
		exit(1);
	}
}

void check_main_args(int argc, char *argv[], basic_info *base) {
	if (argc == 3 && !strcmp(argv[1], "--example")) { /* example is done */
		if (atoi(argv[2]) == 1) {
			base->filename = "example1.bmp";
			base->width    = 2;
			base->height   = 2;
			base->bpp 	   = 24;
			base->mode = EXAMPLE1_MODE;
		}
		else if (atoi(argv[2]) == 2) {
			base->filename = "example2.bmp";
			base->width	   = 4;
			base->height   = 2;
			base->bpp      = 32;
			base->mode = EXAMPLE2_MODE;
		}
		else {
			show_help();
			exit(1);
		}
	}
	else if ((argc == 2 && !strcmp(argv[1], "--basic")) || argc == 1)
		base->mode = BASIC_MODE;
	else if (argc == 2 && !strcmp(argv[1], "--advanced"))
		base->mode = ADVANCED_MODE;
	else {
		show_help();
		exit(1);
	}
}

void show_help() { /* done */
	str title    = "BMP File Format Study";
	str args     = "arguments: --basic (default), --example, --advanced";
	str basic    = "--basic: basic functionalities only (patterns, size)";
	str example  = "--example NUM (1 or 2, only): presets from Wikipedia";
	str advanced = "--advanced: full freedom";

	fprintf(stderr, "%s\n%s\n%s\n%s\n%s\n",
			title, args, basic, example, advanced);
}

void bmp_example1_fill(FILE *img, basic_info base) { /* done */
	RGBpixel color[] = {{0, 0, 0xff}, {0xff, 0xff, 0xff},
						{0xff, 0, 0}, {0, 0xff, 0}};
	hex_value nils[2] = {0, 0};

	for (int i = 0; i < (base.width * base.height); i++) {
		fwrite(&color[i], sizeof(RGBpixel), 1, img);

		if (i % base.width == 1)
			fwrite(nils, sizeof(nils), 1, img);

	}
}

void bmp_example2_fill(FILE *img, basic_info base) {
	/* to do */
}
