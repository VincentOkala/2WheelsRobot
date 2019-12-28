#pragma once
// MESSAGE PID_PARAMS PACKING

#define MAVLINK_MSG_ID_PID_PARAMS 11

MAVPACKED(
typedef struct __mavlink_pid_params_t {
 float whe0_KP; /*<  Wheel 0 velocity control KP*/
 float whe0_KI; /*<  Wheel 0 velocity control KI*/
 float whe0_KD; /*<  Wheel 0 velocity control KD*/
 float whe1_KP; /*<  Wheel 1 velocity control KP*/
 float whe1_KI; /*<  Wheel 1 velocity control KI*/
 float whe1_KD; /*<  Wheel 1 velocity control KD*/
 float sync_KP; /*<  Synchronous control KP*/
 float sync_KI; /*<  Synchronous control KI*/
 float sync_KD; /*<  Synchronous control KD*/
}) mavlink_pid_params_t;

#define MAVLINK_MSG_ID_PID_PARAMS_LEN 36
#define MAVLINK_MSG_ID_PID_PARAMS_MIN_LEN 36
#define MAVLINK_MSG_ID_11_LEN 36
#define MAVLINK_MSG_ID_11_MIN_LEN 36

#define MAVLINK_MSG_ID_PID_PARAMS_CRC 140
#define MAVLINK_MSG_ID_11_CRC 140



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_PID_PARAMS { \
    11, \
    "PID_PARAMS", \
    9, \
    {  { "whe0_KP", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_pid_params_t, whe0_KP) }, \
         { "whe0_KI", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_pid_params_t, whe0_KI) }, \
         { "whe0_KD", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_pid_params_t, whe0_KD) }, \
         { "whe1_KP", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_pid_params_t, whe1_KP) }, \
         { "whe1_KI", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_pid_params_t, whe1_KI) }, \
         { "whe1_KD", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_pid_params_t, whe1_KD) }, \
         { "sync_KP", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_pid_params_t, sync_KP) }, \
         { "sync_KI", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_pid_params_t, sync_KI) }, \
         { "sync_KD", NULL, MAVLINK_TYPE_FLOAT, 0, 32, offsetof(mavlink_pid_params_t, sync_KD) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_PID_PARAMS { \
    "PID_PARAMS", \
    9, \
    {  { "whe0_KP", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_pid_params_t, whe0_KP) }, \
         { "whe0_KI", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_pid_params_t, whe0_KI) }, \
         { "whe0_KD", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_pid_params_t, whe0_KD) }, \
         { "whe1_KP", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_pid_params_t, whe1_KP) }, \
         { "whe1_KI", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_pid_params_t, whe1_KI) }, \
         { "whe1_KD", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_pid_params_t, whe1_KD) }, \
         { "sync_KP", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_pid_params_t, sync_KP) }, \
         { "sync_KI", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_pid_params_t, sync_KI) }, \
         { "sync_KD", NULL, MAVLINK_TYPE_FLOAT, 0, 32, offsetof(mavlink_pid_params_t, sync_KD) }, \
         } \
}
#endif

/**
 * @brief Pack a pid_params message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param whe0_KP  Wheel 0 velocity control KP
 * @param whe0_KI  Wheel 0 velocity control KI
 * @param whe0_KD  Wheel 0 velocity control KD
 * @param whe1_KP  Wheel 1 velocity control KP
 * @param whe1_KI  Wheel 1 velocity control KI
 * @param whe1_KD  Wheel 1 velocity control KD
 * @param sync_KP  Synchronous control KP
 * @param sync_KI  Synchronous control KI
 * @param sync_KD  Synchronous control KD
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_pid_params_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               float whe0_KP, float whe0_KI, float whe0_KD, float whe1_KP, float whe1_KI, float whe1_KD, float sync_KP, float sync_KI, float sync_KD)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PID_PARAMS_LEN];
    _mav_put_float(buf, 0, whe0_KP);
    _mav_put_float(buf, 4, whe0_KI);
    _mav_put_float(buf, 8, whe0_KD);
    _mav_put_float(buf, 12, whe1_KP);
    _mav_put_float(buf, 16, whe1_KI);
    _mav_put_float(buf, 20, whe1_KD);
    _mav_put_float(buf, 24, sync_KP);
    _mav_put_float(buf, 28, sync_KI);
    _mav_put_float(buf, 32, sync_KD);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_PID_PARAMS_LEN);
#else
    mavlink_pid_params_t packet;
    packet.whe0_KP = whe0_KP;
    packet.whe0_KI = whe0_KI;
    packet.whe0_KD = whe0_KD;
    packet.whe1_KP = whe1_KP;
    packet.whe1_KI = whe1_KI;
    packet.whe1_KD = whe1_KD;
    packet.sync_KP = sync_KP;
    packet.sync_KI = sync_KI;
    packet.sync_KD = sync_KD;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_PID_PARAMS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_PID_PARAMS;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_PID_PARAMS_MIN_LEN, MAVLINK_MSG_ID_PID_PARAMS_LEN, MAVLINK_MSG_ID_PID_PARAMS_CRC);
}

/**
 * @brief Pack a pid_params message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param whe0_KP  Wheel 0 velocity control KP
 * @param whe0_KI  Wheel 0 velocity control KI
 * @param whe0_KD  Wheel 0 velocity control KD
 * @param whe1_KP  Wheel 1 velocity control KP
 * @param whe1_KI  Wheel 1 velocity control KI
 * @param whe1_KD  Wheel 1 velocity control KD
 * @param sync_KP  Synchronous control KP
 * @param sync_KI  Synchronous control KI
 * @param sync_KD  Synchronous control KD
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_pid_params_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   float whe0_KP,float whe0_KI,float whe0_KD,float whe1_KP,float whe1_KI,float whe1_KD,float sync_KP,float sync_KI,float sync_KD)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PID_PARAMS_LEN];
    _mav_put_float(buf, 0, whe0_KP);
    _mav_put_float(buf, 4, whe0_KI);
    _mav_put_float(buf, 8, whe0_KD);
    _mav_put_float(buf, 12, whe1_KP);
    _mav_put_float(buf, 16, whe1_KI);
    _mav_put_float(buf, 20, whe1_KD);
    _mav_put_float(buf, 24, sync_KP);
    _mav_put_float(buf, 28, sync_KI);
    _mav_put_float(buf, 32, sync_KD);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_PID_PARAMS_LEN);
#else
    mavlink_pid_params_t packet;
    packet.whe0_KP = whe0_KP;
    packet.whe0_KI = whe0_KI;
    packet.whe0_KD = whe0_KD;
    packet.whe1_KP = whe1_KP;
    packet.whe1_KI = whe1_KI;
    packet.whe1_KD = whe1_KD;
    packet.sync_KP = sync_KP;
    packet.sync_KI = sync_KI;
    packet.sync_KD = sync_KD;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_PID_PARAMS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_PID_PARAMS;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_PID_PARAMS_MIN_LEN, MAVLINK_MSG_ID_PID_PARAMS_LEN, MAVLINK_MSG_ID_PID_PARAMS_CRC);
}

/**
 * @brief Encode a pid_params struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param pid_params C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_pid_params_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_pid_params_t* pid_params)
{
    return mavlink_msg_pid_params_pack(system_id, component_id, msg, pid_params->whe0_KP, pid_params->whe0_KI, pid_params->whe0_KD, pid_params->whe1_KP, pid_params->whe1_KI, pid_params->whe1_KD, pid_params->sync_KP, pid_params->sync_KI, pid_params->sync_KD);
}

/**
 * @brief Encode a pid_params struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param pid_params C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_pid_params_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_pid_params_t* pid_params)
{
    return mavlink_msg_pid_params_pack_chan(system_id, component_id, chan, msg, pid_params->whe0_KP, pid_params->whe0_KI, pid_params->whe0_KD, pid_params->whe1_KP, pid_params->whe1_KI, pid_params->whe1_KD, pid_params->sync_KP, pid_params->sync_KI, pid_params->sync_KD);
}

/**
 * @brief Send a pid_params message
 * @param chan MAVLink channel to send the message
 *
 * @param whe0_KP  Wheel 0 velocity control KP
 * @param whe0_KI  Wheel 0 velocity control KI
 * @param whe0_KD  Wheel 0 velocity control KD
 * @param whe1_KP  Wheel 1 velocity control KP
 * @param whe1_KI  Wheel 1 velocity control KI
 * @param whe1_KD  Wheel 1 velocity control KD
 * @param sync_KP  Synchronous control KP
 * @param sync_KI  Synchronous control KI
 * @param sync_KD  Synchronous control KD
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_pid_params_send(mavlink_channel_t chan, float whe0_KP, float whe0_KI, float whe0_KD, float whe1_KP, float whe1_KI, float whe1_KD, float sync_KP, float sync_KI, float sync_KD)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PID_PARAMS_LEN];
    _mav_put_float(buf, 0, whe0_KP);
    _mav_put_float(buf, 4, whe0_KI);
    _mav_put_float(buf, 8, whe0_KD);
    _mav_put_float(buf, 12, whe1_KP);
    _mav_put_float(buf, 16, whe1_KI);
    _mav_put_float(buf, 20, whe1_KD);
    _mav_put_float(buf, 24, sync_KP);
    _mav_put_float(buf, 28, sync_KI);
    _mav_put_float(buf, 32, sync_KD);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PID_PARAMS, buf, MAVLINK_MSG_ID_PID_PARAMS_MIN_LEN, MAVLINK_MSG_ID_PID_PARAMS_LEN, MAVLINK_MSG_ID_PID_PARAMS_CRC);
#else
    mavlink_pid_params_t packet;
    packet.whe0_KP = whe0_KP;
    packet.whe0_KI = whe0_KI;
    packet.whe0_KD = whe0_KD;
    packet.whe1_KP = whe1_KP;
    packet.whe1_KI = whe1_KI;
    packet.whe1_KD = whe1_KD;
    packet.sync_KP = sync_KP;
    packet.sync_KI = sync_KI;
    packet.sync_KD = sync_KD;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PID_PARAMS, (const char *)&packet, MAVLINK_MSG_ID_PID_PARAMS_MIN_LEN, MAVLINK_MSG_ID_PID_PARAMS_LEN, MAVLINK_MSG_ID_PID_PARAMS_CRC);
#endif
}

/**
 * @brief Send a pid_params message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_pid_params_send_struct(mavlink_channel_t chan, const mavlink_pid_params_t* pid_params)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_pid_params_send(chan, pid_params->whe0_KP, pid_params->whe0_KI, pid_params->whe0_KD, pid_params->whe1_KP, pid_params->whe1_KI, pid_params->whe1_KD, pid_params->sync_KP, pid_params->sync_KI, pid_params->sync_KD);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PID_PARAMS, (const char *)pid_params, MAVLINK_MSG_ID_PID_PARAMS_MIN_LEN, MAVLINK_MSG_ID_PID_PARAMS_LEN, MAVLINK_MSG_ID_PID_PARAMS_CRC);
#endif
}

#if MAVLINK_MSG_ID_PID_PARAMS_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_pid_params_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  float whe0_KP, float whe0_KI, float whe0_KD, float whe1_KP, float whe1_KI, float whe1_KD, float sync_KP, float sync_KI, float sync_KD)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, whe0_KP);
    _mav_put_float(buf, 4, whe0_KI);
    _mav_put_float(buf, 8, whe0_KD);
    _mav_put_float(buf, 12, whe1_KP);
    _mav_put_float(buf, 16, whe1_KI);
    _mav_put_float(buf, 20, whe1_KD);
    _mav_put_float(buf, 24, sync_KP);
    _mav_put_float(buf, 28, sync_KI);
    _mav_put_float(buf, 32, sync_KD);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PID_PARAMS, buf, MAVLINK_MSG_ID_PID_PARAMS_MIN_LEN, MAVLINK_MSG_ID_PID_PARAMS_LEN, MAVLINK_MSG_ID_PID_PARAMS_CRC);
#else
    mavlink_pid_params_t *packet = (mavlink_pid_params_t *)msgbuf;
    packet->whe0_KP = whe0_KP;
    packet->whe0_KI = whe0_KI;
    packet->whe0_KD = whe0_KD;
    packet->whe1_KP = whe1_KP;
    packet->whe1_KI = whe1_KI;
    packet->whe1_KD = whe1_KD;
    packet->sync_KP = sync_KP;
    packet->sync_KI = sync_KI;
    packet->sync_KD = sync_KD;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PID_PARAMS, (const char *)packet, MAVLINK_MSG_ID_PID_PARAMS_MIN_LEN, MAVLINK_MSG_ID_PID_PARAMS_LEN, MAVLINK_MSG_ID_PID_PARAMS_CRC);
#endif
}
#endif

#endif

// MESSAGE PID_PARAMS UNPACKING


/**
 * @brief Get field whe0_KP from pid_params message
 *
 * @return  Wheel 0 velocity control KP
 */
static inline float mavlink_msg_pid_params_get_whe0_KP(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field whe0_KI from pid_params message
 *
 * @return  Wheel 0 velocity control KI
 */
static inline float mavlink_msg_pid_params_get_whe0_KI(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field whe0_KD from pid_params message
 *
 * @return  Wheel 0 velocity control KD
 */
static inline float mavlink_msg_pid_params_get_whe0_KD(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field whe1_KP from pid_params message
 *
 * @return  Wheel 1 velocity control KP
 */
static inline float mavlink_msg_pid_params_get_whe1_KP(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Get field whe1_KI from pid_params message
 *
 * @return  Wheel 1 velocity control KI
 */
static inline float mavlink_msg_pid_params_get_whe1_KI(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  16);
}

/**
 * @brief Get field whe1_KD from pid_params message
 *
 * @return  Wheel 1 velocity control KD
 */
static inline float mavlink_msg_pid_params_get_whe1_KD(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  20);
}

/**
 * @brief Get field sync_KP from pid_params message
 *
 * @return  Synchronous control KP
 */
static inline float mavlink_msg_pid_params_get_sync_KP(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  24);
}

/**
 * @brief Get field sync_KI from pid_params message
 *
 * @return  Synchronous control KI
 */
static inline float mavlink_msg_pid_params_get_sync_KI(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  28);
}

/**
 * @brief Get field sync_KD from pid_params message
 *
 * @return  Synchronous control KD
 */
static inline float mavlink_msg_pid_params_get_sync_KD(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  32);
}

/**
 * @brief Decode a pid_params message into a struct
 *
 * @param msg The message to decode
 * @param pid_params C-struct to decode the message contents into
 */
static inline void mavlink_msg_pid_params_decode(const mavlink_message_t* msg, mavlink_pid_params_t* pid_params)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    pid_params->whe0_KP = mavlink_msg_pid_params_get_whe0_KP(msg);
    pid_params->whe0_KI = mavlink_msg_pid_params_get_whe0_KI(msg);
    pid_params->whe0_KD = mavlink_msg_pid_params_get_whe0_KD(msg);
    pid_params->whe1_KP = mavlink_msg_pid_params_get_whe1_KP(msg);
    pid_params->whe1_KI = mavlink_msg_pid_params_get_whe1_KI(msg);
    pid_params->whe1_KD = mavlink_msg_pid_params_get_whe1_KD(msg);
    pid_params->sync_KP = mavlink_msg_pid_params_get_sync_KP(msg);
    pid_params->sync_KI = mavlink_msg_pid_params_get_sync_KI(msg);
    pid_params->sync_KD = mavlink_msg_pid_params_get_sync_KD(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_PID_PARAMS_LEN? msg->len : MAVLINK_MSG_ID_PID_PARAMS_LEN;
        memset(pid_params, 0, MAVLINK_MSG_ID_PID_PARAMS_LEN);
    memcpy(pid_params, _MAV_PAYLOAD(msg), len);
#endif
}
