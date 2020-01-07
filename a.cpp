#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    int algo_type;
    bool flag = true;
    vector <int> maze;
    cin >> algo_type;
    cout << "Algorithm type: " << algo_type << endl;
    while (1) {
        string s;
        string l;
        if (flag == true) {
            l = "1";
            flag = false;
        }
        getline(cin, s);
        if ((s == "quit") || (s == "exit")) {
            break;
        }
        //cout << "String: " << s << endl;
        //cout << "String Size: " << s.size() << endl;
        for (int i = 0; i < s.size(); i++) {
            char c = s[i];
            if (isblank(c)) {
                l += "1";
                cout << "Found" << endl;
                //l.append("1", 1);
            }
            else if (c == '*') {
                l += "1";
                //l.append("0", 1);
            }
            else {
                l += "0";
            }
        } 
        cout << "Line Converted: " << l << endl;
    }
}
