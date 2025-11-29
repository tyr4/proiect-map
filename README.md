# Proiect sincretic MAP - Turn images and videos into ASCII art

## Overview
This is a C++ CLI program that uses CMake for builds and includes a Dockerfile for containerized builds and execution. The repository contains source code under `src/`, public headers under `include/`, and an `input/` directory intended for input data or sample files. The project is licensed under the MIT License.

## Repository layout
- `.github/workflows/` - Docker Build & Push Action to Dockerhub
- `include/` - public headers
- `input/` - sample test files, includes `.png`, `.jpg` and `.mp4` formats
- `src/` - implementation source files
- `CMakeLists.txt` - CMake configuration file for building the binary
- `Dockerfile` - image to build/run the project in a container

## Requirements
- C++ compiler with C++20
- CMake 3.16+
- make / ninja or appropriate build tool
- External libraries:
    - OpenCV
    - cxxopts
    - ccache (optional, can be removed from CMake, build time optimization)
- Docker (optional, for using the Dockerfile)

## Building locally (recommended)
Clone the repository:
```bash
git clone https://github.com/tyr4/proiect-map.git
cd proiect-map
```
<br>

Create and enter a build directory:
```bash
mkdir build
cd build
```
<br>

Configure with CMake and build:
```bash
cmake ..
cmake --build .
```
<br>

Alternatively, you can also use `ninja` to build for faster times:
```bash
cmake ..
cmake -G Ninja
ninja # acts the same as cmake --build .
```
<br>

The executable will be named `MAP_ascii_from_image`. You can run it with:
```bash
./MAP_ascii_from_image
```
With no arguments, it will print the help command which will server as a guide for building an actual command.

## Running with Docker
Pull the image from the Dockerhub:
```bash
docker pull tyr4/ascii-art:latest
```
This will take a while, it's about 1.5GB (99% is just the image processing library)

<br>

Run the Docker image:
```bash
docker run ascii-art:latest
```
This will behave the same way as the `./MAP_ascii_from_image` command, as no arguments have been given.

## Example commands
When you run the program with no arguments, or the `--help` option, the following will print:
```
  MAP-ascii-from-image [OPTION...]

  -i, --input arg    Input a path to the image.
  -o, --output arg   Output to the specified path. (default: "")
  -w, --width arg    Set the width in characters of the ASCII art. 
                     (default: 120)
  -c, --charset arg  Set the charset to be used. Recommended order is 
                     lowest to greatestin terms of fill. (default:   
                     .,;:=+*oahkbdpzmqAXHNRDQ0M&B8$W#%@)
  -f, --filter arg   Set the filter to be applied before processing the 
                     image. Options: Blur, Grayscale, Inverse, Contrast. 
                     (default: "")
  -a, --amount arg   Amount of blur/contrast for the filters.
                     Blur amount: e.g. '5' blurs in a 5x5 neighbor grid
                     Contrast amount: e.g. >1 increases contrast and <1 
                     decreases contrast (turns it into pitch black) 
                     (default: 5)
  -l, --logo arg     Converts the text input into logo art. (default: "")
  -r, --color        Enable ANSI color support.
  -t, --terminal     Enable terminal output.
  -h, --help         Prints this help command!
```
### Executable
The following command is the most basic example to test the program. It passes an **input file** (`-i` or `--input`), and enables **terminal output** (`-t` or `--terminal`).
```bash
./MAP_ascii_from_image -i /home/user/my-images/wowcoolimage.png -t
```
<br>

The following command also passes an **output file** (`-o` or `--output`), **width** (`-w` or `--width`) and **charset** (`-c` or `--charset`):
```bash
./MAP_ascii_from_image -i /home/user/not-my-images/ilovepenguins.jpg --output /home/user/very_secret.txt --width 150 -c " .:+a#%@" -t
```
<br>

If you feel like typing a lot and building a mega command, here's an example using all available parameters:
```bash
./MAP_ascii_from_image --input /home/user/probably-my-images/AIslop.jpg --output /home/user/whatisthis.txt --filter blur --amount 30 --width 200 --charset "  123456" --terminal --color
```

### Docker
The only different thing here is mounting a local input folder to the container. The rest of the parameters can be used as normal.
```bash
docker run -v /home/user/my-images/:/input ascii-art:latest -i /input/yourlocalimage.png (rest of the stuff)
```
The command above links the local `my-images/` directory to the `/input` container directory. That path becomes the path for your local directory inside the container. 

## Example output
All the input files can be found in the `input/` directory.

Command:
```bash
./MAP_ascii_from_image -i ../input/upt.jpg -o ../output/output.txt -t -w 80
```

Output:
```
                                                                                
                                                                                
                                  +zAAp*                                        
                                 .Q&BBBMH,                                      
                                  pMBBBBMA                                      
                                  :0BBBBBD,                                     
                                  ;0BBBBBD.                                     
                                  a0BBBB&q                                      
                                 ;D&BBB&0mbpmAAAqpo,                            
                                :R&BBBBBBBBBBBB&&&M0Nza,                        
                              ,p0&BBBBB88888BBB&&&MMMM0Rk                       
                     +qXAmzbkmQ&&BB8888888888B&&MQQQQQQDq                       
                    aQMMMMMM&&BBB88888BB888BBB&&&M0QRNAa                        
                   ,RM&&&&&&BBBBBBBBBBBBBBBBB&&&&MMM00QH*                       
                   oQ&&&&&BBBBBBBBBBBBBBBB8BB&&&MQDDDQQRk                       
                   =Q&&&&&&&&&&&&&&&&&BBBBBBB&&&M0DRNHz*                        
                    XM&&&&&&&&&&&&&&&&&&&BBBB&&&MMM00QHa                        
                    :RMMMMMMMMMMMMMM&&&&&BBBB&M0QQQQQDNo                        
                     +NQQQQQQRRDQQ000MMM&&&&&&&&M0QDHb:                         
                      .kHRHzh=;+hbpqXHRRD00M&&&&&&MM0QRNqzh=                    
                         .                .:+hdmXDQ000QQQDDHa                   
                                                   ,=ohdmmzk,                   
                                                                                
                                                                                

```
<br>
Command:

```bash
./MAP_ascii_from_image -i ../input/slide1.jpg -o ../output/output.txt --filter contrast --amount 1 -t -c "@#$%dwnf:.  "
```

Output:
```
......::::::::::::::::::::::::::::ff::fffnnnnnnnnnnnnnnnnnnnnwwwwwwwwwwdddddddddddddddddddddddddddddddddddddddd%%%%%%%%%
 ...:::::::::::::::::::::::::::::::::::ffnnnnffnnnnnnnnnnnnnnwwwwwwwddddddddddddddddddddddddddddddddddddddddddddddddd%%%
    ......:::::::::::::::::::::.::::::fffffffffffnnnnnnnfffnnnwwwwwdddddddddddddddddddddddddddddddddddddddddddddddddddd%
       ...:::::::::::::::::::::.::::fffffffffffffffffffffffnnnnwwwdddddddddddddddddddddddddddddddddddddddddddddddddddddd
          .......:::::::::::::::.::fffffffffffffffffffffffnnnnwwdddddddddddddddddddddddddddddddddddddddddddddddddddddddd
                 ...:::::::::::::::::ffffffffffffffffffffnnnwwwddddddddddddddddddddddddddddddddddddddddddddddddddddddddd
                  ....:::::::::::::::ffffffffffffffffffnnwwwwwwwwddddddddddddddddddddddddddddddddddddddddddddddddddddddd
                ...::::.::::::::::::::::::::ffffffffnnnwwwwwwwwddddddddddddddddddddddddddddddddddddddddddddddddddddddddd
      ............:::::::::::::::::::::::::::fffnnnnwwwwwwwwwwwddddddddddddddddddddddddddddddddddddddddddddddddddddddddd
...............::::::::::::::::::::::::::::ffnnnnwwwwwwwwwwwwwwwwwddddddddddddddddddddddddddddddddddddddddddddddwwwwwwww
..............::..:::::::::::::::::::::ffffnnnnnnnnnnnnnnnfnfnwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
..........::::nd:.......:::::fffffffffffnnnnnnnnnnnnnnnnnn:nfnnnwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwnfnnnnnnnnn
........::::::nwwn:......:::fffffffffnnnnnnnnnnnnnnnnnnnnnndwdnnnnnnnnnnnnwwwwwwwwwwwwwwwwwwwwnnnnnnnnnnnnnnnnwnnnffffff
.......:::::::wdwdwwf:.::::ffffffffffffffffffffffffnnnnnnnnwwdnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnfndnff::::::
....:nndw:::fwwwwwwd%wnffffffffffffffffffffffffffffffffffnnddwnfffffffffnnnnnnnnnnnnnfffffff::::::ffndnffffffndn::::::::
.::::nfwnnnwwdnwnwnw%%dndnfffffffffffffffffffffffffffffffffndffffffffffffffffffffffff::::.........::fnf::::::nwwf.......
:fnwwdd%%%ddwwwwdwwwwddd%%wnwwwnnwnfffnnnffff::::::::::::ffnwfffffffffffff:::::::::................:d%d:.....nwn:.....:f
%dddwwnnnfnn:dwwdwww%%%ddddw$$$dwdw%dwwwwwwwwnnnnf:::::::::nwfffffffff:::::ff::.............:.....::fffn:...ff::f...:fff
fnnnfffffndw:d%%%%dw%dd%dwdwwwwwwdwd%%%$$w$$%nwwwwwnfffffnwnw:::::::::::::::::fwf:........:nwn:::::::ffnf:::.f%.f:ffffnn
fndnfnnnfffnnwwdd%dw$$#$%%%wwd%wwdwwwdnwnwwddwwwd%%w$%nnnn%fndwnnf::....:f.:ff.n.f::::ff::nd%wf:::fffnnwwwnnffwnwwwwwwww
nnnwfnnnwwnwnwdd%dwn%%d%dwwdd$$$ddd%%%nwnwnnnfwnnnwwnwnwwwnfw$%%dd%nd:::::::::..fnff::::ffw%%$df:ffnnnnwd%$$$df:fwwdwwdw
nnnwddw%wfnwwddwwwdd$#$$$%%%d%$dw%wd$%nwndwwwfnnnnnnnnw#%wnfw%##%%d:::::....:....ff:ff::nfnd$$$wnffnnnnwd%$###%nf::nnnf:
ddddw%dw%ddn$#$#$$$$###$###$%$#$%%%$$$nwnwnwnnwwnwwwwwd#wwnww%$#ddd:f::f:n::n:.n:fn.:n.:wnw$##$n..:::ffnw%$###%%w:.fnf:.
%wwwnwnwnfnn$###$##%$$$$$$$%d%%$$$%#%%wwwdwdwnw%wwnwwwd$nddddd%$%%df:.:f.:.:n::f.f:.::.:nnw$##wn:ffff:ffn%$#@#w%w::f:::f
wwddwdwwdwdn%#$#$#%%##$$#$$%dd%%###$%$dddwddddddddwdddd$nwnnfnnnnw%:f:ff..:d$dnn:ff::f.:wnd$#%wf.:::: :nn%##$%%$dnwwddnw
%d##%%%d$%$nd###$#$%$##$$$$%%%%dd%%d%dwdwdwwwwd$wwwdwdw%:nwwwwwwnnn::::n:ff%#%fw:fn.fn.:%d%$###d.::..f:wnwd$$$$%n::ndwf:
dd%%wd%wddd%%%%%%$ddd%%%%%%%%%dd%%%%%%%%%%dddddddwdwwwn:.fwdddddwwwfnnnwwwwwwnfnffnfffffnnwnffnf:fnnnwf%ww%ddwnnnnfnwnnn
wwwwdwdddddwwnnff:::::fnwdddddddddddddddddddddwwnf::fnnnnnnnnnnfnwdddddddwddddddddddddddddddddwdwwwwwwnnnnwnnnnnnnnnnnnn
nnnnnnnnff:::::::::::::::::::::fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff
............:::::::::fnwwwwddddddddddddddwwwdddwwwwwwwwwwwwwwwwwwwddddwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwddddwwwwwwwwwwwww
.................::::fwwddddd%ddd%%%%ddddd%%%%%%%%%d%%%%%%%ddddddddddddddddddddddd%%ddddd%%dddddddd%%%dddddddddddddddddd
..................::::nwd%%%ddd%dd%%%%%%ddd%%%%%%%%%%%%%%d%%%%%%dddddd%%dddd%%dddd%%%%%%%%%%%%dddddddddddddddddddddddddd
.......:..:.:..::::::::nwwdd%%dddddddddddddddddd%ddddddd%d%%%%ddd%ddd%%%%%%%%%%%%%%%%%%%%%%%%%%%%%ddddd%d%%ddddddddddd%d
.:...::::.:::::::.:::::fnwwd%%%%ddddddddddddddd%%%%%%%ddd%%%%ddd%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%dddddddd%%%%%%%dddddddddd
:.:::::::::::::::::::::ffnwd%%%%%ddddddddddddddddd%ddddddd%%%%%%%%%%%%%%%d%%%%dd%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%dd%%%%%%%
.:::::::::::::::::::::::fnwwd%%%%d%%%%%%dddd%ddddddddd%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%ddddddd%
:::::::::::::::::::::::::fw%d%%%%%%%%%%%%%%%%dddd%%%%%%%%%%%%%%%dd%%%%%%%%dd%%%%%%%%%%%%%%%%%%%%%%%d%%%%%%%%%%%%%%dddd%%
::::::::::.::::::::::::::ffndd%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%d%ddd%%%
:::::::::::::::::::::::::::nnww%$%$%%%%%%%%%d%%%%ddd%d%%%%%%$%$$$%%%%%%%%%%%%%%%%%%%%%%%%%%%%d%%%d%%%%%%%%%%%%%%%%%%%%%%
:::.:::::::::::::::::::::::fnnnwwdd%%%%%%ddddd%ddddd%%%%%%$$$$$$%$$%%%%%%%%$$%%%%%%%%%%%%%%%%%ddd%%%ddd%%%d%%ddddd%dddd%
Sent output to: ../output/output.txt
```
<br>
Command:

```bash
./MAP_ascii_from_image -i ../input/slide1.jpg -t --color
```

Output:

![who reads fthis](/assets/result1.png)

<br>
Command:

```bash
./MAP_ascii_from_image -i ../input/upt.jpg -t -w 150 --color
```

Output:

![who reads fthis](/assets/result2.png)

<br>
Command:

```bash
./MAP_ascii_from_image -i ../input/BadApple.mp4
```

Output:

![insert alt text](/assets/badapple.gif)

## Other stuff
If, for some reason, you want cool banner text, you can also do:
```bash
./MAP_ascii_from_image --logo cooltext
```
The command above will give the following terminal output:
```
 ██████╗  ██████╗   ██████╗  ██╗      ████████╗ ███████╗ ██╗  ██╗ ████████╗ 
██╔════╝ ██╔═══██╗ ██╔═══██╗ ██║      ╚══██╔══╝ ██╔════╝ ╚██╗██╔╝ ╚══██╔══╝ 
██║      ██║   ██║ ██║   ██║ ██║         ██║    █████╗    ╚███╔╝     ██║    
██║      ██║   ██║ ██║   ██║ ██║         ██║    ██╔══╝    ██╔██╗     ██║    
╚██████╗ ╚██████╔╝ ╚██████╔╝ ███████╗    ██║    ███████╗ ██╔╝ ██╗    ██║    
 ╚═════╝  ╚═════╝   ╚═════╝  ╚══════╝    ╚═╝    ╚══════╝ ╚═╝  ╚═╝    ╚═╝  
```


## Troubleshooting
- If CMake reports a missing dependency, install the required system packages (compiler, libraries)
- For build errors, re-run CMake from a clean `build/` directory
- If Docker builds fail, check the Dockerfile and build context