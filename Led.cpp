
class Led{
    public:
        Led(int pinID):_pinID(pinID){
            pinMode(_pinID, OUTPUT);
            Serial.println("[LED:" + String(_pinID) +"] " + " New Led at pin: " + String(_pinID));
        }

        void toggle(bool isBlink = false){
            _isOn ? off(isBlink) : on(isBlink);
        }

        void on(bool isBlink = false){
            if(!isBlink && _isBlinking){
                _isBlinking = false;
                Serial.println("[LED:" + String(_pinID) +"] " + "Stopped blinking due interruption");
            }
            Serial.println("[LED:" + String(_pinID) +"] " + "On");
            _isOn = true;
            digitalWrite(_pinID, HIGH);
        }

        void off(bool isBlink = false){
            if(!isBlink && _isBlinking){
                _isBlinking = false;
                Serial.println("[LED:" + String(_pinID) +"] " + "Stopped blinking due interruption");
            }
            Serial.println("[LED:" + String(_pinID) +"] " + "Off");
            _isOn = false;
            digitalWrite(_pinID, LOW);
        }

        void blink(){
            Serial.println("[LED:" + String(_pinID) +"] " + (!_isBlinking ? "Starting" : "Stopping") + " blinking");
            _isBlinking = !_isBlinking;
        }

        void blinkAction(){
            if(!_isBlinking) return;

            if(millis() - _lastBlinkTime >= 1000){
                toggle(true);
                _lastBlinkTime = millis();
            }

        }

        int getPinID(){
          return _pinID;
        }

        bool isOn(){
            return _isOn;
        }

        bool isBlinking(){
            return _isBlinking;
        }

    private:
        int _pinID;
        bool _isOn = false;
        bool _isBlinking = false;
        unsigned long _lastBlinkTime = -1;
};
