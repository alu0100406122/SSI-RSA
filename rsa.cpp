// Seguridad en Sistemas Informáticos. 
// María Nayra Rodríguez Pérez.

#include <vector>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <istream>
#include <cmath>

using namespace std;

// Exponenciación Rápida.
double exponenciacion(int base, int exponente, int mod){
    double x = 1;
    double y = fmod(base, mod);
    while ((exponente > 0) && (y > 1)){
        if (fmod(exponente,2) != 0){
            x = fmod((x*y), mod);
            exponente = (exponente - 1);
        }
        else{
            y = fmod((y*y), mod);
            exponente = (exponente / 2);
        }
    }
    return x;
}

// Introducir valores
void pedir_valores(int &p, int &q, int &d){
    cout << "Introduzca el valor de un número primo P: ";
    cin >> p;
    cout << "Introduzca el valor de Q: ";
    cin >> q;
    cout << "Introduzca el valor de D: ";
    cin >> d;
}

// Lehman Peralta
// Comprobar que p no es divisible por ningún primo pequeño (2,3,5,7,11). 
bool divisible(int p){
     
    if (((p % 2) != 0) && ((p % 3) != 0) && ((p % 5) != 0) && ((p % 7) != 0) && ((p % 11) != 0)){
        return false;
    }
    else{
        return true;
    }
    
}

// Lehman Peralta
// Comprobar que los números aleatorios no se repiten
bool existe_aleatorio(vector<int> v_, int num_, int i_){
    bool igual = false;
    for (int j=0; j<i_; j++){
        if(v_[j] == num_){
            igual = true;
            break;
        }
        else{
            igual = false;
        }
    }
    return igual;
}


// Lehman Peralta
// Elegir números aleatorios entre 1 y p-1
void aleatorio(vector<int> &v, int tam_, int p){
    int num;
    int existe = 0;

    for (int i=0; i<tam_; i++){
        srand(clock());
        num = 1 + rand() % (p-1);  //variable = limite_inferior + rand() % (limite_superior +1 - limite_inferior) ;
        
        //Comprobación que los números aleatorios no se repitan.
        while (existe_aleatorio(v, num, i) == true){
            num = 1 + rand() % (p-1);  //variable = limite_inferior + rand() % (limite_superior +1 - limite_inferior) ;
        }
        v[i]=num;

    }
    cout << "Vector aleatorio obtenido: ";
    for (int i=0; i<tam_; i++){
        cout << v[i] << " ";
    }
    cout << endl;
}

/* Función Lehman y Peralta.
     1) Comprobar que p no es divisible por ningún primo pequeño (2,3,5,7,11).
     2) Elegir 100 enteros aleatorios (a1,a2,...,a100) entre (1 y p-1). 
     3) Para cada i calcular ai^((p-1)/2) (mod p) */
void lehman_peralta(int p){
    int tam;
    vector<int> v1;
    bool divi = false;
    divi = divisible(p);
    int exponente = ((p - 1)/2);
    double resultado;
    bool primo = true;
    
    if (p<100){
        tam = (p * 0.2);
    }
    else{
        tam = 100;
    }
    v1.resize(tam);
    
    //cout << "\t" << "LEHMAN PERALTA" << endl;
    // Comprobamos que el número introducido sea un número primo pequeño.
    if ( (p!=2) && (p!=3) && (p!=5) && (p!=7) && (p!=11) ){
        // 1) Comprobamos que dicho número sea divisible por un primo pequeño.
        if (divi == true){
            cout << endl;
            cout << "El número P es divisible por algún número primo pequeño (2,3,5,7,11)." << endl;
            primo = false;
            cout << endl;
        }
        else {
            aleatorio(v1,tam, p);    // 2)
            
            // 3) Para cada posicion i del vector aleatorio -->   ai^(p-1)/2 (mod p): 
            
            for (int i=0; i<v1.size(); i++){
                resultado = exponenciacion(v1[i], exponente, p);
                //cout << "Resultado: " << resultado << endl;
                
                //Comprobamos que el resultado sea 1 o (p-1) para que sea primo.
                if ( (resultado == 1) || (resultado == (p - 1)) ){
                    primo = true;
                }
                else{
                    primo = false;
                }
            } 
            
        }
    }
    cout << endl;
    if (primo == true){
        cout << p << " es primo. " << endl;
    }
    else{
        cout << p << " NO es primo. " << endl;
    }
    cout << endl;
}

/* Euclides Extendido
     Para el cálculo de mcd(a,b) y b-1 (mod a) (con a>b) :
     1) Inicializar: dividendo x0 := a, divisor x1 := b, z-1=0, z0=1 
     2) Mientras el resto no dé 0: dividir xi-1 por xi y asignar a xi+1 el resto asignar a zi := -div(xi-1,xi)• zi-1+ zi-2
     3) El mcd(a,b) es xi
     4) Si mcd(a,b)=1, entonces el inverso es zi-1 
*/

int euclides(int a, int b, int n){  // b --> phi, a--> d

    // Inicializar variables
    int resto = 1;
    int inverso = 0;
    int mcd= 0;
    vector<int> z;
    z.resize(z.size()+1);
    vector<int> x;
    x.resize(2);
    cout << "b" << b << endl;
    x[0] = a;   // Dividendo
    x[1] = b;   // Divisor
    z[-1] = 0;
    z[0] = 1;
    
    // Mientras que el resto no dé 0
    int i = 1;
    while(resto != 0){
        // Buscamos orden correcto dividendo y divisor.
        int aux;
        if (x[i-1] < x[i]){
            aux = x[i-1];
            x[i-1] = x[i];
            x[i] = aux;
        }
        x.resize(x.size()+1);
        resto = x[i-1] % x[i];
        cout << "Modulo entre: "<< x[i-1] << " y "<< x[i] << " es igual a " << resto << endl;
        x[i+1] = resto;
        cout << "Resto: " << resto << endl;
        z.resize(z.size()+1);
        z[i] = -(x[i-1] / x[i]) * z[i-1] + z[i-2];

        i++;
    }
    
    // Si obtenemos un 1, entonces en z está el inverso.
    for (int i=0; i<x.size(); i++){
        if ( (x[i] == 0) && (x[i-1] == 1) ){
            mcd = x[i-1];
            inverso = z[i-2];
        }    
        else{
            mcd = x[i-1];
            inverso = 0;
        }
    }
    
    cout << endl;
    cout << "m.c.d (a,b): " << mcd << endl;
    
    
    // Mostramos el vector x.
    cout << "Vector X: ";
    for (int i=0; i<x.size(); i++){
        cout << x[i] << " ";
    }
    cout << endl;
    
    // Mostramos el vector z.
    cout << "Vector Z: ";
    for (int i=0; i<z.size(); i++){
        cout << z[i] << " ";
    }
    cout << endl;
    
    // Comprobación si el inverso obtenido es negativo.
    if (inverso > 0){
        cout << "Inverso: " << inverso << endl;
    }
    else {
        if (inverso < 0){
            cout << "n: " << n << endl;
            cout << "Inverso: " << inverso << " + Phi(n) " << b << endl;
            inverso = (inverso + b);
            cout << "Inverso (e): " << inverso << endl;
        } 
    }
    cout << endl;
    
    return inverso;
}

// Función para separar espacios y comas al texto de entrada.
vector<char> separar(string texto_){
    int i=0;
    int j=0;
    vector<char> vec_aux;
    while (texto_[i] != '\0'){
        if(texto_[i] != ' '){
            vec_aux.resize(vec_aux.size()+1);
            vec_aux[j] = texto_[i];
            j++;
        }
        i++;
    }    
    return vec_aux;
}

// Determinar el valor de j, para separar los bloques.
int generar_j(int n_){
    vector<int> v;
    int mod = 23456789;
    v.resize(v.size()+1);
    for (int i=0; i<v.size(); i++){
        v.resize(v.size()+1);
        v[i] = (exponenciacion(26, i, mod));
        if (v[i] > n_){
            return i;
        }
    }
}

// Posición de la letra en el alfabeto.
int pos_letra(char letra){
    char abecedario[26];
    strcpy(abecedario, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    int numero;
    for (int i=0; i<26; i++){
        if(abecedario[i] == letra){
            numero = i;
            break;
        }
    }
    return numero;
    
}

// Función para pasar de letras a decimales. tam_bloque --> j
int texto_decimal(vector<char> texto, int tam_bloque){
    int valor = 0;
    double expon = 0;
    int base = 26;
    int mod = 23456789;
    for (int i=0; i<tam_bloque; i++){
        expon = exponenciacion(base, ((tam_bloque-1) - i), mod);
        valor += pos_letra(texto[i]) * expon;
    }
    
    return valor;
}

//Función que va dividiendo el texto en bloques de tamaño j. Devuelve vector con los enteros.
vector<int> dividir_bloques(vector<char> texto, int tam_bloque){
    vector<int> enteros;
    int i=0; 
    int k=0;
    int x=0;
    //cout << "texto.size(): " << texto.size() << endl;
    while (i < texto.size()){
        
        vector<char> aux;
        aux.resize(tam_bloque);
        while(k<tam_bloque){
            aux[k] = texto[i];
            k++;
            i++;
        }
        cout << "Vector auxiliar (bloque): ";
        for (int i=0; i<aux.size(); i++){
            cout << aux[i];
        }
        cout << endl;
        k=0;
        enteros.resize(enteros.size()+1);
        enteros[x] = texto_decimal(aux, tam_bloque);
        
        x++;
    }
    return enteros;
}

// Cifrado
vector<int> cifrado(vector<int> enteros_, int e_, int n_){
    vector<int> cifrado;
    cifrado.resize(enteros_.size());
    for (int i=0; i<enteros_.size(); i++){
        cifrado[i] = exponenciacion(enteros_[i], e_, n_);
    }
    
    return cifrado;
}

// Descifrado
vector<int> descifrado(vector<int> cifrado_, int d_, int n_){
    vector<int> descifrado;
    descifrado.resize(cifrado_.size());
    for (int i=0; i<cifrado_.size(); i++){
        descifrado[i] = exponenciacion(cifrado_[i], d_, n_);
    }
    
    return descifrado;
}

int main(){
    int p;
    int q;
    int d;
    int n; // p*q
    int phi;
    
    vector<char> texto_f;
    
    cout << "-------------------------------------------------------------------" << endl;
    cout << "\t \t \t \t" << "RSA" << endl;
    cout << "-------------------------------------------------------------------" << endl;
    cout << endl;
    cout << "-------------------------------------------------------------------" << endl;
    cout << "1: Introducir información necesaria (p, q, d y texto a cifrar)." << endl;
    cout << "-------------------------------------------------------------------" << endl;
    cout << endl;
    
    // Paso 1 --> Pedimos los valores p, q, d y texto a cifrar.
    pedir_valores(p,q,d);
    
    // Calculo de n y phi
    n = (p * q);
    phi = (p - 1)*(q - 1);
    
    //Pedimos el texto original
    
    string texto = "AMIGO MIO";
    cout << "Texto introducido: " << texto << endl;
    texto_f = separar(texto);
    
    for (int i=0; i<texto_f.size(); i++){
        cout << texto_f[i];    
    }
    
    /*texto = new char[256];
    cout << "Introduzca el texto original: " << endl;
    cin.ignore();
    cin.getline(texto,256);
    texto_f = separar(texto);
    cout << "Texto introducido: " << texto << endl;*/
    
    cout << endl;
    cout << "-------------------------------------------------------------------" << endl;
    cout << "2: Comprobación que p y q son números primos. LEHMAN PERALTA" << endl;
    cout << "-------------------------------------------------------------------" << endl;
    cout << endl;
    lehman_peralta(p);
    lehman_peralta(q);

    cout << endl;
    cout << "-------------------------------------------------------------------" << endl;
    cout << "3: Aplicación del algoritmo de EUCLIDES. Parámetro e." << endl;
    cout << "-------------------------------------------------------------------" << endl;
    int e = euclides(d, phi, n);
    
    
    cout << "-------------------------------------------------------------------" << endl;
    cout << "4: Convertir texto original en enteros." << endl;
    cout << "-------------------------------------------------------------------" << endl;
    
    int j = generar_j(n);
    cout << "Generar j: " << j << endl;

    vector<int> enteros;
    enteros = dividir_bloques(texto_f, (j-1));
    cout << endl;
    
    cout << "Enteros: ";
    for (int i=0; i<enteros.size(); i++){
            cout << enteros[i] << " ";
    }
    cout << endl;
    
    cout << "-------------------------------------------------------------------" << endl;
    cout << "5: Cifrado." << endl;
    cout << "-------------------------------------------------------------------" << endl;
    
    vector<int> cif;
    
    //cout << "n: " << n << endl;
    //cout << "e: " << e << endl;
    cif = cifrado(enteros,e,n);
    cout << "C: " ;
    for (int i=0; i<cif.size(); i++){
            cout << cif[i] << " ";
    }
    cout << endl;
    
    cout << "-------------------------------------------------------------------" << endl;
    cout << "6:: Descifrado." << endl;
    cout << "-------------------------------------------------------------------" << endl;
    
    vector<int> descif;
    //cout << "DESCIFRADO" << endl;
    descif = descifrado(cif,d,n);
    cout << "M: " ;
    for (int i=0; i<descif.size(); i++){
            cout << descif[i] << " ";
    }
    cout << endl;
    cout << "-------------------------------------------------------------------" << endl;
    return 0;
}