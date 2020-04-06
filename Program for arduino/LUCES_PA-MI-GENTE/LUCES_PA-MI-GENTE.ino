
#define   R_LED   9
#define   G_LED   10
#define   B_LED   11

String tmp="";
String tmp1="";
char a='\0';
char* data;
byte dmxR_1;
byte dmxG_1;
byte dmxB_1;
byte dmxE_1;

String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete

void setup() 
{  
  dmxR_1=0;
  dmxG_1=0;
  dmxB_1=0;

  Serial.begin(74880);
  
  inputString.reserve(200);
  tmp="";

  
  delay(1000);
  Serial.println("Ready");
  //Serial.print(tmp);
}

void loop() 
{ 
    if (stringComplete) {
    //Serial.println(inputString);
    // clear the string:
    tmp = inputString;
    inputString = "";
    stringComplete = false;
    //Serial.println(tmp);
  }
 
  if(tmp != "")
  {
  //Serial.println(tmp);
  int posR = tmp.indexOf("R:");
  int posG = tmp.indexOf("G:");
  int posB = tmp.indexOf("B:");
  int strobe = tmp.indexOf("E:");

    tmp1 = tmp.substring(posR+2,posG);
  dmxR_1 = tmp1.toInt();
         tmp1 = tmp.substring(posG+2,posB);
  dmxG_1 = tmp1.toInt();
         tmp1 = tmp.substring(posB+2,strobe);
  dmxB_1 = tmp1.toInt();
         tmp1 = tmp.substring(strobe+2);
  dmxE_1 = tmp1.toInt();

  Serial.print(dmxR_1);
  Serial.print(" ");
  Serial.print(dmxG_1);
  Serial.print(" ");
  Serial.print(dmxB_1);
  Serial.print(" ");
  Serial.println(dmxE_1);

  tmp="";
  tmp1="";
  }
  byte _dmxR_1 = map(dmxR_1,0,255,0,80);

if(dmxE_1 ==0)
{
  analogWrite(R_LED,_dmxR_1);
  analogWrite(G_LED,dmxG_1);
  analogWrite(B_LED,dmxB_1); 
}
 else if (dmxE_1 >1)
{
  analogWrite(R_LED,_dmxR_1);
  analogWrite(G_LED,dmxG_1);
  analogWrite(B_LED,dmxB_1);

  delay(dmxE_1);
  
  analogWrite(R_LED,0);
  analogWrite(G_LED,0);
  analogWrite(B_LED,0);

  delay(dmxE_1);
}

}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
