#include "benchmarks/tatp/tatp_benchmark.h"
#include "inmem_arrays_TATP_db.h"
#include <iostream>
#include <memory>

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

int main(int argc, char **argv) {
  auto server = std::make_unique<InMemArraysTATPServer<AlexTATPDB>>();
  std::shared_ptr<AlexTATPDB> db = server->db_;

  TATPBenchmark benchmark = TATPBenchmark::parse(argc, argv, std::move(server));
  double tps = benchmark.run();

  db->print_stats();

  std::cout << "Throughput (tps): " << tps << std::endl;

  return 0;
}
