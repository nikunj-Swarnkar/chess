# Pocket Chess

*A portable handheld chess board built with ESP32-S3*

Pocket Chess is a compact handheld chess console that lets you play chess anywhere without needing a phone, internet connection, or a full-sized board.

Built using an **ESP32-S3 Mini**, a **2" ST7789 TFT display**, physical control buttons, and battery support, this project turns chess into something you can carry in your pocket.

Designed for **Hack Club Stasis**.

---

## Features

- Play full chess games on a handheld device  
- Physical button controls  
- Portable battery-powered design  
- Save/load game state  
- Built-in chess piece rendering  
- Compact form factor  
- Instant boot into game  
- No phone required  

---

## Hardware Used

- **ESP32-S3 Mini**
- **2" ST7789 SPI TFT Display (240x320)**
- Push buttons for navigation/input
- LiPo battery
- Battery charging module
- Power switch
- Jumper wires / custom PCB
- 3D printed enclosure

---

## Controls

| Button | Function |
|---------|-----------|
| Up | Move cursor up |
| Down | Move cursor down |
| Left | Move cursor left |
| Right | Move cursor right |
| Select | Pick piece / confirm move |
| Back *(optional)* | Cancel selection |

---

## How It Works

The ESP32 runs the chess game logic and displays the board on the TFT screen.

### Flow

1. Boot device  
2. Load previous save (if available)  
3. Display chess board  
4. Navigate using physical buttons  
5. Select a piece  
6. Make a move  
7. Save progress automatically  

---

## Software Stack

- C++
- Arduino IDE / PlatformIO
- TFT_eSPI library
- ESP32 Preferences library
- Custom chess logic

---

## Challenges

Some of the major challenges during development included:

- Display driver configuration  
- Button wiring and debugging  
- Managing game save data  
- Battery integration  
- Optimizing the interface for a small screen  
- Making chess pieces readable on a compact display  

---

## Future Improvements

- Bluetooth multiplayer  
- AI opponent  
- Custom PCB  
- USB-C charging  
- Better animations  
- E-paper display version  

---

## Why I Built This

I wanted to build something that felt like a complete hardware product instead of a simple beginner electronics project.

Chess is timeless, but traditional boards are not very portable. This project combines embedded systems, hardware design, and game development into a functional handheld device.

---

## Repository Structure

```bash
Pocket-Chess/
│
├── src/
│   ├── main.cpp
│   ├── chess_logic.cpp
│   ├── display.cpp
│
├── assets/
│   ├── chess_sprites/
│
├── docs/
│   ├── wiring_diagram.png
│
└── README.md
```

---

## Build Your Own

Clone the repository:

```bash
git clone https://github.com/yourusername/pocket-chess.git
```

Upload the code to your ESP32 and start playing.

---

## Credits

Built for Hack Club Stasis.

---

## License

MIT License
