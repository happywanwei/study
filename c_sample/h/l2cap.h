/* 
 * l2cap.h --  Implementation of Bluetooth Logical Link Control 
 *             and Adaption Protocol (L2CAP)          
 **********************************************************************/ 

#ifndef L2CAP_H
#define L2CAP_H

/****************** INCLUDE FILES SECTION ***********************************/
#ifdef __KERNEL__
#include <linux/bluetooth/btcommon.h>
#include <linux/types.h>
#else
#include "btcommon.h"
#endif
/****************** CONSTANT AND MACRO SECTION ******************************/

#define MAX_L2CAPSIZE 2048

#define L2CAP_CON_MAGIC 0xb055e

#define PARANOIA_CHECKCON(con) (!con || (con->magic!=L2CAP_CON_MAGIC))

#define FALSE 0
#define TRUE 1

#define MTU_MIN 48
#define MTU_DEFAULT 672
#define FLUSHTIMEOUT_DEFAULT 0xffff /* Always retransmit */

#define MAX_CMD_ID 255

/* Valid PSM values */
#define MAX_PSM 8
#define SDP_LAYER 1
#define RFCOMM_LAYER 3
#define TCS_LAYER 5

#define L2CAP_TEST_LAYER 0x1231
#define L2CAP_TEST2_LAYER 0x1233
#define L2CAP_TEST3_LAYER 0x4561

#define MIN_DYNAMIC_PSM 0x1001
#define MAX_DYNAMIC_PSM 0xFFFF

/* Result in respones in L2CAP */
#define RES_SUCCESS 0x0
#define RES_PENDING 0x01
#define RES_PSMNEG 0x02
#define RES_SECNEG 0x03
#define RES_NOSRC 0x04

#define STAT_NOINFO 0x0
#define STAT_AUTHENTPEND 0x01
#define STAT_AUTHORPEND 0x02

/* The different state in l2cap */
#define CLOSED 0
#define W4_L2CAP_CONNECT_RSP 1
#define W4_L2CA_CONNECT_RSP 2
#define CONFIG 3
#define OPEN 4
#define W4_L2CAP_DISCONNECT_RSP 5
#define W4_L2CA_DISCONNECT_RSP 6
#define ANY_STATE 7

#define CIDNULL 0x0
#define CIDSIG 0x1
#define CIDRCVCONLESS 0x2 /* Connection less reception channel */

#define CONF_SUCCESS 0x0
#define CONF_FAILURE 0x1
#define CONF_REJ 0x2
#define CONF_UNKNOWN 0x3
 
#define OPT_MTU 0x1
#define OPT_FLUSH 0x2
#define OPT_QOS 0x3

/* Information Signalling stuff */

/* info req types */
#define INFO_CONNLESS_MTU 0x0001

/* info rsp codes */
#define INFO_RSP_SUCCESS 0x1
#define INFO_RSP_NOSUPP 0x02

/* L2CAP Signalling codes */
#define SIG_RESERVED 0x00
#define SIG_CMDREJECT 0x01
#define SIG_CONREQ 0x02
#define SIG_CONRSP 0x03
#define SIG_CONFREQ 0x04
#define SIG_CONFRSP 0x05
#define SIG_DISCREQ 0x06
#define SIG_DISCRSP 0x07
#define SIG_ECHOREQ 0x08
#define SIG_ECHORSP 0x09
#define SIG_INFOREQ 0x0A
#define SIG_INFORSP 0x0B

#define L2CAP_HDRSIZE sizeof(l2cap_packet)
#define SIGCMD_HDRSIZE sizeof(sig_cmd)

/* Response */
#define CON_RSPSIZE sizeof(sig_conrsp)
#define CONF_RSPSIZE sizeof(sig_confrsp)

/* Request */
#define CON_REQSIZE sizeof(sig_conreq)
#define CONF_REQSIZE sizeof(sig_confreq)
#define DISC_REQSIZE sizeof(sig_discreq)


/****************** TYPE DEFINITION SECTION *********************************/

/****************** EXPORTED FUNCTION DECLARATION SECTION *******************/

/******************/
/* l2cap protocol */
/******************/

typedef struct l2cap_layer {
	s32 initiated;
	BD_ADDR my_bd;
	protocol_layer *upper_layers;
	u16 mtu; /* Not negotiable, more of an informational parameter */
	u16 flush_timeout;
	struct flow qos;
	u16 cid_count;
	u32 id_count; /* FIXME - Use one id_count for all hci handles for now,
			 add separate for each handle when MULTIPOINT */  
	u8 allow_conless; /* determines whether connectionless traffic is 
			     allowed*/
} l2cap_layer;

typedef struct l2cap_packet {
	u16 len; /* Length payload excl l2cap header */
	CID cid; /* destination CID */
	u8 data[0]; 
} l2cap_packet;

typedef struct l2cap_option
{
	u8 type;
	u8 len; /* payload length */
	u8 option_data[0];
} l2cap_option;


/**************/
/* SIGNALLING */
/**************/

typedef struct sig_cmd {
	u8 code;
	u8 id;
	u16 len;
	u8 data[0];
} sig_cmd;

/* Signalling requests */

typedef struct sig_conreq {
	u16 psm;
	CID src_cid; /* sending rsp */
} sig_conreq;

typedef struct sig_confreq {
	CID dst_cid; /* sending rsp */
	u16 flags;
	u8 options[0];
} sig_confreq;

typedef struct sig_discreq {
	CID dst_cid; /* receiving rsp */
	CID src_cid; /* sending rsp */
} sig_discreq;

typedef struct sig_info_req {
	u16 type;
} sig_info_req;

/* Signalling responses */

typedef struct sig_cmdreject {
	u16 reason;
	u8 data[0];
} sig_cmdreject;

 
typedef struct sig_conrsp {
	CID dst_cid; /* sending rsp*/
	CID src_cid; /* receiving rsp */
	u16 result;
	u16 status;
} sig_conrsp;

typedef struct sig_confrsp {
	CID src_cid; /* receiving rsp */
	u16 flags;
	u16 result;
	u8 options[0];
} sig_confrsp;


typedef struct sig_discrsp {
	CID dst_cid; /* sending rsp */
	CID src_cid; /* receiving rsp */
} sig_discrsp;

/* use same struct for both req and rsp */
typedef struct sig_echo_pkt {
	u8 data[0];
} sig_echo_pkt;


typedef struct sig_info_rsp {
	u16 type;
	u16 result;
	u8 infodata[0];
} sig_info_rsp;



/* Start timer rtx when sending signalling request */
/* If expired, resend message */

/*********************************************************************/
/*---------------------- INIT AND SHUTDOWN --------------------------*/
/*********************************************************************/

s32 l2cap_init(void);
s32 l2cap_shutdown(void);
s32 l2cap_register_upper(u16 psm, struct protocol_layer *prot);
void l2cap_protocol_default(struct protocol_layer *prot);

void not_registered_cfm(l2cap_con *con, s32 status);
void not_registered_cfm_noparams(l2cap_con *con);
void not_registered_ind(l2cap_con *con);
void not_registered_rcv(l2cap_con *con, u8 *data, u32 len);
// void init_flow(flow *f);

/* /proc sprint functions */
s32 l2cap_sprint_status(u8 *buf);
s32 l2cap_sprint_bd(u8 *buf, BD_ADDR bd);

/****************************************************************/
/*---------------------- STATE MACHINE -------------------------*/
/****************************************************************/

/* Collects hci packets from HCI and reassebles them to l2cap packets */
 
void l2cap_receive_data(u8 *data,  u32 len, u16 hci_handle, u32 *l2cap_len);

void signal_handler(u16 hci_handle, u8 *data, u32 len);

void process_request(u16 hci_handle, struct sig_cmd *req);

void process_response(u16 hci_handle, struct sig_cmd *req);


/*******************************************************************/
/*-------------------------- EVENTS -------------------------------*/
/*******************************************************************/

/*******************************************************************/
/* (E1) Lower layer to l2cap */
/****************************/

/* Confirms the request to establish a lower layer (baseband) connection*/
void lp_connect_cfm(u8 *bd_addr, u32 status, u16 con_hdl);

/* Indicates the lower protocol has successfully established connection */
void lp_connect_ind(BD_ADDR bd_addr);

/* called from hci when baseband is up (server) */
void l2cap_create_con(BD_ADDR bd);

/* Indicates the baseband has been shutdown */
void lp_disconnect_ind(u32 con_hdl);

/* FIXME - lp_qos_cfm() */
/* FIXME - lp_qos_violation_ind() */


/********************************************************************/
/* (E2) l2cap to l2cap signalling */
/*********************************/

s32 l2cap_connect_req(l2cap_con *con, u16 psm);

s32 l2cap_connect_rsp(l2cap_con* con, u16 response, 
                      u16 status);

/* FIXME l2cap_connect_rsp_pnd() */

s32 l2cap_config_req(l2cap_con *con, u16 in_mtu,
                     flow  *outflow, u16 flush_timeout,
                     u16 link_timeout);

s32 l2cap_config_rsp(l2cap_con* con, u32 out_mtu, 
                     flow *in_flow);

s32 l2cap_disconnect_req(l2cap_con *con);

s32 l2cap_disconnect_rsp(l2cap_con* con);

/*******************************************************************/
/*  (E3) Data from peers */
/************************/

void process_frame(struct l2cap_con *con, u8 *data, 
		   u32 len);

/**************************************************************/
/* (E4) Upper layers to l2cap */
/*****************************/

s32 l2ca_connect_req(BD_ADDR bd, u16 psm);
s32 l2ca_connect_rsp(l2cap_con* con, u16 response, 
		     u16 status);

s32 l2ca_config_req(l2cap_con *con, u16 in_mtu, flow *outflow, 
		    u16 flush_timeout, u16 link_timeout);

/* 'ok=0' handles 'l2ca_config_rsp_neg'... */
s32 l2ca_config_rsp(l2cap_con* con, u32 out_mtu, flow *in_flow, s32 ok);
 
s32 l2ca_disconnect_req(l2cap_con *con);
s32 l2ca_disconnect_rsp(l2cap_con *con);

s32 l2ca_ping(BD_ADDR bd);
s32 l2cap_echo_req(l2cap_con *con, u8 *opt_data, s32 opt_len);


s32 l2ca_getinfo(BD_ADDR bd, u16 infotype);
s32 l2cap_info_req(l2cap_con *con, u16 info_type);
s32 l2cap_info_rsp(s32 hci_hdl, s32 id, u16 info_type, u8 *info_data, 
		   s32 info_len, s32 result);


/**************************************************************/
/* (E5) Timer events  */
/**********************/

/* FIXME */
/* RTX timer */
/* ERTX timer */

/*******************************************************************/
/*-------------------------- ACTIONS ------------------------------*/
/*******************************************************************/

/*******************************************************************/
/* (A1) l2cap to lower layers */
/*****************************/

/* lp_connect_req () in hci.h */

/* FIXME - lp_qos_req() */

/* lp_connect_rsp() in hci.h */


/*******************************************************************/
/* (A2) l2cap to l2cap signalling */
/**********************************/

/* See events */

/*******************************************************************/
/* (A3) l2cap to l2cap data transmission */
/*****************************************/

s32 l2cap_send_data(bt_tx_buf *tx, l2cap_con *con);

/*******************************************************************/
/* (A4) l2cap to upper layers */
/*****************************/
 
void l2ca_connect_ind(l2cap_con *con);
void l2ca_connect_pnd(l2cap_con *con, s32 status);
void l2ca_connect_cfm(l2cap_con *con, s32 result);

void l2ca_config_ind(l2cap_con *con);
void l2ca_config_cfm(l2cap_con *con, s32 result);

void l2ca_disconnect_ind(l2cap_con *con);
void l2ca_disconnect_cfm(l2cap_con *con);

/* FIXME */
void l2ca_timeout_ind(l2cap_con *con);

/* FIXME */
void l2ca_qos_violation_ind(l2cap_con *con);

void l2ca_ping_rsp(u8* data, u32 len, BD_ADDR remote_bd);

int l2ca_opened(l2cap_con *con);

int l2ca_remote_conf_done(l2cap_con *con);

int l2ca_local_conf_done(l2cap_con *con);


/*******************************************************************/
/* (A5) setting timers */
/***********************/

/* GROUP functions not implemented */
/* INFO functions not implemented */
/* CONNECTIONLESS functions not implemented */

 
#endif
/****************** END OF FILE l2cap.h *************************************/
