/*
 * USB.cpp - Creates an 8 LED WS2812 strip for use with PixelMaestro Studio.
 *    1) Attach your strip to pin 10 on the Arduino (or change LED_PIN).
 *    2) Connect your Arduino to your computer via USB.
 *    3) Run PixelMaestro Studio and select the Device tab.
 *    4) Select "Live updates" to update your device in real-time, or click "Upload Cuefile" to upload the configuration to your Arduino.
 *    5) Have fun!
 */

#include <Arduino.h>
#include <EEPROM.h>
#include <PixelMaestro/core/maestro.h>
#include <WS2812.h>

using namespace PixelMaestro;

// Declare variables for tracking EEPROM and header reads
uint8_t header[6];
uint8_t header_index = 0;
uint16_t eeprom_index = 0;
bool eeprom_read = false;

// Create a Maestro with a single 8x1 Section
Maestro maestro(8, 1);

// Initialize WS2812 components
const uint8_t LED_PIN = 10;
WS2812 ws = WS2812(maestro.get_section(0)->get_dimensions()->x);

// Run the Cuefile stored in EEPROM
void run_eeprom_cue() {
  uint8_t cuefile_size[] = {EEPROM[0], EEPROM[1]};
  uint16_t size = IntByteConvert::byte_to_int(cuefile_size);
  for (uint16_t index = 2; index < size; index++) {
    maestro.get_cue_controller()->read(EEPROM[index]);
  }
}

void setup () {
    ws.setOutput(LED_PIN);

		// Set the global brightness to 10%
		maestro.set_brightness(25);

		/*
		 * Initialize the CueController and CueHandlers.
		 * To reduce the sketch size, disable any unused CueHandlers.
		 */
		CueController* controller = maestro.set_cue_controller();
    controller->enable_animation_cue_handler();
    controller->enable_canvas_cue_handler();
    controller->enable_maestro_cue_handler();
    controller->enable_section_cue_handler();
    controller->enable_show_cue_handler();

    // If we have Cue data stored in EEPROM, read it in.
    if (EEPROM.read(2) == 'P' && EEPROM.read(3) == 'M' && EEPROM.read(4) == 'C') {
      run_eeprom_cue();
    }

		Serial.begin(9600);
}

void loop() {
		// Listen for incoming Cues
		if (Serial.available()) {
      uint8_t in = Serial.read();

      // Read in the current byte to the CueController
      maestro.get_cue_controller()->read(in);

      // If the current byte might indicate an EEPROM start/stop command, reset the header read index
      if (in == 'R') {
        header_index = 0;
      }
      header[header_index] = in;
      header_index++;

      // If we're in EEPROM read mode, write the current byte to EEPROM.
      if (eeprom_read) {
        EEPROM.write(eeprom_index, in);
        eeprom_index++;
      }

      // If we read in the EEPROM start header, write the following serial data to EEPROM (set EEPROM read mode to true)
      if (header[0] == 'R' && header[1] == 'O' && header[2] == 'M' && header[3] == 'B' && header[4] == 'E' && header[5] == 'G') {
        eeprom_read = true;
      }
      // If we read in the EEPROM end header, stop writing to EEPROM and reset the eeprom read index
      else if (header[0] == 'R' && header[1] == 'O' && header[2] == 'M' && header[3] == 'E' && header[4] == 'N' && header[5] == 'D') {
        eeprom_read = false;
        eeprom_index = 0;
      }

      // Reset the EEPROM index
      if (eeprom_index >= EEPROM.length()) {
        eeprom_index = 0;
        eeprom_read = false;
      }
      // Reset the header index.
      if (header_index >= 6) {
        header_index = 0;
      }
		}

    // Update the Maestro
    if (maestro.update(millis())) {
  		// Copy each Pixel's color to the WS2812 strip
			for (unsigned char x = 0; x < maestro.get_section(0)->get_dimensions()->x; x++) {
				Colors::RGB color = maestro.get_pixel_color(0, x, 0);
				ws.set_crgb_at(x, color.r, color.g, color.b);
			}

      ws.sync();
    }
}