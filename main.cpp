#include "Sniffer.hpp"

int main() {
	unsigned int inPort, outPort;

	RtMidiIn midiin;
	for (int i = 0; i < midiin.getPortCount(); ++i)
		std::cout << i << " " << midiin.getPortName(i) << std::endl;
	std::cout << "Choose input port: ";
	std::cin >> inPort;
	std::cout << std::endl;

	RtMidiOut midiout;
	for (int i = 0; i < midiout.getPortCount(); ++i)
		std::cout << i << " " << midiout.getPortName(i) << std::endl;
	std::cout << "Choose output port: ";
	std::cin >> outPort;
	std::cout << std::endl;

	Sniffer sniff{"piwo", inPort, outPort};
	sniff.join();
}