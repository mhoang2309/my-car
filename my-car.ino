/*************************************************************
  Blynk is a platform with iOS and Android apps to control
  ESP32, Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build mobile and web interfaces for any
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: https://www.blynk.io
    Sketch generator:           https://examples.blynk.cc
    Blynk community:            https://community.blynk.cc
    Follow us:                  https://www.fb.com/blynkapp
                                https://twitter.com/blynk_app

  Blynk library is licensed under MIT license
 *************************************************************
  Blynk.Edgent implements:
  - Blynk.Inject - Dynamic WiFi credentials provisioning
  - Blynk.Air    - Over The Air firmware updates
  - Device state indication using a physical LED
  - Credentials reset using a physical Button
 *************************************************************/

/* Fill in information from your Blynk Template here */
/* Read more: https://bit.ly/BlynkInject */
#define BLYNK_TEMPLATE_ID "TMPL6u77HTzjN"
#define BLYNK_TEMPLATE_NAME "demo"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial
#define BLYNK_DEBUG

#define APP_DEBUG

// Uncomment your board, or configure a custom board in Settings.h
//#define USE_SPARKFUN_BLYNK_BOARD
//#define USE_NODE_MCU_BOARD
//#define USE_WITTY_CLOUD_BOARD
//#define USE_WEMOS_D1_MINI

#include "BlynkEdgent.h"

#define Relay 12

int SW[][2] = {{34, 35}, {32, 33}, {25, 26}, {27, 14}};
int IN[][2] = {{22, 21}, {19, 18}, {5, 17}, {16, 4}};

#define SW_SIZE sizeof(SW) / sizeof(SW[0])
#define IN_SIZE sizeof(IN) / sizeof(IN[0])

class CarGlass {
private:
    int RPWM;
    int LPWM;
    int doorNumber;
    int timedelay;

public:
    CarGlass() {} // Hàm tạo mặc định

    CarGlass(int RPWM, int LPWM, int doorNumber, int timedelay);

    ~CarGlass();

    int getRPWM() const;
    void setRPWM(int value);
    int getLPWM() const;
    void setLPWM(int value);
    int getdoorNumber() const;
    void setdoorNumber(int value);
    int gettimedelay() const;
    void settimedelay(int value);
    void upGlass();
    void downGlass();
    void stopGlass(int locate = 0);
    void control(int valueIn);
};

CarGlass::CarGlass(int RPWM, int LPWM, int doorNumber, int timedelay) {
    this->RPWM = RPWM;
    this->LPWM = LPWM;
    this->doorNumber = doorNumber;
    this->timedelay = timedelay;
    pinMode(RPWM, OUTPUT);
    pinMode(LPWM, OUTPUT);
    stopGlass();
}

CarGlass::~CarGlass() {
    // Destructor code (if needed)
}

int CarGlass::getRPWM() const {
    return RPWM;
}
void CarGlass::setRPWM(int value) {
    RPWM = value;
}
int CarGlass::getLPWM() const {
    return LPWM;
}
void CarGlass::setLPWM(int value) {
    LPWM = value;
}
int CarGlass::getdoorNumber() const {
    return doorNumber;
}
void CarGlass::setdoorNumber(int value) {
    doorNumber = value;
}
int CarGlass::gettimedelay() const {
    return timedelay;
}
void CarGlass::settimedelay(int value) {
    timedelay = value;
}
void CarGlass::upGlass() {
    if (digitalRead(RPWM) == digitalRead(LPWM)){
        digitalWrite(RPWM, HIGH);
        digitalWrite(LPWM, LOW);
        String message = "Up Glass " + String(doorNumber);
        Serial.println(message);
        delay(timedelay);
    }
}
void CarGlass::downGlass() {
    if (digitalRead(RPWM) == digitalRead(LPWM)){
        digitalWrite(RPWM, LOW);
        digitalWrite(LPWM, HIGH);
        String message = "Down Glass " + String(doorNumber);
        Serial.println(message);
        delay(timedelay);
    }
}
void CarGlass::stopGlass(int locate) {
    if (!locate){
        digitalWrite(RPWM, LOW);
        digitalWrite(LPWM, LOW);
        String message = "Stop Glass " + String(doorNumber);
        Serial.println(message);
    }
    else if (digitalRead(RPWM) == HIGH || digitalRead(LPWM) == LOW)
    {
       if (locate==1){
            digitalWrite(RPWM, LOW);
            digitalWrite(LPWM, LOW);
            String message = "Stop Glass " + String(doorNumber);
            Serial.println(message);
       }
    }
    else if (digitalRead(RPWM) == LOW || digitalRead(LPWM) == HIGH)
    {
       if (locate==2){
            digitalWrite(RPWM, LOW);
            digitalWrite(LPWM, LOW);
            String message = "Stop Glass " + String(doorNumber);
            Serial.println(message);
       }
    }
}
void CarGlass::control(int valueIn) {
    if (valueIn == 1)
        upGlass();
    else if (valueIn == 0)
        downGlass();
    else
        stopGlass();
}

struct SwitchStatus {
    bool top;
    bool bot;
};

class PositionSwitch {
private:
    int topSwitch;
    int botSwitch;
    int doorNumber;
    int timedelay;

public:
    PositionSwitch() {} // Hàm tạo mặc định

    PositionSwitch(int topSwitch, int botSwitch, int doorNumber, int timedelay);

    ~PositionSwitch();

    int gettopSwitch() const;
    void settopSwitch(int value);
    int getbotSwitch() const;
    void setbotSwitch(int value);
    int getdoorNumber() const;
    void setdoorNumber(int value);
    int gettimedelay() const;
    void settimedelay(int value);
    SwitchStatus read_status();
};

PositionSwitch::PositionSwitch(int topSwitch, int botSwitch, int doorNumber, int timedelay) {
    this->topSwitch = topSwitch;
    this->botSwitch = botSwitch;
    this->doorNumber = doorNumber;
    this->timedelay = timedelay;
    pinMode(topSwitch, INPUT);
    pinMode(botSwitch, INPUT);
}

PositionSwitch::~PositionSwitch() {
    // Destructor code (if needed)
}

int PositionSwitch::gettopSwitch() const {
    return topSwitch;
}
void PositionSwitch::settopSwitch(int value) {
    topSwitch = value;
}
int PositionSwitch::getbotSwitch() const {
    return botSwitch;
}
void PositionSwitch::setbotSwitch(int value) {
    botSwitch = value;
}
int PositionSwitch::getdoorNumber() const {
    return doorNumber;
}
void PositionSwitch::setdoorNumber(int value) {
    doorNumber = value;
}
int PositionSwitch::gettimedelay() const {
    return timedelay;
}
void PositionSwitch::settimedelay(int value) {
    timedelay = value;
}
SwitchStatus PositionSwitch::read_status() {
    SwitchStatus status;
    status.top = digitalRead(topSwitch);
    status.bot = digitalRead(botSwitch);
    return status;
}

CarGlass glasses[IN_SIZE];
PositionSwitch positionSwitch[SW_SIZE];

int door[] = {0, 0, 0, 0};
int autoMode = 0; // Renamed auto to autoMode
int SWtimedelay = 100;
int INtimedelay = 100;

BLYNK_WRITE(V0) {
    int pinDoor = param.asInt();
    door[0] = pinDoor;
    glasses[0].control(2);
}
BLYNK_WRITE(V1) {
    int pinDoor = param.asInt();
    door[1] = pinDoor;
    glasses[1].control(2);
}
BLYNK_WRITE(V2) {
    int pinDoor = param.asInt();
    door[2] = pinDoor;
    glasses[2].control(2);
}
BLYNK_WRITE(V3) {
    int pinDoor = param.asInt();
    door[3] = pinDoor;
    glasses[3].control(2);
}

BLYNK_WRITE(V4) {
    int pinGlass = param.asInt();
    if (pinGlass) {
        for (int i = 0; i < IN_SIZE; i++)
            if (door[i] == 1) {
                SwitchStatus status = positionSwitch[i].read_status();
                if (!status.top){
                    glasses[i].control(1);
                }
            }
            
    } else if (!autoMode) {
        for (int i = 0; i < IN_SIZE; i++)
            if (door[i]) {
                glasses[i].control(2);
            }
    }
}

BLYNK_WRITE(V5) {
    int pinGlass = param.asInt();
    if (pinGlass) {
        for (int i = 0; i < IN_SIZE; i++)
            if (door[i] == 1) {
                SwitchStatus status = positionSwitch[i].read_status();
                if (!status.bot){
                    glasses[i].control(0);
                }
            }
             
    } else if (!autoMode) {
        for (int i = 0; i < IN_SIZE; i++)
            if (door[i]) {
                glasses[i].control(2);
            }
    }
}

BLYNK_WRITE(V6) {
    int pinGlass = param.asInt();
    if (pinGlass) {
        for (int i = 0; i < IN_SIZE; i++)
            if (door[i] == 1) {
                glasses[i].control(2);
            }
            
    }
}

BLYNK_WRITE(V7) {
    autoMode = param.asInt(); // Renamed auto to autoMode
    if (!autoMode) {
        for (int i = 0; i < IN_SIZE; i++)
            if (door[i] == 1) {
                glasses[i].control(2);
            }
    }
    
}

void setup()
{
    Serial.begin(115200);
    delay(100);

    BlynkEdgent.begin();
    for (int i = 0; i < SW_SIZE; i++)
          positionSwitch[i] = PositionSwitch(SW[i][0], SW[i][1], i + 1, SWtimedelay);
  
    for (int i = 0; i < IN_SIZE; i++)
          glasses[i] = CarGlass(IN[i][0], IN[i][1], i + 1, INtimedelay);
    Blynk.virtualWrite(V0, 0);
    Blynk.virtualWrite(V1, 0);
    Blynk.virtualWrite(V2, 0);
    Blynk.virtualWrite(V3, 0);
    Blynk.virtualWrite(V4, 0);
    Blynk.virtualWrite(V5, 0);
    Blynk.virtualWrite(V6, 0);
    Blynk.virtualWrite(V7, 0);
}

void loop() {
  BlynkEdgent.run();
  for (int i = 0; i < SW_SIZE; i++){
    SwitchStatus status = positionSwitch[i].read_status();
        if (status.top){
            glasses[i].stopGlass(1);
        }
        else if (status.bot){
            glasses[i].stopGlass(2);
        }
  }  
}
