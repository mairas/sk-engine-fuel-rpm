#include <Arduino.h>

#include "sensors/digital_input.h"
#include "sensesp_app.h"
#include "sensesp_app_builder.h"
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

  auto builder = SensESPAppBuilder();

  setup_fuel_flow_meter(D1, D2);
  sensesp_app = builder
    .set_wifi("Sample SSID", "wifi_passphrase")
    ->set_sk_server("sk-server.local", 80)
    ->set_hostname("engine-rpm")
    ->set_standard_sensors(ALL)
    ->get_app();

  (new DigitalInputCounter(D5, INPUT_PULLUP, RISING, 500))
      ->connectTo(new Frequency(1. / 97., "/sensors/engine_rpm/calibration"))
      ->connectTo(new SKOutput<float>("propulsion.main.revolutions", "/sensors/engine_rpm/sk"));

  sensesp_app->enable();
});
