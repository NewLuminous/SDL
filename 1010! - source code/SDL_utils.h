/*!
    \file       SDL_utils.h
    \brief      Include file for creating window and rendering textures.
    \pre        Add linker options: -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf.
                Then search directories: Compiler for include\SDL2\ folder and Linker for lib\ folder.
*/
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include "board.h"
#include "menu.h"

using namespace std;

/*!
    \class  SDLUtils
    \brief  A window displaying textures
*/
class SDLUtils {
    private:
        const int COLOR_KEY_R = 0;
        const int COLOR_KEY_G = 0;
        const int COLOR_KEY_B = 0;

        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;
        SDL_Texture* texture = nullptr;

        void logError(const string &msg, const string &error, bool fatal) {
            cout << msg << " Error: " << error << endl;
            if (fatal) {SDL_Quit(); exit(1);}
        }

        void loadTexture(const string &path) {
            if (texture != nullptr) {
                SDL_DestroyTexture(texture);
                texture = nullptr;
            }
            SDL_Surface* surface = IMG_Load(path.c_str());
            if (surface == nullptr) logError("IMG_Load", IMG_GetError(), true);
            SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
            texture = SDL_CreateTextureFromSurface(renderer, surface);
            if (texture == nullptr) logError("CreateTextureFromSurface", SDL_GetError(), true);
            SDL_FreeSurface(surface);
        }

        pair<int, int> loadFont(const string &path, const string &text, const int &ptsize, const Color &color) {
            TTF_Font* font = TTF_OpenFont(path.c_str(), ptsize);
            if (font == nullptr) logError("OpenFont", TTF_GetError(), true);
            if (texture != nullptr) {
                SDL_DestroyTexture(texture);
                texture = nullptr;
            }
            SDL_Color text_color = {color.getR(), color.getG(), color.getB()};
            SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), text_color);
            if (surface == nullptr) logError("TTF_RenderText_Solid", TTF_GetError(), true);
            SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
            texture = SDL_CreateTextureFromSurface(renderer, surface);
            if (texture == nullptr) logError("CreateTextureFromSurface", SDL_GetError(), true);
            pair<int, int> pii = {surface->w, surface->h};
            SDL_FreeSurface(surface);
            TTF_CloseFont(font);
            return pii;
        }
    public:
        /*!
            \brief  Constructor creating window.
            \sa     SDL_CreateWindow()
            \sa     SDL_CreateRenderer()
        */
        SDLUtils(const int &screenWidth, const int &screenHeight, const string &windowTitle) {
            if (SDL_Init(SDL_INIT_EVERYTHING)) logError("SDL_Init", SDL_GetError(), true);
            int flags = IMG_INIT_PNG | IMG_INIT_JPG;
            if (IMG_Init(flags) != flags) logError("IMG_Init", IMG_GetError(), true);
            if (TTF_Init() == -1) logError("TTF_Init", TTF_GetError(), true);
            window = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
            if (window == nullptr) logError("CreateWindow", SDL_GetError(), true);
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (renderer == nullptr) logError("CreateRenderer", SDL_GetError(), true);
            SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
            SDL_SetRenderDrawColor(renderer, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B, 0xFF);
        }

        /*!
            \brief  Destructor.
        */
        ~SDLUtils() {
            if (texture != nullptr) SDL_DestroyTexture(texture);
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            texture = nullptr;
            renderer = nullptr;
            window = nullptr;
            TTF_Quit();
            IMG_Quit();
            SDL_Quit();
        }

        /*!
            \brief  Render image.
            \param  path The path pointing to the image.
            \param  x The x coordinate of the upper left corner of the image.
            \param  y The y coordinate of the upper left corner of the image.
            \param  w The width of the image being rendered.
            \param  h The height of the image being rendered.
            \sa     SDL_RenderCopy()
        */
        void draw(const string &path, const int &x, const int &y, const int &w, const int &h) {
            loadTexture(path);
            SDL_Rect rect = {x, y, w, h};
            SDL_RenderCopy(renderer, texture, NULL, &rect);
        }

        /*!
            \brief      Render/Delete Board object.
            \details    This deletes the Board object by rendering a rectangle which covers that object.
            \sa         SDL_RenderFillRect()
            \sa         SDL_RenderCopy()
        */
        void draw(const Board* board) {
            if (board->isDel()) {
                SDL_Rect rect = {board->getX(), board->getY(), board->getSizeX(), board->getSizeY()};
                SDL_RenderFillRect(renderer, &rect);
                return;
            }
            loadTexture(board->getUnitSquareImg());
            for (int i = 0; i < board->getHeight(); ++i)
                for (int j = 0; j < board->getWidth(); ++j) {
                    Color color = board->getUnitSquareColor(i, j);
                    SDL_SetTextureColorMod(texture, color.getR(), color.getG(), color.getB());
                    SDL_Rect rect = {board->getX() + board->getUnitSquareSize() * j, board->getY() + board->getUnitSquareSize() * i, board->getUnitSquareSize(), board->getUnitSquareSize()};
                    SDL_RenderCopy(renderer, texture, NULL, &rect);
                }
        }

        /*!
            \brief      Render/Delete Shape object.
            \details    This deletes the Shape object by making it transparent.
            \sa         SDL_RenderCopy()
            \sa         SDL_SetTextureColorMod()
            \sa         SDL_SetColorKey()
        */
        void draw(const Shape* shape) {
            loadTexture(shape->getUnitSquareImg());
            if (!shape->isDel()) SDL_SetTextureColorMod(texture, shape->getColor().getR(), shape->getColor().getG(), shape->getColor().getB());
                else SDL_SetTextureColorMod(texture, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B);
            for (int i = 0; i < shape->getHeight(); ++i)
                for (int j = 0; j < shape->getWidth(); ++j)
                    if (shape->getBit(i, j)){
                        SDL_Rect rect = {shape->getX() + shape->getUnitSquareSize() * j, shape->getY() + shape->getUnitSquareSize() * i,
                                         shape->getUnitSquareSize(), shape->getUnitSquareSize()};
                        SDL_RenderCopy(renderer, texture, NULL, &rect);
                    }
        }

        /*!
            \brief      Render Score object.
            \param      score The score
            \param      num_digits Number of digits being presented.
            \sa         SDL_RenderCopy()
        */
        void draw(const Score* score, const int &num_digits) {
            vector<int> vec_d = score->getDigits(num_digits);
            for (int i = 0; i < num_digits; ++i) {
                loadTexture(score->getDigitImg(vec_d[num_digits - 1 - i]));
                SDL_Rect rect = {score->getX() + score->getDSizeX() * i, score->getY(), score->getDSizeX(), score->getDSizeY()};
                SDL_RenderFillRect(renderer, &rect);
                SDL_RenderCopy(renderer, texture, NULL, &rect);
            }
        }

        /*!
            \brief      Render/Delete Button object.
            \details    This deletes the Button object by rendering a rectangle which covers that object.
            \sa         SDL_RenderFillRect()
            \sa         SDL_RenderCopy()
        */
        void draw(Button* button) {
            loadTexture(button->getIcon());
            int icon_size = button->isDel() ? button->getTriggeredIconSize() : button->getIconSize();
            SDL_Rect rect = {button->getX(), button->getY(), icon_size, icon_size};
            if (!button->isDel()) SDL_RenderCopy(renderer, texture, NULL, &rect); else SDL_RenderFillRect(renderer, &rect);

            pair<int, int> pii = loadFont(button->getFont(), button->getName(), button->getFontSize(), button->getFontColor());
            rect = {button->getX() + button->getNormalIconSize() * 2, button->getY(),
                    icon_size * pii.first / pii.second + (icon_size - button->getNormalIconSize()) * 2, icon_size};
            if (!button->isDel()) SDL_RenderCopy(renderer, texture, NULL, &rect); else SDL_RenderFillRect(renderer, &rect);
        }

        /*!
            \brief      Render/Delete Menu object.
            \details    This deletes the Menu object by rendering a rectangle which covers that object.
            \sa         SDL_RenderFillRect()
            \sa         SDL_RenderCopy()
        */
        void draw(Menu* menu) {
            pair<int, int> pii = loadFont(menu->getFont(), menu->getTitle(), menu->getFontSize(), menu->getFontColor());
            SDL_Rect rect = {menu->getX(), menu->getY(), menu->getWidth(), menu->getWidth() * pii.second / pii.first};
            if (!menu->isDel()) SDL_RenderCopy(renderer, texture, NULL, &rect); else SDL_RenderFillRect(renderer, &rect);
            for (int i = 0; i < menu->numButton(); ++i)
                if (!menu->isDel()) draw(menu->getButton(i)->recover()); else draw(menu->getButton(i)->del());
        }

        /*!
            \brief      Update the window.
            \sa         SDL_RenderPresent()
        */
        void present() {SDL_RenderPresent(renderer);}
};
