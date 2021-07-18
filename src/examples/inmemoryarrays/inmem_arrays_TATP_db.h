#ifndef TXBENCH_SRC_EXAMPLES_INMEMORYARRAYS_INMEMARRAYSTATPDB_H_
#define TXBENCH_SRC_EXAMPLES_INMEMORYARRAYS_INMEMARRAYSTATPDB_H_

#include "benchmarks/tatp/tatp_benchmark.h"

#include <vector>
#include <memory>
#include <string>
#include <array>
#include<shared_mutex>

#include "alex/alex_lib/alex.h"

struct SRow {
// public:
  int s_id;
  std::string sub_nbr;
  std::array<bool, 10> bit;
  std::array<int, 10> hex;
  std::array<int, 10> byte2;
  int msc_location;
  int vlr_location;
  int mtx_array_id;

  SRow(int s_id,
       const std::string &sub_nbr,
       const std::array<bool, 10> &bit,
       const std::array<int, 10> &hex,
       const std::array<int, 10> &byte_2,
       int msc_location,
       int vlr_location);

  SRow(int s_id,
       const std::string &sub_nbr,
       const std::array<bool, 10> &bit,
       const std::array<int, 10> &hex,
       const std::array<int, 10> &byte_2,
       int msc_location,
       int vlr_location,
       int mtx_row_id);

  SRow() {}

  friend std::ostream& operator<<(std::ostream &os, const SRow& n)
  {
    os << "SROW - " << n.s_id;
    return os;
  }

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

  AIRow() {}

  friend std::ostream& operator<<(std::ostream &os, const AIRow& n)
  {
    os << "AIRow - " << n.s_id << ", " << n.ai_type;
    return os;
  }
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

  SFRow() {}


  friend std::ostream& operator<<(std::ostream &os, const SFRow& n)
  {
    os << "SFRow - " << n.s_id << ", " << n.sf_type;
    return os;
  }
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

  CFRow() {}

  friend std::ostream& operator<<(std::ostream &os, const CFRow& n)
  {
    os << "CFRow - " << n.s_id << ", " << n.sf_type << ", " << n.start_time;
    return os;
  }

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

int to_ai_compound_key(int s_id, int ai_type);

int ai_compound_key_to_s_id(int ai_key);

int ai_compound_key_to_ai_type(int ai_key);

int to_sf_compound_key(int s_id, int sf_type);

int sf_compound_key_to_s_id(int sf_key);

int sf_compound_key_to_sf_type(int sf_key);

int to_cf_compound_key(int s_id, int sf_type, int start_time);

int cf_compound_key_to_s_id(int cf_key);

int cf_compound_key_to_sf_type(int cf_key);

int cf_compound_key_to_start_time(int cf_key);

template <typename DBType>
class InMemArraysTATPConnection : public TATPConnection {
 public:
  InMemArraysTATPConnection(std::shared_ptr<DBType> db) : db_(db) {}

  void new_subscriber_row(int s_id, std::string sub_nbr,
                          std::array<bool, 10> bit, std::array<int, 10> hex,
                          std::array<int, 10> byte2, int msc_location,
                          int vlr_location) override {
    return db_->new_subscriber_row(s_id, std::move(sub_nbr), bit, hex, byte2,
                                   msc_location, vlr_location);
  }

  void new_access_info_row(int s_id, int ai_type, int data1, int data2,
                           std::string data3, std::string data4) override {
    return db_->new_access_info_row(s_id, ai_type, data1, data2,
                                    std::move(data3), std::move(data4));
  }

  void new_special_facility_row(int s_id, int sf_type, bool is_active,
                                int error_cntrl, int data_a,
                                std::string data_b) override {
    return db_->new_special_facility_row(s_id, sf_type, is_active, error_cntrl,
                                         data_a, std::move(data_b));
  }

  void new_call_forwarding_row(int s_id, int sf_type, int start_time,
                               int end_time, std::string numberx) override {
    return db_->new_call_forwarding_row(s_id, sf_type, start_time, end_time,
                                        std::move(numberx));
  }

  void get_subscriber_data(int s_id, std::string *sub_nbr,
                           std::array<bool, 10> &bit, std::array<int, 10> &hex,
                           std::array<int, 10> &byte2, int *msc_location,
                           int *vlr_location) override {
    return db_->get_subscriber_data(s_id, sub_nbr, bit, hex, byte2,
                                    msc_location, vlr_location);
  }

  void get_new_destination(int s_id, int sf_type, int start_time, int end_time,
                           std::vector<std::string> *numberx) override {
    return db_->get_new_destination(s_id, sf_type, start_time, end_time,
                                    numberx);
  }

  void get_access_data(int s_id, int ai_type, int *data1, int *data2,
                       std::string *data3, std::string *data4) override {
    return db_->get_access_data(s_id, ai_type, data1, data2, data3, data4);
  }

  void update_subscriber_data(int s_id, bool bit_1, int sf_type,
                              int data_a) override {
    return db_->update_subscriber_data(s_id, bit_1, sf_type, data_a);
  }

  void update_location(const std::string &sub_nbr, int vlr_location) override {
    return db_->update_location(sub_nbr, vlr_location);
  }

  void insert_call_forwarding(std::string sub_nbr, int sf_type, int start_time,
                              int end_time, std::string numberx) override {
    return db_->insert_call_forwarding(sub_nbr, sf_type, start_time,
                                       end_time, numberx);
  }

  void delete_call_forwarding(const std::string &sub_nbr, int sf_type,
                              int start_time) override {
    return db_->delete_call_forwarding(sub_nbr, sf_type, start_time);
  }

 private:
  std::shared_ptr<DBType> db_;
};

template <typename DBType>
class InMemArraysTATPServer : public TATPServer {
 public:
  InMemArraysTATPServer() :
      db_(std::make_shared<DBType>()) {}

  std::unique_ptr<TATPConnection> connect() override {
    return std::make_unique<InMemArraysTATPConnection<DBType>>(db_);
  }

  void print_db_stats() {
    db_->print_stats();
  }

  std::shared_ptr<DBType> db_;
};


#endif //TXBENCH_SRC_EXAMPLES_INMEMORYARRAYS_INMEMARRAYSTATPDB_H_
