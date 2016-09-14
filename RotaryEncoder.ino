/*
The circuit
Encoder Pins A, B (center), C
connect to digital pins Dx and Dy

            A
            |
Gnd - 0.1uF - 10K - VCC
            |
			Dx

      Gnd - C

            B
            |
Gnd - 0.1uF - 10K - VCC
            |
            Dy
*/

// min/max thresholds, can be as big as a int
const int RE_MAX = 10;
const int RE_MIN = -10;

const uint8_t pinA = 8;    // rotary encoder channel A on digital pin 8
const uint8_t pinB = 9;    // rotary encoder channel B on digital pin 9

int val;
int encoderPos = 0;             // return the direction of the endoder, in this case increment or decrement a int
int encoderPinALast = LOW;		// start off with all values low, store the last value of pin A to detect change.
int n = LOW;                    // storage pin A value, pin A will be the key to detect change

void setup()
{
	pinMode(pinA, INPUT);
	pinMode(pinB, INPUT);

	Serial.begin(9600);
}

void loop()
{
	n = digitalRead(pinA);
	if ((encoderPinALast == LOW) && (n == HIGH))    // check if pinA state changed
	{
		if (digitalRead(pinB) == LOW)               // read pinB to determine direction
		{
			// decrement counter
			encoderPos--;
		}
		else
		{
			// increment counter
			encoderPos++;
		}

		/*
		Serial.print(encoderPos);
		Serial.print("/");
		*/

		if (encoderPos > RE_MAX)
		{
			Serial.println("Max");
			encoderPos = 10;
		}
		if (encoderPos < RE_MIN)
		{
			Serial.println("Min");
			encoderPos = -10;
		}

		Serial.println(encoderPos);
	}
	encoderPinALast = n; // store the last position of pin A
}

