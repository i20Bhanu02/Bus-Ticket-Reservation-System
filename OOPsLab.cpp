#define pass "qwerty"
#include<fstream>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<process.h>
#include<iomanip>
#include<iostream>
#include<windows.h>
using namespace std;

char CODE[10];
char name[20];

void user_admin();
void admin();
void user();


class bus{
    int bno;
    char source[20];
    char dest[20];
    char driver_name[20];
    char at[20];
    char lt[20];
    bool seat[40];
    int fare;
    
    public:
    
    void input();
    void print_bus();
    int ret_bno(){
        return bno;
    }

    bool ret_seatf(int s){
        return seat[s-1];
    }

    void seatt(int s){
        seat[s-1] = true;
    }

}B;



class passenger{
    int bno;
    char pname[20];
    int age;
    int seatn;

    public:
    void getdata();
    void busno(int b){
        bno = b;
    }
    void seatno(int b){
        seatn = b;
    }
    void out();
}P;



void gotoxy(int x, int y)
{
    COORD c = { x, y };  
    SetConsoleCursorPosition(  GetStdHandle(STD_OUTPUT_HANDLE) , c);
}




void add_bus(){
    char m;
    system("cls");
    B.input();
    fstream f("busdata.dat",ios::binary|ios::app);
    f.write((char*)&B, sizeof(B));
    f.close();
    getch();
    admin();
}



void del_bus(){
    int btno;
    system("cls");
    cout<<"Enter bus number whose record is to be deleted : ";
    cin>>btno;
    fstream f("busdata.dat",ios::binary|ios::in);
    fstream g("temp",ios::out);

    bus Bt;
    int check=0;

    while(f.read((char*)&Bt, sizeof(Bt))){
        if(btno != Bt.ret_bno())
            g.write((char*)&Bt, sizeof(Bt));
        else
            check=1;
    }

    if(check==0)
        cout<<"\n Record Not Found";

    f.close();
    g.close();
    remove("busdata");
    rename("temp","busdata");
    Sleep(1000);
    admin();
}



void mod_bus(){
    system("cls");
    gotoxy(32,13);
    cout<<"Coming Soon !! Stay tuned ";
    getch();
    admin();
}



void book_seat(){
    system("cls");
    fstream f("busdata.dat",ios::binary|ios::in|ios::out);
    int tbn,s=0;
    cout<<"Enter bus number : ";
    cin>>tbn;
    int sn;
    cout<<"Enter seat number : ";
    cin>>sn;
    bus Bt;

    while(f.read((char*)&Bt, sizeof(Bt))){
    
        if(Bt.ret_bno() == tbn){
            s=1;
            if(Bt.ret_seatf(sn)==0){
                Bt.seatt(sn);
                P.getdata();
                P.busno(tbn);
                P.seatno(sn);
                cout<<"\n\t\t\tSeat Booked !!";
                fstream g("reserved.dat",ios::binary|ios::app);
                //f.seekp(-sizof(Bt,ios::cur));
                f.seekp(0);
                f.write((char*)&Bt,sizeof(Bt));
                g.write((char*)&P,sizeof(P));
                break;
            }
            else{
                cout<<"\n\t\t\tSeat is already occupied ";
            }
        }
        if(s==0){
            cout<<"\n\t\t\t Bus not found !";
        }
    }
    getch();
    f.close();
    user();
}



void empty_seat(){ 

    system("cls");
    fstream f("busdata.dat",ios::binary|ios::in|ios::out);
    bus Bt;
    int tbn,s=0;
    cout<<"Enter bus number : ";
    cin>>tbn;

    while(f.read((char*)&Bt, sizeof(Bt))){

        if(tbn == Bt.ret_bno()){
            s=1;
            for(int i=0;i<40;i++){
                if(i<9){
                    cout<<" ";
                }
                cout<<i+1<<" ";
                if(Bt.ret_seatf(i+1)==0){
                    cout<<"O   ";
                }
                else{
                    cout<<"X   ";
                }

                if(i+1 == 10 || i+1 == 20 || i+1 == 30){
                    cout<<"\n";
                }
                if(i+1 == 20){
                    cout<<"\n";
                }
            }
        }
    f.close();
    }  
    if(s==0){
        cout<<"\nBus not found ";
    }
    getch();
    user();
}



void bus_d(){
    system("cls");
    fstream f("busdata.dat",ios::binary|ios::in|ios::out);
    bus Bt;

    while(f.read((char*)&Bt, sizeof(Bt))){
        Bt.print_bus();
        cout<<"\n-----------------------------------------------------------";
    }
    f.close();
    getch();
    user();
}



void reserved(){
    system("cls");
    fstream f("reserved.dat",ios::binary|ios::in|ios::out);
    
    while(f.read((char*)&P, sizeof(P))){
        P.out();
        cout<<"\n-----------------------------------------------------------";
    }
    f.close();
    getch();
    user();
}



void user(){
    system("cls");

    gotoxy(35,2);
    cout<<"USER : "<<name<<"\n\n";
    cout<<"\n1.Book a seat\n2.Show Reservation\n3.Show empty seats\n4.Show available buses\n5.Back";
    switch(getch()){
        case '1':book_seat();break;
        case '2':reserved();break;
        case '3':empty_seat();break;
        case '4':bus_d();break;
        case '5':user_admin();
        default: cout<<"Enter a valid choice";
    }
}



void admin(){
    system("cls");

    gotoxy(35,2);
    cout<<"ADMIN\n\n";
    cout<<"\n1. Add new Bus";
    cout<<"\n2. Delete Bus Details";
    cout<<"\n3. Modify Bus Details";
    cout<<"\n4. Back";
    switch(getch()){
        case '1': add_bus();break;
        case '2': del_bus();break;
        case '3': mod_bus();break;
        case '4': user_admin();break;
        default: "\nEnter a valid choice";
   }
}



void admin_entry(){
    int c=1;
    again:
    cout<<"\n\t\t\tEnter the Password : ";
    gets(CODE);
    if(strcmpi(pass,CODE)){
        cout<<"\t\t  wrong password!! "<<3-c<<" attempts left\n";
        Sleep(1000);
        if(c>=3){
            cout<<"\nYou have entered wrong password 3 times";
	        cout<<"\nWe are making a entry as user";
            Sleep(2000);

	        system("cls");

	        gotoxy(32,13);
	        cout<<"Entering as User....";
            Sleep(1000);

	        user();
        }
        c++;
        goto again;  
    }
    else{
        system("cls");
        gotoxy(32,13);
        cout<<"Entering as Admin....";Sleep(1000);
        admin();     
    }
}



void user_admin(){
    system("cls");
    gotoxy(35,2);
    cout<<"MyBus";
    cout<<"\n\n\nEnter the Application as - \n\n1. User\n2. Admin\n3. Exit";
    switch(getch()){
        case '1':cout<<"\n\n\t\tEnter name : ";cin>>name;system("cls");gotoxy(32,13);cout<<"Entering as User....";Sleep(1000);user();break;
        case '2':admin_entry();break;
        case '3':cout<<"\nThanks for Joining Us";Sleep(1000);exit(0);
        default :cout<<"\nenter a valid option";Sleep(1000);user_admin();
    }
}



void startpage(){
    cout<<"MyBus";
    Sleep(1000);
    user_admin();
}


//MAIN
int main()
{
    startpage();
    return 0;
}


//In class Functions
void bus::input(){
    cout<<"Enter Bus number   : ";
    cin>>bno;
    cout<<"Enter Source       : ";
    cin>>source;
    cout<<"Enter Destination  : ";
    cin>>dest;
    cout<<"Enter Driver name  : ";
    cin>>driver_name;
    cout<<"Enter Leaving time : ";
    cin>>lt;
    cout<<"Enter Arrival time : ";
    cin>>at;
    cout<<"Enter fare : ";
    cin>>fare;
}



void bus::print_bus(){
    cout<<"\nBus number    : "<<bno;
    cout<<"\nSource        : "<<source;
    cout<<"\nDestination   : "<<dest;
    cout<<"\nDriver name   : "<<driver_name;
    cout<<"\nLeaving time  : "<<lt;
    cout<<"\nArriaval time : "<<at;
    cout<<"\nFare          : "<<fare;
    cout<<"\n\n";
}



void passenger::getdata(){
    cout<<"Enter Passenger name : ";
    cin>>pname;
    cout<<"Enter age : ";
    cin>>age;
}



void passenger::out(){
    cout<<"\nName        : "<<pname;
    cout<<"\nAge         : "<<age;
    cout<<"\nBus number  : "<<bno;
    cout<<"\nSeat number : "<<seatn;
}