#pragma once
#ifndef GRAPHICS_SPRITES_SQUARE_HPP
#define GRAPHICS_SPRITES_SQUARE_HPP

#include <graphics/sprite.hpp>

namespace spherical {
namespace graphics {

	class square : public sprite
	{
	public:
		square();
		virtual ~square();
		virtual void draw_impl() override;
	};
}}

#endif

