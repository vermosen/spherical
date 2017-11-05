#pragma once
#ifndef GRAPHICS_SPRITES_HPP
#define GRAPHICS_SPRITES_HPP

namespace spherical {
namespace graphics {
	class sprite
	{
	public:
		sprite();
		virtual ~sprite();

		virtual draw = 0;
	};
}}

#endif

