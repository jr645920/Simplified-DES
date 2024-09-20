#include <iostream>
#include <fstream>
#include <bitset>

using namespace std;

// swap 4 front and back bits
// void Swap(){}

// 2 4 3 1
int P4(int num){
    int pos1 = 8;
    int pos2 = 4;
    int pos3 = 2;
    int pos4 = 1;
    int num2 = 0;

    if((num & pos2)==pos2)
        num2 |= pos1;
    if((num & pos4)==pos4)
        num2 |= pos2;
    if((num & pos3)==pos3)
        num2 |= pos3;
    if((num & pos1)==pos1)
        num2 |= pos4;
    return num2;
}

// 6 3 7 4 8 5 10 9
int P8(int num){
    int pos3 = 128;
    int pos4 = 64;
    int pos5 = 32;
    int pos6 = 16;
    int pos7 = 8;
    int pos8 = 4;
    int pos9 = 2;
    int pos10 = 1;
    int num2 = 0;

    if((num & pos6)==pos6)
        num2 |= pos3;
    if((num & pos3)==pos3)
        num2 |= pos4;
    if((num & pos7)==pos7)
        num2 |= pos5;
    if((num & pos4)==pos4)
        num2 |= pos6;
    if((num & pos8)==pos8)
        num2 |= pos7;
    if((num & pos5)==pos5)
        num2 |= pos8;
    if((num & pos10)==pos10)
        num2 |= pos9;
    if((num & pos9)==pos9)
        num2 |= pos10;
    return num2;
}

// 3 5 2 7 4 10 1 9 8 6
int P10(int num){
    int pos1 = 512;
    int pos2 = 256;
    int pos3 = 128;
    int pos4 = 64;
    int pos5 = 32;
    int pos6 = 16;
    int pos7 = 8;
    int pos8 = 4;
    int pos9 = 2;
    int pos10 = 1;
    int num2 = 0;

    if((num & pos3)==pos3)
        num2 |= pos1;
    if((num & pos5)==pos5)
        num2 |= pos2;
    if((num & pos2)==pos2)
        num2 |= pos3;
    if((num & pos7)==pos7)
        num2 |= pos4;
    if((num & pos4)==pos4)
        num2 |= pos5;
    if((num & pos10)==pos10)
        num2 |= pos6;
    if((num & pos1)==pos1)
        num2 |= pos7;
    if((num & pos9)==pos9)
        num2 |= pos8;
    if((num & pos8)==pos8)
        num2 |= pos9;
    if((num & pos6)==pos6)
        num2 |= pos10;
    return num2;
}

// 2 6 3 1 4 8 5 7
int IP(int num){
    int pos1 = 128;
    int pos2 = 64;
    int pos3 = 32;
    int pos4 = 16;
    int pos5 = 8;
    int pos6 = 4;
    int pos7 = 2;
    int pos8 = 1;
    int num2 = 0;

    if((num & pos2)==pos2)
        num2 |= pos1;
    if((num & pos6)==pos6)
        num2 |= pos2;
    if((num & pos3)==pos3)
        num2 |= pos3;
    if((num & pos1)==pos1)
        num2 |= pos4;
    if((num & pos4)==pos4)
        num2 |= pos5;
    if((num & pos8)==pos8)
        num2 |= pos6;
    if((num & pos5)==pos5)
        num2 |= pos7;
    if((num & pos7)==pos7)
        num2 |= pos8;
    return num2;
}

// 4 1 3 5 7 2 8 6
int IIP(int num){
    int pos1 = 128;
    int pos2 = 64;
    int pos3 = 32;
    int pos4 = 16;
    int pos5 = 8;
    int pos6 = 4;
    int pos7 = 2;
    int pos8 = 1;
    int num2 = 0;

    if((num & pos4)==pos4)
        num2 |= pos1;
    if((num & pos1)==pos1)
        num2 |= pos2;
    if((num & pos3)==pos3)
        num2 |= pos3;
    if((num & pos5)==pos5)
        num2 |= pos4;
    if((num & pos7)==pos7)
        num2 |= pos5;
    if((num & pos2)==pos2)
        num2 |= pos6;
    if((num & pos8)==pos8)
        num2 |= pos7;
    if((num & pos6)==pos6)
        num2 |= pos8;
    return num2;
}

// 4 1 2 3 2 3 4 1
int EP(int num){
    int pos1 = 128;
    int pos2 = 64;
    int pos3 = 32;
    int pos4 = 16;
    int pos5 = 8;
    int pos6 = 4;
    int pos7 = 2;
    int pos8 = 1;
    int num2 = 0;

    if((num & pos4)==pos4)
        num2 |= pos1;
    if((num & pos1)==pos1)
        num2 |= pos2;
    if((num & pos2)==pos2)
        num2 |= pos3;
    if((num & pos3)==pos3)
        num2 |= pos4;
    if((num & pos2)==pos2)
        num2 |= pos5;
    if((num & pos3)==pos3)
        num2 |= pos6;
    if((num & pos4)==pos4)
        num2 |= pos7;
    if((num & pos1)==pos1)
        num2 |= pos8;
    return num2;
}

void Keygen(int key, int *keys){
    int left = 0x00000;
    int right = 0x00000;
    ///P10
    key = P10(key);
    keys[0] = key;
    ///split into two
    left = key >> 5 << 5;
    right = key << 27 >> 22;
    ///left shift(wraparound) 1
    left = left << 1 | (left >> 9 << 5);
    right = right << 1 | (right >> 9 << 5);
    ///recombine and P8
    right >>= 5;
    key = left | right;
    key = P8(key);
    keys[1] = key;
    ///left shift(wraparound) 2
    right <<= 5;
    left = left << 2 | (left >> 8 << 5);
    right = right << 2 | (right >> 8 << 5);
    ///recombine and P8
    right >>= 5;
    key = left | right;
    key = P8(key);
    keys[2] = key;
}

// void KeyMixing(){}

// using S0 and S1 tables
// void Substitution(){}

// expansion, key mixing, substitution, permutation 
// void Feistal(){}

void DES_decrypt(const char key[], char input){

    int keys[3] = {0,0,0};
    //cout << bitset<16>((int)input) << " ";
    cout << bitset<10>(0x36C) << endl;
    cout << bitset<10>(P10(0x36C)) << endl;
    Keygen(0x36C, keys);
    cout << keys[0] << endl;
    cout << keys[1] << endl;
    cout << keys[2] << endl;
    return;
}

int main(int argc, char *argv[]){
    ifstream fin;
    char input;

    //arg check
    // if(argc != 2){
    //     printf("Incorrect arguments\n");
    //     exit(2);
    // }

    DES_decrypt(argv[1], input);
    return 0;

    /// secret key in examples is 0x36C
    /// log files printed to stderr
    //DES_decrypt(argv[1], "tbd");
    char* key = argv[1];

    fin.open("decrypt_in 1.txt");
    if(fin.fail()){
       printf("failed to open file\n");
       exit(1);
    }
    while(!fin.eof()){
        fin >> input;
        DES_decrypt(argv[1], input);
        //cout << int(s) << endl;
    }

    int b = 0xF; //0b00001111;
    b <<= 1; //0b00011110;
    //cout << b << endl;

    exit(0);
}