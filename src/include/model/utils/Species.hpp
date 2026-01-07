#ifndef SPECIES_HPP
#define SPECIES_HPP

#pragma once

namespace bd::Species {
/**
 * @enum BoidSpecies
 * @brief Définit les différentes espèces d'agents disponibles dans la simulation.
 * * Les valeurs numériques sont utilisées pour déterminer le rang dans la chaîne alimentaire :
 * - Rang 1 : Petites proies (Cyan, Vert, Jaune)
 * - Rang 2 : Chasseurs (Bleu)
 * - Rang 3 : Super-prédateurs (Rouge)
 */
enum BoidSpecies {
    CYAN = 1,
    GREEN = 2,
    YELLOW = 3,
    BLUE = 10,
    RED = 100
};

/**
 * @brief Détermine le niveau trophique (rang alimentaire) d'une espèce.
 * * @param s L'espèce à évaluer.
 * @return int Le niveau du rang :
 * - 1 pour les proies de base (Cyan, Vert, Jaune)
 * - 2 pour les chasseurs (Bleu)
 * - 3 pour les prédateurs (Rouge)
 */
inline int speciesTier(BoidSpecies s) {
    int v = static_cast<int>(s);
    if (v < 10) return 1;
    if (v < 100) return 2;
    return 3;
}

/**
 * @brief Détermine le niveau trophique (rang alimentaire) d'une espèce.
 * * @param s L'espèce à évaluer.
 * @return int Le niveau du rang :
 * - 1 pour les proies de base (Cyan, Vert, Jaune)
 * - 2 pour les chasseurs (Bleu)
 * - 3 pour les prédateurs (Rouge)
 */
inline bool fear(BoidSpecies subject, BoidSpecies other) {
    int subjectTier = speciesTier(subject);
    int otherTier = speciesTier(other);

    if (subjectTier == otherTier)
        return false;

    return otherTier > subjectTier;
}

/**
 * @brief Détermine si un prédateur peut manger une proie spécifique.
 * * Les règles sont les suivantes :
 * - Rang 3 (Rouge) mange tout le monde.
 * - Rang 2 (Bleu) ne mange que le Rang 1.
 * - Rang 1 ne mange personne.
 * * @param predator L'espèce chasseresse.
 * @param prey L'espèce ciblée.
 * @return true Si l'interaction résulte en la consommation de la proie.
 */
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

/**
 * @brief Fonction utilitaire pour vérifier si une espèce peut être mangée par une autre.
 * * Sucre syntaxique pour `canEat(predator, prey)`.
 * * @param prey La victime potentielle.
 * @param predator La menace potentielle.
 * @return true Si le prédateur peut manger la proie.
 */
inline bool canBeEatenBy(BoidSpecies prey, BoidSpecies predator) {
    return canEat(predator, prey);
}

}

#endif
