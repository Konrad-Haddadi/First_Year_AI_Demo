#pragma once

#include "Azimuth/Azimuth.h"

#include "Azimuth/Resources/Resource.h"

#include <raylib/raylib.h>
class ImageResource : public Resource<Image>
{
public:
	DLL ImageResource(const char* _path);

};
