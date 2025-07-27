# Death's Edge

A C++ RPG game developed using SFML (Simple and Fast Multimedia Library). Death's Edge is a turn-based combat game featuring exploration, character progression, and various enemies to battle.

## 🎮 Game Features

- **Turn-based Combat System**: Engage in strategic battles with various enemies including Goblins, Skeletons, Pink Slimes, and powerful bosses
- **Character Progression**: Level up your character and improve stats
- **Map Exploration**: Navigate through procedurally generated maps
- **Inventory System**: Manage items including health potions
- **Multiple Enemy Types**: Face different enemies with unique stats and abilities
- **Boss Battles**: Challenge powerful bosses like Bruce and Maybelline

## 📋 Prerequisites

Before building and running Death's Edge, ensure you have the following installed:

### Required Software
- **Visual Studio 2022** (with C++ development tools)
  - MSVC v143 compiler toolset
  - Windows 10/11 SDK
- **Git** (for cloning the repository)

### System Requirements
- **Operating System**: Windows 10 or later
- **Architecture**: x64 or x86
- **Memory**: At least 4GB RAM
- **Graphics**: DirectX compatible graphics card

## 🛠️ Installation & Setup

### 1. Clone the Repository
```bash
git clone https://github.com/username/Deaths_Edge.git
cd Deaths_Edge
```

### 2. SFML Dependencies
The project includes SFML 3.0 libraries in the `External` folder:
- **Include files**: `External/include/SFML/`
- **Library files**: `External/lib/`
- **DLL files**: `External/bin/`

No additional SFML installation is required as all dependencies are included.

### 3. Open the Project
1. Navigate to the project directory
2. Open `Death's_Edge.sln` in Visual Studio 2022
3. The solution will load with the main project

## 🏗️ Building the Project

### Debug Build
1. In Visual Studio, select **Debug** configuration
2. Choose your target platform (**x64** recommended)
3. Build the solution:
   - **Menu**: Build → Build Solution
   - **Shortcut**: `Ctrl + Shift + B`

### Release Build
1. In Visual Studio, select **Release** configuration
2. Choose your target platform (**x64** recommended)
3. Build the solution

### Build Configurations
- **Debug|Win32**: 32-bit debug build
- **Release|Win32**: 32-bit release build
- **Debug|x64**: 64-bit debug build (recommended)
- **Release|x64**: 64-bit release build (recommended)

## 🚀 Running the Game

### Method 1: From Visual Studio
1. Ensure the project is built successfully
2. Press `F5` (Start Debugging) or `Ctrl + F5` (Start Without Debugging)

### Method 2: From File Explorer
1. Navigate to `x64/Debug/` (or `x64/Release/` for release builds)
2. Double-click `Death's_Edge.exe`

### Method 3: From Command Line
```bash
cd "x64/Debug"
./Death's_Edge.exe
```

## 🎯 Game Controls

- **Movement**: Arrow keys or WASD
- **Combat**: Follow on-screen prompts for turn-based combat
- **Inventory**: Access through the game interface
- **Exit**: Press `Escape` key or close the window

## 📁 Project Structure

```
Death's_Edge/
├── Death's_Edge.sln              # Visual Studio solution file
├── Death's_Edge/                 # Main project folder
│   ├── Source Files/
│   │   ├── main.cpp              # Entry point
│   │   ├── Game.cpp              # Main game logic
│   │   ├── Player.cpp            # Player character implementation
│   │   ├── Enemy.cpp             # Enemy system
│   │   ├── CombatManager.cpp     # Combat system
│   │   ├── MapGenerator.cpp      # Map generation
│   │   └── ...                   # Other source files
│   ├── Header Files/
│   │   ├── Game.hpp
│   │   ├── Player.hpp
│   │   └── ...                   # Header files
│   ├── Fonts/                    # Game fonts
│   ├── Sprites/                  # Game graphics
│   │   ├── Entities/            # Character and enemy sprites
│   │   └── Maps/                # Map tiles and graphics
│   └── *.dll                    # SFML runtime libraries
├── External/                     # SFML dependencies
│   ├── include/                 # SFML header files
│   ├── lib/                     # SFML library files
│   └── bin/                     # SFML DLL files
└── x64/                         # Build output
    ├── Debug/                   # Debug build output
    └── Release/                 # Release build output
```

## 🔧 Troubleshooting

### Common Issues

#### 1. "SFML DLLs not found" Error
**Solution**: Ensure the SFML DLL files are in the same directory as the executable:
- Copy DLLs from `Death's_Edge/` folder to `x64/Debug/` or `x64/Release/`
- Or run the game from the `Death's_Edge/` folder where DLLs are located

#### 2. Build Errors
**Solution**: 
- Ensure Visual Studio 2022 is installed with C++ development tools
- Verify Windows SDK is installed
- Clean and rebuild the solution (Build → Clean Solution, then Build → Rebuild Solution)

#### 3. Missing Assets
**Solution**: Ensure the following folders exist relative to the executable:
- `Fonts/` (contains trebuc.ttf)
- `Sprites/Entities/` (contains character sprites)
- `Sprites/Maps/` (contains map graphics)

#### 4. Performance Issues
**Solution**: 
- Use Release build for better performance
- Ensure graphics drivers are up to date
- Close unnecessary background applications

### Debug Mode
If you encounter issues, run in Debug mode for detailed error information:
1. Select Debug configuration
2. Press `F5` to start debugging
3. Check the Output window for error messages

## 🤝 Contributing

If you'd like to contribute to Death's Edge:

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Test thoroughly
5. Submit a pull request

## 📄 License

[Add your license information here]

## 📞 Support

If you encounter any issues or have questions:
- Check the troubleshooting section above
- Review the Visual Studio output for error messages
- Ensure all prerequisites are installed correctly

## 🎮 Enjoy the Game!

Embark on your adventure in Death's Edge and face the challenges that await. Good luck, adventurer!
