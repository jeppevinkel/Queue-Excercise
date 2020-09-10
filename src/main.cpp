#include <iostream>
#include "queue.hpp"

int main(int argc, char *argv[])
{
	Queue<4, char> charQueue1;
	Queue<4, char> charQueue2;
	Queue<64, int> intQueue;

	char output;
	int intOutput;

	charQueue1.putSafe('H');
	charQueue1.putSafe('e');
	charQueue1.putSafe('l');
	charQueue1.putSafe('l');
	charQueue1.putSafe('o');

	charQueue2.put('H');
	charQueue2.put('e');
	charQueue2.put('l');
	charQueue2.put('l');
	charQueue2.put('o');

	int i = 0;
	while (intQueue.putSafe(i++)) { }
	
	std::cout << "Safe put: ";
	while(charQueue1.take(&output))
		std::cout << output;
	std::cout << std::endl;

	std::cout << "Unsafe put: ";
	while(charQueue2.take(&output))
		std::cout << output;

	std::cout << std::endl << std::endl << "[" << intQueue.type()->name() << "] " << "IntQueue: [";
	while (intQueue.take(&intOutput))
		std::cout << intOutput << ", ";
	std::cout << "]";

	std::cout << std::endl << std::endl;
}