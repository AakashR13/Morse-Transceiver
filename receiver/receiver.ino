#include <SoftwareSerial.h>
SoftwareSerial mySerial(0,1);
const char MorseTree[] = {'\0','E', 'T', 'I', 'A', 'N', 'M', 'S',
                          'U', 'R', 'W', 'D', 'K', 'G', 'O', 'H',
                          'V', 'F', 'U', 'L', 'A', 'P', 'J', 'B',
                          'X', 'C', 'Y', 'Z', 'Q', '\0','\0','5',
                          '4', '\0','3', '\0','\0','\0','2', '\0',
                          '\0','+', '\0','\0','\0','\0','1', '6',
                          '=', '/', '\0','\0','\0','(', '\0','7',
                          '\0','\0','\0','8', '\0','9', '0', '\0',
                          '\0','\0','\0','\0','\0','\0','\0','\0',
                          '\0','\0','\0','?', '_', '\0','\0','\0',
                          '\0','"', '\0','\0','.', '\0','\0','\0',
                          '\0','@', '\0','\0','\0','\0','\0','\0',
                          '-', '\0','\0','\0','\0','\0','\0','\0',
                          '\0',';', '!', '\0',')', '\0','\0','\0',
                          '\0','\0',',', '\0','\0','\0','\0',':',
                          '\0','\0','\0','\0','\0','\0','\0'
                         };

int val = 0; // A Variable to Store the Light Value from the LDR
int ctrHigh = 0;
int ctrLow = 0;
int codePtr = 0;
int dotLen = 100;

void setup()
{
  mySerial.begin(9600);// Start a Serial Connection
  Serial.print(codePtr);
  
}

void loop()
{
  val = analogRead(4);
  if (val >= 20) // Triggering point for LED based on surrounding by trial and error method.
  {
    ctrHigh++;
    ctrLow = 0;
    digitalWrite(13, HIGH);
  } else {
    ctrLow++;
    if ((ctrHigh >= dotLen) && (ctrHigh < dotLen * 6)) { // ctrHigh value calculated as dotLen*6 on the basis of surroundings by trial and error.
      codePtr = (2*codePtr) + 1;
    } else if (ctrHigh >= dotLen * 6) {
      codePtr = (2*codePtr) + 2;
    } else {
      if(ctrLow == dotLen * 6){ 
        mySerial.print(MorseTree[codePtr]);
        codePtr = 0;
      }
    }

    ctrHigh = 0;
    digitalWrite(13, LOW);
  }
}