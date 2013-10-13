#ifndef __servo__
#define __servo__

class Servo {

private:
    unsigned char _channel;
    unsigned int  _min;
    unsigned int  _max;

public:
    Servo(unsigned char c, unsigned int mn, unsigned int mx) :_channel(c), _min(mn), _max(mx){}

    unsigned char getChannel() { return _channel; }
    unsigned int  getMin() { return _min; }
    unsigned int  getMax() { return _max; }

};

#endif