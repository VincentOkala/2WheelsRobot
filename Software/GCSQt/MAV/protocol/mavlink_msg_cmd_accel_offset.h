#pragma once
// MESSAGE CMD_ACCEL_OFFSET PACKING

#define MAVLINK_MSG_ID_CMD_ACCEL_OFFSET 10

MAVPACKED(
typedef struct __mavlink_cmd_accel_offset_t {
 int8_t cmd_params; /*<  Save Or Load Accel Offset*/
}) mavlink_cmd_accel_offset_t;

#define MAVLINK_MSG_ID_CMD_ACCEL_OFFSET_LEN 1
#define MAVLINK_MSG_ID_CMD_ACCEL_OFFSET_MIN_LEN 1
#define MAVLINK_MSG_ID_10_LEN 1
#define MAVLINK_MSG_ID_10_MIN_LEN 1

#define MAVLINK_MSG_ID_CMD_ACCEL_OFFSET_CRC 5
#define MAVLINK_MSG_ID_10_CRC 5



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_CMD_ACCEL_OFFSET { \
    10, \
    "CMD_ACCEL_OFFSET", \
    1, \
    {  { "cmd_params", NULL, MAVLINK_TYPE_INT8_T, 0, 0, offsetof(mavlink_cmd_accel_offset_t, cmd_params) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_CMD_ACCEL_OFFSET { \
    "CMD_ACCEL_OFFSET", \
    1, \
    {  { "cmd_params", NULL, MAVLINK_TYPE_INT8_T, 0, 0, offsetof(mavlink_cmd_accel_offset_t, cmd_params) }, \
         } \
}
#endif

/**
 * @brief Pack a cmd_accel_offset message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param cmd_params  Save Or Load Accel Offset
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_cmd_accel_offset_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               int8_t cmd_params)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_CMD_ACCEL_OFFSET_LEN];
    _mav_put_int8_t(buf, 0, cmd_params);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_CMD_ACCEL_OFFSET_LEN);
#else
    mavlink_cmd_accel_offset_t packet;
    packet.cmd_params = cmd_params;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_CMD_ACCEL_OFFSET_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_CMD_ACCEL_OFFSET;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_CMD_ACCEL_OFFSET_MIN_LEN, MAVLINK_MSG_ID_CMD_ACCEL_OFFSET_LEN, MAVLINK_MSG_ID_CMD_ACCEL_OFFSET_CRC);
}

/**
 * @brief Pack a cmd_accel_offset message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param cmd_params  Save Or Load Accel Offset
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_cmd_accel_offset_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   int8_t cmd_params)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_CMD_ACCEL_OFFSET_LEN];
    _mav_put_int8_t(buf, 0, cmd_params);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_CMD_ACCEL_OFFSET_LEN);
#else
    mavlink_cmd_accel_offset_t packet;
    packet.cmd_params = cmd_params;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_CMD_ACCEL_OFFSET_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_CMD_ACCEL_OFFSET;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_CMD_ACCEL_OFFSET_MIN_LEN, MAVLINK_MSG_ID_CMD_ACCEL_OFFSET_LEN, MAVLINK_MSG_ID_CMD_ACCEL_OFFSET_CRC);
}

/**
 * @brief Encode a cmd_accel_offset struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param cmd_accel_offset C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_cmd_accel_offset_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_cmd_accel_offset_t* cmd_accel_offset)
{
    return mavlink_msg_cmd_accel_offset_pack(system_id, component_id, msg, cmd_accel_offset->cmd_params);
}

/**
 * @brief Encode a cmd_accel_offset struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param cmd_accel_offset C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_cmd_accel_offset_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_cmd_accel_offset_t* cmd_accel_offset)
{
    return mavlink_msg_cmd_accel_offset_pack_chan(system_id, component_id, chan, msg, cmd_accel_offset->cmd_params);
}

/**
 * @brief Send a cmd_accel_offset message
 * @param chan MAVLink channel to send the message
 *
 * @param cmd_params  Save Or Load Accel Offset
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_cmd_accel_offset_send(mavlink_channel_t chan, int8_t cmd_params)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_CMD_ACCEL_OFFSET_LEN];
    _mav_put_int8_t(buf, 0, cmd_params);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CMD_ACCEL_OFFSET, buf, MAVLINK_MSG_ID_CMD_ACCEL_OFFSET_MIN_LEN, MAVLINK_MSG_ID_CMD_ACCEL_OFFSET_LEN, MAVLINK_MSG_ID_CMD_ACCEL_OFFSET_CRC);
#else
    mavlink_cmd_accel_offset_t packet;
    packet.cmd_params = cmd_params;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CMD_ACCEL_OFFSET, (const char *)&packet, MAVLINK_MSG_ID_CMD_ACCEL_OFFSET_MIN_LEN, MAVLINK_MSG_ID_CMD_ACCEL_OFFSET_LEN, MAVLINK_MSG_ID_CMD_ACCEL_OFFSET_CRC);
#endif
}

/**
 * @brief Send a cmd_accel_offset message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_cmd_accel_offset_send_struct(mavlink_channel_t chan, const mavlink_cmd_accel_offset_t* cmd_accel_offset)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_cmd_accel_offset_send(chan, cmd_accel_offset->cmd_params);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CMD_ACCEL_OFFSET, (const char *)cmd_accel_offset, MAVLINK_MSG_ID_CMD_ACCEL_OFFSET_MIN_LEN, MAVLINK_MSG_ID_CMD_ACCEL_OFFSET_LEN, MAVLINK_MSG_ID_CMD_ACCEL_OFFSET_CRC);
#endif
}

#if MAVLINK_MSG_ID_CMD_ACCEL_OFFSET_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_cmd_accel_offset_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  int8_t cmd_params)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_int8_t(buf, 0, cmd_params);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CMD_ACCEL_OFFSET, buf, MAVLINK_MSG_ID_CMD_ACCEL_OFFSET_MIN_LEN, MAVLINK_MSG_ID_CMD_ACCEL_OFFSET_LEN, MAVLINK_MSG_ID_CMD_ACCEL_OFFSET_CRC);
#else
    mavlink_cmd_accel_offset_t *packet = (mavlink_cmd_accel_offset_t *)msgbuf;
    packet->cmd_params = cmd_params;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CMD_ACCEL_OFFSET, (const char *)packet, MAVLINK_MSG_ID_CMD_ACCEL_OFFSET_MIN_LEN, MAVLINK_MSG_ID_CMD_ACCEL_OFFSET_LEN, MAVLINK_MSG_ID_CMD_ACCEL_OFFSET_CRC);
#endif
}
#endif

#endif

// MESSAGE CMD_ACCEL_OFFSET UNPACKING


/**
 * @brief Get field cmd_params from cmd_accel_offset message
 *
 * @return  Save Or Load Accel Offset
 */
static inline int8_t mavlink_msg_cmd_accel_offset_get_cmd_params(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int8_t(msg,  0);
}

/**
 * @brief Decode a cmd_accel_offset message into a struct
 *
 * @param msg The message to decode
 * @param cmd_accel_offset C-struct to decode the message contents into
 */
static inline void mavlink_msg_cmd_accel_offset_decode(const mavlink_message_t* msg, mavlink_cmd_accel_offset_t* cmd_accel_offset)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    cmd_accel_offset->cmd_params = mavlink_msg_cmd_accel_offset_get_cmd_params(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_CMD_ACCEL_OFFSET_LEN? msg->len : MAVLINK_MSG_ID_CMD_ACCEL_OFFSET_LEN;
        memset(cmd_accel_offset, 0, MAVLINK_MSG_ID_CMD_ACCEL_OFFSET_LEN);
    memcpy(cmd_accel_offset, _MAV_PAYLOAD(msg), len);
#endif
}
