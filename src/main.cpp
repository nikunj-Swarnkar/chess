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
}
void loop()
{
    // Main game loop
    // Here you would handle user input, update the game state, and redraw the board as needed
}
