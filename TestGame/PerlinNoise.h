#include <vector>

class PerlinNoise
{
public:
	static bool initPerlinNoise(int seed);
	static float getPerlinNoise(float x, float y, float res);

private:
	PerlinNoise();
	~PerlinNoise();

	static std::vector<int> m_xPositif;
	static std::vector<int> m_xNegatif;
	static std::vector<int> m_yPositif;
	static std::vector<int> m_yNegatif;
};

