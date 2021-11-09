#include "RenderWindow.hpp"
#include "Geometry/Disc.hpp"
#include "Utils.hpp"
#include "DisplayReader.hpp"
#include "JSONReader.hpp"
#include <fstream>


/* Global variables */
char title[] = "OpenGL-PUC PR (TDE 3)";

void info() {
	std::cout << "\nControles:\n";
	std::cout << "F1 - Shade Flat/Smooth\n";
	std::cout << "F2 - Rotacionar Camera/Objeto\n";
	std::cout << "G - Ativar/Desativar Grid\n";
	std::cout << "L - Ativar/Desativar Iluminacao\n";
	std::cout << "C - Ativa/Desativar Cull Face\n";
	std::cout << "R - Resetar Camera\n";
	std::cout << "WASD ou Setas e Page up/down- Rotacionar Camera/Objeto\n";
	std::cout << "Roda do mouse - Zoom in/out\n";
}

/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv) {
	std::cout << "Start\n";

	RenderWindow rw = RenderWindow{ title, argc, argv };
	print_version();
	info();

	rw.run();
	std::cout << "\nEnd" << std::endl;
	std::cin.get();
}