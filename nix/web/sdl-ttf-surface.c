/*
 * Surface creation and filling for SDL_ttf under Emscripten.
 *
 * Emscripten's SDL mallocs a surface's pixels without clearing them,
 * and SDL_FillRect only paints the canvas behind the surface. SDL_ttf
 * fills a new surface and then ORs the glyphs into its pixels, so text
 * would pick up whatever the memory held before. These work on the
 * pixels, like SDL does on the desktop.
 */

#include <string.h>

#include <SDL.h>

SDL_Surface* sdl_ttf_create_surface (Uint32 flags, int width, int height, int depth,
                                     Uint32 rmask, Uint32 gmask, Uint32 bmask, Uint32 amask)
{
    SDL_Surface* surf = SDL_CreateRGBSurface (flags, width, height, depth,
                                              rmask, gmask, bmask, amask);
    if (surf && surf->pixels)
        memset (surf->pixels, 0, (size_t) surf->h * surf->pitch);
    return surf;
}

int sdl_ttf_fill_rect (SDL_Surface* surf, SDL_Rect* rect, Uint32 color)
{
    SDL_Rect all = { 0, 0, surf->w, surf->h };
    if (!rect)
        rect = &all;
    if (!surf->pixels)
        return -1;

    /* Emscripten's surfaces are four bytes per pixel. */
    for (int y = rect->y; y < rect->y + rect->h && y < surf->h; ++y) {
        Uint32* row = (Uint32*) ((Uint8*) surf->pixels + y * surf->pitch);
        for (int x = rect->x; x < rect->x + rect->w && x < surf->w; ++x)
            row[x] = color;
    }
    return 0;
}
