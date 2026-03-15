#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector> 
#include <stack> 
#include <queue>
using namespace std;
const char PALINDROME = 'P';
const char BALANCE = 'B';

bool isPalindrome(string& str) {
    
    stack<char> stack;
    for (int i = 0; i < str.length(); i++) {
        stack.push(str[i]);
    }

    for (int i = 0; i < str.length(); i++) {
        if (stack.top() == str[i]) {
            stack.pop();
     }
        else {return false;}
    }

    if ( stack.empty()) {
        return true;
    }
    return false;


}

//I try using queue and stack but it couldn't derive correct solution so i implement this part throught python

//The role of this method is to check whether the stack is empty when 
//it meets left parentheses, and check if the stack is empty when it meets right parentheses, and check if the top of the stack is right parentheses
bool balance(string& str) {

    stack<char> stack; //O(1)
    int length=str.length();//O(1)
    char ch;//O(1)

    for (int i = 0; i < length; i++) {//O(n)
        if (str[i] == '(' || str[i] == '{' || str[i] == '[') {//O(1)
            stack.push(str[i]);//O(1)
        }

        else if (str[i] == ')') {//O(1)

            if (stack.empty()) { //O(1)
                return false;//O(1)
            }
           
            ch = stack.top(); //O(1)
            stack.pop(); //O(1)
            if (ch != '(') {//O(1)
                return false;//O(1)
            }
            

        }
        else if (str[i] == '}') {//O(1)

            if (stack.empty()) { //O(1)
                return false;//O(1)
            }            
            ch = stack.top(); //O(1)
            stack.pop(); //O(1)
            if (ch != '{') {//O(1)
                return false;//O(1)
            }
        }
        else if (str[i] == ']') {//O(1)

            if (stack.empty()) { //O(1)
                return false;//O(1)
            }
            ch = stack.top();//O(1)
            stack.pop();//O(1)
            if (ch != '[') {//O(1)
                return false; //O(1)
            }
        }

    }
    if (!stack.empty()) {
        return false;//O(1)
    }

    return true;//O(1)
}

//total method's time complexity is O(n)

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Correct usage: [program] [input] [output]" << endl;
        exit(1);
    } //프로그램 이름, 입력파일명,출력파일 3개가 주어지지않는다면 오류메시지 출력후 프로그램 종료
    ifstream inFile(argv[1]);//입력파일의 경로
    ofstream outFile(argv[2]);//출력파일의 경로
    string line;
    string input;
    while (getline(inFile, line))//입력파일에서 한줄씩 읽어옴
    {
        char op = line[0]; //line 스트링 변수에서 첫번쨰 철자를 op에 차 변수로 저장함
        istringstream iss(line.substr(1));
        //line 스트링 변수에서 첫번째 철자를 제외한 나머지 문자열이 iss객체에 저장 
        //isstringstream 클래스는 문자열을 스트림형(가공하기 쉬운 형태)로 바꿔주는 클래스

        int data;
        switch (op)
        {
        case PALINDROME:
            input = line.substr(2); //line.substr 함수 == 문자열의 인덱스 2부터 끝까지만 input에 넣는 함수
            if (isPalindrome(input))
                outFile << "T" << endl;
            else
                outFile << "F" << endl;
            break;
        case BALANCE:
            input = line.substr(2);
            if (balance(input))
                outFile << "T" << endl;
            else
                outFile << "F" << endl;
            break;
        default:
            cerr << "Undefined operator" << endl;
            exit(1);
        }
    }
    outFile.close();
    inFile.close();
}
