DOWNLOAD 
SDL2 : "https://github.com/libsdl-org/SDL/releases/tag/release-2.24.0"   
SDL2_image-2.0.1: "https://github.com/libsdl-org/SDL_image/releases"  
SDL2_MIXER-2.0.0: "https://github.com/libsdl-org/SDL_mixer/releases"  
sdl_ttf-2.20.0: "https://github.com/libsdl-org/SDL_ttf/releases"  

PLACE IT IN THE PROJECT DIRECTORY OR ANY OTHER DESIRED DIRECTORIES 

IN MICROSOFT VISUAL STUDIO  
  Include the Hogwarts_0.3 folder in the project.  
  Open the project properties and set to All Platforms   
  Place the include files of all the above SDL folders as additional include files in the project properties (C/C++).    
  Include additional library directories in the linker section of project properties.  
  Add the additional Dependencies: Name of the .lib files of all the above mentioned SDL directories.  
  Include .dll (Dynamic Link Library: a type of file that contains instructions that other programs can call upon to do certain things)  
    files in the the game folder that includes the visual studio solution file.  
