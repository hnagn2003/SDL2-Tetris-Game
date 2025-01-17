#ifndef Tetromino_h
#define Tetromino_h

// #include <stdio.h>
// #include <SDL_image.h>
#include "Specifications.h"
#include "Grid.h"
#include "Game.h"
#include <algorithm>  
const int xTetradsInit = 3;
const int yTetradsInit = -1;
const int sizeOfTetradsSide = 4;

void transPos(bool matrix[sizeOfTetradsSide][sizeOfTetradsSide]);
enum TetroType
{
    I_BLOCK,
    L_BLOCK,
    J_BLOCK,
    O_BLOCK,
    S_BLOCK,
    T_BLOCK,
    Z_BLOCK,
    TOTAL_OF_TETRADS
};

const SDL_Color TetroColor[] = {
    {0, 209, 232},
    {0, 126, 229},
    {218, 147, 0},
    {232, 214, 0},
    {0, 222, 61},
    {187, 0, 222},
    {232, 0, 0}
};

class Tetromino{
    private:
        TetroType type;
        SDL_Color color;
        // xPos, yPos tọa độ x, y chiếu trong bảng grid
        int xPos, yPos;
        // hình chữ nhật bao quanh khối tetrads
        SDL_Rect collin;
        // mảng 2 chiều đại diện cho khối tetrads
        bool matrix[sizeOfTetradsSide][sizeOfTetradsSide];
        bool active;
        bool falling;
        bool pause;
        Uint32 startTime;
    public:
        Tetromino();
        Tetromino (TetroType _type, SDL_Color _color, bool _matrix[sizeOfTetradsSide][sizeOfTetradsSide], int _w, int _h, int _x, int _y, int _xPos = xTetradsInit, int _yPos = yTetradsInit);
        ~Tetromino();
        void setCollinYInitTetrads(int landingPoint);
        TetroType getType();
        bool getStatus();
        void setActice(bool _active);
        bool getFall();
        void setFall(bool fall);
        int getXPos();
        int getYPos();
        void setXPos(int x);
        void setYPos(int y);
        int getXCol();
        int getYCol();
        int getWCol();
        int getHCol();
        void setPause(bool p);
        void render(SDL_Renderer* renderer, int gridXPos, bool ghost = 0);
        void render(SDL_Renderer* renderer, int gridXPos, int x, int y);        // tắt active
        void disableFromActivate();
        // kết nạp khối tetrads vào grid của game
        void mergeToGrid(Grid *grid);
        // kiểm tra va chạm dưới

        bool collision(Grid *grid, bool disabled = 1, bool mergeToGrid_ = 1);
        //kiểm tra chồng chéo giữa các khối tetrads và tetrads với grid
        bool checkSuperimposed(Grid *grid);
        // kiểm tra va chạm với các khối tetrads khác
        bool collisionWithOtherTetrads(Grid *grid);
        // va chạm phải, trái
        bool collisionWithRightTetrads(Grid *grid);
        bool collisionWithLeftTetrads(Grid *grid);
        bool leftCollision(Grid grid);
        bool rightCollision(Grid grid);
        // xác định hình chữ nhật bao quanh khối tetrads
        void detectCoveredRect();

       // hàm thực hiện hành động xoay khối ngược lại
        void rotateBack();
        // rơi khối tetrads
        void fall(int velocity, Grid *grid);
        // di chuyển
        void moveUp(Grid *grid);
        void moveDown(Grid *grid, bool disable = 1);
        void moveRight(Grid *grid);

        void moveLeft(Grid *grid);
        // rơi thẳng xuống nếu phím enter is pressed
        void dropDown(Grid *grid);
        void fixTheSuperimposed(Grid *grid);
        // hàm xoay (fix lỗi va chạm, lỗi chồng chéo khi xoay, có thể refac để code đẹp hơn nhưng em chưa kịp làm)
        void rotate(Grid *grid);
        void swapWithHolding(Tetromino &holding);
        void renderGhostPiece(SDL_Renderer* renderer, Grid* grid);
};
static bool matrixStructure_I[sizeOfTetradsSide][sizeOfTetradsSide] = {
    {0, 0, 0, 0},
    {1, 1, 1, 1},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
};

static bool matrixStructure_L[sizeOfTetradsSide][sizeOfTetradsSide] = {
    {0, 0, 0, 0},
    {1, 0, 0, 0},
    {1, 1, 1, 0},
    {0, 0, 0, 0}
};

static bool matrixStructure_J[sizeOfTetradsSide][sizeOfTetradsSide] = {
    {0, 0, 0, 0},
    {0, 0, 1, 0},
    {1, 1, 1, 0},
    {0, 0, 0, 0}
};

static bool matrixStructure_O[sizeOfTetradsSide][sizeOfTetradsSide] = {
    {0, 0, 0, 0},
    {0, 1, 1, 0},
    {0, 1, 1, 0},
    {0, 0, 0, 0}
};

static bool matrixStructure_S[sizeOfTetradsSide][sizeOfTetradsSide] = {
    {0, 0, 0, 0},
    {0, 1, 1, 0},
    {1, 1, 0, 0},
    {0, 0, 0, 0}
};

static bool matrixStructure_T[sizeOfTetradsSide][sizeOfTetradsSide] = {
    {0, 0, 0, 0},
    {0, 1, 0, 0},
    {1, 1, 1, 0},
    {0, 0, 0, 0}
};

static bool matrixStructure_Z[sizeOfTetradsSide][sizeOfTetradsSide] = {
    {0, 0, 0, 0},
    {1, 1, 0, 0},
    {0, 1, 1, 0},
    {0, 0, 0, 0}
};
// khởi tạo 7 loại tetrads
const Tetromino Tetrads[TOTAL_OF_TETRADS] =
    {
        {
            I_BLOCK,
            TetroColor[I_BLOCK],
            matrixStructure_I,
            4, 1,
            xTetradsInit, yTetradsInit+1
        },

        {
            L_BLOCK,
            TetroColor[L_BLOCK],
            matrixStructure_L,
            3, 2,
            xTetradsInit, yTetradsInit+1
        },

        {
            J_BLOCK,
            TetroColor[J_BLOCK],
            matrixStructure_J,
            3, 2,
            xTetradsInit, yTetradsInit+1
        },

        {
            O_BLOCK,
            TetroColor[O_BLOCK],
            matrixStructure_O,
            2, 2,
            xTetradsInit+1, yTetradsInit+1
        },

        {
            S_BLOCK,
            TetroColor[S_BLOCK],
            matrixStructure_S,
            3, 2,
            xTetradsInit, yTetradsInit+1
        },

        {
            T_BLOCK,
            TetroColor[T_BLOCK],
            matrixStructure_T,
            3, 2,
            xTetradsInit, yTetradsInit+1
        },

        {
            Z_BLOCK,
            TetroColor[Z_BLOCK],
            matrixStructure_Z,
            3, 2,
            xTetradsInit, yTetradsInit+1
        }
    };

Tetromino* getRandomTetrads();


#endif