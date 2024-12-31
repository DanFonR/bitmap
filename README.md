# BMP File Format Study (*By DanFonR*)

## Version 0.3.2

## About

This is simply a small study on how BMP files are structured.  
The information was taken straight out of the [Wikipedia page on BMP files](https://en.wikipedia.org/wiki/BMP_file_format).  
The header file contains several definitions that may or may not be used in the program.  

The intent is to write the program as *clearly* as possible, and explain everything so anyone can understand its structure.  

In the terminal, use ```./bitmap-gen``` (or ```.\bitmap-gen.exe```, if on Windows) with the arguments ```--help``` (or ```-h```), ```--basic``` (```-b``` or nothing), ```--advanced``` (or ```-a```), or ```--example``` (or ```-e```) to show the help menu, enter Basic Mode, enter Advanced Modes, or generate example images, respectively (to be fully implemented).  

### Make

On Linux (or WSL), make sure ```make``` is installed. Then, in the terminal, use ```make``` to create just the example image(s), ```make exec``` to create just the executable, and ```make clean``` to clean everything up.  

### Windows

There *is* a Windows executable available as well, but it isn't signed.  

### Example Mode

Example Mode supersedes the previous DEBUG Mode.  
```make``` generates the 2×2 [example 1 bitmap](https://upload.wikimedia.org/wikipedia/commons/e/e8/Bmp_format.svg).  
In the future, it will also generate the 4×2 [example 2 bitmap](https://upload.wikimedia.org/wikipedia/commons/thumb/3/36/Bmp_format2.svg/390px-Bmp_format2.svg.png).  
Example 3 is _Colliding Planets_, by [Hamid Naderi Yeganeh](https://en.wikipedia.org/wiki/Hamid_Naderi_Yeganeh), taken from [his post on X/Twitter](https://x.com/naderi_yeganeh/status/1845760888512414061) (October 14, 2024). This one is **not** generated automatically by ```make```, as it is **very** computationally demanding, and would take hours/days for the image to be generated.  

## Issues

- Example 3 is generated incorrectly;  
- Example Mode not fully implemented;  
- Basic and Advanced Modes not fully implemented;  
- Windows .exe not signed.    

## License

This repository uses the GNU Affero copyleft license. More info [here](https://www.gnu.org/licenses/agpl-3.0.en.html).  
