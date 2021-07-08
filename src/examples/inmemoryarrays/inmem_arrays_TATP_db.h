#ifndef TXBENCH_SRC_EXAMPLES_INMEMORYARRAYS_INMEMARRAYSTATPDB_H_
#define TXBENCH_SRC_EXAMPLES_INMEMORYARRAYS_INMEMARRAYSTATPDB_H_

#include <vector>
#include <memory>
#include <string>
#include <array>

struct SRow {
  int s_id;
  std::string sub_nbr;
  std::array<bool, 10> bit;
  std::array<int, 10> hex;
  std::array<int, 10> byte2;
  int msc_location;
  int vlr_location;
  SRow(int s_id,
       const std::string &sub_nbr,
       const std::array<bool, 10> &bit,
       const std::array<int, 10> &hex,
       const std::array<int, 10> &byte_2,
       int msc_location,
       int vlr_location);
};

struct AIRow {
  int s_id;
  int ai_type;
  int data1;
  int data2;
  std::string data3;
  std::string data4;
  AIRow(int s_id,
        int ai_type,
        int data_1,
        int data_2,
        const std::string &data_3,
        const std::string &data_4);
};

struct SFRow {
  int s_id;
  int sf_type;
  bool is_active;
  int error_cntrl;
  int data_a;
  std::string data_b;
  SFRow(int s_id,
        int sf_type,
        bool is_active,
        int error_cntrl,
        int data_a,
        const std::string &data_b);
};

struct CFRow {
  int s_id;
  int sf_type;
  int start_time;
  int end_time;
  std::string numberx;
  CFRow(int s_id,
        int sf_type,
        int start_time,
        int end_time,
        const std::string &numberx);
};

struct Tx1Res {
  int s_id;
  std::string sub_nbr;
  std::array<bool, 10> bit;
  std::array<int, 10> hex;
  std::array<int, 10> byte2;
  int msc_location;
  int vlr_location;
};

struct Tx2Res {
  std::vector<std::string> numberx;
};

struct Tx3Res {
  std::vector<int> data1;
  std::vector<int> data2;
  std::vector<std::string> data3;
  std::vector<std::string> data4;
};

class InMemArraysTATPDB {
 public:

  InMemArraysTATPDB() {}

  void print_stats();

  void new_subscriber_row(int s_id, std::string sub_nbr,
                          std::array<bool, 10> bit, std::array<int, 10> hex,
                          std::array<int, 10> byte2, int msc_location,
                          int vlr_location);

  void new_access_info_row(int s_id, int ai_type, int data1, int data2,
                           std::string data3, std::string data4);

  void new_special_facility_row(int s_id, int sf_type, bool is_active,
                                int error_cntrl, int data_a,
                                std::string data_b);

  void new_call_forwarding_row(int s_id, int sf_type, int start_time,
                               int end_time, std::string numberx);
  void get_subscriber_data(int s_id, std::string *sub_nbr,
                           std::array<bool, 10> &bit, std::array<int, 10> &hex,
                           std::array<int, 10> &byte2, int *msc_location,
                           int *vlr_location);

  void get_new_destination(int s_id, int sf_type, int start_time, int end_time,
                           std::vector<std::string> *numberx);

  void get_access_data(int s_id, int ai_type, int *data1, int *data2,
                       std::string *data3, std::string *data4);
  void update_subscriber_data(int s_id, bool bit_1, int sf_type,
                              int data_a);

  void update_location(const std::string &sub_nbr, int vlr_location);

  void insert_call_forwarding(std::string sub_nbr, int sf_type, int start_time,
                              int end_time, std::string numberx);

  void delete_call_forwarding(const std::string &sub_nbr, int sf_type,
                              int start_time);
 private:
  std::vector<SRow> s_;
  std::vector<AIRow> ai_;
  std::vector<SFRow> sf_;
  std::vector<CFRow> cf_;

  std::atomic_uint32_t tx1_succ = 0, tx2_succ = 0, tx3_succ = 0, tx4_succ = 0,
                       tx5_succ = 0, tx6_succ = 0, tx7_succ = 0;
  std::atomic_uint32_t  tx1_total = 0, tx2_total = 0, tx3_total = 0,
                        tx4_total = 0, tx5_total = 0, tx6_total = 0,
                        tx7_total = 0;

};

class AlexTATPDB {
 public:

  AlexTATPDB() {}

  void print_stats();

  void new_subscriber_row(int s_id, std::string sub_nbr,
                          std::array<bool, 10> bit, std::array<int, 10> hex,
                          std::array<int, 10> byte2, int msc_location,
                          int vlr_location);

  void new_access_info_row(int s_id, int ai_type, int data1, int data2,
                           std::string data3, std::string data4);

  void new_special_facility_row(int s_id, int sf_type, bool is_active,
                                int error_cntrl, int data_a,
                                std::string data_b);

  void new_call_forwarding_row(int s_id, int sf_type, int start_time,
                               int end_time, std::string numberx);
  void get_subscriber_data(int s_id, std::string *sub_nbr,
                           std::array<bool, 10> &bit, std::array<int, 10> &hex,
                           std::array<int, 10> &byte2, int *msc_location,
                           int *vlr_location);

  void get_new_destination(int s_id, int sf_type, int start_time, int end_time,
                           std::vector<std::string> *numberx);

  void get_access_data(int s_id, int ai_type, int *data1, int *data2,
                       std::string *data3, std::string *data4);
  void update_subscriber_data(int s_id, bool bit_1, int sf_type,
                              int data_a);

  void update_location(const std::string &sub_nbr, int vlr_location);

  void insert_call_forwarding(std::string sub_nbr, int sf_type, int start_time,
                              int end_time, std::string numberx);

  void delete_call_forwarding(const std::string &sub_nbr, int sf_type,
                              int start_time);
 private:
  std::vector<SRow> s_;
  std::vector<AIRow> ai_;
  std::vector<SFRow> sf_;
  std::vector<CFRow> cf_;

  std::atomic_uint32_t tx1_succ = 0, tx2_succ = 0, tx3_succ = 0, tx4_succ = 0,
      tx5_succ = 0, tx6_succ = 0, tx7_succ = 0;
  std::atomic_uint32_t  tx1_total = 0, tx2_total = 0, tx3_total = 0,
      tx4_total = 0, tx5_total = 0, tx6_total = 0,
      tx7_total = 0;

};

class PalmTATPDB {
 public:

  PalmTATPDB() {}

  void print_stats();

  void new_subscriber_row(int s_id, std::string sub_nbr,
                          std::array<bool, 10> bit, std::array<int, 10> hex,
                          std::array<int, 10> byte2, int msc_location,
                          int vlr_location);

  void new_access_info_row(int s_id, int ai_type, int data1, int data2,
                           std::string data3, std::string data4);

  void new_special_facility_row(int s_id, int sf_type, bool is_active,
                                int error_cntrl, int data_a,
                                std::string data_b);

  void new_call_forwarding_row(int s_id, int sf_type, int start_time,
                               int end_time, std::string numberx);
  void get_subscriber_data(int s_id, std::string *sub_nbr,
                           std::array<bool, 10> &bit, std::array<int, 10> &hex,
                           std::array<int, 10> &byte2, int *msc_location,
                           int *vlr_location);

  void get_new_destination(int s_id, int sf_type, int start_time, int end_time,
                           std::vector<std::string> *numberx);

  void get_access_data(int s_id, int ai_type, int *data1, int *data2,
                       std::string *data3, std::string *data4);
  void update_subscriber_data(int s_id, bool bit_1, int sf_type,
                              int data_a);

  void update_location(const std::string &sub_nbr, int vlr_location);

  void insert_call_forwarding(std::string sub_nbr, int sf_type, int start_time,
                              int end_time, std::string numberx);

  void delete_call_forwarding(const std::string &sub_nbr, int sf_type,
                              int start_time);
 private:
  std::vector<SRow> s_;
  std::vector<AIRow> ai_;
  std::vector<SFRow> sf_;
  std::vector<CFRow> cf_;

  std::atomic_uint32_t tx1_succ = 0, tx2_succ = 0, tx3_succ = 0, tx4_succ = 0,
      tx5_succ = 0, tx6_succ = 0, tx7_succ = 0;
  std::atomic_uint32_t  tx1_total = 0, tx2_total = 0, tx3_total = 0,
      tx4_total = 0, tx5_total = 0, tx6_total = 0,
      tx7_total = 0;

};

#endif //TXBENCH_SRC_EXAMPLES_INMEMORYARRAYS_INMEMARRAYSTATPDB_H_
