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

class InMemArraysTATPDB {
 public:

  InMemArraysTATPDB() {}

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
                           std::string *numberx);

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
};

#endif //TXBENCH_SRC_EXAMPLES_INMEMORYARRAYS_INMEMARRAYSTATPDB_H_
