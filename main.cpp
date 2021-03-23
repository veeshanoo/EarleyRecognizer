#include <bits/stdc++.h>
#include "Production.h"
#include "Grammar.h"
#include "EarleyRecognizer.h"

using namespace std;

int main() {
    ifstream in("../input.in"); // modify input path
    ofstream out("output.out");

    Grammar grammar;
    grammar.read(in);

    EarleyRecognizer recognizer(grammar);

    for (string word; getline(in, word); ) {
        recognizer.recognize(word, 1, out);
    }

    return 0;
}