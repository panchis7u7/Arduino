#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <termios.h>

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "Serial por name not given!" << std::endl;
        exit(0);
    }

    char *deviceName = argv[1];
    std::cout << "Serial port: " << deviceName << " selected!" << std::endl;

    int fd = 0;
    if ((fd = open(deviceName, O_RDWR | O_NOCTTY)) < 0)
    {
        std::cerr << "Error opening serial port!."
                  << "\n";
        exit(0);
    }

    fsync(fd);
    struct termios options;
    int result = tcgetattr(fd, &options);
    if (result)
    {
        std::cerr << ("tcgetattr failed") << "\n";
        close(fd);
        return -1;
    }

    options.c_iflag &= ~(INLCR | IGNCR | ICRNL | IXON | IXOFF);
    options.c_oflag &= ~(ONLCR | OCRNL);
    options.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);

    // Set up timeouts: Calls to read() will return as soon as there is
    // at least one byte available or when 100 ms has passed.
    options.c_cc[VTIME] = 1;
    options.c_cc[VMIN] = 0;

    cfsetospeed(&options, B9600);
    cfsetispeed(&options, cfgetospeed(&options));

    result = tcsetattr(fd, TCSANOW, &options);
    if (result)
    {
        std::cerr << ("tcsetattr failed") << "\n";
        close(fd);
        return -1;
    }

    sleep(2);

    char encendido[10] = "encendido";
    if (write(fd, encendido, strlen(encendido)) < 0)
    {
        std::cerr << "Error de escritura al dispositivo!." << std::endl;
        close(fd);
        exit(0);
    }

    sleep(2);

    char apagado[8] = "apagado";
    if (write(fd, apagado, strlen(apagado)) < 0)
    {
        std::cerr << "Error de escritura al dispositivo!." << std::endl;
        close(fd);
        exit(0);
    }

    sleep(2);

    close(fd);
    return 0;
};