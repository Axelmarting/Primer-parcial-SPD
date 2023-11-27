
/*
Explicacion del codigo=
El programa inicia con 4 variables globales: 3 contadores(
contadorDecena, contadorUnidad, contadorLetras) y letras.

El contador letras funciona del 0 al 6, siendo cada numero
una letra distinta iniciando desde la a hasta la f. Aca es 
donde se le setea el valor a la variable letras.

Luego, si el contador de unidades es menor que 10, me va a 
mostrar en los displays los numeros del 0 al 9 y me va a aumentar
en 1 el contador mientras que se siga cumpliendo la condicion.

Cuando el contador llega a 10, ya me deja de contar y entra en
la otra condicion. En la cual me va a mostrar la decena y las 
letras. Aca es donde empieza a funcionar el contadorLetras y a
aumentar en 1 mientras que se cumpla la condicion, si este contador
llega a 6 se reincia a 0.

Cuando llega a  6, quiere decir que el valor de letras es "f", 
por lo tanto, la siguiente condicion fuera de este else dice que
si letras llega a valer "f" que el contador de unidades, que antes
valia 10, valga 0 y que el contador de decenas aumente en 1.

Luego, al hacer que el contador de unidades vuelva a valer
1 despues de que letras valga f, hace que se reinicie todo y vuelva
a entrar a la condicion inicial de mostrar solo numeros en los
displays y aumentar en 1 el contador de unidades mientras que este
se mantenga siendo menor que 10.

Finalmente, cuando el contadorDecena llega a 10 y letras vale
"f" el contadorDecena se reinicia a 0 iniciando nuevamente el 
conteo de 0 a 9f(ultimo numero an

*/

//LED
#define A 13
#define B 12
#define C 11
#define D 10
#define E 9
#define F 8
#define G 7

//DISPLAY
#define unidad 5 
#define decena 6

//INTERRUPTOR
#define INTERRUPTOR 4

//MOTOR
#define MOTOR 3

//SENSOR
#define SENSOR A0

//FOTORESISTENCIA
#define FOTORESISTENCIA A1

//LED ROJO
#define ROJO 2

void setup()
{
  //Se configuran como salida los pines
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);

  
  //se configuran como salida los display
  pinMode(unidad, OUTPUT);
  pinMode(decena, OUTPUT);
  
  //declaro como salida el led y el motor
  pinMode(ROJO,OUTPUT);
  pinMode(MOTOR,OUTPUT);
  
  //configuro como entrada la fotoresistencia
  pinMode(FOTORESISTENCIA, INPUT);
  
  Serial.begin(9600);
}


//contadores para numeros normales.
int num1 = 0; //unidad
int num2 = 0; //decena


//contadores para c/display hexadecimal
int contadorDecena = 0;
int contadorUnidad = 0;
//contador del que dependen las letras
String letras = "";
int contadorLetras = 0;


void loop()
{
  int lecturaCuenta = analogRead(SENSOR);//valor sensor temp
  int valorFotoresistencia = analogRead(FOTORESISTENCIA);//valor foto
  int interruptor = digitalRead(INTERRUPTOR); //valor interruptor
  
  int temperatura = map(lecturaCuenta,20,358,-40,125); //temp real
  
  Serial.print("Temperatura: ");
  Serial.println(temperatura);
  
  Serial.print("fotoresistencia: ");
  Serial.println(valorFotoresistencia);
  
  //Funcion que enciende el Led y motor.
  encenderLed(temperatura, valorFotoresistencia);
  
  if(interruptor == 0){ //contador normal, valor interruptor 0
    contadorDecena=0;//reinicio los contadores hexadecimales.
    contadorUnidad=0;
    
    encenderDisplayNumeros(num1, num2, 70); //muestro numeros
    
    num1++;
    if(num1 == 10){ //aumento de decena
      num1=0;
      num2++;
    }
    
    if(num2 == 10){ //reinicio total
      num2 = 0;
    }
    
  }
  
  else{ //contador hexadecimal, valor interruptor 1
    num1 = 0; //reinicio los valores del contador normal.
    num2 = 0;
    
    if (contadorLetras == 0){
      letras = "a"; //seteando letras segun su contador
    }else if (contadorLetras == 1){
      letras = "b";
    }else if (contadorLetras == 2){
      letras = "c";
    }else if (contadorLetras == 3){
      letras = "d";
    }else if (contadorLetras == 4){
      letras = "e";
    }else if (contadorLetras == 5){
      letras = "f";
    }

    if (contadorUnidad < 10){ //muestro solo numeros
      encenderDisplayNumeros(contadorUnidad, contadorDecena, 70);
      contadorUnidad ++;
    }
    else{ //muestro numeros y letras
      encenderDisplayLetras(contadorDecena, letras, 70);

      contadorLetras++;
      if (contadorLetras == 6){
        contadorLetras = 0;
      }
    }

    if (letras == "f"){ //aumento de decena
      contadorUnidad = 0;
      contadorDecena ++;
    }

    if (letras == "f" && contadorDecena == 10){ //reinicio total
      contadorDecena = 0;
    }

    
  }
}

//Esta funcion enciende el led y el motorCC dependiendo los valores
// de la fotoresistencia y la temperatura.

void encenderLed(int valor1, int valor2){
    if (valor1 > 30 && valor2 > 200){
      digitalWrite(ROJO,HIGH);
      digitalWrite(MOTOR,HIGH);
    }
    else  {
      digitalWrite(ROJO,LOW);
      digitalWrite(MOTOR,LOW);
    }
}

void encenderDisplayLetras(int n2,String letras, int tiempo)
{
  encenderNumero(n2, decena, tiempo);
  encenderletra( letras, unidad, tiempo);
  
  encenderNumero(n2, decena, tiempo);
  encenderletra( letras, unidad, tiempo);
  
  encenderNumero(n2, decena, tiempo);
  encenderletra( letras, unidad, tiempo);
  
  encenderNumero(n2, decena, tiempo);
  encenderletra( letras, unidad, tiempo);
}



void encenderDisplayNumeros(int n1,int n2, int tiempo)
{
  encenderNumero(n1,  unidad, tiempo);
  encenderNumero(n2,  decena, tiempo);
  
  encenderNumero(n1, unidad, tiempo);
  encenderNumero(n2, decena, tiempo);
  
  encenderNumero(n1, unidad, tiempo);
  encenderNumero(n2, decena, tiempo);
  
  encenderNumero(n1, unidad, tiempo);
  encenderNumero(n2, decena, tiempo);
}



void encenderletra(String  letra, int display, int tiempo)
{
  apagado();//Apaga los led para que no se superpongan
  digitalWrite(display, HIGH);//Enciende el display 
  mostrarletra(letra);//muestra el numero
  delay(tiempo);//delay 
  digitalWrite(display, LOW);//y apaga el display
}



void encenderNumero(int numero, int display, int tiempo)
{
  apagado();
  digitalWrite(display, HIGH);
  mostrarNumero(numero);
  delay(tiempo);
  digitalWrite(display, LOW);
}



void mostrarletra(String variable)
{
  if (variable == "a") {
    letraA();
  } else if (variable == "b") {
    letraB();
  } else if (variable == "c") {
    letraC();
  } else if (variable == "d") {
    letraD();
  } else if (variable == "e") {
    letraE();
  } else if (variable == "f") {
    letraF();
  }
}



// Esta función muestra el número o letra dicha.
void mostrarNumero(int variable)
{
  if (variable == 0) {
    cero();
  } else if (variable == 1) {
    uno();
  } else if (variable == 2) {
    dos();
  } else if (variable == 3) {
    tres();
  } else if (variable == 4) {
    cuatro();
  } else if (variable == 5) {
    cinco();
  } else if (variable == 6) {
    seis();
  } else if (variable == 7) {
    siete();
  } else if (variable == 8) {
    ocho();
  } else if (variable == 9) {
    nueve();
  }
}



//Esta funcion apaga completamente los leds del display
//se usa para evitar que se superpongan cuando se encienden.
void apagado()
{ 
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(F, HIGH);
  digitalWrite(G, HIGH);
}

//A partir de aca son las funciones para cada numero y letra.
//Son los leds que se tienen que encender y apagar 
//para cada uno. 
void cero()
{
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  digitalWrite(G, HIGH);
  
}
void uno()
{
  digitalWrite(A, HIGH);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(F, HIGH);
  digitalWrite(G, HIGH);
  
}
void dos()
{
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, HIGH);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, HIGH);
  digitalWrite(G, LOW);
}
void tres()
{
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
  digitalWrite(E, HIGH);
  digitalWrite(F, HIGH);
  digitalWrite(G, LOW);
}

void cuatro()
{
  digitalWrite(A, HIGH);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(F, LOW);
  digitalWrite(G, LOW);
}

void cinco()
{
  digitalWrite(A, LOW);
  digitalWrite(B, HIGH);
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
  digitalWrite(E, HIGH);
  digitalWrite(F, LOW);
  digitalWrite(G, LOW);
}

void seis()
{
  digitalWrite(A, LOW);
  digitalWrite(B, HIGH);
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  digitalWrite(G, LOW);
}

void siete()
{
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(F, HIGH);
  digitalWrite(G, HIGH);
}

void ocho()
{
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  digitalWrite(G, LOW);
}

void nueve()
{
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
  digitalWrite(E, HIGH);
  digitalWrite(F, LOW);
  digitalWrite(G, LOW);
}

void letraA()
{
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  //digitalWrite(d, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  digitalWrite(G, LOW);
}

void letraB()
{
  //digitalWrite(a, LOW);
  //digitalWrite(b, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  digitalWrite(G, LOW);
}

void letraC()
{
  digitalWrite(A, LOW);
  //digitalWrite(b, LOW);
  //digitalWrite(c, LOW);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  //digitalWrite(g, LOW);
}

void letraD()
{
  //digitalWrite(a, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  //digitalWrite(f, LOW);
  digitalWrite(G, LOW);
}

void letraE()
{
  digitalWrite(A, LOW);
  //digitalWrite(B, HIGH);
  //digitalWrite(C, HIGH);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  digitalWrite(G, LOW);
}

void letraF()
{
  digitalWrite(A, LOW);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  digitalWrite(G, LOW);
}

