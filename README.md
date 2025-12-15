# A tiny window manager aimed to learn X11 and its functionalities.

## Prerequisites
This program must be run from a linux system, because it relies on packages like **X11** (Display Server) and **Sddm** (Display Manager) and the libraries involving them.

## Run the code
We need to use the X11 library as linker in order to run the program. Thus, compile the code using:
```bash
gcc -lX11 main.c -o main
```