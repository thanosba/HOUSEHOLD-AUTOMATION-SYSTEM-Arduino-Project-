
#include <DHT.h>
#include <Twitter.h>
#include <Servo.h> 
Servo myservo; 
#define DHTPIN A7     // what pin we're connected the DHT output
#define DHTTYPE DHT11   // DHT 11 
DHT dht(DHTPIN, DHTTYPE);

#include <SPI.h>
#include <Ethernet.h>

 int pos = 0; 
 int photocellPin = A15;     // the cell and 10K pulldown are connected to a0
 int photocellReading;     // the analog reading from the sensor divider
 int LEDpin = 32;          // connect Red LED to pin 11 (PWM pin)
 int LEDbrightness;        // 
 int idopoihsh=46;
 boolean pirButton = false;
 boolean prePirButton = false;
 int pirpin = 24;               // choose the input pin (for PIR sensor)
 int sensorPin = 22;
 int pirSensor;
 int flame=28;
 int gas=30;
 int buzer = 26;
 int fotia;
 int aerio;
 int sensor=0;
 int sensor1=0;
 int sensor2=0;
 int sensor3=0;
 int porta1=13;

    // Counter
 int n=1;  // start with 1
 char buf[100];
                     

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x2D };
byte gateway[] = { 192, 168, 2, 1 }; //               <------- PUT YOUR ROUTERS IP Address to which your shield is connected Here
byte subnet[] = { 255, 255, 255, 0 }; //                <------- It will be as it is in most of the cases
IPAddress ip(192,168,2,100);

EthernetServer server(80);



#define RELAY_CH1  34
#define RELAY_CH2  44
#define RELAY_CH3  36
#define RELAY_CH4  48
#define RELAY_CH5  38
#define RELAY_CH6  42


String readString;
 
  
void setup() {
        myservo.write(90);
        myservo.attach(42);
        
        pinMode(flame, INPUT);
        pinMode(gas, INPUT);
 
        pinMode(sensorPin, INPUT);
        pinMode(pirpin, INPUT);
        
        pinMode (porta1,OUTPUT); 
        digitalWrite(porta1,LOW);
        
        pinMode (idopoihsh,OUTPUT); 
        digitalWrite(idopoihsh,LOW);
        
        pinMode(buzer, OUTPUT); 
 	digitalWrite(buzer, LOW);
  
        pinMode(RELAY_CH1, OUTPUT); 
 	digitalWrite(RELAY_CH1, LOW);  // switch on LED1
 
        pinMode(RELAY_CH2, OUTPUT); 
 	digitalWrite(RELAY_CH2, LOW);  // switch on LED2
 
        pinMode(RELAY_CH3, OUTPUT); 
 	digitalWrite(RELAY_CH3, LOW);  // switch on LED3
 
        pinMode(RELAY_CH4, OUTPUT); 
 
	digitalWrite(RELAY_CH4, LOW);  // switch on LED4
 
        pinMode(RELAY_CH5, OUTPUT); 
 	digitalWrite(RELAY_CH5, LOW);  // switch on LED5
 
        pinMode(RELAY_CH6, OUTPUT); 
 	digitalWrite(RELAY_CH6, LOW);  // switch on LED6
  
  
 // Open serial communications and wait for port to open:
  Serial.begin(9600);
while (!Serial) {
    ;
}
  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP()); 
  
}

 Twitter twitter("2869755941-P552lZRQn3mUNdjeHXuA4dJk0YXnuGenM3XyGAz"); // your OAuth Token
                                void tweet(char msg[]){
                                  Serial.println("connecting ...");
                                 if (twitter.post(msg)) {
                                    // Specify &Serial to output received response to Serial.
                                    // If no output is required, you can just omit the argument, e.g.
                                    // int status = twitter.wait();
                                    int status = twitter.wait(&Serial);
                                    if (status == 200) {
                                      Serial.println("OK.");
                                    } 
                                    else {
                                      Serial.print("failed : code ");
                                      Serial.println(status);
                                    }
                                  } 
                                  else {
                                    Serial.println("connection failed.");
                                  }
                                }
  


void loop() {

  
 Serial.println(photocellReading); 
 photocellReading = analogRead(photocellPin); 
 
// LED gets brighter the darker it is at the sensor
  // that means we have to -invert- the reading from 0-1023 back to 1023-0
  photocellReading = 1023 - photocellReading;
  //now we have to map 0-1023 to 0-255 since thats the range analogWrite uses
  LEDbrightness = map(photocellReading, 0, 1023, 0, 255);
  analogWrite(LEDpin, LEDbrightness);
   
   
EthernetClient client = server.available();
      int h = dht.readHumidity();
      int t = dht.readTemperature();
     
        pirSensor= digitalRead(pirpin);
        Serial.print(F(" kinisi "));Serial.println(pirSensor);
     
        int magnetSensor = digitalRead(sensorPin);
        Serial.print(F(" porta "));Serial.println(magnetSensor);
                           
         fotia = digitalRead(flame);     
         Serial.print(F(" fotia "));Serial.println(fotia);
                    
         aerio = digitalRead(gas);
         Serial..print(F(" aerio "));Serial.println(aerio);
                    
                   
                           if ((digitalRead(sensorPin ) == HIGH) && !pirButton){ // check if button is triggered
                            // convert everything to a string(char)
                            sprintf(buf, "o aisfitiras portas energopoithike %d fores!", n); 
                            //tweet(buf);
                            n++;
                             digitalWrite(buzer,HIGH);
                            // zero delay
                            delay(1000);
                           }
                           if ((digitalRead(pirpin ) == HIGH) && !pirButton) { // check if button is triggered
                             //convert everything to a string(char)
                            sprintf(buf, "o aisfitiras kinhshs energopoithike %d fores!", n); 
                            //tweet(buf);
                            n++;
                            digitalWrite(buzer,HIGH);
                          //   zero delay                   
                           delay(1000);
                           
                         }
                            if (digitalRead(flame ) == LOW) { 
                            sprintf(buf, "o aisfitiras fotias energopoithike %d fores!", n); 
                            //tweet(buf);
                            n++;
                             digitalWrite(buzer,HIGH);
                             delay(1000);
                            // zero delay
                           // delay(1000);
                          }
                            if (digitalRead( gas) == LOW) { 
                           sprintf(buf, "o asfitiras aeriou energopoithike %d fores!", n); 
                            //tweet(buf);
                            n++;
                             digitalWrite(buzer,HIGH);
                            // zero delay
                           delay(1000);
                        } 
                        
                         
        digitalWrite(buzer,LOW);             

      //aytosigratish kai reset sinagermou            
      if (digitalRead(sensorPin)==1)
      {   sensor=HIGH;
         digitalWrite (idopoihsh,HIGH);
      }  
      else if (digitalRead(40) == HIGH)
      {sensor=LOW;
      digitalWrite (idopoihsh,LOW);
      }
      if (digitalRead(pirpin)==1)
      {   sensor1=HIGH;
          digitalWrite (idopoihsh,HIGH);
      }  
      else if (digitalRead(40) == HIGH)
      {sensor1=LOW;
      digitalWrite (idopoihsh,LOW);
      } 
      
      if (digitalRead(flame)==0)
      {   sensor2=HIGH;
        digitalWrite (idopoihsh,HIGH);
      }  
      else if (digitalRead(40) == HIGH)
      {  sensor2=LOW;
        digitalWrite (idopoihsh,LOW);
      }
      if (digitalRead(gas)==0)
      {   sensor3=HIGH;
      digitalWrite (idopoihsh,HIGH);
      }  
      else if (digitalRead(40) == HIGH)
      {sensor3=LOW;
        digitalWrite (idopoihsh,LOW);
      }

 
 
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
           
      if (client.available()) {
        
        char c = client.read();
        
        if (readString.length() < 100) {
          //store characters to string
          readString += c;			//Serial.print(c);
        }
        
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
	  client.println("Refresh: 2");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");


          client.println("<html>");          
          client.println("<HEAD>");
          client.println("</HEAD>");          
          client.println("<body bgcolor=#3399FF>");       
          client.print("<center> <p> <h1>Arduino Smart Home  </h1></p> ");
        
          // Relay Status Display
  client.println("<center>");
   client.println("<table border=\"3\">");
    client.println("<tr>"); 
                  

 if(sensor)
                     {
                        client.print(F("<td> <p style=\"font-family:arial;color:black;font-size:20px;\">porta</p><p style=\"font-family:arial;color:green;font-size:25px;\">Klisth</p> </td>"));

                      }
                      else
                      {
                              client.print(F("<td> <p style=\"font-family:arial;color:black;font-size:20px;\">porta</p><p style=\"font-family:arial;color:red;font-size:25px;\">Anoixth</p></td>"));

                      }   
               
 if(sensor1)
                     {
                          client.print(F("<td> <p style=\"font-family:arial;color:black;font-size:20px;\">kinish</p><p style=\"font-family:arial;color:red;font-size:25px;\">ON</p> </td>"));
                      }
                      else
                      {
                           client.print(F("<td> <p style=\"font-family:arial;color:black;font-size:20px;\">kinish</p><p style=\"font-family:arial;color:green;font-size:25px;\">OFF</p></td>"));
                      }
         
 if(sensor2)
                     {
                       client.print(F("<td> <p style=\"font-family:arial;color:black;font-size:20px;\">Fire</p><p style=\"font-family:arial;color:red;font-size:25px;\">fotia</p> </td>"));
                       
                      }
                      else
                      {
                          client.print(F("<td> <p style=\"font-family:arial;color:black;font-size:20px;\">Fire</p><p style=\"font-family:arial;color:green;font-size:25px;\">OK</p></td>"));    
                      }
  if(sensor3)
                     {
                          
                        client.print(F("<td> <p style=\"font-family:arial;color:black;font-size:20px;\">gas</p><p style=\"font-family:arial;color:red;font-size:25px;\">gas alert</p> </td>"));  
                      }
                      else
                      {
                       
                       client.print(F("<td> <p style=\"font-family:arial;color:black;font-size:20px;\">gas</p><p style=\"font-family:arial;color:green;font-size:25px;\">OK</p></td>"));    

                    }
         
                  
          client.println("<center>");
          
              client.println("<table border=\"3\">");
              
                  client.println("<tr>"); 
    
                      if (digitalRead(RELAY_CH1))
                      { 
                           client.print(F("<td> <p style=\"font-family:arial;color:black;font-size:20px;\">Domatio 1</p><p style=\"font-family:arial;color:green;font-size:25px;\">ON</p> </td>"));
                      }
                      else
                      {
                           client.print(F("<td> <p style=\"font-family:arial;color:black;font-size:20px;\">Domatio 1</p><p style=\"font-family:arial;color:red;font-size:25px;\">OFF</p></td>"));
                      }
                      
                                  
                      if (digitalRead(RELAY_CH2))
                      {   
                           client.print(F("<td> <p style=\"font-family:arial;color:black;font-size:20px;\">fournos </p><p style=\"font-family:arial;color:green;font-size:25px;\">ON</p></td>"));
                      }
                      else
                      {  
                          client.print(F("<td> <p style=\"font-family:arial;color:black;font-size:20px;\">fournos </p><p style=\"font-family:arial;color:red;font-size:25px;\">OFF</p></td>"));
                      }
                     
                      
                      if (digitalRead(RELAY_CH3))
                      { 
                           client.print(F("<td><p style=\"font-family:arial;color:black;font-size:20px;\">   saloni   </p><p style=\"font-family:arial;color:green;font-size:25px;\">ON</p></td>"));
                      }
                      else
                      {
                          client.print(F("<td><p style=\"font-family:arial;color:black;font-size:20px;\">   saloni   </p><p style=\"font-family:arial;color:red;font-size:25px;\">OFF</p></td>"));
                      }
                     
                     
                      if (digitalRead(RELAY_CH4))
                      { 
                         client.print(F("<td><p style=\"font-family:arial;color:black;font-size:20px;\">klimatismos</p><p style=\"font-family:arial;color:green;font-size:25px;\">ON</p></td>"));
                      }                      
                     else
                     {
                     client.print(F("<td><p style=\"font-family:arial;color:black;font-size:20px;\">klimatismos</p><p style=\"font-family:arial;color:red;font-size:25px;\">OFF</p></td>"));
                     }
                      if (digitalRead(RELAY_CH5))
                      { 
                           client.print(F("<td><p style=\"font-family:arial;color:black;font-size:20px;\">thermosifonas</p><p style=\"font-family:arial;color:green;font-size:25px;\">ON</p>"));                    
                   
                  }          
                      else
                      {
                          client.print(F("<td><p style=\"font-family:arial;color:black;font-size:20px;\">thermosifonas</p><p style=\"font-family:arial;color:red;font-size:25px;\">OFF</p></td>"));
                      }
                     
                             
                      if (digitalRead(porta1))
                      {   
                           client.print(F("<td><p style=\"font-family:arial;color:black;font-size:20px;\">parking</p><p style=\"font-family:arial;color:green;font-size:25px;\">ON</p></td>"));
                      }
                      else
                      {  
                          client.print(F("<td><p style=\"font-family:arial;color:black;font-size:20px;\">parking</p><p style=\"font-family:arial;color:red;font-size:25px;\">OFF</p></td>"));
                      }
      
                     
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
                    
          //client.println("<meta http-equiv=\"refresh\" content=\"5\">");
          client.println("<title>");
          client.print("Temperature and Humidity");
          client.println("</title>");
          
          // output the value of temperature and humuidity from DHT
          client.println("<center>");
          client.println("<h1>");
          client.println("</h1>");
          client.println("<h2>");
          client.println("</h2>");
          client.println("<h4>");
          client.print("Temperature : ");
          client.print(t);
          client..print("<sup>0</sup>");
          client.print("C");
          client.println("<br />");
          client.print("Humidity : ");
          client.print(h);
          client.print("%");
          client.println("</h4>");
          client.println("</center>");
                           
                 client.println("</tr>");                   
              client.println("</table>"); 
              
          client.println("</center>");
          client.println("<br />");

          
          
         /* Relay Control Code  */                
        
          client.println(F("<a href=\"/?relay1on\"\"><button style='font-size:100%;background-color:darkgray; color:green; border-radius:50px; position:absolute; top:450px; left:145px;'>domatio 1 ON</button></a>"));
          client.println(F("<a href=\"/?relay1off\"\"><button style='font-size:100%;background-color:darkgray; color:red; border-radius:50px; position:absolute; top:450px; left:260px;'>domatio 1 OFF</button></a>"));
          client.println("<br />");
          

          client.println(F("<a href=\"/?relay2on\"\"><button style='font-size:100%;background-color:darkgray; color:green; border-radius:50px; position:absolute; top:500px; left:145px;'>fournos ON</button></a>"));
          client.println(F("<a href=\"/?relay2off\"\"><button style='font-size:100%;background-color:darkgray; color:red; border-radius:50px; position:absolute; top:500px; left:260px;'>fournos OFF</button></a>"));
          client.println("<br />");
          
          
          client.println(F("<a href=\"/?relay3on\"\"> <button style='font-size:100%;background-color:darkgray; color:green; border-radius:50px; position:absolute; top:450px; left:430px;'>saloni ON</button></a>"));
          client.println(F("<a href=\"/?relay3off\"\"><button style='font-size:100%;background-color:darkgray; color:red; border-radius:50px; position:absolute; top:450px; left:550px;'>saloni OFF</button></a>"));
          client.println("<br />");
          

          client..println(F("<a href=\"/?relay4on\"\">  <button style='font-size:100%;background-color:darkgray; color:green; border-radius:50px; position:absolute; top:500px; left:405px;'>klimatismos ON</button></a>"));
          client.println(F("<a href=\"/?relay4off\"\"><button style='font-size:100%;background-color:darkgray; color:red; border-radius:50px; position:absolute; top:500px; left:535px;'>klimatimos OFF</button></a>"));
          client.println("<br />");
         
          
          client.println(F("<a href=\"/?relay5on\"\"><button style='font-size:100%;background-color:darkgray; color:green; border-radius:50px; position:absolute; top:450px; left:645px;'>thermosifinas ON</button></a>"));
          client.println(F("<a href=\"/?relay5off\"\"><button style='font-size:100%;background-color:darkgray; color:red; border-radius:50px; position:absolute; top:450px; left:785px;'>thermosifonas OFF</button></a>"));
          client.println("<br />");        


          client.println(F("<a href=\"/?relay6on\"\"><button style='font-size:100%;background-color:darkgray; color:green; border-radius:50px; position:absolute; top:500px; left:665px;'>porta auto ON</button></a>"));
          client.println(F("<a href=\"/?relay6off\"\"><button style='font-size:100%;background-color:darkgray; color:red; border-radius:50px; position:absolute; top:500px; left:790px;'>porta auto OFF</button></a>"));
          client.println("<br />");
         
      
           
          // control arduino pin via ethernet Start //

        if(readString.indexOf("?relay1on") >0)//checks for on
        {
            digitalWrite(RELAY_CH1, HIGH);    // set pin 4 high
            
            client.println("<br />");
	}
        else{
          if(readString.indexOf("?relay1off") >0)//checks for off
          {
            digitalWrite(RELAY_CH1, LOW);    // set pin 4 low
           
            client.println("<br />");
          }
        }
          
          
         if((readString.indexOf("?relay2on") >0))//checks for on
        {
            digitalWrite(RELAY_CH2, HIGH);    // set pin 4 high
            
            client.println("<br />");
	}
        else{
          if(readString.indexOf("?relay2off") >0)//checks for off
          {
            digitalWrite(RELAY_CH2, LOW);    // set pin 4 low
            
            client.println("<br />");
          }
        }
          
          
          if(readString.indexOf("?relay3on") >0)//checks for on
        {
           digitalWrite (RELAY_CH3, HIGH);    // set pin 4 high
           
            client.println("<br />");
	}
        else{
          if(readString.indexOf("?relay3off") >0)//checks for off
          {
            digitalWrite(RELAY_CH3, LOW);    // set pin 4 low
   

            client.println("<br />");
          }
        }
        
        if(readString.indexOf("?relay4on") >0)//checks for on
        {
            digitalWrite(RELAY_CH4, HIGH);    // set pin 4 high
            
            client.println("<br />");
	}
        else{
          if(readString.indexOf("?relay4off") >0)//checks for off
          {
            digitalWrite(RELAY_CH4, LOW);    // set pin 4 low

            client.println("<br />");
          }
        }
        
         if(readString.indexOf("?relay5on") >0)//checks for on
        {
            digitalWrite(RELAY_CH5, HIGH);    // set pin 4 high
            
            client.println("<br />");
	}
        else{
          if(readString.indexOf("?relay5off") >0)//checks for off
          {
            digitalWrite(RELAY_CH5, LOW);    // set pin 4 low
           
            client.println("<br />");
          }
        }
          
          if(readString.indexOf("?relay6on") >0)//checks for on
          {
            myservo.write(55);
            digitalWrite(porta1, HIGH);    // set pin 5 high

          }
          if(readString.indexOf("?relay6off") >0)//checks for off
          {
            myservo.write(140);
           digitalWrite(porta1, LOW);    // set pin 5 low

          }
              
        client.println("<html>");          
          client.println("<HEAD>");
          client.println("</HEAD>");          
          client.println("<body bgcolor=#3399FF>");       
          client.print("<center> <p> <h1> My System </h1></p> ");
                   
         
           readString="";
           client.println("</body>");         
           client.println("</html>");
         
          break;
        }// if ( c == \n )
        
        
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } 
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
                
      }
    }
    
    // give the web browser time to receive the data   
   // delay(1);
  
     //close the connection:
   client.stop();
    Serial.println("client disonnected");
   
} 
  
  }//if(Client)


