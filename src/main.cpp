#include <Arduino.h>

#include "sensors/digital_input.h"
#include "sensesp_app.h"
#include "signalk/signalk_output.h"
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

  setup_fuel_flow_meter(D1, D2);

  (new DigitalInputCounter(D5, INPUT_PULLUP, RISING, 500))
      ->connectTo(new Frequency(1. / 97., "/sensors/engine_rpm/calibration"))
      ->connectTo(new SKOutput<float>("propulsion.main.revolutions", "/sensors/engine_rpm/sk"));

  sensesp_app->enable();
});
