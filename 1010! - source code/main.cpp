/*!
    \file       main.cpp
    \brief      This file starts the game.
    \author     Nguyen Minh Tan
    \version    1.0
    \date       01/04/2019
    \pre        Add linker options: -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf.
                Then search directories: Compiler for include\SDL2\ folder and Linker for lib\ folder.
*/
#include "SDL_utils.h"

using namespace std;

/*!
    \class Game1010
    \brief The game itself
*/
class Game1010 {
    private:
        const int SCREEN_WIDTH = 1280, SCREEN_HEIGHT = 720, NUM_FIGURE = 3, MAX_FIGURE_HEIGHT = 5, BOARD_HEIGHT = 10, SCORE_DIGITS = 6, FONT_SIZE = 72;
        const string GAME_TITLE = "1010!";
        const string IMG_DIGIT_SOURCE = "img/digits/default-";
        const string IMG_DIGIT_TYPE = "png";
        const string IMG_GRID_SOURCE = "img/grid.png";
        const string IMG_LOGO_SOURCE = "img/logo.png";
        const string IMG_CUP_SOURCE = "img/cup.jpg";
        const string FONT_SOURCE = "font/zorque.ttf";
        const string ICON_SOURCE = "icons/";
        const string ICON_TYPE = ".png";

        vector<string> buttons {"Retry", "Sound ON ", "Sound OFF"};
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
        vector<Color> pieces_colors = {
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
        Score current_score, high_score;
        SDLUtils window = SDLUtils(SCREEN_WIDTH, SCREEN_HEIGHT, GAME_TITLE);
        vector<Shape> piece_list = vector<Shape>(NUM_FIGURE);
        vector<Button> button_list = vector<Button>(buttons.size());
        bool quit = false;
        int num_piece = NUM_FIGURE;
    public:
        /*!
            \brief  constructor initializing the game
            \sa     gen_piece()
            \sa     SDLUtils::draw()
        */
        Game1010() {
            gameboard.setUnitSquareSize(SCREEN_HEIGHT / (BOARD_HEIGHT + 2));
            gameboard.setUnitSquareImg(IMG_GRID_SOURCE);
            gameboard.setPos((SCREEN_WIDTH - gameboard.getSizeX()) / 2, (SCREEN_HEIGHT - gameboard.getSizeY()) / 2);
            gameboard.setColor(96, 96, 96); //Gray

            current_score.setDigitImg(IMG_DIGIT_SOURCE, IMG_DIGIT_TYPE);
            current_score.setDSize(44, 46);
            current_score.setPos((gameboard.getX() - current_score.getDSizeX() * SCORE_DIGITS) / 2, SCREEN_HEIGHT * 3 / 4 + gameboard.getX() / 7 - current_score.getDSizeY() / 2);

            high_score.setDigitImg(IMG_DIGIT_SOURCE, IMG_DIGIT_TYPE);
            high_score.setDSize(44, 46);
            high_score.load();
            high_score.save();
            high_score.setPos((gameboard.getX() - high_score.getDSizeX() * SCORE_DIGITS) / 2, SCREEN_HEIGHT / 4 + gameboard.getX() / 6 - high_score.getDSizeY() / 2);

            for (int i = 1; i < pieces_rates.size(); ++i) pieces_rates[i] += pieces_rates[i - 1];
            gen_piece();

            for (int i = 0; i < buttons.size(); ++i) {
                button_list[i].setName(buttons[i]);
                button_list[i].setTriggeredFontColor({0, 0xFF, 0xFF});
                button_list[i].setTriggeredSizeRate(1.1);
                button_list[i].setIcon(ICON_SOURCE + buttons[i] + ICON_TYPE, 0);
            }

            window.draw(IMG_LOGO_SOURCE, 0, -gameboard.getX() / 4, gameboard.getX(), gameboard.getX());
            window.draw(&high_score, SCORE_DIGITS);
            window.draw(IMG_CUP_SOURCE, gameboard.getX() / 4, SCREEN_HEIGHT / 2 - gameboard.getX() / 10, gameboard.getX() / 2, gameboard.getX() / 2);
            window.draw(&current_score, SCORE_DIGITS);
            window.draw(&gameboard);
            for (int i = 0; i < NUM_FIGURE; ++i) window.draw(&piece_list[i]);
            window.present();
        }

        /*!
            \brief  Get a random piece from pieces[]
        */
        pair<vector<vector<bool> >, Color> randShape() {
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
                pair<vector<vector<bool> >, Color> tmp = randShape();
                piece_list[i].setBitMap(tmp.first);
                piece_list[i].setUnitSquareSize(SCREEN_HEIGHT / (MAX_FIGURE_HEIGHT * NUM_FIGURE + NUM_FIGURE + 1));
                piece_list[i].setUnitSquareImg(IMG_GRID_SOURCE);
                piece_list[i].setPos(SCREEN_WIDTH - (gameboard.getX() - piece_list[i].getSizeX()) / 2 - piece_list[i].getSizeX(),
                                        (SCREEN_HEIGHT - (piece_list[i].getUnitSquareSize() * MAX_FIGURE_HEIGHT * NUM_FIGURE)) * (i + 1) / (NUM_FIGURE + 1)
                                        + piece_list[i].getUnitSquareSize() * (MAX_FIGURE_HEIGHT * (2 * i + 1) - piece_list[i].getHeight()) / 2);
                piece_list[i].setColor(tmp.second.getR(), tmp.second.getG(), tmp.second.getB());
                piece_list[i].recover();
            }
        }

        void show_menu(Menu* menu) {
            /*!
                Remove the current board from the screen.
                Minimize and put it back into the screen.
            */
            Board _gameboard = gameboard;
            window.draw(_gameboard.del());
            _gameboard.setUnitSquareSize(SCREEN_HEIGHT * (MAX_FIGURE_HEIGHT * NUM_FIGURE + NUM_FIGURE - 1) / ((MAX_FIGURE_HEIGHT + 1) * (BOARD_HEIGHT * NUM_FIGURE + BOARD_HEIGHT + NUM_FIGURE) - 1));
            _gameboard.setPos((SCREEN_WIDTH - _gameboard.getSizeX()) / 2, _gameboard.getUnitSquareSize());
            window.draw(_gameboard.recover());

            /*!
                Remove the remaining pieces from the screen.
                Put them under the minimized board to make space for menu.
            */
            vector<Shape> _piece_list = piece_list;
            for (int i = 0; i < NUM_FIGURE; ++i)
                if (!_piece_list[i].isDel()) {
                    window.draw(_piece_list[i].del());
                    _piece_list[i].setUnitSquareSize(_gameboard.getSizeX() / (MAX_FIGURE_HEIGHT * NUM_FIGURE + NUM_FIGURE - 1));
                    _piece_list[i].setPos(i * _piece_list[i].getUnitSquareSize() * (MAX_FIGURE_HEIGHT + 1) + _gameboard.getX() + _piece_list[i].getUnitSquareSize() * (MAX_FIGURE_HEIGHT + 1 - _piece_list[i].getWidth()) / 2,
                                          (SCREEN_HEIGHT - _gameboard.getY() - _gameboard.getSizeY() - _piece_list[i].getSizeY()) / 2 + _gameboard.getY() + _gameboard.getSizeY());
                    window.draw(_piece_list[i].recover());
                }

            window.draw(menu);  //! Show menu.
            window.present();

            int last_button = -1;
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
                                    Clicking on the "Retry" button restarts the game:
                              */
                                if (button_cur->getName() == buttons[0]) {
                                    window.draw(_gameboard.del());
                                    for (int i = 0; i < NUM_FIGURE; ++i)
                                        if (!_piece_list[i].isDel()) window.draw(_piece_list[i].del());
                                    window.draw(menu->del());
                                    current_score.setVal(0);    //!Set current score to 0,
                                    window.draw(&current_score, SCORE_DIGITS);
                                    gameboard.clear();          //!Clear the board,
                                    num_piece = NUM_FIGURE;
                                    gen_piece();                //!Generate new pieces
                                    for (int i = 0; i < NUM_FIGURE; ++i) window.draw(&piece_list[i]);
                                    return;
                                }
                                /*!
                                    Clicking on the "Sound" button turn on/off game sounds.
                              */
                                if (button_cur->getName() == buttons[1]) {
                                    window.draw(button_cur->del());
                                    button_cur->setName(buttons[2]);
                                    button_cur->setIcon(button_list[2].getIcon(), button_cur->getNormalIconSize());
                                    window.draw(button_cur->recover());
                                    swap(buttons[1], buttons[2]);
                                    swap(button_list[1], button_list[2]);
                                    continue;
                                }
                            }
                            break;
                        /*!
                            Highlight button that is being pointed at.
                       */
                        case SDL_MOUSEMOTION:
                            if (last_button >= 0 && !menu->getButton(last_button)->inside(mouse_x, mouse_y)) {
                                window.draw(menu->getButton(last_button)->del());
                                window.draw(menu->getButton(last_button)->recover());
                                last_button = -1;
                            }
                            if (last_button != index && button_cur != nullptr && button_cur->inside(mouse_x, mouse_y)) {
                                last_button = index;
                                window.draw(button_cur->del());
                                window.draw(button_cur->recover());
                            }
                            break;
                    }
                    window.present();
                }
            }
        }

        /*!
            \brief  GAME OVER menu shows up when placing any piece on the board is not possible.
            \sa     show_menu()
        */
        void gameOver() {
            Menu game_over(856 + 50, 200, SCREEN_WIDTH - 856 - 100, 300, "GAME OVER");
            game_over.setButtonPos(0, 150);
            game_over.setFont(FONT_SOURCE, FONT_SIZE, {0xFF, 0xFF, 0xFF});
            game_over.pushButton(button_list[0]);
            game_over.pushButton(button_list[1]);
            show_menu(&game_over);
        }

        /*!
            \brief  Play the game!
            \sa     gen_piece()
            \sa     Board::set()
            \sa     gameOver()
        */
        void play() {
            int chosen_piece = -1;
            SDL_Event e;
            while (!quit) {
                while (SDL_PollEvent(&e)) {
                    int mouse_x, mouse_y;
                    SDL_GetMouseState(&mouse_x, &mouse_y);
                    switch (e.type) {
                        case SDL_QUIT:
                            quit = true;
                            break;
                        /*!
                            Check whether any piece is chosen.
                       */
                        case SDL_MOUSEBUTTONDOWN:
                            for (int i = 0; i < NUM_FIGURE; ++i)
                                if (piece_list[i].inside(mouse_x, mouse_y)) window.draw(piece_list[chosen_piece = i].del());
                            break;
                        case SDL_MOUSEBUTTONUP:
                            if (chosen_piece >= 0) {
                                if (!gameboard.inside(mouse_x, mouse_y) || gameboard.collideMouse(mouse_x, mouse_y, &piece_list[chosen_piece])) {
                                    window.draw(piece_list[chosen_piece].recover());    //!Return the chosen piece to the list if it does not fit.
                                } else {
                                                                                        //!Otherwise, place it on the board,
                                    gameboard.set(mouse_x, mouse_y, piece_list[chosen_piece].del(), &current_score);
                                    window.draw(&current_score, SCORE_DIGITS);
                                    if (current_score.cmp(&high_score) > 0) {           //!Update high score.
                                        high_score.setVal(current_score.val());
                                        window.draw(&high_score, SCORE_DIGITS);
                                        high_score.save();
                                    }
                                    if (--num_piece == 0) {
                                        num_piece = NUM_FIGURE;
                                        gen_piece();                                    //!Generate new ones when all pieces are in place.
                                        for (int i = 0; i < NUM_FIGURE; ++i) window.draw(&piece_list[i]);
                                    }
                                    bool can_continue = false;
                                    for (int i = 0; i < NUM_FIGURE; ++i)
                                        if (!piece_list[i].isDel() && gameboard.canSet(&piece_list[i])) can_continue = true;
                                    if (!can_continue) gameOver();                      //!GAME OVER menu shows up when placing any piece on the board is not possible.
                                }
                                chosen_piece = -1;
                                window.draw(&gameboard);
                            }
                            break;
                        case SDL_MOUSEMOTION:
                            if (chosen_piece >= 0) {
                                window.draw(&gameboard);
                                if (gameboard.inside(mouse_x, mouse_y)) window.draw(gameboard.preview(mouse_x, mouse_y, piece_list[chosen_piece]));
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
