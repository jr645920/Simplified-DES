#include <iostream>
#include <fstream>
#include <bitset>

using namespace std;

// swap 4 front and back bits
int SW(int left, int right){
    int num = (right << 4) | left;
    return num;
}

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
    int left = 0;
    int right = 0;
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

int KeyMixing(int num, int key){
    return num ^ key;
}

// using S0 and S1 tables
int Substitution(int num){
    int num2 = 0;
    int left, right, row, col;
    int s0[4][4] = {{1, 0, 3, 2},
                    {3, 2, 1, 0},
                    {0, 2, 1, 3},
                    {3, 1, 3, 2}};
    int s1[4][4] = {{0, 1, 2, 3},
                    {2, 0, 1, 3},
                    {3, 0, 1, 0},
                    {2, 1, 0, 3}};
    left = num >> 4;
    right = num << 28 >> 28;
    row = left & 9;
    col = left & 6;
    num2 |= s0[row][col];
    num2 <<= 2;
    row = right & 9;
    col = right & 6;
    num2 |= s1[row][col];
    return num2;
}

// expansion, key mixing, substitution, permutation 
int Feistal(int num, int key){
    int num2 = 0;
    ///expansion
    num = EP(num);
    ///keymixing
    num = KeyMixing(num, key);
    ///substitution
    num2 = Substitution(num);
    ///permutation 4
    num2 = P4(num2);
    return num2;
}

int DES_decrypt(const char key[], char input){
    int left = 0;
    int right = 0;
    int f1 = 0;
    int f2 = 0;
    int result = 0;
    int keys[3] = {0,0,0};
    //cout << bitset<16>((int)input) << " ";
    // cout << bitset<10>(0x36C) << endl;
    // cout << bitset<10>(P10(0x36C)) << endl;
    Keygen(0x36C, keys);
    // cout << "p10: " << keys[0] << endl;
    // cout << "k1: " << keys[1] << endl;
    // cout << "k2: " << keys[2] << endl;

    ///Initial permutation
    input = IP(input);
    ///split
        //cout << "Input: " << bitset<8>(input) << endl;
    left = input >> 4;
    right = input << 28 >> 28;
        //cout << "L: " << bitset<8>(left) << " R: " << bitset<8>(right) << endl;
    ///feistal 1
    f1 = Feistal(left, keys[2]);
    cout << f1 << endl;
    ///xor with right 4 bits
    f1 = f1 ^ left;
    cout << f1 << endl;
    ///think we swap different here but ok
    ///swap
    input = SW(f1, right);
    left = input >> 4;
    right = input << 28 >> 28;
    ///feistal 2
    f2 = Feistal(left, keys[1]);
    ///xor with the right 4 bits
    f2 = f2 ^ left;
    ///combine and inverse permutation
    input = (f2 << 4) | right;
    result = IIP(input);

    return result;
}

int main(int argc, char *argv[]){
    ifstream fin;
    char input;
    int decrypted;

    //arg check
    // if(argc != 2){
    //     printf("Incorrect arguments\n");
    //     exit(2);
    // }

    //DES_decrypt(argv[1], input);
    //return 0;

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
        decrypted = DES_decrypt(argv[1], input);
        cout << "char: " << decrypted << endl;
        cout << "bin: " << bitset<8>(decrypted) << endl;
        //cout << int(s) << endl;
        exit(0);
    }

    int b = 0xF; //0b00001111;
    b <<= 1; //0b00011110;
    //cout << b << endl;

    exit(0);
}