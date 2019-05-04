/*!
    \file       SDL_utils.h
    \brief      Include file for creating window and rendering textures.
    \pre        Add linker options: -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer.
                Then search directories: Compiler for include\SDL2\ folder and Linker for lib\ folder.
*/

#ifndef SDL_UTILS_H
#define SDL_UTILS_H

#include "isurface.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <cstdlib>

/*!
    \class  SDLUtils
    \brief  A window displaying textures
*/
class SDLUtils {
    private:
        const int COLOR_KEY_R = 0;
        const int COLOR_KEY_G = 0;
        const int COLOR_KEY_B = 0;

        SDL_Window* mwindow = nullptr;
        SDL_Renderer* mrenderer = nullptr;

    public:
        /*!
            \brief      Report errors and exit the program if necessary
        */
        void logError(const std::string &msg, const std::string &error, bool fatal);

        /*!
            \brief      Constructor creating window.
            \sa         SDL_CreateWindow()
            \sa         SDL_CreateRenderer()
        */
        SDLUtils(const int &screenWidth, const int &screenHeight, const std::string &windowTitle);

        /*!
            \brief      Destructor.
        */
        virtual ~SDLUtils();

        /*!
            \brief      Delete image
        */
        virtual void del(SDL_Rect rect);

        /*!
            \brief      Render image
            \param      surface ISurface object where the image is rendered from
            \param      delBeforeRender del the previous rendered image
            \details    warning: surface will be destroyed afterward
        */
        virtual SDL_Rect render(ISurface* surface, bool delBeforeRender = true);

        /*!
            \brief      Update the window.
            \sa         SDL_RenderPresent()
        */
        virtual void present();
};

#endif
