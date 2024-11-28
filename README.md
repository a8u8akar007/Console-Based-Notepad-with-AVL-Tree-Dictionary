# Console-Based-Notepad-with-AVL-Tree-Dictionary  

## **Introduction**
The AVL Tree Dictionary is a dynamic and efficient dictionary system built using the principles of AVL Trees, which are self-balancing binary search trees. This project provides core functionalities like word insertion, deletion, and search with optimal time complexity. It integrates file handling to load and save dictionary data and uses the Ncurses library for a user-friendly command-line interface.

This project is ideal for understanding AVL Trees' practical applications and demonstrates the use of advanced data structures to solve real-world problems.

---

## **Key Features**
1. **AVL Tree Integration**:
   - Automatically balances itself during insertions and deletions for efficient operations.
   - Ensures operations like search, insertion, and deletion are performed in O(log n) time.

2. **Core Dictionary Functions**:
   - **Insert Words**: Add new words to the dictionary dynamically.
   - **Delete Words**: Remove unwanted words while maintaining tree balance.
   - **Search Words**: Quickly locate words with case-insensitive matching.
   - **Display Words**: Print all words in alphabetical order using in-order traversal.

3. **File Handling**:
   - Loads words from `dictionary.txt` into the AVL Tree.
   - Saves updated dictionary data back to the file.

4. **Enhanced User Interface**:
   - Uses the **Ncurses library** for an interactive and intuitive command-line experience.

---

## **Instructions to Run the Code**

### **1. Prerequisites**
- **C++ Compiler**: Ensure you have a C++ compiler installed (e.g., `g++`).
- **Ncurses Library**: Required for the terminal UI.
### **2. Compile the Program**  
- **To compile the project, run:** `g++ -o dictionary main.cpp -lncurses`
### **3.Run The Program**  
- **After compiling, you can run the program with the following command:** `./dictionary`

  To install Ncurses (Linux):
```bash
sudo apt-get install libncurses5-dev libncursesw5-dev


