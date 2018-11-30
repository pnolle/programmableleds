#ifndef FRAGMENT
#define FRAGMENT

class Fragment
{
    protected:
        // animation
        int wait, fade;
        // color
        double hue, hueIncrement;
        int sat, bri;
    public:
        Fragment();
        void setAnimationProperties(int wait, int fade);
        void setColorProperties(double hue, double hueIncrement, int sat, int bri);
        virtual bool nextFrame();
};

#endif 