


/////////////////////////////////////////////////////////////////////////////////////////////

//Shreyash_Dabhade - Team The Robo-Tech Forum GCOEA
//4WD_Holonomic_Drivetrain with actuations 
// DD ROBOCON 2024
// Interchange Wala Chutiyapa
// PS4

//////////////////////////////////////////////////////////////////////////////////////////////


#include <ESP32_Servo.h>
#include <PS4Controller.h>
#include<Arduino.h>


///////////////////////////Motor Connections////////////////////////////////////////////////

int M1 = 18, M2 = 5, M3 = 15, M4 = 2;
int pa=0,pb=0,pc=0,pd=0;
int x = 0, y = 0;
float a = 0, b = 0, c = 0, d = 0, absA = 0, absB = 0, absC = 0, absD = 0;

///////////////////////////Variables///////////////////////////////////////////////////////

int Max_value = 0;
int pwm = 0;
int max_pwm = 0;
float magnitude = 0;
int rotational = 0, rotational_pwm = 0, max_rotational_pwm =0 ;
float theta = 0;
int up = 0;
int down = 0;
///////////////////////////sabertooth motor signal pins/////////////////////////////////////

Servo PA;
Servo PB;
Servo PC;
Servo PD;

///////////////////////////////////////Pneumatics///////////////////////////////////////////

int IN_1 = 13;
int IN_2 = 12;
int IN_3 = 14;
int IN_4 = 27;

////////////////////////////////////// E bike ////////////////////////////////////////////////

Servo e1;
Servo e2;

//////////////////////////////////////Viper//////////////////////////////////////////////////

Servo v;
//////////////////////////////////////////////////////////////////////////////////////////////
int R = 255;
int G = 0;
int B = 0;

// Calculates the next value in a rainbow sequence
void nextRainbowColor() {
  if (R > 0 && B == 0) {
    R--;
    G++;
  }
  if (G > 0 && R == 0) {
    G--;
    B++;
  }
  if (B > 0 && G == 0) {
    R++;
    B--;
  }
}

void setup() {
  // put your setup code here, to run once:a
  
 Serial.begin(115200);
  PS4.begin("1a:2b:3c:01:01:02");
  Serial.println("Ready.");
  PA.attach(M1);
  PB.attach(M2);
  PC.attach(M3);
  PD.attach(M4);
  ///////////////////////////////////viper///////////////////////////////////////////////////
  v.attach(26);
  ////////////////////////////////////E-Bike////////////////////////////////////////////////////
  e1.attach(32);
  e2.attach(33);

  /////////////////////////////////////Pneumatics/////////////////////////////////////////////
  pinMode(IN_1,OUTPUT);
  pinMode(IN_2,OUTPUT);
  pinMode(IN_3,OUTPUT);
  pinMode(IN_4,OUTPUT);
}
void loop() {
  // put your main code here, to run repeatedly:
   
 if (PS4.isConnected()) 
 {
  
  PS4.setLed(90, 20,145 );
    nextRainbowColor();

    // Sets how fast the controller's front light flashes
    // Params: How long the light is on in ms, how long the light is off in ms
    // Range: 0->2550 ms, Set to 0, 0 for the light to remain on
    PS4.setFlashRate(PS4.LStickY() * 0, PS4.RStickY() * 0);

    // Sets the rumble of the controllers
    // Params: Weak rumble intensity, Strong rumble intensity
    // Range: 0->255
    PS4.setRumble(PS4.L2Value()  , PS4.R2Value() );

    // Sends data set in the above three instructions to the controller
    PS4.sendToController();

    // Don't send data to the controller immediately, will cause buffer overflow
    delay(10);
  
  

    
  

        if (PS4.LStickX() > 15 || PS4.LStickX() < -15 || PS4.LStickY() > 15 || PS4.LStickY() < -15 || PS4.RStickX() > 15 || PS4.RStickX() < -15 || PS4.RStickY() > 15 || PS4.RStickY() < -15) 
        {
          if (PS4.RStickX() > 15 ) 
          {
            x = PS4.RStickX();
            x = map(PS4.RStickX(), 15, 127, 0,-90 );
          }
          else if (PS4.RStickX() < -15)
          {
            x = PS4.RStickX();
            x = map(PS4.RStickX(), -15, -127, 0,90); 
          }
          else if (PS4.RStickX() > -15 && PS4.RStickX() < 15)
          {
            x = 0;
          }
          if (PS4.RStickY() > 15  )
           {
            y = PS4.RStickY();
            y = map(PS4.RStickY(), 15, 127, 0,-90);
          }
          else if (PS4.RStickY() < -15)
          {
            y = PS4.RStickY();
            y = map(PS4.RStickY(), -15, -127, 0,90);
          }
          else if (PS4.RStickY() > -15 && PS4.RStickY() < 15)
          {
            y = 0;
          }

        
         if (PS4.LStickX() > 15 )
         {
          rotational = PS4.LStickX();
          rotational_pwm = map(rotational, 15, 127, 0, -50);
         }
         else if (PS4.LStickX() < - 15 )
         {
           rotational = PS4.LStickX();
          rotational_pwm = map(rotational, -15, -127, 0, 50);
         }
         else if (PS4.LStickX() > - 15 && PS4.LStickX() <  15 )
         {
          rotational_pwm = 0;
         }
         if (PS4.RStickX() > -15 && PS4.RStickX() < 15)
          {
            x = 0;
          }
          if (PS4.RStickY() > -15 && PS4.RStickY() < 15)
          {
            y = 0;
          }
       }
 ///////////////////////////////////////////Viper/////////////////////////////////////////        
        if (PS4.L2())
         {
          if(PS4.L2Value() < 30)
          {
              up = 0;
          }
          else
          {
            up = map(PS4.L2Value(),30,255,90,180);
          }
       v.write(up);
      

       }

    if (PS4.R2()) 
    {
      if(PS4.R2Value() < 30)
      {
        down = 0;
      }
      else
      {
        down = map(PS4.R2Value(),30,255,0, 90 );
      }
        v.write(down);
    }
   /////////////////////////////////////////E-Bike(Ball Throwing)////////////////////////////////
    if (PS4.Square())
     
       {
          e1.write(70);
          e2.write(70);
          delay(1000);
          digitalWrite(IN_4,1);
          delay(400);
          digitalWrite(IN_4,0);
          delay(400);
        }
     
    if (PS4.Triangle()) 
    
      {
         e1.write(50);
          e2.write(50);
          delay(1000);
          digitalWrite(IN_4,1);
          delay(400);
          digitalWrite(IN_4,0);
          delay(400);
          
      }
      if(PS4.Circle())
      {
        e1.write(30);
          e2.write(30);
         delay(1000);
          digitalWrite(IN_4,1);
          delay(400);
          digitalWrite(IN_4,0);
          delay(400);
      }
      if(PS4.Cross())
      {
        e1.write(90);
          e2.write(90);
          delay(50);      
      }
  ///////////////////////////////////////Pneumatics////////////////////////////////////////////

  /////////////////////////////////Front Piston Up/Down////////////////////////////////////////
    
    if (PS4.Up())
    {
      digitalWrite(IN_3,1);
      delay(400);
    }

    if(PS4.Touchpad())
    {
      v.write(90);
      
    }
  //////////////////////////////////////Gripper Piston (Push)////////////////////////////////////
  
    if (PS4.Down())
    {
       digitalWrite(IN_3,0);
      delay(400);
       }

  //////////////////////////////////////Ball Gripper open/close///////////////////////////////////
    if(PS4.Left())
    {
      digitalWrite(IN_2,0);
      delay(400);
      }
    if(PS4.Right())
    {
      digitalWrite(IN_2,1);
      delay(400);
    }
   ///////////////////////////////////Seedling Open/Close////////////////////////////////////////
   
   if(PS4.R1())
   {
    digitalWrite(IN_1,1);
    delay(400);
   }
   if(PS4.L1())
   {
    digitalWrite(IN_1,0);
    delay(400);
   }
     
  }     
   //////////////////////////////////////////////////////////////////////////////////////////////

  magnitude = sqrt(sq(x) + sq(y));
  theta = atan2(y,x);
  a = magnitude * (sin(theta + (PI / 4)));
  b = magnitude * (cos(theta + (PI / 4)));
  c = magnitude * (sin(theta + (PI / 4)));
  d = magnitude * (cos(theta + (PI / 4)));

  Serial.print("a = ");
  Serial.println(a);
  Serial.print("b = ");
  Serial.println(b);
  Serial.print("c = ");
  Serial.println(c);
  Serial.print("d = ");
  Serial.println(d);
  
Serial.print("L2 = ");
        Serial.println(up);


 Serial.print("R2 = ");
      Serial.println(down);

 Serial.print("rotational_pwm = ");
 Serial.println(rotational_pwm);


 pa = map(a,-127,127,180,0);
 pb = map(b,-127,127,0,180);
 pc = map(a,-127,127,0,180); 
 pd = map(b,-127,127,180,0); 

  Serial.print("pa = ");
  Serial.println(pa);
  Serial.print("pb = ");
  Serial.println(pb);
  Serial.print("pc = ");
  Serial.println(pc);
  Serial.print("pd = ");
  Serial.println(pd);

  pa = pa + rotational_pwm;
  pb = pb - rotational_pwm;
  pc = pc + rotational_pwm;
  pd = pd - rotational_pwm;
  
  /////////////////Motor Commands//////////////////////
  PA.write(pa);
  PB.write(pb);
  PC.write(pc);
  PD.write(pd); 
}
  