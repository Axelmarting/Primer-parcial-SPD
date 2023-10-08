//LED
#define A 13
#define B 12
#define C 11
#define D 10
#define E 9
#define F 8
#define G 7

//BOTONES
#define suma 4
#define resta 3
#define reset 2

//DISPLAY
#define unidad 5 
#define decena 6

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
  
  //Se configuran los pulsadores como entrada 
  pinMode(suma, INPUT_PULLUP);
  pinMode(resta, INPUT_PULLUP);
  pinMode(reset, INPUT_PULLUP);
  
  //se configuran como salida los display
  pinMode(unidad, OUTPUT);
  pinMode(decena, OUTPUT);
  
  Serial.begin(9600);
}

//contadores de cada display
int contadorU = 0;
int contadorD = 0;

//anti rebotes
int pulsador1Antes = 1;
int pulsador2Antes = 1;
int pulsador3Antes = 1;
  
  void loop()
{   
    //Se lee el estado del pulsador y se guarda en una variable
    int pulsador1Ahora = digitalRead(suma);
  	int pulsador2Ahora = digitalRead(resta);
  	int pulsador3Ahora = digitalRead(reset);
    
    
    //Apaga los led para que no se superpongan
    //Enciende el display decena(izquierda)
    //Muestra el numero del contador de decena
    //y apaga el display
    apagado();
    digitalWrite(decena,  HIGH);
    mostrarNumero(contadorD);
    digitalWrite(decena,  LOW);
    
    
    //Apaga los led para que no se superpongan
    //Enciende el display unidad(derecha)
    //Muestra el numero del contador de unidad
    //y apaga el display
    apagado();
    digitalWrite(unidad,  HIGH);
    mostrarNumero(contadorU);
    digitalWrite(unidad,  LOW);
    
    
    //Si se esta pulsando el boton de suma(primero)
    //y si el mismo boton antes vale 1 (anti rebote)
    //suma el contador de unidad
    if(pulsador1Ahora == 0 && pulsador1Antes == 1)
    {
      contadorU++;
    }
    
    
    //Si se esta pulsando el boton de resta(segundo)
    //y si el mismo boton antes vale 1 (anti rebote)
    //resta el contador de unidad
    if(pulsador2Ahora == 0 && pulsador2Antes == 1)
    {
      contadorU--;
    }
    
    
    //Si se esta pulsando el boton de reset(tercero)
    //y si el mismo boton antes vale 1 (anti rebote)
    //resetea ambos contadores a 0.
    if(pulsador3Ahora == 0 && pulsador3Antes == 1)
    {
      contadorU = 0;
      contadorD = 0;
    }
    
    
    //Si el contador de unidades llega a 10 se reinicia a 0
    //y el contador de decenas aumenta en 1.
    //Sino, si el contador de unidades llega a -1 se reinicia a 9
    //y el contador de decenas resta 1.
    if(contadorU == 10)
    {
      contadorU = 0;
      contadorD++; 
    }
    else if(contadorU == -1)
    {
      contadorD--;
      contadorU = 9;
    }
    
    
    //Si el contador de decenas llega a 10 se reinicia a 0
    //Sino, si el contador de decenas llega a -1 se reinicia a 9
    //y el contador de decenas resta 1.
    if(contadorD == 10)
    {
      contadorD = 0;
    }
    else if(contadorD == -1)
    {
      contadorD--;
      contadorD = 9;
    }
    
    
    //Se les asigna los nuevos valores de los pulsadores
    //a los anti rebotes.
    pulsador1Antes = pulsador1Ahora;
    pulsador2Antes = pulsador2Ahora;
    pulsador3Antes = pulsador3Ahora;
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