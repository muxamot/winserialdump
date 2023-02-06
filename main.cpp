#include <iostream>
#include <string>
#include "serial.hpp"
#include "dumper.hpp"

std::string port = "COM4";	   // имя порта
std::string file = "dump.txt"; // имя файла, в который записывается вывод
bool console_log = true;	   // true если нужно выводить также в консоль

/*

	Функция main()

*/

int main()
{
	// Ввод названия порта для чтения
	std::cout << "Enter port name (COM4 for example): ";
	std::cin >> port;

	// Чтение с ардуино на выбранном порту
	arduinoDumper(port, file, console_log);

	// Удобный выход из программы
	std::cout << "Press ESC to exit programm..." << std::endl;
	while (true)
	{
		if (GetAsyncKeyState(VK_ESCAPE) == -32767) // выход по escape
		{
			break;
		}
	}

	return 0;
}