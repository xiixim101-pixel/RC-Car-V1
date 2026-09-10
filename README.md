# RC-Car-V1 - Arduino UNO + L298N

 --> ...0...V1 . Zasilanie z wbudowanego stabilizatora 78M05 na module L298N.

--> Wiring
- LiPo 2S -> Switch ON/OFF -> L298N 7.4V/GND
- L298N 5V (78M05) -> Arduino VIN + Turnigy TGY-iA6

--> VCC
- ENA/ENB zworki założone
- IN1=9 FWD, IN2=6 BWD, IN3=11 LEFT, IN4=10 RIGHT
- RC CH1= D2 (INT0), CH2= D3 (INT1)

--> Kod
- `RC_Car_V1_simple.ino` - prosty 4x PWM, deadband 50us, brak 16-bit timer
- Odczyt RC via CHANGE interrupt, micros()

