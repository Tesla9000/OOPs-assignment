#include<bits/stdc++.h>
using namespace std;
// Classes used
class Traveller;
class Astronaut;
class Passenge;
class Commander;
class Ticket;
class Planet;
class SpaceTravel;
class Path;


static int K=1200; // The K Paramater for Ticket price
int cur_date=0;  //Current date

class Planet{
    // Private attributes
    int x;
    int y;
    int z;
    string Name;
    int ID;
    public:
        static int count;
        // Constructor and destructor functions
        Planet(){}
        Planet(string,int,int,int);
        ~Planet(){}
        // Member Functions
        int getX(){return x;}
        int getY(){return y;}
        int getZ(){return z;}
        string getName(){return Name;}
        int getID(){return ID;}
};

int Planet::count=0;
vector<Planet> Planets;


Planet::Planet(string name,int x1,int y1,int z1){Name=name,x=x1,y=y1,z=z1,ID=count++,Planets.push_back(*this);}

class Path{
    int source_id;
    int destination_id;
    int Travel_date;
    int ID;
    public:
        // 
        static int count;
        // Constructor and Destructor functions
        Path(){}
        Path(int,int,int);
        ~Path(){}
        // Member Functions
        int getSource(){return source_id;}
        int getDest(){return destination_id;}
        int getDate(){return Travel_date;}
        int getID(){return ID;}
        // Friend Class and Functions
        friend Ticket;
};

int Path:: count=0;

vector<Path> Paths;
vector<vector<int>> Path_passenger_stack(100);

int path_match(Path path,int src_id,int dest_id,int date){
    return (path.getSource()==src_id&&path.getDest()==dest_id&&path.getDate()==date);
}


class Ticket{
    // Private attributes
    int Price;
    int person_ID;
    Path road;
    public:
        // static functions
        // static unordered_map<Path,int> Path_counter;
        // Constructor and destructor functions
        Ticket(){}
        Ticket(int,int,int,int);//Book ticket function
        // Ticket(string,Planet,Planet,int);//book_ticket function
        ~Ticket(){}
        // Member Function
        // void updateTicket(int,int,int,int){}
        void cancelTicket();
        void set_price(){
            Price=K/(road.Travel_date-cur_date+1);
        }
        int getPrice(){return Price;}
        int getPersonID(){return person_ID;}
        Path getPath(){return road;}
};
class Traveller{
    // Private attributes
    protected:
    string Name;
    public:
        static int count;
        static vector<string> complete_traveller_list;
        // Public attributes
        vector<Ticket> list_of_tickets;
        //Constructor and Desctrutor
        Traveller(){}
        Traveller(string name);
        ~Traveller(){}
        // Member Functions

        string getName(){return Name;}
        vector<Ticket> getTickets(){return list_of_tickets;}
};

class Passenger:public Traveller{
    int validity;
    int ID;
    public:
        // Constructor and Destructor functions
        Passenger(){}
        Passenger(string);
        ~Passenger(){}
        // Member Functoins
        int getValidity(){return validity;}
        int getID(){return ID;}
        friend Ticket;
};

vector<Passenger> Passengers;

class Astronaut :public Traveller{
    int Experience;
    int ID;
    public:
        static int count;
        // Constructor and Destructor functions
        Astronaut(){}
        Astronaut(string,int);
        ~Astronaut(){}
        // Member Functoins
        int getExperience(){return Experience;} 
};

int Astronaut::count=0;
vector<Astronaut> Astronauts;


class Commander:public Traveller{
    // ???Authhority???
    int ID;
    public:
        static vector<string> List_of_commanders;
        static int count;
        Commander(){}
        Commander(string);
        ~Commander(){}
};

int Commander::count=0;
vector<Commander> Commanders;

class SpaceTravel{
    Astronaut astronaut;
    Commander commander;
    int ID;
    public:
        Path road;
        vector<Passenger> List_of_passengers;
        // static variables
        static int count;
        // Constructor and destructor functions
        SpaceTravel(){}
        SpaceTravel(int as,int com,int path_id);
        ~SpaceTravel(){}
        // Member Functions
        void AddTravellers(vector<int> passenger_list);
        void ListTravllers();
        void SetAstronaut(int );
        void SetCommander(int);
        void UpdateAstronaut(int );
        void ChangeCommander(int );
        
        // void updateAstronaut();
        // void updateCommander();
        vector<Passenger> getPassengers(){return List_of_passengers;}
        // Astronaut getAstronaut();
        // Commander getCommander();
        int getID(){return ID;}
        
};


int SpaceTravel::count=0;
vector<SpaceTravel> SpaceTravels;

void SpaceTravel::AddTravellers(vector<int> passengers){
    for(auto pass:passengers){
        List_of_passengers.push_back(Passengers[pass]);
    }
}

void SpaceTravel::ListTravllers(){
    cout<<"Commander is "<<this->commander.getName()<<endl;
    cout<<"Astronaut is "<<this->astronaut.getName()<<endl;
    cout<<"Passengers :"<<endl;
    for(auto passenger :List_of_passengers){
        cout<<"\t"<<passenger.getName()<<endl;
    }
}

void SpaceTravel::UpdateAstronaut(int as){
    astronaut=Astronauts[as];
}

void SpaceTravel::ChangeCommander(int com){
    commander=Commanders[com];
}

SpaceTravel::SpaceTravel(int as,int com,int path_id){
    astronaut=Astronauts[as];
    commander=Commanders[com];
    road=Paths[path_id];
    AddTravellers(Path_passenger_stack[path_id]);
    ID=count++;
    SpaceTravels.push_back(*this);
}

int travel_match(SpaceTravel travel,int src,int dest,int date){
    return travel.road.getSource()==src&&travel.road.getDest()==dest&&travel.road.getDate()==date;
}

Ticket::Ticket(int pass_id,int src_id,int dst_id,int date){
            if(date>cur_date+10){
                cout<<"Booking failed, date booked is too far ahead"<<endl;
            }
            else{
                if(pass_id>=Passengers.size())cout<<"Invalid ID"<<endl;

            else{
            cout<<"Ticket booked!"<<endl;
            for(auto travel:SpaceTravels){
                if(travel_match(travel,src_id,dst_id,date)){
                    if(travel.List_of_passengers.size()==8)cout<< "Housefull!!"<<endl;
                    travel.List_of_passengers.push_back(Passengers[pass_id]);
                }
            }
            int f=0;
            for(auto path:Paths){
                if(path_match(path,src_id,dst_id,date)){
                    f=1;
                    Path_passenger_stack[path.getID()].push_back(pass_id);
                    if(Path_passenger_stack[path.getID()].size()==2){
                        SpaceTravel* st_temp = new SpaceTravel(0,0,path.getID());
                        cout<<"Space travel " <<st_temp->getID()<< " created!!"<<endl;
                    }
                }
            }
            if(!f){
                Path* temp = new Path(src_id,dst_id,date);
                Paths.push_back(*temp);
                Path_passenger_stack[temp->getID()].push_back(pass_id);
            }
            road.source_id=src_id;
            road.destination_id=dst_id;
            road.Travel_date=date;
            set_price();
            person_ID=pass_id;
            Passengers[pass_id].list_of_tickets.push_back(*this);
            // person.list_of_tickets.push_back(*this);
            // Path_counter[road]++;
            // if(Path_counter[road]==2){
                // SpaceTravel  
            // }
            }
            }
}

int ticket_match(Ticket t1,Ticket t2){
    return t1.getPersonID()==t2.getPersonID()&&(path_match(t1.getPath(),t2.getPath().getSource(),t2.getPath().getDest(),t2.getPath().getDate()));
}

void Ticket:: cancelTicket(){
    for(int i=0;i<Passengers[person_ID].list_of_tickets.size();i++){
        if(ticket_match(*this,Passengers[person_ID].list_of_tickets[i])){
            while(i<Passengers[person_ID].list_of_tickets.size()){
                Passengers[person_ID].list_of_tickets[i]=Passengers[person_ID].list_of_tickets[i+1];
            }
            Passengers[person_ID].list_of_tickets.resize(Passengers[person_ID].list_of_tickets.size()-1);
        }
    }
}
// Space Travel Functions

void SpaceTravel::SetAstronaut(int id){
    if(id>=Astronauts.size())cout<<"Invalid Astronaut ID"<<endl;
    else{
        astronaut=Astronauts[id];
    }
}

void SpaceTravel::SetCommander(int id){
    if(id>=Commanders.size())cout<<"Invalid Commander ID"<<endl;
    else{
        commander=Commanders[id];
    }
}

//Path Functions

Path::Path(int src_id,int dst_id,int date){
    source_id=src_id;
    destination_id=dst_id;
    Travel_date=date;
    ID=count++;
}

// Ticket Functions


// Traveller Funcitons

int Traveller::count=0;
vector<string> Traveller :: complete_traveller_list(0); 

Traveller::Traveller(string name){
    Name=name;
}

// Passenger Functions

Passenger :: Passenger(string name){
    Name=name;
    ID=count++;
    Passengers.push_back(*this);
}

// Astronaut function

Astronaut::Astronaut(string name,int exp){
    Name=name;
    Experience=exp;
    ID=++count;
    Astronauts.push_back(*this);
}

// Commander functions

vector<string> Commander::List_of_commanders(0);

Commander::Commander(string name){
    Name=name;
    ID=++count;
    List_of_commanders.push_back(name);
    Commanders.push_back(*this);
}

int main(){
    int cur_date=1;
    Planet Earth("Earth",0,7,2);
    Planet Moon("Moon",0,1,2);
    Planet Mars("Mars",2,3,5);
    Passenger P1("P1");
    Passenger P2("P2");
    Passenger P3("P3");
    Passenger P4("P4");
    Passenger P5("P5");
    Passenger P6("P6");
    Passenger P7("P7");
    Passenger P8("P8");
    Passenger P9("P9");
    Passenger P10("P10");
    Passenger P11("P11");
    Astronaut A1("A1",4);
    Astronaut A2("A2",7);
    Commander C1("C1");
    Commander C2("C2");
    Ticket(0,0,1,7);
    Ticket(1,0,1,7);
    Ticket(2,1,0,7);
    SpaceTravels[0].ListTravllers();
}
