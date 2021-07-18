#include "tatp_worker.h"

#include "tatp_util.h"
#include "utilities/random_generator.h"
#include <stdexcept>
#include <climits>
#include <iostream>

TATPWorker::TATPWorker(size_t num_rows,
                       std::unique_ptr<TATPConnection> connection)
    : num_rows_(
          num_rows <= (size_t)INT_MAX
              ? (int)num_rows
              : throw std::runtime_error(
                    "number of rows must representable by the integer type")),
      a_val_(num_rows <= 1000000    ? 65535
             : num_rows <= 10000000 ? 1048575
                                    : 2097151),
      connection_(std::move(connection)) {}

void TATPWorker::run(std::atomic_bool &terminate,
                     std::atomic_uint32_t &commit_count) {
  RandomGenerator rg;

  constexpr int8_t start_times[] = {0, 8, 16};

  while (!terminate) {

    int s_id_rnd = RandomNonUniSid(a_val_, num_rows_);
    int trans_prob = RandomValue<int>(1, 100);

    if (trans_prob < 35) {
      // GET_SUBSCRIBER_DATA
      // Probability: 35%
      std::string sub_nbr;
      std::array<bool, 10> bit{};
      std::array<int, 10> hex{};
      std::array<int, 10> byte2{};
      int msc_location, vlr_location;

      connection_->get_subscriber_data(
          s_id_rnd, &sub_nbr, bit, hex, byte2,
          &msc_location, &vlr_location);
    } else if (trans_prob < 45) {
      // GET_NEW_DESTINATION
      // Probability: 10%
      int sf_type = rg.random_int(1, 4);
      int start_time = start_times[rg.random_int(0, 2)];
      int end_time = rg.random_int(1, 24);
      std::vector<std::string> numberxs;
      connection_->get_new_destination(
          s_id_rnd,  sf_type, start_time, end_time,
          &numberxs);
    }
      else if (trans_prob < 80) {
      // GET_ACCESS_DATA
      // Probability: 35%
      int data1, data2;
      std::string data3, data4;

      connection_->get_access_data(
          s_id_rnd, rg.random_int(1, 4) /* ai_type */,
          &data1, &data2, &data3, &data4);
    } else if (trans_prob < 82) {
      // UPDATE_SUBSCRIBER_DATA
      // Probability: 2%
      bool bit_1 = rg.random_bool();
      int sf_type = rg.random_int(1, 4);
      int data_a = rg.random_int(0, 255);

      connection_->update_subscriber_data(s_id_rnd, bit_1, sf_type, data_a);

    } else if (trans_prob < 96) {
      // UPDATE_LOCATION
      // Probability: 14%
      std::string sub_nbr = leading_zero_pad(15, std::to_string(s_id_rnd));
      int vlr_location = rg.random_int(INT_MIN, INT_MAX);

      connection_->update_location(
          sub_nbr, vlr_location);

    } else if (trans_prob < 98) {
      // INSERT_CALL_FORWARDING
      // Probability: 2%
      std::string sub_nbr = leading_zero_pad(15, std::to_string(s_id_rnd));
      int sf_type = rg.random_int(1, 4);
      int start_time = start_times[rg.random_int(0, 2)];
      int end_time = rg.random_int(1, 24);

      std::string numberx =
          leading_zero_pad(15, std::to_string(rg.random_int(1, num_rows_)));

      connection_->insert_call_forwarding(sub_nbr, sf_type, start_time,
                                          end_time, numberx);

    } else {
      // DELETE_CALL_FORWARDING
      // Probability: 2%
      std::string sub_nbr = leading_zero_pad(15, std::to_string(s_id_rnd));
      int sf_type = rg.random_int(1, 4);
      int start_time = start_times[rg.random_int(0, 2)];
      connection_->delete_call_forwarding(sub_nbr, sf_type, start_time);
    }

    commit_count++;
  }
}
