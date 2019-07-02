// This #include statement was automatically added by the Particle IDE.
#include <InternetButton.h>


InternetButton b = InternetButton();

void setup() {
   b.begin();
}

void loop() {
    b.ledOn(3, 28, 219, 109);
    b.ledOn(5, 28, 219, 109);
    b.ledOn(9, 28, 219, 109);
}

int controlNumberOfLights(String command){
	
	// get number of light
    // to convert String --> int
	int noOfLights = atoi(command.c_str());
	
	// validate
	// error 1: negative number
	if(noOfLights < 0) {
		noOfLights = 0;
	}
	// error 2: more than 11
	else if (noOfLights > 11){
		noOfLights = 11;
	}
}