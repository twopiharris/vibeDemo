// Simple SDL2 example: move the square with arrow keys, ESC to quit
#include <SDL2/SDL.h>
#include <stdio.h>

#define WINDOW_W 800
#define WINDOW_H 600
#define SQUARE_SIZE 48

int main(int argc, char **argv) {
    (void)argc; (void)argv;
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *win = SDL_CreateWindow("VibeDemo - SDL2 Basic Game",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       WINDOW_W, WINDOW_H,
                                       SDL_WINDOW_SHOWN);
    if (!win) {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!ren) {
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    SDL_Rect player = { WINDOW_W/2 - SQUARE_SIZE/2, WINDOW_H/2 - SQUARE_SIZE/2, SQUARE_SIZE, SQUARE_SIZE };
    const int speed = 300; // pixels per second

    int running = 1;
    Uint64 now = SDL_GetPerformanceCounter();
    Uint64 last = 0;
    double delta = 0;

    while (running) {
        last = now;
        now = SDL_GetPerformanceCounter();
        delta = (double)((now - last) * 1000) / (double)SDL_GetPerformanceFrequency(); // ms
        double seconds = delta / 1000.0;

        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = 0;
            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_ESCAPE) running = 0;
            }
        }

        const Uint8 *ks = SDL_GetKeyboardState(NULL);
        int dx = 0, dy = 0;
        if (ks[SDL_SCANCODE_LEFT] || ks[SDL_SCANCODE_A]) dx = -1;
        if (ks[SDL_SCANCODE_RIGHT] || ks[SDL_SCANCODE_D]) dx = 1;
        if (ks[SDL_SCANCODE_UP] || ks[SDL_SCANCODE_W]) dy = -1;
        if (ks[SDL_SCANCODE_DOWN] || ks[SDL_SCANCODE_S]) dy = 1;

        player.x += (int)(dx * speed * seconds);
        player.y += (int)(dy * speed * seconds);

        // clamp to window
        if (player.x < 0) player.x = 0;
        if (player.y < 0) player.y = 0;
        if (player.x + player.w > WINDOW_W) player.x = WINDOW_W - player.w;
        if (player.y + player.h > WINDOW_H) player.y = WINDOW_H - player.h;

        // render
        SDL_SetRenderDrawColor(ren, 30, 30, 40, 255);
        SDL_RenderClear(ren);

        // draw player
        SDL_SetRenderDrawColor(ren, 220, 80, 60, 255);
        SDL_RenderFillRect(ren, &player);

        SDL_SetRenderDrawColor(ren, 200, 200, 200, 255);
        SDL_Rect border = {10, 10, WINDOW_W - 20, WINDOW_H - 20};
        SDL_RenderDrawRect(ren, &border);

        SDL_RenderPresent(ren);

        // small delay to avoid 100% CPU in case vsync is off
        SDL_Delay(1);
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
