#include "ift.h"
#include <limits>
#include <iostream>
using namespace std;

IFT::IFT()
{
}

vector<PixelNode*> IFT::transform_4adj(QImage image, int (*cost_function)(PixelNode *, int *, const int))
{
    const int imageRows = image.height();
    const int imageCols = image.width();
    int cost_matrix[imageRows*imageCols];
    PixelNode *matrix[imageRows][imageCols];
    vector<PixelNode*> priority_queue;

    for (int i = 0; i < imageRows; i++)
    {
        for (int j = 0; j < imageCols; j++)
        {
            PixelNode *newNode = new PixelNode(NULL, NULL, 0, i, j, qRed(image.pixel(j,i)));

            newNode->setCost((*cost_function)(newNode, cost_matrix, imageCols));
            newNode->setPathRoot(newNode);
            matrix[i][j] = newNode;
            cost_matrix[i*imageCols + j] = newNode->getCost();
            if (newNode->getCost() < INT_MAX)
            {
                priority_queue.push_back(newNode);
            }
        }
    }

    std::make_heap(priority_queue.begin(), priority_queue.end(), pixelNodeComparer);

    while (! priority_queue.empty())
    {
        PixelNode *s = priority_queue.front();
        std::pop_heap(priority_queue.begin(), priority_queue.end(), pixelNodeComparer); priority_queue.pop_back();
        cout << s->getCost() << endl;
        int j;
        for (int i = max(0, s->getRow() - 1); i <= min(imageRows - 1, s->getRow() + 1); i += 2)
        {
            j = s->getCol();
                PixelNode *t = matrix[i][j];
                PixelNode *oldParent = t->getPredecessor();

                t->setPredecessor(s);
                int newCost = (*cost_function)(t, cost_matrix, imageCols);
                if (newCost < t->getCost())
                {
                    cout << "\tLinked!" << endl;
                        t->setPredecessor(oldParent);
                        vector<PixelNode*>::iterator pos = std::find(priority_queue.begin(), priority_queue.end(), t);
                        if (pos != priority_queue.end())
                        {
                            priority_queue.erase(pos);
                        }
                        t->setCost(newCost);
                        t->setPredecessor(s);
                        cost_matrix[t->getRow() * imageCols + t->getCol()] = newCost;
                        t->setPathRoot(s->getPathRoot());
                        priority_queue.push_back(t);
                        make_heap(priority_queue.begin(), priority_queue.end(), pixelNodeComparer);


                }
                else { t->setPredecessor(oldParent);}
            }

    int i;
    for (int j = max(0, s->getCol() - 1); j <= min(imageCols - 1, s->getCol() + 1); j += 2)
    {
        i = s->getRow();
            PixelNode *t = matrix[i][j];
            PixelNode *oldParent = t->getPredecessor();

            t->setPredecessor(s);
            int newCost = (*cost_function)(t, cost_matrix, imageCols);
            if (newCost < t->getCost())
            {
                cout << "\tLinked!" << endl;
                    t->setPredecessor(oldParent);
                    vector<PixelNode*>::iterator pos = std::find(priority_queue.begin(), priority_queue.end(), t);
                    if (pos != priority_queue.end())
                    {
                        priority_queue.erase(pos);
                    }
                    t->setCost(newCost);
                    t->setPredecessor(s);
                    cost_matrix[t->getRow() * imageCols + t->getCol()] = newCost;
                    t->setPathRoot(s->getPathRoot());
                    priority_queue.push_back(t);
                    make_heap(priority_queue.begin(), priority_queue.end(), pixelNodeComparer);


            }
            else { t->setPredecessor(oldParent);}
        }
    }

    cout << "Ended!" << endl;
    vector<PixelNode*> final;
    for (int i = 0; i < imageRows; i++)
        for (int j = 0; j < imageCols; j++)
        {
            if (matrix[i][j]->getPathRoot() == matrix[i][j])
            {
                final.push_back(matrix[i][j]);
            }
        }
    return final;
}

bool IFT::pixelNodeComparer(PixelNode *a, PixelNode *b)
{
    return a->getCost() > b->getCost();
}
