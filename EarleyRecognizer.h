//
// Created by cristi on 3/23/21.
//

#include <utility>

#include "Grammar.h"
#include "State.h"

#ifndef EARLEYRECOGNIZER_EARLEYRECOGNIZER_H
#define EARLEYRECOGNIZER_EARLEYRECOGNIZER_H

struct EarleyRecognizer {
    Grammar grammar;
    std::map<int, std::vector<State> > states; // -1 indexed
    std::map<int, std::set<State> > statesSet; // will be used to fast check for a state

    explicit EarleyRecognizer(Grammar grammar) : grammar(std::move(grammar)) {}

    // Clears state sets
    void clear();

    bool canAddState(const State &state, int column);

    void addState(State state, int column);

    // Clears state sets and populates S(-1) (input string is 0 indexed)
    void init();

    // Earley algorithm
    void recognize(const std::string &input, int verbose, std::ostream &out);

    // Prediction: For every state in S(k) of the form (X → α • Y β, j) (where j is the origin position as above),
    // add (Y → • γ, k) to S(k) for every production in the grammar with Y on the left-hand side (Y → γ).
    void predict(State state, int column);

    // Prediction: For every state in S(k) of the form (X → α • Y β, j) (where j is the origin position as above and
    // Y is a nullable nonterminal), add (X → α Y • β, j) to S(k)
    void predictNullable(State state, int column);

    // Scanning: If a is the next symbol in the input stream, for every state in S(k) of the form (X → α • a β, j), add (X → α a • β, j) to S(k+1).
    void scan(State state, int column);

    // Completion: For every state in S(k) of the form (Y → γ •, j), find all states in S(j) of the form (X → α • Y β, i) and add (X → α Y • β, i) to S(k).
    void complete(State state, int column);

    // Prints all state sets S(k) for k in -1..(input.size() - 1)
    void print(const std::string &input, std::ostream &out);
};

#endif //EARLEYRECOGNIZER_EARLEYRECOGNIZER_H