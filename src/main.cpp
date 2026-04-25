#include <Arduino.h>
#include <TFT_eSPI.h>
#include "chess.h"
TFT_eSPI tft = TFT_eSPI(); // Invoke library, pins defined in User_Setup.h
chess_game_t game;

void drawBoard()
{
 
    int squareSize = 30; // Size of each square on the chessboard
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            int x = col * squareSize;
            int y = row * squareSize;
            if ((row + col) % 2 == 0) {
                tft.fillRect(x, y, squareSize, squareSize, TFT_WHITE); // Light square
            } else {
                tft.fillRect(x, y, squareSize, squareSize, TFT_BLACK); // Dark square
            }
        }
    }
}

void drawPieces()
{
    int squareSize = 30; // Size of each square on the chessboard

    for (int i = 0; i < 64; i++) {
        chess_id_t id = game.board[i];
        if (id != CHESS_NONE) {
            int row = i / 8;
            int col = i % 8;
            int x = col * squareSize + 8;
            int y = row * squareSize + 6;
            char symbol = '?';
            switch (CHESS_TYPE(id)) {
                case CHESS_PAWN:
                    symbol = 'P';
                    break;
                case CHESS_KNIGHT:
                    symbol = 'N';
                    break;    
                case CHESS_BISHOP:
                    symbol = 'B';
                    break;
                case CHESS_ROOK:
                    symbol = 'R';
                    break;
                case CHESS_QUEEN:
                    symbol = 'Q';
                    break;
                case CHESS_KING:
                    symbol = 'K';
                    break;  
            }
            if(CHESS_TEAM(id) == CHESS_WHITE)
            {
                tft.setTextColor(TFT_BLUE);
            }
            else
            {
                tft.setTextColor(TFT_RED);
            }
            tft.drawChar(symbol, x, y, 2);
        }
    }
}

void drawCursor()
{
    int squareSize = 30; // Size of each square on the chessboard
    int x = cursorX * squareSize;
    int y = cursorY * squareSize;
    tft.drawRect(x, y, squareSize, squareSize, TFT_GREEN);

    if(pieceSelected)
    {
        tft.drawRect(x + 2, y + 2, squareSize - 4, squareSize - 4, TFT_YELLOW);
    }
}

void printBoardState()
{
    Serial.println(" Current Board State:");
    for (int i = 0;i <64;i++) {
        Serial.print(game.board[i]);
        Serial.print(" ");
        if ((i + 1) % 8 == 0) {
            Serial.println();
        }
    }
}

int cursorX = 0;
int cursorY = 0;
bool pieceSelected = false;

void setup() {
    Serial.begin(115200);

    chess_init(&game);

    Serial.println("Chess initialized!");

    chess_index_t from = 12;
    chess_index_t to = 28;

    chess_index_t result = chess_move(&game, from, to);

    if(result == -2){
        Serial.println("Invalid move!");
    }
    else{
        Serial.println("Pawn moved successfully!");
    }
    
    printBoardState();

    tft.init();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);

    drawBoard();
    drawPieces();
    drawCursor();
}

void loop()
{
    delay(1000);

    cursorX++;
    if(cursorX >= 8)    {
        cursorX = 0;
    }
        cursorY++;
        if(cursorY >= 8) {
            cursorY = 0;    
        }

        tft.fillScreen(TFT_BLACK);
        drawBoard();
        drawPieces();
        drawCursor();
}
