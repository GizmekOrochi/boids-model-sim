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

inline int speciesTier(BoidSpecies s) {
    int v = static_cast<int>(s);
    return (v < 10) ? 1 : (v < 100) ? 2 : 3;
}

inline bool fear(BoidSpecies subject, BoidSpecies other) {
    int subjectTier = speciesTier(subject);
    int otherTier = speciesTier(other);
    return (subjectTier == otherTier) ? false : (otherTier > subjectTier);
}

inline bool canEat(BoidSpecies predator, BoidSpecies prey) {
    int subjectTier = speciesTier(predator);
    int otherTier = speciesTier(prey);
    return (subjectTier == 3) ? true : (subjectTier == 2) ? otherTier == 1 : false;
}

inline bool canBeEatenBy(BoidSpecies prey, BoidSpecies predator) {
    return canEat(predator, prey);
}

}

#endif
