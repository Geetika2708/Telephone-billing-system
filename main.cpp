#include <iostream>
#include<bits/stdc++.h>
#include<sstream>
#include <conio.h>
#include <string.h>
#include <unistd.h>
#include <cstdlib>
#include<fstream>
#include <time.h>
using namespace std;

const std::string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}

void
cls ()
{
  cout << "\033[2J\033[1;1H";
}

unordered_map < long long, int >um;
unordered_map<int,int> plans;

class Customers{
    public:
    string name;
    string aadharNum;
    long long phone_no;
    int plan_amount;
    string expiry;
    string recharge_date;
}ob[50];

vector < Customers >number_array;
bool
has_any_digits (const std::string & s)
{
  return any_of (s.begin (), s.end (),::isdigit);
}

bool
has_any_alpha (const std::string & s)
{
  return any_of (s.begin (), s.end (),::isalpha);
}
bool
number_validation (long long phone_no)
{
  for (int i = 0; i < number_array.size (); i++)
    {
      if (number_array[i].phone_no == phone_no)
	{
	  cout << "\t\t Validation successful \t\t" << endl;
	  sleep (2);
	  return true;
	  break;
	}
    }
  return false;
}

void current_date(int &year,int& month,int& day){
    string local_date=currentDateTime();
  string year_str="",month_str="",day_str="";
  for(int i=0;i<4;i++){
    year_str+=local_date[i];
  }
  for(int i=5;i<7;i++){
    month_str+=local_date[i];
  }
  for(int i=8;i<10;i++){
    day_str+=local_date[i];
  } 
    year=stoi(year_str);
    month=stoi(month_str);
    day=stoi(day_str);
}

void
payment (int plan_amount,long long phone_no)
{
  int o;
  int amu;			// amount
  string upi;
  string mpin;
  string cno;			// card number
  long long cdt;		// valid date
  string cn;			// card holder name
  string cvv;			// card cvv
  ofstream fout("payment.txt",ios::app);
  cout << "Payment type :" << endl;
  cout << "\t\t1. UPI \n";
  cout << "\t\t2. CARD \n";

  cout << "Enter your choice :" << endl;
  cin >> o;
  switch (o)
    {
    case 1:
      while (true)
	{
	  cout << "Enter your UPI id (10 digits) :" << endl;
	  cin >> upi;
	  if (upi.size () < 10 || upi.size () > 10)
	    {
	      cout <<
		"\t\t Upi number should be of 10 numbers  Try again! \t\t" <<
		endl << endl;
	      continue;
	    }
	  if (upi[0] == '0')
	    {
	      cout <<
		"\t\t Upi number can not start with zero. try again! \t\t" <<
		endl << endl;
	      continue;
	    }
	  cout << "Enter your MPIN (should be of 4 number) :" << endl;
	  cin >> mpin;
	  if (mpin.size () < 4 || mpin.size () > 4)
	    {
	      cout << "\t\t mpin should be of 4 number  try again! \t\t" <<
		endl << endl;
	      continue;
	    }
	  break;
	}
      cout << "***************PAYMENT SUCCESSFUL*******************" << endl;
      sleep (2);
      cls ();
      break;
    case 2:
      while (true)
	{
	  cout << "Enter your card number (16 digits) :" << endl;
	  cin >> cno;
	  if (cno.size () < 16 or cno.size () > 16)
	    {
	      cout <<
		"\t\t card number should have 16 digits.  try again! \t\t" <<
		endl << endl;
	      continue;
	    }
	  if (cno[0] == '0')
	    {
	      cout <<
		"\t\t card number can not start with zero. try again! \t\t" <<
		endl << endl;
	      continue;
	    }
	  if (has_any_alpha (cno))
	    {
	      cout << "\t\t card number can not contain alphabets \t\t" <<
		endl << endl;
	      continue;
	    }
	  cout << "Enter valid date :" << endl;
	  cin >> cdt;
	  cout << "Enter card holder name (should only contain alphabets) :"
	    << endl;
	  cin >> cn;
	  if (has_any_digits (cn))
	    {
	      cout <<
		"\t\t card holder name can not contain digits  try again! \t\t"
		<< endl << endl;
	      continue;
	    }
	  cout << "Enter CVV (3 digits) :" << endl;
	  cin >> cvv;
	  if (cvv.size () < 3 or cvv.size () > 3)
	    {
	      cout << "\t\t cvv should be of 3 digits. try again!" << endl <<
		endl;
	      continue;
	    }
	  if (has_any_alpha (cvv))
	    {
	      cout << "\t\t cvv can not contain aplhabets. try again!" << endl
		<< endl;
	      continue;
	    }
	  break;

	}

      cout << "***************PAYMENT SUCCESSFUL*******************" << endl;
      sleep (2);
      cls ();
      break;

    default:
      cout << "invalid choice try again!" << endl << endl;
      payment (plan_amount,phone_no);
    }
    int id;
    for(int i=0;i<number_array.size();i++){
        if(number_array[i].phone_no==phone_no){
            id=i;
            break;
        }
    }
    int year,month,day;
    current_date(year,month,day);
    number_array[id].recharge_date=to_string(year)+"/"+to_string(month)+"/"+to_string(day);
    int plan_days=plans[plan_amount];
    int plan_month=0;
    if(day+plan_days>30){
        int total_days=day+plan_days;
        plan_month+=(total_days)/30;
        day=(day+plan_days)%30;
        day=day==0?30:day;
    }
    if(plan_month+month>12){
        year++;
        month=(plan_month+month)%12;
        month=month==0?30:month;
    }else{
        month+=plan_month;
    }
    fout<<"Phone No : "<<phone_no<<"\t"<<"Plan Amount : "<<plan_amount<<"\t"<<"Expires on : "<<year<<"/"<<month<<"/"<<day<<endl;
    number_array[id].plan_amount=plan_amount;
    number_array[id].expiry=to_string(year)+" "+to_string(month)+" "+to_string(day);
     fout.close();
     ofstream new_file("Active_no.txt",ios::app);
     new_file <<"Name : "<<number_array[id].name<<" Adhaar No : "<<number_array[id].aadharNum<<" Mobile No : "<<number_array[id].phone_no<<" Plan Amount : "<<plan_amount<<" Expires on : "<<year<<"/"<<month<<"/"<<day<<endl;
     new_file.close();
     getchar();
}

void
intro ()
{
  cout <<
    "\n\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
  cout <<
    "\n\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
  cout << "\n\t\t|| || ";
  cout <<
    "\n\t\t||-----------------------------------------------------------||";
  cout << "\n\t\t|| Mobile Billing Management System ||";
  cout <<
    "\n\t\t||-----------------------------------------------------------||";
  cout << "\n\t\t|| ||";
  cout <<
    "\n\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
  cout <<
    "\n\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    << endl;
}

void show_current_plan(){

    long long phone_no;
    int plan_amount;
  cout << "\t\t Enter Your Phone Number \t\t" << endl;
  cin >> phone_no;
  if (!number_validation (phone_no))
    {
      cout << "\t\t Invalid Number \t\t" << endl;
      return;
    }
  if (um.find (phone_no) != um.end ())
    {
        plan_amount=um[phone_no];
      cout << "\t\t\t  Plan amount is : \t" << um[phone_no] << endl;
      cout << "\t\t\t  Plan validity is : \t" << plans[plan_amount] << endl;
      for(int i=0;i<number_array.size();i++){
        if(number_array[i].phone_no==phone_no){
            cout << "\t\t\t  Your Recharge date is : \t" << number_array[i].recharge_date << endl;
            cout << "\t\t\t  Your Plan will expire on : \t" << number_array[i].expiry << endl;
            break;
        }
      }
    }
  else
    {
      cout <<
	"\t\t\t There is no active plan on this number please choose one!  \t\t"
	<< endl << endl;
    }
}

void
show_plans ()
{
    long long phone_no;
  cout << "\t\t Enter Your Phone Number \t\t" << endl;
  cin >> phone_no;
  if (!number_validation (phone_no))
    {
      cout << "\t\t Invalid Number \t\t" << endl;
      return;
    }
  int plan_amount;
  cout << " Plan \t Amount \t Validity \t Data" << endl;
  cout << " Plan 1:\t 199 \t 28 Days \t 1.5 GB/Day" << endl;
  cout << " Plan 2:\t 399 \t 56 Days \t 2 GB/Day" << endl;
  cout << " Plan 3:\t 699 \t 84 Days \t 1.5 GB/Day" << endl;
   plans[199]=28;
  plans[399]=56;
  plans[699]=84;
  int choice = 0;
  cout << "\n Do you want to make payment press 1 for yes and 0 for no \t" <<
    endl;
  cin >> choice;
  while (choice)
    {
      cout << "Enter the plan amount" << endl;
      cin >> plan_amount;
      if (plan_amount == 199 || plan_amount == 399 || plan_amount == 699)
	{
	    payment (plan_amount,phone_no);
	      um[phone_no] = plan_amount;
	  break;
	}
      else
	{
	  cout << "\t\t Plan amount is invalid!  Try Again! \t\t" << endl;
	}

    }
}

void
help ()
{
  cout << "\t\tWELCOME TO CUSTOMER CARE \n";
  cout << "\t\tCUSTOMER CARE NUMBER : \n";
  cout << "\t\t Interested in Jio Talk to us on 1860-893-3333 \n";
  cout << "\t\t For Queries 199 \n";
  cout << "\t\t For Complaints 198 \n";
  cout << "\t\t Calling from Non Jio number 1800-889-9999 \n";
}

void admin(){
    string name="geetika";
    string password ="****";
    string entered_name,entered_password;
    cout << "\n\t\t\t|| Enter your name (case sensitive) || " << endl;
    cin>>entered_name;
    cout << "\n\t\t\t|| Enter your password || " << endl;
    cin>>entered_password;
    if(name!=entered_name and password!=entered_password){
        cout << "\n\t\t\t|| Wrong credentials Try again! || " << endl;
        return;
    }
    ifstream in;
    in.open("Active_no.txt");
    cout<<"\t\t\t || Active contact list : || \t\t\t"<<endl;
    cout<<endl;
    string details;
    while(getline(in,details)){
        cout<<details<<endl;
    }
    in.close();
    getchar();
}

void
disp ()
{

  cout << "\t\t\t****************************************************";
  cout << "\n\t\t\t|| Press 1 Apply for new connection || " << endl;
  cout << "\n\t\t\t|| Press 2 Show Plan || " << endl;
  cout << "\n\t\t\t|| Press 3 Display a bill || " << endl;
  cout << "\n\t\t\t|| Press 4 Current plan details || " << endl;
  cout << "\n\t\t\t|| Press 5 Help || " << endl;
  cout << "\n\t\t\t|| Press 6 Admin || " << endl;
  cout << "\n\t\t\t|| Press 7 Exit || " << endl;
  cout << "\t\t\t******************************************************\n";
}

void
apply ()
{
  string aadharNum,name;
  long long lb = 9000000000, ub = 9999999999;
  ofstream fout("Inactive.txt",ios::app);
  cout << "\t\t\t****************************************************";
  cout << "\n\t\t\t|| Enter Your Name || " << endl;
  cin>>name;
  cout << "\n\t\t\t|| Enter Your Aadhar Number (12 digits) || " << endl;
  cin >> aadharNum;
  if (aadharNum.size () < 12 || aadharNum.size () > 12)
    {
      cout <<
	"\n\t\t\t|| Aadhar number can not be less/more than 12 number!    Try Again! || "
	<< endl << endl;
      return;
    }
  if (aadharNum[0] == '0')
    {
      cout <<
	"\n\t\t\t|| Aadhar number can not start with zero!    Try Again! || "
	<< endl << endl;
      return;
    }
  long long new_number;
  while (true)
    {
      new_number = (rand () % (ub - lb + 1)) + lb;
      if (um.find (new_number) == um.end ())
	{  int size=number_array.size(); 
	  ob[size].phone_no=new_number;
      ob[size].name=name;
      ob[size].aadharNum=aadharNum;
      number_array.push_back(ob[size]);
	  break;
	}
    }
  cout << "\n\t\t\t|| Your New Mobile Number is : " << new_number << " || " <<
    endl;
  cout << "\t\t\t******************************************************\n";
  cout << "                  Thank You!" << endl;
  fout <<"Name : "<<name<<" Adhaar No : "<<aadharNum<<" Mobile No : "<<new_number<<endl;
  fout.close();
  cin.ignore ();
  getchar ();

}

void
displayBill ()
{
  long long mobileNum = 0;
  long long lb = 1000, ub = 9999;
  cout << "\t\t\t ****************************************************";
  cout << "\n\t\t\t|| Enter Your Mobile Number || " << endl;
  cin >> mobileNum;
  if (!number_validation (mobileNum))
    {
      cout << "\t\t\t Mobile Number is not registered! \t\t" << endl << endl;
      return;
    }
  if (um.find (mobileNum) == um.end ())
    {
      cout <<
	"\n\t\t\t|| There is no active paln on this monile number!    Please choose a plan! || "
	<< endl;
      return;
    }
    int year,month,date,expiry_date,expiry_year,expiry_month;
    string expiry_year_str,expiry_month_str,expiry_date_str;
    current_date(year,month,date);
    int id;
    for(int i=0;i<number_array.size();i++){
        if(number_array[i].phone_no==mobileNum){
            id=i;
            stringstream ss(number_array[i].expiry);
            ss>>expiry_year_str;
            ss>>expiry_month_str;
            ss>>expiry_date_str;
            expiry_year=stoi(expiry_year_str);
            expiry_month=stoi(expiry_month_str);
            expiry_date=stoi(expiry_date_str);
            break;
        }
    }
    if(expiry_year>year){
        cout<<"\t\t\t Your plan expire on "<<expiry_year<<"/"<<expiry_month<<"/"<<expiry_date<<endl;
        cout<<"You can pay only after your plan expires Thankyou!"<<endl;
        return;
    }
    if(expiry_month>month){
        cout<<"\t\t\t Your plan expire on "<<expiry_year<<"/"<<expiry_month<<"/"<<expiry_date<<endl;
        cout<<"\t\t\t You can pay only after your plan expires Thankyou!"<<endl;
        return;
    }
    if(expiry_date>date){
        cout<<"\t\t\t Your plan expire on "<<expiry_year<<"/"<<expiry_month<<"/"<<expiry_date<<endl;
        cout<<" \t\t\t You can pay only after your plan expires Thankyou!"<<endl;
        return;
    }
  cout << "\n\t\t\t|| Your Bill Amount is : " << um[mobileNum] << " || " <<
    endl;
  cout << "\t\t\t Do you want to make payment press 1 for yes or 0 for no" << endl;
  int choice;
  cin>>choice;
  if(choice){
    payment(um[mobileNum],mobileNum);
  }
  getchar ();
}

void
mainchoices ()
{
    
  disp ();
  cout << "\n\t\tEnter your choice ::";
  int choice;
  cin >> choice;
  switch (choice)
    {
    case 1:
      cls ();			// clean privious output screen
      apply ();
      break;
    case 2:
      cls ();
      show_plans ();
      break;
    case 3:
      cls ();
      displayBill ();
      break;
    case 4:
     cls ();
      show_current_plan();
      break;
    case 5:
      cls();
      help();

      break;
     case 6:
        cls();
      admin();
      break; 
    case 7:
      cls ();
      exit (0);
      break;
    default:
      cout << "\t\t\tYou have enterd wrong choice  try again";
      cout << "\a";
      mainchoices ();
    }
}

int
main ()
{   

  intro ();
  for (;;)			// run infinity time until you press exit button.
    {

      mainchoices ();
    }
  return 0;
}
