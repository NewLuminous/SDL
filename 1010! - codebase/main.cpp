/*!
    \file       main.cpp
    \brief      This file starts the game.
    \author     Nguyen Minh Tan
    \version    1.3.0
    \date       04/05/2019
    \pre        Add linker options: -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer.
                Then search directories: Compiler for include\SDL2\ folder and Linker for lib\ folder.
*/

#include "SDL_utils.h"
#include "board_surface.h"
#include "menu_surface.h"
#include "visible_encrypted_num_surface.h"
#include "visible_shape_surface.h"

using namespace std;

/*!
    \class Game1010
    \brief The game itself
*/
class Game1010 {
    private:
        const int SCREEN_WIDTH = 1280, SCREEN_HEIGHT = 720, NUM_FIGURE = 3, MAX_FIGURE_HEIGHT = 5, BOARD_HEIGHT = 10, SCORE_DIGITS = 6, FONT_SIZE = 72, ICON_SIZE = 30;
        const string GAME_TITLE = "1010!";
        const string IMG_DIGIT_SOURCE = "img/digits/default-";
        const string IMG_DIGIT_TYPE = "png";
        const string IMG_GRID_SOURCE = "img/unit_square.png";
        const string IMG_GRID_REVERSE_SOURCE = "img/unit_square_reverse.png";
        const string IMG_LOGO_SOURCE = "img/logo.png";
        const string IMG_CUP_SOURCE = "img/cup.jpg";
        const string FONT_SOURCE = "font/zorque.ttf";
        const string ICON_SOURCE = "icons/";
        const string ICON_TYPE = "png";
        const string SOUND_SOURCE = "sound/";
        const string SOUND_TYPE = "wav";
        const RGBColor BOARD_COLOR = {96, 96, 96};

        vector<string> buttons {"Retry", "Sound ON", "Sound OFF", "Resume"};
        vector<vector<vector<bool> > > pieces {
                                                {
                                                    {1}},
                                                {
                                                    {1, 1}},
                                                {
                                                    {1},
                                                    {1}},
                                                {
                                                    {1, 1, 1}},
                                                {
                                                    {1},
                                                    {1},
                                                    {1}},
                                                {
                                                    {0, 1},
                                                    {1, 1}},
                                                {
                                                    {1, 0},
                                                    {1, 1}},
                                                {
                                                    {1, 1},
                                                    {0, 1}},
                                                {
                                                    {1, 1},
                                                    {1, 0}},
                                                {
                                                    {1, 1, 1, 1}},
                                                {
                                                    {1},
                                                    {1},
                                                    {1},
                                                    {1}},
                                                {
                                                    {1, 1},
                                                    {1, 1}},
                                                {
                                                    {1, 1, 1, 1, 1}},
                                                {
                                                    {1},
                                                    {1},
                                                    {1},
                                                    {1},
                                                    {1}},
                                                {
                                                    {0, 0, 1},
                                                    {0, 0, 1},
                                                    {1, 1, 1}},
                                                {
                                                    {1, 0, 0},
                                                    {1, 0, 0},
                                                    {1, 1, 1}},
                                                {
                                                    {1, 1, 1},
                                                    {0, 0, 1},
                                                    {0, 0, 1}},
                                                {
                                                    {1, 1, 1},
                                                    {1, 0, 0},
                                                    {1, 0, 0}},
                                                {
                                                    {1, 1, 1},
                                                    {1, 1, 1},
                                                    {1, 1, 1}}};
        vector<RGBColor> pieces_colors = {
                                        {128, 128, 255},
                                        {255, 255, 128},
                                        {255, 255, 128},
                                        {255, 128,  64},
                                        {255, 128,  64},
                                        {128, 255, 128},
                                        {128, 255, 128},
                                        {128, 255, 128},
                                        {128, 255, 128},
                                        {255, 128, 153},
                                        {255, 128, 153},
                                        {128, 255,  68},
                                        {255,  64, 128},
                                        {255,  64, 128},
                                        {128, 255, 255},
                                        {128, 255, 255},
                                        {128, 255, 255},
                                        {128, 255, 255},
                                        { 64, 255, 128}};
        vector<int> pieces_rates = {20, 70, 70, 70, 70, 35, 35, 35, 35, 35, 35, 140, 70, 70, 35, 35, 35, 35, 70};

        Board gameboard = Board(BOARD_HEIGHT, BOARD_HEIGHT);
        VisibleEncryptedNum current_score;
        VisibleEncryptedNum high_score;
        SDLUtils window = SDLUtils(SCREEN_WIDTH, SCREEN_HEIGHT, GAME_TITLE);
        vector<VisibleShape> piece_list = vector<VisibleShape>(NUM_FIGURE);
        vector<Button> button_list = vector<Button>(buttons.size());
        Button pause_button;
        Mix_Chunk *click_menu_sound, *complete_line_sound, *new_game_sound, *new_pieces_sound, *place_fail_sound, *place_success_sound;
        Mix_Music *game_over_sound;
        bool quit = false, sound_mode = true;
        int num_piece = NUM_FIGURE;
    public:
        /*!
            \brief  constructor initializing the game
            \sa     gen_piece()
            \sa     SDLUtils::draw()
        */
        Game1010() {
            gameboard.setUnitSquareImg(Image("", "", IMG_GRID_SOURCE));
            gameboard.setUnitSquareSize(SCREEN_HEIGHT / (BOARD_HEIGHT + 2));
            gameboard.setCoordinate((SCREEN_WIDTH - gameboard.getWidth()) / 2, (SCREEN_HEIGHT - gameboard.getHeight()) / 2);
            gameboard.setColor(BOARD_COLOR); //Gray

            current_score.setType(IMG_DIGIT_TYPE);
            current_score.setLocation(IMG_DIGIT_SOURCE);
            current_score.setDWidth(44);
            current_score.setDHeight(46);
            current_score.setCoordinate((gameboard.getX() - current_score.getDWidth() * SCORE_DIGITS) / 2, SCREEN_HEIGHT * 3 / 4 + gameboard.getX() / 7 - current_score.getDHeight() / 2);

            high_score.setType(IMG_DIGIT_TYPE);
            high_score.setLocation(IMG_DIGIT_SOURCE);
            high_score.setDWidth(44);
            high_score.setDHeight(46);
            high_score.load();
            high_score.save();
            high_score.setCoordinate((gameboard.getX() - high_score.getDWidth() * SCORE_DIGITS) / 2, SCREEN_HEIGHT / 4 + gameboard.getX() / 6 - high_score.getDHeight() / 2);

            for (int i = 1; i < (int)pieces_rates.size(); ++i) pieces_rates[i] += pieces_rates[i - 1];
            gen_piece();

            for (int i = 0; i < (int)buttons.size(); ++i) {
                button_list[i].setTitle(Font(FONT_SOURCE, buttons[i]));
                button_list[i].setIcon(Image(ICON_TYPE, buttons[i], ICON_SOURCE));
            }
            pause_button.setIcon(Image(ICON_TYPE, "Pause", ICON_SOURCE));
            pause_button.setHeight(ICON_SIZE);
            pause_button.setWidth(ICON_SIZE);
            pause_button.setCoordinate(SCREEN_WIDTH - ICON_SIZE * 3 / 2 + 1, ICON_SIZE / 2);
            window.render(new ButtonSurface(pause_button));

            Image logo("", "", IMG_LOGO_SOURCE);
            logo.setCoordinate(0, -gameboard.getX() / 4);
            logo.setSize(gameboard.getX(), gameboard.getX());
            window.render(new ImageSurface(logo), false);
            window.render(new VisibleEncryptedNumSurface(high_score), false);
            Image cup("", "", IMG_CUP_SOURCE);
            cup.setCoordinate(gameboard.getX() / 4, SCREEN_HEIGHT / 2 - gameboard.getX() / 10);
            cup.setSize(gameboard.getX() / 2, gameboard.getX() / 2);
            window.render(new ImageSurface(cup), false);
            window.render(new VisibleEncryptedNumSurface(current_score), false);
            window.render(new BoardSurface(gameboard), false);

            for (int i = 0; i < NUM_FIGURE; ++i) window.render(new VisibleShapeSurface(piece_list[i]));
            window.present();

            click_menu_sound = Mix_LoadWAV((SOUND_SOURCE + "click_menu." + SOUND_TYPE).c_str());
            if (click_menu_sound == nullptr) window.logError("Mix_LoadWAV", Mix_GetError(), true);
            complete_line_sound = Mix_LoadWAV((SOUND_SOURCE + "complete_line." + SOUND_TYPE).c_str());
            if (complete_line_sound == nullptr) window.logError("Mix_LoadWAV", Mix_GetError(), true);
            new_game_sound = Mix_LoadWAV((SOUND_SOURCE + "new_game." + SOUND_TYPE).c_str());
            if (new_game_sound == nullptr) window.logError("Mix_LoadWAV", Mix_GetError(), true);
            new_pieces_sound = Mix_LoadWAV((SOUND_SOURCE + "new_pieces." + SOUND_TYPE).c_str());
            if (new_pieces_sound == nullptr) window.logError("Mix_LoadWAV", Mix_GetError(), true);
            place_fail_sound = Mix_LoadWAV((SOUND_SOURCE + "place_fail." + SOUND_TYPE).c_str());
            if (place_fail_sound == nullptr) window.logError("Mix_LoadWAV", Mix_GetError(), true);
            place_success_sound = Mix_LoadWAV((SOUND_SOURCE + "place_success." + SOUND_TYPE).c_str());
            if (place_success_sound == nullptr) window.logError("Mix_LoadWAV", Mix_GetError(), true);

            game_over_sound = Mix_LoadMUS((SOUND_SOURCE + "game_over." + SOUND_TYPE).c_str());
            if (game_over_sound == nullptr) window.logError("Mix_LoadMUS", Mix_GetError(), true);
        }

        /*!
            \brief  destructor deleting pointers
        */
        ~Game1010() {
            Mix_FreeChunk(click_menu_sound);
            Mix_FreeChunk(complete_line_sound);
            Mix_FreeChunk(new_game_sound);
            Mix_FreeChunk(new_pieces_sound);
            Mix_FreeChunk(place_fail_sound);
            Mix_FreeChunk(place_success_sound);
            Mix_FreeMusic(game_over_sound);
        }

        /*!
            \brief  Get a random piece from pieces[]
        */
        pair<vector<vector<bool> >, RGBColor> randShape() {
            int i = 0, rand_num = rand() % pieces_rates[pieces_rates.size() - 1] + 1;
            while (rand_num > pieces_rates[i]) ++i;
            return {pieces[i], pieces_colors[i]};
        }

        /*!
            \brief  Generate new ones when all pieces are in place
            \sa     randShape()
        */
        void gen_piece() {
            for (int i = 0; i < NUM_FIGURE; ++i) {
                pair<vector<vector<bool> >, RGBColor> tmp = randShape();
                piece_list[i].setBitMap(tmp.first);
                piece_list[i].setUnitSquareSize(SCREEN_HEIGHT / (MAX_FIGURE_HEIGHT * NUM_FIGURE + NUM_FIGURE + 1));
                piece_list[i].setUnitSquareImg(Image("", "", IMG_GRID_SOURCE));
                piece_list[i].setCoordinate(SCREEN_WIDTH - (gameboard.getX() - piece_list[i].getWidth()) / 2 - piece_list[i].getWidth(),
                                            (SCREEN_HEIGHT - (piece_list[i].getUnitSquareSize() * MAX_FIGURE_HEIGHT * NUM_FIGURE)) * (i + 1) / (NUM_FIGURE + 1)
                                            + piece_list[i].getUnitSquareSize() * (MAX_FIGURE_HEIGHT * (2 * i + 1) - piece_list[i].getRowNum()) / 2);
                piece_list[i].setColor({tmp.second.getR(), tmp.second.getG(), tmp.second.getB()});
            }
        }

        void show_menu(Menu* menu) {
            /*!
                Remove the current board from the screen.
                Minimize and put it back into the screen.
            */
            window.del({gameboard.getX(), gameboard.getY(), gameboard.getWidth(), gameboard.getHeight()});
            Board _gameboard = gameboard;
            _gameboard.setUnitSquareSize(SCREEN_HEIGHT * (MAX_FIGURE_HEIGHT * NUM_FIGURE + NUM_FIGURE - 1) / ((MAX_FIGURE_HEIGHT + 1) * (BOARD_HEIGHT * NUM_FIGURE + BOARD_HEIGHT + NUM_FIGURE) - 1));
            _gameboard.setCoordinate((SCREEN_WIDTH - _gameboard.getWidth()) / 2, _gameboard.getUnitSquareSize());
            window.render(new BoardSurface(_gameboard), false);

            /*!
                Remove the remaining pieces from the screen.
                Put them under the minimized board to make space for menu.
            */
            vector<VisibleShape> _piece_list = piece_list;
            for (int i = 0; i < NUM_FIGURE; ++i) {
                    window.del({_piece_list[i].getX(), _piece_list[i].getY(), _piece_list[i].getWidth(), _piece_list[i].getHeight()});
                    _piece_list[i].setUnitSquareSize(_gameboard.getWidth() / (MAX_FIGURE_HEIGHT * NUM_FIGURE + NUM_FIGURE - 1));
                    _piece_list[i].setCoordinate(i * _piece_list[i].getUnitSquareSize() * (MAX_FIGURE_HEIGHT + 1) + _gameboard.getX()
                                                   + _piece_list[i].getUnitSquareSize() * (MAX_FIGURE_HEIGHT + 1 - _piece_list[i].getColNum()) / 2,
                                                (SCREEN_HEIGHT - _gameboard.getY() - _gameboard.getHeight() - _piece_list[i].getHeight()) / 2
                                                               + _gameboard.getY() + _gameboard.getHeight());
                    window.render(new VisibleShapeSurface(_piece_list[i]), false);
                }

            window.render(new MenuSurface(*menu), false);  //! Show menu.
            window.present();

            //int last_button = -1;
            SDL_Event e;
            while (!quit) {
                while (SDL_PollEvent(&e)) {
                    int mouse_x, mouse_y;
                    SDL_GetMouseState(&mouse_x, &mouse_y);
                    int index = menu->getButtonIndex(mouse_y);
                    Button* button_cur = menu->getButton(index);
                    switch (e.type) {
                        case SDL_QUIT:
                            quit = true;
                            break;
                        case SDL_MOUSEBUTTONDOWN:
                            if (button_cur != nullptr && button_cur->inside(mouse_x, mouse_y)) {
                                /*!
                                    Clicking on the "Resume" button resume the game:
                              */
                                if (button_cur->getTitle().getText() == buttons[3]) {
                                    if (sound_mode) Mix_PlayChannel(-1, click_menu_sound, 0);
                                    window.del({_gameboard.getX(), _gameboard.getY(), _gameboard.getWidth(), _gameboard.getHeight()});
                                    for (int i = 0; i < NUM_FIGURE; ++i)
                                        window.del({_piece_list[i].getX(), _piece_list[i].getY(), _piece_list[i].getWidth(), _piece_list[i].getHeight()});
                                    window.del({menu->getX(), menu->getY(), menu->getWidth(), menu->getHeight()});
                                    for (int i = 0; i < NUM_FIGURE; ++i) window.render(new VisibleShapeSurface(piece_list[i]), false);
                                    return;
                                }
                                /*!
                                    Clicking on the "Retry" button restarts the game:
                              */
                                if (button_cur->getTitle().getText() == buttons[0]) {
                                    if (sound_mode) Mix_PlayChannel(-1, new_game_sound, 0);
                                    window.del({_gameboard.getX(), _gameboard.getY(), _gameboard.getWidth(), _gameboard.getHeight()});
                                    for (int i = 0; i < NUM_FIGURE; ++i)
                                        window.del({_piece_list[i].getX(), _piece_list[i].getY(), _piece_list[i].getWidth(), _piece_list[i].getHeight()});
                                    window.del({menu->getX(), menu->getY(), menu->getWidth(), menu->getHeight()});
                                    current_score.setVal(0);    //!Set current score to 0,
                                    window.render(new VisibleEncryptedNumSurface(current_score));
                                    gameboard.clear();          //!Clear the board,
                                    num_piece = NUM_FIGURE;
                                    gen_piece();                //!Generate new pieces
                                    for (int i = 0; i < NUM_FIGURE; ++i) window.render(new VisibleShapeSurface(piece_list[i]), false);
                                    return;
                                }
                                /*!
                                    Clicking on the "Sound" button turn on/off game sounds.
                              */
                                if (button_cur->getTitle().getText() == buttons[1]) {
                                    if (sound_mode) Mix_PlayChannel(-1, click_menu_sound, 0);
                                    sound_mode = !sound_mode;
                                    if (!sound_mode && Mix_PlayingMusic()) Mix_HaltMusic();
                                    window.del({button_cur->getX(), button_cur->getY(), button_cur->getWidth(), button_cur->getHeight()});
                                    Font font(FONT_SOURCE, buttons[2]);
                                    font.setCoordinate(button_cur->getX() + button_cur->getHeight() * 2, button_cur->getY());
                                    font.setHeight(button_cur->getHeight());
                                    font.setWidth(button_cur->getWidth() - button_cur->getHeight() * 2);
                                    font.setColor(button_cur->getColor());
                                    button_cur->setTitle(font);
                                    Image icon = button_list[2].getIcon();
                                    icon.setCoordinate(button_cur->getX(), button_cur->getY());
                                    icon.setSize(button_cur->getHeight(), button_cur->getHeight());
                                    icon.setColor(button_cur->getColor());
                                    button_cur->setIcon(icon);
                                    window.render(new ButtonSurface(*button_cur));
                                    swap(buttons[1], buttons[2]);
                                    swap(button_list[1], button_list[2]);
                                    continue;
                                }
                            }
                            break;
                        /*!
                            Highlight button that is being pointed at.
                       */
                        /*
                        case SDL_MOUSEMOTION:
                            if (last_button >= 0 && !menu->getButton(last_button)->inside(mouse_x, mouse_y)) {
                                window.del({menu->getButton(last_button)->getX(), menu->getButton(last_button)->getY(),
                                            menu->getButton(last_button)->getWidth(), menu->getButton(last_button)->getHeight()});
                                window.render(new ButtonSurface(*menu->getButton(last_button)));
                                last_button = -1;
                            }
                            if (last_button != index && button_cur != nullptr && button_cur->inside(mouse_x, mouse_y)) {
                                last_button = index;
                                window.del({button_cur->getX(), button_cur->getY(), button_cur->getWidth(), button_cur->getHeight()});
                                window.render(new ButtonSurface(*button_cur));
                            }
                            break;*/
                    }
                    window.present();
                }
            }
        }

        /*!
            \sa     show_menu()
        */
        void gamePaused() {
            if (sound_mode) Mix_PlayChannel(-1, click_menu_sound, 0);

            window.del({pause_button.getX(), pause_button.getY(), pause_button.getWidth(), pause_button.getHeight()});

            Menu game_paused_menu(Font(FONT_SOURCE, "GAME PAUSED"));
            game_paused_menu.setCoordinate(856 + 50, 100);
            game_paused_menu.setWidth(SCREEN_WIDTH - 856 - 100);
            game_paused_menu.setHeight(400);
            game_paused_menu.setButtonCoordinate(0, 150);
            game_paused_menu.setColor({0xFF, 0xFF, 0xFF});
            game_paused_menu.pushButton(button_list[3]);
            game_paused_menu.pushButton(button_list[0]);
            game_paused_menu.pushButton(button_list[1]);
            show_menu(&game_paused_menu);

            window.render(new ButtonSurface(pause_button));
        }

        /*!
            \brief  GAME OVER menu shows up when placing any piece on the board is not possible.
            \sa     show_menu()
        */
        void gameOver() {
            if (sound_mode && Mix_PlayingMusic() == 0) Mix_PlayMusic(game_over_sound, 1);

            window.del({pause_button.getX(), pause_button.getY(), pause_button.getWidth(), pause_button.getHeight()});

            Menu game_over_menu(Font(FONT_SOURCE, "GAME OVER"));
            game_over_menu.setCoordinate(856 + 50, 200);
            game_over_menu.setWidth(SCREEN_WIDTH - 856 - 100);
            game_over_menu.setHeight(300);
            game_over_menu.setButtonCoordinate(0, 150);
            game_over_menu.setColor({0xFF, 0xFF, 0xFF});
            game_over_menu.pushButton(button_list[0]);
            game_over_menu.pushButton(button_list[1]);
            show_menu(&game_over_menu);

            window.render(new ButtonSurface(pause_button));
        }

        /*!
            \brief  Play the game!
            \sa     gen_piece()
            \sa     Board::set()
            \sa     gameOver()
        */
        void play() {
            int chosen_piece = -1;
            SDL_Rect last_rendered = {-1, -1, 0, 0};
            SDL_Event e;
            while (!quit) {
                while (SDL_PollEvent(&e)) {
                    int mouse_x, mouse_y;
                    SDL_GetMouseState(&mouse_x, &mouse_y);
                    /*!
                        Redraw pieces in case the chosen piece overlaps them
                    */
                    if (chosen_piece >= 0) {
                        window.del({last_rendered.x, last_rendered.y, last_rendered.w, last_rendered.h});
                        for (int i = 0; i < NUM_FIGURE; ++i)
                            if (i != chosen_piece) window.render(new VisibleShapeSurface(piece_list[i]), false);
                    }
                    switch (e.type) {
                        case SDL_QUIT:
                            quit = true;
                            break;
                        /*!
                            Check whether player pauses the game. If not, check whether any piece is chosen.
                       */
                        case SDL_MOUSEBUTTONDOWN:
                            if (pause_button.inside(mouse_x, mouse_y)) {
                                gamePaused();
                                window.render(new BoardSurface(gameboard));
                            }
                            for (int i = 0; i < NUM_FIGURE; ++i)
                                if (piece_list[i].inside(mouse_x, mouse_y)) {
                                    chosen_piece = i;
                                    last_rendered = {piece_list[i].getX(), piece_list[i].getY(), piece_list[i].getWidth(), piece_list[i].getHeight()};
                                }
                            break;
                        case SDL_MOUSEBUTTONUP:
                            if (chosen_piece >= 0) {
                                if (!gameboard.inside(mouse_x, mouse_y) || !gameboard.canPlaceShapeAtCoordinate(&piece_list[chosen_piece], mouse_x, mouse_y)) {
                                    if (sound_mode) Mix_PlayChannel(-1, place_fail_sound, 0);
                                    window.render(new VisibleShapeSurface(piece_list[chosen_piece]), false);    //!Return the chosen piece to the list if it does not fit.
                                } else {
                                                                                        //!Otherwise, place it on the board,
                                    if (gameboard.placeMouse(&piece_list[chosen_piece], mouse_x, mouse_y, &current_score)) {
                                        if (sound_mode) Mix_PlayChannel(-1, complete_line_sound, 0);
                                    }
                                    else if (sound_mode) Mix_PlayChannel(-1, place_success_sound, 0);
                                    window.render(new VisibleEncryptedNumSurface(current_score));
                                    if (current_score.cmp(&high_score) > 0) {           //!Update high score.
                                        high_score.setVal(current_score.val());
                                        window.render(new VisibleEncryptedNumSurface(high_score));
                                        high_score.save();
                                    }
                                    if (--num_piece == 0) {
                                        if (sound_mode) Mix_PlayChannel(-1, new_pieces_sound, 0);
                                        num_piece = NUM_FIGURE;
                                        gen_piece();                                    //!Generate new ones when all pieces are in place.
                                        for (int i = 0; i < NUM_FIGURE; ++i) window.render(new VisibleShapeSurface(piece_list[i]), false);
                                    }
                                    bool can_continue = false;
                                    for (int i = 0; i < NUM_FIGURE; ++i)
                                        if (gameboard.isAnySpacePlaceable(&piece_list[i])) can_continue = true;
                                    if (!can_continue) gameOver();                      //!GAME OVER menu shows up when placing any piece on the board is not possible.
                                }
                                chosen_piece = -1;
                                window.render(new BoardSurface(gameboard));
                            }
                            break;
                        case SDL_MOUSEMOTION:
                            if (chosen_piece >= 0) {
                                window.render(new BoardSurface(gameboard.sub(last_rendered.x, last_rendered.y, last_rendered.w, last_rendered.h)), false);
                                if (gameboard.inside(mouse_x, mouse_y)) {               //!Preview the position of the shape if it is placed
                                    last_rendered = window.render(new VisibleShapeSurface(gameboard.preview(piece_list[chosen_piece], mouse_x, mouse_y, IMG_GRID_REVERSE_SOURCE)), false);
                                }
                                else
                                    if (mouse_x >= gameboard.getX()) last_rendered = window.render(new VisibleShapeSurface(piece_list[chosen_piece].clone(mouse_x, mouse_y)), false);
                            }
                            break;
                    }
                    window.present();
                }
            }

        }
};

int main(int argc, char**argv) {
    Game1010* game = new Game1010;
    game->play();
    delete game;
    return 0;
}
