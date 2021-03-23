//
// Created by cristi on 3/23/21.
//

#include "Grammar.h"

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