#include "PerlinNoise.h"

std::vector<int> PerlinNoise::m_xPositif;
std::vector<int> PerlinNoise::m_xNegatif;
std::vector<int> PerlinNoise::m_yPositif;
std::vector<int> PerlinNoise::m_yNegatif;

bool PerlinNoise::initPerlinNoise(int seed)
{
	srand(4 * seed);
	for (int i = 0; i < 10000; i++)
	{
		PerlinNoise::m_xPositif.push_back(rand() % 8);
	}
	srand(4 * seed + 1);
	for (int i = 0; i < 10000; i++)
	{
		PerlinNoise::m_yPositif.push_back(rand() % 8);
	}
	PerlinNoise::m_xNegatif.push_back(PerlinNoise::m_xPositif[0]);
	srand(4 * seed + 2);
	for (int i = 1; i < 10000; i++)
	{
		PerlinNoise::m_xNegatif.push_back(rand() % 8);
	}
	PerlinNoise::m_yNegatif.push_back(PerlinNoise::m_yPositif[0]);
	srand(4 * seed + 3);
	for (int i = 1; i < 10000; i++)
	{
		PerlinNoise::m_yNegatif.push_back(rand() % 8);
	}
	return true;
}

float PerlinNoise::getPerlinNoise(float x, float y, float res)
{
	float tempX, tempY;
	int x0, y0, gi0, gi1, gi2, gi3;
	float unit = 1.0f / sqrt(2);
	float tmp, s, t, u, v, Cx, Cy, Li1, Li2;
	float gradient2[][2] = { { unit, unit }, { -unit, unit }, { unit, -unit }, { -unit, -unit }, { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };


	//Adapter pour la r�solution

	x /= res;
	y /= res;


	//On r�cup�re les positions de la grille associ�e � (x,y)

	x0 = floor(x);
	y0 = floor(y);


	//Pour r�cup�rer les vecteurs

	gi0 = (m_xPositif[abs(x0)] * (x0 >= 0) + m_xNegatif[abs(x0)] * (x0 < 0) + m_yPositif[abs(y0)] * (y0 >= 0) + m_yNegatif[abs(y0)] * (y0 < 0)) % 8;
	gi1 = (m_xPositif[abs(x0 + 1)] * (x0 + 1 >= 0) + m_xNegatif[abs(x0 + 1)] * (x0 + 1 < 0) + m_yPositif[abs(y0)] * (y0 >= 0) + m_yNegatif[abs(y0)] * (y0 < 0)) % 8;
	gi2 = (m_xPositif[abs(x0)] * (x0 >= 0) + m_xNegatif[abs(x0)] * (x0 < 0) + m_yPositif[abs(y0 + 1)] * (y0 + 1 >= 0) + m_yNegatif[abs(y0 + 1)] * (y0 + 1 < 0)) % 8;
	gi3 = (m_xPositif[abs(x0 + 1)] * (x0 + 1 >= 0) + m_xNegatif[abs(x0 + 1)] * (x0 + 1 < 0) + m_yPositif[abs(y0 + 1)] * (y0 + 1 >= 0) + m_yNegatif[abs(y0 + 1)] * (y0 + 1 < 0)) % 8;


	//on r�cup�re les vecteurs et on pond�re

	tempX = x - x0;
	tempY = y - y0;
	s = gradient2[gi0][0] * tempX + gradient2[gi0][1] * tempY;

	tempX = x - (x0 + 1);
	tempY = y - y0;
	t = gradient2[gi1][0] * tempX + gradient2[gi1][1] * tempY;

	tempX = x - x0;
	tempY = y - (y0 + 1);
	u = gradient2[gi2][0] * tempX + gradient2[gi2][1] * tempY;

	tempX = x - (x0 + 1);
	tempY = y - (y0 + 1);
	v = gradient2[gi3][0] * tempX + gradient2[gi3][1] * tempY;

	//Lissage

	tmp = x - x0;
	Cx = 3 * tmp * tmp - 2 * tmp * tmp * tmp;

	Li1 = s + Cx*(t - s);
	Li2 = u + Cx*(v - u);

	tmp = y - y0;
	Cy = 3 * tmp * tmp - 2 * tmp * tmp * tmp;

	return Li1 + Cy*(Li2 - Li1);
}

PerlinNoise::PerlinNoise()
{
}

PerlinNoise::~PerlinNoise()
{
}
