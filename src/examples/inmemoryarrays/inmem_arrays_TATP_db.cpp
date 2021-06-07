#include "inmem_arrays_TATP_db.h"


void InMemArraysTATPDB::print_stats() {

}

void InMemArraysTATPDB::new_subscriber_row(int s_id, std::string sub_nbr,
                        std::array<bool, 10> bit, std::array<int, 10> hex,
                        std::array<int, 10> byte2, int msc_location,
                        int vlr_location) {
  s_.emplace_back(s_id, sub_nbr, bit, hex, byte2,
                   msc_location, vlr_location);
}

void InMemArraysTATPDB::new_access_info_row(int s_id, int ai_type, int data1, int data2,
                         std::string data3, std::string data4) {
  ai_.emplace_back(s_id, ai_type, data1, data2,
                   std::move(data3), std::move(data4));
}

void InMemArraysTATPDB::new_special_facility_row(int s_id, int sf_type, bool is_active,
                              int error_cntrl, int data_a,
                              std::string data_b)  {
  sf_.emplace_back(s_id, sf_type, is_active, error_cntrl,
                    data_a, std::move(data_b));
}

void InMemArraysTATPDB::new_call_forwarding_row(int s_id, int sf_type, int start_time,
                             int end_time, std::string numberx)  {
  cf_.emplace_back(s_id, sf_type, start_time, end_time, std::move(numberx));
}

void InMemArraysTATPDB::get_subscriber_data(int s_id, std::string *sub_nbr,
                         std::array<bool, 10> &bit, std::array<int, 10> &hex,
                         std::array<int, 10> &byte2, int *msc_location,
                         int *vlr_location) {
  return;
}

void InMemArraysTATPDB::get_new_destination(int s_id, int sf_type, int start_time, int end_time,
                         std::string *numberx) {
  return;
}

void InMemArraysTATPDB::get_access_data(int s_id, int ai_type, int *data1, int *data2,
                     std::string *data3, std::string *data4) {
  return;
}

void InMemArraysTATPDB::update_subscriber_data(int s_id, bool bit_1, int sf_type,
                            int data_a) {
  return;
}

void InMemArraysTATPDB::update_location(const std::string &sub_nbr, int vlr_location) {
  return;
}

void InMemArraysTATPDB::insert_call_forwarding(std::string sub_nbr, int sf_type, int start_time,
                            int end_time, std::string numberx) {
  return;
}

void InMemArraysTATPDB::delete_call_forwarding(const std::string &sub_nbr, int sf_type,
                            int start_time) {
  return;
}
SFRow::SFRow(int s_id,
             int sf_type,
             bool is_active,
             int error_cntrl,
             int data_a,
             const std::string &data_b)
    : s_id(s_id),
      sf_type(sf_type),
      is_active(is_active),
      error_cntrl(error_cntrl),
      data_a(data_a),
      data_b(data_b) {}

AIRow::AIRow(int s_id,
             int ai_type,
             int data_1,
             int data_2,
             const std::string &data_3,
             const std::string &data_4)
    : s_id(s_id),
      ai_type(ai_type),
      data1(data_1),
      data2(data_2),
      data3(data_3),
      data4(data_4) {}

SRow::SRow(int s_id,
           const std::string &sub_nbr,
           const std::array<bool, 10> &bit,
           const std::array<int, 10> &hex,
           const std::array<int, 10> &byte_2,
           int msc_location,
           int vlr_location)
    : s_id(s_id),
      sub_nbr(sub_nbr),
      bit(bit),
      hex(hex),
      byte2(byte_2),
      msc_location(msc_location),
      vlr_location(vlr_location) {}

CFRow::CFRow(int s_id,
             int sf_type,
             int start_time,
             int end_time,
             const std::string &numberx)
    : s_id(s_id),
      sf_type(sf_type),
      start_time(start_time),
      end_time(end_time),
      numberx(numberx) {}
