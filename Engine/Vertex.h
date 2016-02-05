#pragma once

#include <GL\glew.h>

namespace Engine
{
	struct Position
	{
		Position() : x(0), y(0), z(0) { }
		Position(float X, float Y, float Z) : x(X), y(Y), z(Z) { }
		float x;
		float y;
		float z;
	};

	struct ColorRGBA
	{
		ColorRGBA() : r(255), g(255), b(255), a(255) { }
		ColorRGBA(GLubyte R, GLubyte G, GLubyte B, GLubyte A) : r(R), g(G), b(B), a(A) { }
		GLubyte r;
		GLubyte g;
		GLubyte b;
		GLubyte a;
	};

	struct UV
	{
		UV() : u(0), v(0) { }
		UV(float U, float V) : u(U), v(V) { }
		float u;
		float v;
	};

	struct Vertex
	{
		Position position;
		ColorRGBA color;
		UV uv;

		void setPosition(float x, float y, float z)
		{
			position.x = x;
			position.y = y;
			position.z = z;
		}

		void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a)
		{
			color.r = r;
			color.g = g;
			color.b = b;
			color.a = a;
		}

		void setUV(float u, float v)
		{
			uv.u = u;
			uv.v = v;
		}
	};
}