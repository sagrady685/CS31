#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>
using namespace std;

int main() {
    
    // Asks user for data and responds accordingly with/without error messages
    string name;
    double taxableIncome;
    string occupation;
    int numberOfChildren;
    
    cout << "Name: ";
    getline(cin,name);
    if (name == ""){
        cout << "---" << endl ;
        cout << "You must enter a name\n";
        return 1;
    }
    cout << "Taxable income: ";
    cin >> taxableIncome;
    if (taxableIncome < 0){
        cout << "---" << endl;
        cout << "The taxable income must not be negative\n";
        return 1;
    }
    cin.ignore(10000, '\n');
    cout << "Occupation: ";
    getline(cin,occupation);
    if (occupation == ""){
        cout << "---" << endl;
        cout << "You must enter an occupation\n";
        return 1;
    }
    cout << "Number of children: ";
    cin >> numberOfChildren;
    if (numberOfChildren < 0){
        cout << "---" << endl;
        cout << "The number of children must not be negative\n";
        return 1;
    }
    
    //deals with initial 70000 taxable income
    double lowerBracket = taxableIncome;
    double lowerBracketDue = 0;
    double middleBracket = taxableIncome - 55000;
    double middleBracketDue = 0;
    double topBracket = taxableIncome - 125000;
    double topBracketDue = 0;
    double taxRateMiddle = 0.07;
    
    //deals with instances where occupation is nurse or teacher
    if ((occupation == "nurse") || (occupation == "teacher")){
        taxRateMiddle = 0.05;
    }
    //taxing income under 55000
    if (taxableIncome <= 55000){
        lowerBracketDue = lowerBracket * 0.04;
    }
    else{
        lowerBracketDue = 2200;
    }
    //taxing income between 55000 and 125000
    if ((taxableIncome > 55000) && (taxableIncome <= 125000)){
        middleBracketDue = middleBracket * taxRateMiddle;
    }
    else if (taxableIncome > 125000)
        middleBracketDue = taxRateMiddle * 70000;
    
    //taxing income over 125000
    if (taxableIncome > 125000){
        topBracketDue = topBracket * 0.093;
    }
    
    double amountDue = lowerBracketDue + middleBracketDue + topBracketDue;
    
    //deals with instances where taxpayer has children
    if ((numberOfChildren > 0) && (taxableIncome < 125000)){
        amountDue = amountDue - (numberOfChildren * 200);
    }
    
    if (amountDue < 0){
        amountDue = 0;
    }
    
    //Output statement to 2 decimal points
    cout << "---" <<endl;
    cout << name << " would pay $" << fixed << setprecision(2)<< amountDue << endl;
}
