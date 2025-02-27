# Directory Structure

## C/C++

```
├── LICENSE                 - License Agreement of Project.
├── STRUCTURE.md            - Project repositiry structure.
├── README.md               - Project description and guidelines.
├── CMakeLists.txt          - Configuration file for CMake build System.
├── Makefile                - Build Script for compiling and linking the project.
│
├── examples                - Directory containing example usage.
│   │
│   ├── example.c           - Example implemetation file.
│   └── example.c           - Example implementation file.
│
├── include                 - Directory containing header files.
│   │
│   └── project             - Directory containing project header files.
│        │
│        ├── header.h       - header file.
│        └── header.h       - header file.
│
├── src                     - Directory containing project source files.
│   │
│   ├── library.c           - source file.
│   └── library.c           - source file.
│
├── lib                     - Directory containing libraries used by project.
│   │
│   ├── library.a           - library file.
│   └── library.a           - library file.
│
└── tests                   - Directory containing unit test and integration test
    │
    ├── CmakeLists.txt      -  CMake configuration file for tests/directory.
    └── test.c              - Test file for individual.module.
```

## SFML

```
├── LICENSE             - License Agreement of Project.
├── STRUCTURE.md        - Project repositiry structure.
├── README.md           - Project description and guidelines.
├── requirement.txt     - Dependencies required to run the game.
├── setup.py            - Build script for packaging and distrubuting game.
│
├── docs                - Directory containing game documentation.
│   │
│   └── index.rst       - Main documentation file.
│
├── example             - Directory containing example usage.
│   │
│   ├── example.py      - Example Script
│   └── example.py      - Example Script
│
├── project             - Directoty containing the game's source code.
│   │
│   ├── __init__.py     - Initialize the game package.
│   ├── __main__.py     - Entry point of game.
│   └── game.py         - Game logic and loop.
│
├── assets              - Directoty containing game assets.
│   │
│   ├── Images          - Directory containing game image files.
│   │    │
│   │    ├── player.png - image file.
│   │    └── enemy.png  - image file.
│   │
│   ├── Sounds          - Directory containing game audio files.
│   │    │
│   │    ├── jump.wav   - audio file.
│   │    └── explo.wav  - audio file.
│   │
│   └── Fonts           - Directory containing game font files.
│        │
│        ├── arial.ttf  - font file.
│        └── mono.ttf   - font file.
│
└── test                - Directory containing unit test and integration test
    │
    ├── __init__.py     - Initialize the test package.
    └── test.py         - Test file for individaul module.
```
