#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int appendToAll(string a[], int n, string value) {
    
    if (n <= 0)
        return -1;
    
    for (int i = 0; i < n; i ++){ // appends value to string a
        a[i] += value;
    }
    return n;
}

int lookup(const string a[], int n, string target) {
    
    if (n <= 0)
        return -1;
    
    for (int i = 0; i < n; i++) { // checks for target
        if (a[i] == target) {
            return i;
        }
    }
    return -1;
}

int positionOfMax(const string a[], int n) {
    
    if (n <= 0)
        return -1;
    
    string maxIndex = a[0];
    int repeat = 0;
    
    for (int i = 0; i < n; i++) { // checks for repeats and returns max string seen earliest
        if (a[i] > maxIndex) {
            maxIndex = a[i];
            repeat = i;
        }
    }
    return repeat;
}
    
int rotateLeft(string a[], int n, int pos) {
    
    if (n < 0)
        return -1;
    
    if (pos < 0)
        return -1;
    
    if (pos > n)
        return -1;
    
    string storage = a[pos]; // stores pos to append at the end
    
    for (int i = pos; i <= n - 2; i++) { // shifts all other elements down one after pos
        a[i] = a[i + 1];
    }
    
    a[n - 1] = storage;
    return pos;
}
int countRuns(const string a[], int n) {
    
    if (n < 0)
        return -1;
    
    int sequence = 0;
    for (int i = 0; i < n - 1; i ++) {
        if (a[i] != a[i  + 1]) {
            sequence += 1;
        }
    }
    return sequence + 1;
}
int flip(string a[], int n) {
    
    if (n < 0)
        return -1;
    
    int end = n - 1;
    int start = 0;
    while (start < end){ // swaps strings until center
        swap(a[start],a[end]);
        start++;
        end--;
    }
    return n;
}
int differ(const string a1[], int n1, const string a2[], int n2) {

    if ((n1 <= 0) || (n2 <= 0))
        return -1;
    
    int i = 0;
    int first = 0;
    
    if (n1 < n2) { // determining which string is smaller
      first = n1;
    }
    else {
        first = n2;
    }
    while (i < first) {
        if (i == first) { // if elements do not mismatch
            return first;
        }
        else if (a1[i] == a2[i]) { // find when elements match
            i++;
        }
        else
            return i;
    }
    return i;
}
int subsequence(const string a1[], int n1, const string a2[], int n2) {
  
    if ((n1 < 0) || (n2 < 0))
        return -1;
    
    else if ((n1 == 0) && (n2 == 0))  //comparing empty strings
        return 0;
    
    if ((n1 > 0) && (n2 == 0)) // if there is no comparable subsequence
        return 0;
    
    
    int i = 0;
    bool isMatch = false;
    
    while (i < n1) {
        if (a1[i] == a2[0]) { // if first check is equal
            for (int j = 0; j < n2; j++){
                if (a1[j + i] == a2[j]){
                    isMatch = true;
                }
                else {
                    isMatch = false;
                }
            }
            if (isMatch == true) {
                return i;
            }
        }
        i++; // next element of a1
    }
    return -1;
}

int lookupAny(const string a1[], int n1, const string a2[], int n2){
    /*
     string names5[10] = {"john", "margaret", "theresa", "rishi", "boris", "liz"};
     string set1[10] = {"david", "boris", "rishi", "margaret"};
     */
    if ((n1 < 0) || (n2 < 0))
        return -1;
    
    int i = 0;
    int j = 0;
    
    while (i < n1){
        while (j < n2){
            if (a1[i] == a2[j]) { // checks every element of a2 to a1
                return i; // returns point at a1
            }
            j++;
        }
        j = 0; // resets for next iteration
        i++;
    }
    return -1;
}

int split(string a[], int n, string splitter) {
    
    if (n < 0)
        return -1;
    
    int i = 0;
    int end = n - 1;
    
    for (i = 0; i < end; i++) { // rearranges string
        while (a[i] > splitter) { // insures i checks swap until false
            swap(a[i],a[end]);
            end --;
        }
    }
    return i;
}
int main() {
    string people[5] = {"sarah", "nicole", "rowdy", "krista", "john"};
    // tests normal case should return 5
    cerr << "appendToAll(people, 5, \"!!!\") = " << appendToAll(people, 5, "!!!") << endl;
    // tests negative input should return -1
    cerr << "appendToAll(people, -4, \"!!!\") = " << appendToAll(people, -4, "!!!") << endl;
    
    string people1[6] = {"sarah", "nicole", "rowdy", "krista", "john", "nick"};
    string people2[6] = {"sarah", "nicole", "rowdy", "rowdy", "john", "nick"};
    // find nicole should return 1
    cerr << "lookup(people1, 6, \"nicole\") = " << lookup(people1, 6, "nicole") << endl;
    // find amanda should return -1 because unknown string
    cerr << "lookup(people1, 6, \"amanda\") = " << lookup(people1, 6, "amanda") << endl;
    // find rowdy, should return 2 even though rowdy appears twice
    cerr << "lookup(people1, 6, \"rowdy\") = " << lookup(people2, 6, "amanda") << endl;

    string ppl[7] = {"david", "liz", "margaret", "tony", "gordon", "boris", "tony"};
    string ppl1[0] = {};
    // finds max and should return first position at 3
    cerr << "positionOfMax(ppl, 7) = " << positionOfMax(ppl, 7) << endl;
    // tests for no interesting elements and should return -1
    cerr << "positionOfMax(ppl1, 0) = " << positionOfMax(ppl1, 0) << endl;

    string rotate[5] = {"john", "david", "liz", "theresa", "margaret"};
    string rotate1[5] = {"john", "david", "liz", "theresa", "margaret"};
    // testing normal instance and should return 1
    cerr << "rotateLeft(rotate, 5, 1) = " << rotateLeft(rotate, 5, 1) << endl;
    // tests for negative input and should return -1
    cerr << "rotateLeft(rotate1, 5, -1) = " << rotateLeft(rotate1, 5, -1) << endl;
    // tests for out of bounds input and should return -1
    cerr << "rotateLeft(rotate1, 5, 6) = " << rotateLeft(rotate1, 5, 6) << endl;
    // tests for negative n value and should return -1
    cerr << "rotateLeft(rotate1, -1, 3) = " << rotateLeft(rotate1, -1, 3) << endl;

    string count[9] = {"tony", "boris", "rishi", "rishi", "gordon", "gordon", "gordon", "rishi", "rishi"};
    string count1[5] = {"mom", "dad", "jonny", "ryan", "sarah"};
    // tests a normal string and should return 5
    cerr << "countRuns(count, 9) = " << countRuns(count, 9) << endl;
    // tests negative input and should return -1
    cerr << "countRuns(count, -1) = " << countRuns(count, -1) << endl;
    // tests when every element is different and should return 5
    cerr << "countRuns(count1, 5) = " << countRuns(count, -1) << endl;

    string leader[6] = {"boris", "rishi", "xD", "tony", "theresa", "david"};
    string leader1[7] = {"boris", "rishi", "xD", "tony", "theresa", "david", "sarah"};
    string leader2[2] = {"boris", "rishi"};
    // testing first 4 flips should return 4
    cerr << "flip(leader, 4) = " << flip(leader, 4) << endl;
    // tests an odd array and should return 7
    cerr << "flip(leader1, 7) = " << flip(leader1, 7) << endl;
    // checks just two strings to swap and should return 2
    cerr << "flip(leader2, 2) = " << flip(leader2, 2) << endl;

    string leader3[6] = {"boris", "rishi", "", "tony", "theresa", "david"};
    string politician[5] = {"boris", "rishi", "david", "", "tony"};
    // testing a valid array and should return 2
    cerr << "differ(leader2, 6, politician, 5) = " << differ(leader3, 6, politician, 5) << endl;
    // tests when both finish and no != and should return 1
    cerr << "differ(leader2, 2, politician, 1) = " << differ(leader3, 2, politician, 1) << endl;
    // tests when input is negative should return -1
    cerr << "differ(leader2, -1, politician, 1) = " << differ(leader3, -3, politician, 1) << endl;

    string names[10] = {"john", "margaret", "theresa", "rishi", "boris", "liz"};
    string names1[10] = {"margaret", "theresa", "rishi"};
    string names2[10] = {"john", "rishi"};
    string names3[0] = {};
    string names4[0] = {};
    // tests valid array and should return 1
    cerr << "subsequence(names, 6, names1, 3) = " << subsequence(names, 6, names1, 3) << endl;
    // tests when there is no subsequence and should return -1
    cerr << "subsequence(names, 5, names2, 2) = " << subsequence(names, 5, names2, 2) << endl;
    // test for an empy subsequence and should return 0
    cerr << "subsequence(names, 6, names3, 0) = " << subsequence(names, 6, names3, 0) << endl;
    // tests for both as empty arrays and should return 0
    cerr << "subsequence(names3, 0, names4, 0) = " << subsequence(names3, 0, names4, 0) << endl;
    // tests when subsequence is larger than array and hsould return -1
    cerr << "subsequence(names3, 0, names2, 6) = " << subsequence(names3, 0, names2, 6) << endl;

    string names5[10] = {"john", "margaret", "theresa", "rishi", "boris", "liz"};
    string set1[10] = {"david", "boris", "rishi", "margaret"};
    string set2[10] = {"tony", "gordon"};
    string set3[0] = {};
    // tests a normal array and should return 1
    cerr << "lookupAny(names5, 6, set1, 4) = " << lookupAny(names5, 6, set1, 4) << endl;
    // tests for non existant comparison and should return -1
    cerr << "lookupAny(names5, 6, set2, 2) = " << lookupAny(names5, 6, set2, 2) << endl;
    // tests with an empty array
    cerr << "lookupAny(names5, 6, set3, 0) = " << lookupAny(names5, 6, set3, 0) << endl; //empty set, should return -1
    cerr << "\n";

    string pm2[6] = {"david", "liz", "margaret", "tony", "gordon", "boris"};
    string pm3[4] = {"margaret", "theresa", "liz", "rishi"};
    // tests normal array and should return 3
    cerr << "split(pm2, 6, \"john\") = " << split(pm2, 6, "john") << endl;
    // tests an array that includes the splitter string and should return 2
    cerr << "split(pm3, 4, \"rishi\") = " << split(pm3, 4, "rishi") << endl;
    return 0;
    
}
