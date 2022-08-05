
//@author:Batuhan Kucukyildiz

#include <Arduino.h>
TaskHandle_t Task1;
TaskHandle_t Task2;

const int redred = 2;
const int ledgreen = 4;
void Task1kodu( void * pvParameters ){
  Serial.print("Task1'in Çalıştığı Çekirdek: ");
  Serial.println(xPortGetCoreID());

  for(;;){ //sonsuz döner
    digitalWrite(redred, HIGH);
    delay(2000);
    digitalWrite(redred, LOW);
    delay(500);
    Serial.println("ok");


  } 
}

//Task2kodu: Yeşil ledi 300 ms'de bir yakıp söndüreceğiz
void Task2kodu( void * pvParameters ){
  Serial.print("Task2'nin Çalıştığı Çekirdek: ");
  Serial.println(xPortGetCoreID());

  for(;;){ //sonsuz döner
    digitalWrite(ledgreen, HIGH);
    delay(300);
    digitalWrite(ledgreen, LOW);
    delay(300);
        Serial.println("no");

  }
}
void setup() {
  Serial.begin(9600); 
  pinMode(redred, OUTPUT);
  pinMode(ledgreen, OUTPUT);

  //Task1kodu() fonksiyonunun çalışacağı görev bloğunu öncelik 1 olarak işlemci 0'da çalışacak şekilde ayarlıyoruz
  xTaskCreatePinnedToCore(
                    Task1kodu,   /* Görevin çalışacağı fonksiyon. */
                    "Task1",     /* Görevin adı. */
                    10000,       /* Görev stack boyutu */
                    NULL,        /* ilave parametreler */
                    1,           /* Görevin önceliği */
                    &Task1,      /* Görevin işaretçisi */
                    1);          /* Görevi 1 numaralı çekirdeğe atayalım */                  
  delay(500); 

  //Task2kodu() fonksiyonunun çalışacağı görev bloğunu öncelik 1 olarak işlemci 1'de çalışacak şekilde ayarlıyoruz
  xTaskCreatePinnedToCore(
                    Task2kodu,   /* Görevin çalışacağı fonksiyon. */
                    "Task2",     /* Görevin adı. */
                    10000,       /* Görev stack boyutu */
                    NULL,        /* ilave parametreler */
                    1,           /* Görevin önceliği */
                    &Task2,      /* Görevin işaretçisi */
                    1);          /* Görevi 1 numaralı çekirdeğe atayalım */
    delay(500); 
}



void loop() {
  
}