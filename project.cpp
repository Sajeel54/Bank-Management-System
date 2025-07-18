#include<iostream>
#include<string>
#include<fstream>
#include<conio.h>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;

class login
{
    string e_id;
    long long int passcode;
    long a_id;
    public:
    login()
    {
        e_id='\0';        a_id=0;
        passcode=0;
    }

    login(long x1,string s,long long int x2)
    {
        e_id=s;      a_id=x1;
        passcode=x2;
    }

    void input(int choice)
    {
        string s;
        if(choice==1)
        {
            cout<<"Enter Account number: ";
            cin>>a_id;
            cout<<"Enter PIN: ";
            e_id="null";

        }
        else 
        {
            cout<<"Enter name: ";
            cin.ignore();
            getline(cin,s);
            e_id=s;
            cout<<"Enter Password: ";
            a_id=0;
        }
        cin>>passcode;
    }

    void show(int choice)
    {
        fstream file;
        if(choice==1)
            file.open("a_login.txt",ios::in);
        else
            file.open("a_login.txt",ios::in);
        while(file>>a_id>>e_id>>passcode)
        {
            if(e_id=="null")
                cout<<a_id<<"\t"<<passcode<<endl;
            else    
                cout<<e_id<<"\t"<<passcode<<endl;
        }   
        file.close();
    }

    bool check_login(int choice)
    {
        login::input(choice);
        login search;
        fstream file;
        if(choice==1)
            file.open("a_login.txt",ios::in);
        else if(choice==2)
            file.open("e_login.txt",ios::in);
        else
            file.open("m_login.txt",ios::in);
        bool check=false;
        while(file>>search.a_id>>search.e_id>>search.passcode)
        {
            int i=0;
            while(search.e_id[i]!='\0')
            {
                if(search.e_id[i]=='_')
                   search.e_id[i]=' ';
                i++;
            }
            if(search==login(a_id,e_id,passcode))
            {
                check=true;
                break;
            }
        }
        return check; 
    }

    void create_login(int choice)
    {
        fstream file;
        if(choice==1)
            file.open("a_login.txt",ios::out|ios::app);
        else
            file.open("e_login.txt",ios::out|ios::app);
        int i=0;
        if(choice==1)   cout<<a_id<<"\t"<<passcode<<endl;
        else cout<<e_id<<"\t"<<passcode<<endl;
        while(e_id[i]!='\0')
        {
            if(e_id[i]==' ')
                e_id[i]='_';
            i++;
        }
        file<<a_id<<" "<<e_id<<" "<<passcode<<" ";
        file.close();
    }

    void delete_login(int choice)
    {
        login search1;
        fstream file1,file2;
        if(choice==1)
            file1.open("a_login.txt",ios::in);
        else
            file1.open("e_login.txt",ios::in);
        file2.open("t_temp.txt",ios::out|ios::app);
        while(file1>>search1.a_id>>search1.e_id>>search1.passcode)
        { 
            int i=0;
            while(search1.e_id[i]!='\0')
            {
                if(search1.e_id[i]=='_')
                   search1.e_id[i]=' ';
                i++;
            }
            if(((a_id==search1.a_id&& search1.a_id!=0)||(e_id==search1.e_id&&search1.e_id!="null")))
                cout<<"login Deleted\n";
            else
            {
                int j=0;
                while(search1.e_id[i]!='\0')
                {
                    if(search1.e_id[i]==' ')
                        search1.e_id[i]='_';
                    j++;
                }
                file2<<search1.a_id<<" "<<search1.e_id<<" "<<search1.passcode<<" ";
            }        
        }
        file1.close(); file2.close();
        if(choice==1)
        {
            remove("a_login.txt");
            rename("t_temp.txt","a_login.txt");
        }
        else
        {
            remove("e_login.txt");
            rename("t_temp.txt","e_login.txt");
        }
    }
    long return_login()
    {
        return a_id;
    }
    void modify_login(string s1,string s2)
    {
        fstream file1,file2("e_login.txt",ios::out|ios::app);
        file1.open("temp.txt",ios::in);
        while(file1>>a_id>>e_id>>passcode)
        {
            if(s2==e_id)
                e_id=s1;
            file2<<a_id<<" "<<e_id<<" "<<passcode<<" ";
        }
        file1.close(); file2.close();
    }
    bool operator==(login x)
    {
        if(e_id==x.e_id && passcode==x.passcode && a_id==x.a_id)
            return true;
        else
            return false;
    }        
};

class account
{
    protected:
    long number;
    long long int cnic;
    string name;
    long amount;
    int static x;
    char type;
    public:
    account()
    { }
    account(long x1,long long int x2,string x3,long x4)
    {
        number=x1;  name=x3;
        cnic=x2;    amount=x4;
    }
    ~account()
    {  
        fstream file;
        file.open("number.txt",ios::out);
        file<<x;
        file.close();
    }
    void show_list() 
    {
        ifstream file("accounts.txt");
        cout<<"NAME  \t\t\tCNIC\t\t\t\t\tAMOUNT\tACOUNT NO\n";
        while(file>>name>>cnic>>number>>amount)
        {
            int i=0;
            while(name[i]!='\0')
            {
                if(name[i]=='_')
                   name[i]=' ';
                i++;
            }
            cout<<name<<"\t\t"<<cnic<<"\t\t\t\t"<<amount<<"\t"<<number<<endl;
        }
    }
    void input()
    {
        cout<<"Enter name: ";
        cin.ignore();
        getline(cin,name);
        cout<<"Enter cnic: ";
        cin>>cnic;
        do{ 
            cout<<"Enter the rype of account(saving(s)/current(c)): ";
            cin>>type;
            if(type=='c')
            { do{ cout<<"Enter amount: "; cin>>amount; }while(amount<5000);}
            else if(type=='s')
            { do{ cout<<"Enter amount: "; cin>>amount; }while(amount<3000); }
            else cout<<"Wrong account type\n";
        }while(type!='c'&&type!='s');
    }
    void display() const
    {
        cout<<"name: "<<name<<endl;
        cout<<"cnic: "<<cnic<<endl;
        cout<<"amount: "<<amount<<endl;
        cout<<"Account number: "<<number<<endl;
    }
    bool check_creation()
    {
        int count=0;
        account search;
        fstream file;
        file.open("accounts.txt",ios::in);
        while(file>>search.name>>search.cnic>>search.number>>search.amount)
        {
            if(search.cnic==cnic)
               count++;
        }
        if(count<3)
           return false;
        else 
           return true;

    }
    void create_account()
    {
            account::input();
            fstream file;
            file.open("accounts.txt",ios::out|ios::app);
            int i=0;
            while(name[i]!='\0')
            {
                if(name[i]==' ')
                    name[i]='_';
                i++;
            }
            file<<name<<" "<<cnic<<" "<<number<<" "<<amount<<" ";
            cout<<"Account number: "<<number<<endl;
            file.close();
    }
    void delete_account()
    {
        account search;
        fstream file("accounts.txt",ios::in);
        fstream file1("temp.txt",ios::out|ios::app);

        while(file>>search.name>>search.cnic>>search.number>>search.amount)
        {
            if(number!=search.number)
            {
                file1<<search.name<<" "<<search.cnic<<" "<<search.number<<" "<<search.amount<<" ";
            }
            else
                cout<<"account deleted\n"; 
        }
        file1.close();
        file.close();
        remove("accounts.txt");
        rename("temp.txt","accounts.txt");
    }
    void search_account()
    {
        account search; bool check=true;
        cout<<"Enter account number: "; cin>>number;
        fstream file("accounts.txt",ios::in);
        while(file>>search.name>>search.cnic>>search.number>>search.amount)
        {
            int i=0;
            while(search.name[i]!='\0')
            {
                if(search.name[i]=='_')
                    search.name[i]=' ';
                i++;
            }
            if(search.number==number)
            {
                search.display(); check=false;
                break;
            }
        }
        if(check){ cout<<"The account with number "<<number<<" does not exist\n"; }
        file.close();
    }
    void search_name() 
    {
        account search; bool check=true;
        cout<<"Enter name: ";
        getline(cin,name);
        fstream file("accounts.txt",ios::in);
        while(file>>search.name>>search.cnic>>search.number>>search.amount)
        {
            int i=0;
            while(search.name[i]!='\0')
            {
                if(search.name[i]=='_')
                    search.name[i]=' ';
                i++;
            }
            if(search.name==name)
            {
                account::display(); check=false;
                break;
            }
        }
        if(check){ cout<<"The account with number "<<name<<" does not exist\n"; }
        file.close();
    }

    void search_cnic()
    {
        long long int search; bool check=true;
        cout<<"Enter cnic: ";
        cin>>search;
        fstream file("accounts.txt",ios::in);
        while(file>>name>>cnic>>number>>amount)
        {
            if(search==cnic)
            {
                account::display(); check=false;
                break;
            }
        }
        if(check){ cout<<"The account with number "<<cnic<<" does not exist\n"; }
        file.close();
    }

    void withdraw()
    {
        account search; bool check=true;
        fstream file,file1;
        file.open("accounts.txt",ios::in);
        file1.open("temp.txt",ios::out|ios::app);
        while(file>>search.name>>search.cnic>>search.number>>search.amount)
        {
            if(search.number==number)
            {
                r:
                search.display(); check=false;
                cout<<"Enter amount you want to withdraw: ";
                long withdraw;
                cin>>withdraw;
                search.amount-=withdraw;
                if(search.amount<0)
                {
                    cout<<"\n|||You don't have enough balance to withdraw this amount|||\n\n";
                    search.amount+=withdraw; system("cls"); goto r;
                }
                search.display();
            }
            file1<<search.name<<" "<<search.cnic<<" "<<search.number<<" "<<search.amount<<" ";
        }
        if(check){ cout<<"The account with number "<<number<<" does not exist\n"; }
        file.close();
        file1.close();
        remove("accounts.txt");
        rename("temp.txt","accounts.txt");
    }

    void deposite()
    {
        account search; bool check=true;
        fstream file,file1;
        file.open("accounts.txt",ios::in);
        file1.open("temp.txt",ios::out|ios::app);
        while(file>>search.name>>search.cnic>>search.number>>search.amount)
        {
            if(search.number==number)
            {
                search.display(); check=false;
                cout<<"Enter amount you want to deposite: ";
                long deposite;
                cin>>deposite;
                search.amount+=deposite;
                
                search.display();
            }
            file1<<search.name<<" "<<search.cnic<<" "<<search.number<<" "<<search.amount<<" ";
        }
        if(check){ cout<<"The account with number "<<number<<" does not exist\n"; }
        file.close();
        file1.close();
        remove("accounts.txt");
        rename("temp.txt","accounts.txt");
    }

    void transaction()
    {
        account search1; bool check=false,check1=false;
        long double search2;
        cout<<"Enter account number you want to shift amount to: ";
        cin>>search2;
        cout<<"Enter amount you want to transaction amount: ";                
        long transaction;
        cin>>transaction;
        fstream file,file1;
        file.open("accounts.txt",ios::in | ios::out | ios::app);
        file1.open("temp.txt",ios::out|ios::app);
        while(file>>search1.name>>search1.cnic>>search1.number>>search1.amount)
        {
            if(search1.number==number)
            {
                search1.display(); check=true;
                search1.amount-=transaction;
                if(search1.amount<0)
                {
                    cout<<"\nYou don't have enough balance to transfer this amount\n\n";
                    search1.amount+=transaction;
                    check1=true;
                }
                search1.display();
            }
            if(search2==search1.number && check && !check1)
            {
                search1.display();
                search1.amount+=transaction;
                search1.display();
            }
            file1<<search1.name<<" "<<search1.cnic<<" "<<search1.number<<" "<<search1.amount<<" ";
        }
        if(!check){ cout<<"The account with number "<<search2<<" not found\n"; }
        if(check1){ cout<<"Your balance is not enough to make this transfer\n"; }
        file.close(); file1.close();
        remove("accounts.txt");
        rename("temp.txt","accounts.txt");
    }
};

int allocate_acc_no()
{
    int temp;
    fstream file;
    file.open("D:/2nd semester/oop project/number.txt",ios::in);
    file>>temp;
    file.close();
    return temp;
}
int account::x=allocate_acc_no();
class employee:public account
{
    public:
    employee()
    {
        name="null"; amount=0;
        cnic=0;
    }
    employee(long x1)
    { number= x1; }
    employee(string s,long long int x1,long x2)
    {
        name=s; amount=x2;
        cnic=x1;
    }

    void add_a()
    {
        number=x;
        account::create_account();
        long long int a=cnic;
        while(a>=10000){ a=a/10; }
        a=(a+(cnic%10000))+number;
        while(a>=10000){ a=a/10; }
        login log(number,"null",a);
        log.create_login(1);
        x++;
    }

    void remove_a()
    {
        cout<<"Enter account number: ";
        long search;
        cin>>search;
        number=search;
        account::delete_account();
        login log(search,"null",0);
        log.delete_login(1);
    }
    void modify_a()
    {
        string search_name; fstream file1("accounts.txt",ios::in),file2;
        long long int search_cnic; int i=0;
        file2.open("temp.txt",ios::out|ios::app); 
        cout<<"Enter cnic: "; cin>>search_cnic;
        while(file1>>name>>cnic>>number>>amount)
        {
            while(name[i]=='\0'){ if(name[i]==' ') name[i]='_'; i++; }
            if(search_cnic==cnic)
            {
                account::display();
                cout<<"Enter modification details\nEnter name: ";
                cin>>search_name;
                cout<<"Enter cnic: "; cin>>search_cnic;
                name=search_name; cnic=search_cnic;
                account::display();
            }
            while(name[i]=='\0'){ if(name[i]==' ') name[i]='_'; i++; }
            file2<<name<<" "<<cnic<<" "<<number<<" "<<amount<<" ";
        }
        file1.close(); file2.close();
        remove("accounts.txt");
        rename("temp.txt","accounts.txt");
    }
    bool operator==(employee x)
    {
        bool i;
        if(name==x.name && cnic==x.cnic )
            i=true;
        else
            i=false;
        return i;
    }
};

class user:protected account
{
    public:
    void access(login x) 
    { 
        long search=x.return_login();
        fstream file("accounts.txt",ios::in); 
        while(file>>name>>cnic>>number>>amount)
        {
            if(search==number)
            {
               break;
            }   
        }
    }
    void display() 
    { 
        int i=0; while(name[i]!='\0'){if(name[i]=='_') name[i]=' ';i++;}
        account::display();
    }
    void withdraw() { account::withdraw(); }
    void deposite() { account::deposite(); }
    void transaction() { account::transaction(); }
};

class manager:public employee
{
    login log;
    public:
    manager(){ }
    manager(long x1){ number=x1; }
    void input_e()
    {
        cout<<"Enter Name: ";
        cin.ignore();
        getline(cin,name);
        cout<<"Enter cnic: ";
        cin>>cnic;
        cout<<"Enter salary: ";
        cin>>amount;
    }
    void add_e()
    {
        manager::input_e();
        fstream file;
        file.open("employee.txt",ios::out|ios::app);
        int i=0;
        while(name[i]!='\0')
        {
            if(name[i]==' ')
            {
                name[i]='_';
            }    
            i++;
        }
        file<<name<<" "<<cnic<<" "<<" "<<amount<<" ";
        long long int a=cnic;
        while(a>=10000){ a=a/10; }
        a=(a+(cnic%10000));
        while(a>=10000){ a=a/10; }
        log=login(0,name,a);
        log.create_login(2);
    }
    void show_e_list()
    {
        fstream file;
        file.open("employee.txt",ios::in);
        cout<<"name\tcnic\tSalary\n";
        while(file>>name>>cnic>>amount)
        {
            int i=0;
            while(name[i]!='\0')
            {
                if(name[i]=='_')
                    name[i]=' ';
                i++;
            }
            cout<<name<<"\t"<<cnic<<"\t"<<amount<<endl;
        }
        file.close();
    }
    void remove_e()
    {
        fstream file1,file2;
        string search_name;
        long long int search_cnic;
        cout<<"Enter name:";
        cin>>search_name;
        cout<<"Enter cnic: ";
        cin>>search_cnic;
        employee search(search_name,search_cnic,0);
        file1.open("employee.txt",ios::in);
        file2.open("temp.txt",ios::out|ios::app);
        while(file1>>name>>cnic>>amount)
        {
            int i=0;
            while(name[i]!='\0')
            {
                if(name[i]=='_')
                    name[i]=' ';
                i++;
            }
            if(search==employee(name,cnic,0))
            {
                cout<<"Deleted\n";
                log=login(0,name,0);
                log.delete_login(2);
            }    
            else
            {
                int i=0;
                while(name[i]!='\0')
                {
                    if(name[i]==' ')
                        name[i]='_';
                    i++;
                }
                file2<<name<<" "<<cnic<<" "<<amount<<" ";
                cout<<name<<"\t"<<cnic<<"\t"<<amount<<" ";
            }    
        }
        file1.close(); file2.close();
        remove("employee.txt");
        rename("temp.txt","employee.txt");
    }
    void modify_e()
    {
        string search_name; fstream file1("employee.txt",ios::in),file2;
        long long int search_cnic; int i=0;
        file2.open("temp.txt",ios::out|ios::app);
        cout<<"Enter name: ";
        cin>>search_name;
        cout<<"Enter cnic: ";
        cin>>search_cnic;
        while(file1>>name>>cnic>>amount)
        {
            while(name[i]=='\0'){ if(name[i]=='_') name[i]=' '; i++; };
            if(name==search_name && cnic==search_cnic)
            {
                manager::display_e();
                cout<<"Enter modification details\n";
                manager::input_e();
                log.modify_login(search_name,name);
                manager::display_e();
            }
            while(name[i]=='\0'){ if(name[i]==' ') name[i]='_'; i++; };
            file2<<name<<" "<<cnic<<" "<<amount<<" ";
        }
        file1.close(); file2.close();
        remove("employee.txt");
        rename("temp.txt","employee.txt");
    }
    void search_e_name()
    {
        string search;
        cout<<"Enter name: ";
        cin>>search;
        fstream file("employee.txt",ios::in);
        while(file>>name>>cnic>>amount)
        {
            if(name==search)
            {
                manager::display_e();
            }
        }
        file.close();
    }
    void search_e_cnic()
    {
        long long int search;
        cout<<"Enter name: ";
        cin>>search;
        fstream file("employee.txt",ios::in);
        while(file>>name>>cnic>>amount)
        {
            if(cnic==search)
            {
                manager::display_e();
            }
        }
        file.close();
    }
    void display_e()
    {
        cout<<"Name: "<<name<<endl;
        cout<<"CNIC: "<<cnic<<endl;
        cout<<"Salary: "<<amount<<endl; 
    }
};
user u1;
manager m1;
login l1;
employee e1;
void menu();
void functions_menu();
void user_menu()
{
    if(l1.check_login(1))
    {
        cout<<"||||Login Succesfull\n";
        system("pause"); system("cls");
        char c;
        while(1)
        {
            cout<<"Press the following keys to select the corresponding option\n";
            cout<<"a)View account\nb)Withdraw\nc)Deposite\nd)Transaction\n";
            cout<<"press esc to exit\n";
            c=getch();
            system("cls");
            if(c=='a'){ u1.access(l1); u1.display(); }
            else if(c=='b'){ u1.access(l1); u1.withdraw(); }
            else if(c=='c'){ u1.access(l1); u1.deposite(); }
            else if(c=='d'){ u1.access(l1); u1.transaction(); }
            else if(c=='\e'){ break; }
            else cout<<"wrong choice\n";
            system("pause"); system("cls");
        }
    }
    else
    {
        cout<<"Wrong id or password\n";
    }    
}
// employee record login details
//1.login id=Musa Bajwa , password=1133
//2.login id=soban hameed , password=8023
void employee_menu()
{
    long no;
    char c;
    if(l1.check_login(2))
    {
        cout<<"||||Login Succesfull\n"; 
        system("pause"); system("cls");
        while(1)
        {
            cout<<"Press the following keys to select the corresponding option\n";
            cout<<"a)Create account\nb)Delete account\nc)View list of accounts\n";
            cout<<"d)Search account\ne)Search by name\nf)search by cnic\n";
            cout<<"g)withdraw amount\nh)deposite amount\ni)transfer amount\nj)Modify account\npress esc to exit\n";
            c=getch();
            system("cls");
            if(c=='a')  e1.add_a();
            else if(c=='b') e1.remove_a();
            else if(c=='c') e1.show_list();
            else if(c=='d') e1.search_account();
            else if(c=='e') e1.search_name();
            else if(c=='f') e1.search_cnic();
            else if(c=='g')
            { 
                cout<<"Enter account number:\n";
                cin>>no;
                e1=employee(no);         
                e1.withdraw();
            }    
            else if(c=='h')
            {
                cout<<"Enter account number:\n";
                cin>>no;
                e1=employee(no);
                e1.deposite();
            }    
            else if(c=='i')
            {
                cout<<"Enter account number:\n";
                cin>>no;
                e1=employee(no);
                e1.transaction();
            }    
            else if(c=='j') e1.modify_a();
            else if(c=='\e') break;
            else cout<<"Wrong choice\n";
            system("pause"); system("cls");
        }
    }
    else cout<<"Wrong name or password\n";
}
// manager login details
// login id=Sajeel , password=8691
void manager_menu()
{
    char c; long no;
    if(l1.check_login(3))
    {
        cout<<"||||Login Succesfull\n";
        system("pause"); system("cls");
        while(1)
        {
            cout<<"Press the following keys to select the corresponding option\n";
            cout<<"a)Create account\nb)Delete account\nc)View list of accounts\n";
            cout<<"d)Search account\ne)Search account by name\nf)search account by cnic\n";
            cout<<"g)withdraw amount\nh)deposite amount\ni)transfer amount\n";
            cout<<"j)Add an employee\nk)Remove an employee\nl)Show list of employee\n";
            cout<<"m)Search employee by name\nn)Search employee by cnic\no)Modify employee data\n";
            cout<<"p)Modify account data\npress esc to exit\n";
            c=getch();
            system("cls");
            if(c=='a')   m1.add_a();
            else if(c=='b') m1.remove_a(); 
            else if(c=='c') m1.show_list();
            else if(c=='d') m1.search_account();
            else if(c=='e') m1.search_name();
            else if(c=='f') m1.search_cnic();
            else if(c=='g')
            { 
                cout<<"Enter account number: "; cin>>no;
                m1=manager(no); m1.withdraw();
            }    
            else if(c=='h')
            {
                cout<<"Enter account number: "; cin>>no;
                m1=manager(no); m1.deposite();
            }
            else if(c=='i') 
            {
                cout<<"Enter account number: "; cin>>no;
                m1=manager(no); m1.transaction();//edit
            }    
            else if(c=='j') m1.add_e();
            else if(c=='k') m1.remove_e();
            else if(c=='l') m1.show_e_list();
            else if(c=='m') m1.search_e_name();
            else if(c=='n') m1.search_e_cnic();
            else if(c=='o') m1.modify_e();
            else if(c=='p') m1.modify_a();
            else if(c=='\e') break;
            else cout<<"wrong choice\n";
            system("pause"); system("cls");
        }
    }
    else cout<<"Wrong name or password\n";
}
void menu()
{
    char c; 
    system("cls");
    cout<<"|||||||BANK MANAGEMENT SYSTEM|||||||\n";
    while(1)
    {
        cout<<"Press the following keys to select the corresponding option\n";
        cout<<"You want to login as\n";
        cout<<"a)Account holder\nb)Employee\nc)Manager\n";
        cout<<"Press esc to exit\n";
        c=getch();
        system("cls");
        if(c=='a'){user_menu();}
        else if(c=='b'){employee_menu();}
        else if(c=='c'){manager_menu();}
        else if(c=='\e') break; 
        else cout<<"wrong choice\n";
        system("pause"); system("cls");
    }
    cout<<"||||||||||||||\t\t\t||||||||||||||\n||||||||||||||Process Terminated||||||||||||||\n";
    cout<<"||||||||||||||\t\t\t||||||||||||||";
}
account a1;
int main()
{ 
    menu(); 
}