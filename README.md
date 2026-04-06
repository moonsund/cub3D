*This project has been created as part of the 42 curriculum by `lorlov` and `asharafe`.*

## Description
This project is a 3D graphical representation of a maze from a first-person perspective, inspired by the legendary Wolfenstein 3D. The core of the project is the implementation of a ray-casting engine using the MiniLibX library to create a dynamic and fluid view of a maze. The program handles wall textures based on orientation (North, South, East, West) and allows for customizable floor and ceiling colors.

## Instructions

### Compilation
The project includes a Makefile with all mandatory rules. To compile the program, run the following command in your terminal:
`make`

This will produce the `cub3D` executable.

### Usage
To start the game, provide a map file with the `.cub` extension as an argument:
./cub3D maps/subject_map.cub

### Controls
* **Movement**: Use the `W`, `A`, `S`, and `D` keys to navigate the maze.
* **Camera**: Use the `Left` and `Right` arrow keys to rotate your view.
* **Exit**: Press the `ESC` key or click the red cross on the window frame to close the program cleanly.

## Resources

### References
* **Lode's Raycasting Tutorial**: Used as a primary guide for implementing the DDA algorithm and mathematical principles of ray-casting.
* **MiniLibX Documentation**: Essential for handling window events, pixel manipulation, and image rendering.

### AI Usage
As required by the 42 curriculum guidelines:
* **Research**: AI helped in research and understandings of the concepts.
* **Documentation**: AI helped in drafting this README.md to ensure it meets all technical requirements of the subject.

