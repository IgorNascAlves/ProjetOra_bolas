#include "mainwindow.h"
#include "ui_mainwindow.h"


using namespace std;

void MainWindow::lerArquivo(){
    vector<string> v;

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
}

void MainWindow::PlotGrafico(QVector<double> vx, QVector<double> vy,QString x, QString y, int i){
    // create graph and assign data to it:
    ui->qcustomplot->addGraph();
    if(i == 0)
        ui->qcustomplot->graph(i)->setPen(QPen(Qt::green));
    if(i == 1)
        ui->qcustomplot->graph(i)->setPen(QPen(Qt::blue));
    if(i == 2)
        ui->qcustomplot->graph(i)->setPen(QPen(Qt::red));
    ui->qcustomplot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    //ui->qcustomplot->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->qcustomplot->graph(i)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssPlusCircle, 4));
    ui->qcustomplot->graph(i)->setData(vx,vy);
    // give the axes some labels:
    ui->qcustomplot->xAxis->setLabel(x);
    ui->qcustomplot->yAxis->setLabel(y);
    // set axes ranges, so we see all data:
    ui->qcustomplot->xAxis->setRange(vx.first(), vx.last());
    ui->qcustomplot->yAxis->setRange(vy.first(), vy.last());
    ui->qcustomplot->replot();
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    lerArquivo();
    PlotGrafico(vx,vy,"x","y",0);
    PlotGrafico(vx,vt,"x","t",1);
    PlotGrafico(vy,vt,"y","t",2);

}

MainWindow::~MainWindow()
{
    delete ui;
}
