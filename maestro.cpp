#include "maestro.h"

int Maestro::goHome(Servo * servo) {
    unsigned char command[] = {0xA2, servo->getChannel()};
    if(write(_fd, command, sizeof(command)) == -1) {
        perror("error writing");
        return -1;
    }
    return 0;
}

int Maestro::getError(Servo * servo) {

    unsigned char command[] = {0x93, servo->getChannel()};
    if(write(_fd, command, sizeof(command)) == -1) {
        perror("error writing");
        return -1;
    }

    unsigned char response[2];
    if(read(_fd,response,2) != 2)  {
        perror("error reading");
        return -1;
    }

    if(response[0] == 0x00) {
        return response[0] + 256*response[1];
    }

    return 0;
}

int Maestro::getPosition(Servo * servo) {

    unsigned char command[] = {0x90, servo->getChannel()};
    if(write(_fd, command, sizeof(command)) == -1) {
        perror("error writing");
        return -1;
    }

    unsigned char response[2];
    if(read(_fd,response,2) != 2)  {
        perror("error reading");
        return -1;
    }

    return response[0] + 256*response[1];
}

int Maestro::setPosition(Servo * servo, unsigned short target) {

    if (target > servo->getMax()) { target = servo->getMax(); }
    if (target < servo->getMin()) { target = servo->getMin(); }

    unsigned char command[] = {0x84, servo->getChannel(), static_cast<unsigned char>(target & 0x7F), static_cast<unsigned char>(target >> 7 & 0x7F)};

    if (write(_fd, command, sizeof(command)) == -1) {
        perror("error writing");
        return -1;
    }

    return 0;
}

int Maestro::stepUp(Servo* servo, int value) {
    return setPosition(servo, getPosition(servo)+value);
}

int Maestro::stepDown(Servo* servo, int value) {
    return setPosition(servo, getPosition(servo)-value);
}

bool Maestro::isMoving(Servo * servo){

    unsigned char command[] = {0x93, servo->getChannel()};
    if(write(_fd, command, sizeof(command)) == -1) {
        perror("error writing");
        return -1;
    }

    unsigned char response[1];
    if(read(_fd, response, 1) != 1)  {
        perror("error reading");
        return -1;
    }

    return response[0] == 0x01;
}
