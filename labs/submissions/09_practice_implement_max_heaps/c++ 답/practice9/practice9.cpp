// Practice 9. Max Heap
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <climits>
using namespace std;
const char INSERT = 'I';
const char DELETE = 'D';
const char MAXIMUM = 'M';
const int MAX_CAPACITY = 1000;

class MaxHeap {
public:
    int capacity;
    int count;
    int* elements;

   
    int parent(int i) {
        return (i - 1) / 2;
    }
    
    int left(int i) {
        return 2 * i + 1;
    }
  
    int right(int i) {
        return 2 * i + 2;
    }
    void maxHeapify(int i);
public:
    MaxHeap(int num = MAX_CAPACITY) {
        elements = new int[num];
        count = 0;
        capacity = num;
    }
    ~MaxHeap() {
        delete elements;
    }

   
    void insertElement(int);
   
    int maximum();

    int deleteMaximum();
};

void MaxHeap::maxHeapify(int i) {

    int l, r, largest, temp;
    l = left(i);
    r = right(i);
    if (l != -1 && elements[l] > elements[i])
        largest = l;

    else
        largest = i;

    if (r != -1 && elements[r] > elements[largest])
        largest = r;

    if (largest != i) {
        temp = elements[i];
        elements[i] = elements[largest];
        elements[largest] = temp;
        maxHeapify(largest);
    }
}

void MaxHeap::insertElement(int x) {
    int c = count;
    int p = parent(c);


    while (c > 0 && elements[p] < x) {
        elements[c] = elements[p];

        c = p;

        p = parent(c);
    }

    elements[c] = x;
    count++;
}

int MaxHeap::maximum() {

    if (count == 0) {
        cerr << "no elements" << endl;
        exit(1);
    }

    return elements[0];
    
}

int MaxHeap::deleteMaximum() {
    if (count == 0) {

        cerr << "heap enderflow" << endl;
        exit(1);

    }

    int largest = elements[0];
    elements[0] = elements[count - 1];
    count--;

    maxHeapify(0);
    return largest;

}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Correct usage: [program] [input] [output]" << endl;
        exit(1);
    }
    MaxHeap h;
    ifstream inFile(argv[1]);
    ofstream outFile(argv[2]);
    string line;
    while (getline(inFile, line))
    {
        char op = line[0];
        istringstream iss(line.substr(1));
        int key;
        string name;
        cout << line << endl;
        switch (op)
        {
        case INSERT:
            if (!(iss >> key)) {
                cerr << "INSERT: invalid input" << endl;
                exit(1);
            }

            h.insertElement(key);

            for (int i = 0; i < h.count; i++) {
                outFile << h.elements[i] << " ";
            }

            outFile<<endl;
            break;


        case DELETE:
            
            h.deleteMaximum();
          
            for (int i = 0; i < h.count; i++) {
                outFile << h.elements[i] << " ";
            }
            outFile<<endl;
            break;
        case MAXIMUM:
    
            outFile << h.maximum() << endl;
            break;
        default:
            cerr << "Undefined operator" << endl;
            exit(1);
        }
    }
    outFile.close();
    inFile.close();
}
