# Server Documentation


## Installation
1. Clone the repository: `git clone git@github.com:Left4DeadTaller1/Left4Dead.git`
2. Install the required dependencies: 
   | Library         | Installation Command                   |
   |-----------------|----------------------------------------|
   | `yaml.cpp`      | `sudo apt-get install libyaml-cpp-dev` |
   | `googletest`    | `sudo apt-get install libgtest-dev`    | -> go to item 2.1


2.1  to correctly install googletest, follow this instructions:
   - after running sudo apt-get install libgtest-dev, go to /usr/src/googletest
   with cd /usr/src/googletest
   -Create a build directory within the Google Test source directory.
   with sudo mkdir build
   -Switch to that directory.
   with cd build
   -Run cmake with sudo cmake ..
   -Run make with sudo make
   Install the Google Test library:
   sudo make install
   
3. Build the project: Follow the build instructions provided in the repository's documentation.
 <!-- Add steps later -->


 haber falta lo de revivir jugadores
 lo de remover jugadores inactivos
 lo de cerrar el juego si no hay mas jugadores
 los ataques de cada zombie