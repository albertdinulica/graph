# graph
Below is a short documentation that describes the purpose, usage, and architecture of the program:

------------------------------------------------
# Graph Algorithms Program Documentation

## Overview

This C++ program demonstrates several fundamental graph algorithms on an undirected graph. The graph data (vertices and edges) is read from an external text file (`graph.txt`), and the program supports operations such as:

- Detecting connected components using Depth-First Search (DFS)
- Finding the shortest path between two vertices using Breadth-First Search (BFS)
- Constructing a minimal spanning forest (spanning tree per connected component) using Kruskal's algorithm (with all edges assigned a unit weight)
- Finding a matching using a simple, greedy algorithm

## File Structure

- **graph.txt**  
  Contains the graph data. Each line represents a vertex and its adjacent vertices in the following format:  
  `vertex: (neighbor1), (neighbor2), ...`  
  For example:  
  ```
  0: (1), (2), (3)
  1: (0), (2), (4)
  2: (0), (1), (3), (5)
  ...
  ```

- **graph_program.cpp** (or similar naming)  
  Contains the complete C++ source code that implements the graph data structure, algorithms, and a text-based menu for user interaction.

## How It Works

1. **Reading Graph Data:**

   - The program opens `graph.txt` (using a relative or absolute path).
   - It reads each line to both determine the maximum vertex label (thus the total number of vertices) and then to parse the neighbors.
   - Edges are added in an undirected fashion (i.e., for vertex `u` and neighbor `v`, both `u → v` and `v → u` are inserted).

2. **Graph Class:**

   - The `Graph` class encapsulates:
     - An integer `V` representing the number of vertices.
     - An adjacency list `vector<vector<int>> adj`.
   - It provides member functions for:
     - Adding an edge (`addEdge`)
     - Performing DFS to find connected components (`dfsUtil`, `connectedComponents`)
     - Finding the shortest path using BFS (`shortestPath`)
     - Building a minimal spanning forest with Kruskal's algorithm (`minimalSpanningForest`)
     - Computing a greedy matching (`greedyMatching`)

3. **User Interaction:**

   - A menu prompts the user to select one of the following options:
     1. **Connected Components:** Lists all components found in the graph.
     2. **Shortest Path:** Requests two vertices (source and target) and displays the shortest path between them.
     3. **Minimal Spanning Forest:** Displays the edges of the minimal spanning forest.
     4. **Greedy Matching:** Displays a matching computed by a greedy pairing algorithm.
  
4. **Helper Functions:**

   - Several helper functions (like `printVector`, `printEdgeList`, and `printMatching`) are defined as static to provide internal linkage. They help display the algorithm results in the console.

## Usage Instructions

1. **Prepare the Data File:**
   - Ensure that `graph.txt` is in the same directory as the executable or adjust the file path in the source code accordingly.
   - Verify that the file follows the expected formatting.

2. **Compiling the Program:**
   - Use a standards-conforming C++ compiler (e.g., g++ with C++17 support):
     ```
     g++ -std=c++17 -o graph_program graph_program.cpp
     ```
     
3. **Running the Program:**
   - Run the executable. For example:
     ```
     ./graph_program
     ```
   - Follow the on-screen menu instructions.
   - If asked for vertices (e.g., for the shortest path), input valid vertex numbers that exist in your graph.

## Troubleshooting

- **Error Opening File:**  
  Ensure that the file `graph.txt` exists in the program’s working directory, or update the file path in the code.
  
- **Compilation Warnings:**  
  The helper functions are marked as static to avoid linkage warnings. If additional warnings occur, verify that all required headers (especially `<fstream>` and `<functional>`) are included.

## Conclusion

This program is designed as a practical demonstration of basic graph algorithms. Its modular structure makes it a useful starting point for further exploration and extension of graph theory concepts in C++.
------------------------------------------------

This documentation provides a brief yet comprehensive overview for users and developers working with the code.
