//
// Created by cristi on 3/23/21.
//

#include "EarleyRecognizer.h"

void EarleyRecognizer::clear() {
    states.clear();
    statesSet.clear();
}

bool EarleyRecognizer::canAddState(const State &state, int column) {
    return (statesSet[column].find(state) == statesSet[column].end());
}

void EarleyRecognizer::addState(State state, int column) {
    if (canAddState(state, column)) {
        states[column].push_back(state);
        statesSet[column].insert(state);
    }
}

void EarleyRecognizer::init() {
    clear();
    for (auto p : grammar.getTopLevelProductions()) {
        addState(State(p, 0, -1), -1);
    }
}

void EarleyRecognizer::recognize(const std::string &input, int verbose, std::ostream &out) {
    init();

    for (int i = -1; i < (int) input.size(); i++) {
        for (int j = 0; j < (int) states[i].size(); j++) {
            if (states[i][j].canAdvance()) {
                if (grammar.isNonterminal(states[i][j].nextElement())) {
                    predict(states[i][j], i);

                    if (grammar.isNullable(states[i][j].nextElement())) { // magic handling of nullable nonterminals
                        predictNullable(states[i][j], i);
                    }
                } else {
                    if (states[i][j].nextElement() ==
                        std::string(1, input[i + 1])) { // checks if nextElement() matches next input symbol
                        scan(states[i][j], i + 1);
                    }
                }
            } else {
                complete(states[i][j], i);
            }
        }
    }

    if (verbose == 1) {
        print(input, out);
    }
}

void EarleyRecognizer::predict(State state, int column) {
    for (auto p : grammar.getProductions(state.nextElement())) {
        addState(State(p, 0, column), column);
    }
}

void EarleyRecognizer::predictNullable(State state, int column) {
    addState(State(state.production, state.currentPtr + 1, state.originPtr), column);
}

void EarleyRecognizer::scan(State state, int column) {
    addState(State(state.production, state.currentPtr + 1, state.originPtr), column);
}

void EarleyRecognizer::complete(State state, int column) {
    for (auto s : states[state.originPtr]) {
        if (s.nextElement() == state.production.from) {
            addState(State(s.production, s.currentPtr + 1, s.originPtr), column);
        }
    }
}

void EarleyRecognizer::print(const std::string &input, std::ostream &out) {
    out << "Earley tables for \"" << input << "\":" << std::endl;
    for (int i = -1; i < (int) input.size(); i++) {
        out << "S(" << i << "):" << std::endl;
        for (int j = 0; j < (int) states[i].size(); j++) {
            states[i][j].print(out);
        }

        out << std::endl;
    }

    bool isAccepted = false;
    int row = 0;
    for (auto state : states[(int) input.size() - 1]) {
        if (state.production.from == grammar.start) {
            if (!state.canAdvance()) {
                if (state.originPtr == -1) {
                    isAccepted = true;
                    break;
                }
            }
        }

        row++;
    }

    if (isAccepted) {
        out << "String \"" << input << "\" was accepted." << std::endl << std::endl << std::endl;
    } else {
        out << "String \"" << input << "\" was rejected." << std::endl << std::endl << std::endl;
    }
}