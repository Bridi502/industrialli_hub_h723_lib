#include "LoRaMESH.h"

enum ApplicationCommand {
  REQUEST_TEMP = 0x7F,
  REQUEST_HUMIDITY = 0x7E
};

/**
 * @brief Requests temperature from a LoRaMESH node.
 *
 * This function sends a temperature request command to a specified LoRaMESH node
 * and waits for the response containing the temperature data.
 *
 * @param lora A reference to the LoRaMESH object for communication.
 * @param idNode The ID of the target LoRaMESH node to request temperature from.
 * @param temperature Reference to a float variable to store the received temperature.
 */
void requestTemperature(LoRaMESH &lora, uint16_t idNode, float &temperature) {
  uint8_t payload[0];
  if (lora.prepareFrameCommand(idNode, REQUEST_TEMP, payload, 0)) {
    Serial1.print("Requesting temperature from node ");
    Serial1.print(idNode);
    Serial1.println(" ... ");
  }

  uint16_t received_id;
  uint8_t received_payload[MAX_PAYLOAD_SIZE];
  uint8_t received_command, received_payload_size;

  if (lora.receivePacketCommand(&received_id, &received_command, received_payload, &received_payload_size, 1000)) {
    Serial1.println("Response received:");
  } else {
    Serial1.println("ERROR: TIMEOUT");
  }

  memcpy(&temperature, received_payload, sizeof(float));
}

/**
 * @brief Sends temperature response to a LoRaMESH node.
 *
 * This function sends a temperature response containing the provided temperature
 * data to a specified LoRaMESH node.
 *
 * @param lora A reference to the LoRaMESH object for communication.
 * @param idNode The ID of the target LoRaMESH node to send the temperature response to.
 * @param temperature The temperature data to be sent in the response.
 */
void sendTemperature(LoRaMESH &lora, uint16_t idNode, float temperature) {
  uint8_t payload[sizeof(float)];
  memcpy(payload, &temperature, sizeof(float));
  if (lora.prepareFrameCommand(0, REQUEST_TEMP, payload, sizeof(float))) {
    Serial1.println("Temperature response sent.");
  }
}

/**
 * @brief Requests humidity from a LoRaMESH node.
 *
 * This function sends a humidity request command to a specified LoRaMESH node
 * and waits for the response containing the humidity data.
 *
 * @param lora A reference to the LoRaMESH object for communication.
 * @param idNode The ID of the target LoRaMESH node to request humidity from.
 * @param humidity Reference to a float variable to store the received humidity.
 */
void requestHumidity(LoRaMESH &lora, uint16_t idNode, float &humidity) {
  uint8_t payload[0];
  if (lora.prepareFrameCommand(idNode, REQUEST_HUMIDITY, payload, 0)) {
    Serial1.print("Requesting humidity from node ");
    Serial1.print(idNode);
    Serial1.println(" ... ");
  }

  uint16_t received_id;
  uint8_t received_payload[MAX_PAYLOAD_SIZE];
  uint8_t received_command, received_payload_size;

  if (lora.receivePacketCommand(&received_id, &received_command, received_payload, &received_payload_size, 1000)) {
    Serial1.println("Response received:");
  } else {
    Serial1.println("ERROR: TIMEOUT");
  }

  memcpy(&humidity, received_payload, sizeof(float));
}

/**
 * @brief Sends humidity response to a LoRaMESH node.
 *
 * This function sends a humidity response containing the provided humidity
 * data to a specified LoRaMESH node.
 *
 * @param lora A reference to the LoRaMESH object for communication.
 * @param idNode The ID of the target LoRaMESH node to send the humidity response to.
 * @param humidity The humidity data to be sent in the response.
 */
void sendHumidity(LoRaMESH &lora, uint16_t idNode, float humidity) {
  uint8_t payload[sizeof(float)];
  memcpy(payload, &humidity, sizeof(float));
  if (lora.prepareFrameCommand(0, REQUEST_HUMIDITY, payload, sizeof(float))) {
    Serial1.println("Humidity response sent.");
  }
}