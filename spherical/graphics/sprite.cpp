#include <graphics/sprite.hpp>

#include <Windows.h>
#include <GL/gl.h>

namespace spherical {
namespace graphics {

	sprite::sprite() {}
	sprite::~sprite() {}
	void sprite::draw() 
	{
		glEnd();
		draw_impl();
	}
}}