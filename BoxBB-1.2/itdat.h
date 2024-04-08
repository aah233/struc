#ifndef __ITDAT__
#define __ITDAT__

struct iTDAT // Temporal data to kv
{
    PBOX pBIncumb; // For Incombent
    PBOX pBPoint;  // For centoid, bumman, etc
    ub::vector<double> rVector;
};
#endif /*__BOX__*/