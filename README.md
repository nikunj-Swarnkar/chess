# Pocket Chess

*A portable handheld chess board built with ESP32-S3*

Pocket Chess is a compact handheld chess console that lets you play chess anywhere without needing a phone, internet connection, or a full-sized board.

Built using an **ESP32-S3 Mini**, a **2" ST7789 TFT display**, physical control buttons, and battery support, this project turns chess into something you can carry in your pocket.

Designed for **Hack Club Stasis**.

---

# Project Renders

## Front Render

![Front Render](docs/front_render.png)

## Back Render

![Back Render](docs/back_render.png)

## Internal Layout

![Internal Layout](docs/internal_layout.png)

## Prototype

![Prototype](docs/prototype.jpg)

---

# Final Assembly

The Pocket Chess console is assembled inside a compact 3D printed enclosure designed for portability and comfortable handheld gameplay.

The ESP32-S3 controls the display, handles chess logic, reads button input, and manages save data storage.

The device is powered using a rechargeable LiPo battery with onboard charging support.

## Final Device Features

- Portable handheld design
- Battery powered
- Instant boot into chess
- Physical button controls
- Save/load support
- Compact travel-friendly size

### Assembled Device

![Assembly Front](docs/assembly_front.jpg)

![Assembly Back](docs/assembly_back.jpg)

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

# Hardware Used

- **ESP32-S3 Mini**
- **2" ST7789 SPI TFT Display (240x320)**
- Push buttons for navigation/input
- LiPo battery
- Battery charging module
- Power switch
- Jumper wires / custom PCB
- 3D printed enclosure

---

# Bill of Materials

| Part | Purpose | Quantity | Cost (USD) |
|------|------|------|------|
| ZY-201 830 Points Solderless Breadboard | Breadboard for testing parts | 1 | $5.67 |
| M3 Allen Button Head SS304 Assorted Box | Screws | 1 | $2.55 |
| XY-016 2A DC-DC Step Up Power Module | Voltage controller | 1 | $0.39 |
| Waveshare ESP32-S3 Mini Development Board | Main microcontroller | 1 | $6.80 |
| Tactile Push Button Switch 6x6x5 | Controls / Input buttons | 1 Pack | $0.14 |
| WLY103048 3.7V 1500mAh 1S LiPo Battery | Battery power | 1 | $2.90 |
| SS-A0322SG-9R2BB-XKB Slide Switch | Power switch | 1 | $0.21 |
| SmartElex TP4056 Li-ion Battery Charger Module | Charging board | 1 | $1.60 |
| GoldenMorning ST7789V 2.0" 240x320 SPI TFT Display | Display | 1 | $8.30 |

## Total Estimated Cost

**~$28.56 USD**

---

# Wiring Diagram

The following diagram shows the wiring connections between the ESP32-S3, TFT display, buttons, and power system.

![Wiring Diagram](docs/wiring_diagram.png)

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
│   ├── front_render.png
│   ├── back_render.png
│   ├── internal_layout.png
│   ├── assembly_front.jpg
│   ├── assembly_back.jpg
│
└── README.md
```

---

## Build Your Own

Clone the repository:

```bash
git clone https://github.com/nikunj-Swarnkar/chess.git
```

Upload the code to your ESP32 and start playing.

---

## Credits

Built for Hack Club Stasis.

This project was inspired by:
https://github.com/codewitch-honey-crisis/pocket_chess

---

## License

MIT License
