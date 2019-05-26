#include <Arduino.h>

#include "devices/digital_input.h"
#include "sensesp_app.h"
#include "transforms/frequency.h"
#include "wiring_helpers.h"

ReactESP app([] () {
  #ifndef SERIAL_DEBUG_DISABLED
  Serial.begin(115200);

  // A small arbitrary delay is required to let the
  // serial port catch up

  delay(100);
  Debug.setSerialEnabled(true);
  #endif

  sensesp_app = new SensESPApp();

  setup_fuel_flow_meter(sensesp_app, D5, D6);

  (new DigitalInputCounter(D7, INPUT_PULLUP, RISING, 500))
      ->connectTo(new Frequency("propulsion.left.revolutions", 1. / 97.,
                                "/sensors/engine_rpm"));

  sensesp_app->enable();
});
