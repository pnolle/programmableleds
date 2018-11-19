#ifndef FRAGMENT
#define FRAGMENT

class Fragment
{
    public:
        Fragment();
        void setAnimationProperties(int wait, int fade);
        void setColorProperties(double hue, double hueIncrement, int sat, int bri);
        void nextFrame();
};

#endif 