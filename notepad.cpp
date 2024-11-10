#include<iostream>
#include<fstream>
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

        void inorder(Node* node)
        {
            if(node == NULL)
                return;

            inorder(node->left);
            cout << node->word <<endl;
            inorder(node->right);
        }

    public:

        Dict_AVL()
        {
            root = NULL;
        }

        void insert(string word)
        {
            root = insert(root, word);
        }

        void display()
        {
            inorder(root);
            cout << endl;
        }

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


int main()
{
    Dict_AVL dict;
    dict.read_file();
    dict.display();
    return 0;
}