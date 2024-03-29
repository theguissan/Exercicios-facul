
#include "Address.h"
#include "Address.cpp"
#include <vector>
string octects[4];
string maskOctects[4];


// rotina para pegar o tamanho de uma string
int len(string str) {  
    int length = 0;  
    for (int i = 0; str[i] != '\0'; i++)  
    {  
        length++;  
          
    }  
    return length;     
}  

// rotina para fazer separar um input em um objeto vector  
void split (string str, char seperator, string *arr) {  
    int currIndex = 0, i = 0;  
    int startIndex = 0, endIndex = 0;  
    while (i <= len(str))  {  
        if (str[i] == seperator || i == len(str)) {  
            endIndex = i;  
            string subStr = "";  
            subStr.append(str, startIndex, endIndex - startIndex);  
            arr[currIndex] = subStr;  
            currIndex += 1;  
            startIndex = endIndex + 1;  
        }  
        i++;  
    }     
}

//menu de opcoes
int printScreen( ) {

    int option;

    cout << "THE MAGIC IP CALCULATOR OF MATHEUS GUILHERME SOUZA SANTANA" << "\n";
    cout << "Class: Redes De Computadores II                           " << "\n";
    cout << "\n";
    cout << "Options:                                                  " << "\n";
    cout << "1 - Calculate Class IP                                    " << "\n";
    cout << "2 - Calculate Classless IP with Decimal Notation          " << "\n";
    cout << "3 - Calculate Classless IP with CIDR                      " << "\n";
    cout << "4 - Exit                                                  " << "\n";
    cout << "Enter your option: ";
    cin >> option;

    return option;
}

//rotina para imprimir vectors na forma (n.n.n.n.)
void printIp(vector<int> ip) {
    for( auto i = ip.begin(); i != ip.end(); ++ i) {
        cout << *i <<".";
    }
    cout << "\n";
}

//rotina que calcula um ip com classe
void calculateClassIP() {

    Address address;

    string input;
    
    cout<< "Type something bruh (n.n.n.n)... ";
    
    cin >> input;

    bool isValid = address.checkCode(input);

    if(isValid) {
        cout << "is Valid\n";
        
        address.setAddressCode(input);

        split(address.getAddressCode(), '.', octects);

        address.setOctects(octects);

        string uai = address.checkClass();

        cout << "Class: " << uai << "\n";
 
        if(uai  != "D" && uai != "E") {

        string mask = address.checkMask();

        int cidr = address.getCIDR();

        cout << "CIDR: /" << cidr << endl;

        cout << "Mask: " << mask << "\n";

        split(mask,'.',maskOctects );

        address.setMask(maskOctects);

        int numberOfHosts  = address.getNumberOfHosts(cidr);

        cout << "Number of Hosts: " << numberOfHosts << "\n";

        vector<int> firstAddress = address.getFirstAddress();

        cout << "First Address: ";

        printIp(firstAddress);

        vector<int> broadcast = address.getBroadcast();

        cout << "Broadcast: ";

        printIp(broadcast);

        cout << "First IP: ";

        vector<int> firstIp = address.getFirstIp(firstAddress);

        printIp(firstIp);

        cout << "Last IP: ";

        vector<int> lastIp = address.getLastIp(broadcast);

        printIp(lastIp);
        }

    } else {
        cout << "is Invalid\n";
    }
}

//rotina que calcula um ip sem classe com mascara decimal
void calculateClasslessIP() {

    string ipCode;
    
    Address address;

    cout << "Enter your ip bruh (n.n.n.n)... ";
    cin >> ipCode;

    bool isValid = address.checkCode(ipCode);

    if(isValid) {

        address.setAddressCode(ipCode);

        string inputMask;

        cout << "Enter your mask bruh (n.n.n.n)... ";
        cin >> inputMask;

        bool isValidMask = address.isValidDecimalMask(inputMask);

         if(isValidMask) {

            split(address.getAddressCode(), '.', octects);

            address.setOctects(octects);

            split(inputMask,'.',maskOctects );

            address.setMask(maskOctects);

            cout << "your ip Address " << address.getAddressCode() << "\n";

            cout << "your decimal mask " << inputMask << "\n";

            int classlessCidr =  address.getClasslessCIDR(inputMask);

            cout << "Your cidr is /" << classlessCidr << "\n";

            cout << "Your number of hosts: " << address.getNumberOfHosts(classlessCidr) << "\n";

            vector<int> firstAddress = address.getFirstAddress();

            cout << "Your first Address is ";

            printIp(firstAddress);

            cout << "Your broadcast is ";

            vector<int> broadcast = address.getBroadcast();

            printIp(broadcast);

            cout << "your first ip ";

            printIp(address.getFirstIp(firstAddress));

            cout << "your last ip ";

            printIp(address.getLastIp(broadcast));

         } else {
            cout << "your mask is invalid bruh :(" << "\n";
         }

    }else {
        cout << "Oopsie, sorry its invalid :(" << "\n";
    }
}

//rotina que calcula um ip com cidr
void calculateClasslessIpWithCidr() {

    string ipCode;
    
    Address address;

    cout << "Enter your ip bruh (n.n.n.n)... ";
    cin >> ipCode;

    bool isValid = address.checkCode(ipCode);

    if(isValid) {

        Address address;

        address.setAddressCode(ipCode);

        int cidrInput;

        cout << "Enter your cidr bruh... /";
        cin >> cidrInput;

        bool isCidrValid = address.isValidCIDR(cidrInput); 

        if(isCidrValid) {

            split(address.getAddressCode(), '.', octects);

            address.setOctects(octects);

            string mask = address.getMaskByCidr(cidrInput);

            split(mask,'.',maskOctects );

            address.setMask(maskOctects);

            cout << "your ip Address " << address.getAddressCode() << "\n";

            cout << "your decimal mask " << mask << "\n";

            cout << "Your cidr is /" << cidrInput << "\n";

            cout << "Your number of hosts: " << address.getNumberOfHosts(cidrInput) << "\n";

            vector<int> firstAddress = address.getFirstAddress();

            cout << "Your first Address is ";

            printIp(firstAddress);

            cout << "Your broadcast is ";

            vector<int> broadcast = address.getBroadcast();

            printIp(broadcast);

            cout << "your first ip ";

            printIp(address.getFirstIp(firstAddress));

            cout << "your last ip ";

            printIp(address.getLastIp(broadcast));

        }else {
            cout << "Sorry bruh its invalid" << "\n";
        }

    } else {
        cout << "Oopsie, sorry its invalid :(" << "\n";
    }

}
  
//rotina do main que pega a opcao da funcionalidade e faz o tipo de calculo desejado.
int main() {

    int option = printScreen();

    switch (option) {

        case 1:
        calculateClassIP();
        break;
        case 2:
        calculateClasslessIP();
        break;
        case 3:
        calculateClasslessIpWithCidr();
        break;
        default:
        cout << "BUUUUHH" << "\n";
    }

    return 0;
}