#pragma once
// MESSAGE CMD_SET_PID PACKING

#define MAVLINK_MSG_ID_CMD_SET_PID 13

MAVPACKED(
typedef struct __mavlink_cmd_set_pid_t {
 float KP; /*<  KP*/
 float KI; /*<  KI*/
 float KD; /*<  KD*/
}) mavlink_cmd_set_pid_t;

#define MAVLINK_MSG_ID_CMD_SET_PID_LEN 12
#define MAVLINK_MSG_ID_CMD_SET_PID_MIN_LEN 12
#define MAVLINK_MSG_ID_13_LEN 12
#define MAVLINK_MSG_ID_13_MIN_LEN 12

#define MAVLINK_MSG_ID_CMD_SET_PID_CRC 73
#define MAVLINK_MSG_ID_13_CRC 73



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_CMD_SET_PID { \
    13, \
    "CMD_SET_PID", \
    3, \
    {  { "KP", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_cmd_set_pid_t, KP) }, \
         { "KI", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_cmd_set_pid_t, KI) }, \
         { "KD", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_cmd_set_pid_t, KD) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_CMD_SET_PID { \
    "CMD_SET_PID", \
    3, \
    {  { "KP", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_cmd_set_pid_t, KP) }, \
         { "KI", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_cmd_set_pid_t, KI) }, \
         { "KD", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_cmd_set_pid_t, KD) }, \
         } \
}
#endif

/**
 * @brief Pack a cmd_set_pid message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param KP  KP
 * @param KI  KI
 * @param KD  KD
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_cmd_set_pid_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               float KP, float KI, float KD)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_CMD_SET_PID_LEN];
    _mav_put_float(buf, 0, KP);
    _mav_put_float(buf, 4, KI);
    _mav_put_float(buf, 8, KD);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_CMD_SET_PID_LEN);
#else
    mavlink_cmd_set_pid_t packet;
    packet.KP = KP;
    packet.KI = KI;
    packet.KD = KD;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_CMD_SET_PID_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_CMD_SET_PID;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_CMD_SET_PID_MIN_LEN, MAVLINK_MSG_ID_CMD_SET_PID_LEN, MAVLINK_MSG_ID_CMD_SET_PID_CRC);
}

/**
 * @brief Pack a cmd_set_pid message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param KP  KP
 * @param KI  KI
 * @param KD  KD
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_cmd_set_pid_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   float KP,float KI,float KD)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_CMD_SET_PID_LEN];
    _mav_put_float(buf, 0, KP);
    _mav_put_float(buf, 4, KI);
    _mav_put_float(buf, 8, KD);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_CMD_SET_PID_LEN);
#else
    mavlink_cmd_set_pid_t packet;
    packet.KP = KP;
    packet.KI = KI;
    packet.KD = KD;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_CMD_SET_PID_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_CMD_SET_PID;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_CMD_SET_PID_MIN_LEN, MAVLINK_MSG_ID_CMD_SET_PID_LEN, MAVLINK_MSG_ID_CMD_SET_PID_CRC);
}

/**
 * @brief Encode a cmd_set_pid struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param cmd_set_pid C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_cmd_set_pid_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_cmd_set_pid_t* cmd_set_pid)
{
    return mavlink_msg_cmd_set_pid_pack(system_id, component_id, msg, cmd_set_pid->KP, cmd_set_pid->KI, cmd_set_pid->KD);
}

/**
 * @brief Encode a cmd_set_pid struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param cmd_set_pid C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_cmd_set_pid_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_cmd_set_pid_t* cmd_set_pid)
{
    return mavlink_msg_cmd_set_pid_pack_chan(system_id, component_id, chan, msg, cmd_set_pid->KP, cmd_set_pid->KI, cmd_set_pid->KD);
}

/**
 * @brief Send a cmd_set_pid message
 * @param chan MAVLink channel to send the message
 *
 * @param KP  KP
 * @param KI  KI
 * @param KD  KD
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_cmd_set_pid_send(mavlink_channel_t chan, float KP, float KI, float KD)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_CMD_SET_PID_LEN];
    _mav_put_float(buf, 0, KP);
    _mav_put_float(buf, 4, KI);
    _mav_put_float(buf, 8, KD);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CMD_SET_PID, buf, MAVLINK_MSG_ID_CMD_SET_PID_MIN_LEN, MAVLINK_MSG_ID_CMD_SET_PID_LEN, MAVLINK_MSG_ID_CMD_SET_PID_CRC);
#else
    mavlink_cmd_set_pid_t packet;
    packet.KP = KP;
    packet.KI = KI;
    packet.KD = KD;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CMD_SET_PID, (const char *)&packet, MAVLINK_MSG_ID_CMD_SET_PID_MIN_LEN, MAVLINK_MSG_ID_CMD_SET_PID_LEN, MAVLINK_MSG_ID_CMD_SET_PID_CRC);
#endif
}

/**
 * @brief Send a cmd_set_pid message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_cmd_set_pid_send_struct(mavlink_channel_t chan, const mavlink_cmd_set_pid_t* cmd_set_pid)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_cmd_set_pid_send(chan, cmd_set_pid->KP, cmd_set_pid->KI, cmd_set_pid->KD);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CMD_SET_PID, (const char *)cmd_set_pid, MAVLINK_MSG_ID_CMD_SET_PID_MIN_LEN, MAVLINK_MSG_ID_CMD_SET_PID_LEN, MAVLINK_MSG_ID_CMD_SET_PID_CRC);
#endif
}

#if MAVLINK_MSG_ID_CMD_SET_PID_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_cmd_set_pid_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  float KP, float KI, float KD)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, KP);
    _mav_put_float(buf, 4, KI);
    _mav_put_float(buf, 8, KD);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CMD_SET_PID, buf, MAVLINK_MSG_ID_CMD_SET_PID_MIN_LEN, MAVLINK_MSG_ID_CMD_SET_PID_LEN, MAVLINK_MSG_ID_CMD_SET_PID_CRC);
#else
    mavlink_cmd_set_pid_t *packet = (mavlink_cmd_set_pid_t *)msgbuf;
    packet->KP = KP;
    packet->KI = KI;
    packet->KD = KD;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CMD_SET_PID, (const char *)packet, MAVLINK_MSG_ID_CMD_SET_PID_MIN_LEN, MAVLINK_MSG_ID_CMD_SET_PID_LEN, MAVLINK_MSG_ID_CMD_SET_PID_CRC);
#endif
}
#endif

#endif

// MESSAGE CMD_SET_PID UNPACKING


/**
 * @brief Get field KP from cmd_set_pid message
 *
 * @return  KP
 */
static inline float mavlink_msg_cmd_set_pid_get_KP(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field KI from cmd_set_pid message
 *
 * @return  KI
 */
static inline float mavlink_msg_cmd_set_pid_get_KI(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field KD from cmd_set_pid message
 *
 * @return  KD
 */
static inline float mavlink_msg_cmd_set_pid_get_KD(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Decode a cmd_set_pid message into a struct
 *
 * @param msg The message to decode
 * @param cmd_set_pid C-struct to decode the message contents into
 */
static inline void mavlink_msg_cmd_set_pid_decode(const mavlink_message_t* msg, mavlink_cmd_set_pid_t* cmd_set_pid)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    cmd_set_pid->KP = mavlink_msg_cmd_set_pid_get_KP(msg);
    cmd_set_pid->KI = mavlink_msg_cmd_set_pid_get_KI(msg);
    cmd_set_pid->KD = mavlink_msg_cmd_set_pid_get_KD(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_CMD_SET_PID_LEN? msg->len : MAVLINK_MSG_ID_CMD_SET_PID_LEN;
        memset(cmd_set_pid, 0, MAVLINK_MSG_ID_CMD_SET_PID_LEN);
    memcpy(cmd_set_pid, _MAV_PAYLOAD(msg), len);
#endif
}
