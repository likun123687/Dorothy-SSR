/* Copyright (c) 2017 Jin Li, http://www.luvfight.me

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#include "Const/Header.h"
#include "Support/Common.h"

NS_DOROTHY_BEGIN

Color3::Color3():
r(255),
g(255),
b(255)
{ }

Color3::Color3(Uint32 rgb):
r((rgb & 0x00FF0000) >> 16),
g((rgb & 0x0000FF00) >> 8),
b(rgb & 0x000000FF)
{ }

Color3::Color3(Uint8 r, Uint8 g, Uint8 b):
r(r),
g(g),
b(b)
{ }

Uint32 Color3::toRGB() const
{
	return r << 16 | g << 8 | b;
}

Color::Color():
r(255),
g(255),
b(255),
a(255)
{ }

Color::Color(Color3 color):
r(color.r),
g(color.g),
b(color.b)
{ }

Color::Color(Uint32 argb):
a(argb >> 24),
r((argb & 0x00FF0000) >> 16),
g((argb & 0x0000FF00) >> 8),
b(argb & 0x000000FF)
{ }

Color::Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a):
r(r),
g(g),
b(b),
a(a)
{ }

Uint32 Color::toABGR() const
{
	return *r_cast<Uint32*>(c_cast<Color*>(this));
}

Color3 Color::toColor3() const
{
	return Color3(r, g, b);
}

void Color::setOpacity(float var)
{
	a = s_cast<Uint8>(Clamp(var, 0.0f, 1.0f) * 255.0f);
}

float Color::getOpacity() const
{
	return a / 255.0f;
}

Color& Color::operator=(const Color3& color)
{
	r = color.r;
	g = color.g;
	b = color.b;
	return *this;
}

Color& Color::operator=(const Color& color)
{
	r = color.r;
	g = color.g;
	b = color.b;
	a = color.a;
	return *this;
}

BlendFunc::BlendFunc(Uint32 src, Uint32 dst):src(src), dst(dst)
{ }

const BlendFunc BlendFunc::Normal(BlendFunc::SrcAlpha, BlendFunc::InvSrcAlpha);

Uint64 BlendFunc::toValue()
{
	return BGFX_STATE_BLEND_FUNC(src, dst);
}

NS_DOROTHY_END
