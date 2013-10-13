## C++ Wrapper for Pololu Maestro Servo Controller

Extension of the [Cross-platform C](http://www.pololu.com/docs/0J40/5.h.1) example into a C++ wrapper which implements the full serial servo [command protocol](http://www.pololu.com/docs/0J40/5.e).

Only tested on OS X and Linux.

## Sample code

This is an example of how to use this library:

```c++
#include "maestro.h"

#ifdef __APPLE__
#define MAESTRO_DEVICE "/dev/cu.usbmodem00065291"
#else
#define MAESTRO_DEVICE "/dev/ttyACM0"
#endif

using namespace std;

int main(int argc, const char * argv[])
{
    try
    {
        Maestro maestro(MAESTRO_DEVICE);

        Servo horizontalServo(0, 3968, 9216);

        maestro.goHome(&horizontalServo);

    } catch (std::exception& e)
    {
        cout << e.what() << endl;
    }

    return EXIT_SUCCESS;
}

```

## Contributors

* [Neil Ang](https://github.com/neilang)
* [Val Lyashov](https://github.com/vly)
* [Yuan Yang](https://github.com/AlfredYang1986)
