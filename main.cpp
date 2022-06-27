#include "DoorControl.h"


using namespace std;
/* Das Programm in Eclipse mittels des Menüeintrags:
 * "Run -> External Tools" -> run in xterm"
 * starten! */
int main ()
{
	// ... maybe insert your class initialization here?
	// example:

	DoorControl control;
	control.run();

    /*Konfiguration config;
    config.Konfiguration_einlesen();
    for (int i = 0; i < 16; ++i) {
        int k = config.sensor_liste.at(i)->getPin();
        std::cout << "Sensor: " << i << "mit Pin: " << k << "\n";
    }*/

return 0;
}
