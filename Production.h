//
// Created by cristi on 3/23/21.
//

#include <bits/stdc++.h>
#include <utility>

#ifndef EARLEYRECOGNIZER_PRODUCTION_H
#define EARLEYRECOGNIZER_PRODUCTION_H

struct Production {
    std::string from; // left side of production
    std::vector<std::string> to; // right side of production

    Production(std::string from, std::vector<std::string> to) : from(std::move(from)), to(std::move(to)) {}

    bool operator==(const Production &other) const;

    bool operator!=(const Production &other) const;

    bool operator<(const Production &other) const;
};

#endif //EARLEYRECOGNIZER_PRODUCTION_H

