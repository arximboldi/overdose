/**
 *  @file        sdl_emscripten.cpp
 *
 *  Adapts Emscripten's SDL_ttf to what the engine expects.
 */

/*
 *  Copyright (C) 2009 Juan Pedro Bolívar Puente
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

/*
 * Emscripten draws text with the browser's canvas, which always
 * antialiases and does not expose font styles, so it only implements
 * the Solid renderer. Its text surfaces also only fill in their pixels
 * when locked, unlike the images loaded by its IMG_Load, which come
 * with their pixels but without a canvas. Give the engine text surfaces
 * that behave like images, whichever renderer it asks for.
 */

#include <SDL_ttf.h>

namespace
{

SDL_Surface* render_text (TTF_Font* font, const char* text, SDL_Color fg)
{
    /* Emscripten treats the text as UTF-8 in every TTF_Render* call. */
    SDL_Surface* surf = TTF_RenderText_Solid (font, text, fg);
    /* Fills in pixels. Unlocking would copy them back to the canvas,
       which Emscripten's SDL does not allow while OpenGL is in use. */
    if (surf)
	SDL_LockSurface (surf);
    return surf;
}

} /* anonymous namespace */

extern "C" {

SDL_Surface* TTF_RenderUTF8_Solid (TTF_Font* font, const char* text,
				   SDL_Color fg)
{
    return render_text (font, text, fg);
}

SDL_Surface* TTF_RenderUTF8_Shaded (TTF_Font* font, const char* text,
				    SDL_Color fg, SDL_Color)
{
    return render_text (font, text, fg);
}

SDL_Surface* TTF_RenderUTF8_Blended (TTF_Font* font, const char* text,
				     SDL_Color fg)
{
    return render_text (font, text, fg);
}

int TTF_GetFontStyle (const TTF_Font*)
{
    return TTF_STYLE_NORMAL;
}

void TTF_SetFontStyle (TTF_Font*, int)
{
}

int TTF_FontFaceIsFixedWidth (const TTF_Font*)
{
    return 0;
}

} /* extern "C" */
