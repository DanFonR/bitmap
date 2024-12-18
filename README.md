# BMP File Format Study (*By DanFonR*)

## About

This is simply a small study on how BMP files are structured.  
The information was taken straight out of the [Wikipedia page on BMP files](https://en.wikipedia.org/wiki/BMP_file_format).  
The header file contains several definitions that may or may not be used in the program.  

The intent is to write the program as *clearly* as possible, and explain everything so anyone can understand its structure.  

In the terminal, use ```./bitmap-gen``` (or ```.\bitmap-gen.exe```, if on Windows) with the arguments ```--help``` (or ```-h```), ```--basic``` (```-b``` or nothing), or ```--advanced``` (or ```-a```) to show the help menu, enter Basic Mode, or enter Advanced Modes, respectively (to be implemented).  

### Make

On Linux (or WSL), make sure ```make``` is installed. Then, in the terminal, use ```make``` to create just the example image(s), ```make exec``` to create just the executable, and ```make clean``` to clean everything up.  

### Windows

There *is* a Windows executable available as well, but it isn't signed.  

### ~~DEBUG Mode~~

~~The C file has a ```#define``` directive to turn **DEBUG** mode on or off. Comment it out to turn it off, uncomment to turn it on.~~  
~~The next ```make``` will generate a test .bmp file.~~  
~~**DEBUG** output should match [this image](https://upload.wikimedia.org/wikipedia/commons/e/e8/Bmp_format.svg).~~  

### Example Mode

Example Mode supersedes the previous DEBUG Mode.  
```make``` generates the 2×2 [example 1 bitmap](https://upload.wikimedia.org/wikipedia/commons/e/e8/Bmp_format.svg).  
In the future, it will also generate the 4×2 [example 2 bitmap](https://upload.wikimedia.org/wikipedia/commons/thumb/3/36/Bmp_format2.svg/390px-Bmp_format2.svg.png).  

## Issues

- ~~The test .bmp is generated incorrectly~~ (Fixed in version 0.1.1: Wrong [endianness](https://en.wikipedia.org/wiki/Endianness) in [```header_field_values```](./src/bitmap.h));  
- ~~Non-DEBUG mode not fully implemented~~ (Changed in version 0.2.0: Superseded by Example Mode);  
- Example Mode not fully implemented;  
- Basic and Advanced Modes not fully implemented;  
- Windows .exe not signed;  
- Windows .exe now not working (for now has been removed).  

## License

This repository uses the GNU Affero copyleft license. More info [here](https://www.gnu.org/licenses/agpl-3.0.en.html).  
