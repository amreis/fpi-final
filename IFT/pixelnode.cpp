#include "pixelnode.h"

PixelNode::PixelNode()
{
}

PixelNode::PixelNode(PixelNode *predecessor, PixelNode *root, int cost, int row, int col, int intensity)
{
    this->predecessor = predecessor;
    this->pathRoot = root;
    this->cost = cost;
    this->pxRow = row;
    this->pxCol = col;
    this->pxIntensity = intensity;
}

int PixelNode::getCol()
{
    return this->pxCol;
}

int PixelNode::getRow()
{
    return this->pxRow;
}

int PixelNode::getCost()
{
    return this->cost;
}

int PixelNode::getIntensity()
{
    return this->pxIntensity;
}

PixelNode * PixelNode::getPathRoot()
{
    return this->pathRoot;
}

PixelNode * PixelNode::getPredecessor()
{
    return this->predecessor;
}

void PixelNode::setCol(int newCol)
{
    this->pxCol = newCol;
}

void PixelNode::setCost(int cost)
{
    this->cost = cost;
}

void PixelNode::setIntensity(int newIntensity)
{
    this->pxIntensity = newIntensity;
}

void PixelNode::setPathRoot(PixelNode *newRoot)
{
    this->pathRoot = newRoot;
}

void PixelNode::setPredecessor(PixelNode *newPred)
{
    this->predecessor = newPred;
}

void PixelNode::setRow(int newRow)
{
    this->pxRow = newRow;
}
