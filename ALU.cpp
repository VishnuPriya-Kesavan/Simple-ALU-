#include <bits/stdc++.h>
using namespace std;
 
// function to perform adding in the accumulator
void add(int ac[], int x[], int qrn)
{
    int i, c = 0;
     
    for (i = 0; i < qrn; i++) {
         
        // updating accumulator with A = A + BR
        ac[i] = ac[i] + x[i] + c;
         
        if (ac[i] > 1) {
            ac[i] = ac[i] % 2;
            c = 1;
        }
        else
            c = 0;
    }
}
 
// function to find the number's complement
void complement(int a[], int n)
{
    int i;
    int x[8] = {0};
    x[0] = 1;
     
    for (i = 0; i < n; i++) {
        a[i] = (a[i] + 1) % 2;
    }
    add(a, x, n);
}
 
// function to perform right shift
void rightShift(int ac[], int qr[], int& qn, int qrn)
{
    int temp, i;
    temp = ac[0];
    qn = qr[0];
     
    cout << "\t\trightShift\t";
     
    for (i = 0; i < qrn - 1; i++) {
        ac[i] = ac[i + 1];
        qr[i] = qr[i + 1];
    }
    qr[qrn - 1] = temp;
}
 
// function to display operations
void display(int ac[], int qr[], int qrn)
{
    int i;
     
    // accumulator content
    for (i = qrn - 1; i >= 0; i--)
        cout << ac[i];
    cout << "\t";
     
    // multiplier content
    for (i = qrn - 1; i >= 0; i--)
        cout << qr[i];
}
 
// Function to implement booth's algo
void boothAlgorithm(int br[], int qr[], int mt[], int qrn, int sc)
{
 
    int qn = 0, ac[10] = { 0 };
    int temp = 0;
    cout << "qn\tq[n+1]\t\tBR\t\tAC\tQR\t\tsc\n";
    cout << "\t\t\tinitial\t\t";
     
    display(ac, qr, qrn);
    cout << "\t\t" << sc << "\n";
     
    while (sc != 0) {
        cout << qr[0] << "\t" << qn;
         
        // SECOND CONDITION
        if ((qn + qr[0]) == 1)
        {
            if (temp == 0) {
                 
                // subtract BR from accumulator
                add(ac, mt, qrn);
                cout << "\t\tA = A - BR\t";
                 
                for (int i = qrn - 1; i >= 0; i--)
                    cout << ac[i];
                temp = 1;
            }
             
            // THIRD CONDITION
            else if (temp == 1)
            {
                // add BR to accumulator
                add(ac, br, qrn);
                cout << "\t\tA = A + BR\t";
                 
                for (int i = qrn - 1; i >= 0; i--)
                    cout << ac[i];
                temp = 0;
            }
            cout << "\n\t";
            rightShift(ac, qr, qn, qrn);
        }
         
        // FIRST CONDITION
        else if (qn - qr[0] == 0)
            rightShift(ac, qr, qn, qrn);
        
        display(ac, qr, qrn);
        
        cout << "\t";
         
        // decrement counter
        sc--;
        cout << "\t" << sc << "\n";
    }
}

// C++ program to divide two
// unsigned integers using
// Non-Restoring Division Algorithm
 
/*#include <iostream>
#include <string>
using namespace std;*/
 
// Function to add two binary numbers
string add1(string A, string M)
{
    int carry = 0;
    string Sum = ""; // Iterating through the number
    // A. Here, it is assumed that
    // the length of both the numbers
    // is same
    for (int i = A.length() - 1; i >= 0; i--) {
        // Adding the values at both
        // the indices along with the
        // carry
        int temp = (A[i] - '0') + (M[i] - '0') + carry;
 
        // If the binary number exceeds 1
        if (temp > 1) {
            Sum += to_string(temp % 2);
            carry = 1;
        }
        else {
            Sum += to_string(temp);
            carry = 0;
        }
    }
 
    // Returning the sum from
    // MSB to LSB
    return string(Sum.rbegin(), Sum.rend());
}
 
// Function to find the compliment
// of the given binary number
string compliment1(string m)
{
    string M = ""; // Iterating through the number
    for (int i = 0; i < m.length(); i++) {
        // Computing the compliment
        M += to_string((m[i] - '0' + 1) % 2);
    }
 
    // Adding 1 to the computed
    // value
    M = add1(M, "0001");
    return M;
}
 
// Function to find the quotient
// and remainder using the
// Non-Restoring Division Algorithm
void nonRestoringDivision(string Q, string M, string A)
{
    // Computing the length of the number
    int count = M.length();
    string comp_M = compliment1(M);
 
    //Var to determine whether add or sub has to be computed for the next step
    string flag = "successful";
 
    // Printing the initial values of the accumulator, dividend and divisor
    cout << "Initial Values: A: " << A << " Q: " << Q
         << " M: " << M << endl;
 
    // The number of steps is equal to the length of the binary number
    while (count) {
        // Printing the values at every step
        cout << "\nstep: " << M.length() - count + 1;
 
        // Step1: Left Shift, assigning LSB of Q to MSB of A.
        cout << " Left Shift and ";
 
        A = A.substr(1) + Q[0];
        
 //Choosing the add or subt based on the result of the previous step
        if (flag == "successful") {
            A = add1(A, comp_M);
            cout << "subtract: ";
        }
        else {
            A = add1(A, M);
            cout << "Addition: ";
        }
 
        cout << "A: " << A << " Q: " << Q.substr(1) << "_";
 
        if (A[0] == '1') {
            // Step is unsuccessful and the quotient bit will be '0'
            Q = Q.substr(1) + "0";
            cout << " -Unsuccessful";
 
            flag = "unsuccessful";
            cout << " A: " << A << " Q: " << Q
                 << " -Addition in next Step" << endl;
        }
        else {
            // Step is successful and the quotient bit will be '1'
            Q = Q.substr(1) + "1";
            cout << " Successful";
            flag = "successful";
            cout << " A: " << A << " Q: " << Q
                 << " -Subtraction in next step" << endl;
        }
        count--;
    }
    cout << "\nQuotient(Q): " << Q << " Remainder(A): " << A
         << endl;
}


// Function to add two binary numbers
string add(string A, string M) {
 
    int carry = 0;
    string Sum;
 
    // Iterating through the number A. Here, it is assumed that
    // the length of both the numbers is same
    for (int i = A.length() - 1; i >= 0; i--) {
        //Adding the values at both the indices along with the carry
        int temp = A[i] - '0' + M[i] - '0' + carry;
        // If the binary number exceeds 1
        if (temp > 1) {
            Sum.push_back('0' + (temp % 2));
            carry = 1;
        }
        else {
            Sum.push_back('0' + temp);
            carry = 0;
        }
    }
    // Return the sum from Most Significant to Low Significant
    reverse(Sum.begin(), Sum.end());
    return Sum;
}
 
// Function of find the complement of the binary number
string complement(string m) {
    string M;
 
    // Iterating through the number
    for (int i = 0; i < m.length(); i++) {
        // Computing the Complement
        M.push_back('0' + ((m[i] - '0' + 1) % 2));
    }
    // Adding 1 to the computed value
    M = add(M, "0001");
    return M;
}
 
// Function to find the quotient and remainder Using Restoring Division
void restoringDivision(string Q, string M, string A) {
    int count = M.length();
    //Printing the initial values of the accumulator, dividend and divisor
    cout << "Initial Values: A:" << A << " Q:" << Q << " M:" << M << endl;
    // The number of steps is equal to the length of the binary number
    while (count > 0) {
        // Printing the values at every step
        cout << "\nstep:" << (M.length() - count + 1) << endl;
        A = A.substr(1) + Q[0];
    // Taking complement and adding it to A Indirectly we are subtracting(A-M)
        string comp_M = complement(M);
        A = add(A, comp_M);
        // Left shift,assigning LSB of Q to MSB of A.
        cout << "Left Shift and Subtract: ";
        cout << " A:" << A << endl;
        cout << "A:" << A << " Q:" << Q.substr(1) << "_";
        if (A[0] == '1') {
            // Unsuccessful and Quotient bit will be zero
            Q = Q.substr(1) + '0';
            cout << "  -Unsuccessful" << endl;
            // Restoration is required for A
            A = add(A, M);
            cout << "A:" << A << " Q:" << Q << " -Restoration" << endl;
        }
        else {
            // Quotient bit will be 1
            Q = Q.substr(1) + '1';
            cout << " Successful" << endl;
            // No restoration
            cout << "A:" << A << " Q:" << Q << " -No Restoration" << endl;
        }
        count--;
    }
    // Final quotient and remainder of the given dividend and divisor
    cout << "\nQuotient(Q):" << Q << " Remainder(A):" << A << endl;
}
// Function to add two binary numbers
string addNum(string A, string B) {
    int carry = 0;
    string sum;

    // Iterate through the numbers
    int n = A.length();
    for (int i = n - 1; i >= 0; i--) {
        int bitA = A[i] - '0';
        int bitB = B[i] - '0';

        int bitSum = (bitA + bitB + carry) % 2;
        carry = (bitA + bitB + carry) / 2;

        sum = to_string(bitSum) + sum;
    }

    if (carry)
        sum = '1' + sum;

    return sum;
}

// Function to subtract two binary numbers
string subtract(string A, string B) {
    int carry = 0;
    string diff;

    // Iterate through the numbers
    int n = A.length();
    for (int i = n - 1; i >= 0; i--) {
        int bitA = A[i] - '0';
        int bitB = B[i] - '0';

        int bitDiff = (bitA - bitB - carry + 2) % 2;
        carry = (bitA - bitB - carry < 0) ? 1 : 0;

        diff = to_string(bitDiff) + diff;
    }

    return diff;
}

 
// driver code
int main()
{
    int choice;
    do {
        cout << "\n1. Addition of 'n' bit numbers\n";
        cout << "2. Subtraction of 'n' bit numbers\n";
        cout<<"3.Booth's Algorithm\n";
        cout<<"4.Non-Restoring Division\n";
        cout<<"5.Restoring Division\n";
        cout<< " 6. Exit\n";
        cout<<"\nEnter choice \n";
        cin >> choice;

        switch (choice) {
         case 1: {
                // Addition of 'n' bit numbers
                int n;
                cout << "Enter the number of bits (n): ";
                cin >> n;

                string num1, num2;
                cout << "Enter the first number (n bits): ";
                cin >> num1;
                cout << "Enter the second number (n bits): ";
                cin >> num2;

                string sum = addNum(num1, num2);
                cout << "Sum: " << sum << endl;
                break;
            }
            case 2: {
                // Subtraction of 'n' bit numbers
                int n;
                cout << "Enter the number of bits (n): ";
                cin >> n;

                string num1, num2;
                cout << "Enter the first number (n bits): ";
                cin >> num1;
                cout << "Enter the second number (n bits): ";
                cin >> num2;

                string diff = subtract(num1, num2);
                cout << "Difference: " << diff << endl;
                break;
            }
             
            case 3:{
                cout<<"Booths\n";
               int mt[10], sc;
               int brn, qrn;
     
    // Number of multiplicand bit
    cout<<"Enter the  Number of multiplicand bit: \n";
    cin>>brn;
     
    // multiplicand
    int br[brn];
    int qr[qrn];

  cout << "Enter the multpilcand: ";

  //  store input from user to array
  for (int i = 0; i < brn; ++i) {
    cin >> br[i];
  }
     
    // copy multiplier to temp array mt[]
    for (int i = brn - 1; i >= 0; i--)
        mt[i] = br[i];
         
    reverse(br, br + brn);
 
    complement(mt, brn);
 
    // No. of multiplier bit
    cout<<"Enter the multipier bit: ";
    cin>>qrn;
     
    // sequence counter
    sc = qrn;
    
    cout << "Enter the multiplier: ";

  //  store input from user to array
  for (int i = 0; i < qrn; ++i) {
    cin >> qr[i];
  }
     
    // multiplier
   
    reverse(qr, qr + qrn);
 
    boothAlgorithm(br, qr, mt, qrn, sc);
 
    cout << endl
         << "Result = ";
          
    for (int i = qrn - 1; i >= 0; i--){
        cout << qr[i];}
    break;
            }
        case 4:{
            
            cout<<"Non-Restoring Division\n";
                string dividend;
                string divisor;
                cout<<"Enter dividend: ";
                cin>>dividend;
                cout<<"Enter divisor : ";
                cin>>divisor;
                string accumulator = string(dividend.size(), '0');
                nonRestoringDivision(dividend, divisor, accumulator);

                break;
        }
         case 5:{
                cout<<"Restoring Division";
                string dividend;
                string divisor;
                cout<<"Enter dividend: ";
                cin>>dividend;
                cout<<"Enter divisor : ";
                cin>>divisor;
                string accumulator= string(dividend.length(), '0');
 
 
                restoringDivision(dividend, divisor, accumulator);

                break;}
          case 6:{
          cout<< "\n Exiting...."<< endl;
          }
         default:
                cout << "\nInvalid choice!\n";}
        
    }while (choice != 6);}