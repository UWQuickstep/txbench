#include "../inmem_arrays_TATP_db.h"
#include "inmem_arrays_TATP_db_ART.h"

#include <string.h>
#include <iostream>

void ArtTATPDB::print_stats() {
  std::cout << "ART sizes" << std::endl;
  std::cout << "\tS: " << art_size(&s_art) << std::endl;
  std::cout << "\tAI: " << art_size(&ai_art) << std::endl;
  std::cout << "\tSF: " << art_size(&sf_art) << std::endl;
  std::cout << "\tCF: " << art_size(&cf_art) << std::endl;
  std::cout << "Success rates" << std::endl;
  std::cout << "\tTx1: " << ((double) tx1_succ / tx1_total) * 100
            << "% (expected 100%, executed "
            << tx1_total << ", successful " << tx1_succ << ")" << std::endl;
  std::cout << "\tTx2: " << ((double) tx2_succ / tx2_total) * 100
            << "% (expected 23.9%, executed "
            << tx2_total << ", successful " << tx2_succ << ")" << std::endl;
  std::cout << "\tTx3: " << ((double) tx3_succ / tx3_total) * 100
            << "% (expected 62.5%, executed "
            << tx3_total << ", successful " << tx3_succ << ")" << std::endl;
  std::cout << "\tTx4: " << ((double) tx4_succ / tx4_total) * 100
            << "% (expected 62.5%, executed "
            << tx4_total << ", successful " << tx4_succ << ")" << std::endl;
  std::cout << "\tTx5: " << ((double) tx5_succ / tx5_total) * 100
            << "% (expected 100%, executed "
            << tx5_total << ", successful " << tx5_succ << ")" << std::endl;
  std::cout << "\tTx6: " << ((double) tx6_succ / tx6_total) * 100
            << "% (expected 31.25%, executed "
            << tx6_total << ", successful " << tx6_succ << ")" << std::endl;
  std::cout << "\tTx7: " << ((double) tx7_succ / tx7_total) * 100
            << "% (expected 31.25%, executed "
            << tx7_total << ", successful " << tx7_succ << ")" << std::endl;
}

void ArtTATPDB::new_subscriber_row(int s_id,
                                   std::string sub_nbr,
                                   std::array<bool, 10> bit,
                                   std::array<int, 10> hex,
                                   std::array<int, 10> byte2,
                                   int msc_location,
                                   int vlr_location) {
  s_heap_[s_heap_index_] = {s_id, sub_nbr, bit, hex, byte2,
                            msc_location, vlr_location};

  std::string s = std::to_string(s_id);
  art_insert(&s_art,
             (unsigned char *) s.c_str(),
             strlen(s.c_str()),
             (void *) s_heap_index_);
  s_heap_index_++;
}

void ArtTATPDB::new_access_info_row(int s_id,
                                    int ai_type,
                                    int data1,
                                    int data2,
                                    std::string data3,
                                    std::string data4) {

  ai_heap_[ai_heap_index_] = {s_id, ai_type, data1, data2,
                              std::move(data3), std::move(data4)};

  std::string s = std::to_string(to_ai_compound_key(s_id, ai_type));
  art_insert(&ai_art,
             (unsigned char *) s.c_str(),
             strlen(s.c_str()),
             (void *) ai_heap_index_);
  ai_heap_index_++;
}

void ArtTATPDB::new_special_facility_row(int s_id,
                                         int sf_type,
                                         bool is_active,
                                         int error_cntrl,
                                         int data_a,
                                         std::string data_b) {

  sf_heap_[sf_heap_index_] = {s_id, sf_type, is_active, error_cntrl,
                              data_a, std::move(data_b)};

  std::string s = std::to_string(to_sf_compound_key(s_id, sf_type));
  art_insert(&sf_art,
             (unsigned char *) s.c_str(),
             strlen(s.c_str()),
             (void *) sf_heap_index_);
  sf_heap_index_++;
}

void ArtTATPDB::new_call_forwarding_row(int s_id,
                                        int sf_type,
                                        int start_time,
                                        int end_time,
                                        std::string numberx) {
  cf_heap_[cf_heap_index_] =
      {s_id, sf_type, start_time, end_time, std::move(numberx)};

  std::string s = std::to_string(to_cf_compound_key(s_id, sf_type, start_time));
  art_insert(&cf_art,
             (unsigned char *) s.c_str(),
             strlen(s.c_str()),
             (void *) cf_heap_index_);
  cf_heap_index_++;
}

void ArtTATPDB::get_subscriber_data(int s_id,
                                    std::string *sub_nbr,
                                    std::array<bool, 10> &bit,
                                    std::array<int, 10> &hex,
                                    std::array<int, 10> &byte2,
                                    int *msc_location,
                                    int *vlr_location) {
  tx1_total++;

  //////
//  std::shared_lock lock(s_mutex_);
  //////
  std::string s = std::to_string(s_id);

  uintptr_t out = (uintptr_t) art_search(&s_art,
                                         (unsigned char *) s.c_str(),
                                         strlen(s.c_str()));


  if (out == NULL) {
    return;
  }
  SRow *srow = &s_heap_[out];

//    std::shared_lock lock(s_row_mtxs_[srow->mtx_array_id]);
////    [[likely]]
    sub_nbr->assign(srow->sub_nbr);
    bit = srow->bit;
    hex = srow->hex;
    byte2 = srow->byte2;
    *msc_location = srow->msc_location;
    *vlr_location = srow->vlr_location;
    tx1_succ++;
    return;
//  }
}

void ArtTATPDB::get_new_destination(int s_id,
                                    int sf_type,
                                    int start_time,
                                    int end_time,
                                    std::vector<std::string> *numberxs) {
// SELECT cf.numberx FROM Special_Facility AS sf, Call_Forwarding AS cf
// WHERE (sf.s_id = <s_id rnd> AND sf.sf_type = <sf_type rnd>
//        AND sf.is_active = 1)
//  AND (cf.s_id = sf.s_id AND cf.sf_type = sf.sf_type)
//  AND (cf.start_time \<= <start_time rnd>
//       AND <end_time rnd> \< cf.end_time);

  tx2_total++;

  /////
//  std::shared_lock lock(sf_mutex_);
//  std::shared_lock lock1(cf_mutex_);
  /////

  std::string s = std::to_string(to_sf_compound_key(s_id, sf_type));
  uintptr_t out = (uintptr_t) art_search(&sf_art,
                                         (unsigned char *) s.c_str(),
                                         strlen(s.c_str()));

  SFRow *sfrow = &sf_heap_[out];


  if (sfrow == NULL || sfrow->is_active != 1) {
    return;
  }
//
//  auto cfiter_l = cf_art_.lower_bound(to_cf_compound_key(s_id, sf_type, 0));
//  const auto cfiter_u =
//      cf_art_.upper_bound(to_cf_compound_key(s_id, sf_type, start_time + 1));
//
//  while (cfiter_l != cfiter_u) {
//    if (cfiter_l.payload().end_time > end_time) {
//      numberxs->emplace_back(cfiter_l.payload().numberx);
//    }
//    cfiter_l++;
//  }
//
//  if (numberxs->size() > 0) {
//    tx2_succ++;
//  }

  return;
}

void ArtTATPDB::get_access_data(int s_id,
                                int ai_type,
                                int *data1,
                                int *data2,
                                std::string *data3,
                                std::string *data4) {

  // SELECT data1, data2, data3, data4 FROM Access_Info
  // WHERE s_id = <s_id rnd> AND ai_type = <ai_type rnd>;
  // (s_id, ai_type) is a composite primary key.
  tx3_total++;
//
//  std::shared_lock lock(ai_mutex_);
//
  std::string s = std::to_string(to_ai_compound_key(s_id, ai_type));
  uintptr_t out = (uintptr_t) art_search(&ai_art,
                                         (unsigned char *) s.c_str(),
                                         strlen(s.c_str()));

  if (out != NULL) { return; }

  AIRow *airow = &ai_heap_[out];
    *data1 = airow->data1;
    *data2 = airow->data2;
    data3->assign(airow->data3);
    data4->assign(airow->data4);
    tx3_succ++;

  return;
}

void ArtTATPDB::update_subscriber_data(int s_id,
                                       bool bit_1,
                                       int sf_type,
                                       int data_a) {

  tx4_total++;
  /////////
//
//  /////////
//
//  // UPDATE Subscriber SET bit_1 = <bit_rnd>
//  // WHERE s_id = <s_id rnd subid>;


  std::string s = std::to_string(s_id);
  uintptr_t out = (uintptr_t) art_search(&s_art,
                                         (unsigned char *) s.c_str(),
                                         strlen(s.c_str()));


  if (out == NULL) {
    return;
  }
  SRow *srow = &s_heap_[out];


//  std::unique_lock lock(s_row_mtxs_[srow->mtx_array_id]);
//  std::unique_lock lock1(sf_mutex_);


//  // UPDATE Special_Facility SET data_a = <data_a rnd>
//  // WHERE s_id = <s_id value subid> AND sf_type = <sf_type rnd>;

  std::string s2 = std::to_string(to_sf_compound_key(s_id, sf_type));
  out = (uintptr_t) art_search(&s_art,
                                         (unsigned char *) s2.c_str(),
                                         strlen(s2.c_str()));

  if (out == NULL) {return;}
  SFRow *sf_rowid = &sf_heap_[out];


//  // Perform both updates at the same time, instead of rolling back
  srow->bit[0] = bit_1;
  sf_rowid->data_a = data_a;
  tx4_succ++;

  return;
}

void ArtTATPDB::update_location(const std::string &sub_nbr,
                                int vlr_location) {
  tx5_total++;

  ////////////
//  std::unique_lock lock(s_mutex_);
  ///////////
//
//  // UPDATE Subscriber SET vlr_location = <vlr_location rnd>
//  // WHERE sub_nbr = <sub_nbr rndstr>;
//
  int s_id = std::stoi(sub_nbr);
  std::string s = std::to_string(s_id);
  uintptr_t out = (uintptr_t) art_search(&s_art,
                                         (unsigned char *) s.c_str(),
                                         strlen(s.c_str()));

  if (out == NULL) {
    return;
  }
  SRow *srow = &s_heap_[out];

//  std::unique_lock lock(s_row_mtxs_[srow->mtx_array_id]);
//
//  if (srow != nullptr) {
    srow->vlr_location = vlr_location;
    tx5_succ++;
//  }

  return;
}

void ArtTATPDB::insert_call_forwarding(std::string sub_nbr,
                                       int sf_type,
                                       int start_time,
                                       int end_time,
                                       std::string numberx) {
  tx6_total++;

  //////

  //////


  // SELECT <s_id bind subid s_id> FROM Subscriber
//  // WHERE sub_nbr = <sub_nbr rndstr>;
//
  int s_id = std::stoi(sub_nbr);
  std::string s = std::to_string(s_id);
  uintptr_t out = (uintptr_t) art_search(&s_art,
                                         (unsigned char *) s.c_str(),
                                         strlen(s.c_str()));

  if (out == NULL) {
    return;
  }
  SRow *srow = &s_heap_[out];

//  std::shared_lock lock(s_row_mtxs_[srow->mtx_array_id]);
//  std::shared_lock lock1(sf_mutex_);
//  std::unique_lock lock2(cf_mutex_);
//
//
//  // SELECT <sf_type bind sfid sf_type>
//  // FROM Special_Facility
//  // WHERE s_id = <s_id value subid>;


  int key = to_sf_compound_key(s_id, sf_type);
  std::string s2 = std::to_string(key);

  out = (uintptr_t) art_search(&sf_art,
                                         (unsigned char *) s2.c_str(),
                                         strlen(s2.c_str()));


    if (out == NULL) {return;}


//  // INSERT INTO Call_Forwarding
//  // VALUES (<s_id value subid>, <sf_type rnd sf_type>,
//  // <start_time rnd>, <end_time rnd>, <numberx rndstr>);
//
//


  int key2 = to_cf_compound_key(s_id, sf_type, start_time);
  std::string s3 = std::to_string(key2);

  out = (uintptr_t) art_search(&cf_art,
                              (unsigned char *) s3.c_str(),
                              strlen(s3.c_str()));

  if (out == NULL) {return;}



  // TODO(chronis) fix corecteness bug :)
  int index_to_use = cf_heap_index_++;
  cf_heap_[index_to_use] =
      {s_id, sf_type, start_time, end_time, std::move(numberx)};

  std::string s4 = std::to_string(to_cf_compound_key(s_id, sf_type, start_time));
  art_insert(&cf_art,
             (unsigned char *) s4.c_str(),
             strlen(s4.c_str()),
             (void *) index_to_use);
  tx6_succ++;

  return;
}

void ArtTATPDB::delete_call_forwarding(const std::string &sub_nbr,
                                       int sf_type,
                                       int start_time) {
  tx7_total++;

  //////
//  std::shared_lock lock(s_mutex_);

//  //////
//
//  // SELECT <s_id bind subid s_id> FROM Subscriber
//  // WHERE sub_nbr = <sub_nbr rndstr>;

  int s_id = std::stoi(sub_nbr);
  std::string s = std::to_string(s_id);
  uintptr_t out = (uintptr_t) art_search(&s_art,
                                         (unsigned char *) s.c_str(),
                                         strlen(s.c_str()));

  if (out == NULL) {
    return;
  }
  SRow *srow = &s_heap_[out];

//  std::shared_lock lock(s_row_mtxs_[srow->mtx_array_id]);
//  std::unique_lock lock1(cf_mutex_);
//
//
//  // DELETE FROM Call_Forwarding
//  // WHERE s_id = <s_id value subid> AND sf_type = <sf_type rnd>
//  // AND start_time = <start_time rnd>;
//

  int key = to_cf_compound_key(s_id, sf_type, start_time);
  std::string s2 = std::to_string(key);

  uintptr_t val = (uintptr_t)art_delete(&cf_art, (unsigned char*)s2.c_str(), strlen(s2.c_str()));
  if (val != NULL) {
    tx7_succ++;
  }

  return;
}
