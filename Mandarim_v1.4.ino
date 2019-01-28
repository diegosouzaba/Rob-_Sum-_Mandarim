//Projeto Mandarim v1.4
//Data: 19/05/15
//Por: Diego Souza e Matheus Pereira


//Sensores de Linha
#define LinhaFE 2
#define LinhaTD 3
#define LinhaTE 4
#define LinhaFD 5

//Sensores de Oponente (Infra)
#define OponD 10
#define OponT 11
#define OponE 7
#define OponF 8

//Motores
#define MotDir1 14
#define MotDir2 15
#define MotEsq1 16
#define MotEsq2 17

int rec = 1000; //Tempo de Ré
int rot = 1300; //Tempo de Rotação

void setup() {                    
  
  pinMode(MotDir1, OUTPUT);  //Motor direita  
  pinMode(MotDir2, OUTPUT);  //Motor direita  
  pinMode(MotEsq1, OUTPUT);   //Motor esquerda  
  pinMode(MotEsq2, OUTPUT);   //Motor esquerda  
  
  pinMode(LinhaFE, INPUT);    //Sensor de arena frontal esquerda (Usando sensor binário)
  pinMode(LinhaFD, INPUT);    //Sensor de arena frontal direita (Usando sensor binário)
  pinMode(LinhaTD, INPUT);    //Sensor de arena trazeiro esquerdo(Usando sensor binário)
  pinMode(LinhaTE, INPUT);    //Sensor de arena trazeiro direito (Usando sensor binário)
  
  pinMode(OponD,   INPUT);    //Sensor do oponente lado direito (Usando sensor binário)
  pinMode(OponT,   INPUT);    //Sensor do oponente traseira (Usando sensor binário)
  pinMode(OponE,   INPUT);    //Sensor do oponente lado esquerdo (Usando sensor binário)
  pinMode(OponF,   INPUT);    //Sensor do oponente frente (Usando sensor binário)
    
  parar();
  delay(5000);
  re();
  delay(80);
  frente();
  delay(80);

}    
  
void loop() {     
  
  //Prioridade dos Sensores Frontais
  if(digitalRead(LinhaFD)==LOW || digitalRead(LinhaFE)==LOW){  //Teste Sensor Frontal
    parar();
    re();
    delay(500);
    for(int a=0;a<=rec;a++){
      if(digitalRead(OponD)==LOW||digitalRead(OponE)==LOW||digitalRead(OponT)==LOW){
        a=rec;
      }
      delay(1);
    }
    
    parar();
    
    for(int a=0;a<=rot;a++){
      esquerdaberta();
      if(digitalRead(OponD)==LOW||digitalRead(OponE)==LOW||digitalRead(OponT)==LOW||digitalRead(OponF)==LOW){
        a=rot;
      }
      delay(1);  
    }
    
    parar();
    
    frente();
  }
  
/*==================================================================================================================*/

  else if(digitalRead(OponF)==LOW){  //Teste do Sensor de Oponente Frontal
    parar();
    frente();
    }
  
/*==============================================================================================================================================*/

  else if(digitalRead(OponD)==LOW){  //Teste do Sensor de Oponente Direito
    parar();
    
    for(int a=0;a<=rot;a++){
      esquerdaberta();
      if(digitalRead(OponF)==LOW||digitalRead(LinhaFE)==LOW||digitalRead(LinhaFD)==LOW||digitalRead(OponE)==LOW||digitalRead(OponT)==LOW){
        a=rot;
      }
      delay(1);
    }
  }
  
/*==============================================================================================================================================*/
     
  else if(digitalRead(OponE)==LOW){  //Teste do Sensor de Oponente Esquerdo
    parar();
    
    for(int a=0;a<=rot;a++){
      direitaberta();
      if(digitalRead(OponF)==LOW||digitalRead(LinhaFE)==LOW||digitalRead(LinhaFD)==LOW||digitalRead(OponE)==LOW||digitalRead(OponT)==LOW){
        a=rot;
      }
      delay(1);
    }
  }
  
/*==============================================================================================================================================*/

  else if(digitalRead(OponT)==LOW){  //Teste do Sensor de Oponente Traseiro
    parar();
    
    for(int a=0;a<=2*rot;a++){
      direitaberta();
      if(digitalRead(OponF)==LOW||digitalRead(LinhaFE)==LOW||digitalRead(LinhaFD)==LOW||digitalRead(OponE)==LOW||digitalRead(OponD)==LOW){
        a=2*rot;
      }
      delay(1);
    }
  }
  else giro();
  
  
}  //FIM DO LOOP ();
  
/*==============================================================================================================================================*/

 
 
//A função parar() desliga ambos motores  
void parar(){    
  digitalWrite(MotDir1, HIGH);    
  digitalWrite(MotDir2, HIGH);    
  digitalWrite(MotEsq1, HIGH);    
  digitalWrite(MotEsq2, HIGH);
  delay(0.5);  
}    
  
// A função frente() liga ambos motores para a frente   
void frente(){    
  digitalWrite(MotDir1, HIGH);    
  digitalWrite(MotDir2, LOW);    
  digitalWrite(MotEsq1, HIGH);    
  digitalWrite(MotEsq2, LOW);    
}    
  
  
// A função re() liga ambos motores para trás     
void re(){    
  digitalWrite(MotDir1, LOW);    
  digitalWrite(MotDir2, HIGH);    
  digitalWrite(MotEsq1, LOW);    
  digitalWrite(MotEsq2, HIGH);    
}    
  
//Liga o motor da direita para frente e da esquerda para trás    
void direita(){    
  digitalWrite(MotDir1, LOW);    
  digitalWrite(MotDir2, HIGH);    
  digitalWrite(MotEsq1, HIGH);    
  digitalWrite(MotEsq2, LOW);   
}    
  
//Liga o motor da esquerda para frente e da direita para trás    
void esquerda(){    
  digitalWrite(MotDir1, HIGH);    
  digitalWrite(MotDir2, LOW);    
  digitalWrite(MotEsq1, LOW);    
  digitalWrite(MotEsq2, HIGH);    
}

//Liga apenas o motor da esquerda pra frente
void esquerdaberta(){
  digitalWrite(MotDir1, HIGH);    
  digitalWrite(MotDir2, LOW);    
  digitalWrite(MotEsq1, HIGH);    
  digitalWrite(MotEsq2, HIGH);
}

//Liga apenas o motor da direita pra frente
void direitaberta(){
  digitalWrite(MotDir1, HIGH);    
  digitalWrite(MotDir2, HIGH);    
  digitalWrite(MotEsq1, HIGH);    
  digitalWrite(MotEsq2, LOW);
}
void giro(){
  frente();
  for(int a=0;a<=rot;a++){
    if(digitalRead(OponF) == LOW || digitalRead(OponD) == LOW || digitalRead(OponE) == LOW || digitalRead(OponT) == LOW){
      a=rot;
    }
    if(digitalRead(LinhaFD) == LOW || digitalRead(LinhaFE) == LOW){
      a=rot;
    }
    delay(1);
  }
  parar();
  direitaberta();
  for(int a=0;a<=rec/2;a++){
    if(digitalRead(OponF) == LOW || digitalRead(OponD) == LOW || digitalRead(OponE) == LOW || digitalRead(OponT) == LOW){
      a=rec/2;
    }
    if(digitalRead(LinhaFD) == LOW || digitalRead(LinhaFE) == LOW){
      a=rec/2;
    }
    delay(1);
  }
  parar();
  
}




