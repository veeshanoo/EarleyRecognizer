//
// Created by cristi on 3/23/21.
//

#include "Production.h"

bool Production::operator==(const Production &other) const {
    return from == other.from && to == other.to;
}

bool Production::operator!=(const Production &other) const {
    return !(*this == other);
}

bool Production::operator<(const Production &other) const {
    if (from != other.from) {
        return from < other.from;
    }
    return to < other.to;
}