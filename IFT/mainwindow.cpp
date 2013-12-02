#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ift.h"
#include <cmath>
int fsum(PixelNode* node, int*, const int);
#include <iostream>
using std::cout;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_openImageButton_clicked()
{
    //QImage image(ui->imageNameEdit->text());
    QImage image(8, 6, QImage::Format_RGB32);
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 8; j++)
        {
            if (i != 5)
            {
                image.setPixel(j,i, qRgb(5,0,0));
            }
            else if (j == 0 || j == 7)
            {
                image.setPixel(j,i,qRgb(0,0,0));
            }
        }
    if (image.isNull())
        return;
    else
    {
        vector<PixelNode*> result;
        result = IFT::transform_4adj(image, fsum);
        for (vector<PixelNode*>::iterator it = result.begin(); it != result.end(); it++)
        {
            cout << (*it)->getRow() << "," << (*it)->getCol() << endl;
        }
    }
}


int fsum(PixelNode* node, int *cost_table, const int nCols)
{
    if (node->getPredecessor() == NULL)
    {
        if (node->getCol() == 0 || node->getCol() == 7)
        {
            if (node->getRow() == 5)
                return node->getIntensity();
            else return INT_MAX;
        }
        else return INT_MAX;
    }
    else
    {
        int path_cost = cost_table[node->getPredecessor()->getRow() * nCols + node->getPredecessor()->getCol()];
        if (path_cost == INT_MAX) return node->getPredecessor()->getIntensity() + node->getIntensity();
        return cost_table[node->getPredecessor()->getRow() * nCols + node->getPredecessor()->getCol()]
                + node->getIntensity();
    }
}
