// Copyright (c) 2020-present,  INSPUR Co, Ltd.  All rights reserved.

#ifndef KWDBTS_SERVER_SRC_H_MA_CGO_H_
#define KWDBTS_SERVER_SRC_H_MA_CGO_H_

#ifdef __cplusplus
extern "C" {
#endif

  #define CGO_DEFAULT_IP_MAX_NUM    64
  #define CGO_DEFAULT_PORT_MAX_NUM  50
  #define CGO_DEFAULT_KWDBT_MAX_NUM  255
  #define CGO_DEFAULT_NAME_MAX_NUM  255

  int process_kwdb_me(int argc, char *argv[]);

  void handle_me_signal(int sig);

  // start ME only
  int cgo_start_me(unsigned char is_e_mode);

  // start ME and TS
  // TODO(xiabohan): will remove the function of cgo_start_me_ts after demo.
  // AE shoud be started on demand.
  // Adding start AE from ME based on request type.
  int cgo_start_me_ts(unsigned char is_e_mode, unsigned char is_initial);

  // stop E side ME( if TS exist, will stop TS)
  void kwdbe_stop();
  // start E side ts
  void kwdbe_start_ts();
  // stop E side ts
  void kwdbe_stop_ts();

  /**
  * @brief send msg to all ME(include KWDBE_ME)
  * @param[in]  pStr bussiness data
  * @param[in]  nstrLen bussiness data's length
  * @param[in]  szInnType inner model's operation type
  * @param[in]  szSubType related model's type
  * @param[in]  szType inner connect data type 'g'
  * @return  success 0, failed -1
  * TODO(jinmou): if we need list all failed ip?
  */
  int cgo_send_to_all_me(char *pStr, int nstrLen, char szInnType, char szSubType, char **result, int* resLen);

  // get inner connection ID
  int get_inner_conn_id(int logic_id, cgo_uint64 *conn_id);

  // get outer connection ID
  int get_conn_id(cgo_uint64 *conn_id);

  // init connection data
  int init_connection(cgo_uint64 conn_id, cgo_int64 token, cgo_int64 goroutine_id);

  // release connection data
  int release_connection(cgo_uint64 connID);

  // get token
  long long int get_token(unsigned long long int connID);  // NOLINT runtime/int

  // notify me open to work
  void notify_me_open_towork();

  /**
   * @brief send msg to AE by ts_message_queue
   * @param[in]  value send info , malloc from share memory
   * @return  success 1, failed 0
   */
  int send_msg_to_ae(char *value);

  /**
   * @brief block and wait me startup
   * @return  startup succeed 0, failed -1
  */
  int cgo_wait_me_startup_result();

    /**
   * @brief block and notify me to stop ae client
   * @return  startup succeed 0, failed -1
  */
  int cgo_notify_ae_stop_client();

  // kwdbe_get_ae_ts_if_alive checks if Ae_Ts is running
  int kwdbe_get_ae_ts_if_alive();

  /**
   * @brief send workloadinfo to AE by workloadinfo_message_queue
   * @param[in]  value send info , malloc from share memory
   * @return  success 1, failed 0
   */
   int send_workloadinfo_to_ae(char *value);
  
  /**
   * @brief get current device descriptor
   * @return deviceDescriptor
  */
  typedef struct {
    char internalIp_[CGO_DEFAULT_IP_MAX_NUM];
    unsigned int internalPort_;
    unsigned int agentInternalPort_[CGO_DEFAULT_PORT_MAX_NUM];
    unsigned int storageInternalPort_;
    char nodeExternalIp_[CGO_DEFAULT_IP_MAX_NUM];
    unsigned int nodeExternalPort_;
    unsigned int agentExternalPort_[CGO_DEFAULT_PORT_MAX_NUM];
    unsigned int storageExternalPort_;
    char kwdbtList_[CGO_DEFAULT_KWDBT_MAX_NUM];
    char portalName_[CGO_DEFAULT_NAME_MAX_NUM];
    int role_;
  }meDeviceDescriptor;

  void cgo_get_device_descriptor(meDeviceDescriptor* pDevice, int kwdbType_, char* key_);
  
  /**
   * @brief get error string
   * @param[in]  conn_id connnect id
   * @return  error string
   */
  const char * get_last_error_string(unsigned long long int conn_id);  // NOLINT runtime/int
#ifdef __cplusplus
}
#endif

#endif  // KWDBTS_SERVER_SRC_H_MA_CGO_H_
