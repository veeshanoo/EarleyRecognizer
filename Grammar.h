//
// Created by cristi on 3/23/21.
//

#include <utility>
#include <bits/stdc++.h>
#include "Production.h"

#ifndef EARLEYRECOGNIZER_GRAMMAR_H
#define EARLEYRECOGNIZER_GRAMMAR_H

struct Grammar {
    std::set<std::string> terminals; // a single character for convenience
    std::set<std::string> nonterminals; // any std::string that's not a terminal
    std::set<Production> productions;
    std::set<std::string> nullables;
    std::string start; // start symbol
    std::string lambda; // usually is _

    Grammar(std::set<std::string> terminals, std::set<std::string> nonterminals, std::set<Production> productions,
            std::string start, std::string lambda) : terminals(std::move(terminals)),
                                                     nonterminals(std::move(nonterminals)),
                                                     productions(std::move(productions)), nullables(),
                                                     start(std::move(start)), lambda(std::move(lambda)) {
        genNullables();
    }

    bool isTerminal(const std::string &s);

    bool isNonterminal(const std::string &s);

    bool isNullable(const std::string &s);

    // Generates nullable nonterminals
    void genNullables();

    // Returns all productions with given left side
    std::vector<Production> getProductions(const std::string &leftSide);

    std::vector<Production> getTopLevelProductions();
};

#endif //EARLEYRECOGNIZER_GRAMMAR_H
