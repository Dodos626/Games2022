#pragma once
#ifndef WHEREAMIINCLUDE
#define WHEREAMIINCLUDE

#include <stdio.h>  /* defines FILENAME_MAX */

#include <direct.h>
#define GetCurrentDir _getcwd

void GetPath();

#endif