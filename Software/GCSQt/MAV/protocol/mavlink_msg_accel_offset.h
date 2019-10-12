#pragma once
// MESSAGE ACCEL_OFFSET PACKING

#define MAVLINK_MSG_ID_ACCEL_OFFSET 9

MAVPACKED(
typedef struct __mavlink_accel_offset_t {
 int16_t accel_offet_x; /*<  Accel Offset X*/
 int16_t accel_offet_y; /*<  Accel Offset Y*/
 int16_t accel_offet_z; /*<  Accel Offset Z*/
}) mavlink_accel_offset_t;

#define MAVLINK_MSG_ID_ACCEL_OFFSET_LEN 6
#define MAVLINK_MSG_ID_ACCEL_OFFSET_MIN_LEN 6
#define MAVLINK_MSG_ID_9_LEN 6
#define MAVLINK_MSG_ID_9_MIN_LEN 6

#define MAVLINK_MSG_ID_ACCEL_OFFSET_CRC 8
#define MAVLINK_MSG_ID_9_CRC 8



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_ACCEL_OFFSET { \
    9, \
    "ACCEL_OFFSET", \
    3, \
    {  { "accel_offet_x", NULL, MAVLINK_TYPE_INT16_T, 0, 0, offsetof(mavlink_accel_offset_t, accel_offet_x) }, \
         { "accel_offet_y", NULL, MAVLINK_TYPE_INT16_T, 0, 2, offsetof(mavlink_accel_offset_t, accel_offet_y) }, \
         { "accel_offet_z", NULL, MAVLINK_TYPE_INT16_T, 0, 4, offsetof(mavlink_accel_offset_t, accel_offet_z) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_ACCEL_OFFSET { \
    "ACCEL_OFFSET", \
    3, \
    {  { "accel_offet_x", NULL, MAVLINK_TYPE_INT16_T, 0, 0, offsetof(mavlink_accel_offset_t, accel_offet_x) }, \
         { "accel_offet_y", NULL, MAVLINK_TYPE_INT16_T, 0, 2, offsetof(mavlink_accel_offset_t, accel_offet_y) }, \
         { "accel_offet_z", NULL, MAVLINK_TYPE_INT16_T, 0, 4, offsetof(mavlink_accel_offset_t, accel_offet_z) }, \
         } \
}
#endif

/**
 * @brief Pack a accel_offset message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param accel_offet_x  Accel Offset X
 * @param accel_offet_y  Accel Offset Y
 * @param accel_offet_z  Accel Offset Z
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_accel_offset_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               int16_t accel_offet_x, int16_t accel_offet_y, int16_t accel_offet_z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ACCEL_OFFSET_LEN];
    _mav_put_int16_t(buf, 0, accel_offet_x);
    _mav_put_int16_t(buf, 2, accel_offet_y);
    _mav_put_int16_t(buf, 4, accel_offet_z);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ACCEL_OFFSET_LEN);
#else
    mavlink_accel_offset_t packet;
    packet.accel_offet_x = accel_offet_x;
    packet.accel_offet_y = accel_offet_y;
    packet.accel_offet_z = accel_offet_z;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ACCEL_OFFSET_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_ACCEL_OFFSET;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_ACCEL_OFFSET_MIN_LEN, MAVLINK_MSG_ID_ACCEL_OFFSET_LEN, MAVLINK_MSG_ID_ACCEL_OFFSET_CRC);
}

/**
 * @brief Pack a accel_offset message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param accel_offet_x  Accel Offset X
 * @param accel_offet_y  Accel Offset Y
 * @param accel_offet_z  Accel Offset Z
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_accel_offset_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   int16_t accel_offet_x,int16_t accel_offet_y,int16_t accel_offet_z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ACCEL_OFFSET_LEN];
    _mav_put_int16_t(buf, 0, accel_offet_x);
    _mav_put_int16_t(buf, 2, accel_offet_y);
    _mav_put_int16_t(buf, 4, accel_offet_z);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ACCEL_OFFSET_LEN);
#else
    mavlink_accel_offset_t packet;
    packet.accel_offet_x = accel_offet_x;
    packet.accel_offet_y = accel_offet_y;
    packet.accel_offet_z = accel_offet_z;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ACCEL_OFFSET_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_ACCEL_OFFSET;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_ACCEL_OFFSET_MIN_LEN, MAVLINK_MSG_ID_ACCEL_OFFSET_LEN, MAVLINK_MSG_ID_ACCEL_OFFSET_CRC);
}

/**
 * @brief Encode a accel_offset struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param accel_offset C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_accel_offset_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_accel_offset_t* accel_offset)
{
    return mavlink_msg_accel_offset_pack(system_id, component_id, msg, accel_offset->accel_offet_x, accel_offset->accel_offet_y, accel_offset->accel_offet_z);
}

/**
 * @brief Encode a accel_offset struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param accel_offset C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_accel_offset_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_accel_offset_t* accel_offset)
{
    return mavlink_msg_accel_offset_pack_chan(system_id, component_id, chan, msg, accel_offset->accel_offet_x, accel_offset->accel_offet_y, accel_offset->accel_offet_z);
}

/**
 * @brief Send a accel_offset message
 * @param chan MAVLink channel to send the message
 *
 * @param accel_offet_x  Accel Offset X
 * @param accel_offet_y  Accel Offset Y
 * @param accel_offet_z  Accel Offset Z
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_accel_offset_send(mavlink_channel_t chan, int16_t accel_offet_x, int16_t accel_offet_y, int16_t accel_offet_z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ACCEL_OFFSET_LEN];
    _mav_put_int16_t(buf, 0, accel_offet_x);
    _mav_put_int16_t(buf, 2, accel_offet_y);
    _mav_put_int16_t(buf, 4, accel_offet_z);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ACCEL_OFFSET, buf, MAVLINK_MSG_ID_ACCEL_OFFSET_MIN_LEN, MAVLINK_MSG_ID_ACCEL_OFFSET_LEN, MAVLINK_MSG_ID_ACCEL_OFFSET_CRC);
#else
    mavlink_accel_offset_t packet;
    packet.accel_offet_x = accel_offet_x;
    packet.accel_offet_y = accel_offet_y;
    packet.accel_offet_z = accel_offet_z;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ACCEL_OFFSET, (const char *)&packet, MAVLINK_MSG_ID_ACCEL_OFFSET_MIN_LEN, MAVLINK_MSG_ID_ACCEL_OFFSET_LEN, MAVLINK_MSG_ID_ACCEL_OFFSET_CRC);
#endif
}

/**
 * @brief Send a accel_offset message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_accel_offset_send_struct(mavlink_channel_t chan, const mavlink_accel_offset_t* accel_offset)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_accel_offset_send(chan, accel_offset->accel_offet_x, accel_offset->accel_offet_y, accel_offset->accel_offet_z);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ACCEL_OFFSET, (const char *)accel_offset, MAVLINK_MSG_ID_ACCEL_OFFSET_MIN_LEN, MAVLINK_MSG_ID_ACCEL_OFFSET_LEN, MAVLINK_MSG_ID_ACCEL_OFFSET_CRC);
#endif
}

#if MAVLINK_MSG_ID_ACCEL_OFFSET_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_accel_offset_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  int16_t accel_offet_x, int16_t accel_offet_y, int16_t accel_offet_z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_int16_t(buf, 0, accel_offet_x);
    _mav_put_int16_t(buf, 2, accel_offet_y);
    _mav_put_int16_t(buf, 4, accel_offet_z);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ACCEL_OFFSET, buf, MAVLINK_MSG_ID_ACCEL_OFFSET_MIN_LEN, MAVLINK_MSG_ID_ACCEL_OFFSET_LEN, MAVLINK_MSG_ID_ACCEL_OFFSET_CRC);
#else
    mavlink_accel_offset_t *packet = (mavlink_accel_offset_t *)msgbuf;
    packet->accel_offet_x = accel_offet_x;
    packet->accel_offet_y = accel_offet_y;
    packet->accel_offet_z = accel_offet_z;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ACCEL_OFFSET, (const char *)packet, MAVLINK_MSG_ID_ACCEL_OFFSET_MIN_LEN, MAVLINK_MSG_ID_ACCEL_OFFSET_LEN, MAVLINK_MSG_ID_ACCEL_OFFSET_CRC);
#endif
}
#endif

#endif

// MESSAGE ACCEL_OFFSET UNPACKING


/**
 * @brief Get field accel_offet_x from accel_offset message
 *
 * @return  Accel Offset X
 */
static inline int16_t mavlink_msg_accel_offset_get_accel_offet_x(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  0);
}

/**
 * @brief Get field accel_offet_y from accel_offset message
 *
 * @return  Accel Offset Y
 */
static inline int16_t mavlink_msg_accel_offset_get_accel_offet_y(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  2);
}

/**
 * @brief Get field accel_offet_z from accel_offset message
 *
 * @return  Accel Offset Z
 */
static inline int16_t mavlink_msg_accel_offset_get_accel_offet_z(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  4);
}

/**
 * @brief Decode a accel_offset message into a struct
 *
 * @param msg The message to decode
 * @param accel_offset C-struct to decode the message contents into
 */
static inline void mavlink_msg_accel_offset_decode(const mavlink_message_t* msg, mavlink_accel_offset_t* accel_offset)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    accel_offset->accel_offet_x = mavlink_msg_accel_offset_get_accel_offet_x(msg);
    accel_offset->accel_offet_y = mavlink_msg_accel_offset_get_accel_offet_y(msg);
    accel_offset->accel_offet_z = mavlink_msg_accel_offset_get_accel_offet_z(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_ACCEL_OFFSET_LEN? msg->len : MAVLINK_MSG_ID_ACCEL_OFFSET_LEN;
        memset(accel_offset, 0, MAVLINK_MSG_ID_ACCEL_OFFSET_LEN);
    memcpy(accel_offset, _MAV_PAYLOAD(msg), len);
#endif
}
