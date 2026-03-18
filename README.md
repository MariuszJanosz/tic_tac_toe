## Tic Tac Toe

Simple Tic Tac Toe implementation.

### To build it requires:
1. C compiler supporting at least C11
2. CMake version 3.14 or higher
3. Python 3.x

### Build: (Tested with Ubuntu24.04 + GCC, Windows11 + MSVC)
```
cmake -B build
cmake --build build [--config <config>]
```

### Install:
```
#If you build to system location, you have to run this command with elevated privilege.
cmake --install build [--config <config>] [--prefix <prefix>]
```

If you start executable with no arguments it would start in GUI mode.
If you pass --cli it will start in terminal mode.

### Control:
1. GUI mode:
    * Click buttons with the LMB.
    * Press "q" to quit at any time.
2. Terminal mode:
    * Follow instructions in menus.
    * Numbers map to board cells in the following way:
    ```
    #####
    #123#
    #456#
    #789#
    #####
    ```

