#include "keyinput.h"

#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>
#include <errno.h>
#include <QtCore>

KeyInput::KeyInput(QObject *parent) : QObject(parent)
{
    pressed_btns = 0;
    fd = open("/dev/buttons", 0);
    if(fd > 0)
    {
        qDebug()<<"open /dev/buttons"<<fd;
        notifier = new QSocketNotifier(fd, QSocketNotifier::Read, this);
        connect(notifier, &QSocketNotifier::activated, this, &KeyInput::readData);
    }
}

KeyInput::~KeyInput()
{
    if(fd > 0)
    {
        close(fd);
        delete notifier;
    }
}

void KeyInput::readData(int socket)
{
    char current_buttons[num_of_btns];
    int count_of_changed_key;
    int i;
    if (read(socket, current_buttons, num_of_btns) != sizeof current_buttons)
    {
        perror("read buttons:");
        return;
    }
    pressed_btns = 0;
    for (i = 0, count_of_changed_key = 0; i < num_of_btns; i++)
    {
        pressed_btns |= (current_buttons[i] - '0') << i;
        if (buttons[i] != current_buttons[i])
        {
            buttons[i] = current_buttons[i];
            emit keyPressed(i + 1, buttons[i] == '1');
            count_of_changed_key++;
        }
    }
    emit keyChanged(pressed_btns);
}

