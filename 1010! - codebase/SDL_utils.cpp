/*!
    \file       SDL_utils.cpp
    \brief      Implementation file for creating window and rendering textures.
*/

#include "SDL_utils.h"

void SDLUtils::logError(const std::string &msg, const std::string &error, bool fatal) {
    std::cout << msg << " Error: " << error << std::endl;
    if (fatal) {SDL_Quit(); exit(1);}
}

SDLUtils::SDLUtils(const int &screenWidth, const int &screenHeight, const std::string &windowTitle) {
    if (SDL_Init(SDL_INIT_EVERYTHING)) logError("SDL_Init", SDL_GetError(), true);
    int flags = IMG_INIT_PNG | IMG_INIT_JPG;
    if (IMG_Init(flags) != flags) logError("IMG_Init", IMG_GetError(), true);
    if (TTF_Init() == -1) logError("TTF_Init", TTF_GetError(), true);
    mwindow = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
    if (mwindow == nullptr) logError("CreateWindow", SDL_GetError(), true);
    mrenderer = SDL_CreateRenderer(mwindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (mrenderer == nullptr) logError("CreateRenderer", SDL_GetError(), true);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_SetRenderDrawColor(mrenderer, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B, 0xFF);
}

SDLUtils::~SDLUtils() {
    SDL_DestroyRenderer(mrenderer);
    SDL_DestroyWindow(mwindow);
    mrenderer = nullptr;
    mwindow = nullptr;
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void SDLUtils::del(SDL_Rect rect) {SDL_RenderFillRect(mrenderer, &rect);}

void SDLUtils::render(ISurface* surface) {
    for (int i = 0; i < surface->getNum(); ++i) {
        del(*surface->getSize(i));
        SDL_SetColorKey(surface->get(i), SDL_TRUE, SDL_MapRGB(surface->get(i)->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
        SDL_Texture* texture = SDL_CreateTextureFromSurface(mrenderer, surface->get(i));
        if (texture == nullptr) logError("CreateTextureFromSurface", SDL_GetError(), true);
        SDL_SetTextureColorMod(texture, surface->getColor(i).r, surface->getColor(i).g, surface->getColor(i).b);
        SDL_RenderCopy(mrenderer, texture, NULL, surface->getSize(i));
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
    delete surface;
}

void SDLUtils::present() {SDL_RenderPresent(mrenderer);}
