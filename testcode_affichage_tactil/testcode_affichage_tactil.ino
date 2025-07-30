#include <TFT_eSPI.h>              // Include TFT library (for display)
#include <XPT2046_Touchscreen.h>    // Include touch library

// Define the pin connections for the touch controller (SPI)
#define T_CS    5  // Chip Select for touch controller
#define T_IRQ   34  // Interrupt for detecting touch input
#define T_CLK   18  // Clock signal for SPI (SCK)
#define T_DIN   23  // Data input (MOSI)
#define T_DOUT  19  // Data output (MISO)


// Button coordinates and dimensions
#define BUTTON_WIDTH  100
#define BUTTON_HEIGHT  50
#define BUTTON_ON_X  60    // X position of the "On" button
#define BUTTON_ON_Y  100   // Y position of the "On" button
#define BUTTON_OFF_X  180  // X position of the "Off" button
#define BUTTON_OFF_Y  100  // Y position of the "Off" button

// Initialize the TFT and touchscreen objects
TFT_eSPI tft = TFT_eSPI();         // Create TFT instance
XPT2046_Touchscreen ts(T_CS, T_IRQ);  // Create instance of the touch screen object

// Function to draw the buttons
void drawButtons() {
  // Draw "On" button
  tft.fillRect(BUTTON_ON_X, BUTTON_ON_Y, BUTTON_WIDTH, BUTTON_HEIGHT, TFT_GREEN);
  tft.setTextColor(TFT_WHITE);
  tft.drawString("ON", BUTTON_ON_X + 30, BUTTON_ON_Y + 15, 2); // Centered "ON" text
  
  // Draw "Off" button
  tft.fillRect(BUTTON_OFF_X, BUTTON_OFF_Y, BUTTON_WIDTH, BUTTON_HEIGHT, TFT_RED);
  tft.setTextColor(TFT_WHITE);
  tft.drawString("OFF", BUTTON_OFF_X + 30, BUTTON_OFF_Y + 15, 2); // Centered "OFF" text
}

// Function to detect if a touch is within a button
bool isTouchedInButton(int touchX, int touchY, int buttonX, int buttonY) {
  return (touchX > buttonX && touchX < buttonX + BUTTON_WIDTH && touchY > buttonY && touchY < buttonY + BUTTON_HEIGHT);
}

void setup() {
  // Start serial communication for debugging
  Serial.begin(115200);
  // Initialize the display
  tft.init();
  tft.setRotation(1);  // Set screen rotation (adjust if necessary)
  tft.fillScreen(TFT_BLACK);

  // Initialize the touch screen SPI interface
  ts.begin();                // Initialize the touch controller
  ts.setRotation(1);         // Set touch screen rotation to match display
  
  // Print a message to indicate the touch screen is initialized
  Serial.println("Touch screen initialized!");

  // Draw buttons on the screen
  drawButtons();
}

void loop() {
  // Check if the screen is touched
  if (ts.touched()) {
    TS_Point p = ts.getPoint();  // Get the coordinates of the touch point
    
    if (p.z > 0) {  // Ensure valid touch
      int touchX = p.x;
      int touchY = p.y;
       Serial.print("X = ");
      Serial.print(p.x);
      Serial.print(", Y = ");
      Serial.println(p.y);
      
      // Map touch coordinates to match display orientation
      touchX = map(p.x, 0, 4095, 0, tft.width());  // Map X from 0-4095 to 0-240 (screen width)
      touchY = map(p.y, 0, 4095, 0, tft.height()); // Map Y from 0-4095 to 0-320 (screen height)

      // Check if "On" button is pressed
      if (isTouchedInButton(touchX, touchY, BUTTON_ON_X, BUTTON_ON_Y)) {
        Serial.println("ON button pressed!");
        
        // Clear the screen and display "Bonjour"
        tft.fillScreen(TFT_BLACK);
        tft.setTextColor(TFT_WHITE);
        tft.drawString("bonjour", 120, 60, 4);  // Display "Bonjour"
        
        // Redraw buttons after displaying text
        drawButtons();
      }
      
      // Check if "Off" button is pressed
      else if (isTouchedInButton(touchX, touchY, BUTTON_OFF_X, BUTTON_OFF_Y)) {
        Serial.println("OFF button pressed!");
        
        // Clear the screen and display "Bonsoir"
        tft.fillScreen(TFT_BLACK);
        tft.setTextColor(TFT_WHITE);
        tft.drawString("Bonsoir ", 120, 60, 4);  // Display "Bonsoir"
        
        // Redraw buttons after displaying text
        drawButtons();
      }
    }
  }
  delay(100);
}
