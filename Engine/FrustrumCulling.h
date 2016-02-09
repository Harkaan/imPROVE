#ifndef FRUSTRUMCULLING_H
#define FRUSTRUMCULLING_H
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

namespace Engine
{
	class Chunk;

	class FrustrumCulling
	{
	public:

		FrustrumCulling(double angle, double rapport);
		~FrustrumCulling();
		void setFrustrumCulling(glm::vec3 position, glm::vec3 pointCible);
		bool pointInside(glm::vec3 point);

	private:

		glm::vec3 m_axeVertical;
		double m_angle;
		double m_rapport;

		glm::mat2x3 m_faces1;
		glm::mat2x3 m_faces2;
		glm::mat2x3 m_faces3;
		glm::mat2x3 m_faces4;
	};
}
#endif // FRUSTRUMCULLING_H
