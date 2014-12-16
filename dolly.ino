
String inputString = "";         // a string to hold incoming data
String inCharS = "";
String inCharD = "";
String inCharB = "Hello";
char i;
char b;
boolean k = true;
boolean j = true;
boolean dec = false;
boolean stringComplete = false;  // whether the string is complete

void setup() {
  // initialize serial:
  Serial.begin(9600);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
  inCharS.reserve(200);
}


/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read(); 
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    } 
  }
}

void move(char m, int mm, int mantissa)
{
   Serial.println(m);
      Serial.println('\n');
      Serial.println(mm);
      Serial.println('\n');      
         Serial.println(mantissa);
               Serial.println('\n');

}


//  retreiveD looks at incoming string extracts distance in mm's and the mantissa in a seperate variable up to 2 dec place
//  sends distances and motor label to the move function 
void retrieveD(char m, String inputString)
{
              char motor = m;
              char i = 0;
              char b = 0;
              boolean k = true;
              boolean dec = false;
              while (k) {
                  char inChar = inputString[i+2];
                  if (inChar == '.') {  //if we hit a decimal place put the mantissa in a seperate var
                      inCharS[i] = '\0'; //terminate first buffer
                      dec = true;  //indicate this number has a decimal place
                      for (b=0; b <=1; b++) {  //don't store more than 2 decimal places
                          i++;
                          inChar = inputString[i+2];
                              if (inChar == '\n'){
                                  inCharD[b] = '\0';
                                  k = false;
                              }
                          inCharD  += inChar;
                      }
                   }
                   if (inChar == '\n') {
                       inCharS[i] = '\0';
                       k = false;
                   }
              
              if (dec == false) {
                  inCharS += inChar; //have to use inChar beacuse inCharS[i] = inputString[i+2]; doesn't work
                                    
              }
              i++;
              }
              
              int mm = (int)inCharS.toInt();
              
              if (dec) { 
                  int mantissa = (int)inCharD.toInt();
                  move(motor, mm, mantissa);
                  inputString = "";
                  inCharD = "";
                  inCharS = "";

              }
              else  {
                  int mantissa = 0;
                  move(motor, mm, mantissa);
                  inputString = "";
                  inCharS = "";
              }


}

void loop() {
    if (stringComplete) {
      switch (inputString[0]) {
        
        case 'x':{                           //
          char x = 'x';                      //
          retrieveD(x,  inputString);        // 
          break;                             // 
        }                                    //    
        case 'y':{                           // 
          char y = 'y';                      //  if (lowercase only) x y or z is recieved, retrieveD() will extract the numbers following a space after the letter.      
          retrieveD(y,  inputString);        //  template message: "x 20" (x, y or z followed by a space followed by distance in mm's)
          break;                             //   0.01 mm = smallest increment. 3 decimal input will be truncated to 2 decimal places ( not rounded ).     
        }                                    //  x 20 does not mean 'travel forward 20 mm's' (relative positioning)    
        case 'z':{                           //  it means 'travel to the 20th mm (absoloute positioning)   
          char z = 'z';                      //
          retrieveD(z,  inputString);        //
          break;                             //
        }                                    //
                                           
        
        case 'h':
          break;
        case 'a':
          break;
        case 't':
          break;
        case 'k':
          break;
        case '1':
          break;
        case '2':
          break;
        case '3':
          break;           
        case '4':
          break;   
        case '5':
          break;
        case '6':
          break;   
        case '7':
          break;   
      }
    
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
}


