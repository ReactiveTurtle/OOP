#include <iostream>
#include <string>
#include "HTMLDecoder.hpp"

using namespace std;

int main()
{
    string line;
    while (getline(cin, line)) {
        cout << HtmlDecode(line) << endl;
    }
}
