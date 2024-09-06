#pragma once

#include "Azimuth/Azimuth.h"

#include "Azimuth/Resources/Resource.h"

#include <raylib/raylib.h>
class SoundResource : public Resource<Sound>
{
public:
	DLL SoundResource(string _path);

};

