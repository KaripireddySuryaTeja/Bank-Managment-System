#include<iostream>
#include<stdlib.h>
#include<conio.h> 
#include<string>
using namespace std;

struct bankmanagement
{
    int accno; 
    string name, address; 
    char actype; 
    float amount;
    
    bool checkavailabilty(); 
    bool searchaccount(int); 
    void newaccount(); 
    void deposit();
    void withdraw(); 
    void check_account(); 
    void modifyaccount(); 
    void deleteaccount(); 
  
    bankmanagement()
    {
        accno=0;
        name="";
        address="";
        actype='\0';
        amount=0.0; 
    }
};

int main()
{
    bankmanagement b[5]; 
    int x,an; 
    bool check; 
    
    while(1)
    {   
        system("CLS"); 
        cout<<"             =================              "<<endl;
        cout<<"             |   Bank Menu   |              "<<endl;
        cout<<"=========================================="<<endl;
        cout<<" Enter 1 to create a new account.\n Enter 2 to Deposit.\n Enter 3 to Withdraw.\n Enter 4 to Check account.\n Enter 5 to Modify.\n Enter 6 to Delete.\n Enter 7 to show all accounts.\n Enter 8 to exit";
        cout<<"\n=========================================="<<endl;
        cout<<" Enter choice no: ";
        cin>>x; 
        
        switch(x)
        {
            case 1: 
            {
                check=false;
                for(int i=0; i<5; i++)
                {
                    if(b[i].checkavailabilty()) 
                    {
                        check=true;
                        b[i].newaccount();
                        cout<<" working.";
                        break;
                    }   
                }
                
                if(check==false)
                    cout<<" Accounts exceeded."; 
                    
                break;  
            }
            case 2: 
            {
                check=false;
                cout<<" Enter account no. : ";
                cin>>an; 
                for(int i=0; i<5; i++)
                {
                    if(b[i].searchaccount(an)) 
                    {
                        check=true;
                        b[i].deposit(); 
                        break;
                    }   
                }
                
                if(check==false)
                    cout<<" No account found ."; 
                    
                break;
            }
            case 3: 
            {
                check=false;
                cout<<" Enter account no. : ";
                cin>>an; 
                for(int i=0; i<5; i++)
                {
                    if(b[i].searchaccount(an)) 
                    {
                        check=true;
                        b[i].withdraw(); 
                        break;
                    }   
                }
                
                if(check==false)
                    cout<<" No account found ."; 
                    
                break;      
            }
            case 4: 
            {
                check=false;
                cout<<" Enter account no. : ";
                cin>>an; 
                for(int i=0; i<5; i++)
                {
                    if(b[i].searchaccount(an)) 
                    {
                        check=true;
                        b[i].check_account(); 
                        break;
                    }   
                }
                
                if(check==false)
                    cout<<" No account found ."; 
                    
                break;      
                
            }
            case 5: 
            {
                check=false;
                cout<<" Enter account no. : ";
                cin>>an; 
                for(int i=0; i<5; i++)
                {
                    if(b[i].searchaccount(an)) 
                    {
                        check=true;
                        b[i].modifyaccount(); 
                        break;
                    }   
                }
                
                if(check==false)
                    cout<<" No account found ."; 
                    
                break;      
            }
            case 6: 
            {
                check=false;
                cout<<" Enter account no. : ";
                cin>>an; 
                for(int i=0; i<5; i++)
                {
                    if(b[i].searchaccount(an)) 
                    {
                        check=true;
                        b[i].deleteaccount(); 
                        break;
                    }   
                }
                
                if(check==false)
                    cout<<" No account found ."; 
                    
                break;      
            }
            case 7: 
            {
                check=false;
                for(int i=0; i<5; i++)
                {
                    if(!b[i].checkavailabilty()) 
                    {
                        check=true;
                        cout<<"\nAccount details of "<<i+1<<":\n ";
                        b[i].check_account(); 
                        cout<<"\n==========================================\n";
                    }   
                }
                
                if(check==false)
                    cout<<" No account found ."; 
                    
                break;      
            }
            case 8: 
            {
                exit(0); 
            }
            
        }
        getch(); 
    }
    
    return 0;
}

bool bankmanagement::checkavailabilty()
{
    if(accno==0 && name=="" && address=="" && actype=='\0' && amount==0.0)
        return true;
    else
        return false;
}

bool bankmanagement::searchaccount(int a)
{
    if(accno==a )
        return true;
    else
        return false;
}

void bankmanagement::newaccount()
{
    cout<< " Enter your account no: ";
    cin>> accno; 
    
    cout<< " Enter your full name: ";
    cin>> name; 
    
    cout<< " Enter your address: ";
    cin>> address; 
   
    cout<< " What type of account you want to open saving(s) or Current(c):";
    cin>> actype; 
   
    cout<< " Enter How much money you want to deposit: ";
    cin>> amount; 
	    
    cout << " Account Created Successfully...";	    
}

void bankmanagement::deposit()
{
    float d;
    cout<<"\n Enter amount to Deposit = ";
    cin>>d; 
    amount += d; 
    cout<<" Updated...New Amount = "<<amount; 
}

void bankmanagement::withdraw()
{
    int wd;
    cout<<"\n Enter amount to withdraw = ";
    cin>>wd; 
    if(wd<=amount) 
    {
        amount -= wd; 
        cout<<"\n Amount is withdrawed."; 
    }
    else
    {
        cout<<"\n You don't have enough amount in the bank."; 
    }
    cout<<"\n Remaining amount: "<<amount; 
}

void bankmanagement::check_account()
{
    cout<< "\n Your name: "<<name; 
    cout<< "\n Your address: "<<address; 
    cout<< "\n Account type: "<<actype; 
    cout<< "\n Amount= "<<amount; 
}

void bankmanagement::modifyaccount()
{
    cout<<"\n Account No. : "<<accno; 
    cout<<"\n Modify Account Holder Name : ";
    cin>>name; 
    cout<< "\n Modify your address: ";
    cin>> address; 
    cout<<"\n Modify Type of Account: saving (s) or Current (c): ";
    cin>>actype; 
    cout<<"\n Account is modified."; 
}

void bankmanagement::deleteaccount()
{
    accno=0; 
    name=""; 
    address=""; 
    actype='\0'; 
    amount=0.0; 
    cout<<"\n Successfully deleted."; 
}
