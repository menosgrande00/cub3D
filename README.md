*This project has been created as part of the 42 curriculum by oonal, sesimsek.*

# cub3D

## Description

**cub3D** is a project inspired by the world-famous Wolfenstein 3D game, which was the first FPS ever implemented. The goal of this project is to explore raycasting, a rendering technique used to create a 3D perspective from a 2D map.

This project is written in **C** and uses the **MiniLibX** library (the graphical library used by 42 students). It is a significant milestone in the 42 curriculum, testing skills in:
- rigorous memory management.
- window management and event handling.
- mathematics (trigonometry).
- file parsing and validation.

The program takes a map file (`.cub`) as an argument, allowing the user to navigate through a maze with textured walls.

## Instructions

### Compilation

To compile the project, run the following command in the root directory:

```bash
make
```

This will generate the `cub3D` executable.

### Execution

Run the program by providing a valid map file as an argument:

```bash
./cub3D maps/good/subject_map.cub
```

You can find various test maps in the `maps/` directory.

### Controls

| Key | Action |
| :--- | :--- |
| **W** | Move Forward |
| **S** | Move Backward |
| **A** | Move Left (Strafe) |
| **D** | Move Right (Strafe) |
| **←** | Rotate Left |
| **→** | Rotate Right |
| **ESC** | Quit Game |
| **Click X** | Quit Game |

## Resources

### References

Here are the main resources used to understand raycasting and the MiniLibX library:

- [Lodev's Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html) - The bible of raycasting for this project.
- [MinilibX Documentation](https://harm-smits.github.io/42docs/libs/minilibx) - Unofficial but excellent documentation.
- [Wolfenstein 3D Source Code](https://github.com/id-Software/wolf3d) - Historical reference.

### AI Usage

Artificial Intelligence tools were used in the development of this project for the following tasks:

- **Concept Explanation**: Clarifying the mathematical principles of DDA (Digital Differential Analyzer) and fish-eye effect correction.
- **Debugging**: Assisting in identifying memory leaks and segmentation faults during the map parsing phase.
- **Refactoring**: Suggesting cleaner code structures for helper functions in `libft` compatibility.
- **Documentation**: Helping needed to draft this README file to meet specific requirements.

## Features

- [x] Wall collisions.
- [x] Textured walls (North, South, East, West).
- [x] Floor and Ceiling colors (RGB parsing).
- [x] Correct movement and rotation handling.
- [x] Comprehensive map validation (closed maps, valid characters, etc.).
