#pragma once
#ifndef GRAPHICS_SPRITES_TRIANGLE_HPP
#define GRAPHICS_SPRITES_TRIANGLE_HPP

#include <graphics/sprite.hpp>

namespace spherical {
namespace graphics {

	class triangle : public sprite
	{
	public:
		triangle();
		virtual ~triangle();
		virtual void draw_impl() override;
	};
}}

#endif

