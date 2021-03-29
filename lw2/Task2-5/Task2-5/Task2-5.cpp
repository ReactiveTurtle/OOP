#include <iostream>
#include <string>
#include "HTMLDecoder.hpp"

using namespace std;

int main()
{
    string buffer;
    while (getline(cin, buffer)) {
        cout << HtmlDecode(buffer) << endl;
    }
}
