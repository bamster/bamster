// vim: set ts=4 sw=4 expandtab sts=4:
#ifndef BAMSTER_H_INCLUDED
#define BAMSTER_H_INCLUDED


class bamster {
    private:
        // Position of the bamster
        float bamsterPos[2];
        // Velocity of the bamster
        float bamsterVel[2];
    public:
        float bamsterPos();
        float bamsterVel();

}

#endif
