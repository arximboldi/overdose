/* An SDL_RWops reading a file with stdio, for SDL_ttf under Emscripten. */

#include <stdio.h>
#include <stdlib.h>

#include <SDL.h>

static FILE* file_of (SDL_RWops* rw)
{
    return (FILE*) rw->hidden.unknown.data1;
}

static long rw_seek (SDL_RWops* rw, long offset, int whence)
{
    if (fseek (file_of (rw), offset, whence) != 0)
        return -1;
    return ftell (file_of (rw));
}

static size_t rw_read (SDL_RWops* rw, void* ptr, size_t size, size_t maxnum)
{
    return fread (ptr, size, maxnum, file_of (rw));
}

static size_t rw_write (SDL_RWops* rw, const void* ptr, size_t size, size_t num)
{
    return 0;
}

static int rw_close (SDL_RWops* rw)
{
    int result = fclose (file_of (rw));
    free (rw);
    return result == 0 ? 0 : -1;
}

SDL_RWops* sdl_ttf_rw_from_file (const char* path, const char* mode)
{
    FILE* file = fopen (path, mode);
    if (!file) {
        SDL_SetError ("Could not open %s", path);
        return NULL;
    }

    SDL_RWops* rw = calloc (1, sizeof (SDL_RWops));
    if (!rw) {
        fclose (file);
        SDL_SetError ("Out of memory");
        return NULL;
    }
    rw->seek = rw_seek;
    rw->read = rw_read;
    rw->write = rw_write;
    rw->close = rw_close;
    rw->hidden.unknown.data1 = file;
    return rw;
}
