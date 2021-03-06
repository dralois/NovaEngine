#pragma once

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <random>
#include <vector>
#include <ctime>

#include "SimpleImage.h"
#include "TextureGenerator.h"

#include "DiamondSquare.h"
#include "NormalsTexturesGen.h"

#define IDX(x, y, w) ((x) + (y) * (w))

using namespace std;

// Makes an array smaller by a factor
void X_DownsizeArray(float * &pi_dArray, const int &pi_iResolution, const int &pi_iFactor)
{
	float * l_dReturn = new float[(pi_iResolution / pi_iFactor) * (pi_iResolution / pi_iFactor)];
	// Calculate and save avg
	for (int x = 0; x < (pi_iResolution / pi_iFactor); x++)
	{
		for (int y = 0; y < (pi_iResolution / pi_iFactor); y++)
		{
			float l_dAvg = 0.0F;
			// Sum up certain area
			for (int i = x * pi_iFactor; i < (x * pi_iFactor) + pi_iFactor; i++)
			{
				for (int j = y * pi_iFactor; j < (y * pi_iFactor) + pi_iFactor; j++)
				{
					l_dAvg += pi_dArray[IDX(i, j, pi_iResolution)];
				}
			}
			// Save
			l_dAvg /= (pi_iFactor * pi_iFactor) * 1.0F;
			l_dReturn[(IDX(x, y, pi_iResolution / pi_iFactor))] = l_dAvg;
		}
	}
	// Cleanup and return
	delete[] pi_dArray;
	pi_dArray = l_dReturn;
}

int main(int argc, char* argv[])
{
	int l_iResolution;
	// Check arguments
	if (argc != 9)
	{
		cerr << "Incorrect number of arguments!" << endl;
		system("pause");
		exit(1);
	}
	else if ((l_iResolution = atoi(argv[2])) <= 0)
	{
		cerr << "Resolution is zero or not valid!" << endl;
		system("pause");
		exit(1);
	}		
	// Create DS calculator
	DiamondSquare l_dSquare (l_iResolution);
	// Compute and smooth heighfield
	l_dSquare.Compute(10);
	// Save heightfield
	float *&l_dDSquareHeightField = l_dSquare.GetHeightField();
	// Create texture and normals generator
	NormalsTexturesGen l_MyGen ("../../../Assets/textures/gras01.jpg",
								"../../../Assets/textures/mud01.jpg",
								"../../../Assets/textures/pebble03.jpg",
								"../../../Assets/textures/rock04.jpg");	
	// Generate textures
	l_MyGen.GenerateAndStore(l_dDSquareHeightField, l_iResolution, argv[6], argv[8]);
	// Downsize the field
	int l_iFactor = 4;  
	X_DownsizeArray(l_dDSquareHeightField, l_iResolution, l_iFactor);
	// Create image
	GEDUtils::SimpleImage l_bmpHeightfield(l_iResolution / l_iFactor, l_iResolution / l_iFactor);
	// Fill image
	for (int x = 0; x < (l_iResolution / l_iFactor); x++)
	{
		for (int y = 0; y < (l_iResolution / l_iFactor); y++)
		{
			l_bmpHeightfield.setPixel(x, y, l_dDSquareHeightField[IDX(x, y, (l_iResolution / l_iFactor))]);
		}
	}
	// Save to file
	l_bmpHeightfield.save(argv[4]);
	// Done
    return 0;
}