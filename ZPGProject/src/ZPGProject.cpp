#include "Application.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


int main()
{
	Application app{1600, 900};
	app.Init();
	app.Run();
	
}