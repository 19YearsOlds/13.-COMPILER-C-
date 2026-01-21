#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>


using namespace std;


vector<string> tokenize(const string& code) {
    vector<string> tokens;
    string token;
    for (char ch : code) {
        if (isspace(ch)) {
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
        } else {
            token += ch;
        }
    }
    if (! token.empty()) tokens.push_back(token);
    return tokens;
}


void parseTokens(const vector<string>& tokens) {
    cout << "Parsing Tokens:\n";
    for (const string& token : tokens) {
        cout << token << " ";
    }
    cout << endl;
}

void compile(const string& filename) {
    string command = "g++ " + filename + " -o output.exe";
    int result = system(command.c_str());
    if (result == 0) {
        cout << "Compilation Successful! Run with: ./output.exe\n";
    } else {
        cout << "Compilation Failed!\n";
    }
}

int main() {
    string filename;
    cout << "Enter C++ source file to compile: ";
    cin >> filename;

    ifstream file(filename);
    if (!file) {
        cerr << "Error: File not found!\n";
        return 1;
    }

    string code((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    vector<string> tokens = tokenize(code);
    parseTokens(tokens);
    compile(filename);

    return 0;
}