#pragma once

#include "Azimuth/Azimuth.h"

#include "Azimuth/Resources/Resource.h"

#include <raylib/raylib.h>
class FontResource : public Resource<Font>
{
public:
	DLL FontResource(string _path);

};
