//
// Created by cristi on 3/23/21.
//

#include "State.h"

bool State::operator==(const State &other) const {
    return production == other.production && currentPtr == other.currentPtr && originPtr == other.originPtr;
}

bool State::operator<(const State &other) const {
    if (production != other.production) {
        return production < other.production;
    }
    if (currentPtr != other.currentPtr) {
        return currentPtr < other.currentPtr;
    }
    return originPtr < other.originPtr;
}

bool State::canAdvance() {
    return currentPtr < (int) production.to.size();
}

void State::advance() {
    if (canAdvance()) {
        currentPtr++;
    }
}

std::string State::nextElement() {
    if (canAdvance()) {
        return production.to[currentPtr];
    }
    return "";
}

void State::print(std::ostream &out) {
    out << "State(";
    out << "Production(";
    out << production.from << ", {";
    for (int i = 0; i < (int) production.to.size(); i++) {
        if (i > 0) {
            out << ", ";
        }
        if (currentPtr == i) {
            out << ".";
        }
        out << production.to[i];
    }
    if (!canAdvance()) {
        out << ".";
    }
    out << "}";
    out << "), ";
    out << originPtr;
    out << ")\n";
}
