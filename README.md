# Infrared Home Assistant Bridge

This is just a little project I made a while ago for an ESP32 to read infrared codes from a connected IR sensor and then forward them to a Home Assistant event listener via API endpoint.

It's useful if you want a way to control your HA devices with a remote control. All the logic must be done within Home Assistant, this only forwards the IR codes to it.

If you want to try it for yourself, you'll need to make a `private_constants.h` file within `/src`:
```
#ifndef PRIVATE_CONSTANTS_H
#define PRIVATE_CONSTANTS_H

const char* ssid = "YOUR SSID";
const char* password = "YOUR PASSWORD";
const char* serverURL = "HOME ASSISTANT API ENDPOINT";
const char* token = "Bearer (HOME ASSISTANT API TOKEN)";

#endif
```
There are some bugs with it occasionally misrecognizing IR codes. I may try to fix those down the road if I have time.
