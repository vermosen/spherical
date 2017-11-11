#pragma once
#ifndef GRAPHICS_SPRITE_HPP
#define GRAPHICS_SPRITE_HPP

namespace spherical {
namespace graphics {

	class sprite
	{
	public:
		sprite();
		virtual ~sprite();
		void draw();
		virtual void draw_impl() = 0;
	};
}}

#endif