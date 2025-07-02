// Include libraries 
#include <Wire.h> 
#include <Adafruit_GFX.h> 
#include <Adafruit_SSD1306.h> 

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1); 

// Button pins 
const int startButton = 2; 
const int player1Button = 3; 
const int player2Button = 4; 
const int player3Button = 5; 

bool gameStarted = false; 
bool gameEnded = false; 

unsigned long startTime; 
unsigned long reactionTimes[3] = {0, 0, 0}; 
int winner = -1; 

void setup() { 
  Serial.begin(9600); 

  pinMode(startButton, INPUT_PULLUP); 
  pinMode(player1Button, INPUT_PULLUP); 
  pinMode(player2Button, INPUT_PULLUP); 
  pinMode(player3Button, INPUT_PULLUP); 

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println("OLED not found!"); 
    while (true); 
  } 

  display.clearDisplay(); 
  display.setTextSize(1); 
  display.setTextColor(SSD1306_WHITE); 
  display.setCursor(10, 20); 
  display.println("Ready for the game!"); 
  display.setCursor(10, 40); 
  display.println("Press START button"); 
  display.display(); 
} 

void loop() { 
  if (!gameStarted && digitalRead(startButton) == LOW) { 
    waitForRelease(startButton); 
    startCountdown(); 
  } 

  if (gameStarted && !gameEnded) { 
    checkPlayerButtons(); 
  } 

  if (gameEnded && digitalRead(startButton) == LOW) { 
    waitForRelease(startButton); 
    resetGame(); 
  } 
} 

void waitForRelease(int pin) { 
  while (digitalRead(pin) == LOW); 
  delay(50); // Debounce 
} 

void startCountdown() { 
  display.clearDisplay(); 
  display.setTextSize(2); 
  for (int i = 5; i >= 1; i--) { 
    display.clearDisplay(); 
    display.setCursor(55, 25); 
    display.print(i); 
    display.display(); 
    delay(1000); 
  } 
  display.clearDisplay(); 
  display.setCursor(20, 20); 
  display.setTextSize(1); 
  display.println("GO!!! Press your button"); 
  display.display(); 

  gameStarted = true; 
  gameEnded = false; 
  startTime = millis(); 
} 

void checkPlayerButtons() { 
  if (digitalRead(player1Button) == LOW && reactionTimes[0] == 0) { 
    reactionTimes[0] = millis() - startTime; 
    setWinner(1); 
  } 
  if (digitalRead(player2Button) == LOW && reactionTimes[1] == 0) { 
    reactionTimes[1] = millis() - startTime; 
    setWinner(2); 
  } 
  if (digitalRead(player3Button) == LOW && reactionTimes[2] == 0) { 
    reactionTimes[2] = millis() - startTime; 
    setWinner(3); 
  } 
} 

void setWinner(int playerNum) { 
  if (!gameEnded) { 
    winner = playerNum; 
    gameEnded = true; 
    showResult(); 
  } 
} 

void showResult() { 
  display.clearDisplay(); 
  display.setTextSize(1); 
  display.setCursor(10, 0); 
  display.print("Player "); 
  display.print(winner); 
  display.println(" wins!"); 

  for (int i = 0; i < 3; i++) { 
    display.setCursor(10, 15 + i * 15); 
    display.print("P"); 
    display.print(i + 1); 
    display.print(": "); 
    if (reactionTimes[i] > 0) { 
      display.print(reactionTimes[i]); 
      display.println(" ms"); 
    } else { 
      display.println("No press"); 
    } 
  } 
  display.display(); 
} 

void resetGame() { 
  winner = -1; 
  gameStarted = false; 
  gameEnded = false; 
  for (int i = 0; i < 3; i++) { 
    reactionTimes[i] = 0; 
  } 

  display.clearDisplay(); 
  display.setTextSize(1); 
  display.setCursor(10, 20); 
  display.println("Ready for the game!"); 
  display.setCursor(10, 40); 
  display.println("Press START button"); 
  display.display(); 
}
