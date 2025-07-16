#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#include "types.h"

void printZnak(Token tok, char znak){
    printf("%s[%c]\n", tokenStrings[tok], znak);
}

int main(){
    char znak = '~';
    char curr;
    int i = 0; // index v currWord
    char currWord[1001];
    while(znak != EOF){
        znak = getc(stdin);

        switch(znak){
            // operatorji
            case '=' : 
            case '+' : 
            case '-' : 
            case '*' : 
                curr = znak;
                znak = getc(stdin);
                if(znak == '='){
                    printf("%s[%c=]\n", tokenStrings[tok_operator], curr);
                }else{
                    ungetc(znak, stdin);
                    printZnak(tok_operator, curr);
                }
            break;
            
            // vrstični komentar in blocni komentar
            case '/' : 
                curr = znak;
                znak = getc(stdin);
                if(znak == '='){
                    printf("%s[/=]\n", tokenStrings[tok_operator]);
                }else if(znak == '/'){
                    znak = getc(stdin);
                    while(znak != '\n' && znak != EOF){
                        znak = getc(stdin);
                    } 
                }else if(znak == '*'){
                    int dolzinaKomentarja = 2;
                    char prev = '~';
                    while(1){
                        if(prev == '*' && znak == '/' && dolzinaKomentarja >= 4){
                           break; 
                        }
                        dolzinaKomentarja++;
                        prev = znak;
                        znak = getc(stdin);
                    } 
                }else{
                    ungetc(znak, stdin);
                    printZnak(tok_operator, curr);
                }
            break;
            
            case '>' : 
            case '<' : 
                curr = znak;
                znak = getc(stdin);
                if(znak == '='){
                    printf("%s[%c=]\n", tokenStrings[tok_operator], curr);
                }else{
                    ungetc(znak, stdin);
                    printZnak(tok_operator, curr);
                }
            break;

            // locila
            case ',' : 
            case ';' : 
            case '(' : 
            case ')' : 
            case '{' : 
            case '}' : 
            case '[' : 
            case ']' : 
                printZnak(tok_separator, znak);
            break;
            
            // niz
            case '"' : 
                i = 0;
                znak = getc(stdin);
                currWord[i] = znak;
                while(znak != '"' && znak != EOF){
                    i++;
                    znak = getc(stdin);
                    currWord[i] = znak;
                }
                currWord[i] = '\0';
                printf("%s[%s]\n",tokenStrings[tok_str], currWord);
            break;

            // rezerviranke
            default:
                if(isdigit(znak)){
                    i = 0;
                    while(isdigit(znak)){
                        currWord[i++] = znak;
                        znak = getc(stdin);
                    }
                    currWord[i] = '\0';
                    ungetc(znak, stdin);
                    printf("%s[%s]\n", tokenStrings[tok_num], currWord);
                }else if(isalpha(znak) || znak == '_'){
                    i = 0;
                    currWord[i] = znak;
                    znak = getc(stdin);
                    while(isalpha(znak) || isdigit(znak) || znak == '_'){
                        i++;
                        currWord[i] = znak;
                        znak = getc(stdin);
                    }
                    i++;
                    currWord[i] = '\0';
                    ungetc(znak, stdin);
                    // printf("%s\n", currWord);
                    bool printed = false;
                    if(i < 7){
                        for(int idx = 0; idx < 7; idx++){
                            if(strcmp(currWord, reservedKeywords[idx]) == 0){
                                printf("%s[%s]\n", tokenStrings[tok_reserved], currWord);
                                printed = true;
                                break;
                            }
                        }
                    }
                    if(!printed){
                        printf("%s[%s]\n", tokenStrings[tok_name], currWord);
                    }
                }
            break;
        }
    }
    return 0;
}