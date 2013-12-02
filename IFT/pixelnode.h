#ifndef PIXELNODE_H
#define PIXELNODE_H

class PixelNode
{
public:
    PixelNode();
    PixelNode(PixelNode* predecessor, PixelNode *root, int cost, int row, int col, int intensity);
    PixelNode *getPathRoot();
    PixelNode *getPredecessor();
    int getCost();
    int getCol();
    int getRow();
    int getIntensity();

    void setPathRoot(PixelNode* newRoot);
    void setPredecessor(PixelNode* newPred);
    void setCost(int cost);
    void setRow(int newRow);
    void setCol(int newCol);
    void setIntensity(int newIntensity);

private:
    PixelNode *pathRoot;
    PixelNode *predecessor;
    int cost;
    int pxRow;
    int pxCol;
    int pxIntensity;
};

#endif // PIXELNODE_H
