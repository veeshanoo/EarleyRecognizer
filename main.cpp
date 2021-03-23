#include <bits/stdc++.h>
#include "Production.h"
#include "Grammar.h"
#include "EarleyRecognizer.h"

using namespace std;

int main() {
    // ifstream cin("tst.in");
    ofstream out("tst.out");

    set<string> terminals = {"a", "b"};
    set<string> nonterminals = {"S", "X"};
    set<Production> productions;
    // x -> y "+" x
    // x -> y
    // y -> "1", y -> "2"
    productions.insert(Production("S", vector<string> {"a", "X", "b", "X"}));
    productions.insert(Production("S", vector<string> {"b", "X", "a", "X"}));
    productions.insert(Production("X", vector<string> {"a", "X", "b", "X"}));
    productions.insert(Production("X", vector<string> {"b", "X", "a", "X"}));
    productions.insert(Production("X", vector<string> {"_"}));

    string start = "S";
    string lambda = "_";
    Grammar grammar(terminals, nonterminals, productions, start, lambda);
    EarleyRecognizer recognizer(grammar);

    // for (auto it : parser.grammar.nullables) {
    //     cout << it << endl;
    // }

    vector<string> words = {"ab", "abab", "ba", "aaabbb", "baab", "bbbb", "baba", "abb"};
    for (const auto& word : words) {
        recognizer.recognize(word, 1, out);
    }

    return 0;
}