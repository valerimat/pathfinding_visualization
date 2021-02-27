#include "MainWindow.h"
#include <iostream>
#include "Macros.h"

int main()
{
	while (1)
	{
		int number;
		std::cout << "Choose the algorithm you want (inserte the wanted number and press enter)\n"
			<< "0 - Exit \n1 - BFS\n2 - DFS \n3 - Dijikstra \n4- A*\n";
		std::cin >> number;

		//clear:
		std::cout << "\x1B[2J\x1B[H";

		if (number == 0)
			exit(EXIT_SUCCESS);

		MainWindow::Run((Algorithm)number);
	}
	return 0;
}