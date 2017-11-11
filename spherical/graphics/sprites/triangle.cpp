#include <graphics/sprites/triangle.hpp>

#include <Windows.h>
#include <GL/gl.h>

namespace spherical {
namespace graphics {

	triangle::triangle() {}
	triangle::~triangle() {}
	void triangle::draw_impl()
	{
		glBegin(GL_TRIANGLES);
		glColor3f(1.0, 0.0, 0.0);  glVertex3i(400, 350, 0);
		glColor3f(0.0, 1.0, 0.0);  glVertex3i(500, 200, 0);
		glColor3f(0.0, 0.0, 1.0);  glVertex3i(600, 350, 0);
	}
}}

