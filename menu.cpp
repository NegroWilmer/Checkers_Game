#include <iostream>
#include "checkers.h"


void mostrarMenu() {
    int opcion;

    do {
        std::cout << "\n=== JUEGO DAMAS ===" << std::endl;
        std::cout << "1. Jugar Damas" << std::endl;
		std::cout << "2. Reglas del juego" << std::endl;
        std::cout << "3. Salir" << std::endl;
        std::cout << "Elige una opcion: ";
        std::cin >> opcion;

        switch (opcion) {
        case 1:
			std::cout << "\n=== Iniciando el juego de Damas ===" << std::endl;
            jugarDamas(); 
            break;
        case 2:
            std::cout << "\n=== Reglas del Juego de Damas ===" << std::endl;
            std::cout << "1. El juego se juega en un tablero de 10x10." << std::endl;
            std::cout << "2. Cada jugador comienza con 20 piezas." << std::endl;
            std::cout << "3. Las piezas se mueven diagonalmente hacia adelante." << std::endl;
            std::cout << "4. Si una pieza alcanza el otro lado del tablero, se convierte en dama." << std::endl;
            std::cout << "5. El objetivo es capturar todas las piezas del oponente." << std::endl;
			std::cout << "6. EL rey se puede mover diagonalmente." << std::endl;
			std::cout << "7. Para mover una pieza, ingresa las coordenadas de origen y destino (1 4) (2 3)." << std::endl;
			break;
        case 3:
            std:: cout << "Saliendo del juego..." << std:: endl;
            break;
        default:
            std:: cout << "Opcion invalida. Intenta de nuevo." << std::endl;
        }
    } while (opcion != 3);
}

int main() {
    mostrarMenu(); 
    return 0;
}
