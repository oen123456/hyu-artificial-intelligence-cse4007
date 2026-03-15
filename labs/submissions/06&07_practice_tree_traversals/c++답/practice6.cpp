// Practices 6&7. Binary Search Tree Operations
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <tuple>
#include <utility>
#include <algorithm>
#include <queue>
#include <cmath>
using namespace std;
const char BUILD = 'B';
const char FIND_MIN = 'm';
const char FIND_MAX = 'M';
const char SEARCH = 'S';
const char INSERT = 'I';
const char DELETE = 'D';
const char INORDER = 'N';
const char PREORDER = 'R';
const char POSTORDER = 'O';

class TreeNode {
public:
    int key;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int k, TreeNode* l = NULL, TreeNode* r = NULL) {
        key = k;
        left = l;
        right = r;
    }
};

class BinarySearchTree {
public:
    TreeNode* root;
    BinarySearchTree() : root(NULL) {}
    ~BinarySearchTree();

    TreeNode* arrayToBST(vector<int>&, int, int);
    bool isEmpty() { return (root == NULL); }
    TreeNode* findMin();
    TreeNode* findMax();
    TreeNode* search(int);
    void insertNode(int);
    void deleteNode(int);
    void writeInorder(ofstream& , TreeNode*);
    void writePreorder(ofstream&, TreeNode*);
    void writePostorder(ofstream&, TreeNode*);
    void printTree();
private:
    int _getHeight(TreeNode*);
    void _printSpaces(double, TreeNode*);
};

BinarySearchTree::~BinarySearchTree() {
//O(n)
    while (root != NULL) {

        TreeNode* current = root;

        if (root->left != NULL) {

            root = root->left;
            current->left = NULL;
        }

        else if (root->right != NULL) {

            root = root->right;

            current->right = NULL;
        }

        else {

            TreeNode* toDelete = root;

            root = NULL;

            delete toDelete;
        }
    }
}


TreeNode* BinarySearchTree::arrayToBST(vector<int>& arr, int l, int r)
//O(n)
{
    if (l > r) {
        return NULL;
    }
    for (int i = l + 1; i <= r; ++i) {
        if (arr[i - 1] > arr[i]) {

            return NULL;
        }
    }



    int mid = (l + r) / 2;
    TreeNode* root = new TreeNode(0, NULL, NULL);
    root->key = arr[mid];


    root->left = arrayToBST(arr, l, mid - 1);


    root->right = arrayToBST(arr, mid + 1, r);

    return root;

}


TreeNode* BinarySearchTree::findMin() {
    //O(log(n))
    if (root == NULL) {
        
        return NULL;
    }


    TreeNode* current = root;
    while (current->left != NULL) {
        current = current->left;
    }
    return current;

}


TreeNode* BinarySearchTree::findMax() {
    //O(log(n))
    if (root == NULL) {
       
        return NULL;
    }

    TreeNode* current = root;
    while (current->right != NULL) {
        current = current->right;
    }
    return current;


}


TreeNode* BinarySearchTree::search(int query) {
    //O(log(n))

    TreeNode* curr = root;

    while (curr != NULL) { //O(lnn)
        if (curr->key > query) {
            curr = curr->left;
        }
        else if (curr->key < query) {
            curr = curr->right;

        }
        else return curr;

    }

    return NULL;

}

void BinarySearchTree::insertNode(int k) {
    //O(log(n))

       TreeNode* curr = root;
    
    if(isEmpty()){
        root = new TreeNode(k);
    }
    
    else{
        while(true){ 
            if(curr -> key < k && curr -> right != nullptr){
                curr = curr -> right;
            }
            else if(curr -> key > k && curr -> left != nullptr){
                curr = curr -> left;
            }
            else{
                break;
            }
        }
        
        if(curr -> key < k){
            TreeNode* newNode = new TreeNode(k);
            curr -> right = newNode;
        }
        if(curr -> key > k){
            TreeNode* newNode = new TreeNode(k);
            curr -> left = newNode;
        }
    }
}



    void BinarySearchTree::deleteNode(int k) {
        //O(log(n))
        TreeNode* del = search(k);

        if (!del) {
            exit(1);
        }

        if (!(del->right && del->left)) {
            delete del;
        }

        else if (del->right == NULL && del->left != NULL) {
            TreeNode* curr = del->left;
            del->key = curr->key;
            del->left = curr->left;
            del->right = curr->right;
            delete curr;
        }

        else if (del->left == NULL && del->right != NULL) {
            TreeNode* curr = del->right;
            del->key = curr->key;
            del->left = curr->left;
            del->right = curr->right;
            delete curr;
        }

        else {
            TreeNode* curr = del->right;
            TreeNode* prev = del;

            while (curr->left) {
                prev = curr;
                curr = curr->left;
            }

            del->key = curr->key;
            prev->left = curr->right;
            delete curr;
        }
    }

    
  


    void BinarySearchTree::writeInorder(ofstream& outFile, TreeNode* t) {
        //O(n)
        if(t != NULL){
        
        writeInorder(outFile, t -> left);
         outFile << t -> key << " ";
        writeInorder(outFile, t -> right);
        
        }

    }


  void BinarySearchTree::writePreorder(ofstream& outFile, TreeNode* t) {
 //O(n)
    if(t != NULL){
        outFile << t -> key << " ";
        writePreorder(outFile, t-> left);
        writePreorder(outFile, t-> right);
        
    }
}



    void BinarySearchTree::writePostorder(ofstream & outFile,TreeNode* t) {
         //O(n)
     if(t != NULL){
       
        writePreorder(outFile, t-> left);
        writePreorder(outFile, t-> right);
         outFile << t -> key << " ";
        
          }
    }

    int BinarySearchTree::_getHeight(TreeNode * curr) {
        //O(log(n))
        if (curr == NULL)
            return 0;
        return 1 + max(_getHeight(curr->left), _getHeight(curr->right));
    }

    void BinarySearchTree::_printSpaces(double n, TreeNode * curr) {
        //O(n)
        for (double i = 0; i < n; ++i)
            cout << "  ";
        if (curr == NULL)
            cout << " ";
        else
            cout << curr->key;
    }

    void BinarySearchTree::printTree() {
        //O(n)
        if (root == NULL)
            return;
        queue<TreeNode*> q;
        q.push(root);
        queue<TreeNode*> temp;
        int cnt = 0;
        int height = _getHeight(root) - 1;
        double nMaxNodes = pow(2, height + 1) - 1;
        while (cnt <= height) {
            TreeNode* curr = q.front();
            q.pop();
            if (temp.empty())
                _printSpaces(nMaxNodes / pow(2, cnt + 1) + height - cnt, curr);
            else
                _printSpaces(nMaxNodes / pow(2, cnt), curr);
            if (curr == NULL) {
                temp.push(NULL);
                temp.push(NULL);
            }
            else {
                temp.push(curr->left);
                temp.push(curr->right);
            }
            if (q.empty()) {
                cout << endl << endl;
                q = temp;
                queue<TreeNode*> empty;
                swap(temp, empty);
                ++cnt;
            }
        }
    }

    int main(int argc, char* argv[]) {
        if (argc != 3) {
            cerr << "Correct usage: [exe] [input] [output]" << endl;
            exit(1);
        }
        BinarySearchTree tree;
        ifstream inFile(argv[1]);
        ofstream outFile(argv[2]);
        string line;
        while (getline(inFile, line))
        {
            char op = line[0];
            istringstream iss(line.substr(1));
            int k;
            TreeNode* found = NULL;
            vector<int> data;
            switch (op)
            {
            case BUILD:
                while (iss >> k)
                    data.push_back(k);
                tree.root = tree.arrayToBST(data, 0, data.size() - 1);
                if (tree.root) {
                    outFile << BUILD << endl;
                }
                else {
                    cerr << "BUILD: invalid input" << endl;
                    exit(1);
                }
                tree.printTree();
                break;
            case FIND_MIN:
                found = tree.findMin();
                if (found == NULL) {
                    cerr << "FindMin failed" << endl;
                    exit(1);
                }
                else {
                    outFile << found->key << endl;
                }
                break;
            case FIND_MAX:
                found = tree.findMax();
                if (found == NULL) {
                    cerr << "FindMax failed" << endl;
                    exit(1);
                }
                else {
                    outFile << found->key << endl;
                }
                break;
            case SEARCH:
                if (!(iss >> k)) {
                    cerr << "SEARCH: invalid input" << endl;
                    exit(1);
                }

                else {
                    if (tree.search(k) != NULL) {
                        outFile << tree.search(k)->key << endl;
                    }

                    else {
                        cerr << "Search failed" << endl;
                        exit(1);
                    }
                }
                break;
            case INORDER:

                tree.writeInorder(outFile, tree.root);
                outFile << endl;
                break;
            case PREORDER:

                tree.writePreorder(outFile, tree.root);
                outFile << endl;
                break;
            case POSTORDER:

                 tree.writePostorder(outFile, tree.root);
                outFile << endl;
                break;
            case INSERT:
                if (!(iss >> k)) {
                    cerr << "INSERT: invalid input" << endl;
                    exit(1);
                }

                else {
                    tree.insertNode(k);
                    outFile << "I " << k << endl;
                }
                break;
            case DELETE:
                if (!(iss >> k)) {
                    cerr << "DELETE: invalid input" << endl;
                    exit(1);
                }

                else {
                    tree.deleteNode(k);
                    outFile << "D " << k << endl;
                }
                break;
            default:
                cerr << "Undefined operator" << endl;
                exit(1);
            }
        }
        outFile.close();
        inFile.close();
    }
