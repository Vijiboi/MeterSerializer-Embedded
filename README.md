MeterSerializer - Embedded JSON Library

![Platform](https://img.shields.io/badge/platform-Arduino-blue)
![Language](https://img.shields.io/badge/language-C%2F%2C%2B%2B-orange)
![License](https://img.shields.io/badge/license-MIT-green)

1. Project Overview
This is a custom C library I wrote to serialize w-M-Bus meter data into a specific JSON format.

The main goal of this project was to solve a real world firmware task of taking raw data structs and turning them into a strict JSON string without relying on pre existing libraries.

No external libraries: I didn't use ArduinoJson or cJSON. I wrote the string formatting logic myself.
Memory safety: I avoided using malloc or free. Everything works with fixed buffers to keep the memory usage predictable.
Hardware independent: Even though I tested this on Arduino, the core logic is just standard C, so it can be easily moved to other platforms.

2. Platform & Justification
Chosen Platform: Arduino Framework
IDE: Arduino IDE

Why I chose this: I decided to use the Arduino framework and IDE for two main reasons:

a) Focus on the Code: I am already very comfortable with the Arduino environment. Using a tool I know well allowed me to focus completely on the main crux of the assignment (the serialization logic and pointer arithmetic). 
b) Rapid Verification: The Arduino Serial Monitor gave me a quick way to test and visually verify the JSON output instantly. Since the assignment permits the Arduino framework as an alternative, this felt like the most efficient path to a working and bug free solution.

3. Project Structure
I organized the code in the following structure
/MeterReader_Assignment ->
           ─ MeterReader_Assignment.ino   # The demo app that creates dummy data and runs the test
           ─ MeterSerializer.h            # My header file (Struct definitions & API)
           ─ MeterSerializer.cpp          # The actual code that does the JSON formatting
           ─ README.md                    # Documentation
                       
5. How to Run It
Requirements
Any standard Arduino board (Uno, Mega, ESP32, etc.)

Arduino IDE

Steps
Open NinetiGmbh_Internship_Assignment_VijayeshDey.ino

Make sure the .h and .cpp files are in the same folder.

Upload the code to your board.

Open the Serial Monitor and set the baud rate to 115200.

You will see the generated JSON string appear.

5. Library Usage
The API is designed to be simple. We verify if we have enough buffer space, and then pass the data in.


int serialize_meter_data(const GatewayMeta* meta, 
                         const DeviceData* devices, 
                         int device_count, 
                         char* buffer, 
                         size_t bufferSize);
Return Values:

Returns 0 if everything worked.

Returns -1 if there was an error.

6. Design Choices
Handling Floats: The requirement asked for specific formatting (like 3 decimal places for volume), so I used snprintf with %.3f.

Buffer Safety: One of the biggest risks in C is overwriting memory. I added checks every time I write to the string to make sure we never go past the end of the buffer.

Static Memory: I wanted this to be "embedded friendly," so I designed it to use stack memory. This makes it safe for mission-critical firmware where dynamic memory allocation is often banned.

7. Example Output
When running the demo, the library produces this exact JSON (verified using JSONLint):


[
  {
    "gatewayId": "gateway_1234",
    "date": "1970-01-01",
    "deviceType": "stromleser",
    "interval minutes": 15,
    "total_readings": 1,
    "values": {
      "device_count": 1,
      "readings": [
        {
          "media": "water",
          "meter": "waterstarm",
          "deviceId": "stromleser_50898527",
          "unit": "m3",
          "data": [
            {
              "timestamp": "1970-01-01 00:00",
              "meter datetime": "1970-01-01 00:00",
              "total m3": 107.752,
              "status": "OK"
            }
         ]
        }
      ]
    }
  }
]
