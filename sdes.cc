#include <iostream>
#include <fstream>
#include <bitset>
#include <string.h>

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

//Generates key1 and key2 from the key given in argument 1
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

// Key Mixing step
int KeyMixing(int num, int key){
    return num ^ key;
}

// using S0 and S1 tables to perform substitution
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
    right = num & 0x0000000F; // changed from << 28 >> 28
        //cout << "left: " << bitset<8>(left) << " right: " << bitset<8>(right) << endl;
    row = (left & 0b1001) >> 2 | left & 0b0001;
    col = (left & 0b0110) >> 1;
        //cout << "row: " << bitset<8>(row) << " col: " << bitset<8>(col) << endl;
    num2 |= s0[row][col];
    num2 <<= 2;
    row = (right & 0b1001) >> 2 | right & 0b0001;
    col = (right & 0b0110) >> 1;
        //cout << "row: " << bitset<8>(row) << " col: " << bitset<8>(col) << endl;
    num2 |= s1[row][col];
        //cout << "sub: " << bitset<16>(num2) << endl;
    return num2;
}

// expansion, key mixing, substitution, permutation 
int Feistal(int num, int key){
    int num2 = 0;
    ///expansion
        //cout << "pre ep num: " << bitset<8>(num) << endl;
    num2 = EP(num << 4);
    ///keymixing
        //cout << "Key mixing: " << bitset<8>(num2) << " key: " << bitset<8>(key) << endl;
    num2 = KeyMixing(num2, key);
    ///substitution
    num2 = Substitution(num2);
    ///permutation 4
    num2 = P4(num2);
    return num2;
}

//Simiplified DES decryption function
int DES_decrypt(int keys[], int input){
    int left = 0;
    int right = 0;
    int f1 = 0;
    int f2 = 0;
    int result = 0;
    ///Initial permutation
    input = IP(input);
    cerr << "ip: " << input << endl;
    ///split
    left = input >> 4;
    right = input & 0x0000000F;//<< 28 >> 28; /// need to fix this : maybe and with FFFF or something
        //cout << "L: " << bitset<8>(left) << " R: " << bitset<8>(right) << endl;
    ///feistal 1
    f1 = Feistal(right, keys[2]);
    ///xor with right 4 bits
    f1 = f1 ^ left;
    ///think we swap different here but ok
    ///swap
    f1 = SW(f1, right);
    cerr << "fk1: " << f1 << endl;
    left = f1 >> 4;
    right = f1 & 0x0000000F;
    ///feistal 2
    f2 = Feistal(right, keys[1]);
    ///xor with the right 4 bits
    f2 = f2 ^ left;
    ///combine and inverse permutation
    f2 = (f2 << 4) | right;
    cerr << "fk2: " << f2 << endl;
    result = IIP(f2);

    return result;
}

//main program to run the simplified DES decryption
int main(int argc, char *argv[]){
    ifstream fin;
    char input;
    int encrypted;
    int decrypted;
    string filename;
    int keys[3] = {0,0,0};
    int key;
    int count = 0;

    //arg check
    if(argc != 2){
        printf("Incorrect arguments\n");
        exit(2);
    }

    // cout << "Filename: ";
    // getline(cin, filename);
    // cout << "\n" << filename << "\n";

    // fin.open(filename);
    // if(fin.fail()){
    //    printf("failed to open file\n");
    //    exit(1);
    // }
    // while(fin >> input){
    //     encrypted = input & 0x000000FF;
    //         //cout << "encrypted: " << encrypted << endl;
    //     decrypted = DES_decrypt(argv[1], encrypted);
    //         //cout << "decrypted: " << decrypted << endl;
    //         //cout << "bin: " << bitset<8>(decrypted) << endl;
    //         //cout << int(encrypted) << endl;
    //     cout << char(decrypted);
    //     //count++;
    // }
    // fin.close();

    key = stoi(argv[1], 0, 16) & 0b1111111111;
    Keygen(key, keys);
    cerr << "p10: " << keys[0] << endl;
    cerr << "k1: " << keys[1] << endl;
    cerr << "k2: " << keys[2] << endl;
    while(cin.get(input)){
        encrypted = input & 0x000000FF;
        cerr << "decrypting byte #" << count << " with value " << encrypted << endl;
        decrypted = DES_decrypt(keys, encrypted);
        cout << char(decrypted);
        count++;
    }

    exit(0);
}