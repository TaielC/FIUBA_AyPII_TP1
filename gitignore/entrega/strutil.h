#ifndef STRULTIL_H
#define STRULTIL_H

char** split( const char* cadena , char separador );

char* join( char** arr_cadenas , char separador ); 

void free_strv( char** arr_cadenas );

#endif //STRULTIL_H