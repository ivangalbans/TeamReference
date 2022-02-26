char s[100];

scanf("%[aeiou]", s); // solo lee las vocales

scanf("%[^aeiou]", s); // solo lee las letras

scanf("%[^\n]", z); // funciona igual q gets()

// eliminar rayita de la fecha (5-29-2014) o (5/29/2014)
scanf("%d %*c %d %*c %d", &m, &d, &y);

printf("%09d\n", f); // imprime el entero f y rellena con 9 ceros

printf("%G\n", c); // imprime c sin ceros finales (convierte a E)

printf("%g\n", c); // imprime c sin ceros finales (convierte a e)

printf("%x\n", x); // imprime x en hexadecimal (Letras minusculas)

printf("%X\n", x); // imprime x en hexadecimal (Letras mayusculas)

printf("%o\n", o); // imprime o como octal unsigned

printf("%e\n", cient); // imprime el # en notacion cientifica (e minuscula)

printf("%E\n", cient); // imprime el # en notacion cientifica (E mayuscula)

// muestra un valor de apuntador en forma de puesta en marcha definida
printf("El valor de Ptr es %p\n", ptr);

// Almacena el # char almacenados en el printf.
printf("Total de char impresos en esta linea es:%n", &cant);
printf(" %d\n\n", cant);

printf("%%\n"); // muestra el caracter de porciento

printf("\\\n"); //muestra el caracter \

printf("\'\n"); // muestra el caracter '

printf("\"\n"); // muestra el caracter "

printf("\?\n"); // muestra el caracter '

printf("\\n\n"); // muestra el caracter \n

printf("%11d\n", 123); // justifica a la derecha en 11

// 7:ancho del campo 2:preicision, valor 98.74 justificado derecha
printf("%*.*f\n", 7, 2, 98.736);
// if precision < 0 ---> justificado izquierda

/*sprintf*/
char numstr[100];
int num = 1200;

sprintf(numstr, "%d", num); // a decimal
printf("%s\n", numstr);

sprintf(numstr, "%X", num); // a hexadecimal en mayuscula
printf("%s\n", numstr);
//-----------------------------------------------

int base = 8;
cout << setbase(base) << 8 << endl; // pone a cout a imprimir en base
                                    // (0,8,10,16)

/* istringstream
