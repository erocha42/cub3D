*This project has been created as part of the 42 curriculum by mchesnea and erocha--.*

# cub3D (Nextbots Edition)

![Norminette](https://img.shields.io/badge/norminette-passing-success?style=flat-square) ![Score](https://img.shields.io/badge/score-...%2F100-brightgreen?style=flat-square) ![Language](https://img.shields.io/badge/language-C-blue?style=flat-square)

![cub3D Preview](https://github.com/user-attachments/assets/07853942-57dc-4631-ba8c-69a80e4f25a2)

## Description

The goal of this project is to create a 2.5D graphic rendering engine inspired by the famous *Wolfenstein 3D*. It simulates a first-person perspective inside a maze using the **Raycasting** technique. This special "Nextbots" version transforms the project into a survival game where 2D entities relentlessly track you down within a fully textured environment.

The mathematical core relies on the **DDA** (Digital Differential Analysis) algorithm to calculate the precise distance between the player and the walls:

$$dist = \sqrt{(x_2 - x_1)^2 + (y_2 - y_1)^2}$$

Key concepts learned include:
* **Graphic programming**: Manipulating pixels and rendering frames smoothly using MiniLibX.
* **Raycasting**: Projecting rays to calculate wall visibility and dynamic heights.
* **Texture mapping**: Applying images onto vertical surfaces based on wall orientation (North, South, East, West).
* **Sprite system**: Implementing "Nextbots" (animated 2D images that constantly face the player).
* **Game engine**: Managing collision detection, player velocity, and camera rotation.

**Bonus features:**
* **Nextbots AI**: Dynamic entities chasing the player through the map.
* **Minimap**: A real-time top-down view tracking level layout and incoming dangers.
* **Doors**: Ability to open and close secret passages or standard doors.
* **Mouse Control**: Smooth camera rotation using the mouse (look around).
* **Ceiling and FlashLight**: Textured ceilings and FlashLight for better immersion.
* **Sprint**: Speed bursts to escape enemies.
* **Music**: Add song and jumpscare for atmosphere.

## Instructions

### Compilation

You can compile the project using the provided Makefile.

**For the mandatory part:**
```bash
make
```

**For the bonus part (includes zoom, colors, rotations, etc.):**
```bash
make bonus
```
## Usage

*To run the program, provide a .cub configuration map file as an argument:*
```bash
./cub3d resources/maps/map.cub
```

### Controls

| Key / Action | Effect |
| :--- | :--- |
| **`ESC`** | Close the window and quit |
| **`Arrow Keys (Right & Left)`** | Rotate camera (Keyboard)|
| **`Mouse`** | Rotate camera (Mouse look) |
| **`W` / `S`** | Rotate around X axis |
| **`A` / `D`** | Rotate around Z axis |
| **`E`** | Interact (Open/close doors) |
| **`R`** | FlashLight (Active/Disable Flash) |
| **`Left Shift`** | Sprint (Evade Nextbots) |

## Resources

### Resources

* **Lode's Raycasting Tutorial**: The primary reference for understanding the DDA algorithm and texture mapping mathematics.
* **Wolfenstein 3D (1992)**: The classic reference for 2.5D rendering styles and early FPS mechanics.
* **42 Docs / MiniLibX**: Official technical documentation for window management and pixel manipulation.

### AI Usage

* **Documentation**: Structuring and translating the project documentation to meet 42 standards.
* **Problem Solving**: Identifying and debugging issues within event handling and ensuring memory management remained leak-free.
