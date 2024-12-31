/* https://en.wikipedia.org/wiki/BMP_file_format */
/* version 0.3.2 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "bitmap.h"

#define ERASE_LINE(file) fprintf(file, "\x01b[2K\r") 

enum basic_info_modes {
	EXAMPLE1_MODE = '1',
	EXAMPLE2_MODE = '2',
	EXAMPLE3_MODE = '3',
	BASIC_MODE 	 = 'B',
	ADVANCED_MODE = 'A'
};

/* Example 1 From Wikipedia */
void bmp_example1(FILE *img, basic_info base);

/* Example 2 From Wikipedia */
void bmp_example2(FILE *img, basic_info base);

/* Example 3 by Hamid Naderi Yeganeh */
void bmp_example3(FILE *img, basic_info base);

/* creates bitmap file with headers */
FILE *bmp_init(basic_info base,
			   int32_t header_field, dib_header dib_header_option);

/* if DIB header option is valid, insert proper BMPFileHeader offset */
void check_dib_header_option(dib_header dib_header_option, int32_t *offset);

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
		bmp_example1(bmp, base);
	}
	/*
	else if (base.mode == EXAMPLE2_MODE) {
		bmp = bmp_init(base, BM, "v4");
		bmp_example2(bmp, base);
	}
	*/
	else if (base.mode == EXAMPLE3_MODE) {
		bmp = bmp_init(base, BM, "default");
		bmp_example3(bmp, base);
	}
/*
	printf("insert bitmap dimensions (W x H): ");

	if (scanf("%d %d", &width, &height) != 2) {
		fprintf(stderr, "1 or more invalid inputs\n");
		exit(EXIT_FAILURE);
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
			exit(EXIT_FAILURE);
	}
*/
	fclose(bmp);

	return 0;
}

FILE *bmp_init(basic_info base,
			   int32_t header_field, dib_header dib_header_option) {
	int32_t offset;

	check_dib_header_option(dib_header_option, &offset);

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

void check_dib_header_option(dib_header dib_header_option, int32_t *offset) {
	size_t length = strlen(dib_header_option);

	if (!strncmp(dib_header_option, "default", length))
		*offset = FILE_OFFSET(BITMAPINFOHEADER);
	else if (!strncmp(dib_header_option, "core", length))
		*offset = FILE_OFFSET(BITMAPCOREHEADER);
	else if (!strncmp(dib_header_option, "os22x", length))
		*offset = FILE_OFFSET(OS22XBITMAPHEADER);
	/*
	else if (!strncmp(dib_header, "os22xvar", length))
		*offset = FILE_OFFSET(OS22XBITMAPHEADER);
	else if (!strncmp(dib_header, "v2", length))
		*offset = FILE_OFFSET(BITMAPV2INFOHEADER);
	else if (!strncmp(dib_header, "v3", length))
		*offset = FILE_OFFSET(BITMAPV3INFOHEADER);
	else if (!strncmp(dib_header, "v4", length))
		*offset = FILE_OFFSET(BITMAPV4HEADER);
	else if (!strncmp(dib_header, "v5", length))
		*offset = FILE_OFFSET(BITMAPV5HEADER);
	*/
	else {
		fprintf(stderr, "invalid option\n");
		exit(EXIT_FAILURE);
	}
}

void check_main_args(int argc, char *argv[], basic_info *base) {
	if (argc == 3 && !(strcmp(argv[1], "--example")
					   && strcmp(argv[1], "-e"))) {
		if (atoi(argv[2]) == 1) {
			strcpy(base->filename, "example1.bmp");

			base->width    = 2;
			base->height   = 2;
			base->bpp 	   = 24;
			base->mode 	   = EXAMPLE1_MODE;
		}
		else if (atoi(argv[2]) == 2) {
			strcpy(base->filename, "example2.bmp");

			base->width	   = 4;
			base->height   = 2;
			base->bpp      = 32;
			base->mode 	   = EXAMPLE2_MODE;
		}
		else if (atoi(argv[2]) == 3) {
			char c;

			fprintf(stderr, "are you sure? "
						    "it will take literal days to generate [y/N] ");

			if ((c = getchar()) != 'y' && c != 'Y') {
				fprintf(stderr, "ok. exiting...\n");
				exit(0);
			}

			fprintf(stderr, "starting image generation...\n\n");
			strcpy(base->filename, "example3.bmp");

			base->width	   = 2100;
			base->height   = 1200;
			base->bpp      = 24;
			base->mode 	   = EXAMPLE3_MODE;
		}
		else {
			fprintf(stderr,
				    "invalid options\n use options \"1\", \"2\""
					" or \"3\" for example images");
			exit(EXIT_FAILURE);
		}
	}
	else if ((argc == 2 && !(strncmp(argv[1], "--basic", 7)
							 && strncmp(argv[1], "-b", 2))) || argc == 1)
		base->mode = BASIC_MODE;
	else if (argc == 2 && !(strncmp(argv[1], "--advanced", 10)
							&& strncmp(argv[1], "-a", 2)))
		base->mode = ADVANCED_MODE;
	else if (argc == 2 && !(strncmp(argv[1], "--help", 6)
							&& strncmp(argv[1], "-h", 2))) {
		show_help();
		exit(EXIT_SUCCESS);
	}
	else {
		fprintf(stderr, "invalid argument\n use \"--help\" or \"-h\"");
		exit(EXIT_FAILURE);
	}
}

void show_help() {
	help_string title    = "BMP File Format Study";
	help_string args     = "arguments: --example/-e (default),"
				   		   " --basic/-b, --advanced/-a, --help/-h";
	help_string basic    = "--basic/-b: basic functionalities only (patterns, size)";
	help_string example  = "--example/-e: NUM (1 or 2, only): presets from Wikipedia";
	help_string advanced = "--advanced/-a: full freedom";
	help_string help 	 = "--help/-h: shows this help";

	fprintf(stderr, "%s\n%s\n%s\n%s\n%s\n%s\n",
			title, args, basic,
			example, advanced, help);
}

void bmp_example1(FILE *img, basic_info base) {
	RGBpixel color[] = {{0, 0, 0xff}, {0xff, 0xff, 0xff},
						{0xff, 0, 0}, {0, 0xff, 0}};
	hex_value padding[2] = {0, 0};

	for (int i = 0; i < (base.width * base.height); i++) {
		fwrite(&color[i], sizeof(RGBpixel), 1, img);

		if (i % base.width == 1)
			fwrite(padding, sizeof(padding), 1, img);

	}
}

void bmp_example2(FILE *img, basic_info base) {
	/* to do */
}

void bmp_example3(FILE *img, basic_info base) {

	RGBpixel  yeganeh[YEGANEH_HEIGHT][YEGANEH_WIDTH];
	hex_value padding[4] = {0, 0, 0, 0};
	float     progress   = 0.0F;

	for (int n = 0; n < base.height; n++) {
		for (int m = 0; m < base.width; m++) {
			double x = (m + 1 - 970) / 652;
			double y = (601 - (1200 - n)) / 652;

			yeganeh[n][m][RGB_RED] 	 = F(H(0, x, y));
			yeganeh[n][m][RGB_GREEN] = F(H(1, x, y));
			yeganeh[n][m][RGB_BLUE]  = F(H(2, x, y));

		}

		fwrite(yeganeh[n], sizeof(RGBpixel), base.width, img);
		fwrite(padding, sizeof(padding), 1, img);
		
		if (n % (base.height / 100) == 0) {
			progress += 0.1F;

			ERASE_LINE(stderr);
			fprintf(stderr, "image %.1f%% done", progress);
		}
	}

	fprintf(stderr, "\n");
}
