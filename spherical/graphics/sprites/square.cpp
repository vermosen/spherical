#include <graphics/sprites/square.hpp>

#include <Windows.h>
#include <GL/gl.h>

namespace spherical {
namespace graphics {

	square::square() {}
	square::~square() {}
	void square::draw_impl() 
	{
		glBegin(GL_QUADS);
		glColor3f(1.0, 1.0, 0.0);		glVertex3i(50 , 200, 0);
		glColor3f(0.0, 1.0, 0.0);		glVertex3i(250, 200, 0);
		glColor3f(0.0, 0.0, 1.0);		glVertex3i(250, 350, 0);
		glColor3f(1.0, 1.0, 1.0);		glVertex3i(50 , 350, 0);
	}
}}