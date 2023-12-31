/* MIT License
 *
 * Copyright (c) 2023 R.F. van Ee
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "pio_counter_pio.h"

PIO pio = pio0;
uint sm = 0;
uint offset;

void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial.println("Programming PIO...");

  // Program RP2040 PIO
  offset = pio_add_program(pio, &counter_program);
  counter_program_init(pio, sm, offset);
}

void loop() {
  // Start timing
  unsigned long micros_t0 = micros();
  uint64_t mycounter_t0 = retrieve_counter(pio, sm, offset);

  Serial.print("Waiting 10s to accumulate counts... ");
  delay(10000);

  // Calculate delta microseconds and delta counts
  unsigned long delta_micros = micros() - micros_t0;
  uint64_t delta_mycounter = retrieve_counter(pio, sm, offset) - mycounter_t0;

  Serial.print(delta_mycounter);
  Serial.print(" counts in ");
  Serial.print(delta_micros);
  Serial.print(" us -> ");
  Serial.print(1000.0 * delta_micros / double(delta_mycounter));
  Serial.println(" ns/count");
}