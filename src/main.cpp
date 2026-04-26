#include <Arduino.h>
#include <TFT_eSPI.h>
#include "chess.h"
TFT_eSPI tft = TFT_eSPI(); // Invoke library, pins defined in User_Setup.h
chess_game_t game;
int cursorX = 0;
int cursorY = 0;

bool pieceSelected = false;
chess_index_t validmoves[64];
size_t validmovecount=0;
int selectedIndex = -1;
const int BTN_UP = 1;
const int BTN_DOWN = 2;
const int BTN_LEFT = 4;
const int BTN_RIGHT = 5;
const int BTN_SELECT = 11;

unsigned long lastButtonPress = 0;
const int debounceDelay = 200;
enum GameState
{
    MENU,
    PLAYING,
    SETTINGS,
    GAME_OVER
};
GameState currentState = MENU;
int menuIndex = 0;
void drawMenu()
{ 
    
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_WHITE);
    tft.drawString("pocket chess:", 50, 50, 4);
    String options[3] = {
        "play",
        "settings",
        "resume"
    };
    

for(int i = 0; i < 3; i++)
{
    if(i == menuIndex)
    {
        tft.setTextColor(TFT_YELLOW);
        tft.drawString("> " + options[i], 40, 120 + (i * 40), 2);
    }
    else
    {
        tft.setTextColor(TFT_WHITE);
        tft.drawString(options[i], 40, 120 + (i * 40), 2);
    }
   
}
}
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

void checkGameStatus()
{
    chess_status_t whiteStatus;
    chess_status_t blackStatus;

    chess_status(&game, &whiteStatus, &blackStatus);

    if(whiteStatus == CHESS_CHECK){
        Serial.println("White is in Check!");
    }
    else if(whiteStatus == CHESS_CHECKMATE){
        Serial.println("White is in Checkmate!");
    }
    else if(whiteStatus == CHESS_STALEMATE){
        Serial.println("White is in Stalemate!");
    }

    if(blackStatus == CHESS_CHECK){
        Serial.println("Black is in Check!");
    }
    else if(blackStatus == CHESS_CHECKMATE){
        Serial.println("Black is in Checkmate!");
    }
    else if(blackStatus == CHESS_STALEMATE){
        Serial.println("Black is in Stalemate!");
    }
}

void drawTurnInfo()
{
    chess_team_t team = chess_turn(&game);

    tft.setTextColor(TFT_WHITE);
    tft.fillRect(0,240,240,80,TFT_DARKGREY);

    if(team == CHESS_WHITE){
        tft.drawString("WHITE TURN",10,260,2);
    }
    else{
        tft.drawString("BLACK TURN",10,260,2);
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

void drawValidMoves()
{
    int squareSize = 30; // Size of each square on the chessboard
    for(size_t i = 0; i < validmovecount; i++)
    {
        chess_index_t moveIndex = validmoves[i];
        int row = moveIndex / 8;
        int col = moveIndex % 8;
        int x = col * squareSize;
        int y = row * squareSize;
        tft.drawCircle(x + squareSize / 2, y + squareSize / 2, 5, TFT_YELLOW);
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



void setup() {
    pinMode(BTN_UP, INPUT_PULLUP);
    pinMode(BTN_DOWN, INPUT_PULLUP);
    pinMode(BTN_LEFT, INPUT_PULLUP);
    pinMode(BTN_RIGHT, INPUT_PULLUP);
    pinMode(BTN_SELECT, INPUT_PULLUP);
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

   drawMenu();
}

void loop()
{
    // ---------------- MENU ----------------
    if(currentState == MENU)
    {
        if(millis() - lastButtonPress > debounceDelay)
        {
            if(digitalRead(BTN_UP) == LOW)
            {
                if(menuIndex > 0)
                {
                    menuIndex--;
                }

                drawMenu();
                lastButtonPress = millis();
            }

            else if(digitalRead(BTN_DOWN) == LOW)
            {
                if(menuIndex < 2)
                {
                    menuIndex++;
                }

                drawMenu();
                lastButtonPress = millis();
            }

            else if(digitalRead(BTN_SELECT) == LOW)
            {
                if(menuIndex == 0)
                {
                    currentState = PLAYING;

                    tft.fillScreen(TFT_BLACK);
                    drawBoard();
                    drawPieces();
                    drawCursor();
                    drawTurnInfo();
                }

                lastButtonPress = millis();
            }
        }

        return;
    }

    // ---------------- GAMEPLAY ----------------
    if(millis() - lastButtonPress > debounceDelay)
    {
        if(digitalRead(BTN_UP) == LOW)
        {
            if(cursorY > 0)
            {
                cursorY--;
            }
        }

        else if(digitalRead(BTN_DOWN) == LOW)
        {
            if(cursorY < 7)
            {
                cursorY++;
            }
        }

        else if(digitalRead(BTN_LEFT) == LOW)
        {
            if(cursorX > 0)
            {
                cursorX--;
            }
        }

        else if(digitalRead(BTN_RIGHT) == LOW)
        {
            if(cursorX < 7)
            {
                cursorX++;
            }
        }

        else if(digitalRead(BTN_SELECT) == LOW)
        {
            int currentIndex = cursorY * 8 + cursorX;

            if(!pieceSelected)
            {
                if(game.board[currentIndex] != CHESS_NONE)
                {
                    selectedIndex = currentIndex;

                    validmovecount = chess_compute_moves(
                        &game,
                        selectedIndex,
                        validmoves
                    );

                    pieceSelected = true;
                    Serial.println("Piece selected");
                }
            }
            else
            {
                bool validTarget = false;

                for(size_t i = 0; i < validmovecount; i++)
                {
                    if(validmoves[i] == currentIndex)
                    {
                        validTarget = true;
                        break;
                    }
                }

                if(validTarget)
                {
                    chess_move(&game, selectedIndex, currentIndex);

                    checkGameStatus();

                    pieceSelected = false;
                    validmovecount = 0;
                    selectedIndex = -1;
                }
                else
                {
                    Serial.println("Invalid move target!");
                }
            }
        }

        lastButtonPress = millis();

        tft.fillScreen(TFT_BLACK);
        drawBoard();
        drawPieces();
        drawValidMoves();
        drawCursor();
        drawTurnInfo();
    }
}