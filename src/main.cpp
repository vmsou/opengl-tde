#include "RenderWindow.hpp"
#include "Geometry/Disc.hpp"
#include "Utils.hpp"
#include "DisplayReader.hpp"
#include "JSONReader.hpp"
#include <fstream>


/* Global variables */
char title[] = "OpenGL-PUC PR (TDE 3)";
std::string display_file;

// Display File
/*
| ID | POSITION | COLOR | DATA (JSON) |

// Objects
| ID | NAME |
  0	   Luz
  1	   Disco	
  2	   Cone
  3    Tetraedro
  4    Cilindro
  5	   Cubo
*/

void info() {
	std::cout << "\nControles:\n";
	std::cout << "Botao Direito - Menu\n";
	std::cout << "F1 - Shade Flat/Smooth\n";
	std::cout << "G - Ativar/Desativar Grid\n";
	std::cout << "C - Ativa/Desativar Cull Face\n";
	std::cout << "R - Resetar Camera\n";
	std::cout << "P - Trocar projeção Ortogonal/Perspectiva\n";
	std::cout << "Setas e Page up/down- Rotacionar Camera\n";
	std::cout << "WASD - Movimentar objeto selecionado\n";
	std::cout << "Roda do mouse - Zoom in/out\n";
}

/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv) {
	std::cout << "Start\n";

	std::cout << "Display File (*.txt): ";
	std::cin >> display_file;

	std::cout << "\nFile: " << display_file << '\n';

	RenderWindow rw = RenderWindow{ title, argc, argv, display_file.c_str() };
	print_version();
	info();

	rw.run();
	std::cout << "\nEnd" << std::endl;
	std::cin.get();
}
