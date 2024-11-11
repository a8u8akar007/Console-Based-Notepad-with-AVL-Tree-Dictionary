#include<iostream>
#include<fstream>
#include<ncurses.h>
using namespace std;

struct Node
{
    string word;
    Node *left;
    Node *right;
    int height;

    Node() { }

    Node(string word)
    {
        this->word = word;
        left = right = NULL;
        height = 1;
    }
};

class Dict_AVL
{
    private:

        Node* root;

        Dict_AVL(Node* root)
        {
            this->root = root;
        }

        int height(Node* node)
        {
            if(node == NULL)
                return 0;
            return node->height;
        }

        int get_balance(Node* node)
        {
            if(node == NULL)
                return 0;
            return height(node->left) - height(node->right);
        }

        void update_height(Node* node)
        {
            if(node == NULL)
                return;
            node->height = 1 + max(height(node->left), height(node->right));
        }

        Node* right_rotate(Node* y)
        {
            Node* x = y->left;
            Node* T2 = x->right;

            x->right = y;
            y->left = T2;

            update_height(y);
            update_height(x);

            return x;
        }

        Node* left_rotate(Node* x)
        {
            Node* y = x->right;
            Node* T2 = y->left;

            y->left = x;
            x->right = T2;

            update_height(x);
            update_height(y);

            return y;
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
            if(node == NULL)
                return new Node(word);

            if(word < node->word)
                node->left = insert(node->left, word);
            else if(word > node->word)
                node->right = insert(node->right, word);
            else
                return node;

            update_height(node);

            int balance = get_balance(node);

            if(balance > 1 && word < node->left->word)
                return right_rotate(node);

            if(balance < -1 && word > node->right->word)
                return left_rotate(node);

            if(balance > 1 && word > node->left->word)
                return left_right_rotate(node);

            if(balance < -1 && word < node->right->word)
                return right_left_rotate(node);

            return node;
        }

        // void inorder(Node* node)
        // {
        //     if(node == NULL)
        //         return;

        //     inorder(node->left);
        //     cout << node->word <<endl;
        //     inorder(node->right);
        // }

    public:

        Dict_AVL()
        {
            root = NULL;
        }

        void insert(string word)
        {
            root = insert(root, word);
        }

        // void display()
        // {
        //     inorder(root);
        //     cout << endl;
        // }

        void read_file()
        {
            string word;
            ifstream file("dictionary.txt");
            if(file.is_open())
            {
                while(getline(file, word))
                    insert(word);
                file.close();
            }
        }
};


struct char_node
{
    char data;
    char_node* next;

    char_node(char data)
    {
        this->data = data;
        next = NULL;
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

        void pop()
        {
            if(top == nullptr)
                return;
            
            char_node* temp = top;
            top = top->next;
            delete temp;
        }

        char top_element()
        {
            if(top == nullptr)
                return '\0';
            return top->data;
        }

        bool is_empty()
        {
            return top == nullptr;
        }

};

class linklist
{
    private:
        char_node* head;
    
    public:

        linklist()
        {
            head == nullptr;
        }

        void insert(char data, stack Stack)
        {
            char_node* new_node = new char_node(data);
            if(head == nullptr)
            {
                head = new_node;
                Stack.push(data);   
            }
            else
            {
                char_node* temp = head;
                while(temp->next != nullptr)
                    temp = temp->next;
                temp->next = new_node;
                Stack.push(data);
            }
        }

        void delete_node(stack Stack)
        {
            if(head == nullptr)
                return;
            
            char_node* temp = head;

            while(temp->next->next!=nullptr)
                temp = temp->next;
            
            char_node* temp2 = temp->next;
            temp->next = nullptr;
            Stack.pop();
            delete temp2;            
        }

        void write_file()
        {
            ofstream file("save.text");
            if(file.is_open())
            {
                char_node* temp = head;
                while(temp != nullptr)
                {
                    file << temp->data;
                    temp = temp->next;
                }
                file.close();
            }

        }

        void display(WINDOW* win) 
        {
            wclear(win); 
            char_node* temp = head;
            int x = 0, y = 0;  

            while (temp != nullptr) {
                mvwaddch(win, y, x, temp->data);

                x++;  
                if (x >= COLS) {  
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
    int ch;

    refresh();

    while (true) {

        ch = getch();

        if (ch == 27) 
        { 
            break;
        } 
        else if (ch == KEY_BACKSPACE || ch == 127) 
        {  
            notepad.delete_node(Stack);
        }
        else if (ch == 19) 
        {  
            notepad.write_file();
        }
        else if (ch >= 32 && ch <= 126) 
        {  
            notepad.insert(static_cast<char>(ch), Stack);
        }        
        notepad.display(stdscr);
    }

    endwin();  
    return 0;
}
