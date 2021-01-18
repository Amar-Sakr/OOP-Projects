#include <iostream>
#include <iomanip>

using namespace std;

enum time_zone { ACT, CET, CST, EST, GMT, MSK, PST, UTC };

enum arrival_departure{ arrival, departure };

class LocalTime{
    private:

        int minutes;
        time_zone x;
    public:
        LocalTime(){
            minutes = -1;
            x= CET;
        }
        LocalTime(int minute , int hour , time_zone a){
            a= CET;
            set_time(hour, minute);
        }
        void set_time(int hour , int minute){
            if(minute>= 0 && hour<24 && hour>=0){
            minutes= (hour * 60)+ minute;
            }
            else{
                cerr<<"wrong inserted time";
                minutes=-1;
            }
        }
        int get_minutes(){
            return (minutes%60);
        }
        int get_hours(){
            return (minutes/60);
        }

        bool is_valid(){
            if(minutes<0){
            return false;
        }
        }
        friend ostream& operator<< (ostream &out, const LocalTime fLocalTime);
};

ostream& operator<<(ostream& out, LocalTime fLocalTime){
cout<<setw(2)<<setfill('0')<<fLocalTime.get_hours()<<":"<<setw(2)<<setfill('0')<<fLocalTime.get_minutes();
return out;
}

class Flight{
private:
    arrival_departure live_case;
    string code;
    string destination;
    string gate;
    string checkIn;
    string comment;
    LocalTime expected;
public:
    Flight (arrival_departure c, string codes, string destinations , string gates , string checkIns , string x );

    ~Flight();

    string get_code();
    string get_destination();
    string get_gate();
    string get_checkIn();
    string get_comment();
    LocalTime get_expected();

    void set_expected(LocalTime x);
    void set_comment(string x);
    bool is_arrival(){

        if(live_case==0){return true;}
        else
            return false;
        }

    bool is_departure(){

        if(live_case==1){return true;}
        else
            return false;
        }

    void fdata_printing(LocalTime a);

};
Flight :: Flight(arrival_departure c  , string codes, string destinations , string gates , string checkIns , string x){
    live_case=c;
    code=codes;
    destination=destinations;
    gate=gates;
    checkIn=checkIns;
};

Flight :: ~Flight(){

cout<<get_code();
}


string Flight :: get_code(){return code;}
string Flight :: get_destination(){return destination;}
string Flight :: get_gate(){return gate;}
string Flight :: get_checkIn(){return checkIn;}
string Flight :: get_comment(){return comment;}
LocalTime Flight :: get_expected(){return expected;}
void Flight :: set_expected(LocalTime x){expected=x;}
void Flight :: set_comment(string x){comment=x;}
void Flight :: fdata_printing(LocalTime a){
    cout<<code<<"\t"<<destination<<"\t"<<a<<"\t"<<expected<<"\t"<<gate<<"\t"<<checkIn<<"\t"<<comment<<endl;
}

class Airport{
    private:
        string name ;
        Flight *slot [24][60]={};

    public:
        Airport(string n){
            name=n;
            for(int i=0; i<24; i++){
            for(int j=0; j<60; j++){
                slot[i][j] = nullptr;
               }
            }

        }
        ~Airport(){
            for(int i=0; i<24; i++){
                for(int j=0; j<60; j++){
                    if(slot[i][j]!= nullptr)
                    cout<<slot[i][j]->get_code()<<"  deleted"<<endl;
                }
            }
            delete slot;
        }
        void schedule(LocalTime x, Flight *attr){
            slot[x.get_hours()][x.get_minutes()]= attr;
        }
        void comment(LocalTime x, string a){
            slot[x.get_hours()][x.get_minutes()]->set_comment(a);
        }
        void delay(LocalTime x1, LocalTime x2){
            slot[x1.get_hours()][x1.get_minutes()]->set_expected(x2);
        }
        void print(arrival_departure s){
              if(s==0){
                  for(int i=0; i<24; i++){
                    for(int j=0; j<60; j++){
                        if(slot[i][j]!= nullptr &&slot[i][j]->is_arrival() ){
                        cout<<slot[i][j]->get_code();
                        cout<<"  "<<slot[i][j]->get_destination();
                        cout<<"\t               "<<i<<":"<<j;
                        cout<<"    "<<slot[i][j]->get_expected();
                        cout<<"    "<<slot[i][j]->get_gate();
                        cout<<"    "<<slot[i][j]->get_checkIn();
                        cout<<"   "<<slot[i][j]->get_comment()<<endl;
                        }
                    }
                  }

              }
              else

                for(int i=0; i<24; i++){
                    for(int j=0; j<60; j++){
                        if(slot[i][j]!= nullptr &&slot[i][j]->is_departure() ){
                        cout<<slot[i][j]->get_code();
                        cout<<"  "<<slot[i][j]->get_destination();
                        cout<<"\t       "<<i<<":"<<j;
                        cout<<"    "<<slot[i][j]->get_expected();
                        cout<<"    "<<slot[i][j]->get_gate();
                        cout<<"    "<<slot[i][j]->get_checkIn();
                        cout<<"   "<<slot[i][j]->get_comment()<<endl;
                        }
                    }
                  }



}
};


int main()
{
    Airport a("DUSSELDORF AIRPORT");
    LocalTime b;
    LocalTime c;
    b.set_time(12,40);
    c.set_time(13,05);
    Flight *one =new Flight(arrival,"LH 2010", "Munich   " , "A04" , "" , "" );
    a.schedule(b,one);
    a.delay(b,c);

    b.set_time(14,50);
    c.set_time(14,50);
    Flight *two =new Flight(arrival,"EW 9347", "Manchester" , "B04" , "" , "" );
    a.schedule(b,two);
    a.delay(b,c);

    b.set_time(9,10);
    c.set_time(9,10);
    Flight *three =new Flight(departure,"AF 1307", "Paris                " , " B51" , "192-194" , "" );
    a.schedule(b,three);
    a.delay(b,c);
    a.comment(b,"departed");


    b.set_time(10,40);
    c.set_time(10,40);
    Flight *four =new Flight(departure,"SU 2537", "Moscow             " , "C31" , "252-255" , "" );
    a.schedule(b,four);
    a.delay(b,c);
    a.comment(b,"boarding");

    b.set_time(11,15);
    c.set_time(11,15);
    Flight *five =new Flight(departure,"EW 9466", "London-Heathrow" , "B35" , "151-170" , "" );
    a.schedule(b,five);
    a.delay(b,c);

    b.set_time(13,25);
    c.set_time(13,25);
    Flight *six =new Flight(departure,"LH 2011", "Munich             " , "A40" , "115-120" , "" );
    a.schedule(b,six);
    a.delay(b,c);
    a.comment(b,"Code Sharing");

    b.set_time(14,55);
    c.set_time(15,20);
    Flight *seven =new Flight(departure,"XQ 959", " Izmir               " , "C45" , "240-242" , "" );
    a.schedule(b,seven);
    a.delay(b,c);


    cout<<"DUSSELDORF AIRPORT ARRIVALS"<<endl<<"============================="<<endl;
    cout<<"Flight   From                      Scheduled Expected   Gate    Check-in  Comments"<<endl;
    a.print(arrival);


    cout<<endl<<"DUSSELDORF AIRPORT DEPARTURES"<<endl<<"============================="<<endl;
    cout<<"Flight   To                        Scheduled Expected   Gate    Check-in  Comments"<<endl;
    a.print(departure);
    cout<<endl;



    return 0;
}
