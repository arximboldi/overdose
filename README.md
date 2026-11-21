# Overdose

Overdose is a small game in which the player has to virtually
experience (and suffer) the effects of drugs to reach their goal.

It was written in 2009 by Juan Pedro Bolívar Puente as a university
project, on top of a small 3D engine called *yage* that lives in the
same source tree.

Overdose is Free Software, distributed under the GNU General Public
License version 3 or later. See [COPYING](COPYING) for the terms under
which you may modify and share it.


## Building and installing

### With Nix

With [Nix](https://nixos.org) and flakes enabled, you can play the game
without installing anything else:

    nix run

Or build it and install it into your profile:

    nix build            # the result is linked at ./result
    nix profile add .

For development, `nix develop` opens a shell with the compiler, CMake
and every library the game needs; from there, follow the steps in
[Building with CMake](#building-with-cmake).

### Dependencies

Without Nix, you need:

1. A C++17 compiler.
2. [CMake](https://cmake.org) 3.20 or later, and pkg-config.
3. These libraries:
   - [libxml2](https://gitlab.gnome.org/GNOME/libxml2)
   - [Boost](https://www.boost.org/) (headers only)
   - [libsigc++ 2](https://libsigcplusplus.github.io/libsigcplusplus/)
   - [SDL 1.2](https://www.libsdl.org), or its modern replacement
     [sdl12-compat](https://github.com/libsdl-org/sdl12-compat)
   - SDL_image, SDL_ttf and SDL_mixer for SDL 1.2
   - OpenGL
4. Optionally, help2man to generate the man page.

On Debian or Ubuntu they can be installed by running, as root:

    apt-get install build-essential cmake pkg-config help2man \
        libxml2-dev libboost-dev \
        libsigc++-2.0-dev libsdl1.2-dev libsdl-image1.2-dev \
        libsdl-ttf2.0-dev libsdl-mixer1.2-dev libgl-dev

### Building with CMake

From the source directory, as a normal user, run:

    cmake -S . -B build
    cmake --build build

CMake checks that all dependencies are present and stops with an error
message if one is missing. The game ends up at `build/src/overdose` and
can be started right from there: by default it loads its data from the
`data/` directory of the source tree.

### Installing

To install the game system-wide, tell CMake where the game will find
its data once installed, for example:

    cmake -S . -B build -DCMAKE_INSTALL_PREFIX=/usr/local \
        -DOVERDOSE_DATA_DIR=/usr/local/share/overdose
    cmake --build build
    cmake --install build

The last command normally has to be run as root.

### In the browser

The game also builds to WebAssembly with
[Emscripten](https://emscripten.org), as a static website that can be
served by any web server:

    nix build .#web

The site ends up in `./result`: `index.html`, the compiled game, and
`overdose.data` with all the game data (about 75 MB). To try it
locally, serve that directory, for example with:

    python3 -m http.server -d result

and open <http://localhost:8000>. Command line options can be passed in
the URL, for example `?args=-l%205` to start with half the maximum
amount of drugs in the blood.

After rebuilding, reload the page with `Ctrl+Shift+R`: everything Nix
builds is dated 1970, so this server tells the browser that nothing
has changed, and it would go on running the version it has cached.

In the browser, clicking the game grabs the mouse, so that the camera
can turn freely, and `Escape` lets go of it.

The browser build relies on Emscripten's own implementation of SDL 1.2
and on [gl4es](https://github.com/ptitSeb/gl4es) to run the game's
OpenGL code on WebGL. Text is drawn with the same SDL_ttf and FreeType
as on the desktop, built for the web. For working on it, `nix develop .#web` opens a
shell with Emscripten and these dependencies, where:

    emcmake cmake -S . -B build-web -G Ninja $cmakeFlags
    cmake --build build-web

builds the site into `build-web/src`.


## Playing

### Running the game

Once installed, start the game with:

    overdose

Options such as the screen resolution can be given on the command
line. For the full list, run:

    overdose --help

or read the manual page:

    man overdose

Most options you pass are saved in the configuration file
`~/.overdose/config.xml`, so you don't have to repeat them in later
sessions.

### The story

In Overdose you control a banking yuppie who, ruined by the financial
crisis, troubled by his own greed and having wasted his life between
offices and screens, decides to try everything on the last day of his
life.

### Goal

Your mission is to help him die of an overdose, taking every kind of
narcotic he can buy on the street.

The level of drugs in his blood is shown in the top-left corner of the
screen as three coloured bars, which also represent the character's
state of mind:

1. **Psychedelia:** the green bar.
2. **Ecstasy:** the blue bar.
3. **Euphoria:** the red bar.

Each bar goes up (or down) depending on what you take. You win when all
three reach the top. Hurry up: the bars also go down slowly as time
passes.

### Getting and taking drugs

To get drugs, walk up to a dealer on the street. The dealer will stare
at you and a message with their offer will appear on screen.

| Key           | Action                                |
| ------------- | ------------------------------------- |
| `b`           | Buy the drug on offer                 |
| `Space`       | Take the selected drug                |
| `n` / `m`     | Select the previous / next drug       |

Drugs you buy go into an inventory in the top-right corner, which holds
up to five of them.

Be careful: while you carry drugs, police officers will come after you
and take them away. Taking drugs also has temporary effects on how the
character behaves. An indicator at the bottom shows how long the
effects of each kind of substance will last.

### Moving around

| Input              | Action                                         |
| ------------------ | ---------------------------------------------- |
| Arrow keys         | Walk and turn                                  |
| Mouse              | Rotate the camera                              |
| Mouse wheel        | Move the camera closer or further away         |
| Middle button      | Re-centre the camera                           |
| `F1`               | Camera following the player (the default)      |
| `F2`               | Free-flying camera, steered with the mouse and `w`, `a`, `s`, `d` |
| `F3`, `F4`         | Fixed cameras                                  |
| `Enter`            | Go on to the next level once you have won      |
| `f`                | Toggle fullscreen                              |
| `Escape`           | Leave the current level (not in the browser)   |

### Rendering modes

The remaining function keys change how the game is drawn, and were
mostly useful while developing it:

| Key    | Effect                         |
| ------ | ------------------------------ |
| `F8`   | Smooth shading                 |
| `F9`   | Flat shading                   |
| `F10`  | Filled polygons                |
| `F11`  | Points only                    |
| `F12`  | Wireframe                      |
| `F5`–`F7` | Replace a test model with nothing, a sphere or a cylinder |
