#ifndef GAMEPLAY_H
#define GAMEPLAY_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Personaje.h"
#include "TileMap.h"
#include "GUI.h"
#include "Enunciado.h"
#include "Ranking.h"

enum ESTADO{
    juegoEnCurso,
    tablaPuntos,
    nuevoRecord,
    ranking,
    volverAlMenu

};
class Gameplay
{
    private:
        GUI gui;
        Personaje pj;
        Enunciado enun;
        bool entroUnaVez = false;
        TileMap _Map, _Gem, _Oscuridad;
        int estado = ESTADO::juegoEnCurso;
        bool _endGame = false; /// en la colision de gemas cambia la variable _endGame a true si el pj está en el tile 12 (final).
        ///Archivos
        Ranking obj;
    public:
        Gameplay();
        ~Gameplay();
        void AccessMovePJ();
        sf::RectangleShape& getPrintPERSONAJE();
        TileMap& getOscuridadprint();
        TileMap& getMapprint();
        TileMap& getGemMapprint();
        int setMap();
        void checkcollisionPARED();
        bool checkcollisionGEMAS(sf::Vector2i PosPJ, int x = 0, int y = 0);
        void printJuego(sf::RenderWindow& window);
        inline void CheckEndGame();
        void iluminar(int,int);
};
#endif // GAMEPLAY_H
