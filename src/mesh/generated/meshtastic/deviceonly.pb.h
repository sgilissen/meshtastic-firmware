/* Automatically generated nanopb header */
/* Generated by nanopb-0.4.7 */

#ifndef PB_MESHTASTIC_MESHTASTIC_DEVICEONLY_PB_H_INCLUDED
#define PB_MESHTASTIC_MESHTASTIC_DEVICEONLY_PB_H_INCLUDED
#include <pb.h>
#include "meshtastic/channel.pb.h"
#include "meshtastic/localonly.pb.h"
#include "meshtastic/mesh.pb.h"
#include "meshtastic/telemetry.pb.h"
#include "meshtastic/module_config.pb.h"

#if PB_PROTO_HEADER_VERSION != 40
#error Regenerate this file with the current version of nanopb generator.
#endif

/* Enum definitions */
/* TODO: REPLACE */
typedef enum _meshtastic_ScreenFonts {
    /* TODO: REPLACE */
    meshtastic_ScreenFonts_FONT_SMALL = 0,
    /* TODO: REPLACE */
    meshtastic_ScreenFonts_FONT_MEDIUM = 1,
    /* TODO: REPLACE */
    meshtastic_ScreenFonts_FONT_LARGE = 2
} meshtastic_ScreenFonts;

/* Struct definitions */
/* Position with static location information only for NodeDBLite */
typedef struct _meshtastic_PositionLite {
    /* The new preferred location encoding, multiply by 1e-7 to get degrees
 in floating point */
    int32_t latitude_i;
    /* TODO: REPLACE */
    int32_t longitude_i;
    /* In meters above MSL (but see issue #359) */
    int32_t altitude;
    /* This is usually not sent over the mesh (to save space), but it is sent
 from the phone so that the local device can set its RTC If it is sent over
 the mesh (because there are devices on the mesh without GPS), it will only
 be sent by devices which has a hardware GPS clock.
 seconds since 1970 */
    uint32_t time;
    /* TODO: REPLACE */
    meshtastic_Position_LocSource location_source;
} meshtastic_PositionLite;

typedef struct _meshtastic_NodeInfoLite {
    /* The node number */
    uint32_t num;
    /* The user info for this node */
    bool has_user;
    meshtastic_User user;
    /* This position data. Note: before 1.2.14 we would also store the last time we've heard from this node in position.time, that is no longer true.
 Position.time now indicates the last time we received a POSITION from that node. */
    bool has_position;
    meshtastic_PositionLite position;
    /* Returns the Signal-to-noise ratio (SNR) of the last received message,
 as measured by the receiver. Return SNR of the last received message in dB */
    float snr;
    /* Set to indicate the last time we received a packet from this node */
    uint32_t last_heard;
    /* The latest device metrics for the node. */
    bool has_device_metrics;
    meshtastic_DeviceMetrics device_metrics;
    /* local channel index we heard that node on. Only populated if its not the default channel. */
    uint8_t channel;
} meshtastic_NodeInfoLite;

/* The on-disk saved channels */
typedef struct _meshtastic_ChannelFile {
    /* The channels our node knows about */
    pb_size_t channels_count;
    meshtastic_Channel channels[8];
    /* A version integer used to invalidate old save files when we make
 incompatible changes This integer is set at build time and is private to
 NodeDB.cpp in the device code. */
    uint32_t version;
} meshtastic_ChannelFile;

typedef PB_BYTES_ARRAY_T(2048) meshtastic_OEMStore_oem_icon_bits_t;
typedef PB_BYTES_ARRAY_T(32) meshtastic_OEMStore_oem_aes_key_t;
/* This can be used for customizing the firmware distribution. If populated,
 show a secondary bootup screen with custom logo and text for 2.5 seconds. */
typedef struct _meshtastic_OEMStore {
    /* The Logo width in Px */
    uint32_t oem_icon_width;
    /* The Logo height in Px */
    uint32_t oem_icon_height;
    /* The Logo in XBM bytechar format */
    meshtastic_OEMStore_oem_icon_bits_t oem_icon_bits;
    /* Use this font for the OEM text. */
    meshtastic_ScreenFonts oem_font;
    /* Use this font for the OEM text. */
    char oem_text[40];
    /* The default device encryption key, 16 or 32 byte */
    meshtastic_OEMStore_oem_aes_key_t oem_aes_key;
    /* A Preset LocalConfig to apply during factory reset */
    bool has_oem_local_config;
    meshtastic_LocalConfig oem_local_config;
    /* A Preset LocalModuleConfig to apply during factory reset */
    bool has_oem_local_module_config;
    meshtastic_LocalModuleConfig oem_local_module_config;
} meshtastic_OEMStore;

/* RemoteHardwarePins associated with a node */
typedef struct _meshtastic_NodeRemoteHardwarePin {
    /* The node_num exposing the available gpio pin */
    uint32_t node_num;
    /* The the available gpio pin for usage with RemoteHardware module */
    bool has_pin;
    meshtastic_RemoteHardwarePin pin;
} meshtastic_NodeRemoteHardwarePin;

/* This message is never sent over the wire, but it is used for serializing DB
 state to flash in the device code
 FIXME, since we write this each time we enter deep sleep (and have infinite
 flash) it would be better to use some sort of append only data structure for
 the receive queue and use the preferences store for the other stuff */
typedef struct _meshtastic_DeviceState {
    /* Read only settings/info about this node */
    bool has_my_node;
    meshtastic_MyNodeInfo my_node;
    /* My owner info */
    bool has_owner;
    meshtastic_User owner;
    /* Received packets saved for delivery to the phone */
    pb_size_t receive_queue_count;
    meshtastic_MeshPacket receive_queue[1];
    /* We keep the last received text message (only) stored in the device flash,
 so we can show it on the screen.
 Might be null */
    bool has_rx_text_message;
    meshtastic_MeshPacket rx_text_message;
    /* A version integer used to invalidate old save files when we make
 incompatible changes This integer is set at build time and is private to
 NodeDB.cpp in the device code. */
    uint32_t version;
    /* Used only during development.
 Indicates developer is testing and changes should never be saved to flash. */
    bool no_save;
    /* Some GPS receivers seem to have bogus settings from the factory, so we always do one factory reset. */
    bool did_gps_reset;
    /* We keep the last received waypoint stored in the device flash,
 so we can show it on the screen.
 Might be null */
    bool has_rx_waypoint;
    meshtastic_MeshPacket rx_waypoint;
    /* The mesh's nodes with their available gpio pins for RemoteHardware module */
    pb_size_t node_remote_hardware_pins_count;
    meshtastic_NodeRemoteHardwarePin node_remote_hardware_pins[12];
    /* New lite version of NodeDB to decrease memory footprint */
    pb_size_t node_db_lite_count;
    meshtastic_NodeInfoLite node_db_lite[100];
} meshtastic_DeviceState;


#ifdef __cplusplus
extern "C" {
#endif

/* Helper constants for enums */
#define _meshtastic_ScreenFonts_MIN meshtastic_ScreenFonts_FONT_SMALL
#define _meshtastic_ScreenFonts_MAX meshtastic_ScreenFonts_FONT_LARGE
#define _meshtastic_ScreenFonts_ARRAYSIZE ((meshtastic_ScreenFonts)(meshtastic_ScreenFonts_FONT_LARGE+1))



#define meshtastic_PositionLite_location_source_ENUMTYPE meshtastic_Position_LocSource


#define meshtastic_OEMStore_oem_font_ENUMTYPE meshtastic_ScreenFonts



/* Initializer values for message structs */
#define meshtastic_DeviceState_init_default      {false, meshtastic_MyNodeInfo_init_default, false, meshtastic_User_init_default, 0, {meshtastic_MeshPacket_init_default}, false, meshtastic_MeshPacket_init_default, 0, 0, 0, false, meshtastic_MeshPacket_init_default, 0, {meshtastic_NodeRemoteHardwarePin_init_default, meshtastic_NodeRemoteHardwarePin_init_default, meshtastic_NodeRemoteHardwarePin_init_default, meshtastic_NodeRemoteHardwarePin_init_default, meshtastic_NodeRemoteHardwarePin_init_default, meshtastic_NodeRemoteHardwarePin_init_default, meshtastic_NodeRemoteHardwarePin_init_default, meshtastic_NodeRemoteHardwarePin_init_default, meshtastic_NodeRemoteHardwarePin_init_default, meshtastic_NodeRemoteHardwarePin_init_default, meshtastic_NodeRemoteHardwarePin_init_default, meshtastic_NodeRemoteHardwarePin_init_default}, 0, {meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default, meshtastic_NodeInfoLite_init_default}}
#define meshtastic_NodeInfoLite_init_default     {0, false, meshtastic_User_init_default, false, meshtastic_PositionLite_init_default, 0, 0, false, meshtastic_DeviceMetrics_init_default, 0}
#define meshtastic_PositionLite_init_default     {0, 0, 0, 0, _meshtastic_Position_LocSource_MIN}
#define meshtastic_ChannelFile_init_default      {0, {meshtastic_Channel_init_default, meshtastic_Channel_init_default, meshtastic_Channel_init_default, meshtastic_Channel_init_default, meshtastic_Channel_init_default, meshtastic_Channel_init_default, meshtastic_Channel_init_default, meshtastic_Channel_init_default}, 0}
#define meshtastic_OEMStore_init_default         {0, 0, {0, {0}}, _meshtastic_ScreenFonts_MIN, "", {0, {0}}, false, meshtastic_LocalConfig_init_default, false, meshtastic_LocalModuleConfig_init_default}
#define meshtastic_NodeRemoteHardwarePin_init_default {0, false, meshtastic_RemoteHardwarePin_init_default}
#define meshtastic_DeviceState_init_zero         {false, meshtastic_MyNodeInfo_init_zero, false, meshtastic_User_init_zero, 0, {meshtastic_MeshPacket_init_zero}, false, meshtastic_MeshPacket_init_zero, 0, 0, 0, false, meshtastic_MeshPacket_init_zero, 0, {meshtastic_NodeRemoteHardwarePin_init_zero, meshtastic_NodeRemoteHardwarePin_init_zero, meshtastic_NodeRemoteHardwarePin_init_zero, meshtastic_NodeRemoteHardwarePin_init_zero, meshtastic_NodeRemoteHardwarePin_init_zero, meshtastic_NodeRemoteHardwarePin_init_zero, meshtastic_NodeRemoteHardwarePin_init_zero, meshtastic_NodeRemoteHardwarePin_init_zero, meshtastic_NodeRemoteHardwarePin_init_zero, meshtastic_NodeRemoteHardwarePin_init_zero, meshtastic_NodeRemoteHardwarePin_init_zero, meshtastic_NodeRemoteHardwarePin_init_zero}, 0, {meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero, meshtastic_NodeInfoLite_init_zero}}
#define meshtastic_NodeInfoLite_init_zero        {0, false, meshtastic_User_init_zero, false, meshtastic_PositionLite_init_zero, 0, 0, false, meshtastic_DeviceMetrics_init_zero, 0}
#define meshtastic_PositionLite_init_zero        {0, 0, 0, 0, _meshtastic_Position_LocSource_MIN}
#define meshtastic_ChannelFile_init_zero         {0, {meshtastic_Channel_init_zero, meshtastic_Channel_init_zero, meshtastic_Channel_init_zero, meshtastic_Channel_init_zero, meshtastic_Channel_init_zero, meshtastic_Channel_init_zero, meshtastic_Channel_init_zero, meshtastic_Channel_init_zero}, 0}
#define meshtastic_OEMStore_init_zero            {0, 0, {0, {0}}, _meshtastic_ScreenFonts_MIN, "", {0, {0}}, false, meshtastic_LocalConfig_init_zero, false, meshtastic_LocalModuleConfig_init_zero}
#define meshtastic_NodeRemoteHardwarePin_init_zero {0, false, meshtastic_RemoteHardwarePin_init_zero}

/* Field tags (for use in manual encoding/decoding) */
#define meshtastic_PositionLite_latitude_i_tag   1
#define meshtastic_PositionLite_longitude_i_tag  2
#define meshtastic_PositionLite_altitude_tag     3
#define meshtastic_PositionLite_time_tag         4
#define meshtastic_PositionLite_location_source_tag 5
#define meshtastic_NodeInfoLite_num_tag          1
#define meshtastic_NodeInfoLite_user_tag         2
#define meshtastic_NodeInfoLite_position_tag     3
#define meshtastic_NodeInfoLite_snr_tag          4
#define meshtastic_NodeInfoLite_last_heard_tag   5
#define meshtastic_NodeInfoLite_device_metrics_tag 6
#define meshtastic_NodeInfoLite_channel_tag      7
#define meshtastic_ChannelFile_channels_tag      1
#define meshtastic_ChannelFile_version_tag       2
#define meshtastic_OEMStore_oem_icon_width_tag   1
#define meshtastic_OEMStore_oem_icon_height_tag  2
#define meshtastic_OEMStore_oem_icon_bits_tag    3
#define meshtastic_OEMStore_oem_font_tag         4
#define meshtastic_OEMStore_oem_text_tag         5
#define meshtastic_OEMStore_oem_aes_key_tag      6
#define meshtastic_OEMStore_oem_local_config_tag 7
#define meshtastic_OEMStore_oem_local_module_config_tag 8
#define meshtastic_NodeRemoteHardwarePin_node_num_tag 1
#define meshtastic_NodeRemoteHardwarePin_pin_tag 2
#define meshtastic_DeviceState_my_node_tag       2
#define meshtastic_DeviceState_owner_tag         3
#define meshtastic_DeviceState_receive_queue_tag 5
#define meshtastic_DeviceState_rx_text_message_tag 7
#define meshtastic_DeviceState_version_tag       8
#define meshtastic_DeviceState_no_save_tag       9
#define meshtastic_DeviceState_did_gps_reset_tag 11
#define meshtastic_DeviceState_rx_waypoint_tag   12
#define meshtastic_DeviceState_node_remote_hardware_pins_tag 13
#define meshtastic_DeviceState_node_db_lite_tag  14

/* Struct field encoding specification for nanopb */
#define meshtastic_DeviceState_FIELDLIST(X, a) \
X(a, STATIC,   OPTIONAL, MESSAGE,  my_node,           2) \
X(a, STATIC,   OPTIONAL, MESSAGE,  owner,             3) \
X(a, STATIC,   REPEATED, MESSAGE,  receive_queue,     5) \
X(a, STATIC,   OPTIONAL, MESSAGE,  rx_text_message,   7) \
X(a, STATIC,   SINGULAR, UINT32,   version,           8) \
X(a, STATIC,   SINGULAR, BOOL,     no_save,           9) \
X(a, STATIC,   SINGULAR, BOOL,     did_gps_reset,    11) \
X(a, STATIC,   OPTIONAL, MESSAGE,  rx_waypoint,      12) \
X(a, STATIC,   REPEATED, MESSAGE,  node_remote_hardware_pins,  13) \
X(a, STATIC,   REPEATED, MESSAGE,  node_db_lite,     14)
#define meshtastic_DeviceState_CALLBACK NULL
#define meshtastic_DeviceState_DEFAULT NULL
#define meshtastic_DeviceState_my_node_MSGTYPE meshtastic_MyNodeInfo
#define meshtastic_DeviceState_owner_MSGTYPE meshtastic_User
#define meshtastic_DeviceState_receive_queue_MSGTYPE meshtastic_MeshPacket
#define meshtastic_DeviceState_rx_text_message_MSGTYPE meshtastic_MeshPacket
#define meshtastic_DeviceState_rx_waypoint_MSGTYPE meshtastic_MeshPacket
#define meshtastic_DeviceState_node_remote_hardware_pins_MSGTYPE meshtastic_NodeRemoteHardwarePin
#define meshtastic_DeviceState_node_db_lite_MSGTYPE meshtastic_NodeInfoLite

#define meshtastic_NodeInfoLite_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, UINT32,   num,               1) \
X(a, STATIC,   OPTIONAL, MESSAGE,  user,              2) \
X(a, STATIC,   OPTIONAL, MESSAGE,  position,          3) \
X(a, STATIC,   SINGULAR, FLOAT,    snr,               4) \
X(a, STATIC,   SINGULAR, FIXED32,  last_heard,        5) \
X(a, STATIC,   OPTIONAL, MESSAGE,  device_metrics,    6) \
X(a, STATIC,   SINGULAR, UINT32,   channel,           7)
#define meshtastic_NodeInfoLite_CALLBACK NULL
#define meshtastic_NodeInfoLite_DEFAULT NULL
#define meshtastic_NodeInfoLite_user_MSGTYPE meshtastic_User
#define meshtastic_NodeInfoLite_position_MSGTYPE meshtastic_PositionLite
#define meshtastic_NodeInfoLite_device_metrics_MSGTYPE meshtastic_DeviceMetrics

#define meshtastic_PositionLite_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, SFIXED32, latitude_i,        1) \
X(a, STATIC,   SINGULAR, SFIXED32, longitude_i,       2) \
X(a, STATIC,   SINGULAR, INT32,    altitude,          3) \
X(a, STATIC,   SINGULAR, FIXED32,  time,              4) \
X(a, STATIC,   SINGULAR, UENUM,    location_source,   5)
#define meshtastic_PositionLite_CALLBACK NULL
#define meshtastic_PositionLite_DEFAULT NULL

#define meshtastic_ChannelFile_FIELDLIST(X, a) \
X(a, STATIC,   REPEATED, MESSAGE,  channels,          1) \
X(a, STATIC,   SINGULAR, UINT32,   version,           2)
#define meshtastic_ChannelFile_CALLBACK NULL
#define meshtastic_ChannelFile_DEFAULT NULL
#define meshtastic_ChannelFile_channels_MSGTYPE meshtastic_Channel

#define meshtastic_OEMStore_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, UINT32,   oem_icon_width,    1) \
X(a, STATIC,   SINGULAR, UINT32,   oem_icon_height,   2) \
X(a, STATIC,   SINGULAR, BYTES,    oem_icon_bits,     3) \
X(a, STATIC,   SINGULAR, UENUM,    oem_font,          4) \
X(a, STATIC,   SINGULAR, STRING,   oem_text,          5) \
X(a, STATIC,   SINGULAR, BYTES,    oem_aes_key,       6) \
X(a, STATIC,   OPTIONAL, MESSAGE,  oem_local_config,   7) \
X(a, STATIC,   OPTIONAL, MESSAGE,  oem_local_module_config,   8)
#define meshtastic_OEMStore_CALLBACK NULL
#define meshtastic_OEMStore_DEFAULT NULL
#define meshtastic_OEMStore_oem_local_config_MSGTYPE meshtastic_LocalConfig
#define meshtastic_OEMStore_oem_local_module_config_MSGTYPE meshtastic_LocalModuleConfig

#define meshtastic_NodeRemoteHardwarePin_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, UINT32,   node_num,          1) \
X(a, STATIC,   OPTIONAL, MESSAGE,  pin,               2)
#define meshtastic_NodeRemoteHardwarePin_CALLBACK NULL
#define meshtastic_NodeRemoteHardwarePin_DEFAULT NULL
#define meshtastic_NodeRemoteHardwarePin_pin_MSGTYPE meshtastic_RemoteHardwarePin

extern const pb_msgdesc_t meshtastic_DeviceState_msg;
extern const pb_msgdesc_t meshtastic_NodeInfoLite_msg;
extern const pb_msgdesc_t meshtastic_PositionLite_msg;
extern const pb_msgdesc_t meshtastic_ChannelFile_msg;
extern const pb_msgdesc_t meshtastic_OEMStore_msg;
extern const pb_msgdesc_t meshtastic_NodeRemoteHardwarePin_msg;

/* Defines for backwards compatibility with code written before nanopb-0.4.0 */
#define meshtastic_DeviceState_fields &meshtastic_DeviceState_msg
#define meshtastic_NodeInfoLite_fields &meshtastic_NodeInfoLite_msg
#define meshtastic_PositionLite_fields &meshtastic_PositionLite_msg
#define meshtastic_ChannelFile_fields &meshtastic_ChannelFile_msg
#define meshtastic_OEMStore_fields &meshtastic_OEMStore_msg
#define meshtastic_NodeRemoteHardwarePin_fields &meshtastic_NodeRemoteHardwarePin_msg

/* Maximum encoded size of messages (where known) */
#define meshtastic_ChannelFile_size              702
#define meshtastic_DeviceState_size              17062
#define meshtastic_NodeInfoLite_size             153
#define meshtastic_NodeRemoteHardwarePin_size    29
#define meshtastic_OEMStore_size                 3246
#define meshtastic_PositionLite_size             28

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
