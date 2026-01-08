STM32 JSON Serialization Assignment

 Project Overview :

This project demonstrates how structured measurement data can be converted into JSON format on an embedded system using plain C , without relying on any external JSON libraries.

 MCU used : STM32F446RE (Nucleo Board) :

The STM32F446RE was chosen because it is a commonly used ARM Cortex-M4 microcontroller with good performance and stable HAL support. It provides enough memory to handle structured data while still representing a realistic embedded environment. The Nucleo board also includes an on-board ST-LINK debugger and virtual COM port, which makes UART-based testing straightforward.

Platform Used :
STM32CUBEIDE

Programming Language C :

C was used because it is the standard language for embedded firmware development. It provides full control over memory usage, which is critical for this assignment. I had started my embedded journey with C hence this is also a reason for chosing this language 


Build and Run Instructions :

1. Open STM32F446RE .
2. Create or import the project for NUCLEO-F446RE . 
3. Open the (.ioc) file and enable USART2 in asynchronous mode (115200 baud)
4. Build the project using Project to  Build
5. Connect the Nucleo board to the PC via USB
6. Click Run to flash the firmware
7. Open a serial terminal (CubeIDE terminal)

    Baud rate: 115200
    Data bits: 8
    Parity: None
    Stop bits: 1
8. Press the RESET button on the board to view the JSON output

 Public API Description :

The serialization module exposes a single public function:


JsonStatus serialize_gateway_payload(
    const GatewayPayload *payload,
    char *out,
    size_t out_size,
    size_t *written_len
);

 Function Description:

This function converts a populated `GatewayPayload` structure into a JSON string.

 Parameters:

 payload – Pointer to the data structure containing gateway and device information
 out – Output buffer where the JSON string will be written
 out_size – Size of the output buffer
 written_len – Pointer to store the number of bytes written

 Return Value:

 JSON_OK – Serialization successful
 JSON_ERR_BUFFER_TOO_SMALL – Output buffer is insufficient
 JSON_ERR_INVALID_INPUT – Invalid input parameters


Example JSON Output

Below is an example of the JSON produced by the system:


[{
  "gatewayId":"gateway_1234",
  "date":"1970-01-01",
  "deviceType":"stromleser",
  "interval_minutes":15,
  "total_readings":1,
  "values":{
    "device_count":1,
    "readings":[{
      "media":"water",
      "meter":"waterstarm",
      "deviceId":"stromleser_50898527",
      "unit":"m3",
      "data":[{
        "timestamp":"1970-01-01 00:00",
        "meter_datetime":"1970-01-01 00:00",
        "total_m3":107.752,
        "status":"OK"
      }]
    }]
  }
}]

 Design Decisions and Assumptions

 No external JSON libraries were used to keep the solution lightweight and portable.
 Fixed-size structures and buffers were used to ensure predictable memory usage.
 snprintf() was used for safe string formatting and buffer overflow protection.
 The serializer is designed to be transport-independent; UART is used only for demonstration.
The data model assumes a maximum number of devices and data points, which can be adjusted if needed.




