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

void setup()
{
    Serial.begin(115200);

    chess_init(&game);
    tft.init();
    tft.setRotation(1); // Set the display rotation if needed
    tft.fillScreen(TFT_BLACK); // Clear the screen
    drawBoard(); // Draw the chessboard
    Serial.println("Chess game initialized and started!.");
}

void loop()
{
    // Main game loop
    // Here you would handle user input, update the game state, and redraw the board as needed
}
