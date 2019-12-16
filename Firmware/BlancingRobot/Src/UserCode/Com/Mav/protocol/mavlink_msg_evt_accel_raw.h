#pragma once
// MESSAGE EVT_ACCEL_RAW PACKING

#define MAVLINK_MSG_ID_EVT_ACCEL_RAW 12

MAVPACKED(
typedef struct __mavlink_evt_accel_raw_t {
 int16_t accel_x; /*<  Accel X*/
 int16_t accel_y; /*<  Accel Y*/
 int16_t accel_z; /*<  Accel Z*/
}) mavlink_evt_accel_raw_t;

#define MAVLINK_MSG_ID_EVT_ACCEL_RAW_LEN 6
#define MAVLINK_MSG_ID_EVT_ACCEL_RAW_MIN_LEN 6
#define MAVLINK_MSG_ID_12_LEN 6
#define MAVLINK_MSG_ID_12_MIN_LEN 6

#define MAVLINK_MSG_ID_EVT_ACCEL_RAW_CRC 43
#define MAVLINK_MSG_ID_12_CRC 43



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_EVT_ACCEL_RAW { \
    12, \
    "EVT_ACCEL_RAW", \
    3, \
    {  { "accel_x", NULL, MAVLINK_TYPE_INT16_T, 0, 0, offsetof(mavlink_evt_accel_raw_t, accel_x) }, \
         { "accel_y", NULL, MAVLINK_TYPE_INT16_T, 0, 2, offsetof(mavlink_evt_accel_raw_t, accel_y) }, \
         { "accel_z", NULL, MAVLINK_TYPE_INT16_T, 0, 4, offsetof(mavlink_evt_accel_raw_t, accel_z) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_EVT_ACCEL_RAW { \
    "EVT_ACCEL_RAW", \
    3, \
    {  { "accel_x", NULL, MAVLINK_TYPE_INT16_T, 0, 0, offsetof(mavlink_evt_accel_raw_t, accel_x) }, \
         { "accel_y", NULL, MAVLINK_TYPE_INT16_T, 0, 2, offsetof(mavlink_evt_accel_raw_t, accel_y) }, \
         { "accel_z", NULL, MAVLINK_TYPE_INT16_T, 0, 4, offsetof(mavlink_evt_accel_raw_t, accel_z) }, \
         } \
}
#endif

/**
 * @brief Pack a evt_accel_raw message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param accel_x  Accel X
 * @param accel_y  Accel Y
 * @param accel_z  Accel Z
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_evt_accel_raw_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               int16_t accel_x, int16_t accel_y, int16_t accel_z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_EVT_ACCEL_RAW_LEN];
    _mav_put_int16_t(buf, 0, accel_x);
    _mav_put_int16_t(buf, 2, accel_y);
    _mav_put_int16_t(buf, 4, accel_z);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_EVT_ACCEL_RAW_LEN);
#else
    mavlink_evt_accel_raw_t packet;
    packet.accel_x = accel_x;
    packet.accel_y = accel_y;
    packet.accel_z = accel_z;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_EVT_ACCEL_RAW_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_EVT_ACCEL_RAW;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_EVT_ACCEL_RAW_MIN_LEN, MAVLINK_MSG_ID_EVT_ACCEL_RAW_LEN, MAVLINK_MSG_ID_EVT_ACCEL_RAW_CRC);
}

/**
 * @brief Pack a evt_accel_raw message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param accel_x  Accel X
 * @param accel_y  Accel Y
 * @param accel_z  Accel Z
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_evt_accel_raw_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   int16_t accel_x,int16_t accel_y,int16_t accel_z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_EVT_ACCEL_RAW_LEN];
    _mav_put_int16_t(buf, 0, accel_x);
    _mav_put_int16_t(buf, 2, accel_y);
    _mav_put_int16_t(buf, 4, accel_z);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_EVT_ACCEL_RAW_LEN);
#else
    mavlink_evt_accel_raw_t packet;
    packet.accel_x = accel_x;
    packet.accel_y = accel_y;
    packet.accel_z = accel_z;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_EVT_ACCEL_RAW_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_EVT_ACCEL_RAW;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_EVT_ACCEL_RAW_MIN_LEN, MAVLINK_MSG_ID_EVT_ACCEL_RAW_LEN, MAVLINK_MSG_ID_EVT_ACCEL_RAW_CRC);
}

/**
 * @brief Encode a evt_accel_raw struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param evt_accel_raw C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_evt_accel_raw_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_evt_accel_raw_t* evt_accel_raw)
{
    return mavlink_msg_evt_accel_raw_pack(system_id, component_id, msg, evt_accel_raw->accel_x, evt_accel_raw->accel_y, evt_accel_raw->accel_z);
}

/**
 * @brief Encode a evt_accel_raw struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param evt_accel_raw C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_evt_accel_raw_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_evt_accel_raw_t* evt_accel_raw)
{
    return mavlink_msg_evt_accel_raw_pack_chan(system_id, component_id, chan, msg, evt_accel_raw->accel_x, evt_accel_raw->accel_y, evt_accel_raw->accel_z);
}

/**
 * @brief Send a evt_accel_raw message
 * @param chan MAVLink channel to send the message
 *
 * @param accel_x  Accel X
 * @param accel_y  Accel Y
 * @param accel_z  Accel Z
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_evt_accel_raw_send(mavlink_channel_t chan, int16_t accel_x, int16_t accel_y, int16_t accel_z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_EVT_ACCEL_RAW_LEN];
    _mav_put_int16_t(buf, 0, accel_x);
    _mav_put_int16_t(buf, 2, accel_y);
    _mav_put_int16_t(buf, 4, accel_z);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_EVT_ACCEL_RAW, buf, MAVLINK_MSG_ID_EVT_ACCEL_RAW_MIN_LEN, MAVLINK_MSG_ID_EVT_ACCEL_RAW_LEN, MAVLINK_MSG_ID_EVT_ACCEL_RAW_CRC);
#else
    mavlink_evt_accel_raw_t packet;
    packet.accel_x = accel_x;
    packet.accel_y = accel_y;
    packet.accel_z = accel_z;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_EVT_ACCEL_RAW, (const char *)&packet, MAVLINK_MSG_ID_EVT_ACCEL_RAW_MIN_LEN, MAVLINK_MSG_ID_EVT_ACCEL_RAW_LEN, MAVLINK_MSG_ID_EVT_ACCEL_RAW_CRC);
#endif
}

/**
 * @brief Send a evt_accel_raw message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_evt_accel_raw_send_struct(mavlink_channel_t chan, const mavlink_evt_accel_raw_t* evt_accel_raw)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_evt_accel_raw_send(chan, evt_accel_raw->accel_x, evt_accel_raw->accel_y, evt_accel_raw->accel_z);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_EVT_ACCEL_RAW, (const char *)evt_accel_raw, MAVLINK_MSG_ID_EVT_ACCEL_RAW_MIN_LEN, MAVLINK_MSG_ID_EVT_ACCEL_RAW_LEN, MAVLINK_MSG_ID_EVT_ACCEL_RAW_CRC);
#endif
}

#if MAVLINK_MSG_ID_EVT_ACCEL_RAW_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_evt_accel_raw_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  int16_t accel_x, int16_t accel_y, int16_t accel_z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_int16_t(buf, 0, accel_x);
    _mav_put_int16_t(buf, 2, accel_y);
    _mav_put_int16_t(buf, 4, accel_z);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_EVT_ACCEL_RAW, buf, MAVLINK_MSG_ID_EVT_ACCEL_RAW_MIN_LEN, MAVLINK_MSG_ID_EVT_ACCEL_RAW_LEN, MAVLINK_MSG_ID_EVT_ACCEL_RAW_CRC);
#else
    mavlink_evt_accel_raw_t *packet = (mavlink_evt_accel_raw_t *)msgbuf;
    packet->accel_x = accel_x;
    packet->accel_y = accel_y;
    packet->accel_z = accel_z;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_EVT_ACCEL_RAW, (const char *)packet, MAVLINK_MSG_ID_EVT_ACCEL_RAW_MIN_LEN, MAVLINK_MSG_ID_EVT_ACCEL_RAW_LEN, MAVLINK_MSG_ID_EVT_ACCEL_RAW_CRC);
#endif
}
#endif

#endif

// MESSAGE EVT_ACCEL_RAW UNPACKING


/**
 * @brief Get field accel_x from evt_accel_raw message
 *
 * @return  Accel X
 */
static inline int16_t mavlink_msg_evt_accel_raw_get_accel_x(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  0);
}

/**
 * @brief Get field accel_y from evt_accel_raw message
 *
 * @return  Accel Y
 */
static inline int16_t mavlink_msg_evt_accel_raw_get_accel_y(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  2);
}

/**
 * @brief Get field accel_z from evt_accel_raw message
 *
 * @return  Accel Z
 */
static inline int16_t mavlink_msg_evt_accel_raw_get_accel_z(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  4);
}

/**
 * @brief Decode a evt_accel_raw message into a struct
 *
 * @param msg The message to decode
 * @param evt_accel_raw C-struct to decode the message contents into
 */
static inline void mavlink_msg_evt_accel_raw_decode(const mavlink_message_t* msg, mavlink_evt_accel_raw_t* evt_accel_raw)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    evt_accel_raw->accel_x = mavlink_msg_evt_accel_raw_get_accel_x(msg);
    evt_accel_raw->accel_y = mavlink_msg_evt_accel_raw_get_accel_y(msg);
    evt_accel_raw->accel_z = mavlink_msg_evt_accel_raw_get_accel_z(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_EVT_ACCEL_RAW_LEN? msg->len : MAVLINK_MSG_ID_EVT_ACCEL_RAW_LEN;
        memset(evt_accel_raw, 0, MAVLINK_MSG_ID_EVT_ACCEL_RAW_LEN);
    memcpy(evt_accel_raw, _MAV_PAYLOAD(msg), len);
#endif
}
