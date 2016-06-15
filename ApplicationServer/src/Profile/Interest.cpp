//
// Created by chris on 07/05/16.
//

#include "Interest.h"

bool Interest::operator<(const Interest &interest) const {
    // Para poder sacar la intersección, el vector/set tiene que estar ordenado
    return category + value < interest.category + interest.value;
}

Interest::Interest(Json::Value interest) {
    this->value = interest["value"].asString();
    this->category = interest["category"].asString();
}

Interest::Interest(std::string category, std::string value) {
    this->category = category;
    this->value = value;
}

std::string Interest::getCategory() const {
    return category;
}

std::string Interest::getValue() const {
    return value;
}