#pragma once
#ifndef VOXELMAPGEN_H
#define VOXELMAPGEN_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>
#include <direct.h>

class VoxelMapGen
{
public:
	Chunk VoxelMapGen(float f[16][16], int x, int y, int freq, int floor, int ceiling);
	VoxelMapGen();
	~VoxelMapGen();
};
#endif