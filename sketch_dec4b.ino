#define FORWARD  1
#define BACKWARD 2
#define RELEASE  3

#define TRIG_PIN  12
#define ECHO_PIN  11
#define MAX_DISTANCE 200

class DCMotor {
public:
    DCMotor(uint8_t pinA, uint8_t pinB, uint8_t pinC);
    void run(uint8_t);
    void setSpeed(uint8_t);
private:
    uint8_t motorA, motorB, speedPin;
};

DCMotor::DCMotor(uint8_t pinA, uint8_t pinB, uint8_t pinC) {
    motorA = pinA;
    motorB = pinB;
    speedPin = pinC;
    pinMode(motorA, OUTPUT);
    pinMode(motorB, OUTPUT);
    pinMode(speedPin, OUTPUT);
}

void DCMotor::run(uint8_t key) {
    switch (key) {
    case FORWARD:
        digitalWrite(motorA, HIGH);
        digitalWrite(motorB, LOW);
        break;
    case BACKWARD:
        digitalWrite(motorA, LOW);
        digitalWrite(motorB, HIGH);
        break;
    case RELEASE:
        digitalWrite(motorA, LOW);
        digitalWrite(motorB, LOW);
        break;
    default:
        return;
    }
}

void DCMotor::setSpeed(uint8_t speed) {
    analogWrite(speedPin, speed);
}

DCMotor motor1(7, 6, 5);
DCMotor motor2(9, 8, 3);
int speed = 200;

void setup() {
    Serial.begin(9600);
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);

    motor1.setSpeed(speed);
    motor2.setSpeed(speed);



}

float getDistance() {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    float duration = pulseIn(ECHO_PIN, HIGH);
    return (duration * 0.0343) / 2; // 거리 계산 (cm)
}

void loop() {
    float distance = getDistance();
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    if (distance > 0 && distance <= 10) {
        motor1.run(RELEASE);
        motor2.run(RELEASE);
        delay(500);

        motor1.run(BACKWARD);
        motor2.run(BACKWARD);
        delay(700);

        motor1.run(RELEASE);
        motor2.run(RELEASE);
        delay(500);

        motor1.run(BACKWARD);
        motor2.run(FORWARD);
        delay(700);
    }

    delay(100);
}
