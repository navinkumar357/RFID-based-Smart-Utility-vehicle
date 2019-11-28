#include <SPI.h>
#include <MFRC522.h>
#include<ArduinoJson.h>
#include<ESP8266WiFi.h>
#include<FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "customer-database-69914.firebaseio.com"
#define FIREBASE_AUTH "rjlfyc2bT1ZAbvTzBUlW4U54PA3xzJdLOkz7XiVZ"
#define WIFI_SSID "Realme 2 Pro"
#define WIFI_PASSWORD "12345678"
#define SS_PIN  4     //D2
#define RST_PIN 5     //D1                      // i variable exclusively for bread, j variable exclusively for biscuits , a for chocolates, b for nuts.
#define buzzer 2
int balance1 , balance2;
int price1 , price2, price3,price4, q1,q2,q3,q4, tot1, tot2, i, j,a , b, ibill ,jbill,abill,bbill, isalesw, jsalesw, asalesw,bsalesw, weeklytot, isalesm, jsalesm, asalesm, bsalesm;
String flag1= "\"No\"" , bill_status= "\"No\"";
String namefire, date;
int iprev,jprev,aprev,bprev;
MFRC522 mfrc522(SS_PIN, RST_PIN); 
void setup() 
{
  Serial.begin(9600);
  SPI.begin();          // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  delay(10);

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) 
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  pinMode(buzzer,OUTPUT);
}



void loop() 
{

  String flag1= Firebase.getString("Customers/Cust 1/Flag");
  Serial.print(flag1);
  String bill_status = Firebase.getString("Customers/Cust 1/Bill status");
  Serial.print(bill_status);
  String namefire = Firebase.getString("Customers/Cust 1/naam");
  Serial.println(namefire);
  String date = Firebase.getString("Customers/Cust 1/Instant"); 
  
  // previous
  if(flag1 == "\"No\"")
  {
    iprev=Firebase.getInt("Customers/" + namefire + "/Current/Bread");
    Firebase.setInt("Customers/" + namefire + "/Previous/Breadp", iprev);
    jprev=Firebase.getInt("Customers/" + namefire + "/Current/Biscuits");
    Firebase.setInt("Customers/" + namefire + "/Previous/Biscuitsp", jprev);
    aprev=Firebase.getInt("Customers/" + namefire + "/Current/Chocolates");
    Firebase.setInt("Customers/" + namefire + "/Previous/Chocolatesp", aprev);
    bprev=Firebase.getInt("Customers/" + namefire + "/Current/Nuts");
    Firebase.setInt("Customers/" + namefire + "/Previous/Nutsp", bprev);
    exit;
  }
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
                                      //Show UID on serial monitor
  Serial.println();
  Serial.print(" UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  Serial.println();
  digitalWrite(buzzer,HIGH);
  delay(500);
  digitalWrite(buzzer,LOW);
  
  
  if(flag1 == "\"Yes\"")
  {
      if (content.substring(1) == "F2 98 07 2E")            //First product
      {
        
        
        price1=50;

        Firebase.setFloat("Customers/" + namefire + "/Purchase log/" + date + "/item/Product 1/Quantity", ++i);
        Firebase.setString("Customers/" + namefire + "/Purchase log/" + date + "/item/Product 1/Product name", "Bread");
        Firebase.setInt("Customers/" + namefire + "/Purchase log/" + date + "/item/Product 1/Price",50 );
        
        int q1 = Firebase.getInt("Customers/" + namefire + "/Purchase log/" + date + "/item/Product 1/Quantity");
        int tot1 = Firebase.getInt("Customers/" + namefire + "/Purchase log/" + date + "/TotalAmt");
        tot1= tot1+price1;
        float balance1 = Firebase.getFloat("Balance/" + namefire);
        balance1=balance1-price1;
        Firebase.setFloat("Balance/" + namefire, balance1);
        Firebase.setFloat("Customers/" + namefire + "/Purchase log/" + date + "/TotalAmt", tot1 );

        Firebase.setString("Bill_status/log", date);
        Firebase.setInt("Bill_status/totamt", tot1);
        Firebase.setString("Bill_status/P1name", "Bread");
        Firebase.setInt("Bill_status/P1price", 50);
        Firebase.setInt("Bill_status/P1quantity", ++ibill); 

        //weekly sales.
        int isalesw= Firebase.getInt("Admin/Sales/Weekly/Bread");
        Firebase.setInt("Admin/Sales/Weekly/Bread", (isalesw+1));
        int weeklytot= Firebase.getInt("Admin/Sales/Weekly/Totalamount");
        Firebase.setInt("Admin/Sales/Weekly/Totalamount", (weeklytot+price1));

        //monthly sales.
        int isalesm= Firebase.getInt("Admin/Sales/Monthly/Total/Bread");
        Firebase.setInt("Admin/Sales/Monthly/Total/Bread", (isalesm+1));
        
        //current
        Firebase.setInt("Customers/" + namefire + "/Current/Bread", ibill);

        delay(2000);
      }
  
      else if (content.substring(1) == "22 FE BF 4B")       //Second product
      {
        
        
        price2=30;
        
        Firebase.setFloat("Customers/" + namefire + "/Purchase log/" + date + "/item/Product 2/Quantity",++j);
        Firebase.setString("Customers/" + namefire + "/Purchase log/" + date + "/item/Product 2/Product name","Biscuits");
        Firebase.setInt("Customers/" + namefire + "/Purchase log/" + date + "/item/Product 2/Price", 30);
        
        q2 = Firebase.getInt("Customers/" + namefire + "/Purchase log/" + date + "/item/Product 2/Quantity");
        tot1 = Firebase.getInt("Customers/" + namefire + "/Purchase log/" + date + "/TotalAmt");
        tot1= tot1+price2;
        float balance1 = Firebase.getFloat("Balance/" + namefire);
        balance1=balance1-price2;
        Firebase.setFloat("Balance/" + namefire, balance1);
        Firebase.setFloat("Customers/" + namefire + "/Purchase log/" + date + "/TotalAmt", tot1 );

        Firebase.setString("Bill_status/log", date);
        Firebase.setInt("Bill_status/totamt", tot1);
        Firebase.setString("Bill_status/P2name", "Biscuits");
        Firebase.setInt("Bill_status/P2price", 30);
        Firebase.setInt("Bill_status/P2quantity", ++jbill);

        //weekly sales
        int jsalesw= Firebase.getInt("Admin/Sales/Weekly/Biscuits");
        Firebase.setInt("Admin/Sales/Weekly/Biscuits", (jsalesw+1));
        int weeklytot= Firebase.getInt("Admin/Sales/Weekly/Totalamount");
        Firebase.setInt("Admin/Sales/Weekly/Totalamount", (weeklytot+price2));

        //monthly sales
        int jsalesm= Firebase.getInt("Admin/Sales/Monthly/Total/Biscuits");
        Firebase.setInt("Admin/Sales/Monthly/Total/Biscuits", (jsalesm+1));

        //current
        Firebase.setInt("Customers/" + namefire + "/Current/Biscuits", jbill);

        delay(2000);
      }


      else if (content.substring(1) == "82 D9 15 4C")       //Third product - Chocolates
      {
        
        
        price3=60;
        
        Firebase.setFloat("Customers/" + namefire + "/Purchase log/" + date + "/item/Product 3/Quantity",++a);
        Firebase.setString("Customers/" + namefire + "/Purchase log/" + date + "/item/Product 3/Product name","Chocolates");
        Firebase.setInt("Customers/" + namefire + "/Purchase log/" + date + "/item/Product 3/Price", 60);
        
        q3 = Firebase.getInt("Customers/" + namefire + "/Purchase log/" + date + "/item/Product 3/Quantity");
        tot1 = Firebase.getInt("Customers/" + namefire + "/Purchase log/" + date + "/TotalAmt");
        tot1= tot1+price3;
        float balance1 = Firebase.getFloat("Balance/" + namefire);
        balance1=balance1-price3;
        Firebase.setFloat("Balance/" + namefire, balance1);
        Firebase.setFloat("Customers/" + namefire + "/Purchase log/" + date + "/TotalAmt", tot1 );

        Firebase.setString("Bill_status/log", date);
        Firebase.setInt("Bill_status/totamt", tot1);
        Firebase.setString("Bill_status/P3name", "Chocolates");
        Firebase.setInt("Bill_status/P3price", 60);
        Firebase.setInt("Bill_status/P3quantity", ++abill);

        //weekly sales
        int asalesw= Firebase.getInt("Admin/Sales/Weekly/Chocolates");
        Firebase.setInt("Admin/Sales/Weekly/Chocolates", (asalesw+1));
        int weeklytot= Firebase.getInt("Admin/Sales/Weekly/Totalamount");
        Firebase.setInt("Admin/Sales/Weekly/Totalamount", (weeklytot+price3));

        //monthly sales
        int asalesm= Firebase.getInt("Admin/Sales/Monthly/Total/Chocloates");
        Firebase.setInt("Admin/Sales/Monthly/Total/Chocolates", (asalesm+1));

        //current
        Firebase.setInt("Customers/" + namefire + "/Current/Chocolates", abill);

        delay(2000);
     }

     else if (content.substring(1) == "C2 BC 12 4C")       //Fourth product - nuts
      {
        
        
        price4=150;
        
        Firebase.setFloat("Customers/" + namefire + "/Purchase log/" + date + "/item/Product 4/Quantity",++b);
        Firebase.setString("Customers/" + namefire + "/Purchase log/" + date + "/item/Product 4/Product name","Nuts");
        Firebase.setInt("Customers/" + namefire + "/Purchase log/" + date + "/item/Product 4/Price", 150);
        
        q4 = Firebase.getInt("Customers/" + namefire + "/Purchase log/" + date + "/item/Product 4/Quantity");
        tot1 = Firebase.getInt("Customers/" + namefire + "/Purchase log/" + date + "/TotalAmt");
        tot1= tot1+price4;
        float balance1 = Firebase.getFloat("Balance/" + namefire);
        balance1=balance1-price4;
        Firebase.setFloat("Balance/" + namefire, balance1);
        Firebase.setFloat("Customers/" + namefire + "/Purchase log/" + date + "/TotalAmt", tot1 );

        Firebase.setString("Bill_status/log", date);
        Firebase.setInt("Bill_status/totamt", tot1);
        Firebase.setString("Bill_status/P4name", "Nuts");
        Firebase.setInt("Bill_status/P4price", 150);
        Firebase.setInt("Bill_status/P4quantity", ++bbill);

        //weekly sales
        int bsalesw= Firebase.getInt("Admin/Sales/Weekly/Nuts");
        Firebase.setInt("Admin/Sales/Weekly/Nuts", (bsalesw+1));
        int weeklytot= Firebase.getInt("Admin/Sales/Weekly/Totalamount");
        Firebase.setInt("Admin/Sales/Weekly/Totalamount", (weeklytot+price4));

        //monthly sales
        int bsalesm= Firebase.getInt("Admin/Sales/Monthly/Total/Nuts");
        Firebase.setInt("Admin/Sales/Monthly/Total/Nuts", (bsalesm+1));

        //current
        Firebase.setInt("Customers/" + namefire + "/Current/Nuts", bbill);

        delay(2000);
     }
  }
 
  
}
  

