#include <iostream>
#include <string>
using namespace std;

struct data {
    string team_name;
    int no_points;
    int no_matches;

};

int index[2];
void addteams(data team[], int no_teams);
void show_table (data team[], int no_teams);
int choose_team(data team[], int no_teams);
void addPoints(data team[], int x, int index[], int points[]);
void reset(data team[], int x);
int main()
{
    int x,choice;
    char c;
    cout<<"number of teams: ";
    cin>>x;
    data team[x];
    addteams(team, x);

    for(int i=0;i<x;i++)
    team[i] = team[i];
    cout<<"initial ranking \n==============\n";
    show_table (team, x);
  //  cout<<"\nchoose the team:";
  while(true)
  {
    if(x==0)
        break;

        cout<<"\n0 end\n1 add result of a match\n2 show ranking\n9 reset points\nyour choice:";
        cin>>choice;
        if(choice == 0)
        {
          break;
        }
        else if(choice == 1)
        {
          int a,b;
          char c;
          int points[2];
          int check=choose_team(team, x);
          if(check==1){
                  cout<<"input as [points of "<<team[index[0]].team_name<<"] : [points of "<<team[index[1]].team_name<<"]?";
                  cin>>a>>c>>b;
                  points[0] = a;
                  points[1] = b;
                  addPoints(team, x, index, points );

            }
          else
          {
              cout<<"* sorry teams need to be different *\n";
              continue;
          }

        }

       else if(choice==2)
      {

        for (int i = 0; i < x-1; i++)
        {
        for (int j = 0; j < x-i-1; j++)
        {
        if (team[j].no_points > team[j+1].no_points)
        {
          data swp = team[j];
          team[j] = team[j+1];
          team[j+1] = swp;
        }
        }
        }
        data tt[x] = team;
        int jj = 0;
        for(int i =x-1;i>=0;i--)
        {
        team[jj] = tt[i];
        jj++;
        }
        show_table (team, x);
      }

      else if(choice == 9)
      {
          reset(team, x);
      }


  }
}




void addteams(data team[], int no_teams){

    cout << "\ninput of teams \n============== \n";
    for(int i=0; i<no_teams; i++){
        cout<<"team"<<i+1<<":";
        cin>>team[i].team_name;
        team[i].no_points=0;
        team[i].no_matches=0;
    }
 }
//*****************************************************
void show_table(data team[], int no_teams){
    cout << "Points" << "\t" << "Played Matches" << "\t" <<  "Team Name\n";
    for(int i=0; i<no_teams; i++){
        cout << team[i].no_points<< "\t" << team[i].no_matches << "\t\t" <<  team[i].team_name << endl;
    }
}
//*****************************************************
int choose_team(data team[], int no_teams){
    cout<<"please choose team 1?\nteams\n=====\n";
    for(int i=0; i<no_teams; i++){
        cout<<i+1<<"\t"<<team[i].team_name<<endl;
    }
    cout<<"choose team by number:";
    cin>>index[0];
    index[0]--;

    cout<<"please choose team 2?\nteams\n=====\n";
    for(int i=0; i<no_teams; i++){
        cout<<i+1<<"\t"<<team[i].team_name<<endl;
    }
    cout<<"choose team by number:";
    cin>>index[1];
    index[1]--;
    if(index[0]!=index[1])
        return 1;
    else
        return 0;
}
//*************************************************************
void addPoints(data team[], int x, int index[], int points[])
{
    team[index[0]].no_points += points[0];
    team[index[1]].no_points += points[1];
    team[index[0]].no_matches++;
    team[index[1]].no_matches++;
}
//************************************************
void reset(data team[], int x)
{
    for(int i = 0 ;i<x ; i++)
    {
        team[i].no_points = 0;
        team[i].no_matches = 0;
    }
}
