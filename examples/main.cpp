// penser a inactiver la liaison serie en retirant toute reference a la liaison dans fichier /boot/cmdline.txt


#include <iostream>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <unistd.h>
using namespace std;

int main() {
    int fd;
    char caractere = 'W';
    fd = serialOpen("/dev/serial0", 9600);

    if (fd != -1) {
        cout << fd << endl;

        for (;;) {


            //caractere = serialGetchar(fd); //reception sur liaison serie RXD0 du RPI

            serialPutchar(fd, caractere); // reemettre sur TXD du RPI (mode echo)

            cout << caractere << endl; // sans "endl" ca n'affiche pas sur console(ecran)
            delay(1);

        }

    } else {
        cout << fd << endl;
        cout << "Erreur" << endl;
    }
    return 0;

}
