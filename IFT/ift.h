#ifndef IFT_H
#define IFT_H

#include <vector>
#include <algorithm>
#include <QImage>
#include "pixelnode.h"

using namespace std;

class IFT
{
public:
    IFT();
    static vector<PixelNode*> transform_4adj(QImage image, int (*cost_function)(PixelNode*, int*, const int));
private:
    static bool pixelNodeComparer(PixelNode*, PixelNode*);
};

#endif // IFT_H
