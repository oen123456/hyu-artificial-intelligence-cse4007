// Practice 5. Binary Search Tree
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

class TreeNode {
public:
  int key;
TreeNode* left;
TreeNode* right; 
};

class BinarySearchTree {
public:
  TreeNode* root; //TreeNode클래스의 객체를 가리킬수있음
  BinarySearchTree(): root(nullptr) {} //이 생성자는 새로운 이진 탐색 트리 객체를 생성할 때 해당 트리의 루트 노드를 널 포인터로 설정합니다.
  ~BinarySearchTree(); //소멸자 == 데이터 해제

  TreeNode* arrayToBST(vector<int>&, int, int);
  TreeNode* findMin();
  TreeNode* findMax();
  void printTree();
private:
  int _getHeight(TreeNode*);
  void _printSpaces(double, TreeNode*);
};

  BinarySearchTree::~BinarySearchTree() {
    // 소멸자에서 루트 노드를 기반으로 모든 노드를 삭제하고 메모리를 해제하는 방식을 사용할 것입니다.
    // 루트 노드가 없을 경우 아무 작업도 수행하지 않습니다.
    while (root != nullptr) {
        // 현재 루트 노드를 찾습니다.
        TreeNode* current = root;
        // 왼쪽 서브트리가 존재한다면, 왼쪽으로 이동하여 모든 노드를 삭제합니다.
        if (root->left != nullptr) {
            // 왼쪽으로 이동하며 현재 루트를 갱신합니다.
            root = root->left;
            // 이전 루트 노드의 오른쪽을 nullptr로 설정하여 dangling pointer를 방지합니다.
            current->left = nullptr;
        }
        // 오른쪽 서브트리가 존재한다면, 오른쪽으로 이동하여 모든 노드를 삭제합니다.
        else if (root->right != nullptr) {
            // 오른쪽으로 이동하며 현재 루트를 갱신합니다.
            root = root->right;
            // 이전 루트 노드의 왼쪽을 nullptr로 설정하여 dangling pointer를 방지합니다.
            current->right = nullptr;
        }
        // 왼쪽과 오른쪽 서브트리가 없는 경우, 해당 노드는 leaf node입니다. 이를 삭제합니다.
        else {
            // 삭제할 노드를 저장합니다.
            TreeNode* toDelete = root;
            // 루트를 nullptr로 설정하여 노드를 삭제합니다.
            root = nullptr;
            // 메모리를 해제합니다.
            delete toDelete;
        }
    }
}
    
//소멸자 부분 함수가 호출이 끝났을떄 실행 메모리를 반환하기 위해 사용한다.

// Given a sequence arr of integers, start index l, the end index r, 
// build a binary search (sub)tree that contains keys in arr[l], ..., arr[r].
// Return the root node of the tree
TreeNode* BinarySearchTree::arrayToBST(vector<int>& arr, int l, int r) //받아오는 패러미터 ==( arr[l] ... arr[r] , i , r)
//Tree node* 는 포인터를 반환한다는 뜻, BinarySearchTree는 클래스, ::는 자바에서 .과 같은 역할
{
     if (l > r) {
        return nullptr;
    }
    for (int i = 1; i <= r; ++i) {
        if (arr[i - 1] > arr[i]) {
            // 오름차순이 아니라면 nullptr 반환
            return nullptr;
        }
    }
   
    int mid = (l + r) / 2;
    TreeNode* root = new TreeNode();//root라는 새로운 객체 생성2
    root->key = arr[mid]; //화살표를 쓰면 root라는 포인터를통해 객체변수에 접근하겠다는 뜻

    // 왼쪽 서브 트리를 재귀적으로 생성
    root->left = arrayToBST(arr, l, mid - 1);

    // 오른쪽 서브 트리를 재귀적으로 생성
    root->right = arrayToBST(arr, mid + 1, r);

    return root;

}

// Return the node with the minimum value 
TreeNode* BinarySearchTree::findMin() {
    if (root == nullptr) {
        // 루트 노드가 없으면 트리가 비어있으므로 nullptr 반환
        return nullptr;
    }

    // 최소값은 항상 왼쪽 끝에 위치합니다.
    TreeNode* current = root;
    while (current->left != nullptr) {
        current = current->left;
    }
    return current;
}

// Return the nod
// with the maximum value 
TreeNode* BinarySearchTree::findMax() {
    if (root == nullptr) {
        // 루트 노드가 없으면 트리가 비어있으므로 nullptr 반환
        return nullptr;
    }
    

    // 최대값은 항상 오른쪽 끝에 위치합니다.
    TreeNode* current = root;
    while (current->right != nullptr) {
        current = current->right;
    }
    return current;
}

int BinarySearchTree::_getHeight(TreeNode* curr) {
  if (curr == nullptr) 
    return 0;
  return 1 + max(_getHeight(curr->left), _getHeight(curr->right));
} //Max 함수 == 두개중에 더 큰거를  반환

void BinarySearchTree::_printSpaces(double n, TreeNode* curr) {
  for(double i = 0; i < n; ++i) 
    cout<<"  ";
  if (curr == nullptr)
    cout<<" ";
  else
    cout<<curr->key;
}
//화살표는 래퍼런스를 통해 객체변수에 접근 .은 직접접근 상세한 차이는 나중에 공부

void BinarySearchTree::printTree() {
  if (root == nullptr)
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
    if (curr == nullptr) {
      temp.push(nullptr);
      temp.push(nullptr);
    }
    else {
      temp.push(curr->left);
      temp.push(curr->right);
    }
    if (q.empty()) {
      cout<<endl<<endl;
      q = temp;
      queue<TreeNode*> empty;
      swap(temp, empty);
      ++cnt;
    }
  }
}

int main(int argc, char* argv[]) {
  if (argc != 3) {
    cerr<<"Correct usage: [exe] [input] [output]"<<endl;
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
    TreeNode* found = nullptr;
    vector<int> data;
    switch(op)
    {
      case BUILD:
        while (iss >> k)
          data.push_back(k);
        tree.root = tree.arrayToBST(data, 0, data.size() - 1);
        if (tree.root) {
          outFile<<BUILD<<endl;
        }
        else {
          cerr<<"BUILD: invalid input"<<endl;
          exit(1);
        }
        tree.printTree();
        break;
      case FIND_MIN:
        found = tree.findMin();
        if (found == nullptr) {
          cerr<<"FindMin failed"<<endl;
          exit(1);
        }
        else {
          outFile<<found->key<<endl;
        }
        break;
      case FIND_MAX:
        found = tree.findMax();
        if (found == nullptr) {
          cerr<<"FindMax failed"<<endl;
          exit(1);
        }
        else {
          outFile<<found->key<<endl;
        }
        break;
      default:
        cerr<<"Undefined operator"<<endl;
        exit(1);
    }
  }
  outFile.close();
  inFile.close();
}
