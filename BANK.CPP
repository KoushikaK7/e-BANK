#include<fstream.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<math.h>

//Customer Data
struct customer
{
int accno;
char accname[15];
char addr[20];
char city[10];
char state[10];
long int pin;
};

//FD,RD Deposit Data
struct deposit
{
int accno;//accno from Customer Data
char dep_type;//'F'for FD and 'R' for RD
long int amount;//Deposit amount
int period;//Deposit Term in months
};

struct date
{
int day;
int month;
int year;
};

//SB Transaction data
struct trans
{
int accno;//accno from Customer Data
date date1;//Transaction date of type struct date
char trans_type;//'C' for Deposit and 'D' for withdrawl
long int amount;//Transaction amount
};

int validate_date(date d1)
{
  if(d1.day<1 || d1.day>31)
   return 0;
  if(d1.month<1 || d1.month>12)
   return 0;
  if(d1.year<2000 || d1.year>2016)
   return 0;
  return 1;
}

//Deposit Maturity date calculation
date mat_date_calc(date dt1, int pr)
{
  int mon=pr%12;
  int yr=pr/12;
  if((dt1.month+mon)>12)
  {
   dt1.month=(dt1.month+mon)-12;
   yr++;
  }
  else
   dt1.month=dt1.month+mon;
  dt1.year+=yr;
  return dt1;
}

//Add Account
void add_account()
{
customer cust1,cust2;
int acno=1000;
fstream file1("Master.dat",ios::in|ios::binary);
while(file1.read((char*)&cust1,sizeof(cust1)))
{
acno=cust1.accno;
}
file1.close();
acno++;
cout<<"Enter customer details\n";
cout<<"Accout No.: "<<acno<<"\n";
cust2.accno=acno;
cout<<"Name      : " ;
cin>>cust2.accname;
cout<<"Address   : ";
cin>>cust2.addr;
cout<<"City      : ";
cin>>cust2.city;
cout<<"State     : ";
cin>>cust2.state;
cout<<"Pincode   : ";
cin>>cust2.pin;
file1.open("Master.dat",ios::out|ios::binary|ios::app);
file1.write((char*)&cust2,sizeof(cust2));
file1.close();
}

//Modify Account details
void modify_account()
{
 fstream file1("Master.dat",ios::in|ios::binary);
 fstream file2("temp.dat",ios::out|ios::binary);
 customer cust1,cust2;
 int acno;
 char flag='n';
 cout<<"Enter the Account Number to be modified\n";
 cin>>acno;
 file1.read((char*)&cust1,sizeof(cust1));
 while(file1)
 {
  if(cust1.accno!=acno)
   file2.write((char*)&cust1,sizeof(cust1));
  else
  {
   flag='y';
   cout<<"Existing Customer Details\n";
   cout<<cust1.accno<<"  "<<cust1.accname<<"  "<<cust1.addr<<"  "<<cust1.city<<"  "<<cust1.state<<"  "<<cust1.pin<<"\n";
   cout<<"Enter customer`s new details\n";
   cout<<"Accout No.: "<<acno<<"\n";
   cust2.accno=acno;
   cout<<"Name      : " ;
   cin>>cust2.accname;
   cout<<"Address   : ";
   cin>>cust2.addr;
   cout<<"City      : ";
   cin>>cust2.city;
   cout<<"State     : ";
   cin>>cust2.state;
   cout<<"Pincode   : ";
   cin>>cust2.pin;
   file2.write((char*)&cust2,sizeof(cust2));
  }
  file1.read((char*)&cust1,sizeof(cust1));
 }
 if(flag=='n')
  cout<<"Given Account Number not found\n";
 else
 {
  file1.close();
  file2.close();
  remove("Master.dat");
  rename("temp.dat","Master.dat");
 }
}

//Delete an Account
void delete_account()
{
 fstream file1("Master.dat",ios::in|ios::binary);
 fstream file2("temp.dat",ios::out|ios::binary);
 customer cust1;
 int acno;
 char flag='n';
 cout<<"Enter the Account Number to be deleted\n";
 cin>>acno;
 file1.read((char*)&cust1,sizeof(cust1));
 while(file1)
 {
  if(cust1.accno!=acno)
   file2.write((char*)&cust1,sizeof(cust1));
  else
  {
   flag='y';
  }
  file1.read((char*)&cust1,sizeof(cust1));
 }
 if(flag=='n')
  cout<<"Given Account Number not found\n";
 else
 {
  file1.close();
  file2.close();
  remove("Master.dat");
  rename("temp.dat","Master.dat");
 }
}

//Display all the Account details
void account_display()
{
char *space1 = "                                                   ";
customer cust1;
fstream file1("Master.dat",ios::in|ios::binary);
cout<<"Acc No.\t"<<" Account Name  "<<"     Address        "<<"   City   "<<"  State   "<<"Pincode\n";
while(file1.read((char*)&cust1,sizeof(cust1)))
{
 char name[15],address[20],city[10],state[10];
 strcpy(name,cust1.accname);
 cout<<cust1.accno<<"\t";
 cout<<strncat(name,space1,(15-strlen(name)));
 strcpy(address,cust1.addr);
 cout<<strncat(address,space1,(20-strlen(address)));
 strcpy(city,cust1.city);
 cout<<strncat(city,space1,(10-strlen(city)));
 strcpy(state,cust1.state);
 cout<<strncat(state,space1,(10-strlen(state)));
 cout<<cust1.pin<<"\n";
 //cout<<cust1.accno<<"\t"<<cust1.accname<<"\t"<<cust1.addr<<"\t"<<cust1.city<<"\t"<<cust1.state<<"\t"<<cust1.pin<<"\n";
}
file1.close();
}

//Deposit Money
void deposit_money(date dt)
{
 customer cust1;
 trans trans1;
 int acno;
 char flag='n';
 cout<<"Account Number   : ";
 cin>>acno;
 fstream file1("Master.dat",ios::in|ios::binary);
 while(file1.read((char*)&cust1,sizeof(cust1)))
 {
  if(cust1.accno==acno)
  {
    cout<<"Account Name     : "<<cust1.accname<<"\n";
    flag='y';
    break;
  }
 }
 file1.close();
 if(flag=='n')
 {
  cout<<"Account Number is invalid...Try again\n";
  return;
 }
 trans1.accno=acno;
 trans1.date1=dt;
 trans1.trans_type='C';
 cout<<"Deposit Amount   : ";
 cin>>trans1.amount;
 fstream file2("Trans.dat",ios::out|ios::binary|ios::app);
 file2.write((char*)&trans1,sizeof(trans1));
 file2.close();
}

//Withdraw Money
void withdraw_money(date dt)
{
 customer cust1;
 trans trans1,trans2;
 int acno;
 char flag='n';
 long int balance=0;
 cout<<"Account Number   : ";
 cin>>acno;
 fstream file1("Master.dat",ios::in|ios::binary);
 while(file1.read((char*)&cust1,sizeof(cust1)))
 {
  if(cust1.accno==acno)
  {
    cout<<"Account Name     : "<<cust1.accname<<"\n";
    flag='y';
    break;
  }
 }
 file1.close();
 if(flag=='n')
 {
  cout<<"Account Number is invalid...Try again\n";
  return;
 }
 trans1.accno=acno;
 trans1.date1=dt;
 trans1.trans_type='D';
 fstream file2("Trans.dat",ios::in|ios::binary);
 while(file2.read((char*)&trans2,sizeof(trans2)))
 {
  if(trans2.accno==acno)
  {
    if(trans2.trans_type=='C')
     balance+=trans2.amount;
    else
     balance-=trans2.amount;
  }
 }
 file2.close();
 cout<<"Account Balance   : "<<balance<<"\n";
 cout<<"Withdraw Amount   : ";
 cin>>trans1.amount;
 if(trans1.amount+1000>balance)
 {
  cout<<"Maximum Withdrawl amount = "<<balance-1000<<" Pl. try again...\n";
  return;
 }
 else
 {
  file2.open("Trans.dat",ios::out|ios::binary|ios::app);
  file2.write((char*)&trans1,sizeof(trans1));
  file2.close();
 }
}

//List Transactions
void list_trans()
{
 trans trans1;
 cout<<"\t\tTransactions List\n";
 cout<<"Date\t\tAcc_no\tAmount\tTrans_type\n";
 fstream file1("Trans.dat",ios::in|ios::binary);
 while(file1.read((char*)&trans1,sizeof(trans1)))
 {
   cout<<trans1.date1.day<<"/"<<trans1.date1.month<<"/"<<trans1.date1.year<<"\t";
   cout<<trans1.accno<<"\t";
   cout<<trans1.amount<<"\t";
   cout<<trans1.trans_type<<"\n";
 }
 file1.close();
}

//Fixed Deposit
void fixed_deposit(date dt)
{
 customer cust1;
 deposit deposit1;
 int acno;
 char flag='n';
 float maturity_value=0.0;
 float int_rate=8.50;
 cout<<"Account Number   : ";
 cin>>acno;
 fstream file1("Master.dat",ios::in|ios::binary);
 while(file1.read((char*)&cust1,sizeof(cust1)))
 {
  if(cust1.accno==acno)
  {
    deposit1.accno=acno;
    deposit1.dep_type='F';
    cout<<"Amount           : ";
    cin>>deposit1.amount;
    cout<<"Period in months : ";
    cin>>deposit1.period;
    date maturity_date=mat_date_calc(dt,deposit1.period);
    int nt=(deposit1.period*4)/12;
    maturity_value=deposit1.amount*(pow((1+int_rate/400),nt));
    cout<<"***************************************************************************\n";
    cout<<"                            Fixed Deposit Certificate                      \n";
    cout<<"  Certificate No: 0000203408                             Date: ";
    cout<<dt.day<<"/"<<dt.month<<"/"<<dt.year<<"  \n";
    cout<<"  Account No: "<<acno<<"\n";
    cout<<"  "<<cust1.accname<<"\n";
    cout<<"  "<<cust1.addr<<"  "<<cust1.city<<"\n";
    cout<<"  "<<cust1.state<<"  "<<cust1.pin<<"\n";
    cout<<"                                                                           \n";
    cout<<"                                                                           \n";
    cout<<"  Principal Amount : "<<deposit1.amount<<"                          Interest Rate : "<<int_rate<<"   \n";
    cout<<"  Period           : "<<deposit1.period<<" months                 Maturity Date : ";
    cout<<maturity_date.day<<"/"<<maturity_date.month<<"/"<<maturity_date.year<<"   \n";
    cout<<"  Maturity value   : "<<maturity_value<<"                                                \n";
    cout<<"***************************************************************************\n";
    flag='y';
    break;
  }
 }
 file1.close();
 if(flag=='n')
 {
  cout<<"Account Number is invalid...Try again\n";
  return;
 }
 else
 {
  fstream file2("Deposit.dat",ios::out|ios::binary|ios::app);
  file2.write((char*)&deposit1,sizeof(deposit1));
  file2.close();
 }
}

//Recurring Deposit
void recurring_deposit(date dt)
{
 customer cust1;
 deposit deposit1;
 int acno;
 char flag='n';
 float maturity_value=0.0;
 float int_rate=8.5;
 cout<<"Account Number   : ";
 cin>>acno;
 fstream file1("Master.dat",ios::in|ios::binary);
 while(file1.read((char*)&cust1,sizeof(cust1)))
 {
  if(cust1.accno==acno)
  {
    deposit1.accno=acno;
    deposit1.dep_type='R';
    cout<<"Monthly Installment : ";
    cin>>deposit1.amount;
    cout<<"Period in months    : ";
    cin>>deposit1.period;
    date maturity_date=mat_date_calc(dt,deposit1.period);
    int n=(deposit1.period*4)/12;
    float ir=int_rate/400;
    maturity_value=(deposit1.amount*(pow((1+ir),n)-1))/(1-(pow((1+ir),-0.33)));
    cout<<"***************************************************************************\n";
    cout<<"                          Recurring Deposit Certificate                    \n";
    cout<<"  Certificate No: 0000203408                             Date: ";
    cout<<dt.day<<"/"<<dt.month<<"/"<<dt.year<<"  \n";
    cout<<"  Account No: "<<acno<<"                                                         \n";
    cout<<"  "<<cust1.accname<<"                                                                 \n";
    cout<<"  "<<cust1.addr<<"  "<<cust1.city<<"                                                  \n";
    cout<<"  "<<cust1.state<<"  "<<cust1.pin<<"                                                           *\n";
    cout<<"                                                                           \n";
    cout<<"                                                                           \n";
    cout<<"  Monthly Installment : "<<deposit1.amount<<"                        Interest Rate : "<<int_rate<<"  \n";
    cout<<"  Period           : "<<deposit1.period<<" months                 Maturity Date : ";
    cout<<maturity_date.day<<"/"<<maturity_date.month<<"/"<<maturity_date.year<<"  \n";
    cout<<"  Maturity value   : "<<maturity_value<<"                                               \n";
    cout<<"***************************************************************************\n";
    flag='y';
    break;
  }
 }
 file1.close();
 if(flag=='n')
 {
  cout<<"Account Number is invalid...Try again\n";
  return;
 }
 else
 {
  fstream file2("Deposit.dat",ios::out|ios::binary|ios::app);
  file2.write((char*)&deposit1,sizeof(deposit1));
  file2.close();
 }
}

//Get the new Transaction date
date get_date(date d2)
{
  cout<<"current date : "<<d2.day<<"/"<<d2.month<<"/"<<d2.year<<"\n";
  int flag1=0;
  do
  {
   cout<<"Enter date in dd format   : ";
   cin>>d2.day;
   cout<<"Enter month in mm format  : ";
   cin>>d2.month;
   cout<<"Enter year in yyyy format : ";
   cin>>d2.year;
   flag1=validate_date(d2);
   if (flag1==0)
    cout<<"New Date inputs are not valid...Try again\n";
  }while(flag1==0);
  return d2;
}

//Main Program
void main()
{
clrscr();
date bank_date;
bank_date.day=26;
bank_date.month=10;
bank_date.year=2015;
char ch;
do{
cout<<"\t********************************************************************\n";
cout<<"\t*                     Welcome to IBM Bank                          *\n";
cout<<"\t*                                                                  *\n";
cout<<"\t*                         Main Menu                                *\n";
cout<<"\t*  [C]ustomer  [T]ransaction  [D]eposit  [M]odify Date  [E]xit     *\n";
cout<<"\t********************************************************************\n";
cin>>ch;
if(ch=='c' || ch=='C')
{
 char ch1;
 do{
 cout<<"\n\t\tCustomer Master";
 cout<<"\n[A]dd Account\n[E]dit Account\n[L]ist Accounts\n[C]lose Account\n[G]oto Main Menu\n";
 cin>>ch1;
 if(ch1=='a' || ch1=='A')
 {
  cout<<"Adding account\n";
  add_account();
 }
 if(ch1=='e' || ch1=='E')
  modify_account();
 if(ch1=='l' || ch1=='L')
 {
  cout<<"Listing all accounts\n";
  account_display();
 }
 if(ch1=='c' || ch1=='C')
  delete_account();
 if(ch1=='g' || ch1=='G')
  {
   cout<<"Switching to Main Menu\n";
   ch1='g';
   ch='c';
  }
 }while(ch1!='g' && ch1!='G');
}
if(ch=='t' || ch=='T')
{
 char ch2;
 do{
 cout<<"\n\t\tDaily Transactions";
 cout<<"\n[D]eposit\n[W]ithdrawl\n[L]ist Transactions\n[G]oto Main Menu\n";
 cin>>ch2;
 if(ch2=='d' || ch2=='D')
  deposit_money(bank_date);
 if(ch2=='w' || ch2=='W')
  withdraw_money(bank_date);
 if(ch2=='l' || ch2=='L')
  list_trans();
 if(ch2=='g' || ch2=='G')
  cout<<"Switching to Main Menu\n";
 }while(ch2!='g' && ch2!='G');
}
if(ch=='d' || ch=='D')
{
 char ch3;
 do{
 cout<<"\n\t\tDeposits";
 cout<<"\n[F]ixed Deposit\n[R]ecurring Deposit\n[G]oto Main Menu\n";
 cin>>ch3;
 if(ch3=='f' || ch3=='F')
  fixed_deposit(bank_date);
 if(ch3=='r' || ch3=='R')
  recurring_deposit(bank_date);
 if(ch3=='g' || ch3=='G')
  cout<<"Switching to Main Menu\n";
 }while(ch3!='g' && ch3!='G');
}
if(ch=='m' || ch=='M')
{
 date date1=bank_date;
 bank_date=get_date(date1);
}
if(ch=='e' || ch=='E')
{
 cout<<"Exitting.....";
 exit(0);
}
}while(ch!='e' && ch!='E');

getch();
}


