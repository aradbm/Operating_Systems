#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED

#include "codec.h"

#endif

int encode(char * src, char * dst, int len){
    int i=0;
    while( i<len){
        if (isalpha(src[i])){
            if (isalpha(src[i]+3)){
                int newChar=src[i]+3;
                char ch=newChar;
                src[i]=ch;
            }
            else{
                int newChar=src[i]-123+3+65;
                char ch=newChar;
                src[i]=ch;
            }  
        }
        i+=1;
    }
    return 0;
}

int decode(char * src, char * dst, int len){
    int i=0;
    while( i<len){
       if (isalpha(src[i])){
            if (isalpha(src[i]-3)){
                int newChar=src[i]-3;
                char ch=newChar;
                src[i]=ch;
            }
            else{
                int newChar=src[i]-65-3+122;
                char ch=newChar;
                src[i]=ch;
            }  
        }
        i+=1;
    }
    return 0;
}


int main(){
    printf("wrong name for the shared file\n");
    return 0;
}
