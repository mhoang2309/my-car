#include <Arduino.h>

#define BLYNK_TEMPLATE_ID "TMPL6u77HTzjN"
#define BLYNK_TEMPLATE_NAME "demo"
//#define BLYNK_AUTH_TOKEN "5Z6qhQxkG5hQCrRyjo5roBux0ZKdc40U"

#define BLYNK_FIRMWARE_VERSION "0.1.0"
#define BLYNK_PRINT Serial

#include "BlynkEdgent.h"

#define Relay 12

int SW[] = {34, 35, 32, 33, 25, 26, 27, 14};
#define SW_SIZE sizeof(SW) / sizeof(SW[0])
int IN[] = {22, 21, 19, 18, 5, 17, 16, 4};
#define IN_SIZE sizeof(SW) / sizeof(SW[0])

class CarGlass
{
private:
    int RPWM;
    int LPWM;
    int doorNumber;
    int timedelay;

public:
    CarGlass() {} // Hàm tạo mặc định

    CarGlass(int RPWM, int LPWM, int doorNumber);

    ~CarGlass();

    int getRPWM() const;
    void setRPWM(int value);
    int getLPWM() const;
    void setLPWM(int value);
    int getdoorNumber() const;
    void setdoorNumber(int value);
    int gettimedelay() const;
    void settimedelay(int value);
    void init();
    void upGlass();
    void downGlass();
    void stopGlass();
    // Other member functions (if needed)
};

CarGlass::CarGlass(int RPWM, int LPWM, int doorNumber)
{
    this->RPWM = RPWM;
    this->LPWM = LPWM;
    this->doorNumber = doorNumber;
}

CarGlass::~CarGlass()
{
    // Destructor code (if needed)
}

int CarGlass::getRPWM() const
{
    return RPWM;
}
void CarGlass::setRPWM(int value)
{
    RPWM = value;
}
int CarGlass::getLPWM() const
{
    return LPWM;
}
void CarGlass::setLPWM(int value)
{
    LPWM = value;
}
int CarGlass::getdoorNumber() const
{
    return doorNumber;
}
void CarGlass::setdoorNumber(int value)
{
    doorNumber = value;
}
int CarGlass::gettimedelay() const
{
    return timedelay;
}
void CarGlass::settimedelay(int value)
{
    timedelay = value;
}
void CarGlass::init()
{
    pinMode(RPWM, OUTPUT);
    pinMode(LPWM, OUTPUT);
    stopGlass();
}
void CarGlass::upGlass()
{
    digitalWrite(RPWM, HIGH);
    digitalWrite(LPWM, LOW);
    String message = "Up Glass " + String(doorNumber);
    Serial.println(message);
    delay(timedelay);
}
void CarGlass::downGlass()
{
    digitalWrite(RPWM, LOW);
    digitalWrite(LPWM, HIGH);
    String message = "Down Glass " + String(doorNumber);
    Serial.println(message);
    delay(timedelay);
}
void CarGlass::stopGlass()
{
    digitalWrite(RPWM, LOW);
    digitalWrite(LPWM, LOW);
    String message = "Stop Glass " + String(doorNumber);
    Serial.println(message);
}

CarGlass glasses[IN_SIZE];

void setup()
{
    Serial.begin(9600);
    delay(100);
    for (int i = 0; i < SW_SIZE; i++)
        pinMode(SW[i], INPUT);
    for (int i = 0; i < IN_SIZE; i++)
        glasses[i].init();
    BlynkEdgent.run();
}

void loop()
{
    BlynkEdgent.run();
}
