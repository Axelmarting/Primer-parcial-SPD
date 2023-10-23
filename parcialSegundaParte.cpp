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
#define interruptorD 4

//SENSOR, MOTOR Y LED
#define SENSOR A0
#define rojo 2
#define motor 3



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

  //Se configuran como salida los display
  pinMode(unidad, OUTPUT);
  pinMode(decena, OUTPUT);
  
  //Declaro como salida el led y el motor
  pinMode(rojo,OUTPUT);
  pinMode(motor,OUTPUT);
  Serial.begin(9600);
}

//Contadores de cada display 0 a 99
int contadorU = 0;
int contadorD = 0;

//Contadores de cada display primos
int num1 = 0;
int num2 = 0;

void loop()
{   
    int lecturaCuenta = analogRead(SENSOR);
  	//Funcion map() para configurar el sensor de temperatura
  	int temperatura = map(lecturaCuenta,20,358,-40,125);
  
    monitoriza(temperatura);
  
    if(temperatura > 0)
    {
      digitalWrite(rojo,HIGH);
      digitalWrite(motor,HIGH);
    }
    else
    {
      digitalWrite(rojo,LOW);
      digitalWrite(motor,LOW);
    }
  
    //Aca guardamos el valor del interruptor
    int interruptor = digitalRead(interruptorD);
    
    if(interruptor == 1)
    {
      //Reinicio los contadores primos.
      num1=0;
      num2=0;
      
      encenderDisplay(contadorU,contadorD, 50);

      //contador de unidades
      contadorU++;
      //Si el contador de unidades llega a 10 se reinicia a 0
      //y el contador de decenas aumenta en 1.
      //Sino, si el contador de unidades llega a -1 se reinicia a 9
      //y el contador de decenas resta 1.
      if(contadorU == 10)
      {
        contadorU = 0;
        contadorD++;
      }

      //Si el contador de decenas llega a 10 se reinicia a 0
      //Sino, si el contador de decenas llega a -1 se reinicia a 9
      //y el contador de decenas resta 1.
      if(contadorD == 10)
      {
        contadorD = 0;
      }
    }
    
    //Aca es cuando el interruptor vale 0
    else
    {     
      contadorU = 0;
      contadorD = 0;
      
      // Concatenar los números en una cadena
      String concatenacion = String(num2) + String(num1);

      int resultado = concatenacion.toInt();
      // Imprimir el número

      if (primo(resultado)) 
      {
        Serial.println(resultado);
        
		encenderDisplay(num1,num2, 50);
      }

      num1++;
      if (num1 == 10) {
        num1 = 0;
        num2++;
      }

    }
}

//Funciones


void encenderDisplay(int n1,int n2, int tiempo)
{
  encenderNumeroPrimo(n1,  unidad, tiempo);
  encenderNumeroPrimo(n2,  decena, tiempo);
  
  encenderNumeroPrimo(n1, unidad, tiempo);
  encenderNumeroPrimo(n2, decena, tiempo);
  
  encenderNumeroPrimo(n1, unidad, tiempo);
  encenderNumeroPrimo(n2, decena, tiempo);
  
  encenderNumeroPrimo(n1, unidad, tiempo);
  encenderNumeroPrimo(n2, decena, tiempo);
}


// monitoriza la temeperatura
void monitoriza(int temperaturaActual)
{
  Serial.print("La temperatura es ...");
  Serial.println(temperaturaActual);
  
}

void encenderNumeroPrimo(int numero, int display, int tiempo)
{
  apagado();
  digitalWrite(display, HIGH);
  mostrarNumero(numero);
  delay(tiempo);
  digitalWrite(display, LOW);
}

     
bool primo(int n) 
{
  bool mensaje = true;
  if (n <= 1) 
  {
    mensaje = false;
  }
  else 
  {
    for (int i = 2; i * i <= n; i++) 
    {
      if (n % i == 0) 
      {
        mensaje = false;
        break;
      }
    }
  }
  return mensaje;
}

//Esta funcion muestra el numero dicho
void mostrarNumero(int numero)
{
  switch (numero)
  {
    case 0:
      cero();
      break;
    case 1:
      uno(); 
      break;
    case 2:
      dos(); 
      break;
    case 3:
      tres(); 
      break;
    case 4:
      cuatro(); 
      break;
    case 5:
      cinco(); 
      break;
    case 6:
      seis(); 
      break;
    case 7:
      siete(); 
      break;
    case 8:
      ocho(); 
      break;
    case 9:
      nueve(); 
      break;
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

//A partir de aca son las funciones para cada numero.
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