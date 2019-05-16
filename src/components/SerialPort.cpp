#include "SerialPort.h"

using namespace std;


SerialPort::SerialPort() {

}

int SerialPort::open(const char *device, int baud) {
    m_fd = serialOpen(device, baud);

    if (m_fd == -1)
        LOG_F(ERROR, "Failed to open serial port, errno : %d", errno);
    else
        LOG_F(INFO, "Success opening serial port (m_fd = %d)", m_fd);

    //wiringPiSetup();
    usleep(10000);
    return m_fd;
}


void SerialPort::close() {
    if (m_fd != -1)
        serialClose(m_fd);
}

bool SerialPort::putchar(char c) {
    bool retour = false;
    if (m_fd != -1) {
        if (write(m_fd, &c, 1) == 1)
            retour = true;
        else
            retour = false;
    }
    return retour;
}

bool SerialPort::puts(const char *command) {
    if (m_fd != -1) {
        int nb_bytes_written = write(m_fd, command, strlen(command));

        if (nb_bytes_written == strlen(command)){
            LOG_F(INFO, "Successful writing command %s, %d bytes written", command, nb_bytes_written);
            return true;
        }
        else if (nb_bytes_written == -1)
            LOG_F(ERROR, "Could not write command %s, errno : %d", command, errno);
        else
            LOG_F(ERROR, "Could not write command %s, %d bytes written", command, nb_bytes_written);
    } else
        LOG_F(ERROR, "Serial port not opened (m_fd = -1), could not send command %s", command);

    return false;
}

int SerialPort::dataAvailable() {
    if (m_fd != -1)
        return serialDataAvail(m_fd);
    else {
        LOG_F(ERROR, "serial connection error : m_fd = -1, returned 0 as dataAvailable");
        return 0;
    }
}

bool SerialPort::getchar(char *c) {
    bool retour = false;
    if (m_fd != -1) {
        if (read(m_fd, c, 1) == 1)
            retour = true;
    }
    return retour;
}

bool SerialPort::gets(char *reponse, unsigned int taille) {
    bool retour = false;
    int nbCarRecu = 0;
    if (m_fd != -1) {
        nbCarRecu = read(m_fd, reponse, taille);
        if (nbCarRecu > 0) {
            reponse[nbCarRecu] = '\0';
            retour = true;
        } else
            retour = false;
    }
    return retour;
}

void SerialPort::flush() {
    if (m_fd != -1) {
        serialFlush(m_fd);
    }
}
