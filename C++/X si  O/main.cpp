#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstring>

using namespace std;

int i,j,turn=1,x,coin,y,nr=0,p;

char v[10][10],chr;

bool ok,win,play;

void ver();

int main()
{
    play=true;
    while(play){
    cout<<"Press any key to flip the coin!"<<'\n';
    srand(time(0));
    
    cin.get();
    
    coin=(rand()%2)+1;
    if(coin==1)
        cout<< "You are X."<<'\n'<<'\n';
    else
        cout<< "You are O."<<'\n'<<'\n';
    cout<<"Type the coordinates of X or O (first the row, then to column):\n ";
    for(i=1;i<=3;i++)
        for(j=1;j<=3;j++)
            v[i][j]=' ';
    ok=false;
    while(!ok&&nr<9)
    {
        if(turn>0)
        {
            cout<<"X's turn: ";
            cin>>x>>y;
            cout<<'\n';
            while(v[x][y]!=' ')
                cin>>x>>y;
            system("clear");
            v[x][y]='X';
            turn*=(-1);
            nr++;
        }
        else
        {
            cout<<"O's turn: ";
            cin>>x>>y;
            cout<<'\n';
            while(v[x][y]!=' ')
                cin>>x>>y;
            system("clear");
            v[x][y]='O';
            turn*=(-1);
            nr++;
        }
        cout<<' ';
        for(i=1;i<=3;i++)
        {
            for(j=1;j<=3;j++)
                cout<<v[i][j]<<' ';
            cout<<'\n'<<' ';
        }
        cout<<'\n';
        if(nr>=5)
        {
            ver();
            if(win)
            {
                if(chr=='X')
                    cout<<"X wins!"<<'\n';
                else
                    cout<<"O wins!"<<'\n';
                ok=true;
            }
        }
        if(!ok&&nr==9)
            cout<<"It's a Draw! \n"<<'\n';
    }
     cout<<"If you want to play again press 'a',else press 'q'.\n";
     char e;
     cin>>e;

     system("clear");
     if(e=='q')
        play=false;
    }

    return 0;
}


void ver()
{
    win=false;
    for(p=1;p<=8&&!win;p++)
    {
        switch(p)
        {
            case 1:
            {
                if(v[1][1]!=' '&&(v[1][1]==v[1][2]&&v[1][1]==v[1][3]))
                {
                    win=true;
                    chr=v[1][1];
                }
                break;
            }
            case 2:
            {
                if(v[2][1]!=' '&&(v[2][1]==v[2][2]&&v[2][1]==v[2][3]))
                {
                    win=true;
                    chr=v[2][1];
                }
                break;
            }
            case 3:
            {
               if(v[3][1]!=' '&&(v[3][1]==v[3][2]&&v[3][1]==v[3][3]))
                {
                    win=true;
                    chr=v[3][1];
                }
                break;
            }
            case 4:
            {
                if(v[1][1]!=' '&&(v[1][1]==v[2][1]&&v[1][1]==v[3][1]))
                {
                    win=true;
                    chr=v[1][1];
                }
                break;
            }
            case 5:
            {
                if(v[1][2]!=' '&&(v[1][2]==v[2][2]&&v[1][2]==v[3][2]))
                {
                    win =true;
                    chr=v[1][2];
                }
                break;
            }
            case 6:
            {
                if(v[1][3]!=' '&&(v[1][3]==v[2][3]&&v[1][3]==v[3][3]))
                {
                    win=true;
                    chr=v[1][3];
                }
                break;
            }
            case 7:
            {
                if(v[1][1]!=' '&&(v[1][1]==v[2][2]&&v[1][1]==v[3][3]))
                {
                    win=true;
                chr=v[1][1];
                }
                break;
            }
            case 8:
            {
                if(v[1][3]!=' '&&(v[1][3]==v[2][2]&&v[1][3]==v[3][1]))
                {
                    win=true;
                    chr=v[1][3];
                }
                break;
            }
        }
    }
}






















