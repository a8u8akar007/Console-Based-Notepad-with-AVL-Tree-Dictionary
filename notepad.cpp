#include <iostream>
#include <fstream>
#include <ncurses.h>
using namespace std;

struct Node 
{
    string word;
    Node* left;
    Node* right;
    int height;

    Node(string word) 
    {
        this->word = word;
        left = right = nullptr;
        height = 1; 
    }
};


class Dict_AVL 
{

private:
    Node* root;

    int height(Node* node) 
    {
        if(node == nullptr)
            return 0;
        
        return node->height;
    }

    int get_balance(Node* node) 
    {
        if(node == nullptr)
            return 0;
        
        return (height(node->left) - height(node->right));
    }

    void update_height(Node* node) 
    {
        if (node != nullptr) 
        {
            node->height = 1 + max(height(node->left), height(node->right));
        }
    }

    Node* right_rotate(Node* y) 
    {
        Node* temp = y->left;
        Node* temp2 = temp->right;

        temp->right = y;
        y->left = temp2;

        update_height(y);
        update_height(temp);

        return temp;
    }

    Node* left_rotate(Node* y) 
    {
        Node* temp = y->right;
        Node* T2 = temp->left;

        temp->left = y;
        y->right = T2;

        update_height(y);
        update_height(temp);

        return temp;
    }

    Node* right_left_rotate(Node* node) 
    {
        node->right = right_rotate(node->right);
        return left_rotate(node);
    }

    Node* left_right_rotate(Node* node) 
    {
        node->left = left_rotate(node->left);
        return right_rotate(node);
    }

    Node* insert(Node* node, string word) 
    {
        if (node == nullptr)
        {
            return new Node(word);
        }

        if (word < node->word)
        {
            node->left = insert(node->left, word);
        }
        
        else if (word > node->word)
        {
            node->right = insert(node->right, word);
        }
        
        else
            return node;

        update_height(node);

        int balance = get_balance(node);

        if (balance > 1 && word < node->left->word)
        {
            return right_rotate(node);
        }
        
        if (balance < -1 && word > node->right->word)
        { 
            return left_rotate(node);
        }
        
        if (balance > 1 && word > node->left->word)
        {
            return left_right_rotate(node);
        }

        if (balance < -1 && word < node->right->word)
        {
            return right_left_rotate(node);
        }

        return node;
    }

    Node* search(Node* root, string key) 
    {
        if (root == nullptr) 
        {
            return root;
        }

        if (root->word == key) 
        {
            return root;
        }

        if (key < root->word) 
        {
            return search(root->left, key);
        } 
        else 
        {
            return search(root->right, key);
        }
    }

    void inorder_display(Node* root) 
    {
        if (root == nullptr)
            return;

        inorder_display(root->left);
        cout << root->word << endl;
        inorder_display(root->right);
    }

    string to_lowercase(const string& str) 
    {
        string lower_str = str;

        for (size_t i = 0; i < lower_str.size(); ++i) 
        {

            if (lower_str[i] >= 'A' && lower_str[i] <= 'Z') 
            {
                lower_str[i] = lower_str[i] - 'A' + 'a';
            }
        
        }
        return lower_str;
    }

public:
    Dict_AVL() 
    {
        root = nullptr;
    }

    void insert(string word) 
    {
        word = to_lowercase(word);
        root = insert(root, word);
    }

    bool search_word(string word) 
    {
        word = to_lowercase(word);
        Node* temp = search(root, word);
        
        if (temp == nullptr) 
        {
            return false;
        }
        
        return true;
    }

    void inorder_display() 
    {
        inorder_display(root);
    }

    void read_file() 
    {
        string word;
        ifstream file("dictionary.txt");

        if (!file.is_open()) 
        {
            return;
        }

        while (getline(file, word)) 
        {
            word.erase(0, word.find_first_not_of(" \t\n\r\f\v")); 
            word.erase(word.find_last_not_of(" \t\n\r\f\v") + 1); 
            insert(word);
        }

        file.close();
    }

    string letter_substitution(string word)
    {
        string temp = word;

        for (int i = 0; i < word.size(); i++)
        {
            for (int j = 0; j < 26; j++)
            {
                temp[i] = 'a' + j;
                if (search_word(temp))
                {
                    return temp;
                }
            }
            temp = word;
        }
        return word;        
    }

    string letter_ommision(string word)
    {
        string temp = "";
        
        for (int i = 0; i < word.size(); i++)
        {
            temp = word.substr(0, i) + word.substr(i + 1);

            if (search_word(temp))
            {
                return temp;  
            }
        }

        return word;  
    }

    string letter_insertion(string word)
    {
        string temp ="";

        for(int i=0; i<26; i++)
        {
            char c = 'a' + i;
            for(int j=0; j<=word.size(); j++)
            {
                if(j==0)
                {
                    temp = c + word; 
                }

                else if(j == word.size())
                {
                    temp = word;
                    temp += c; 
                }

                else 
                {
                    temp = word.substr(0, j+1) + c + word.substr(j + 1);
                }

                if(search_word(temp))
                    return temp;

            }
            temp = "";
        }

        return word; 
    }

    string letter_reversal(string word)
    {
        string temp = word;
        for(int i=0; i<word.size()-1; i++)
        {
            char c = temp[i+1];
            temp[i+1] = temp[i];
            temp[i] =  c;

            if(search_word(temp))
                return temp;
         
            temp = word;
        }

        return word;   
    }



};


struct char_node 
{
    char data;
    char_node* next;
    char_node* prev;

    char_node(char data) 
    {
        this->data = data;
        next = nullptr;
        prev = nullptr;
    }
};

class stack 
{
private:
    char_node* top;

public:
    stack() 
    {
        top = nullptr;
    }

    void push(char data) 
    {
        char_node* new_node = new char_node(data);
        new_node->next = top;
        top = new_node;
    }

    char pop() 
    {
        if (top == nullptr)
            return '\0';

        char_node* temp = top;
        char data = temp->data;
        top = top->next;
        delete temp;
        return data;
    }

    bool is_empty() 
    {
        return top == nullptr;
    }

    string make_word() 
    {
        string word = "";
        while (top != nullptr) 
        {
            word = pop() + word;
        }
        return word;
    }
};


class linklist 
{
private:
    char_node* head;
    char_node* tail;

public:
    linklist() 
    {
        head = nullptr;
        tail = nullptr;
    }

    void insert(char data) 
    {
        char_node* new_node = new char_node(data);
        if (head == nullptr) 
        {
            head = tail = new_node; 
        } 
        else 
        { 
            tail->next = new_node;
            new_node->prev = tail;
            tail = new_node; 
        }
    }

    void insert_word_after_modification(string word, stack& Stack)
    {
        char_node* temp = tail;
        int i = 0;

        while (temp != nullptr && temp->data != ' ' ) 
        {
            delete_node(Stack);
            temp = temp->prev;
        }

        for(int i=0; i<word.size(); i++)
        {
            insert(word[i]);
        }
    }

    void delete_node(stack& Stack) 
    {
        if (tail == nullptr) 
        {
            if (!Stack.is_empty()) 
            {
                Stack.pop();
            }
            return;
        }

        char_node* temp = tail;
        if (tail == head) 
        {
            head = tail = nullptr;
        } 
        else 
        {
            tail = tail->prev;
            tail->next = nullptr;
        }

        delete temp;

        if (!Stack.is_empty()) 
        {
            Stack.pop();
        }
    }

    void write_file() 
    {
        ofstream file("save.txt");
        if (file.is_open()) 
        {
            char_node* temp = head;
            while (temp != nullptr) 
            {
                file << temp->data;
                temp = temp->next;
            }
            file.close();
        }
    }

    void load_file()
    {
        char_node* node = tail;

        while (node != nullptr)
        {
            char_node* temp = node->prev; 
            delete node;             
            node = temp;                     
        }

        ifstream file("save.txt");
        if (file.is_open()) 
        {
            string word;
            while (getline(file, word)) 
            {
                word.erase(0, word.find_first_not_of(" \t\n\r\f\v")); 
                word.erase(word.find_last_not_of(" \t\n\r\f\v") + 1); 
                for(int i=0; i<word.size(); i++)
                {
                    insert(word[i]);
                }
            }
            file.close();
        }
    }


    void display(WINDOW* win) 
    {
        wclear(win);
        char_node* temp = head;
        int x = 0, y = 0;


        while (temp != nullptr) 
        {
            mvwaddch(win, y, x, temp->data);

            x++;
            if (x >= COLS) 
            {
                x = 0;
                y++;
            }

            temp = temp->next;
        }

        wrefresh(win);
    }
};



int main() 
{
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();

    linklist notepad;
    stack Stack;
    Dict_AVL dict;

    int ch;
    dict.read_file();

    refresh();


    while (true) 
    {
        ch = getch();

        if (ch == 27) 
        { 
            break;
        } 
        else if (ch == KEY_BACKSPACE || ch == 127) 
        { 
            notepad.delete_node(Stack);
        }
        else if (ch == 12) 
        { 
            notepad.load_file();
        }
        else if (ch == 19) 
        { 
            notepad.write_file();
        } 
        else if (ch == 32) 
        {

            string word = Stack.make_word();
            
            if (!dict.search_word(word) && word.size() > 0)
            {
                string new_word = "";

                new_word = dict.letter_substitution(word);
                if (new_word != word)  
                {
                    word = new_word; 
                }
                else
                {
                    new_word = dict.letter_ommision(word);
                    if (new_word != word) 
                    {
                        word = new_word;  
                    }
                    else
                    {
                        new_word = dict.letter_insertion(word);
                        if (new_word != word)
                        {
                            word = new_word;
                        }
                        else
                        {
                            new_word = dict.letter_reversal(word);
                            if (new_word != word)
                            {
                                word = new_word;
                            }
                        }
                    }
                }
                
                notepad.insert_word_after_modification(word, Stack);
            }

            notepad.insert(static_cast<char>(ch));
        }
 
        else if (ch >= 32 && ch <= 126) 
        { 
            notepad.insert(static_cast<char>(ch));
            Stack.push(static_cast<char>(ch));
        }

        notepad.display(stdscr);
    }


    endwin();
    return 0;
}
