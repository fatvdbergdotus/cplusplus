# Personal C++ projects

## Sokoban Solver
This C++ program implements a solver for a Sokoban-style puzzle using an A* search algorithm. It represents the game state with the player and box positions, parses a level from a string grid, and searches for a sequence of moves that places all boxes on goal tiles. The solver uses a priority queue guided by a heuristic (sum of Manhattan distances from boxes to goals), tracks visited states with hashing, and reconstructs the solution path once a goal state is reached. It also includes optimizations such as reachability checks (to see where the player can move), deadlock detection (to avoid unsolvable states like boxes stuck in corners), and metrics reporting (expanded/generated states). The main function runs the solver on a sample level and prints each step of the solution if found.

See [Solution](sokoban/ConsoleApplication1) for the C++ files.
