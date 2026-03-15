// Practice 10. Graph Representation
#include <algorithm>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <queue> // BFS
#include <sstream>
#include <stack> // DFS
#include <tuple>
#include <vector>
using namespace std;
const char CONSTRUCT = 'C';
const char IS_ADJACENT = 'I';
const char GET_NEIGHBORS = 'N';
const char BFS = 'B';
const char DFS = 'D';
const char REACHABLITY = 'R';
const char TOPOLOGICAL_SORT = 'T';
const char SHORTEST_PATH = 'S';

class Graph {
public:
   
    vector<tuple<int, int, int>> data; //튜플로 되어있는 벡터 data 초기화
    vector<vector<pair<int, int>>> box; //벡터 안에 pair로 되어있는 벡터가 있음. 이중벡터 box

    Graph() { //constructor
    }
    void make_graph(vector<tuple<int, int, int>> d_ata, int n_Vertices, int e_dges) { //리턴값 없음
        box.resize(n_Vertices); //box 벡터의 크기를 n_Vertices로 설정.정점 수가 n_Vertices개라는 것을 의미
        data = d_ata;
        for (int i = 0; i < e_dges; i++) {
            int index = get<0>(data[i]); //get<0>: tuple의 첫번째 요소, data[i]: 벡터 data의 i번째 튜플
            box[index].push_back(make_pair(get<1>(data[i]), get<2>(data[i]))); // 튜플 v랑 w를 pair로 만들고 box벡터에 넣기
        }
    }

    vector<pair<int, int>> getNeighbors(int u) { // 벡터 u를 받아와서 u의 이웃을 얻는 함수. 리턴값이 vector<pair>

        return box[u]; //벡터 u의 이웃은 box[u]에 튜플을 담은 벡터들로 이루어져있음
    }

    bool Adjacent(int u, int v) { //u,v를 받아와서 bool값을 리턴. u와 v가 인접한 값이라면 true리턴
        for (int i = 0; i < box[u].size(); i++) {
            if (get<0>(box[u][i]) == v) { // get<0> : pair의 첫번째 요소 box[u][i]: 이중벡터에서 u번째 행의 i번째 요소
                return true;
            }
        }
        return false;
    }

    int[] topologicalSort() {

        queue <int> q;



    }

};

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Correct usage: [exe] [input] [output]" << endl;
        exit(1);
    }
    Graph g;
    ifstream inFile(argv[1]);
    ofstream outFile(argv[2]);
    string line;
    while (getline(inFile, line))
    {
        char op = line[0];
        istringstream iss(line.substr(1));
        int u, v, nVertices, nEdges;
        vector<tuple<int, int, int>> data;
        switch (op)
        {
        case CONSTRUCT:
            if (!(iss >> nVertices >> nEdges)) {
                cerr << "CONSTRUCT: invalid input" << endl;
                exit(1);
            }
            // TODO. Construct a graph
            int u_, v_, wgt_;
            for (int i = 0; i < nEdges; i++) {
                //inFile은 파일 스트림 객체를 나타내며, 파일에서 데이터를 읽어오는 역할
                //line은 파일에서 읽어온 한 줄의 데이터를 저장하는 문자열 변수
                getline(inFile, line); //파일에서 한 줄씩 데이터를 읽어와서 line 문자열에 저장

                istringstream iss(line); //iss 객체를 사용하여 line 문자열을 공백이나 다른 구분자를 기준으로 토큰으로 분리

                if (!(iss >> u_ >> v_ >> wgt_)) {
                    cerr << "CONSTRUCT: invalid input" << endl;
                    exit(1);
                }
                data.push_back(make_tuple(u_, v_, wgt_)); //construct tuple and put into in data
            }
            g.make_graph(data, nVertices, nEdges);

            break;
        case IS_ADJACENT:
            if (!(iss >> u >> v)) {
                cerr << "isAdjacent: invalid input" << endl;
                exit(1);
            }
            // TODO. Check if edge (u, v) exists in the graph
            if (g.Adjacent(u, v) == true) {
                outFile << u << " " << v << " " << "T" << endl;
            }
            if (g.Adjacent(u, v) == false) {
                outFile << u << " " << v << " " << "F" << endl;
            }

            break;

        case GET_NEIGHBORS:
            if (!(iss >> u)) {
                cerr << "getNeighbors: invalid input" << endl;
                exit(1);
            }
            // TODO. Get all the neighbors of u

            for (int i = 0; i < g.getNeighbors(u).size(); i++) {
                outFile << get<0>(g.getNeighbors(u)[i]) << " "; //pair의 앞 부분 가져오기
            }
            outFile << endl;

            break;

        case TOPOLOGICAL_SORT:

            for (i = 0; i < nVertices; i++) {
                outFile << g.topologicalSort << " ";


            }
            outFile << endl;




            break;

        default:
            cerr << "Undefined operator" << endl;
            exit(1);
        }
    }
    outFile.close();
    inFile.close();
}


