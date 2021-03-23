//
// Created by cristi on 3/23/21.
//

#include <bits/stdc++.h>

#include "Grammar.h"

//using namespace std;

std::vector<std::string> split(std::string s, const std::string &delimiter) {
    std::vector<std::string> splitString;
    while ((int) s.size()) {
        int index = s.find(delimiter);

        if (index != std::string::npos) {
            splitString.push_back(s.substr(0, index));
            s = s.substr(index + (int) delimiter.size());
            if ((int) s.size() == 0) {
                splitString.push_back(s);
            }
        } else {
            splitString.push_back(s);
            s = "";
        }
    }

    return splitString;
}

void Grammar::read(std::istream &in) {
    terminals.clear();
    nonterminals.clear();
    productions.clear();

    try {
        std::string line;

        // terminals
        std::getline(in, line);
        for (auto s : split(line, " ")) {
            if ((int) s.size() == 1) {
                terminals.insert(s);
            }
        }

//        cout << "TERMINALS: ";
//        for (auto it : terminals) {
//            cout << it << " ";
//        }
//        cout << endl;

        // nonterminals
        std::getline(in, line);
        for (auto s : split(line, " ")) {
            if ((int) s.size() > 0) {
                nonterminals.insert(s);
            }
        }

//        cout << "NONTERMINALS: ";
//        for (auto it : nonterminals) {
//            cout << it << " ";
//        }
//        cout << endl;

        // start symbol
        std::getline(in, line);
        start = line;
//        cout << "START symbol: " << start << endl;

        // lambda symbol
        std::getline(in, line);
        lambda = line;
//        cout << "LAMBDA symbol: " << lambda << endl;

        // productions
        std::getline(in, line);
        int prodCnt = std::atoi(line.c_str());
//        cout << "PRODUCTIONS:" << endl;
        for (int i = 0; i < prodCnt; i++) {
            std::getline(in, line);

            auto symbols = split(line, "->");
            auto from = split(symbols[0], " ")[0];
//            cout << from << endl;

            std::vector<std::string> to;
            for (auto s : split(symbols[1], " ")) {
                if ((int) s.size() > 0) {
                    to.push_back(s);
                }
            }

            productions.insert(Production(from, to));
//            State(Production(from, to), 0, 0).print(cout);
        }

        genNullables();
        std::cout << "Successful grammar read";
    } catch (...) {
        std::cerr << "Invalid input file" << std::endl;
    }
}

bool Grammar::isTerminal(const std::string &s) {
    return (terminals.find(s) != terminals.end());
}

bool Grammar::isNonterminal(const std::string &s) {
    return (nonterminals.find(s) != nonterminals.end());
}

bool Grammar::isNullable(const std::string &s) {
    return (nullables.find(s) != nullables.end());
}

void Grammar::genNullables() {
    bool found = true;
    nullables.insert(lambda);

    while (found) {
        found = false;

        for (const auto &p : productions) {
            if (isNullable(p.from)) {
                continue;
            }

            bool nullable = true;
            for (const auto &sym : p.to) {
                if (!isNullable(sym)) {
                    nullable = false;
                    break;
                }
            }

            if (nullable) {
                found = true;
                nullables.insert(p.from);
            }
        }
    }
}

std::vector<Production> Grammar::getProductions(const std::string &leftSide) {
    std::vector<Production> ans;
    for (const auto &p : productions) {
        if (p.from == leftSide) {
            ans.push_back(p);
        }
    }

    return ans;
}

std::vector<Production> Grammar::getTopLevelProductions() {
    return getProductions(start);
}