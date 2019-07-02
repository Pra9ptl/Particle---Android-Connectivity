// This #include statement was automatically added by the Particle IDE.
#include <InternetButton.h>


InternetButton b = InternetButton();

void setup() {
   b.begin();
   
   Particle.function("lights",controlNumberOfLights);
}

void loop() {
    
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
	
	for (int i = 1; i <= noOfLights; i++) {
		b.ledOn(i, 0, 100, 100);
	}
 
    // exit the function
	return 1;
}