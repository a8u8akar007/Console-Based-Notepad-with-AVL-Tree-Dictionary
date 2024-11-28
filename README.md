# **AVL Tree-Based Notepad with Spell Checker**

## **Project Overview**
This project implements a console-based notepad application that features a spell checker powered by an AVL tree. The notepad allows users to type and edit text, check spelling, load and save text from a file, and edit the text interactively. The spell checker matches user-typed words against an AVL tree dictionary and suggests corrections using various techniques like letter substitution, omission, insertion, and reversal if a word is misspelled.

## **Key Features**
1. **AVL Tree Dictionary**:
   - **Balanced Storage**: The AVL tree automatically balances itself when words are inserted, ensuring efficient search, insert, and delete operations in O(log n) time.
   - **Efficient Searching**: Fast word lookups, as the dictionary is stored in an AVL tree, preventing degeneration and ensuring balanced search times.

2. **Console-Based Notepad**:
   - **Dynamic Text Editing**: Users can type text where each letter is stored as an individual node in a linked list. The screen is updated dynamically as text is entered.
   - **Text Deletion**: Implemented using the Backspace key to remove the last typed letter.
   - **Text Saving and Loading**: Users can load text from a file using **Ctrl + L** and save the current text to a file named `save.txt` using **Ctrl + S**.
   - **Quit Functionality**: The **Esc** key allows the user to quit the application, releasing all allocated memory.

3. **Word Tracking and Spell Checking**:
   - **Real-Time Spell Checking**: As the user types, words are formed and checked against the AVL tree dictionary. If the word is misspelled, suggestions are made based on common spelling modification techniques.
   - **Spell-Check Modification Techniques**:
     - **Letter Substitution**: Replaces each character with other characters and checks the new word in the dictionary.
     - **Letter Omission**: Omits one character at a time from the word and checks the new word in the dictionary.
     - **Letter Insertion**: Inserts a character at various positions in the word and checks the new word in the dictionary.
     - **Letter Reversal**: Swaps adjacent characters in the word and checks the new word in the dictionary.

## **How the Notepad Works**
### **Text Addition**:
- Each letter typed by the user is stored as an individual node in a linked list.
- The screen is cleared and the updated text is displayed after each input.

### **Text Deletion**:
- The **Backspace** key is used to delete the last letter typed. The text is updated dynamically as each letter is removed.

### **Spell Checking**:
- When a space is pressed, the last typed word is checked against the AVL tree dictionary.
- If the word is misspelled, the program provides suggestions based on the following techniques:
  1. **Letter Substitution**: Replaces each character with every possible letter and checks the dictionary.
  2. **Letter Omission**: Tries to remove each character one by one and checks the dictionary.
  3. **Letter Insertion**: Attempts to insert every letter in every position of the word.
  4. **Letter Reversal**: Swaps adjacent characters in the word and checks for corrections.

### **Special Shortcuts**:
- **Ctrl + L**: Load text from a file into the notepad.
- **Ctrl + S**: Save the current text to a file named `save.txt`.
- **Esc**: Quit the application and release memory.

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


