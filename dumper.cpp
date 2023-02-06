#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "serial.hpp"
#include "dumper.hpp"

using std::cout;
using std::endl;

// строка для данных
char incomingData[MAX_DATA_LENGTH];

/*

	Функция, сохраняющая вывод с ардуино в файл

*/

void arduinoDumper(const std::string &port_name, const std::string &file_name, bool echo)
{
	// Подключение
	std::string pname = "\\\\.\\" + port_name;
	SerialPort arduino((char *)pname.c_str());
	if (arduino.isConnected())
		cout << "Connection Established" << endl;
	else
		cout << "ERROR, check port name" << endl;

	if (arduino.isConnected())
	{
		std::cout << std::endl
				  << "Dumping to file dump.txt" << std::endl;
		std::cout << "Press ESC to stop!" << std::endl
				  << std::endl;
	}

	// Открытие файла
	std::ofstream fl(file_name);

	// Пока Arduino подключено
	while (arduino.isConnected())
	{
		// Ожидание
		Sleep(10);

		// чтение данных, bytes_read - количество прочитанных байт
		int bytes_read = arduino.readSerialPort(incomingData, MAX_DATA_LENGTH);

		// вывод в файл и консоль
		if (bytes_read > 0)
		{
			fl << std::string(incomingData);
			if (echo)
				puts(incomingData);
		}

		if (GetAsyncKeyState(VK_ESCAPE) == -32767) // выход из цикла по escape
		{
			break;
		}
	}

	// Закрытие файла
	std::cout << "Closing file dump.txt" << std::endl;
	fl.flush();
	fl.close();
}