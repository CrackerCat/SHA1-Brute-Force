/* 
 * File:   main.cpp
 * Author: Anthony (oneofthosed3afmutes@yahoo.com)
 * Description: This is a brute force attempt at SHA1
 *
 * The MIT License
 *
 * Copyright (c) <year> <copyright holders>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 * 
 * Created on December 10, 2010, 7:31 PM
 */
#include <iostream>
#include <string>
#include <ctime>
#include <crypto++/sha.h>
#include <crypto++/hex.h>
using namespace std;
using namespace CryptoPP;
void incrementString(string &, int);
/*
 * 
 */
int main(int argc, char** argv) {
    string value = " ";
    string hashValue = "";
    string originalHash = "";
    int stringPosition = 0;
    SHA1 hash;
    SecByteBlock sbbDigest(SHA1::DIGESTSIZE);

    cout << "Please input a SHA1 hash you would like to search for: " << endl;
    cin >> originalHash;

    if(originalHash.length() != 40) {
        cout << "The SHA1 hash you have provided is not valid, exiting." << endl;
        return 1;
    }

    cout << "For safety I am converting your hash to all upper case characters" << endl;
    for(int i = 0; i < originalHash.length(); i++) {
        originalHash[i] = toupper(originalHash[i]);
    }
    cout << "Converted Hash: " << originalHash << endl;
    time_t t = time(NULL);
    cout << "Time started: " << ctime(&t) << endl;

    while(true) {
        hash.CalculateDigest(sbbDigest.begin(), (byte const *)value.c_str(), value.size());
        HexEncoder(new StringSink(hashValue)).Put(sbbDigest.begin(), sbbDigest.size());
        if(hashValue == originalHash) {
            time_t t = time(NULL);
            cout << "Ending time: " << ctime(&t) << endl;
            cout << "We have located a value for orignal hash: " << originalHash << endl;
            cout << "The value is: " << value << endl;
            return 0;
        } else {
            hashValue = "";
            incrementString(value, stringPosition);
        }
    }

    return 0;
}

void incrementString(string &s, int stringPosition) {
    if(s.size() <= stringPosition) {
        s.append(" ");
    } else {
        s[stringPosition] = s[stringPosition] + 1;
        if(s[stringPosition] > 126) {
            s[stringPosition] = ' ';
            incrementString(s, stringPosition+1);
        }
    }
}