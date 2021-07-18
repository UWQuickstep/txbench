#ifndef TXBENCH_SRC_BENCHMARKS_TATP_TATP_CONNECTION_H
#define TXBENCH_SRC_BENCHMARKS_TATP_TATP_CONNECTION_H

#include <array>
#include <string>

class TATPConnection {
 public:
  virtual ~TATPConnection() = default;

  virtual void done_loading() {}
  // Loading functions.

  virtual void new_subscriber_row(int s_id, std::string sub_nbr,
                                  std::array<bool, 10> bit,
                                  std::array<int, 10> hex,
                                  std::array<int, 10> byte2, int msc_location,
                                  int vlr_location) = 0;

  virtual void new_access_info_row(int s_id, int ai_type, int data1, int data2,
                                   std::string data3, std::string data4) = 0;

  virtual void new_special_facility_row(int s_id, int sf_type, bool is_active,
                                        int error_cntrl, int data_a,
                                        std::string data_b) = 0;

  virtual void new_call_forwarding_row(int s_id, int sf_type, int start_time,
                                       int end_time, std::string numberx) = 0;

  // Benchmark functions.

  virtual void get_subscriber_data(int s_id, std::string *sub_nbr,
                                   std::array<bool, 10> &bit,
                                   std::array<int, 10> &hex,
                                   std::array<int, 10> &byte2,
                                   int *msc_location, int *vlr_location) = 0;

  virtual void get_new_destination(int s_id,
                                   int sf_type,
                                   int start_time,
                                   int end_time,
                                   std::vector<std::string> *numberx) = 0;

  virtual void get_access_data(int s_id, int ai_type, int *data1, int *data2,
                               std::string *data3, std::string *data4) = 0;

  virtual void update_subscriber_data(int s_id, bool bit_1, int sf_type,
                                      int data_a) = 0;

  virtual void update_location(const std::string &sub_nbr,
                               int vlr_location) = 0;

  virtual void insert_call_forwarding(std::string sub_nbr, int sf_type,
                                      int start_time, int end_time,
                                      std::string numberx) = 0;

  virtual void delete_call_forwarding(const std::string &sub_nbr, int sf_type,
                                      int start_time) = 0;
};

#endif // TXBENCH_SRC_BENCHMARKS_TATP_TATP_CONNECTION_H
