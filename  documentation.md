
Primero se instalan dependencias que van a necesitar desde apt-get

sudo apt-get install libjpeg-dev libpng-dev libfreetype-dev libopusfile-dev libflac-dev libxmp-dev libfluidsynth-dev libwavpack-dev cmake libmodplug-dev libsdl2-dev

 para instalar y usar la versión 0.18 de libsdl2pp, van a necesitar las ultimas versiones de 
 libsdl2-image ( 2.6.3, https://github.com/libsdl-org/SDL_image/releases/tag/release-2.6.3)
 libsdl2-mixer (2.6.3, https://github.com/libsdl-org/SDL_mixer/releases/tag/release-2.6.3)
 libsdl2-ttf (2.20.2, https://github.com/libsdl-org/SDL_ttf/releases/tag/release-2.20.2)

Se bajan los fuentes de cada uno (yo lo hice así), en formato zip, los descomprimen, los compilan e instalan, todos se hacen de la misma forma:

cd carpeta_sdl_x
mkdir build
cd build
cmake ..
make -j4
sudo make install #importante que hagan esto como sudo!

una vez que compilaron e instalaron las ultimas versiones de libsdl2-{mixer, ttf, image}. compilan e instalan la version 0.18.1 de libsdl2pp

cd libSDL2pp-0.18.1
mkdir build
cd build
cmake ..
make -j4
sudo make install #importante que hagan esto como sudo!

