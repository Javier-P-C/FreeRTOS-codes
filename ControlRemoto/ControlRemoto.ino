#include <IRremote.h>

int RECV_PIN = 11;

const char type ='W';// W for white, B for black. Must keep single quotes like 'B' or 'W'
const boolean PCB = 0;// if receiver is PCB set to 1, if not set to 0. See video for details

IRrecv irrecv(RECV_PIN);

// this is array holding codes for White Remote when used with PCB verion of receiver
unsigned int whiteRemotePCB[] ={
            0xE318261B, // CH-
            0x511DBB,   // CH
            0xEE886D7F,  // CH+

            0x52A3D41F, // |<<
            0xD7E84B1B, // >>|
            0x20FE4DBB, // >||          

            0xF076C13B, // -
            0xA3C8EDDB, // +
            0x12CEA6E6, // EQ

            0xC101E57B, // 0
            0x97483BFB, // 100+
            0xF0C41643, // 200+

            0x9716BE3F, // 1
            0x3D9AE3F7, // 2
            0x6182021B, // 3           

            0x8C22657B, // 4 
            0x488F3CBB, // 5
            0x449E79F,  // 6

            0x32C6FDF7, // 7
            0x1BC0157B, // 8
            0x3EC3FC1B  // 9                          
            };

// this is array holding codes for White Remote when used with non-PCB verion of receiver            
unsigned int whiteRemote[] ={
            0xFFA25D, // CH-
            0xFF629D,   // CH
            0xFFE21D,  // CH+

            0xFF22DD, // |<<
            0xFF02FD, // >>|
            0xFFC23D, // >||          

            0xFFE01F, // -
            0xFFA857, // +
            0xFF906F, // EQ

            0xFF6897, // 0
            0xFF9867, // 100+
            0xFFB04F, // 200+

            0xFF30CF, // 1
            0xFF18E7, // 2
            0xFF7A85, // 3           

            0xFF10EF, // 4 
            0xFF38C7, // 5
            0xFF5AA5,  // 6

            0xFF42BD, // 7
            0xFF4AB5, // 8
            0xFF52AD  // 9                          
            };
// key lables of white remote
 String whiteRemoteKey[] ={
            "CH-",
            "CH",
            "CH+",

            "|<<",
            ">>|",
            ">||",

            "-",
            "+",
            "EQ",

            "0",
            "100+",
            "200+",

            "1",
            "2",
            "3",

            "4",
            "5",
            "6",

            "7",
            "8",
            "9"
            };

decode_results results;


void setup()
{
  Serial.begin(9600);
  // In case the interrupt driver crashes on setup, give a clue
  // to the user what's going on.
  Serial.println("Robojax Remote Decoder");
  irrecv.enableIRIn(); // Start the receiver

}

void loop() {

  if (irrecv.decode(&results)) {
     //Serial.println(results.value, HEX);
    robojaxValidateCode(results.value);// used the "robojaxValidateCode" bellow
    irrecv.resume(); // Receive the next value
  }
  delay(100);
}

/*
 * function: robojaxValidateCode
 * validates the remote code and prints correct key name
 * cd is code poassed from the loop
 * Written by A. S. for Robojax
 */
void robojaxValidateCode(int cd)
{

  // Robojax IR Remote decoder
  int found=0;

 if(type =='W' && !PCB)
 {
    // Robojax IR White Remote decoder
    // if tyepe is set to 'W' (white remote) and PCB=0 then check Black remote code
      for(int i=0; i< sizeof(whiteRemote)/sizeof(int); i++)
      {
        if(whiteRemote[i] ==cd)
        {
          
          Serial.print("Key pressed:");
          Serial.println(whiteRemoteKey[i]);
    
          found=1;
        }// if matched
      }// for
 }else if(type =='W' && PCB){
    // Robojax IR White Remote decoder
    // if tyepe is set to 'W' (white remote) and PCB=1 then check Black remote code
      for(int i=0; i< sizeof(whiteRemotePCB)/sizeof(int); i++)
      {
        if(whiteRemotePCB[i] ==cd)
        {
          
          Serial.print("Key pressed:");
          Serial.println(whiteRemoteKey[i]);
    
          found=1;
        }// if matched
      }// for  
 }else if(type =='B' && PCB){
    // Robojax IR White Remote decoder
       // if tyepe is set to 'B' (black remote) and PCB=1 then check Black remote code
       for(int i=0; i< sizeof(blackRemotePCB)/sizeof(int); i++)
      {
        // Robojax IR black Remote decoder
        if(blackRemotePCB[i] ==cd)
        {

          Serial.print("Key pressed:");
          Serial.println(blackRemoteKey[i]);
    
          found=1;
        }// if matched
      }// for   
 }else{

      // if tyepe is set to 'B' (black remote) and PCB =0 then check Black remote code
       for(int i=0; i< sizeof(blackRemote)/sizeof(int); i++)
      {
        // Robojax IR black Remote decoder
        if(blackRemote[i] ==cd)
        {
          if(blackRemoteKey[i] == "OK"){
            digitalWrite(9,HIGH);
          }
          Serial.print("Key pressed:");
          Serial.println(blackRemoteKey[i]);
    
          found=1;
        }// if matched
      }// for  
 }// else
  if(!found){
    if(cd !=0xFFFFFFFF)
      {
    Serial.println("Key unkown");
      }
  }// found
}
