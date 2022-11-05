#include <iostream>
#include <string>
#include <cassert>
#include <cctype>
using namespace std;

bool isValidStateCode(string stateCode)
{
    const string codes =
    "AL.AK.AZ.AR.CA.CO.CT.DE.FL.GA.HI.ID.IL.IN.IA.KS.KY."
    "LA.ME.MA.MD.MI.MN.MS.MO.MT.NE.NV.NH.NJ.NM.NY.NC.ND."
    "OH.OK.OR.PA.RI.SC.SD.TN.TX.UT.VT.VA.WA.WV.WI.WY";
    return (stateCode.size() == 2  &&
            stateCode.find('.') == string::npos  &&  // no '.' in stateCode
            codes.find(stateCode) != string::npos);  // match found
}
void ConvertToUpperCase(string& pollData) { // forces state codes to uppercase for testing
    for (int i = 0; i < pollData.size(); i++) {
        pollData[i] = toupper(pollData[i]);
    }
}
bool HasInvalidCharacters(string pollData) { // checks for anything other than number letter or comma
    for (int i = 0; i < pollData.size(); i++) {
        if (!isalnum(pollData.at(i)) && pollData.at(i) != ',') {
            return true;
        }
    }
    return false;
}

bool isValidStateForcast(string stateForecast) { // takes string of state forecast and checks validity
    if (stateForecast.size() < 2) {
        return false;
    }
    if (!isValidStateCode(stateForecast.substr(0,2))) {
        return false;
    }
    if (stateForecast.size() == 2){
        return true;
    }
    int i = 2;
    while (i < stateForecast.size()) {
        int tempIndex = i;
        while (tempIndex < stateForecast.size()){
            if (!isdigit(stateForecast[tempIndex])) {
                return false;
            }
            else if (!isalnum(stateForecast[tempIndex + 1])){
                return false;
            }
            else if (isdigit(stateForecast[tempIndex + 1]) && (!isalpha(stateForecast[tempIndex + 2]))){
                return false;
            }
            else if ((tempIndex != stateForecast.size()-1) && (!isalnum(stateForecast[tempIndex + 1]))){
                return false;
            }
            else if (isdigit(stateForecast[tempIndex + 1]) && (isalpha(stateForecast[i + 3]))){
            return false;
            }
            else if (isdigit(stateForecast[tempIndex]) && (isalpha(stateForecast[tempIndex + 1]))
            && (isalpha(stateForecast[i + 2]))){
            return false;
            }
            else if (isalpha(stateForecast[tempIndex + 2])){
                tempIndex = tempIndex + 3;
            }
            else if (isalpha(stateForecast[tempIndex + 1])){
                tempIndex = tempIndex + 2;
        }
        i = tempIndex;
        }
    }
    return true;
}

bool isValidPollString(string pollData) { // uses functions that check validity to create stateforecast complete final check before count
    
    if (HasInvalidCharacters(pollData)) {
        return false;
    }
    ConvertToUpperCase(pollData);
    if (isdigit(pollData[0])){
        return false;
    }
        else if (isdigit(pollData[1])){
            return false;
    }
    if (pollData.size() == 2){
        return true;
    }
    int i = 0;
    while (i < pollData.size()) { // creates state forecast string to check validity
        string stateForecast;
        int currentIndex = i;
        while (currentIndex < pollData.size() && pollData[currentIndex] != ',') {
            stateForecast += pollData[currentIndex];
            currentIndex++;
        }
        i = currentIndex + 1;
        if (!isValidStateForcast(stateForecast))
            return false;
        if (pollData.at(pollData.size()-1) == ','){
            return false;
        }
    }
    return true;
}

int countSeats(string pollData, char party, int& seatCount) {
    
    if (!isValidPollString(pollData)) {
        return 1;
    }
    if (!isalpha(party)) {
        return 2;
    }
    int totalCount = 0;
    string stateForecast;
    seatCount = 0;
    party = toupper(party);
    
    for (int a = 0; a < pollData.size(); a++){ //
        pollData[a] = toupper(pollData[a]);
    }
        int i =0;
        while(i < pollData.size()){
            while ((pollData[i] != ',') && (i < pollData.size())) { // breaking poll data into stateforecast again
                    stateForecast += pollData[i];
                    i++;
                    }
            
                for (int j = 2; j < stateForecast.size(); j++) { // checking for first digit
                        if (party == stateForecast[j]) {
                            int initialDigit = ((int)stateForecast[j - 1] - 48); //use of 48 here for ascii vakue to convert to int
                            totalCount += initialDigit;
                        
                        if (isdigit(stateForecast[j -2])){
                            int nextDigit = ((int)stateForecast[j - 2] - 48) * 10;
                            totalCount += nextDigit;
                        }
                        }
                    seatCount += totalCount;
                    totalCount = 0;
                    }
            stateForecast = "";
            i+=1;
    }
        return 0;
    
    }
    
int main(){
    if (isValidPollString("NY9R16D1I,Vt,NJ3d5r4D,KS4R"))
        cerr << "Passed test valid string: isValidPollString(\"CA34D12R2I,nV9R,vt,Ny3r9I13D\")" << endl; // checking valid string
    if (!isValidPollString("53"))
        cerr << "Passed test random number: !isValidPollString(\"53\")" << endl; // checking random number
    if (!isValidPollString("VT2dd"))
        cerr << "Passed test extra letter: !isValidPollString(\"VT2dd\")" << endl; // checking for extra party letter
    if (isValidPollString("vT"))
        cerr << "Passed test valid state: isValidPollString(\"vT\")" << endl; // checking just a state code
    if (!isValidPollString("NY9R16D1I,Vt,NJ3d5r4D,KS4R,"))
        cerr << "Passed test comma end: !isValidPollString(\"NY9R16D1I,Vt,NJ3d5r4D,KS4R,\")" << endl; // checking for comma in the end
    if (!isValidPollString(",NY9R16D1I,Vt,NJ3d5r4D,KS4R"))
        cerr << "Passed test comma beginning: !isValidPollString(\",NY9R16D1I,Vt,NJ3d5r4D,KS4R\")" << endl; // checking for comma in the beginning
    if (!isValidPollString("QT5D,NY9R16D1I,Vt,NJ3d5r4D,KS4R"))
        cerr << "Passed test invalid state code: !isValidPollString(\"QT5D,NY9R16D1I,Vt,NJ3d5r4D,KS4R\")" << endl; // checking for incorrect state code
    if (!isValidPollString("--=="))
        cerr << "Passed test invalid characters: !isValidPollString(\"--==\")" << endl; // checking for random characters
    if (!isValidPollString("VTdjdjdj"))
        cerr << "Passed test invalid after state code: !isValidPollString(\"VTdjdjdj\")" << endl; // checking for letters after state code
    if (!isValidPollString("odfjvhasdf"))
        cerr << "Passed test invalid whole: !isValidPollString(\"odfjvhasdf\")" << endl; // checking if the whole string is invalid
    if (!isValidPollString("NY9R16D1I,Vt, NJ3d5r4D,KS4R"))
        cerr << "Passed test spaces: !isValidPollString(\"NY9R16D1I,Vt, NJ3d5r4D,KS4R\")" << endl; //checking for spaces
    if (isValidPollString(""))
        cerr << "Passed test empty string: isValidPollString(\"\")" << endl; // checking for empty string
    if (isValidPollString("NY,vT,Al,CA"))
        cerr << "Passed test empty data: idValidPollString(\"NY,vT,Al,CA\")" << endl; // checking for no data given
    int seats = 0;
    if (countSeats("NY9R16D1I,Vt,NJ3d5r4D,KS4R", 'd', seats) == 0  &&  seats == 23)
        cerr << "Passed test valid seats: countSeats(\"NY9R16D1I,Vt,NJ3d5r4D,KS4R\", 'd', seats)" << endl; // checking a valid input for seats
    return 0;
}



