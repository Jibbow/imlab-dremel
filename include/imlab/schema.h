
#ifndef INCLUDE_IMLAB_SCHEMA_H_
#define INCLUDE_IMLAB_SCHEMA_H_

#include <optional>
#include <vector>
#include <unordered_map>
#include "./infra/hash.h"
#include "./infra/types.h"
#include "./algebra/iu.h"

namespace imlab {
namespace tpcc {

class TableBase {
 public:
    uint64_t get_size() { return size; }
 protected:
    uint64_t size = 0;
};

enum Relation {
    kwarehouse,
    kdistrict,
    kcustomer,
    khistory,
    kneworder,
    korder,
    korderline,
    kitem,
    kstock,
};

class warehouseTable : public TableBase {
 public:
    uint64_t insert(
        const Integer w_id,
        const Varchar<10> w_name,
        const Varchar<20> w_street_1,
        const Varchar<20> w_street_2,
        const Varchar<20> w_city,
        const Char<2> w_state,
        const Char<9> w_zip,
        const Numeric<4, 4> w_tax,
        const Numeric<12, 2> w_ytd);

    std::optional<Integer> get_w_id(const uint64_t tid);
    std::optional<Varchar<10>> get_w_name(const uint64_t tid);
    std::optional<Varchar<20>> get_w_street_1(const uint64_t tid);
    std::optional<Varchar<20>> get_w_street_2(const uint64_t tid);
    std::optional<Varchar<20>> get_w_city(const uint64_t tid);
    std::optional<Char<2>> get_w_state(const uint64_t tid);
    std::optional<Char<9>> get_w_zip(const uint64_t tid);
    std::optional<Numeric<4, 4>> get_w_tax(const uint64_t tid);
    std::optional<Numeric<12, 2>> get_w_ytd(const uint64_t tid);

    void update_w_id(const uint64_t tid, const Integer w_id);
    void update_w_name(const uint64_t tid, const Varchar<10> w_name);
    void update_w_street_1(const uint64_t tid, const Varchar<20> w_street_1);
    void update_w_street_2(const uint64_t tid, const Varchar<20> w_street_2);
    void update_w_city(const uint64_t tid, const Varchar<20> w_city);
    void update_w_state(const uint64_t tid, const Char<2> w_state);
    void update_w_zip(const uint64_t tid, const Char<9> w_zip);
    void update_w_tax(const uint64_t tid, const Numeric<4, 4> w_tax);
    void update_w_ytd(const uint64_t tid, const Numeric<12, 2> w_ytd);

    void remove(const uint64_t tid);

    static const std::vector<IU> IUs;

    // Primary Key for: w_id
    std::unordered_map<Key<Integer>, uint64_t> primary_key;

 private:
    std::vector<bool> deleted_tuples;
    size_t first_free_pos = 0;

    std::vector<Integer> w_id;
    std::vector<Varchar<10>> w_name;
    std::vector<Varchar<20>> w_street_1;
    std::vector<Varchar<20>> w_street_2;
    std::vector<Varchar<20>> w_city;
    std::vector<Char<2>> w_state;
    std::vector<Char<9>> w_zip;
    std::vector<Numeric<4, 4>> w_tax;
    std::vector<Numeric<12, 2>> w_ytd;
};

class districtTable : public TableBase {
 public:
    uint64_t insert(
        const Integer d_id,
        const Integer d_w_id,
        const Varchar<10> d_name,
        const Varchar<20> d_street_1,
        const Varchar<20> d_street_2,
        const Varchar<20> d_city,
        const Char<2> d_state,
        const Char<9> d_zip,
        const Numeric<4, 4> d_tax,
        const Numeric<12, 2> d_ytd,
        const Integer d_next_o_id);

    std::optional<Integer> get_d_id(const uint64_t tid);
    std::optional<Integer> get_d_w_id(const uint64_t tid);
    std::optional<Varchar<10>> get_d_name(const uint64_t tid);
    std::optional<Varchar<20>> get_d_street_1(const uint64_t tid);
    std::optional<Varchar<20>> get_d_street_2(const uint64_t tid);
    std::optional<Varchar<20>> get_d_city(const uint64_t tid);
    std::optional<Char<2>> get_d_state(const uint64_t tid);
    std::optional<Char<9>> get_d_zip(const uint64_t tid);
    std::optional<Numeric<4, 4>> get_d_tax(const uint64_t tid);
    std::optional<Numeric<12, 2>> get_d_ytd(const uint64_t tid);
    std::optional<Integer> get_d_next_o_id(const uint64_t tid);

    void update_d_id(const uint64_t tid, const Integer d_id);
    void update_d_w_id(const uint64_t tid, const Integer d_w_id);
    void update_d_name(const uint64_t tid, const Varchar<10> d_name);
    void update_d_street_1(const uint64_t tid, const Varchar<20> d_street_1);
    void update_d_street_2(const uint64_t tid, const Varchar<20> d_street_2);
    void update_d_city(const uint64_t tid, const Varchar<20> d_city);
    void update_d_state(const uint64_t tid, const Char<2> d_state);
    void update_d_zip(const uint64_t tid, const Char<9> d_zip);
    void update_d_tax(const uint64_t tid, const Numeric<4, 4> d_tax);
    void update_d_ytd(const uint64_t tid, const Numeric<12, 2> d_ytd);
    void update_d_next_o_id(const uint64_t tid, const Integer d_next_o_id);

    void remove(const uint64_t tid);

    static const std::vector<IU> IUs;

    // Primary Key for: d_w_id, d_id
    std::unordered_map<Key<Integer, Integer>, uint64_t> primary_key;

 private:
    std::vector<bool> deleted_tuples;
    size_t first_free_pos = 0;

    std::vector<Integer> d_id;
    std::vector<Integer> d_w_id;
    std::vector<Varchar<10>> d_name;
    std::vector<Varchar<20>> d_street_1;
    std::vector<Varchar<20>> d_street_2;
    std::vector<Varchar<20>> d_city;
    std::vector<Char<2>> d_state;
    std::vector<Char<9>> d_zip;
    std::vector<Numeric<4, 4>> d_tax;
    std::vector<Numeric<12, 2>> d_ytd;
    std::vector<Integer> d_next_o_id;
};

class customerTable : public TableBase {
 public:
    uint64_t insert(
        const Integer c_id,
        const Integer c_d_id,
        const Integer c_w_id,
        const Varchar<16> c_first,
        const Char<2> c_middle,
        const Varchar<16> c_last,
        const Varchar<20> c_street_1,
        const Varchar<20> c_street_2,
        const Varchar<20> c_city,
        const Char<2> c_state,
        const Char<9> c_zip,
        const Char<16> c_phone,
        const Timestamp c_since,
        const Char<2> c_credit,
        const Numeric<12, 2> c_credit_lim,
        const Numeric<4, 4> c_discount,
        const Numeric<12, 2> c_balance,
        const Numeric<12, 2> c_ytd_paymenr,
        const Numeric<4, 0> c_payment_cnt,
        const Numeric<4, 0> c_delivery_cnt,
        const Varchar<500> c_data);

    std::optional<Integer> get_c_id(const uint64_t tid);
    std::optional<Integer> get_c_d_id(const uint64_t tid);
    std::optional<Integer> get_c_w_id(const uint64_t tid);
    std::optional<Varchar<16>> get_c_first(const uint64_t tid);
    std::optional<Char<2>> get_c_middle(const uint64_t tid);
    std::optional<Varchar<16>> get_c_last(const uint64_t tid);
    std::optional<Varchar<20>> get_c_street_1(const uint64_t tid);
    std::optional<Varchar<20>> get_c_street_2(const uint64_t tid);
    std::optional<Varchar<20>> get_c_city(const uint64_t tid);
    std::optional<Char<2>> get_c_state(const uint64_t tid);
    std::optional<Char<9>> get_c_zip(const uint64_t tid);
    std::optional<Char<16>> get_c_phone(const uint64_t tid);
    std::optional<Timestamp> get_c_since(const uint64_t tid);
    std::optional<Char<2>> get_c_credit(const uint64_t tid);
    std::optional<Numeric<12, 2>> get_c_credit_lim(const uint64_t tid);
    std::optional<Numeric<4, 4>> get_c_discount(const uint64_t tid);
    std::optional<Numeric<12, 2>> get_c_balance(const uint64_t tid);
    std::optional<Numeric<12, 2>> get_c_ytd_paymenr(const uint64_t tid);
    std::optional<Numeric<4, 0>> get_c_payment_cnt(const uint64_t tid);
    std::optional<Numeric<4, 0>> get_c_delivery_cnt(const uint64_t tid);
    std::optional<Varchar<500>> get_c_data(const uint64_t tid);

    void update_c_id(const uint64_t tid, const Integer c_id);
    void update_c_d_id(const uint64_t tid, const Integer c_d_id);
    void update_c_w_id(const uint64_t tid, const Integer c_w_id);
    void update_c_first(const uint64_t tid, const Varchar<16> c_first);
    void update_c_middle(const uint64_t tid, const Char<2> c_middle);
    void update_c_last(const uint64_t tid, const Varchar<16> c_last);
    void update_c_street_1(const uint64_t tid, const Varchar<20> c_street_1);
    void update_c_street_2(const uint64_t tid, const Varchar<20> c_street_2);
    void update_c_city(const uint64_t tid, const Varchar<20> c_city);
    void update_c_state(const uint64_t tid, const Char<2> c_state);
    void update_c_zip(const uint64_t tid, const Char<9> c_zip);
    void update_c_phone(const uint64_t tid, const Char<16> c_phone);
    void update_c_since(const uint64_t tid, const Timestamp c_since);
    void update_c_credit(const uint64_t tid, const Char<2> c_credit);
    void update_c_credit_lim(const uint64_t tid, const Numeric<12, 2> c_credit_lim);
    void update_c_discount(const uint64_t tid, const Numeric<4, 4> c_discount);
    void update_c_balance(const uint64_t tid, const Numeric<12, 2> c_balance);
    void update_c_ytd_paymenr(const uint64_t tid, const Numeric<12, 2> c_ytd_paymenr);
    void update_c_payment_cnt(const uint64_t tid, const Numeric<4, 0> c_payment_cnt);
    void update_c_delivery_cnt(const uint64_t tid, const Numeric<4, 0> c_delivery_cnt);
    void update_c_data(const uint64_t tid, const Varchar<500> c_data);

    void remove(const uint64_t tid);

    static const std::vector<IU> IUs;

    // Primary Key for: c_w_id, c_d_id, c_id
    std::unordered_map<Key<Integer, Integer, Integer>, uint64_t> primary_key;

 private:
    std::vector<bool> deleted_tuples;
    size_t first_free_pos = 0;

    std::vector<Integer> c_id;
    std::vector<Integer> c_d_id;
    std::vector<Integer> c_w_id;
    std::vector<Varchar<16>> c_first;
    std::vector<Char<2>> c_middle;
    std::vector<Varchar<16>> c_last;
    std::vector<Varchar<20>> c_street_1;
    std::vector<Varchar<20>> c_street_2;
    std::vector<Varchar<20>> c_city;
    std::vector<Char<2>> c_state;
    std::vector<Char<9>> c_zip;
    std::vector<Char<16>> c_phone;
    std::vector<Timestamp> c_since;
    std::vector<Char<2>> c_credit;
    std::vector<Numeric<12, 2>> c_credit_lim;
    std::vector<Numeric<4, 4>> c_discount;
    std::vector<Numeric<12, 2>> c_balance;
    std::vector<Numeric<12, 2>> c_ytd_paymenr;
    std::vector<Numeric<4, 0>> c_payment_cnt;
    std::vector<Numeric<4, 0>> c_delivery_cnt;
    std::vector<Varchar<500>> c_data;
};

class historyTable : public TableBase {
 public:
    uint64_t insert(
        const Integer h_c_id,
        const Integer h_c_d_id,
        const Integer h_c_w_id,
        const Integer h_d_id,
        const Integer h_w_id,
        const Timestamp h_date,
        const Numeric<6, 2> h_amount,
        const Varchar<24> h_data);

    std::optional<Integer> get_h_c_id(const uint64_t tid);
    std::optional<Integer> get_h_c_d_id(const uint64_t tid);
    std::optional<Integer> get_h_c_w_id(const uint64_t tid);
    std::optional<Integer> get_h_d_id(const uint64_t tid);
    std::optional<Integer> get_h_w_id(const uint64_t tid);
    std::optional<Timestamp> get_h_date(const uint64_t tid);
    std::optional<Numeric<6, 2>> get_h_amount(const uint64_t tid);
    std::optional<Varchar<24>> get_h_data(const uint64_t tid);

    void update_h_c_id(const uint64_t tid, const Integer h_c_id);
    void update_h_c_d_id(const uint64_t tid, const Integer h_c_d_id);
    void update_h_c_w_id(const uint64_t tid, const Integer h_c_w_id);
    void update_h_d_id(const uint64_t tid, const Integer h_d_id);
    void update_h_w_id(const uint64_t tid, const Integer h_w_id);
    void update_h_date(const uint64_t tid, const Timestamp h_date);
    void update_h_amount(const uint64_t tid, const Numeric<6, 2> h_amount);
    void update_h_data(const uint64_t tid, const Varchar<24> h_data);

    void remove(const uint64_t tid);

    static const std::vector<IU> IUs;

 private:
    std::vector<bool> deleted_tuples;
    size_t first_free_pos = 0;

    std::vector<Integer> h_c_id;
    std::vector<Integer> h_c_d_id;
    std::vector<Integer> h_c_w_id;
    std::vector<Integer> h_d_id;
    std::vector<Integer> h_w_id;
    std::vector<Timestamp> h_date;
    std::vector<Numeric<6, 2>> h_amount;
    std::vector<Varchar<24>> h_data;
};

class neworderTable : public TableBase {
 public:
    uint64_t insert(
        const Integer no_o_id,
        const Integer no_d_id,
        const Integer no_w_id);

    std::optional<Integer> get_no_o_id(const uint64_t tid);
    std::optional<Integer> get_no_d_id(const uint64_t tid);
    std::optional<Integer> get_no_w_id(const uint64_t tid);

    void update_no_o_id(const uint64_t tid, const Integer no_o_id);
    void update_no_d_id(const uint64_t tid, const Integer no_d_id);
    void update_no_w_id(const uint64_t tid, const Integer no_w_id);

    void remove(const uint64_t tid);

    static const std::vector<IU> IUs;

    // Primary Key for: no_w_id, no_d_id, no_o_id
    std::unordered_map<Key<Integer, Integer, Integer>, uint64_t> primary_key;

 private:
    std::vector<bool> deleted_tuples;
    size_t first_free_pos = 0;

    std::vector<Integer> no_o_id;
    std::vector<Integer> no_d_id;
    std::vector<Integer> no_w_id;
};

class orderTable : public TableBase {
 public:
    uint64_t insert(
        const Integer o_id,
        const Integer o_d_id,
        const Integer o_w_id,
        const Integer o_c_id,
        const Timestamp o_entry_d,
        const Integer o_carrier_id,
        const Numeric<2, 0> o_ol_cnt,
        const Numeric<1, 0> o_all_local);

    std::optional<Integer> get_o_id(const uint64_t tid);
    std::optional<Integer> get_o_d_id(const uint64_t tid);
    std::optional<Integer> get_o_w_id(const uint64_t tid);
    std::optional<Integer> get_o_c_id(const uint64_t tid);
    std::optional<Timestamp> get_o_entry_d(const uint64_t tid);
    std::optional<Integer> get_o_carrier_id(const uint64_t tid);
    std::optional<Numeric<2, 0>> get_o_ol_cnt(const uint64_t tid);
    std::optional<Numeric<1, 0>> get_o_all_local(const uint64_t tid);

    void update_o_id(const uint64_t tid, const Integer o_id);
    void update_o_d_id(const uint64_t tid, const Integer o_d_id);
    void update_o_w_id(const uint64_t tid, const Integer o_w_id);
    void update_o_c_id(const uint64_t tid, const Integer o_c_id);
    void update_o_entry_d(const uint64_t tid, const Timestamp o_entry_d);
    void update_o_carrier_id(const uint64_t tid, const Integer o_carrier_id);
    void update_o_ol_cnt(const uint64_t tid, const Numeric<2, 0> o_ol_cnt);
    void update_o_all_local(const uint64_t tid, const Numeric<1, 0> o_all_local);

    void remove(const uint64_t tid);

    static const std::vector<IU> IUs;

    // Primary Key for: o_w_id, o_d_id, o_id
    std::unordered_map<Key<Integer, Integer, Integer>, uint64_t> primary_key;

 private:
    std::vector<bool> deleted_tuples;
    size_t first_free_pos = 0;

    std::vector<Integer> o_id;
    std::vector<Integer> o_d_id;
    std::vector<Integer> o_w_id;
    std::vector<Integer> o_c_id;
    std::vector<Timestamp> o_entry_d;
    std::vector<Integer> o_carrier_id;
    std::vector<Numeric<2, 0>> o_ol_cnt;
    std::vector<Numeric<1, 0>> o_all_local;
};

class orderlineTable : public TableBase {
 public:
    uint64_t insert(
        const Integer ol_o_id,
        const Integer ol_d_id,
        const Integer ol_w_id,
        const Integer ol_number,
        const Integer ol_i_id,
        const Integer ol_supply_w_id,
        const Timestamp ol_delivery_d,
        const Numeric<2, 0> ol_quantity,
        const Numeric<6, 2> ol_amount,
        const Char<24> ol_dist_info);

    std::optional<Integer> get_ol_o_id(const uint64_t tid);
    std::optional<Integer> get_ol_d_id(const uint64_t tid);
    std::optional<Integer> get_ol_w_id(const uint64_t tid);
    std::optional<Integer> get_ol_number(const uint64_t tid);
    std::optional<Integer> get_ol_i_id(const uint64_t tid);
    std::optional<Integer> get_ol_supply_w_id(const uint64_t tid);
    std::optional<Timestamp> get_ol_delivery_d(const uint64_t tid);
    std::optional<Numeric<2, 0>> get_ol_quantity(const uint64_t tid);
    std::optional<Numeric<6, 2>> get_ol_amount(const uint64_t tid);
    std::optional<Char<24>> get_ol_dist_info(const uint64_t tid);

    void update_ol_o_id(const uint64_t tid, const Integer ol_o_id);
    void update_ol_d_id(const uint64_t tid, const Integer ol_d_id);
    void update_ol_w_id(const uint64_t tid, const Integer ol_w_id);
    void update_ol_number(const uint64_t tid, const Integer ol_number);
    void update_ol_i_id(const uint64_t tid, const Integer ol_i_id);
    void update_ol_supply_w_id(const uint64_t tid, const Integer ol_supply_w_id);
    void update_ol_delivery_d(const uint64_t tid, const Timestamp ol_delivery_d);
    void update_ol_quantity(const uint64_t tid, const Numeric<2, 0> ol_quantity);
    void update_ol_amount(const uint64_t tid, const Numeric<6, 2> ol_amount);
    void update_ol_dist_info(const uint64_t tid, const Char<24> ol_dist_info);

    void remove(const uint64_t tid);

    static const std::vector<IU> IUs;

    // Primary Key for: ol_w_id, ol_d_id, ol_o_id, ol_number
    std::unordered_map<Key<Integer, Integer, Integer, Integer>, uint64_t> primary_key;

 private:
    std::vector<bool> deleted_tuples;
    size_t first_free_pos = 0;

    std::vector<Integer> ol_o_id;
    std::vector<Integer> ol_d_id;
    std::vector<Integer> ol_w_id;
    std::vector<Integer> ol_number;
    std::vector<Integer> ol_i_id;
    std::vector<Integer> ol_supply_w_id;
    std::vector<Timestamp> ol_delivery_d;
    std::vector<Numeric<2, 0>> ol_quantity;
    std::vector<Numeric<6, 2>> ol_amount;
    std::vector<Char<24>> ol_dist_info;
};

class itemTable : public TableBase {
 public:
    uint64_t insert(
        const Integer i_id,
        const Integer i_im_id,
        const Varchar<24> i_name,
        const Numeric<5, 2> i_price,
        const Varchar<50> i_data);

    std::optional<Integer> get_i_id(const uint64_t tid);
    std::optional<Integer> get_i_im_id(const uint64_t tid);
    std::optional<Varchar<24>> get_i_name(const uint64_t tid);
    std::optional<Numeric<5, 2>> get_i_price(const uint64_t tid);
    std::optional<Varchar<50>> get_i_data(const uint64_t tid);

    void update_i_id(const uint64_t tid, const Integer i_id);
    void update_i_im_id(const uint64_t tid, const Integer i_im_id);
    void update_i_name(const uint64_t tid, const Varchar<24> i_name);
    void update_i_price(const uint64_t tid, const Numeric<5, 2> i_price);
    void update_i_data(const uint64_t tid, const Varchar<50> i_data);

    void remove(const uint64_t tid);

    static const std::vector<IU> IUs;

    // Primary Key for: i_id
    std::unordered_map<Key<Integer>, uint64_t> primary_key;

 private:
    std::vector<bool> deleted_tuples;
    size_t first_free_pos = 0;

    std::vector<Integer> i_id;
    std::vector<Integer> i_im_id;
    std::vector<Varchar<24>> i_name;
    std::vector<Numeric<5, 2>> i_price;
    std::vector<Varchar<50>> i_data;
};

class stockTable : public TableBase {
 public:
    uint64_t insert(
        const Integer s_i_id,
        const Integer s_w_id,
        const Numeric<4, 0> s_quantity,
        const Char<24> s_dist_01,
        const Char<24> s_dist_02,
        const Char<24> s_dist_03,
        const Char<24> s_dist_04,
        const Char<24> s_dist_05,
        const Char<24> s_dist_06,
        const Char<24> s_dist_07,
        const Char<24> s_dist_08,
        const Char<24> s_dist_09,
        const Char<24> s_dist_10,
        const Numeric<8, 0> s_ytd,
        const Numeric<4, 0> s_order_cnt,
        const Numeric<4, 0> s_remote_cnt,
        const Varchar<50> s_data);

    std::optional<Integer> get_s_i_id(const uint64_t tid);
    std::optional<Integer> get_s_w_id(const uint64_t tid);
    std::optional<Numeric<4, 0>> get_s_quantity(const uint64_t tid);
    std::optional<Char<24>> get_s_dist_01(const uint64_t tid);
    std::optional<Char<24>> get_s_dist_02(const uint64_t tid);
    std::optional<Char<24>> get_s_dist_03(const uint64_t tid);
    std::optional<Char<24>> get_s_dist_04(const uint64_t tid);
    std::optional<Char<24>> get_s_dist_05(const uint64_t tid);
    std::optional<Char<24>> get_s_dist_06(const uint64_t tid);
    std::optional<Char<24>> get_s_dist_07(const uint64_t tid);
    std::optional<Char<24>> get_s_dist_08(const uint64_t tid);
    std::optional<Char<24>> get_s_dist_09(const uint64_t tid);
    std::optional<Char<24>> get_s_dist_10(const uint64_t tid);
    std::optional<Numeric<8, 0>> get_s_ytd(const uint64_t tid);
    std::optional<Numeric<4, 0>> get_s_order_cnt(const uint64_t tid);
    std::optional<Numeric<4, 0>> get_s_remote_cnt(const uint64_t tid);
    std::optional<Varchar<50>> get_s_data(const uint64_t tid);

    void update_s_i_id(const uint64_t tid, const Integer s_i_id);
    void update_s_w_id(const uint64_t tid, const Integer s_w_id);
    void update_s_quantity(const uint64_t tid, const Numeric<4, 0> s_quantity);
    void update_s_dist_01(const uint64_t tid, const Char<24> s_dist_01);
    void update_s_dist_02(const uint64_t tid, const Char<24> s_dist_02);
    void update_s_dist_03(const uint64_t tid, const Char<24> s_dist_03);
    void update_s_dist_04(const uint64_t tid, const Char<24> s_dist_04);
    void update_s_dist_05(const uint64_t tid, const Char<24> s_dist_05);
    void update_s_dist_06(const uint64_t tid, const Char<24> s_dist_06);
    void update_s_dist_07(const uint64_t tid, const Char<24> s_dist_07);
    void update_s_dist_08(const uint64_t tid, const Char<24> s_dist_08);
    void update_s_dist_09(const uint64_t tid, const Char<24> s_dist_09);
    void update_s_dist_10(const uint64_t tid, const Char<24> s_dist_10);
    void update_s_ytd(const uint64_t tid, const Numeric<8, 0> s_ytd);
    void update_s_order_cnt(const uint64_t tid, const Numeric<4, 0> s_order_cnt);
    void update_s_remote_cnt(const uint64_t tid, const Numeric<4, 0> s_remote_cnt);
    void update_s_data(const uint64_t tid, const Varchar<50> s_data);

    void remove(const uint64_t tid);

    static const std::vector<IU> IUs;

    // Primary Key for: s_w_id, s_i_id
    std::unordered_map<Key<Integer, Integer>, uint64_t> primary_key;

 private:
    std::vector<bool> deleted_tuples;
    size_t first_free_pos = 0;

    std::vector<Integer> s_i_id;
    std::vector<Integer> s_w_id;
    std::vector<Numeric<4, 0>> s_quantity;
    std::vector<Char<24>> s_dist_01;
    std::vector<Char<24>> s_dist_02;
    std::vector<Char<24>> s_dist_03;
    std::vector<Char<24>> s_dist_04;
    std::vector<Char<24>> s_dist_05;
    std::vector<Char<24>> s_dist_06;
    std::vector<Char<24>> s_dist_07;
    std::vector<Char<24>> s_dist_08;
    std::vector<Char<24>> s_dist_09;
    std::vector<Char<24>> s_dist_10;
    std::vector<Numeric<8, 0>> s_ytd;
    std::vector<Numeric<4, 0>> s_order_cnt;
    std::vector<Numeric<4, 0>> s_remote_cnt;
    std::vector<Varchar<50>> s_data;
};


}  // namespace tpcc
}  // namespace imlab
#endif  // INCLUDE_IMLAB_SCHEMA_H_
