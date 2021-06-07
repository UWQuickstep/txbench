#include "benchmarks/tatp/tatp_benchmark.h"
#include <iostream>
#include <memory>

class StdoutTATPConnection : public TATPConnection {
public:
  void get_subscriber_data(int s_id, std::string *sub_nbr,
                           std::array<bool, 10> &bit, std::array<int, 10> &hex,
                           std::array<int, 10> &byte2, int *msc_location,
                           int *vlr_location) override {
    std::cout << "get_subscriber_data(" << s_id << ")" << std::endl;
  }

  void get_new_destination(int s_id, int sf_type, int start_time, int end_time,
                           std::string *numberx) override {
    std::cout << "get_new_destination(" << s_id << "," << sf_type << ","
              << start_time << "," << end_time << ")" << std::endl;
  }

  void get_access_data(int s_id, int ai_type, int *data1, int *data2,
                       std::string *data3, std::string *data4) override {
    std::cout << "get_access_data(" << s_id << "," << ai_type << ")"
              << std::endl;
  }

  void update_subscriber_data(int s_id, bool bit_1, int sf_type,
                              int data_a) override {
    std::cout << "update_subscriber_data(" << s_id << "," << bit_1 << ","
              << sf_type << "," << data_a << ")" << std::endl;
  }

  void update_location(const std::string &sub_nbr, int vlr_location) override {
    std::cout << "update_location(" << sub_nbr << "," << vlr_location << ")"
              << std::endl;
  }

  void insert_call_forwarding(const std::string &sub_nbr, int sf_type,
                              int start_time, int end_time,
                              const std::string &numberx) override {
    std::cout << "insert_call_forwarding(" << sub_nbr << "," << sf_type << ","
              << start_time << "," << end_time << "," << numberx << ")"
              << std::endl;
  }

  void delete_call_forwarding(const std::string &sub_nbr, int sf_type,
                              int start_time) override {
    std::cout << "delete_call_forwarding(" << sub_nbr << "," << sf_type << ","
              << start_time << ")" << std::endl;
  }
};

class StdoutTATPServer : public TATPServer {
public:
  void load() override { std::cout << "load()" << std::endl; }

  std::unique_ptr<TATPConnection> connect() override {
    return std::make_unique<StdoutTATPConnection>();
  }
};

int main(int argc, char **argv) {
  auto server = std::make_unique<StdoutTATPServer>();

  TATPBenchmark benchmark = TATPBenchmark::parse(argc, argv, std::move(server));
  double tps = benchmark.run();

  std::cout << "Throughput (tps): " << tps << std::endl;

  return 0;
}
