#include <iostream> 
#include <queue> 
#include <vector>
#include <stack>
#include <fstream>

using namespace std; 

int main(int argc, char** argv) {
    if (argc != 2) {
        cout << "Usage: ./<output_file> <input_file>" << endl;
        exit(0);
    }
    ifstream in_file;
    string line;
    in_file.open(argv[1]);
    if (in_file.is_open()){
        while (getline (in_file, line)){
            //cout << line << endl;
            for (int i = 0; i < line.size(); i++) {
                int j = i;
                //cout << line[i];
                if (line[i] == ' '){
                    cout << "0";// << endl;
                }
                if ((line[i] == '+') || (line[i] == '-') || (line[i] == '|')){
                    cout << "1";// << endl;
                }
                if (line[i] == '*') {
                    cout << "2";// << endl;
                }
            }
            cout << endl;
        }
    } 
    return 0;
}
