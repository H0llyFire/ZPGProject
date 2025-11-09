#include "Application.h"

#define TINYOBJLOADER_IMPLEMENTATION
//#define TINYOBJLOADER_USE_MAPBOX_EARCUT
#include "tiny_obj_loader.h"


int main()
{
	Application app{1600, 900};
	app.Init();
	app.Run();
	
}