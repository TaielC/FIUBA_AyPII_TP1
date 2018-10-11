#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define NUM_PRIMO   7
#define DCS         256

void hashing_busqueda( char* cadena , int* valor , int largo ){
    for ( size_t i = 0; i < largo ; i++ ){
        *valor = ( DCS * (*valor) + cadena[i])%NUM_PRIMO;
    }
}

int pot(int a , int b ){
    for (int i = 0; i < b; i++ ){
        a*=a;
    }
    return a;
}

bool busqueda_string( char* buscado , char* texto ){

    int largo_buscado = strlen( buscado );
    int largo_texto = strlen( texto );

    int HALO = pot( DCS , largo_buscado )%NUM_PRIMO;

    int hash_buscado = 0;
    hashing_busqueda( buscado , &hash_buscado , largo_buscado );
    int hash_texto = 0;
    hashing_busqueda( texto , &hash_texto , largo_buscado );

    for( int i = 0 ; i < largo_texto - largo_buscado ; i++ ){
        if( hash_buscado == hash_texto )
            if( !strncmp( buscado , &texto[i] , largo_buscado )) 
                return true;

        if ( i < largo_buscado - largo_texto ) {
            hash_texto = (DCS * (hash_texto - texto[i] *HALO) + texto[i+ largo_texto])%NUM_PRIMO;

            if (hash_texto < 0)
                hash_texto = (hash_texto + NUM_PRIMO);
        }
    }
}




// /* Following program is a C implementation of Rabin Karp
// Algorithm given in the CLRS book */
// #include<stdio.h>
// #include<string.h>
 
// #define d 256
 
// void search(char pat[], char txt[], int q)
// {
//     int M = strlen(pat);
//     int N = strlen(txt);
//     int i, j;
//     int p = 0; // hash value for pattern
//     int t = 0; // hash value for txt
//     int h = 1;
 
//     // The value of h would be "pow(d, M-1)%q"
//     for (i = 0; i < M-1; i++)
//         h = (h*d)%q;
 
//     // Calculate the hash value of pattern and first
//     // window of text
//     for (i = 0; i < M; i++){
//         p = (d*p + pat[i])%q;
//         t = (d*t + txt[i])%q;
//     }
 
//     // Slide the pattern over text one by one
//     for (i = 0; i <= N - M; i++){
 
//         // Check the hash values of current window of text
//         // and pattern. If the hash values match then only
//         // check for characters on by one
//         if ( p == t ){
//              Check for characters one by one 
//             for (j = 0; j < M; j++)
//             {
//                 if (txt[i+j] != pat[j])
//                     break;
//             }
 
//             // if p == t and pat[0...M-1] = txt[i, i+1, ...i+M-1]
//             if (j == M)
//                 printf("Pattern found at index %d \n", i);
//         }
 
//         // Calculate hash value for next window of text: Remove
//         // leading digit, add trailing digit
//         if ( i < N-M ) {
//             t = (d*(t - txt[i]*h) + txt[i+M])%q;
 
//             // We might get negative value of t, converting it
//             // to positive
//             if (t < 0)
//                 t = (t + q);
//         }
//     }
// }
 

// int main(){   
//     char txt[80],pat[80];
//     int q;
//     printf("Enter some text \n");
//     scanf("%s",txt);
//     printf("Enter a pattern to be searched \n");
//     scanf("%s",(char*)&pat);
//     printf("Enter a prime number \n");
//     scanf("%d",&q);
//     search(pat, txt, q);
//     return 0;
// }