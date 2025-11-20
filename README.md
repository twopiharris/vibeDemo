# VibeDemo

Basic SDL2 demo that opens a window and moves a square with the arrow keys.

Build & run (Ubuntu / Debian):

1. Install dependencies:

```bash
sudo apt update
sudo apt install -y build-essential libsdl2-dev pkg-config
```

2. Build:

```bash
cd /workspaces/VibeDemo
make
```

3. Run:

```bash
./bin/game
```

Notes:
- If you're running inside a container, ensure the container has access to your display (X11/Wayland) or use X forwarding.
- The demo is in `src/main.c`. It uses `sdl2-config` for flags; if your system doesn't have it, install the `libsdl2-dev` package.

Next ideas:
- Add sprites and textures (SDL_image)
- Add sound (SDL_mixer)
- Switch to CMake for multi-platform builds
