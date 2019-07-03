// This #include statement was automatically added by the Particle IDE.
#include <InternetButton.h>

// This #include statement was automatically added by the Particle IDE.
#include <InternetButton.h>

#include "InternetButton.h"
#include "math.h"


InternetButton b = InternetButton();


// Global variables to store how many lights should be turned on
int numLights = 6;
bool numLightsChanged = false;
int rValue = 0;
int gValue = 0;
int bValue = 0;
bool lightsColorChanged = false;



void setup() {

    // 1. Setup the Internet Button
    b.begin();

    // 2. Setup the API endpoint -- 
    // When person visits http://particle.io/..../lights, run the controlNumLights() function
    Particle.function("lights", controlNumLights);
    // 3. Setup the initial state of the LEDS
    // (by default, turn on 6 lights)
    activateLEDS();
    
    
    
    Particle.function("colors", controlColor);
    activateLEDSColor();

}

void loop(){
    
    // This loop just sits here and waits for the numLightsChanged variable to change to true
    // Once it changes to true, run the activateLEDS() function.
    if(numLightsChanged == true){
        delay(10);
        activateLEDS();
        numLightsChanged = false;
    }
    
    if(lightsColorChanged == true){
        delay(10);
        activateLEDSColor();
        lightsColorChanged = false;
    }
}

// Turn on your LEDS
void activateLEDS(){

    // 1. turn off all lights
    b.allLedsOff();
    
    // 2. Turn on a certain number of lights
    // howManyLights = the number of lights you want to turn on
    for(int i = 1; i <= numLights; i++) {
        //  3. Make each led BLUE
        //  Blue = (r, g, b) = (0, 0, 255)
        b.ledOn(i, 255, 255, 255);
    }
}


// Turn on your LEDS
void activateLEDSColor(){

    // 1. turn off all lights
    b.allLedsOff();
    
    // 2. Turn on a certain number of lights
    // howManyLights = the number of lights you want to turn on
    b.allLedsOn(rValue,gValue,bValue);
}

/*
controlNumLights() is the local function that is executed when the API function "lights" is called.
It changes how many LEDs on the Button are illuminated.
*/
int controlNumLights(String command){
    //parse the string into an integer
    int howManyLights = atoi(command.c_str());

    // Error Checking #1: Check that the number of lights < 11
    // Remember - the device only has 11 lights on it
    
    // Check that the value it's been given is in the right range
    if (howManyLights > 11) {
        howManyLights = 11;
    }
    
    // Error Checking #2: Deal with negative inputs
    if (howManyLights < 0) {
        howManyLights = 0;
    }
    
    
    // If no errors, then set the global variable to numLights
    numLights = howManyLights;

    numLightsChanged = true;

    // In embedded programming, "return 1" means that 
    // the function finished successfully
    return 1;
}


int controlColor(String command){
    
    int commaIndex = command.indexOf(",");
    
    String r = command.substring(0, commaIndex);
    Particle.publish("red", r);
    String r_str = command.substring(commaIndex+1);
    int remaining = r_str.indexOf(",");
    String g = r_str.substring(0, remaining);
    Particle.publish("green", g);
    String b = r_str.substring(remaining+1);
    Particle.publish("blue", b);
    rValue = atoi(r.c_str());
    gValue = atoi(g.c_str());
    bValue = atoi(b.c_str());
    

    
    lightsColorChanged = true;
    
    return 1;
}

