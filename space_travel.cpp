#include<bits/stdc++.h>
using namespace std;
// Classes used
class Traveller;
class Astronaut;
class Passenger;
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
    public:
        // Constructor and destructor functions
        Planet(){}
        Planet(int x1,int y1,int z1){x=x1,y=y1,z=z1;}
        ~Planet(){}
        // Member Functions
        int getX(){return x;}
        int getY(){return y;}
        int getZ(){return z;}
        string getName(){return Name;}
};

class Path{
    Planet source;
    Planet destination;
    int Travel_date;
    vector<Passenger> Passenger_queue;
    public:
        // Constructor and Destructor functions
        Path(){}
        Path(Planet,Planet,int);
        ~Path(){}
        // Member Functions
        Planet getSource(){return source;}
        Planet getDest(){return destination;}
        int getDate(){return Travel_date;}
        vector<Passenger> getPassengerQueue(){return Passenger_queue;}
        // Friend Class and Functions
        friend Ticket;
};

class Ticket{
    // Private attributes
    int Price;
    string Traveller_name;
    Path road;
    int date_booked;
    public:
        // Constructor and destructor functions
        Ticket(){}
        Ticket(string,Planet,Planet,int);//book_ticket function
        ~Ticket(){}
        // Member Function
        // void bookTicket(string,Planet ,Planet,int){}
        // void updateTicket(string,int){}
        // cancelTicket(){}
        void set_price();
        int getPrice(){return Price;}
};


class Traveller{
    // Private attributes
    protected:
    string Name;
    int ID;
    int account_creation_date;
    public:
        static int count;
        static vector<string> complete_traveller_list;
        // Public attributes
        vector<Ticket> list_of_tickets;
        //Constructor and Desctrutor
        Traveller(){}
        Traveller(string name,int date);
        ~Traveller(){}
        // Member Functions
        string getName(){return Name;}
        int getID(){return ID;}
        vector<Ticket> getTickets(){return list_of_tickets;}
        int getDate(){return account_creation_date;};
};

class Passenger:public Traveller{
    int validity;
    public:
        // Constructor and Destructor functions
        Passenger(){}
        Passenger(string,int,int);
        ~Passenger(){}
        // Member Functoins
        int getValidity(){return validity;}
};

class Astronaut :public Traveller{
    int Experience;
    public:
        // Constructor and Destructor functions
        Astronaut(){}
        Astronaut(string,int);
        ~Astronaut(){}
        // Member Functoins
        int getExperience(){return Experience;} 
};

class Commander:public Traveller{
    // ???Authhority???
    public:
        static vector<string> List_of_commanders;
        Commander(){}
        Commander(string);
        ~Commander(){}
};

class SpaceTravel{
    vector<Traveller> List_of_travellers;
    Astronaut astronaut;
    Commander commander;
    Path road;
    public:
        // Constructor and destructor functions
        // SpaceTravel(){}
        // ~SpaceTravel(){}
        // Member Functions
        void AddTravellers();
        // void SetAstronaut();
        // void SetCommander();
        // void updateAstronaut();
        // void updateCommander();
        // vector<Traveller> getTravellers();
        // Astronaut getAstronaut();
        // Commander getCommander();
        
};

// Space Travel Functions

void SpaceTravel::AddTravellers(){

}

//Path Functions

Path::Path(Planet src,Planet dst,int date){
    source=src;
    destination=dst;
    Travel_date=date;
}

// Ticket Functions

Ticket::Ticket(string name,Planet src,Planet dst,int date){
    Traveller_name=name;
    road.source=src;
    road.destination=dst;
    road.Travel_date=date;
    date_booked=cur_date;
    set_price();
}

void Ticket::set_price(){
    Price=K/(road.Travel_date-date_booked+1);
}

// Traveller Funcitons

int Traveller::count=0;
vector<string> Traveller :: complete_traveller_list(0); 

Traveller::Traveller(string name,int date){
    Name=name;
    account_creation_date=date;
    ID=++count;
}

// Passenger Functions

Passenger :: Passenger(string name,int date,int validity_bought=10){
    Name=name;
    account_creation_date=date;
    validity=validity_bought;
    ID=++count;
}

// Astronaut function

Astronaut::Astronaut(string name,int exp){
    Name=name;
    Experience=exp;
    ID=++count;
}

// Commander functions

vector<string> Commander::List_of_commanders(0);

Commander::Commander(string name){
    Name=name;
    ID=++count;
    List_of_commanders.push_back(name);
}

int main(){
    int cur_date=1;
    Passenger p("dev",cur_date);
    cur_date++;
    Passenger p2("yo",cur_date);
    // Astronaut m()
    cout<<p.getName()<<endl;
    cout<<p.getID()<<endl;
    cout<<p2.getName()<<endl;
    cout<<p2.getID()<<endl;
}