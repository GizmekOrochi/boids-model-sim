#ifndef VIEW3D_HPP
#define VIEW3D_HPP

#include <SFML/Graphics.hpp>
#include "../model/utils/Vec2.hpp"
#include "../model/utils/Vec3.hpp"
#include "../model/utils/Species.hpp"
#include "utils/Camera.hpp"

namespace bd {

/**
 * @struct Face
 * @brief Représente une face triangulaire dans un maillage 3D.
 * * Contient les indices des 3 sommets (vertices) qui composent le triangle.
 * Utilisé pour dessiner des formes solides (boids, vaisseaux) via des listes de sommets.
 */
struct Face {
    int a, b, c;
};

/**
 * @class View3D
 * @brief Moteur de rendu 3D simplifié ("Software Renderer").
 * * Cette classe gère toute la pipeline graphique : transformation du monde vers la caméra,
 * projection perspective (3D -> 2D) et dessin des primitives (lignes, triangles)
 * directement via SFML.
 */
class View3D {
public:
    /**
     * @brief Constructeur du moteur de vue.
     * @param w Largeur de la zone de rendu (viewport) en pixels.
     * @param h Hauteur de la zone de rendu (viewport) en pixels.
     */
    View3D(int w, int h);

    /**
     * @brief Récupère l'objet Caméra pour le contrôler.
     * @return Référence modifiable vers la caméra (permet de changer position/rotation).
     */
    Camera& getCamera();

    /**
     * @brief Met à jour les dimensions de la fenêtre de rendu.
     * * À appeler lorsque la fenêtre est redimensionnée pour éviter les déformations.
     */
    void setViewport(int w, int h);

private:
    Camera camera; ///< L'observateur dans la scène 3D.
    int width;     ///< Largeur de l'écran.
    int height;    ///< Hauteur de l'écran.

    /**
     * @brief Facteur de champ de vision (Field of View).
     * * Simule la distance focale. Plus la valeur est élevée, plus le zoom est fort.
     */
    float fovPixels = 520.f;

    /**
     * @brief Plan de découpe proche (Near Clipping Plane).
     * * Les objets dont le Z est inférieur à cette valeur ne sont pas affichés
     * (pour éviter les divisions par zéro ou l'affichage d'objets derrière la tête).
     */
    float nearZ = 0.1f;

    /**
     * @brief Dessine une ligne 3D projetée sur l'écran 2D.
     * * Convertit les coordonnées 3D en 2D et appelle le dessin de ligne SFML.
     */
    void drawLine3D(sf::RenderWindow& win, const Vec3<float>& a, const Vec3<float>& b, sf::Color color);

    /**
     * @brief Dessine un triangle 3D (généralement en fil de fer ou rempli selon l'implémentation).
     * * Relie 3 points 3D entre eux.
     */
    void drawTriangle3D(sf::RenderWindow& win, const Vec3<float>& a, const Vec3<float>& b, const Vec3<float>& c,sf::Color color);


public:
    /**
     * @brief Transforme un point de l'espace Monde vers l'espace Caméra.
     * * Applique la translation (position caméra) et la rotation (yaw/pitch) inversées.
     * @param p Point dans le monde.
     * @return Point relatif à la caméra.
     */
    Vec3<float> worldToCamera(const Vec3<float>& p) const;

    /**
     * @brief Projette un point de l'espace Caméra vers l'espace Écran (2D).
     * * Applique la division perspective (x / z).
     * @param camP Point dans l'espace caméra.
     * @param out [Sortie] Coordonnées 2D sur l'écran (pixels).
     * @param outZ [Sortie] La profondeur Z originale (utile pour le Z-sorting si besoin).
     * @return bool False si le point est derrière la caméra (ne doit pas être dessiné), True sinon.
     */
    bool projectToScreen(const Vec3<float>& camP, Vec2<float>& out, float& outZ) const;

    /**
     * @brief Dessine un agent (Boid) ou un vaisseau (ex: TIE Fighter).
     * * Construit la géométrie locale orientée selon le vecteur direction.
     * @param position Position du boid dans le monde.
     * @param direction Vecteur vitesse/direction du boid.
     * @param BoidSpecie L'espèce du boid (détermine la couleur).
     */
    void drawBoid(sf::RenderWindow& win, const Vec3<float>& position, const Vec3<float>& direction, Species::BoidSpecies BoidSpecie);

    /**
     * @brief Dessine un obstacle cubique en fil de fer.
     * @param position Centre de l'obstacle.
     * @param sizeX, sizeY, sizeZ Dimensions de l'obstacle.
     */
    void drawObstacle(sf::RenderWindow& win, const Vec3<float>& position, int sizeX, int sizeY, int sizeZ);

    /**
     * @brief Dessine la cage délimitant le monde (limites de la simulation).
     * * Affiche généralement une boîte englobante et une grille au sol/plafond pour donner des repères visuels.
     */
    void drawWorldCage(sf::RenderWindow& win);

};

}

#endif