#include "Arduino.h"
#include "../common/dir1/file1.h"
#include "../common/dir2/file2.h"

void setup() {
  Serial.begin(57600);
}


void loop() {
  Serial.print(var1); Serial.print(", ");
  Serial.print(var2); Serial.println();

  while(1) {}
}
