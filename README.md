# RaylibCaster

RaylibCaster is a simple raycasting engine built using the Raylib library. This project demonstrates basic raycasting techniques to render a 3D view from a 2D grid map. The engine includes features such as player movement, 2D and 3D rendering, and simple UI elements like buttons.

## Features

- **2D Grid Map**: A map where each cell represents a wall or empty space.
- **3D Rendering**: A first-person view generated using raycasting.
- **Player Movement**: The player can move forward, backward, and rotate.
- **Simple UI**: Includes buttons and debug information displayed on the screen.

## Installation

1. **Clone the Repository**:
    ```sh
    git clone https://github.com/yourusername/RaylibCaster.git
    cd RaylibCaster
    ```

2. **Install Raylib**:
    Follow the instructions on the [Raylib GitHub repository](https://github.com/raysan5/raylib) to install Raylib for your operating system.

3. **Compile the Project**:
    ```sh
    gcc -o RaylibCaster main.c game.c 2drenderer.c 3drenderer.c button.c -lraylib -lm -ldl -lpthread
    ```

4. **Run the Project**:
    ```sh
    ./RaylibCaster
    ```

## Usage

- **Player Controls**:
    - `W`: Move forward
    - `S`: Move backward
    - `A`: Rotate left
    - `D`: Rotate right

- **Edit Mode**:
    - Click the "Edit" button to toggle edit mode.
    - In edit mode, click on the grid to place walls.

## Code Overview

### main.c

The main entry point of the application. It initializes the window, sets up the game state, and handles the main game loop.

### game.h and game.c

These files define and implement the game state, including player position, map data, and player movement functions.

### 2drenderer.h and 2drenderer.c

These files handle rendering the 2D view of the game, including the grid map, player position, and rays cast from the player's position.

### 3drenderer.h and 3drenderer.c

These files handle rendering the 3D view of the game using raycasting techniques.

### button.h and button.c

These files define and implement simple UI buttons used in the game.

## Contributing

Contributions are welcome! Feel free to open issues or submit pull requests.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Acknowledgements

- Thanks to [Raylib](https://www.raylib.com/) for providing an excellent C library for game development.
- Raycasting algorithm inspiration from [Lode's Computer Graphics Tutorial](https://lodev.org/cgtutor/raycasting.html).
