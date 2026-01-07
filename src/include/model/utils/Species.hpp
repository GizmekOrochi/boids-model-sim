#ifndef SPECIES_HPP
#define SPECIES_HPP

#pragma once

namespace bd::Species {

enum BoidSpecies {
    CYAN = 1,
    GREEN = 2,
    YELLOW = 3,
    BLUE = 10,
    RED = 100
};

// Returns the food-chain tier (1, 2, 3)
inline int speciesTier(BoidSpecies s) {
    int v = static_cast<int>(s);
    if (v < 10) return 1;
    if (v < 100) return 2;
    return 3;
}

// True if subject should fear other
inline bool fear(BoidSpecies subject, BoidSpecies other) {
    int subjectTier = speciesTier(subject);
    int otherTier = speciesTier(other);

    if (subjectTier == otherTier)
        return false;

    return otherTier > subjectTier;
}

inline bool canEat(BoidSpecies predator, BoidSpecies prey) {
    int subjectTier = speciesTier(predator);
    int otherTier = speciesTier(prey);

    if (subjectTier == 3) {
        return true; // eats everything
    }
    if (subjectTier == 2) {
        return otherTier == 1;// eats only tier 1
    }
    return false;// tier 1 eats nothing
}

inline bool canBeEatenBy(BoidSpecies prey, BoidSpecies predator) {
    return canEat(predator, prey);
}

}

#endif
