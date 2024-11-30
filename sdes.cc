/**
 * @file sdes.cc
 * @author Johnathan Reilly
 * @date 9/21/2024
 * @brief This is an implementation of the sipmlified DES decryption, which uses a 10 bit key and 8 bit input. 
 *        This project was done for credit in CS4770 at Ohio University during the Fall '24 semester.
 *        The program takes one argument, a 10 bit key for the decryption. A log file is output to stderr using
 *        the exact format shown in the examples. Works best when input is redirected from a file. 
 */

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
    left = (key >> 5) & 0x1F;
    right = key & 0x1F;
    ///left shift(wraparound) 1
    left = ((left << 1) | (left >> 4)) & 0x1F;
    right = ((right << 1) | (right >> 4)) & 0x1F;
    ///recombine and P8
    key = (left << 5) | right;
    keys[1] = P8(key);
    ///left shift(wraparound) 2
    left = ((left << 2) | (left >> 3)) & 0x1F;
    right = ((right << 2) | (right >> 3)) & 0x1F;
    ///recombine and P8
    key = (left << 5) | right;
    keys[2] = P8(key);
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
    right = num & 0x0000000F;
    row = (left & 0b1001) >> 2 | left & 0b0001;
    col = (left & 0b0110) >> 1;
    num2 |= s0[row][col];
    num2 <<= 2;
    row = (right & 0b1001) >> 2 | right & 0b0001;
    col = (right & 0b0110) >> 1;
    num2 |= s1[row][col];
    return num2;
}

// expansion, key mixing, substitution, permutation 
int Feistal(int num, int key){
    int num2 = 0;
    ///expansion
    num2 = EP(num << 4);
    ///keymixing
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
    right = input & 0x0000000F;
    ///feistal 1
    f1 = Feistal(right, keys[2]);
    ///xor with right 4 bits
    f1 = f1 ^ left;
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
    char input;
    int encrypted;
    int decrypted;
    int keys[3] = {0,0,0};
    int key;
    int count = 0;

    //arg check
    if(argc != 2){
        printf("Incorrect arguments\n");
        exit(2);
    }

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