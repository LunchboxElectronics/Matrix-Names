/*  
  NameMatrix - Input a name and display it on a number of Lunchbox Electronics
  LED Matrix Boards
 
  CC BY-SA Teddy Lowe, December 2016
  Lunchbox Electronics
  http://www.lunchboxelectronics.com/
______________________________________

 Code History:
 --------------

The original code was written for the Wiring board by:
 * Nicholas Zambetti and Dave Mellis /Interaction Design Institute Ivrea /Dec 2004
 * http://www.potemkin.org/uploads/Wiring/MAX7219.txt

First modification by:
 * Marcus Hannerstig/  K3, malmÃ¶ hÃ¶gskola /2006
 * http://www.xlab.se | http://arduino.berlios.de

This version is by:
 * tomek ness /FH-Potsdam / Feb 2007
 * http://design.fh-potsdam.de/ 

 * @acknowledgements: eric f. 

-----------------------------------

General notes: 

-if you are only using one max7219, then use the function maxSingle to control
 the little guy ---maxSingle(register (1-8), collum (0-255))

-if you are using more than one max7219, and they all should work the same, 
then use the function maxAll ---maxAll(register (1-8), collum (0-255))

-if you are using more than one max7219 and just want to change something
at one little guy, then use the function maxOne
---maxOne(Max you want to control (1== the first one), register (1-8), 
column (0-255))

During initiation, be sure to send every part to every max7219 and then
upload it.
For example, if you have five max7219's, you have to send the scanLimit 5 times
before you load it-- otherwise not every max7219 will get the data. the
function maxInUse keeps track of this, just tell it how many max7219 you are
using.
*/

//===============================================
//                  Edit here

char nameArr[] = "LBE"; // Put your own name within the quotes!

int maxInUse = 3;    //change this variable to set how many MAX7219's you'll use

//===============================================

int dataIn = 2;
int load = 3;
int clock = 4;

int e = 0;           // just a variable

// define max7219 registers
byte max7219_reg_noop        = 0x00;
byte max7219_reg_digit0      = 0x01;
byte max7219_reg_digit1      = 0x02;
byte max7219_reg_digit2      = 0x03;
byte max7219_reg_digit3      = 0x04;
byte max7219_reg_digit4      = 0x05;
byte max7219_reg_digit5      = 0x06;
byte max7219_reg_digit6      = 0x07;
byte max7219_reg_digit7      = 0x08;
byte max7219_reg_decodeMode  = 0x09;
byte max7219_reg_intensity   = 0x0a;
byte max7219_reg_scanLimit   = 0x0b;
byte max7219_reg_shutdown    = 0x0c;
byte max7219_reg_displayTest = 0x0f;

void putByte(byte data) {
  byte i = 8;
  byte mask;
  while(i > 0) {
    mask = 0x01 << (i - 1);      // get bitmask
    digitalWrite( clock, LOW);   // tick
    if (data & mask){            // choose bit
      digitalWrite(dataIn, HIGH);// send 1
    }else{
      digitalWrite(dataIn, LOW); // send 0
    }
    digitalWrite(clock, HIGH);   // tock
    --i;                         // move to lesser bit
  }
}

void maxSingle( byte reg, byte col) {    
//maxSingle is the "easy"  function to use for a single max7219

  digitalWrite(load, LOW);       // begin     
  putByte(reg);                  // specify register
  putByte(col);//((data & 0x01) * 256) + data >> 1); // put data   
  digitalWrite(load, LOW);       // and load da stuff
  digitalWrite(load,HIGH); 
}

void maxAll (byte reg, byte col) {    // initialize  all  MAX7219's in the system
  int c = 0;
  digitalWrite(load, LOW);  // begin     
  for ( c =1; c<= maxInUse; c++) {
  putByte(reg);  // specify register
  putByte(col);//((data & 0x01) * 256) + data >> 1); // put data
    }
  digitalWrite(load, LOW);
  digitalWrite(load,HIGH);
}

void maxOne(byte maxNr, byte reg, byte col) {    
//maxOne is for addressing different MAX7219's, 
//while having a couple of them cascaded

  int c = 0;
  digitalWrite(load, LOW);  // begin     

  for ( c = maxInUse; c > maxNr; c--) {
    putByte(0);    // means no operation
    putByte(0);    // means no operation
  }

  putByte(reg);  // specify register
  putByte(col);//((data & 0x01) * 256) + data >> 1); // put data 

  for ( c =maxNr-1; c >= 1; c--) {
    putByte(0);    // means no operation
    putByte(0);    // means no operation
  }

  digitalWrite(load, LOW); // and load da stuff
  digitalWrite(load,HIGH); 
}

void setup () {

  pinMode(dataIn, OUTPUT);
  pinMode(clock,  OUTPUT);
  pinMode(load,   OUTPUT);

  digitalWrite(13, HIGH);  

//initiation of the max 7219
  maxAll(max7219_reg_scanLimit, 0x07);      
  maxAll(max7219_reg_decodeMode, 0x00);  // using an led matrix (not digits)
  maxAll(max7219_reg_shutdown, 0x01);    // not in shutdown mode
  maxAll(max7219_reg_displayTest, 0x00); // no display test
   for (e=1; e<=8; e++) {    // empty registers, turn all LEDs off 
    maxAll(e,0);
  }
  maxAll(max7219_reg_intensity, 0x08 & 0x08);    // the first 0x0f is the value you can set
                                                  // range: 0x00 to 0x0f
}  

void loop () {
  char* x = nameArr;
  int i;
  for (i = 1; i <= maxInUse; i++){
    displayLetter(i, *x);
    x++;
  }
  while(1);
}

void displayLetter(int maxPosition, char letter){

  if (letter > 90 && letter < 123){
    letter = letter - 32;
  }

  switch (letter){
    
    case 'A' :
      letterA(maxPosition);
      break;
    case 'B' :
      letterB(maxPosition);
      break;
    case 'C' :
      letterC(maxPosition);
      break;
    case 'D' :
      letterD(maxPosition);
      break;
    case 'E' :
      letterE(maxPosition);
      break;
    case 'F' :
      letterF(maxPosition);
      break;
    case 'G' :
      letterG(maxPosition);
      break;
    case 'H' :
      letterH(maxPosition);
      break;
    case 'I' :
      letterI(maxPosition);
      break;
    case 'J' :
      letterJ(maxPosition);
      break;
    case 'K' :
      letterK(maxPosition);
      break;
    case 'L' :
      letterL(maxPosition);
      break;
    case 'M' :
      letterM(maxPosition);
      break;
    case 'N' :
      letterN(maxPosition);
      break;
    case 'O' :
      letterO(maxPosition);
      break;
    case 'P' :
      letterP(maxPosition);
      break;
    case 'Q' :
      letterQ(maxPosition);
      break;
    case 'R' :
      letterR(maxPosition);
      break;
    case 'S' :
      letterS(maxPosition);
      break;
    case 'T' :
      letterT(maxPosition);
      break;
    case 'U' :
      letterU(maxPosition);
      break;
    case 'V' :
      letterV(maxPosition);
      break;
    case 'W' :
      letterW(maxPosition);
      break;
    case 'X' :
      letterX(maxPosition);
      break;
    case 'Y' :
      letterY(maxPosition);
      break;
    case 'Z' :
      letterZ(maxPosition);
      break;
    default:
      Heart(maxPosition);
  }
}

void letterA(int maxPosition){

  maxOne(maxPosition,7,B00111110); 
  maxOne(maxPosition,6,B01111110);
  maxOne(maxPosition,5,B11001000);
  maxOne(maxPosition,4,B10001000);
  maxOne(maxPosition,3,B11001000);
  maxOne(maxPosition,2,B01111110);
  maxOne(maxPosition,1,B00111110);
  maxOne(maxPosition,8,B00000000);

}

void letterB(int maxPosition){

  maxOne(maxPosition,7,B01101100); 
  maxOne(maxPosition,6,B11111110);
  maxOne(maxPosition,5,B10010010);
  maxOne(maxPosition,4,B10010010);
  maxOne(maxPosition,3,B10010010);
  maxOne(maxPosition,2,B11111110);
  maxOne(maxPosition,1,B11111110);
  maxOne(maxPosition,8,B00000000);

}

void letterC(int maxPosition){

  maxOne(maxPosition,7,B01000100); 
  maxOne(maxPosition,6,B11000110);
  maxOne(maxPosition,5,B10000010);
  maxOne(maxPosition,4,B10000010);
  maxOne(maxPosition,3,B11000110);
  maxOne(maxPosition,2,B01111100);
  maxOne(maxPosition,1,B00111000);
  maxOne(maxPosition,8,B00000000);

}

void letterD(int maxPosition){

  maxOne(maxPosition,7,B00111000); 
  maxOne(maxPosition,6,B01111100);
  maxOne(maxPosition,5,B11000110);
  maxOne(maxPosition,4,B10000010);
  maxOne(maxPosition,3,B10000010);
  maxOne(maxPosition,2,B11111110);
  maxOne(maxPosition,1,B11111110);
  maxOne(maxPosition,8,B00000000);

}

void letterE(int maxPosition){

  maxOne(maxPosition,7,B10000010); 
  maxOne(maxPosition,6,B10010010);
  maxOne(maxPosition,5,B10010010);
  maxOne(maxPosition,4,B10010010);
  maxOne(maxPosition,3,B10010010);
  maxOne(maxPosition,2,B11111110);
  maxOne(maxPosition,1,B11111110);
  maxOne(maxPosition,8,B00000000);

}

void letterF(int maxPosition){

  maxOne(maxPosition,7,B10000000); 
  maxOne(maxPosition,6,B10010000);
  maxOne(maxPosition,5,B10010000);
  maxOne(maxPosition,4,B10010000);
  maxOne(maxPosition,3,B10010000);
  maxOne(maxPosition,2,B11111110);
  maxOne(maxPosition,1,B11111110);
  maxOne(maxPosition,8,B00000000);

}

void letterG(int maxPosition){

  maxOne(maxPosition,7,B10011110); 
  maxOne(maxPosition,6,B10011110);
  maxOne(maxPosition,5,B10010010);
  maxOne(maxPosition,4,B10000010);
  maxOne(maxPosition,3,B11000110);
  maxOne(maxPosition,2,B01111100);
  maxOne(maxPosition,1,B00111000);
  maxOne(maxPosition,8,B00000000);

}

void letterH(int maxPosition){

  maxOne(maxPosition,7,B11111110); 
  maxOne(maxPosition,6,B11111110);
  maxOne(maxPosition,5,B00010000);
  maxOne(maxPosition,4,B00010000);
  maxOne(maxPosition,3,B00010000);
  maxOne(maxPosition,2,B11111110);
  maxOne(maxPosition,1,B11111110);
  maxOne(maxPosition,8,B00000000);

}

void letterI(int maxPosition){

  maxOne(maxPosition,7,B10000010); 
  maxOne(maxPosition,6,B10000010);
  maxOne(maxPosition,5,B11111110);
  maxOne(maxPosition,4,B11111110);
  maxOne(maxPosition,3,B10000010);
  maxOne(maxPosition,2,B10000010);
  maxOne(maxPosition,1,B00000000);
  maxOne(maxPosition,8,B00000000);

}

void letterJ(int maxPosition){

  maxOne(maxPosition,7,B11111100); 
  maxOne(maxPosition,6,B11111110);
  maxOne(maxPosition,5,B10000010);
  maxOne(maxPosition,4,B10000010);
  maxOne(maxPosition,3,B00000010);
  maxOne(maxPosition,2,B00001110);
  maxOne(maxPosition,1,B00001100);
  maxOne(maxPosition,8,B00000000);

}

void letterK(int maxPosition){

  maxOne(maxPosition,7,B10000010); 
  maxOne(maxPosition,6,B11000110);
  maxOne(maxPosition,5,B01101110);
  maxOne(maxPosition,4,B00111100);
  maxOne(maxPosition,3,B00011000);
  maxOne(maxPosition,2,B11111110);
  maxOne(maxPosition,1,B11111110);
  maxOne(maxPosition,8,B00000000);

}

void letterL(int maxPosition){

  maxOne(maxPosition,7,B00000010); 
  maxOne(maxPosition,6,B00000010);
  maxOne(maxPosition,5,B00000010);
  maxOne(maxPosition,4,B00000010);
  maxOne(maxPosition,3,B11111110);
  maxOne(maxPosition,2,B11111110);
  maxOne(maxPosition,1,B00000000);
  maxOne(maxPosition,8,B00000000);

}

void letterM(int maxPosition){

  maxOne(maxPosition,7,B11111110); 
  maxOne(maxPosition,6,B11111110);
  maxOne(maxPosition,5,B01110000);
  maxOne(maxPosition,4,B00111000);
  maxOne(maxPosition,3,B01110000);
  maxOne(maxPosition,2,B11111110);
  maxOne(maxPosition,1,B11111110);
  maxOne(maxPosition,8,B00000000);

}

void letterN(int maxPosition){

  maxOne(maxPosition,7,B11111110); 
  maxOne(maxPosition,6,B11111110);
  maxOne(maxPosition,5,B00011100);
  maxOne(maxPosition,4,B00111000);
  maxOne(maxPosition,3,B01110000);
  maxOne(maxPosition,2,B11111110);
  maxOne(maxPosition,1,B11111110);
  maxOne(maxPosition,8,B00000000);

}

void letterO(int maxPosition){

  maxOne(maxPosition,7,B01111100); 
  maxOne(maxPosition,6,B11111110);
  maxOne(maxPosition,5,B10000010);
  maxOne(maxPosition,4,B10000010);
  maxOne(maxPosition,3,B10000010);
  maxOne(maxPosition,2,B11111110);
  maxOne(maxPosition,1,B01111100);
  maxOne(maxPosition,8,B00000000);

}

void letterP(int maxPosition){

  maxOne(maxPosition,7,B01110000); 
  maxOne(maxPosition,6,B11111000);
  maxOne(maxPosition,5,B10001000);
  maxOne(maxPosition,4,B10001000);
  maxOne(maxPosition,3,B10001000);
  maxOne(maxPosition,2,B11111110);
  maxOne(maxPosition,1,B11111110);
  maxOne(maxPosition,8,B00000000);

}

void letterQ(int maxPosition){

  maxOne(maxPosition,7,B01111010); 
  maxOne(maxPosition,6,B11111100);
  maxOne(maxPosition,5,B10001110);
  maxOne(maxPosition,4,B10001010);
  maxOne(maxPosition,3,B10000010);
  maxOne(maxPosition,2,B11111110);
  maxOne(maxPosition,1,B01111100);
  maxOne(maxPosition,8,B00000000);

}

void letterR(int maxPosition){

  maxOne(maxPosition,7,B01110010); 
  maxOne(maxPosition,6,B11110110);
  maxOne(maxPosition,5,B10011110);
  maxOne(maxPosition,4,B10001100);
  maxOne(maxPosition,3,B10001000);
  maxOne(maxPosition,2,B11111110);
  maxOne(maxPosition,1,B11111110);
  maxOne(maxPosition,8,B00000000);

}

void letterS(int maxPosition){

  maxOne(maxPosition,7,B00001100); 
  maxOne(maxPosition,6,B01011110);
  maxOne(maxPosition,5,B11010010);
  maxOne(maxPosition,4,B10010010);
  maxOne(maxPosition,3,B10010010);
  maxOne(maxPosition,2,B11110110);
  maxOne(maxPosition,1,B01100100);
  maxOne(maxPosition,8,B00000000);

}

void letterT(int maxPosition){

  maxOne(maxPosition,7,B10000000); 
  maxOne(maxPosition,6,B10000000);
  maxOne(maxPosition,5,B11111110);
  maxOne(maxPosition,4,B11111110);
  maxOne(maxPosition,3,B10000000);
  maxOne(maxPosition,2,B10000000);
  maxOne(maxPosition,1,B00000000);
  maxOne(maxPosition,8,B00000000);

}

void letterU(int maxPosition){

  maxOne(maxPosition,7,B11111100); 
  maxOne(maxPosition,6,B11111110);
  maxOne(maxPosition,5,B00000010);
  maxOne(maxPosition,4,B00000010);
  maxOne(maxPosition,3,B00000010);
  maxOne(maxPosition,2,B11111110);
  maxOne(maxPosition,1,B11111100);
  maxOne(maxPosition,8,B00000000);

}

void letterV(int maxPosition){

  maxOne(maxPosition,7,B11110000); 
  maxOne(maxPosition,6,B11111000);
  maxOne(maxPosition,5,B00011100);
  maxOne(maxPosition,4,B00001110);
  maxOne(maxPosition,3,B00011100);
  maxOne(maxPosition,2,B11111000);
  maxOne(maxPosition,1,B11110000);
  maxOne(maxPosition,8,B00000000);

}

void letterW(int maxPosition){

  maxOne(maxPosition,7,B11111110); 
  maxOne(maxPosition,6,B11111110);
  maxOne(maxPosition,5,B00011100);
  maxOne(maxPosition,4,B00111000);
  maxOne(maxPosition,3,B00011100);
  maxOne(maxPosition,2,B11111110);
  maxOne(maxPosition,1,B11111110);
  maxOne(maxPosition,8,B00000000);

}

void letterX(int maxPosition){

  maxOne(maxPosition,7,B11000110); 
  maxOne(maxPosition,6,B11101110);
  maxOne(maxPosition,5,B01111100);
  maxOne(maxPosition,4,B00111000);
  maxOne(maxPosition,3,B01111100);
  maxOne(maxPosition,2,B11101110);
  maxOne(maxPosition,1,B11000110);
  maxOne(maxPosition,8,B00000000);

}

void letterY(int maxPosition){

  maxOne(maxPosition,7,B11100000); 
  maxOne(maxPosition,6,B11110000);
  maxOne(maxPosition,5,B00011110);
  maxOne(maxPosition,4,B00011110);
  maxOne(maxPosition,3,B11110000);
  maxOne(maxPosition,2,B11100000);
  maxOne(maxPosition,1,B00000000);
  maxOne(maxPosition,8,B00000000);

}

void letterZ(int maxPosition){

  maxOne(maxPosition,7,B11000010); 
  maxOne(maxPosition,6,B11100010);
  maxOne(maxPosition,5,B11110010);
  maxOne(maxPosition,4,B10111010);
  maxOne(maxPosition,3,B10011110);
  maxOne(maxPosition,2,B10001110);
  maxOne(maxPosition,1,B10000110);
  maxOne(maxPosition,8,B00000000);

}

void Heart(int maxPosition) {
  
  maxOne(maxPosition,7,B00110000); 
  maxOne(maxPosition,6,B01111000);
  maxOne(maxPosition,5,B00111100);
  maxOne(maxPosition,4,B00011110);
  maxOne(maxPosition,3,B00111100);
  maxOne(maxPosition,2,B01111000);
  maxOne(maxPosition,1,B00110000);
  maxOne(maxPosition,8,0);

}

void Smile(int maxPosition){
  
  maxOne(maxPosition,7,56);
  maxOne(maxPosition,6,68);
  maxOne(maxPosition,5,130);
  maxOne(maxPosition,4,0);
  maxOne(maxPosition,3,108);
  maxOne(maxPosition,2,108);
  maxOne(maxPosition,1,0);
  maxOne(maxPosition,8,0);

}
  
