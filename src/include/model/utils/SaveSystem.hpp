#ifndef SAVESYSTEM_HPP
#define SAVESYSTEM_HPP

#include <string>

#include "../Simulation.hpp"

namespace bd {

    /**
     * @brief Gère la sérialisation et la désérialisation de l'état de la simulation.
     *
     * La classe SaveSystem fournit des fonctions statiques pour persister et restaurer
     * l'état d'une Simulation. Elle est responsable de la sauvegarde et du chargement
     * des dimensions du monde et de l'état des boids (position et orientation) depuis
     * et vers un fichier externe.
     */
    class SaveSystem {
    public:
        /**
         * @brief Sauvegarde l'état actuel de la simulation dans un fichier.
         *
         * Cette fonction écrit les dimensions du monde et la liste des boids
         * (incluant leurs positions et directions de vitesse normalisées)
         * dans le fichier spécifié.
         *
         * @param simulation La simulation à sauvegarder.
         * @param filename Chemin vers le fichier de sortie.
         * @return True si l'opération de sauvegarde a réussi, false sinon.
         */
        static bool save(const Simulation& simulation, const std::string& filename);

        /**
         * @brief Charge un état de simulation depuis un fichier.
         *
         * Cette fonction lit les dimensions du monde et les données des boids depuis le
         * fichier spécifié et reconstruit l'état de la simulation.
         *
         * @param simulation La simulation à modifier avec les données chargées.
         * @param filename Chemin vers le fichier d'entrée.
         * @return True si l'opération de chargement a réussi, false sinon.
         */
        static bool load(Simulation& simulation, const std::string& filename);
    };

}

#endif