//
// Created by cristi on 3/23/21.
//

#include <bits/stdc++.h>
#include <utility>

#include "Production.h"

#ifndef EARLEYRECOGNIZER_STATE_H
#define EARLEYRECOGNIZER_STATE_H

struct State {
    Production production;
    int currentPtr; // before what position is the "dot" located in production.to
    int originPtr; // position in the input where production began

    State(Production production, int currentPtr, int originPtr) : production(std::move(production)),
                                                                  currentPtr(currentPtr), originPtr(originPtr) {}

    bool operator==(const State &other) const;

    bool operator<(const State &other) const;

    bool canAdvance();

    void advance();

    std::string nextElement();

    void print(std::ostream &out);
};

#endif //EARLEYRECOGNIZER_STATE_H
