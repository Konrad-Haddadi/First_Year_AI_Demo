#pragma once

#include "Azimuth/Azimuth.h"

#include "Azimuth/Resources/Resource.h"

#include <raylib/raylib.h>
class TextureResource : public Resource<Texture2D>
{
public:
	DLL TextureResource(string _path);

};

