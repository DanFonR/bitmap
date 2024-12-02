# BMP File Format Study (*By DanFonR*)

## About

This is simply a small study on how BMP files are structured.  
The information was taken straight out of the [Wikipedia page on BMP files](https://en.wikipedia.org/wiki/BMP_file_format).  
The header file contains several definitions that may or may not be used in the program.  

### Make

On Linux (or WSL), use ```make``` to create just the image, ```make exec``` to create just the executable, and ```make clean``` to clean everything up.  

### Windows

There *is* a Windows executable available as well, but it isn't signed.  

### DEBUG Mode

The C file has a ```#define``` directive to turn **DEBUG** mode on or off. Comment it out to turn it off, uncomment to turn it on.  
The next ```make``` will generate a test .bmp file.  
**DEBUG** output should match [this image](https://upload.wikimedia.org/wikipedia/commons/e/e8/Bmp_format.svg)

## Issues

- ~~The test .bmp is generated incorrectly~~ (wrong [endianness](https://en.wikipedia.org/wiki/Endianness) in [```header_field_values```](./src/bitmap.h); Fixed in version 0.1.1);  
- Non-DEBUG mode not fully implemented;  
- Windows .exe not signed .  

## License

This repository uses the GNU Affero copyleft license. More info [here](https://www.gnu.org/licenses/agpl-3.0.en.html).  
