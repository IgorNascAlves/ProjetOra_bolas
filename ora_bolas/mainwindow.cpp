#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>
#include <fstream>

using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    vector<string> v;
    QVector<double> vt,vx,vy;
    ifstream f;
    f.open("teste.txt", fstream::in);
    //cout<<f.is_open()<<endl;
    string s;

    while(f >> s)
        v.push_back(s);
    f.close();
    //    for(unsigned int i=0;i<v.size();i++)
    //        cout<<v[i]<<endl;
    for(unsigned int i=4;i<v.size()-2;i = i + 4){
        if(v[i][3] == ',')
            vt.push_back((v[i][1]-48)+(v[i][5]-48)/10.0+(v[i][7]-48)/100.0);
        else
            vt.push_back((v[i][1]-48)*10+(v[i][3]-48)+(v[i][7]-48)/10.0+(v[i][9]-48)/100.0);
        vx.push_back((v[i+1][1]-48)+((v[i+1][5]-48)/10.0)+((v[i+1][7]-48)/100.0)+((v[i+1][9]-48)/1000.0));
        vy.push_back((v[i+2][1]-48)+((v[i+2][5]-48)/10.0)+((v[i+2][7]-48)/100.0)+((v[i+2][9]-48)/1000.0));
    }

    // create graph and assign data to it:
    ui->qcustomplot->addGraph();
    ui->qcustomplot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    ui->qcustomplot->graph(0)->setPen(QPen(Qt::blue));
    //ui->qcustomplot->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->qcustomplot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssPlusCircle, 4));
    ui->qcustomplot->graph(0)->setData(vx,vy);
    // give the axes some labels:
    ui->qcustomplot->xAxis->setLabel("x");
    ui->qcustomplot->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    ui->qcustomplot->xAxis->setRange(vx.first(), vx.last());
    ui->qcustomplot->yAxis->setRange(vy.first(), vy.last());
    ui->qcustomplot->replot();
}

MainWindow::~MainWindow()
{
    delete ui;
}
