#pragma once

#include <iostream>
#include <string.h>
#include <sstream>
#include <cstdlib>
#include <random>
#include <vector>
#include <time.h>
/*
GED Utils
*/
#include "SimpleImage.h"
#include "TextureGenerator.h"
/*
Sonstiges
*/
#include "DiamondSquare.h"
#include "NormalsTexturesGen.h"

/*
Arrayzugriff (Breite w) an Position X/Y
*/
#define IDX(x, y, w) ((x) + (y) * (w))

using namespace std;

int main(int argc, char* argv[])
{
	int l_iResolution;
	/*
	Überprüfung ob Argumentzahl stimmt sowie ob Auflösung ein Integer ist
	*/
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
	/*
	Heightfield
	*/
	float *l_dHeightField = new float[l_iResolution * l_iResolution];
	/*
	Initialisiere Generator
	*/
	normal_distribution<float> l_Random(0.5F, 0.5F);
	default_random_engine l_Generator;
	srand(time(nullptr));
	/*
	Ausgabe
	*/
	cout << "Computing random heightfield" << endl;
	/*
	Fülle Heightfield
	*/
	for (int i = 0; i < l_iResolution * l_iResolution; i++) 
	{
		/*
		Bestimme zufällige Zahl (bis gültig) und speichere im Array
		*/
		float l_dHeight;
		while ((l_dHeight = l_Random(l_Generator)) < 0.0F || l_dHeight > 1.0F) {}
		l_dHeightField[i] = l_dHeight;
	}	
	/*
	Erstelle Rechner mit vorgegebener Auflösung
	*/
	DiamondSquare l_dSquare (l_iResolution);
	/*
	Ausgabe
	*/
	cout << "Computing DS heightfield" << endl;
	/*
	Berechne HeightField
	*/
	l_dSquare.Compute(10);
	/*
	Speichere..
	*/
	float *l_dHeightField_DS = l_dSquare.GetHeightField();
	/*
	Leeres Bild
	*/
	GEDUtils::SimpleImage l_bmpHeightfield(l_iResolution, l_iResolution);
	vector<float> l_vecHeightfield = {};
	/*
	Ausgabe
	*/
	cout << "Generating height texture" << endl;
	/*
	Fülle Bild
	*/
	for(int x = 0; x < l_iResolution; x++)
	{
		for (int y = 0; y < l_iResolution; y++)
		{
			l_bmpHeightfield.setPixel(x, y, l_dHeightField_DS[IDX(x, y, l_iResolution)]);
			/*
			Das Vector-Array muss "rückwärts" befüllt werden
			*/
			l_vecHeightfield.push_back(l_dHeightField_DS[IDX(y, x, l_iResolution)]);
		}
	}
	/*
	Speichere Bild
	*/
	l_bmpHeightfield.save(argv[4]);
	/*
	TextureGeneratoren erstellen mit entsprechenden Pfaden
	*/
	GEDUtils::TextureGenerator l_TextureGen (L"../../../../external/textures/gras15.jpg",
											L"../../../../external/textures/mud02.jpg",
											L"../../../../external/textures/pebble03.jpg",
											L"../../../../external/textures/rock7.jpg");
	NormalsTexturesGen l_MyGen ("../../../../external/textures/gras15.jpg",
								"../../../../external/textures/mud02.jpg",
								"../../../../external/textures/pebble03.jpg",
								"../../../../external/textures/rock7.jpg");
	/*
	Wandle Argumente in WStrings um
	*/
	wstringstream wss;
	wstring arg6, arg8;
	wss << "GED" << argv[6] << " GED" << argv[8];
	wss >> arg6 >> arg8;
	/*
	Ausgabe
	*/
	cout << "Generating color and normal textures" << endl;
	/*
	Eigene Implementierung ausführen
	*/
	l_MyGen.GenerateAndStore(l_dHeightField_DS, l_iResolution, argv[6], argv[8]);
	/*
	GED Implementierung ausführen
	*/
	l_TextureGen.generateAndStoreImages(l_vecHeightfield, l_iResolution - 1, arg6, arg8);
	/*
	Aufräumen
	*/
	delete[] l_dHeightField;
	/*
	Ausgabe
	*/
	cout << "Cleanup and textures done" << endl;
	/*
	Ende
	*/
	system("pause");
    return 0;
}