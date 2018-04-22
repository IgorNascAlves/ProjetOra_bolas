#include<string>
#include<cstring>
#include<vector>
#include<fstream>
#include<iostream>
#include<cstdlib>
using namespace std;
struct _pontos{
    char nome[50];
    float x;
    float y;
};
typedef struct _pontos pontos;
void criaHTML(char* str){

    FILE * Stream;
    FILE * Stream2;
    char buffer [1000];

    Stream = fopen ("inicio.txt","r");
    Stream2 = fopen ("index.html","w+");
    while ( ! feof (Stream) )
    {
        if ( fgets (buffer , 100 , Stream) == NULL ) break;{
            fputs(buffer , Stream2);
        }
    }
    fclose (Stream);

    fputs (str,Stream2);

    Stream = fopen ("fim.txt","r");
    while ( fgets (buffer , 100 , Stream) != NULL ){
        fputs(buffer , Stream2);
    }
    fclose (Stream);
    fclose (Stream2);
}
void entradaHTML(vector<double> vt,vector<double> vx,vector<double> vy){
    char str[100*vt.size()];
    char temp[100*vt.size()];
    int i;
    for(i=0;i<1000;i++){
        str[i] = '\0';
        temp[i] = '\0';
    }
    for(unsigned int i=0;i<vt.size();i++){
        sprintf(temp, "[%f , %f, %f ], \n", vt[i],vx[i], vy[i]);
        strcat(str,temp);
    }
    criaHTML(str);

}
void lerArquivo(vector<double> &vt,vector<double> &vx,vector<double> &vy){
    vector<string> v;

    ifstream f;
    f.open("Ora_bolas-trajetoria _bola_oficial.txt", fstream::in);
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
int main(){
    vector<double> vt,vx,vy;
    lerArquivo(vt,vx,vy);
    entradaHTML(vt,vx,vy);
    //    for(int i=0;i<vt.size();i++)
    //        cout<<vt[i]<<" "<<vx[i]<<" "<<vy[i]<<endl;
    system("start index.html");
    return 0;
}
