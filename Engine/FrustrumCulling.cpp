#include "FrustrumCulling.h"
#include "Chunk.h"

using namespace glm;
using namespace Engine;

FrustrumCulling::FrustrumCulling(double angle, double rapport) : m_axeVertical(vec3(0,0,1)), m_angle(angle), m_rapport(rapport)
{

}

FrustrumCulling::~FrustrumCulling()
{

}

void FrustrumCulling::setFrustrumCulling(vec3 position, vec3 pointCible)
{
    vec3 direction = pointCible - position;
    float hauteur = 2*tan(radians(m_angle * 0.5f))*length(direction);
    float largeur = hauteur * m_rapport;
    vec3 perpendiculaire = cross(m_axeVertical, direction);
    vec3 haut = m_axeVertical;
    if (direction.x != 0)
    {
        float c = (direction.y * perpendiculaire.x - perpendiculaire.y * direction.x)/(direction.x * perpendiculaire.y - direction.y * perpendiculaire.x);
        haut = vec3(-(c * direction.y + direction.y)/direction.x, 1, c);
    }
    else if (direction.y != 0)
    {
        float a = (direction.y * perpendiculaire.y - perpendiculaire.y * direction.y)/(direction.y * perpendiculaire.x - direction.x * perpendiculaire.y);
        haut = vec3(a, 1, -(a * direction.x + direction.y)/direction.y);
    }
    if (haut.y < 0)
        haut = -haut;
    haut = normalize(haut);
    vec3 droite = -cross(haut, direction);
    droite = normalize(droite);

    m_faces1[0] = position;
    m_faces1[1] = cross(direction - haut*(hauteur/2) + droite*(largeur/2), direction + haut*(hauteur/2) + droite*(largeur/2));

    m_faces2[0] = position;
    m_faces2[1] = cross(direction + haut*(hauteur/2) + droite*(largeur/2), direction + haut*(hauteur/2) - droite*(largeur/2));

    m_faces3[0] = position;
    m_faces3[1] = cross(direction + haut*(hauteur/2) - droite*(largeur/2), direction - haut*(hauteur/2) - droite*(largeur/2));

    m_faces4[0] = position;
    m_faces4[1] = cross(direction - haut*(hauteur/2) - droite*(largeur/2), direction - haut*(hauteur/2) + droite*(largeur/2));

    /*std::cout<<m_faces1[1][0]<<","<<m_faces1[1][1]<<","<<m_faces1[1][2]<<std::endl;
    std::cout<<m_faces2[1][0]<<","<<m_faces2[1][1]<<","<<m_faces2[1][2]<<std::endl;
    std::cout<<m_faces3[1][0]<<","<<m_faces3[1][1]<<","<<m_faces3[1][2]<<std::endl;
    std::cout<<m_faces4[1][0]<<","<<m_faces4[1][1]<<","<<m_faces4[1][2]<<std::endl;*/
}

bool FrustrumCulling::pointInside(vec3 point)
{
    /*std::cout<<(m_faces1[1][0] * point[0] + m_faces1[1][1] * point[1] + m_faces1[1][2] * point[2] - dot(m_faces1[1], m_faces1[0]))<<std::endl;
    std::cout<<(m_faces2[1][0] * point[0] + m_faces2[1][1] * point[1] + m_faces2[1][2] * point[2] - dot(m_faces2[1], m_faces2[0]))<<std::endl;
    std::cout<<(m_faces3[1][0] * point[0] + m_faces3[1][1] * point[1] + m_faces3[1][2] * point[2] - dot(m_faces3[1], m_faces3[0]))<<std::endl;
    std::cout<<(m_faces4[1][0] * point[0] + m_faces4[1][1] * point[1] + m_faces4[1][2] * point[2] - dot(m_faces4[1], m_faces4[0]))<<std::endl;
    std::cout<<((m_faces1[1][0] * point[0] + m_faces1[1][1] * point[1] + m_faces1[1][2] * point[2] - dot(m_faces1[1], m_faces1[0]) <= 0)
                &(m_faces2[1][0] * point[0] + m_faces2[1][1] * point[1] + m_faces2[1][2] * point[2] - dot(m_faces2[1], m_faces2[0]) <= 0)
                &(m_faces3[1][0] * point[0] + m_faces3[1][1] * point[1] + m_faces3[1][2] * point[2] - dot(m_faces3[1], m_faces3[0]) <= 0)
                &(m_faces4[1][0] * point[0] + m_faces4[1][1] * point[1] + m_faces4[1][2] * point[2] - dot(m_faces4[1], m_faces4[0]) <= 0))<<std::endl;*/
    //return true;
    return ((m_faces1[1][0] * point[0] + m_faces1[1][1] * point[1] + m_faces1[1][2] * point[2] - dot(m_faces1[1], m_faces1[0]) <= 0)
           &(m_faces2[1][0] * point[0] + m_faces2[1][1] * point[1] + m_faces2[1][2] * point[2] - dot(m_faces2[1], m_faces2[0]) <= 0)
           &(m_faces3[1][0] * point[0] + m_faces3[1][1] * point[1] + m_faces3[1][2] * point[2] - dot(m_faces3[1], m_faces3[0]) <= 0)
           &(m_faces4[1][0] * point[0] + m_faces4[1][1] * point[1] + m_faces4[1][2] * point[2] - dot(m_faces4[1], m_faces4[0]) <= 0));
}
