#include <18F46K20.h>

// #fuses hs,nolvp,protect,MCLR,NOPUT,BORV27
#fuses hs, nolvp, protect, MCLR, NOPUT, NOBROWNOUT

#device adc = 10
#use delay(clock = 24000000)
#include "lcd_lib_4bit.c"
// #include "DS1307.C"
#include "PCF8583.C"
#include <stdlib.h>
#include <MATH.H>
#include <stdio.h>
#include "headers/const.h"
#define MIN(i, j) (((i) < (j)) ? (i) : (j))
#define MAX(i, j) (((i) > (j)) ? (i) : (j))
//============================
#define sw_mode PIN_B0
#define sw_up PIN_B1
#define sw_down PIN_B6
#define sw_exit PIN_B7

#define clock_reset PIN_B0

// DEN LCD
#define backligh_lcd PIN_D2
#define backligh_on() output_high(backligh_lcd);
#define backligh_off() output_low(backligh_lcd);

// CHAN OUTPUT KHIEN AC
#define OUT_KHOI_DONG_TU1 PIN_A4
#define OUT_KHOI_DONG_TU2 PIN_C0

#define OUT_KHOI_DONG_TU1_ON() output_high(OUT_KHOI_DONG_TU1);
#define OUT_KHOI_DONG_TU1_OFF() output_low(OUT_KHOI_DONG_TU1);

#define OUT_KHOI_DONG_TU2_ON() output_high(OUT_KHOI_DONG_TU2);
#define OUT_KHOI_DONG_TU2_OFF() output_low(OUT_KHOI_DONG_TU2);

// CHAN OUTPUT KHIEN DC
#define OUT_START_MN PIN_B3
#define OUT_STOP_MN PIN_B4
#define OUT_PREHEAT_MN PIN_B5
// #define OUT_FUEL_MN               PIN_B2
#define OUT_FUEL_MN PIN_C7
#define OUT_AIR_MN PIN_C1 // dung cho may xang

#define OUT_START_MN_ON() output_high(OUT_START_MN);
#define OUT_START_MN_OFF() output_low(OUT_START_MN);

#define OUT_PREHEAT_MN_ON() output_high(OUT_PREHEAT_MN);
#define OUT_PREHEAT_MN_OFF() output_low(OUT_PREHEAT_MN);

#define OUT_STOP_MN_ON() output_high(OUT_STOP_MN);
#define OUT_STOP_MN_OFF() output_low(OUT_STOP_MN);

#define OUT_AIR_MN_ON() output_high(OUT_AIR_MN);
#define OUT_AIR_MN_OFF() output_low(OUT_AIR_MN);

#define OUT_FUEL_MN_ON() output_high(OUT_FUEL_MN);
#define OUT_FUEL_MN_OFF() output_low(OUT_FUEL_MN);

// CHAN INPUT REMOTE START
#define OUT_ACCU_ERROR PIN_E1
// #define INPUT_REMOTE            PIN_C7
// #define   val_remote()            input(INPUT_REMOTE)

// #define INPUT_CHARGE_DC            PIN_C7
// #define   val_ChargeDC()            input(INPUT_CHARGE_DC)

// LED HIEN THI LED
#define OUT_LED1 PIN_D7
// #define   OUT_LED2               PIN_C7
#define OUT_LED3 PIN_C6

#define OUT_LED_STATUS_ON() output_high(OUT_LED1);
#define OUT_LED_STATUS_OFF() output_low(OUT_LED1);

// #define OUT_LED_LOW_DC_ON()         output_high   (OUT_LED2);
// #define OUT_LED_LOW_DC_OFF()      output_low   (OUT_LED2);

#define OUT_LED_FAIL_MN_ON() output_high(OUT_LED3);
#define OUT_LED_FAIL_MN_OFF() output_low(OUT_LED3);

// CHAN INPUT MAY NO
#define INPUT_MN_Pressure PIN_C2
#define INPUT_MN_temperature PIN_C3

#define val_mn_pressure() input(INPUT_MN_Pressure)
#define val_mn_temp() input(INPUT_MN_temperature)

// CHAN INPUT ADC MAY NO / ENABLE ADC
#define EN_MN_PRESSURE PIN_E2
#define EN_MN_TEMPERATURE PIN_A3

#define EN_MN_PRESSURE_ON() output_low(EN_MN_PRESSURE);
#define EN_MN_PRESSURE_OFF() output_high(EN_MN_PRESSURE);

#define EN_MN_TEMPERATURE_ON() output_low(EN_MN_TEMPERATURE);
#define EN_MN_TEMPERATURE_OFF() output_high(EN_MN_TEMPERATURE);

//===================
#define clear_lcd() lcd_printf(0);
#define entersetup() lcd_printf(1);
#define sch_1_s_set() lcd_printf(2);
#define ac_1_pha() lcd_printf(3);
#define ac_3_pha() lcd_printf(4);
#define ac_max_vol() lcd_printf(5);
#define ac_min_vol() lcd_printf(6);
#define tgian_on_dinh_ac() lcd_printf(7);
#define mn_max_vol() lcd_printf(8);
#define mn_min_vol() lcd_printf(9);
#define solan_khoidong() lcd_printf(10);
#define tg_on_lientuc() lcd_printf(11);
#define tg_suoi_mn() lcd_printf(12);
#define tg_nhan_giu_start() lcd_printf(13);
#define tg_start_start() lcd_printf(14);
#define tg_on_dinh_dienap_mn() lcd_printf(15);
#define tg_lamnguoi_mn() lcd_printf(16);
#define dienapmncao() lcd_printf(17);
#define dienapmnthap() lcd_printf(18);
#define test_mn() lcd_printf(19);
#define dienap_mn() lcd_printf(20);
#define enterview() lcd_printf(21);
#define yesno() lcd_printf(22);
#define mn_tudong() lcd_printf(23);
#define thieuapxuatnhot() lcd_printf(24);

#define loading() lcd_printf(25);
#define doi_ondinh_ac() lcd_printf(26);
#define stop_mn() lcd_printf(27);
#define nguondienluoi() lcd_printf(28);
#define qua_nhiet_ket_nc() lcd_printf(29);

#define trang_thai_co_dien_luoi() lcd_printf(30);

#define nguondienmntudong() lcd_printf(31);
#define ondinh_mn() lcd_printf(32);
#define thoigianchaymn() lcd_printf(33);
#define mpd_restart() lcd_printf(34);
#define mn_fail() lcd_printf(35);
#define mn_giainhiet() lcd_printf(36);
#define lamnongmn() lcd_printf(37);
#define thoigianlamnong() lcd_printf(38);
#define start_thucong() lcd_printf(39);
#define test_khoi_dong() lcd_printf(40);
#define test_tg_vol_mn() lcd_printf(41);
#define sudung() lcd_printf(42);
#define kosudung() lcd_printf(43);
#define sac_accu_mn_cao() lcd_printf(44);
#define chukytestmn() lcd_printf(45);
#define khancap() lcd_printf(46);
#define log_tg_run() lcd_printf(47);

// #define log_fail_start()      lcd_printf(48);
#define log_error_code() lcd_printf(48);
#define log_fail_ac() lcd_printf(49);
#define giainhietmn() lcd_printf(50);
#define tg_giainhietmn() lcd_printf(51);
#define tg_start_mpn_tudong() lcd_printf(52);
#define tg_watting_ms_td() lcd_printf(53);
#define nguondienmnthucong() lcd_printf(54);
#define ac_display() lcd_printf(55);
#define mn_thucong_4tiepdiem() lcd_printf(57);
#define val_phut_printf() lcd_printf(58);
#define val_lan_printf() lcd_printf(59);
#define val_phut_giay_printf() lcd_printf(60);
#define val_giay_printf() lcd_printf(61);
#define val_nhietdo_nuoc_printf() lcd_printf(62);
#define overload() lcd_printf(64);
#define view_read_data() lcd_printf(65);
#define view_timer_mn_fail() lcd_printf(66);

#define remote_display() lcd_printf(67);

#define view_gio_ht() lcd_printf(68);
#define set_thu() lcd_printf(69);
#define set_gio() lcd_printf(70);
#define set_phut() lcd_printf(71);

#define test_thu() lcd_printf(72);
#define test_gio() lcd_printf(73);
#define test_phut() lcd_printf(74);
#define val_tuan_printf() lcd_printf(75);

#define set_hour_save_energy_from() lcd_printf(76);
#define set_min_save_energy_from() lcd_printf(77);
#define set_hour_save_energy_to() lcd_printf(78);
#define set_min_save_energy_to() lcd_printf(79);
#define set_dc_low_accu() lcd_printf(80);
#define set_delta_dc_low_accu() lcd_printf(81);

// #define ()         lcd_printf();

#define ds1307_counter_ac_fail 0x11
#define ds1307_error_code ds1307_counter_ac_fail + 1                    // 0x12
#define ds1307_tong_gio_chay_mn ds1307_error_code + 1                   // 0x13   //2byte
#define ds1307_tong_phut_chay_mn ds1307_tong_gio_chay_mn + 2            // 0x15
#define ds1307_energy_save ds1307_tong_phut_chay_mn + 1                 // 0x16
#define ds1307_level_set_ac_fail ds1307_energy_save + 1                 // 0x17
#define ds1307_ac_vol_max ds1307_level_set_ac_fail + 1                  // 0x18   //2byte
#define ds1307_ac_vol_min ds1307_ac_vol_max + 2                         // 0x1a
#define ds1307_val_tg_on_dinh_ac ds1307_ac_vol_min + 1                  // 0x1b
#define ds1307_mn_vol_max ds1307_val_tg_on_dinh_ac + 1                  // 0x1c
#define ds1307_mn_vol_min ds1307_mn_vol_max + 1                         // 0x1d
#define ds1307_val_counter_start ds1307_mn_vol_min + 1                  // 0x1e
#define ds1307_val_tg_run_on ds1307_val_counter_start + 1               // 0x1f
#define ds1307_val_tg_preheat ds1307_val_tg_run_on + 1                  // 0x20
#define ds1307_val_tg_press_start ds1307_val_tg_preheat + 1             // 0x21
#define ds1307_val_tg_on_dinh_mn ds1307_val_tg_press_start + 1          // 0x22
#define ds1307_val_tg_off_mn ds1307_val_tg_on_dinh_mn + 1               // 0x23
#define ds1307_val_tg_giainhiet ds1307_val_tg_off_mn + 1                // 0x24
#define ds1307_en_temp_mn ds1307_val_tg_giainhiet + 1                   // 0x25
#define ds1307_en_pressure_mn ds1307_en_temp_mn + 1                     // 0x26
#define ds1307_val_timer_delay_run_mn ds1307_en_pressure_mn + 1         // 0x27
#define ds1307_style_mod_ac ds1307_val_timer_delay_run_mn + 1           // 0x28
#define ds1307_flag_zero_delay_run_ac ds1307_style_mod_ac + 1           // 0x29
#define ds1307_flag_zero_delay_run_mn ds1307_flag_zero_delay_run_ac + 1 // 0x2a
#define ds1307_val_tg_start_start ds1307_flag_zero_delay_run_mn + 1     // 0x2b
#define ds1307_val_counter_ac_fail ds1307_val_tg_start_start + 1        // 0x2c
#define ds1307_val_counter_mn_fail ds1307_val_counter_ac_fail + 1       // 0x2d
#define ds1307_val_tg_press_stop ds1307_val_counter_mn_fail + 1         // 0x2e
#define ds1307_en_temp_adc_mn ds1307_val_tg_press_stop + 1              // 0x2f
#define ds1307_en_pressure_adc_mn ds1307_en_temp_adc_mn + 1             // 0x30
#define ds1307_list_resistor_pressure ds1307_en_pressure_adc_mn + 1     // 0x31 //6byte
#define ds1307_list_resistor_temp ds1307_list_resistor_pressure + 6     // 0x37 //11byte
#define ds1307_temp_adc_max ds1307_list_resistor_temp + 11              // 0x42
#define ds1307_pressure_adc_max ds1307_temp_adc_max + 1                 // 0x43

#define ds1307_val_tg_air ds1307_pressure_adc_max + 1  // 0x44
#define ds1307_time_check_sensor ds1307_val_tg_air + 1 // 0x45

#define ds1307_thu_test ds1307_time_check_sensor + 1 // 0x46
#define ds1307_gio_test ds1307_thu_test + 1          // 0x47
#define ds1307_phut_test ds1307_gio_test + 1         // 0x48
// #define   ds1307_val_remote_start         0x49
#define ds1307_chu_ky_test ds1307_phut_test + 1           // 0x4a
#define ds1307_chu_ky_hien_tai ds1307_chu_ky_test + 1     // 0x4b
#define ds1307_Control_input ds1307_chu_ky_hien_tai + 1   // 0x4c
#define ds1307_volt_Protect_Accu ds1307_Control_input + 1 // 0x4d

#define ds1307_Hash_Data ds1307_volt_Protect_Accu + 1 // 2byte
#define ds1307_Cert_Data ds1307_Hash_Data + 2         // 2byte

#define ds1307_Hour_Save_From ds1307_Cert_Data + 2     // 1byte
#define ds1307_Min_Save_From ds1307_Hour_Save_From + 1 // 1byte
#define ds1307_Hour_Save_To ds1307_Min_Save_From + 1   // 1byte
#define ds1307_Min_Save_To ds1307_Hour_Save_To + 1     // 1byte

// bit cuoi cung ff

// eerom
//=========================================================================
#define ree(x) read_eeprom(x);
#define ree16(x) read_eeprom16(x);
#define wee(x, y) write_eeprom(x, y);
#define wee16(x, y) write_eeprom16(x, y);

#define BEGIN_EEADDR 0x00
#define ee_counter_ac_fail BEGIN_EEADDR + 0
#define ee_error_code ee_counter_ac_fail + 1
#define ee_tong_gio_chay_mn ee_error_code + 1 // 2byte
#define ee_tong_phut_chay_mn ee_tong_gio_chay_mn + 2
#define ee_energy_save ee_tong_phut_chay_mn + 1
#define ee_level_set_ac_fail ee_energy_save + 1
#define ee_ac_vol_max ee_level_set_ac_fail + 1 // 2byte
#define ee_ac_vol_min ee_ac_vol_max + 2
#define ee_val_tg_on_dinh_ac ee_ac_vol_min + 1
#define ee_mn_vol_max ee_val_tg_on_dinh_ac + 1
#define ee_mn_vol_min ee_mn_vol_max + 1
#define ee_val_counter_start ee_mn_vol_min + 1
#define ee_val_tg_run_on ee_val_counter_start + 1
#define ee_val_tg_preheat ee_val_tg_run_on + 1
#define ee_val_tg_press_start ee_val_tg_preheat + 1
#define ee_val_tg_on_dinh_mn ee_val_tg_press_start + 1
#define ee_val_tg_off_mn ee_val_tg_on_dinh_mn + 1
#define ee_val_tg_giainhiet ee_val_tg_off_mn + 1
#define ee_en_temp_mn ee_val_tg_giainhiet + 1
#define ee_en_pressure_mn ee_en_temp_mn + 1
#define ee_val_timer_delay_run_mn ee_en_pressure_mn + 1
#define ee_style_mod_ac ee_val_timer_delay_run_mn + 1
#define ee_flag_zero_delay_run_ac ee_style_mod_ac + 1
#define ee_flag_zero_delay_run_mn ee_flag_zero_delay_run_ac + 1
#define ee_val_tg_start_start ee_flag_zero_delay_run_mn + 1
#define ee_val_counter_ac_fail ee_val_tg_start_start + 1
#define ee_val_counter_mn_fail ee_val_counter_ac_fail + 1
#define ee_val_tg_press_stop ee_val_counter_mn_fail + 1
#define ee_en_temp_adc_mn ee_val_tg_press_stop + 1
#define ee_en_pressure_adc_mn ee_en_temp_adc_mn + 1
#define ee_list_resistor_pressure ee_en_pressure_adc_mn + 1 // 6byte
#define ee_list_resistor_temp ee_list_resistor_pressure + 6 // 11byte
#define ee_temp_adc_max ee_list_resistor_temp + 11
#define ee_pressure_adc_max ee_temp_adc_max + 1

#define ee_val_tg_air ee_pressure_adc_max + 1
#define ee_time_check_sensor ee_val_tg_air + 1

#define ee_thu_test ee_time_check_sensor + 1
#define ee_gio_test ee_thu_test + 1
#define ee_phut_test ee_gio_test + 1
#define ee_chu_ky_test ee_phut_test + 1
#define ee_chu_ky_hien_tai ee_chu_ky_test + 1
#define ee_Control_input ee_chu_ky_hien_tai + 1
#define ee_volt_Protect_Accu ee_Control_input + 1

#define ee_Hash_Data ee_volt_Protect_Accu + 1 // 2byte
#define ee_Cert_Data ee_Hash_Data + 2         // 2byte

#define ee_Hour_Save_From ee_Cert_Data + 2     // 1byte
#define ee_Min_Save_From ee_Hour_Save_From + 1 // 1byte
#define ee_Hour_Save_To ee_Min_Save_From + 1   // 1byte
#define ee_Min_Save_To ee_Hour_Save_To + 1     // 1byte

//=============================================================
// khai bao bien
long i = 0;

unsigned char val_number_defaul[11] = {"0123456789"};
// con tro phuc vu cai dat
char val_string_run_loop = 0;
char *sch_1 = 0, *sch_2 = 0, val_sch_1 = 0, val_sch_2 = 0;
#define size_pass 5
char password[5] = {"1111"};
char passwordadmin[5] = {"2222"};
char str_temp[25] = {0};
char verson_fw[16] = {"FW=2024VNPTAG"};
char time_reset_password = 0;
short flag_admin = 0;
short waitingData = 1;
long val_printf = 0;
float val_printf_1 = 0;
char state_main = 0;
char mode = 0, mode_sub = 0, mode_sub_1 = 0;
short refresh_menu = 0;
short refresh_menu_sub = 0;
char flag_timer_1s = 0;
char flag_refresh_display = 0;

// short   flag_save_data=0;

char sum_out = 0, sum_out_old = 0, loop_not_display = 0;

char view_test_progam = 0;
long timer_backlight = 0;
char pwm_lcd = 0;
char timer_exit = 0;
char counter_reset = 0;
char counter_view_debug = 0;
//   short   status_backlight=0;

float adc_pha1 = 0, adc_pha2 = 0, adc_pha3 = 0;
float adc_mn_1 = 0, adc_mn_2 = 0, adc_mn_display = 0;
float adc_temp = 0;
char process_kdt_ac = 0;
char process_kdt_mn = 0;

float adc_pha_bak = 0; // hien thi trung binh

long Hash_Data = 0;

// 220vac
unsigned char ac_vol_min = 0;
unsigned long ac_vol_max = 0;
char val_tg_on_dinh_ac = 0, tg_on_dinh_ac = 0;
short ac_vol_fail = 1;
short ac1_vol_fail = 0, ac2_vol_fail = 0, ac3_vol_fail = 0;
short back_ac_flag_fail = 0;
char counter_ac_fail = 0;
char style_mod_ac = 0;
char counter_ac_pha1_fail = 1, counter_ac_pha2_fail = 1, counter_ac_pha3_fail = 1;
char level_set_ac_fail = 0;
char val_counter_ac_fail = 5;

// ac mn
unsigned char mn_vol_max = 0, mn_vol_min = 0;
char counter_start = 0, val_counter_start = 0;
char val_tg_run_on = 0, tg_run_on = 0;
char tg_phut_run_on = 0;
char val_tg_preheat = 0, tg_preheat = 0;
char val_tg_press_start = 0, tg_press_start = 0;
char val_tg_press_stop = 0, tg_press_stop = 0;
char val_tg_start_start = 0, tg_start_start = 0;
char val_tg_on_dinh_mn = 0, tg_on_dinh_mn = 0;
char val_tg_off_mn = 0;
char val_tg_air = 0, tg_air = 0;
long tg_off_mn = 0;
short mn_vol_fail = 0;
char val_tg_giainhiet = 0, tg_giainhiet = 0; // TIMER tam dung
long tong_gio_chay_mn = 0;
char tong_phut_chay_mn = 0;
short flag_save_tg_chay_mn = 0;
char error_code = 0;
// float   error_value=0;

char fail_pressure_mn = 0, en_pressure_mn = 0;
char fail_temp_mn = 0, en_temp_mn = 0;

char counter_mn_fail = 0;
char val_counter_mn_fail = 0;

// test   mn
short val_test_mn = 0;
char tg_run_test = 0;

short remote_start = 0;
char counter_remote_start = 0;
//   char   val_remote_start =1;

short fail_ChargeDC = 0;
char Control_input = 0;
char couter_fail_ChargeDC = 0;
float adc_ChargeDC = 0;
float volt_ChargeDC = 0;
float volt_Protect_Accu = 0;

// tiet kiem nang luong
char energy_save = 0;
char val_timer_delay_run_mn = 0;
long timer_delay_run_mn = 0; // tg tri hoan
long timer_save_oil_mn = 0;
char flag_zero_delay_run_mn = 0;
char timer_hour_fail_mn = 0, timer_min_fail_mn = 0, timer_sec_fail_mn = 0;
char gio_save_from = 23, phut_save_from = 0;
char gio_save_to = 6, phut_save_to = 0;

char flag_zero_delay_run_ac = 0;
// emergency
char counter_emergenry = 0;
short en_out_ac = 0;
short en_out_mn = 0;
short en_start_mn = 0;
short en_stop_mn = 0;
short en_preheat_mn = 0;
short en_fuel_mn = 0;
short en_air_mn = 0;
char val_progam = 0, val_progam_old = 0;
unsigned long counter_timer0 = 0;
short en_led_status = 0, en_led_fail_mn = 0;

// fix read adc
char pause_read_adc = 0;
short pause_clock_reset = 0;
// short   press_button=0;

float val_adc_pressure = 0;
float val_adc_temp = 0;
float resistor_pressure = 0, resistor_pressure_bak = 0;
float resistor_temp = 0, resistor_temp_bak = 0;

char time_test_khoi_dong_tu = 0;

unsigned char list_nhiet_do[11] = {60, 70, 80, 90, 100, 105, 110, 115, 120, 125, 130};
unsigned char list_dien_tro_nhiet_do[11] = {};
unsigned char list_ap_suat[4][6] = {{},
                                    {0, 1, 3, 5, 7, 10},
                                    {0, 1, 2, 3, 4, 5},
                                    {0, 1, 3, 5, 7, 10}};
unsigned char list_dien_tro_ap_suat[6] = {};

char val_temp_max = 0, val_pressure_max = 0;
float val_temp = 0, val_pressure = 0, val_temp_bak = 0, val_pressure_bak = 0;
char en_pressure_mn_adc = 0; // 0:disable - 1:10bar(184ohm) - 2:5bar(184ohm) - 3:tuy chinh
char fail_pressure_mn_adc = 0;
char en_temp_mn_adc = 0; // 0:disable - 1:120d0 - 2:150do - 3:tuy chinh
char fail_temp_mn_adc = 0;
char time_check_sensor = 0;

// test may theo chu ky
unsigned char thu_test = 0, gio_test = 0, phut_test = 0, chu_ky_test = 0, chu_ky_hien_tai = 0, val_printf_2 = 0;

short flag_switch = 0;
long tempnow = 0, temptest = 0, tempfrom = 0, tempto = 0;
int roll = 0;
//===============================
unsigned long ram_Hash_Data = 0;
unsigned long ram_Hash_Save = 0;
unsigned long ram_Cert_Save = 0;

unsigned long eerom_Hash_Data = 0;
unsigned long eerom_Hash_Save = 0;
unsigned long eerom_Cert_Save = 0;

unsigned long Cert_Data = 3107;
unsigned char stringData[16];

// phong accu
char flag_do_phong_accu = 0;
float input_dc_low = 0;
float delta_dc = 0;
char flag_accu_error = 0;

//===============================

char key_scan(void);
void process_menu(void);
void process_up(void);
void process_down(void);
void process_exit(void);
void display_center(void);
void lcd_printf(char code_printf);
void defaul_admin(void);
void defaul_data(void);
void write_data(void);
void read_data(void);
void auto_run(void);

void read_ram_ds1307(void);
void write_ram_ds1307(void);
void write_data_ee(void);
void disable_reset(void);
void Hash_Full(void);
void check_full(void);
float get_adc_accu(void);

// Phong Accu============
float get_adc_accu(void)
{
   float adc_accu = 0;
   SET_ADC_CHANNEL(5);
   for (int i = 2000; i != 0; i--)
   {
      float adc_temp = READ_ADC();
      adc_accu = adc_temp > adc_accu ? adc_temp : adc_accu;
   }
   adc_accu = (adc_accu - 19) * (52.9 / 869) + 1.1;
   return adc_accu;
}

//===============================
void main()
{
   time_test_khoi_dong_tu = 0;
   pause_read_adc = 12;
   pause_clock_reset = 0;
   timer_backlight = 240;

   mode = 0;
   time_reset_password = 0;

   disable_reset();
   // khoi dong mang hinh lcd
   LCD_Init();
   disable_reset();
   // khoi dong adc
   setup_adc(ADC_CLOCK_DIV_2 | ADC_TAD_MUL_2);
   //   SETUP_ADC_PORTS(sAN0|sAN1|sAN2|sAN3|sAN5|sAN6);
   SETUP_ADC_PORTS(sAN0 | sAN1 | sAN2 | sAN3 | sAN5);
   SETUP_TIMER_0(T0_INTERNAL | T0_DIV_4);
   enable_interrupts(INT_TIMER0);
   enable_interrupts(GLOBAL);
   clear_interrupt(INT_TIMER0);
   set_timer0(62536); //(24000000/128)/(65535-65160)=187500/375=500us

   EN_MN_TEMPERATURE_OFF();
   EN_MN_PRESSURE_OFF();

   PCF8583_read_datetime();

   read_ram_ds1307();

   while (waitingData)
   {
      disable_reset();
   }
   backligh_on();
   while (1)
   {
      EN_MN_TEMPERATURE_OFF();
      EN_MN_PRESSURE_OFF();

      PCF8583_read_datetime();

      disable_reset();
      restart_wdt();
      adc_temp = 0;

      // chuong trinh lam viec
      switch (state_main)
      {
      case 0: // khong lam gi ca
         check_full();
         break;

      case 1: // doc adc 1 pha theo thu tu 1/2/3 lan luoc khi mat dien luoi
         adc_pha1 = 0;
         adc_pha2 = 0;
         adc_pha3 = 0;
         SET_ADC_CHANNEL(0);

         READ_ADC(ADC_START_AND_READ);
         for (i = 2000; i != 0; i--)
         {
            adc_temp = READ_ADC();
            if (adc_temp > adc_pha1)
               adc_pha1 = adc_temp;
         }

         adc_pha1 = adc_pha1 * 0.6827;
         adc_pha1 = adc_pha1 + 13.273;
         if (adc_pha1 < 20)
            adc_pha1 = 0;

         // trung binh dien ap ac (tranh hien thi dinh xung nhon ac khi co dong tai)
         adc_pha1 = adc_pha1 + adc_pha_bak;
         adc_pha1 = adc_pha1 / 2;
         adc_pha_bak = adc_pha1;

         if (adc_pha1 < 20)
            adc_pha_bak = 0;

         switch (level_set_ac_fail)
         {        // kiem tra co ac trong khoan hoac muc
         default: // trong khoan 140--> 290 co dien
            if ((adc_pha1 > ac_vol_max) | (adc_pha1 < ac_vol_min))
            {
               if (counter_ac_pha1_fail < val_counter_ac_fail)
                  counter_ac_pha1_fail++;
            }

            if ((adc_pha1 < ac_vol_max - 5) & (adc_pha1 > ac_vol_min + 5))
            {
               if (counter_ac_pha1_fail != 0)
                  counter_ac_pha1_fail--;
            }
            break;

         case 1: // muc lon hon 140 co dien
            if (adc_pha1 >= ac_vol_min)
               if (counter_ac_pha1_fail != 0)
                  counter_ac_pha1_fail--;
            if (adc_pha1 < ac_vol_min)
               if (counter_ac_pha1_fail < val_counter_ac_fail)
                  counter_ac_pha1_fail++;
            break;
         }

         if (counter_ac_pha1_fail == 0)
            ac_vol_fail = 0;
         if (counter_ac_pha1_fail == val_counter_ac_fail)
         {
            ac_vol_fail = 1;
            val_test_mn = 0;
         }
         break;

      case 2: // pha 1
         adc_pha1 = 0;
         SET_ADC_CHANNEL(0);
         READ_ADC(ADC_START_AND_READ);
         for (i = 2000; i != 0; i--)
         {
            adc_temp = READ_ADC();
            if (adc_temp > adc_pha1)
               adc_pha1 = adc_temp;
         }

         adc_pha1 = adc_pha1 * 0.6827;
         adc_pha1 = adc_pha1 + 13.273;
         if (adc_pha1 < 20)
            adc_pha1 = 0;

         switch (level_set_ac_fail)
         {        // kiem tra co ac trong khoan hoac muc
         default: // trong khoan 140--> 290 co dien
            if ((adc_pha1 > ac_vol_max) | (adc_pha1 < ac_vol_min))
            {
               if (counter_ac_pha1_fail < val_counter_ac_fail)
                  counter_ac_pha1_fail++;
            }

            if ((adc_pha1 < ac_vol_max - 5) & (adc_pha1 > ac_vol_min + 5))
            {
               if (counter_ac_pha1_fail != 0)
                  counter_ac_pha1_fail--;
            }
            break;

         case 1: // muc lon hon 140 co dien
            if (adc_pha1 >= ac_vol_min)
               if (counter_ac_pha1_fail != 0)
                  counter_ac_pha1_fail--;
            if (adc_pha1 < ac_vol_min)
               if (counter_ac_pha1_fail < val_counter_ac_fail)
                  counter_ac_pha1_fail++;
            break;
         }

         if (!counter_ac_pha1_fail)
            ac1_vol_fail = 0;
         if (counter_ac_pha1_fail == val_counter_ac_fail)
         {
            ac1_vol_fail = 1;
            val_test_mn = 0;
         }
         break;

      case 3: // doc adc pha 2
         adc_pha2 = 0;
         SET_ADC_CHANNEL(1);
         for (i = 2000; i != 0; i--)
         {
            adc_temp = READ_ADC();
            if (adc_temp > adc_pha2)
               adc_pha2 = adc_temp;
         }

         adc_pha2 = adc_pha2 * 0.6827;
         adc_pha2 = adc_pha2 + 13.273;
         if (adc_pha2 < 20)
            adc_pha2 = 0;

         switch (level_set_ac_fail)
         {        // kiem tra co ac trong khoan hoac muc
         default: // trong khoan 140--> 290 co dien
            if ((adc_pha2 > ac_vol_max) | (adc_pha2 < ac_vol_min))
            {
               if (counter_ac_pha2_fail < val_counter_ac_fail)
                  counter_ac_pha2_fail++;
            }

            if ((adc_pha2 < ac_vol_max - 5) & (adc_pha2 > ac_vol_min + 5))
            {
               if (counter_ac_pha2_fail != 0)
                  counter_ac_pha2_fail--;
            }
            break;

         case 1: // muc lon hon 140 co dien
            if (adc_pha2 >= ac_vol_min)
               if (counter_ac_pha2_fail != 0)
                  counter_ac_pha2_fail--;
            if (adc_pha2 < ac_vol_min)
               if (counter_ac_pha2_fail < val_counter_ac_fail)
                  counter_ac_pha2_fail++;
            break;
         }

         if (!counter_ac_pha2_fail)
            ac2_vol_fail = 0;
         if (counter_ac_pha2_fail == val_counter_ac_fail)
         {
            ac2_vol_fail = 1;
            val_test_mn = 0;
         }
         break;

      case 4: // doc adc pha 3
         adc_pha3 = 0;
         SET_ADC_CHANNEL(2);
         for (i = 2000; i != 0; i--)
         {
            adc_temp = READ_ADC();
            if (adc_temp > adc_pha3)
               adc_pha3 = adc_temp;
         }

         adc_pha3 = adc_pha3 * 0.6827;
         adc_pha3 = adc_pha3 + 13.273;
         if (adc_pha3 < 20)
            adc_pha3 = 0;

         switch (level_set_ac_fail)
         {        // kiem tra co ac trong khoan hoac muc
         default: // trong khoan 140--> 290 co dien
            if ((adc_pha3 > ac_vol_max) | (adc_pha3 < ac_vol_min))
            {
               if (counter_ac_pha3_fail < val_counter_ac_fail)
                  counter_ac_pha3_fail++;
            }

            if ((adc_pha3 < ac_vol_max - 5) & (adc_pha3 > ac_vol_min + 5))
            {
               if (counter_ac_pha3_fail != 0)
                  counter_ac_pha3_fail--;
            }
            break;

         case 1: // muc lon hon 140 co dien
            if (adc_pha3 >= ac_vol_min)
               if (counter_ac_pha3_fail != 0)
                  counter_ac_pha3_fail--;
            if (adc_pha3 < ac_vol_min)
               if (counter_ac_pha3_fail < val_counter_ac_fail)
                  counter_ac_pha3_fail++;
            break;
         }

         if (!counter_ac_pha3_fail)
            ac3_vol_fail = 0;
         if (counter_ac_pha3_fail == val_counter_ac_fail)
         {
            ac3_vol_fail = 1;
            val_test_mn = 0;
         }

         // tong hop xem co mat pha
         ac_vol_fail = ac1_vol_fail | ac2_vol_fail | ac3_vol_fail;
         break;

      case 5: // doc adc may no lay trung binh tren tu quyet dinh
         // doc gia tri cam bien
         fail_pressure_mn = 0;
         fail_temp_mn = 0;
         fail_ChargeDC = 0;

         if (en_pressure_mn)
            fail_pressure_mn = !val_mn_pressure();
         if (en_temp_mn)
            fail_temp_mn = !val_mn_temp();

         // if(Control_input)      fail_ChargeDC       =   val_ChargeDC();
         // INPUT: // KO SU DUNG / REMOTE START / REMOTE + ACCU / ACCU MAX

         SET_ADC_CHANNEL(8);
         adc_ChargeDC = 0;
         for (i = 2000; i != 0; i--)
         {
            adc_temp = READ_ADC();
            if (adc_temp > adc_ChargeDC)
               adc_ChargeDC = adc_temp;
         }
         volt_ChargeDC = adc_ChargeDC / 10;

         switch (Control_input)
         {
         default: // KO SU DUNG
            remote_start = 0;
            fail_ChargeDC = 0;
            break;

         case 1: // REMOTE START
            remote_start = 0;
            fail_ChargeDC = 0;

            if (volt_ChargeDC > 5)
            {
               if (counter_remote_start < 5)
                  counter_remote_start++;
               if (counter_remote_start == 5)
                  remote_start = 1;
            }
            if (volt_ChargeDC < 1)
            {
               if (counter_remote_start > 0)
                  counter_remote_start--;
               if (counter_remote_start == 0)
                  remote_start = 0;
            }
            break;

         case 2: // REMOTE + ACCU
            remote_start = 0;
            fail_ChargeDC = 0;
            if (volt_ChargeDC > 5)
            {
               if (counter_remote_start < 5)
                  counter_remote_start++;
               if (counter_remote_start == 5)
                  remote_start = 1;
            }
            if (volt_ChargeDC < 1)
            {
               if (counter_remote_start > 0)
                  counter_remote_start--;
               if (counter_remote_start == 0)
                  remote_start = 0;
            }

            if (volt_ChargeDC > volt_Protect_Accu)
            {
               if (couter_fail_ChargeDC < 5)
                  couter_fail_ChargeDC++;
               if (couter_fail_ChargeDC == 5)
                  fail_ChargeDC = 1;
            }
            if (volt_ChargeDC < volt_Protect_Accu - 1.5)
            {
               if (couter_fail_ChargeDC > 0)
                  couter_fail_ChargeDC--;
               if (couter_fail_ChargeDC == 0)
                  fail_ChargeDC = 0;
            }
            break;

         case 3: // ACCU MAX
            remote_start = 0;
            fail_ChargeDC = 0;
            if (volt_ChargeDC > volt_Protect_Accu)
            {
               if (couter_fail_ChargeDC < 5)
                  couter_fail_ChargeDC++;
               if (couter_fail_ChargeDC == 5)
                  fail_ChargeDC = 1;
            }
            if (volt_ChargeDC < volt_Protect_Accu - 1.5)
            {
               if (couter_fail_ChargeDC > 0)
                  couter_fail_ChargeDC--;
               if (couter_fail_ChargeDC == 0)
                  fail_ChargeDC = 0;
            }
            break;
         }

         // doc adc
         adc_mn_2 = 0;
         SET_ADC_CHANNEL(4);
         for (i = 1000; i != 0; i--)
         {
            adc_temp = READ_ADC();
            if (adc_temp > adc_mn_2)
               adc_mn_2 = adc_temp;
         }
         adc_mn_2 = adc_mn_2 * 0.6827;
         adc_mn_2 = adc_mn_2 + 13.273;
         if (adc_mn_2 < 20)
            adc_mn_2 = 0;

         if (adc_mn_2 > 50)
         {
            OUT_START_MN_OFF();
            en_start_mn = 0;
            OUT_AIR_MN_OFF();
            en_air_mn = 0;
         }

         // trung binh dien ap may no (tranh hien thi dinh xung nhon ac khi co dong tai)
         if ((adc_mn_2 > mn_vol_max) | (adc_mn_2 < mn_vol_min))
         {
            if (counter_mn_fail < val_counter_mn_fail)
               counter_mn_fail++;
         }

         if ((adc_mn_2 < mn_vol_max - 5) & (adc_mn_2 > mn_vol_min + 5))
         {
            if (counter_mn_fail != 0)
               counter_mn_fail--;
         }
         if (counter_mn_fail == val_counter_mn_fail)
            mn_vol_fail = 1; // mat dien may no/ ngoai nguon
         if (counter_mn_fail == 0)
            mn_vol_fail = 0; // co dien may no
         break;

      case 6: // auto run
         auto_run();
         break;

      case 7: //
         EN_MN_PRESSURE_ON();
         SET_ADC_CHANNEL(5);
         val_adc_pressure = 0;
         resistor_pressure = 0;
         for (i = 2000; i != 0; i--)
         {
            adc_temp = READ_ADC();
            if (adc_temp > val_adc_pressure)
               val_adc_pressure = adc_temp;
         }
         EN_MN_TEMPERATURE_OFF();
         EN_MN_PRESSURE_OFF();

         resistor_pressure = 0.3242 * val_adc_pressure - 1.3231;

         resistor_pressure = (resistor_pressure * 2 + resistor_pressure_bak) / 3;
         resistor_pressure_bak = resistor_pressure;

         // noi suy ap xuat nhot
         val_pressure = 0;
         for (i = 0; i < 6; i++)
         {
            if ((resistor_pressure > list_dien_tro_ap_suat[i]) && (resistor_pressure < list_dien_tro_ap_suat[i + 1]))
            {
               val_sch_1 = list_dien_tro_ap_suat[i + 1] - list_dien_tro_ap_suat[i];
               val_pressure = list_ap_suat[en_pressure_mn_adc][i + 1] - list_ap_suat[en_pressure_mn_adc][i];
               val_pressure = val_pressure / val_sch_1;
               val_pressure = val_pressure * resistor_pressure;
               val_sch_1 = 0;
               goto pressure;
            }
         }

      pressure:
         val_pressure = val_pressure * 3 + val_pressure_bak;
         val_pressure = val_pressure / 4;
         val_pressure_bak = val_pressure;
         fail_pressure_mn_adc = 0;
         if ((en_pressure_mn_adc) & (val_pressure < val_pressure_max))
            fail_pressure_mn_adc = 1;
         break;

      case 8: //
         SET_ADC_CHANNEL(6);
         EN_MN_TEMPERATURE_ON();
         val_adc_temp = 0;
         resistor_temp = 0;
         for (i = 2000; i != 0; i--)
         {
            adc_temp = READ_ADC();
            if (adc_temp > val_adc_temp)
               val_adc_temp = adc_temp;
         }
         EN_MN_TEMPERATURE_OFF();
         EN_MN_PRESSURE_OFF();

         resistor_temp = 0.3242 * val_adc_temp - 1.3231;

         resistor_temp = (resistor_temp * 2 + resistor_temp_bak) / 3;
         resistor_temp_bak = resistor_temp;

         // noi suy nhiet do
         val_temp = 0;
         for (i = 0; i < 10; i++)
         {
            if (resistor_temp > list_dien_tro_nhiet_do[i + 1])
            {
               val_sch_1 = list_dien_tro_nhiet_do[i] - list_dien_tro_nhiet_do[i + 1];
               val_temp = list_nhiet_do[i + 1] - list_nhiet_do[i];

               val_temp = val_temp / val_sch_1;

               val_temp = val_temp * (resistor_temp - list_dien_tro_nhiet_do[i + 1]);

               val_temp = list_nhiet_do[i + 1] - val_temp;
               val_sch_1 = 0;
               goto temperature;
            }
         }

      temperature:
         val_temp = val_temp_bak + val_temp * 3;
         val_temp = val_temp / 4;
         val_temp_bak = val_temp;
         fail_temp_mn_adc = 1 && (en_temp_mn_adc) && (val_temp > val_temp_max);
         break;

      case 9:
         fail_pressure_mn = !val_mn_pressure() & 1;
         fail_temp_mn = !val_mn_temp() & 1;
         break;

      case 10:
         SET_ADC_CHANNEL(8);
         adc_ChargeDC = 0;
         for (i = 2000; i != 0; i--)
         {
            adc_temp = READ_ADC();
            if (adc_temp > adc_ChargeDC)
               adc_ChargeDC = adc_temp;
         }
         volt_ChargeDC = adc_ChargeDC / 10;
         break;
      }

      switch (mode)
      {
      case 0:
         switch (view_test_progam)
         {
         default: // mang hinh binh thuong
         code_run:
            if (++state_main > 8)
               state_main = 0; // xu ly du lieu nhan duoc

            switch (state_main)
            {
            case 1: // 3 pha
               if (style_mod_ac == 1)
                  state_main = 2;
               break;

            case 2: // 1 pha
               if (style_mod_ac == 0)
                  state_main = 5;
               break;
            }

            switch (val_progam)
            {
            default:
            case 0:   // co dien luoi
            case 96:  // tri hoan thoi gian
            case 224: // xoa chuong trinh test may no
            case 240: // xoa chuong trinh test may no
               if (state_main == 7)
                  state_main = 0;
               break;

            case 112: // chay may no
            case 129: // remote start
               switch (process_kdt_mn)
               {
               case 5: // ket thuc suoi may no
                  if (state_main == 7)
                     state_main = 5; // xu ly du lieu nhan duoc
                  break;

               case 6: // khoi dong may no
                  if (state_main == 7)
                     state_main = 5; // xu ly du lieu nhan duoc
                  break;

               case 7: // nha start khi co nguon hoat het thoi gian
                  if (state_main == 7)
                     state_main = 5; // xu ly du lieu nhan duoc
                  break;
               }
               break;

            case 128: // test may no/dang co dien luoi
               switch (process_kdt_mn)
               {
               case 5: // ket thuc suoi may no
                  if (state_main == 7)
                     state_main = 5; // xu ly du lieu nhan duoc
                  break;

               case 6: // khoi dong may no
                  if (state_main == 7)
                     state_main = 5; // xu ly du lieu nhan duoc
                  break;

               case 7: // nha start khi co nguon hoat het thoi gian
                  if (state_main == 7)
                     state_main = 5; // xu ly du lieu nhan duoc
                  break;
               }
               break;
            }
            break;

         case 1: // mang hinh xem cac thong so dien app
            switch (val_string_run_loop)
            {
            default: // dien luoi ca 3 pha dua vao
               if (++state_main > 4)
                  state_main = 2;
               break;

            case 1: // may no
               state_main = 5;
               break;

            case 2: // chay het chuong trinh nhung binh thuong
               goto code_run;
               break;

            case 3: // ap xuat nhot
               state_main = 7;
               break;

            case 4:
               state_main = 8;
               break;

            case 5:
               state_main = 9;
               break;

            case 6:
               state_main = 10;
               break;
            }
            break;
         }
         // truong hop dat biet
         if (pause_read_adc > 8)
            state_main = 0; // xu ly du lieu nhan duoc
         if (pause_read_adc != 0 && state_main == 6)
            state_main = 0;
         break;

      case 1: // nhap mat khau
         state_main = 0;
         break;

      case 2: // cai dat
         state_main = 0;
         break;

      case 3: // cai dat
         state_main = 0;
         break;

      case 4: // cai dat
         state_main = 0;
         break;

      case 5: // cai dat
         state_main = 0;
         break;

      case 6: //
         state_main = 0;
         break;

      case 7: //
         state_main = 0;
         break;

      case 8: //
         state_main = 0;
         break;
      }

      // kiem tra phim nhan
      switch (key_scan())
      {
      case 0x01: // nut menu duoc nhan
         loop_not_display = 1;
         timer_exit = 30;
         timer_backlight = 240;
         process_menu();
         pause_read_adc = 12;
         en_start_mn = 0;
         OUT_START_MN_OFF();
         break;

      case 0x02: // nut up duoc nhan
         loop_not_display = 1;
         timer_exit = 120;
         timer_backlight = 240;
         process_up();
         pause_read_adc = 12;
         en_start_mn = 0;
         OUT_START_MN_OFF();
         break;

      case 0x03: // nut down duoc nhan
         loop_not_display = 1;
         timer_exit = 120;
         timer_backlight = 240;
         process_down();
         pause_read_adc = 12;
         en_start_mn = 0;
         OUT_START_MN_OFF();
         break;

      case 0x04: // nut exit duoc nhan
         loop_not_display = 1;
         timer_exit = 120;
         timer_backlight = 240;
         process_exit();
         pause_read_adc = 12;
         en_start_mn = 0;
         OUT_START_MN_OFF();
         break;
      }

      if (timer_exit == 0)
      {
         mode = 0;
         mode_sub = 0;
         flag_admin = 0;
         mode_sub_1 = 0;
      }

      OUT_KHOI_DONG_TU1_OFF();
      if (en_out_ac)
         OUT_KHOI_DONG_TU1_ON();

      OUT_KHOI_DONG_TU2_OFF();
      if (en_out_mn)
         OUT_KHOI_DONG_TU2_ON();

      OUT_START_MN_OFF();
      if (en_start_mn)
         OUT_START_MN_ON();

      OUT_AIR_MN_OFF();
      if (en_air_mn)
         OUT_AIR_MN_ON();

      OUT_LED_STATUS_OFF();
      if (en_led_status)
         OUT_LED_STATUS_ON();

      OUT_LED_FAIL_MN_OFF();
      if (en_led_fail_mn)
         OUT_LED_FAIL_MN_ON();

      OUT_PREHEAT_MN_OFF();
      if (en_preheat_mn)
         OUT_PREHEAT_MN_ON();

      OUT_STOP_MN_OFF();
      if (en_stop_mn)
         OUT_STOP_MN_ON();

      OUT_FUEL_MN_OFF();
      if (en_fuel_mn)
         OUT_FUEL_MN_ON();

      // chuong trinh hien thi
      sum_out = 0;
      if (en_out_ac == 1)
         sum_out++;
      if (en_out_mn == 1)
         sum_out++;
      if (en_start_mn == 1)
         sum_out++;
      if (en_stop_mn == 1)
         sum_out++;
      if (en_preheat_mn == 1)
         sum_out++;
      if (en_fuel_mn == 1)
         sum_out++;

      if (sum_out != sum_out_old)
      {
         switch (mode)
         {
         case 0: // mang hinh chinh
            loop_not_display = 5;
            break;

         case 1: // nhap mat khau
         case 2: // cai dat may lanh
         case 3: // cai dat thoi gian thuc
         case 4: // cai dat che do tiet kiem dien
         case 5: // cai dat canh bao
         case 7: // xem trang thai canh bao
         case 8: // cai dat mat dinh
            loop_not_display = 0;
            break;

         case 6: // dieu khien bang tay
            loop_not_display = 30;
            break;
         }
      }
      sum_out_old = sum_out;

      switch (loop_not_display)
      {
      case 1:
         LCD_Init();
         if (mode_sub == 0)
            refresh_menu = 1;
         if (mode_sub != 0)
            refresh_menu_sub = 1;
         loop_not_display--;
      case 0:
         display_center();
         break;

      default:
         loop_not_display--;
         break;
      }

      // if(press_button) {
      while (waitingData)
      {
         write_ram_ds1307();
         write_data_ee();
         Hash_Full();
         // press_button=0;
      }
   }
}

//=========================
void display_center(void)
{
   unsigned char menu_main[20][20] = {{""},
                                      {"MAT KHAU !"},
                                      {"NGUONG DIEN LUOI"},
                                      {"NGUONG M.P DIEN"},
                                      {"TIET KIEM DAU MN"},
                                      {"GIA TRI CAM BIEN"},
                                      {"TEST-REMOTE"},
                                      {"LOG MONITOR"},
                                      {"CAI MAC DINH"},
                                      {"DEBUG PROGRAM"}};

   unsigned char menu_sub2[14][20] = {{""},
                                      {"DIEN LUOI AC"},
                                      {"TRANG THAI CO AC"},
                                      {"D.AP NGUONG TREN"},
                                      {"D.AP NGUONG DUOI"},
                                      {"TG_ON K.DONG TU"},
                                      {"CHU KY QUET"}};

   unsigned char menu_sub3[22][20] = {{""},
                                      {"D.AP NGUONG TREN"},
                                      {"D.AP NGUONG DUOI"},
                                      {"SO LAN KHOI DONG"},
                                      {"TG CHAY LIEN TUC"},
                                      {"TG SUOI M.P.D"},
                                      {"TG NHAN START"},
                                      {"TG MO AIR"},
                                      {"TG START<->START"},
                                      {"TG NHAN STOP"},
                                      {"TG_ON K.DONG TU"},
                                      {"TG DUNG M.P.D"},
                                      {"TG TAM DUNG MPD"},
                                      {"CHU KY QUET"}};

   unsigned char menu_sub4[10][20] = {
       {""},
       {"TIET KIEM DAU MN"},  /*KO SU DUNG / TRI HOAN THOI GIAN/ KHUNG GIO TIET KIEM*/
       {"LV1: TRI HOAN"},     /*PHUT*/
       {"LV2: THEO GIO"},     /*GIO*/
       {"LV2: THEO GIO"},     /*PHUT*/
       {"LV2: THEO GIO"},     /*GIO*/
       {"LV2: THEO GIO"},     /*PHUT*/
       {"LV0: D.AP DC LOW"},  /*VOLT*/
       {"LV0: D.AP DC LOW"}}; /*DELTA VOLT*/

   unsigned char menu_sub5[8][20] = {{""},
                                     {"SO LAN MAT DIEN"},
                                     {"T.GIAN CHAY MN"},
                                     {"MAY NO ERROR LOG"},
                                     {"XOA LOG"}};

   unsigned char menu_sub6[12][17] = {{""},
                                      {"CB NHOT ON/OFF"},
                                      {"CB NUOC ON/OFF"},
                                      {"TUY CHINH INPUT"}, // KO SU DUNG / REMOTE START / REMOTE + ACCU / ACCU MAX
                                      {"BAO VE ACCU"},
                                      {"CB NHOT ADC"},
                                      {"GIA TRI CB NHOT"},
                                      {"CB NUOC ADC"},
                                      {"GIA TRI CB NUOC"},
                                      {"CB NHOT AN TOAN"},
                                      {"CB NUOC AN TOAN"},
                                      {"KIEM TRA CB SAU"}};

   unsigned char menu_sub7[12][17] = {
       {""},
       {"NGAY GIO H.TAI"}, // REALTIME
       {"C.DAT NGAY GIO"},
       {"C.DAT NGAY GIO"},
       {"C.DAT NGAY GIO"},
       {"THOI GIAN TEST"}, // SET THU
       {"THOI GIAN TEST"}, // SET GIO
       {"THOI GIAN TEST"}, // SET PHUT
       {"CHU KY TEST"},
       {"CHU KY H.TAI"},
       {"TEST MAY NO"}, // YES/NO
       {"REMOTE START"} // CO/KO
   };

   unsigned char style_vdo_pressure[3][17] = {{"KHONG SU DUNG"},
                                              {"10BAR"},
                                              {"5BAR"}};

   unsigned char style_vdo_temp[4][17] = {{"KHONG SU DUNG"},
                                          {"120 do C"},
                                          {"150 do C"}};

   unsigned char style_input_control[4][17] = {{"KHONG SU DUNG"},
                                               {"REMOTE START"},
                                               {"REMOTE/B.VE ACCU"},
                                               {"BAO VE ACCU"}};

   unsigned char style_energy_save[5][17] = {{"KHONG SU DUNG"},
                                             {"LV0: D.AP DC LOW"},
                                             {"LV1: TRI HOAN"},
                                             {"LV2: THEO GIO"},
                                             {"LV1 + LV2"}};

   if (refresh_menu)
   {
      LCD_PUTCMD(Line_1); // Dua hien thi chu dau dong hang` duoi
      PRINTF(LCD_PUTCHAR, "%s", menu_main[mode]);
      clear_lcd();
   }
   LCD_PUTCMD(Line_2); // Dua hien thi chu dau dong hang` duoi

   switch (mode)
   {
   case 0: //
      switch (view_test_progam)
      {
      case 1:                // mang hinh test
         LCD_PUTCMD(Line_1); // Dua hien thi chu dau dong hang` dau
         PRINTF(LCD_PUTCHAR, "%u %03u %02u %02u", state_main, val_progam, process_kdt_ac, process_kdt_mn);
         clear_lcd();
         LCD_PUTCMD(Line_2); // Dua hien thi chu dau dong hang` duoi

         switch (val_string_run_loop)
         {
         default:
            PRINTF(LCD_PUTCHAR, "1. %03.0f %03.0f %03.0f", adc_pha1, adc_pha2, adc_pha3);
            break;

         case 1:
            PRINTF(LCD_PUTCHAR, "2. %03.0f", adc_mn_2);
            break;

         case 2:
            PRINTF(LCD_PUTCHAR, "%03.0f %03.0f %03.0f %03.0f", adc_pha1, adc_pha2, adc_pha3, adc_mn_2);
            break;

         case 3:
            PRINTF(LCD_PUTCHAR, "4.%03.0f %02.0f", val_adc_pressure, resistor_pressure);
            LCD_PUTCHAR(0xF4);
            PRINTF(LCD_PUTCHAR, " %02.1fB", val_pressure);
            break;

         case 4:
            PRINTF(LCD_PUTCHAR, "5.%03.0f %02.0f", val_adc_temp, resistor_temp);
            LCD_PUTCHAR(0xF4);
            PRINTF(LCD_PUTCHAR, " %02.1f", val_temp);
            LCD_PUTCHAR(0xDF);
            LCD_PUTCHAR('C');
            break;

         case 5:
            PRINTF(LCD_PUTCHAR, "6.BAR:%01u TEMP:%01u", fail_pressure_mn, fail_temp_mn);
            break;

         case 6:
            PRINTF(LCD_PUTCHAR, "7.%03.0f DC:%02.1f", adc_ChargeDC, volt_ChargeDC);
            break;

         case 7:
            sprintf(stringData, "8.Ram %lu:%lu", ram_Hash_Data, ram_Hash_Save); // convert to string

            PRINTF(LCD_PUTCHAR, "%s", stringData);
            break;

         case 8:
            sprintf(stringData, "9.Cert %lu", ram_Cert_Save); // convert to string
            PRINTF(LCD_PUTCHAR, "%s", stringData);
            break;

         case 9:
            sprintf(stringData, "10.Rom %lu:%lu", eerom_Hash_Data, eerom_Hash_Save); // convert to string
            PRINTF(LCD_PUTCHAR, "%s", stringData);
            break;

         case 10:
            sprintf(stringData, "11.Cert %lu", eerom_Cert_Save); // convert to string
            PRINTF(LCD_PUTCHAR, "%s", stringData);
            break;

         case 11:
            sprintf(stringData, "11.Real %lu", Hash_Data); // convert to string
            PRINTF(LCD_PUTCHAR, "%s", stringData);
            break;
         }
         break;

      case 0: // mang hinh binh thuong
         if (pause_read_adc != 0)
         {
            LCD_PUTCMD(Line_1); // Dua hien thi chu dau dong hang` dau
            view_read_data();
            clear_lcd();
            LCD_PUTCMD(Line_2); // Dua hien thi chu dau dong hang` duoi
            loading();
         }
         else
         {
            switch (val_progam)
            {
            case 0:                // co dien luoi
               LCD_PUTCMD(Line_1); // Dua hien thi chu dau dong hang` dau
               PRINTF(LCD_PUTCHAR, "%s", menu_sub2[1]);
               clear_lcd();
               LCD_PUTCMD(Line_2); // Dua hien thi chu dau dong hang` duoi
               switch (process_kdt_ac)
               {
               case 0:
                  loading();
                  break;

               case 1:
                  doi_ondinh_ac();
                  break;

               case 2:
                  ac_display();
                  break;
               }
               break;

            case 128:              // test may no/dang co dien luoi
               LCD_PUTCMD(Line_1); // Dua hien thi chu dau dong hang` dau
               test_mn();
               clear_lcd();
               LCD_PUTCMD(Line_2); // Dua hien thi chu dau dong hang` duoi

               switch (process_kdt_mn)
               {
               default:
                  loading();
                  break;

               case 1: // kiêm tra dien ap may no có tren 50v!
               case 2: // kiem tra dien ap may no co nằm trong ngưởng cho phep
                  dienap_mn();
                  break;

               case 3: // chay đên khi het thoi gian cai dat
                  stop_mn();
                  break;

               case 4: // suoi may no
               case 5: // khoi dong may no
                  thoigianlamnong();
                  break;

               case 6: // nha start khi co nguon hoat het thoi gian
               case 7: // trì hoản trước khi nhan lại start
                  start_thucong();
                  break;

               case 8: // trì hoản trước khi nhan lại start
                  tg_watting_ms_td();
                  break;

               case 9: // may no fail, khoi dong that bai
                  mn_fail();
                  break;

               case 10: // het thoi gian chay/ lam mat roi ngat may no
               case 11:
               case 12:
               case 13:
                  LCD_PUTCMD(Line_1); // Dua hien thi chu dau dong hang` dau
                  mn_giainhiet();
                  clear_lcd();
                  LCD_PUTCMD(Line_2); // Dua hien thi chu dau dong hang` duoi
                  giainhietmn();
                  break;

               case 14: // MAY NO MAT NGUON
                  overload();
                  break;

               case 15: // thieu ap luc nhot
                  thieuapxuatnhot();
                  break;

               case 16: // nhiet do nuoc qua cao
                  qua_nhiet_ket_nc();
                  break;

               case 18: // may no ra dien qua ap
                  dienapmncao();
                  break;

               case 17: // may no ra dien ap thap
                  dienapmnthap();
                  break;

               case 19: // may no sac accu qua cao
                  sac_accu_mn_cao();
                  break;
               }
               break;

            case 96: // tri hoan thoi gian
                     // TODO uncomment
               //  LCD_PUTCMD(Line_1); // Dua hien thi chu dau dong hang` dau
               //  PRINTF(LCD_PUTCHAR, "%s", menu_main[4]);
               //  clear_lcd();
               //  LCD_PUTCMD(Line_2); // Dua hien thi chu dau dong hang` duoi
               //  val_printf = timer_delay_run_mn;
               //  val_phut_giay_printf();

               LCD_PUTCMD(Line_1); // Dua hien thi chu dau dong hang` dau
               PRINTF(LCD_PUTCHAR, "%s", menu_main[4]);
               clear_lcd();
               LCD_PUTCMD(Line_2); // Dua hien thi chu dau dong hang` duoi
               if (energy_save == 1)
               {
                  PRINTF(LCD_PUTCHAR, "ACCU:%02.1fV", get_adc_accu());
               }
               else
               {
                  val_printf = timer_delay_run_mn;
                  val_phut_giay_printf();
               }
               break;

            case 224:              // xoa chuong trinh test may no
            case 240:              // xoa chuong trinh test may no
               LCD_PUTCMD(Line_1); // Dua hien thi chu dau dong hang` dau
               view_read_data();
               clear_lcd();
               LCD_PUTCMD(Line_2); // Dua hien thi chu dau dong hang` duoi
               loading();
               break;

            case 112: // chay may no
               switch (process_kdt_mn)
               {
               default:
                  LCD_PUTCMD(Line_1); // Dua hien thi chu dau dong hang` dau
                  nguondienmnthucong();
                  clear_lcd();
                  LCD_PUTCMD(Line_2); // Dua hien thi chu dau dong hang` duoi
                  loading();
                  break;

               case 1:                // kiêm tra dien ap may no có tren 50v!
               case 2:                // kiem tra dien ap may no co nằm trong ngưởng cho phep
                  LCD_PUTCMD(Line_1); // Dua hien thi chu dau dong hang` dau
                  nguondienmnthucong();
                  clear_lcd();
                  LCD_PUTCMD(Line_2); // Dua hien thi chu dau dong hang` duoi
                  ondinh_mn();
                  break;

               case 3:                // chay đên khi het thoi gian cai dat
                  LCD_PUTCMD(Line_1); // Dua hien thi chu dau dong hang` dau
                  nguondienmnthucong();
                  clear_lcd();
                  LCD_PUTCMD(Line_2); // Dua hien thi chu dau dong hang` duoi
                  thoigianchaymn();
                  break;

               case 4:                // suoi may no
               case 5:                // khoi dong may no
                  LCD_PUTCMD(Line_1); // Dua hien thi chu dau dong hang` dau
                  lamnongmn();
                  clear_lcd();
                  LCD_PUTCMD(Line_2); // Dua hien thi chu dau dong hang` duoi
                  thoigianlamnong();
                  break;

               case 6:                // nha start khi co nguon hoat het thoi gian
               case 7:                // trì hoản trước khi nhan lại start
                  LCD_PUTCMD(Line_1); // Dua hien thi chu dau dong hang` dau
                  nguondienmnthucong();
                  clear_lcd();
                  LCD_PUTCMD(Line_2); // Dua hien thi chu dau dong hang` duoi
                  start_thucong();
                  break;

               case 8:                // trì hoản trước khi nhan lại start
                  LCD_PUTCMD(Line_1); // Dua hien thi chu dau dong hang` dau
                  mpd_restart();
                  clear_lcd();
                  LCD_PUTCMD(Line_2); // Dua hien thi chu dau dong hang` duoi
                  tg_watting_ms_td();
                  break;

               case 9:                // may no fail, khoi dong that bai
                  LCD_PUTCMD(Line_1); // Dua hien thi chu dau dong hang` dau
                  mn_fail();
                  clear_lcd();
                  LCD_PUTCMD(Line_2); // Dua hien thi chu dau dong hang` duoi
                  view_timer_mn_fail();
                  break;

               case 10: // het thoi gian chay/ lam mat roi ngat may no
               case 11:
               case 12:
               case 13:
                  LCD_PUTCMD(Line_1); // Dua hien thi chu dau dong hang` dau
                  mn_giainhiet();
                  clear_lcd();
                  LCD_PUTCMD(Line_2); // Dua hien thi chu dau dong hang` duoi
                  giainhietmn();
                  break;

               case 14:               // MAY NO MAT NGUON
                  LCD_PUTCMD(Line_1); // Dua hien thi chu dau dong hang` dau
                  overload();
                  clear_lcd();
                  LCD_PUTCMD(Line_2); // Dua hien thi chu dau dong hang` duoi
                  view_timer_mn_fail();
                  break;

               case 15:               // thieu ap luc nhot
                  LCD_PUTCMD(Line_1); // Dua hien thi chu dau dong hang` dau
                  thieuapxuatnhot();
                  clear_lcd();
                  LCD_PUTCMD(Line_2); // Dua hien thi chu dau dong hang` duoi
                  view_timer_mn_fail();

                  break;

               case 16:               // nhiet do nuoc qua cao
                  LCD_PUTCMD(Line_1); // Dua hien thi chu dau dong hang` dau
                  qua_nhiet_ket_nc();
                  clear_lcd();
                  LCD_PUTCMD(Line_2); // Dua hien thi chu dau dong hang` duoi
                  view_timer_mn_fail();
                  break;

               case 18:               // may no ra dien qua ap
                  LCD_PUTCMD(Line_1); // Dua hien thi chu dau dong hang` dau
                  dienapmncao();
                  clear_lcd();
                  LCD_PUTCMD(Line_2); // Dua hien thi chu dau dong hang` duoi
                  view_timer_mn_fail();
                  break;

               case 17:               // may no ra dien ap thap
                  LCD_PUTCMD(Line_1); // Dua hien thi chu dau dong hang` dau
                  dienapmnthap();
                  clear_lcd();
                  LCD_PUTCMD(Line_2); // Dua hien thi chu dau dong hang` duoi
                  view_timer_mn_fail();
                  break;

               case 19:               // may no sac accu qua cao
                  LCD_PUTCMD(Line_1); // Dua hien thi chu dau dong hang` dau
                  sac_accu_mn_cao();
                  clear_lcd();
                  LCD_PUTCMD(Line_2); // Dua hien thi chu dau dong hang` duoi
                  view_timer_mn_fail();
                  break;

               case 20: // het thoi gian chay/ lam mat roi ngat may no
               case 21:
                  LCD_PUTCMD(Line_1); // Dua hien thi chu dau dong hang` dau
                  mn_giainhiet();
                  clear_lcd();
                  LCD_PUTCMD(Line_2); // Dua hien thi chu dau dong hang` duoi
                  val_printf = tg_off_mn;
                  val_phut_giay_printf();
                  break;

               case 22:
                  LCD_PUTCMD(Line_1); // Dua hien thi chu dau dong hang` dau
                  mn_giainhiet();
                  clear_lcd();
                  LCD_PUTCMD(Line_2); // Dua hien thi chu dau dong hang` duoi
                  loading();
                  break;

               case 23:
                  LCD_PUTCMD(Line_1); // Dua hien thi chu dau dong hang` dau
                  PRINTF(LCD_PUTCHAR, "%s", menu_main[4]);
                  clear_lcd();
                  LCD_PUTCMD(Line_2); // Dua hien thi chu dau dong hang` duoi
                  val_printf = timer_save_oil_mn;
                  val_phut_giay_printf();
                  break;
               }
               break;

               //---------------remote start-----------------
            case 129: // remote start
               switch (process_kdt_mn)
               {
               default:
                  LCD_PUTCMD(Line_1); // Dua hien thi chu dau dong hang` dau
                  remote_display();
                  clear_lcd();
                  LCD_PUTCMD(Line_2); // Dua hien thi chu dau dong hang` duoi
                  loading();
                  break;

               case 1:                // kiêm tra dien ap may no có tren 50v!
               case 2:                // kiem tra dien ap may no co nằm trong ngưởng cho phep
                  LCD_PUTCMD(Line_1); // Dua hien thi chu dau dong hang` dau
                  remote_display();
                  clear_lcd();
                  LCD_PUTCMD(Line_2); // Dua hien thi chu dau dong hang` duoi
                  ondinh_mn();
                  break;

               case 3:                // chay đên khi het thoi gian cai dat
                  LCD_PUTCMD(Line_1); // Dua hien thi chu dau dong hang` dau
                  remote_display();
                  clear_lcd();
                  LCD_PUTCMD(Line_2); // Dua hien thi chu dau dong hang` duoi
                  thoigianchaymn();
                  break;

               case 4:                // suoi may no
               case 5:                // khoi dong may no
                  LCD_PUTCMD(Line_1); // Dua hien thi chu dau dong hang` dau
                  lamnongmn();
                  clear_lcd();
                  LCD_PUTCMD(Line_2); // Dua hien thi chu dau dong hang` duoi
                  thoigianlamnong();
                  break;

               case 6:                // nha start khi co nguon hoat het thoi gian
               case 7:                // trì hoản trước khi nhan lại start
                  LCD_PUTCMD(Line_1); // Dua hien thi chu dau dong hang` dau
                  remote_display();
                  clear_lcd();
                  LCD_PUTCMD(Line_2); // Dua hien thi chu dau dong hang` duoi
                  start_thucong();
                  break;

               case 8:                // trì hoản trước khi nhan lại start
                  LCD_PUTCMD(Line_1); // Dua hien thi chu dau dong hang` dau
                  mpd_restart();
                  clear_lcd();
                  LCD_PUTCMD(Line_2); // Dua hien thi chu dau dong hang` duoi
                  tg_watting_ms_td();
                  break;

               case 9:                // may no fail, khoi dong that bai
                  LCD_PUTCMD(Line_1); // Dua hien thi chu dau dong hang` dau
                  mn_fail();
                  clear_lcd();
                  LCD_PUTCMD(Line_2); // Dua hien thi chu dau dong hang` duoi
                  view_timer_mn_fail();
                  break;

               case 10: // het thoi gian chay/ lam mat roi ngat may no
               case 11:
               case 12:
               case 13:
                  LCD_PUTCMD(Line_1); // Dua hien thi chu dau dong hang` dau
                  mn_giainhiet();
                  clear_lcd();
                  LCD_PUTCMD(Line_2); // Dua hien thi chu dau dong hang` duoi
                  giainhietmn();
                  break;

               case 14:               // MAY NO MAT NGUON
                  LCD_PUTCMD(Line_1); // Dua hien thi chu dau dong hang` dau
                  overload();
                  clear_lcd();
                  LCD_PUTCMD(Line_2); // Dua hien thi chu dau dong hang` duoi
                  view_timer_mn_fail();
                  break;

               case 15:               // thieu ap luc nhot
                  LCD_PUTCMD(Line_1); // Dua hien thi chu dau dong hang` dau
                  thieuapxuatnhot();
                  clear_lcd();
                  LCD_PUTCMD(Line_2); // Dua hien thi chu dau dong hang` duoi
                  view_timer_mn_fail();

                  break;

               case 16:               // nhiet do nuoc qua cao
                  LCD_PUTCMD(Line_1); // Dua hien thi chu dau dong hang` dau
                  qua_nhiet_ket_nc();
                  clear_lcd();
                  LCD_PUTCMD(Line_2); // Dua hien thi chu dau dong hang` duoi
                  view_timer_mn_fail();
                  break;

               case 17:               // may no ra dien ap thap
                  LCD_PUTCMD(Line_1); // Dua hien thi chu dau dong hang` dau
                  dienapmnthap();
                  clear_lcd();
                  LCD_PUTCMD(Line_2); // Dua hien thi chu dau dong hang` duoi
                  view_timer_mn_fail();
                  break;

               case 18:               // may no ra dien qua ap
                  LCD_PUTCMD(Line_1); // Dua hien thi chu dau dong hang` dau
                  dienapmncao();
                  clear_lcd();
                  LCD_PUTCMD(Line_2); // Dua hien thi chu dau dong hang` duoi
                  view_timer_mn_fail();
                  break;

               case 19:               // may no sac accu qua cao
                  LCD_PUTCMD(Line_1); // Dua hien thi chu dau dong hang` dau
                  sac_accu_mn_cao();
                  clear_lcd();
                  LCD_PUTCMD(Line_2); // Dua hien thi chu dau dong hang` duoi
                  view_timer_mn_fail();
                  break;
               }
               break;
            }
         }
         break;
      }
      break;

   case 1: // nhap mat khau
      sch_1 = str_temp;
      sch_1_s_set();
      break;

   case 2: // cai NGUONG dien luoi
      if (refresh_menu_sub)
      {
         LCD_PUTCMD(Line_1); // Dua hien thi chu dau dong hang` dau
         PRINTF(LCD_PUTCHAR, "%s", menu_sub2[mode_sub]);
         clear_lcd();
      }
      LCD_PUTCMD(Line_2); // Dua hien thi chu dau dong hang` duoi

      switch (mode_sub)
      {
      case 0:
         entersetup();
         break;

      case 1: // lua chon loai dien luoi 1 pha / 3 pha
         if (style_mod_ac == 0)
            ac_1_pha();
         if (style_mod_ac == 1)
            ac_3_pha();
         break;

      case 2:
         trang_thai_co_dien_luoi() break;

      case 3: // NGUONG TREN DIEN AP AC
         ac_max_vol();
         break;

      case 4: // NGUONG DUOI DIEN AP AC
         ac_min_vol();
         break;

      case 5: // THOI GIAN ON DINH DIEN AP DONG KHOI DONG TU CAP NGUON
         tgian_on_dinh_ac();
         break;

      case 6: // do nhay chuong trinh
         val_printf = val_counter_ac_fail;
         val_lan_printf();
         break;
      }
      break;

   case 3: // cai dat NGUONG may no
      if (refresh_menu_sub)
      {
         LCD_PUTCMD(Line_1); // Dua hien thi chu dau dong hang` dau
         PRINTF(LCD_PUTCHAR, "%s", menu_sub3[mode_sub]);
         clear_lcd();
      }

      LCD_PUTCMD(Line_2); // Dua hien thi chu dau dong hang` duoi

      switch (mode_sub)
      {
      case 0:
         entersetup();
         break;

      case 1: // NGUONG TREN DIEN AP MN
         mn_max_vol();
         break;

      case 2: // NGUONG DUOI DIEN AP MN
         mn_min_vol();
         break;

      case 3: // SO LAN KHOI DONG CHO PHEP
         solan_khoidong();
         break;

      case 4: // THOI GIAN CHAY MAY NO LIEN TUC
         tg_on_lientuc();
         break;

      case 5: // thoi gian suoi may no
         tg_suoi_mn();
         break;

      case 6: // thoi gian nhan start khoi dong may no
         tg_nhan_giu_start();
         break;

      case 7: // thoi gian on/off air
         val_printf = val_tg_air;
         val_giay_printf();
         break;

      case 8: // khoan cach giua cac lan nhan start
         tg_start_start();
         break;

      case 9: // thoi gian stop may phat dien thu cong
         val_printf = val_tg_press_stop;
         val_giay_printf();
         break;

      case 10: // thoi gian cho on dinh dien ap
         tg_on_dinh_dienap_mn();
         break;

      case 11: // thoi gian lam mat may truoc khi stop
         tg_lamnguoi_mn();
         break;

      case 12:
         tg_giainhietmn();
         break;

      case 13:
         yesno();
         break;

      case 14: // do nhay chuong trinh
         val_printf = val_counter_mn_fail;
         val_lan_printf();
         break;
      }
      break;

   case 4: // cai dat TIET KIEM NANG LUONG
      if (refresh_menu_sub)
      {
         LCD_PUTCMD(Line_1); // Dua hien thi chu dau dong hang` dau
         PRINTF(LCD_PUTCHAR, "%s", menu_sub4[mode_sub]);
         clear_lcd();
      }
      LCD_PUTCMD(Line_2); // Dua hien thi chu dau dong hang` duoi

      switch (mode_sub)
      {
      case 0:
         entersetup();
         break;

      case 1: // lua chon giam sac NGUONG dien dc phong dai
         // switch(energy_save){
         // case 0:
         // kosudung();
         // break;

         // case 1:
         // sudung();
         // break;
         // }
         PRINTF(LCD_PUTCHAR, "%s", style_energy_save[energy_save]);
         break;

      case 2: // thoi gian tri hoan chay may
         val_printf = val_timer_delay_run_mn;
         val_phut_printf();
         break;

      case 3: // khung gio tri hoan chay may no
         set_hour_save_energy_from();
         break;

      case 4: // khung gio tri hoan chay may no
         set_min_save_energy_from();
         break;

      case 5: // khung gio tri hoan chay may no
         set_hour_save_energy_to();
         break;

      case 6: // khung gio tri hoan chay may no
         set_min_save_energy_to();
         break;
      case 7: // nguong DC LOW cho phong accu
         set_dc_low_accu();
         break;
      case 8:
         set_delta_dc_low_accu();
         break;
      }
      break;

   case 5: // cai dat cam bien
      if (refresh_menu_sub)
      {
         LCD_PUTCMD(Line_1); // Dua hien thi chu dau dong hang` dau
         PRINTF(LCD_PUTCHAR, "%s", menu_sub6[mode_sub]);
         clear_lcd();
      }

      LCD_PUTCMD(Line_2); // Dua hien thi chu dau dong hang` duoi

      switch (mode_sub)
      {
      default:
         entersetup();
         break;

      case 1: // cam bien nhot on/off
         switch (en_pressure_mn)
         {
         case 0:
            kosudung();
            break;

         case 1:
            sudung();
            break;
         }
         break;

      case 2: // cam bien nuoc on/off
         switch (en_temp_mn)
         {
         case 0:
            kosudung();
            break;

         case 1:
            sudung();
            break;
         }
         break;

      case 3: // INPUT: // KO SU DUNG / REMOTE START / REMOTE + ACCU / ACCU MAX
         PRINTF(LCD_PUTCHAR, "%s", style_input_control[Control_input]);
         break;

      case 4: // bao ve accu khi dien ap sac lon hon
         PRINTF(LCD_PUTCHAR, "SAC < %02.1f VOLT", volt_Protect_Accu);
         break;

      case 5: // cam bien nhot adc /su dung/ ko dung
         PRINTF(LCD_PUTCHAR, "%s", style_vdo_pressure[en_pressure_mn_adc]);
         break;

      case 6: // gia tri adc cam bien nhot
         PRINTF(LCD_PUTCHAR, "%u Bar = [%u] ", list_ap_suat[en_pressure_mn_adc][mode_sub_1], list_dien_tro_ap_suat[mode_sub_1]);
         LCD_PUTCHAR(0xF4);
         break;

      case 7: // cam bien nhiet do adc /su dung/ ko dung
         PRINTF(LCD_PUTCHAR, "%s", style_vdo_temp[en_temp_mn_adc]);
         break;

      case 8: // gia tri adc cam nhiet do nuoc
         PRINTF(LCD_PUTCHAR, "%u", list_nhiet_do[mode_sub_1]);
         LCD_PUTCHAR(0xDF);
         PRINTF(LCD_PUTCHAR, "C = [%u] ", list_dien_tro_nhiet_do[mode_sub_1]);
         LCD_PUTCHAR(0xF4);
         break;

      case 9: // gia tri an toan cam bien nhot
         PRINTF(LCD_PUTCHAR, "LON HON %u Bar", val_pressure_max);
         break;

      case 10: // gia tri an toan cam bien nuoc
         PRINTF(LCD_PUTCHAR, "NHO HON %u", val_temp_max);
         LCD_PUTCHAR(0xDF);
         LCD_PUTCHAR('C');
         break;

      case 11: // bat đau kiem tra cam bien sau khoan thoi gian
         val_printf = time_check_sensor;
         val_giay_printf();
         break;
      }
      break;

   case 6: // remote start - test may phat dien
      if (refresh_menu_sub)
      {
         LCD_PUTCMD(Line_1); // Dua hien thi chu dau dong hang` dau
         PRINTF(LCD_PUTCHAR, "%s", menu_sub7[mode_sub]);
         clear_lcd();
      }

      LCD_PUTCMD(Line_2); // Dua hien thi chu dau dong hang` duoi
      switch (mode_sub)
      {
      default:
         entersetup();
         break;

      case 1: //"C.DAT NGAY GIO",   //REALTIME
         view_gio_ht();
         break;

      case 2: //"C.DAT NGAY GIO",
         set_thu();
         break;

      case 3: //"C.DAT NGAY GIO",
         set_gio();
         break;

      case 4: //"C.DAT NGAY GIO",
         set_phut();
         break;

      case 5: //"THOI GIAN TEST", //SET THU
         test_thu();
         break;

      case 6: //"THOI GIAN TEST", //SET GIO
         test_gio();
         break;

      case 7: //"THOI GIAN TEST", //SET PHUT
         test_phut();
         break;

      case 8: // CHU KY TEST
         val_printf_2 = chu_ky_test;
         val_tuan_printf();
         break;

      case 9: // CHU KY HIEN TAI
         val_printf_2 = chu_ky_hien_tai;
         val_tuan_printf();
         break;

      case 10: //"TEST MAY NO",   //YES/NO
         yesno();
         break;
      }
      break;

   case 7: // xem trang thai canh bao
      if (refresh_menu_sub)
      {
         LCD_PUTCMD(Line_1); // Dua hien thi chu dau dong hang` dau
         PRINTF(LCD_PUTCHAR, "%s", menu_sub5[mode_sub]);
         clear_lcd();
      }
      LCD_PUTCMD(Line_2); // Dua hien thi chu dau dong hang` duoi

      switch (mode_sub)
      {
      case 0:
         enterview();
         break;

      case 1: // SO LAN MAT DIEN
         log_fail_ac();
         break;

      case 2: // THOI GIAN CHAY MAY PHAT DIEN
         log_tg_run();
         break;

      case 3: // SO LAN KHOI DONG THAT BAI
         log_error_code();
         //   log_fail_start();
         break;

      case 4: // XOA LOG
         yesno();
         break;
      }
      break;

   case 8: // cai dat mat dinh
      if (refresh_menu_sub)
      {
         LCD_PUTCMD(Line_1); // Dua hien thi chu dau dong hang` dau
         PRINTF(LCD_PUTCHAR, "%s", menu_main[8]);
         clear_lcd();
      }

      switch (mode_sub)
      {
      case 0:
         entersetup();
         break;

      case 1:
         PRINTF(LCD_PUTCHAR, "%s", verson_fw);
         break;

      case 2:
         yesno();
         break;
      }
      break;

   case 9:
      if (view_test_progam)
         sudung();
      if (!view_test_progam)
         kosudung();
      break;
   }
   clear_lcd();
   refresh_menu = 0;     // cap nhat du lieu mang hinh xong
   refresh_menu_sub = 0; // cap nhat du lieu mang hinh xong
}

//=========================
void lcd_printf(char code_printf)
{
   unsigned char list_thu[8][3] = {{"CN"},
                                   {"T2"},
                                   {"T3"},
                                   {"T4"},
                                   {"T5"},
                                   {"T6"},
                                   {"T7"}};

   unsigned char list_code[8][16] = {{"BINH THUONG"},
                                     {"K.DONG THAT BAI"},
                                     {"KHONG RA NGUON"},
                                     {"D.AP QUA CAO"},
                                     {"D.AP QUA THAP"},
                                     {"AP SUAT NHOT"},
                                     {"N.DO QUA CAO"},
                                     {"SAC ACCU CAO"}};

   long temp = 0;
   //   if(++roll>10)roll=0;
   switch (code_printf)
   {
   case 0:
      PRINTF(LCD_PUTCHAR, "                ");
      break;

   case 1:
      PRINTF(LCD_PUTCHAR, "Enter setup");
      break;

   case 2:
      PRINTF(LCD_PUTCHAR, "%s<", sch_1);
      break;

   case 3:
      PRINTF(LCD_PUTCHAR, "MOT PHA");
      break;

   case 4:
      PRINTF(LCD_PUTCHAR, "BA PHA");
      break;

   case 5:
      PRINTF(LCD_PUTCHAR, "%Lu VOLT AC", ac_vol_max);
      break;

   case 6:
      PRINTF(LCD_PUTCHAR, "%u VOLT AC", ac_vol_min);
      break;

   case 7:
      PRINTF(LCD_PUTCHAR, "%u giay", val_tg_on_dinh_ac);
      break;

   case 8:
      PRINTF(LCD_PUTCHAR, "%u VOLT AC", mn_vol_max);
      break;

   case 9:
      PRINTF(LCD_PUTCHAR, "%u VOLT AC", mn_vol_min);
      break;

   case 10:
      PRINTF(LCD_PUTCHAR, "%u LAN", val_counter_start);
      break;

   case 11:
      PRINTF(LCD_PUTCHAR, "%u GIO", val_tg_run_on);
      break;

   case 12:
      PRINTF(LCD_PUTCHAR, "%u GIAY", val_tg_preheat);
      break;

   case 13:
      PRINTF(LCD_PUTCHAR, "%u GIAY", val_tg_press_start);
      break;

   case 14:
      PRINTF(LCD_PUTCHAR, "%u GIAY", val_tg_start_start);
      break;

   case 15:
      PRINTF(LCD_PUTCHAR, "%u GIAY", val_tg_on_dinh_mn);
      break;

   case 16:
      PRINTF(LCD_PUTCHAR, "%u PHUT", val_tg_off_mn);
      break;

   case 17:
      PRINTF(LCD_PUTCHAR, "DIEN AP MN CAO!");
      break;

   case 18:
      PRINTF(LCD_PUTCHAR, "DIEN AP MN THAP!");
      break;

   case 19:
      PRINTF(LCD_PUTCHAR, "TEST M.P.D: %03u S", tg_run_test);
      break;

   case 20:
      PRINTF(LCD_PUTCHAR, "DIEN AP: %02.0f V", adc_mn_2);
      break;

   case 21:
      PRINTF(LCD_PUTCHAR, "Enter view");
      break;

   case 22:
      PRINTF(LCD_PUTCHAR, "  <YES || NO>");
      break;

   case 23:
      PRINTF(LCD_PUTCHAR, "MN TU DONG");
      break;

   case 24:
      PRINTF(LCD_PUTCHAR, "AP SUAT NHOT!");
      break;

   case 25:
      roll++;
      PRINTF(LCD_PUTCHAR, "LOADING ");
      switch (roll)
      {
      default:
         roll = 0;
         break;

      case 1:
         PRINTF(LCD_PUTCHAR, ".");
         break;

      case 2:
         PRINTF(LCD_PUTCHAR, "..");
         break;

      case 3:
         PRINTF(LCD_PUTCHAR, "...");
         break;

      case 4:
         PRINTF(LCD_PUTCHAR, " ..");
         break;

      case 5:
         PRINTF(LCD_PUTCHAR, "  .");
         break;
      }
      break;

   case 26:
      PRINTF(LCD_PUTCHAR, "WAITING: %u s", tg_on_dinh_ac);
      break;

   case 27:
      PRINTF(LCD_PUTCHAR, "TEST OK!");
      break;

   case 28:
      PRINTF(LCD_PUTCHAR, "DIEN LUOI AC");
      break;

   case 29:
      PRINTF(LCD_PUTCHAR, "NHIET DO CAO!");
      break;

   case 30:
      switch (level_set_ac_fail)
      {       // kiem tra co ac trong khoan hoac muc
      case 0: // trong khoan 140--> 290 co dien
         PRINTF(LCD_PUTCHAR, "%uV < AC < %LuV", ac_vol_min, ac_vol_max);
         break;

      case 1: // muc lon hon 140 co dien
         PRINTF(LCD_PUTCHAR, "AC > %uV", ac_vol_min);
         break;
      }
      break;

   case 31:
      PRINTF(LCD_PUTCHAR, "NGUON M.P.D TD");
      break;

   case 32:
      PRINTF(LCD_PUTCHAR, "WAITING: %02u s", tg_on_dinh_mn);
      break;

   case 33:
      // PRINTF(LCD_PUTCHAR,"%02u:%02u:%02u | %02.0f V",tg_run_on,tg_phut_run_on,flag_timer_1s,adc_mn_2);
      PRINTF(LCD_PUTCHAR, "%02u:%02u:%02u | ", tg_run_on, tg_phut_run_on, flag_timer_1s);
      // if(roll>2) roll=0;
      roll++;
      switch (roll)
      {
      default:
         PRINTF(LCD_PUTCHAR, "%02.0f V", adc_mn_2);
         break;

      case 10:
      case 11:
      case 12:
      case 13:
      case 14:
      case 15:
         if (en_pressure_mn_adc)
            PRINTF(LCD_PUTCHAR, "%02.1fB", val_pressure);
         if (!en_pressure_mn_adc)
            PRINTF(LCD_PUTCHAR, "%02.0f V", adc_mn_2);
         break;

      case 16:
      case 17:
      case 18:
      case 19:
      case 20:
         if (!en_temp_mn_adc)
            PRINTF(LCD_PUTCHAR, "%02.0f V", adc_mn_2);

         if (en_temp_mn_adc)
         {
            PRINTF(LCD_PUTCHAR, "%02.1f", val_temp);
            LCD_PUTCHAR(0xDF);
            LCD_PUTCHAR('C');
         }
         break;

      case 25:
         roll = 0;
      case 21:
      case 22:
      case 23:
      case 24:
         if (Control_input == 0)
            PRINTF(LCD_PUTCHAR, "%02.0f V", adc_mn_2);
         if (Control_input == 1)
            PRINTF(LCD_PUTCHAR, "%02.0f V", adc_mn_2);
         if (Control_input == 2)
            PRINTF(LCD_PUTCHAR, "%02.1fV", volt_ChargeDC);
         if (Control_input == 3)
            PRINTF(LCD_PUTCHAR, "%02.1fV", volt_ChargeDC);
         break;
      }

      break;

   case 34:
      PRINTF(LCD_PUTCHAR, "MPD RESTART...");
      break;

   case 35:
      if (flag_accu_error)
      {
         PRINTF(LCD_PUTCHAR, "MPD LOI|ACCU LOI");
      }
      else
      {
         PRINTF(LCD_PUTCHAR, "MPD LOI");
      }
      break;

   case 36:
      PRINTF(LCD_PUTCHAR, "GIAI NHIET MN");
      break;

   case 37:
      PRINTF(LCD_PUTCHAR, "LAM NONG MAY NO");
      break;

   case 38:
      PRINTF(LCD_PUTCHAR, "PREHEAT: %02u GIAY", tg_preheat);
      break;

   case 39:
      PRINTF(LCD_PUTCHAR, "START:%u  | %02.0f V", tg_press_start, adc_mn_1);
      break;

   case 40:
      PRINTF(LCD_PUTCHAR, "TEST MPD KO TAI");
      break;

   case 41:
      PRINTF(LCD_PUTCHAR, "%02u:%02u | %02.0f V", tg_run_test, flag_timer_1s, adc_mn_display);
      break;

   case 42:
      PRINTF(LCD_PUTCHAR, "SU DUNG");
      break;

   case 43:
      PRINTF(LCD_PUTCHAR, "KHONG SU DUNG");
      break;

   case 44:
      PRINTF(LCD_PUTCHAR, "SAC ACCU CAO");
      break;

   case 45:
      break;

   case 46:
      PRINTF(LCD_PUTCHAR, "KHAN CAP!!!");
      break;

   case 47:
      // PRINTF(LCD_PUTCHAR,"%03Lu:%02u",tong_gio_chay_mn,tong_phut_chay_mn);
      sprintf(stringData, "%03Lu:%02u", tong_gio_chay_mn, tong_phut_chay_mn); // convert to string
      PRINTF(LCD_PUTCHAR, "%s", stringData);
      break;

   case 48:
      PRINTF(LCD_PUTCHAR, "%s", list_code[error_code]);
      break;

   case 49:
      PRINTF(LCD_PUTCHAR, "%02u lan", counter_ac_fail);
      break;

   case 50:
      PRINTF(LCD_PUTCHAR, "%02u:%02u", tg_giainhiet, flag_timer_1s);
      break;

   case 51:

      PRINTF(LCD_PUTCHAR, "%02u phut", val_tg_giainhiet);
      break;

   case 52:
      //   PRINTF(LCD_PUTCHAR,"%02u giay",val_tg_start_mn_tudong);
      break;

   case 53:
      PRINTF(LCD_PUTCHAR, "Re-Start: %02u s", tg_start_start);
      break;

   case 54:
      PRINTF(LCD_PUTCHAR, "M.P.D");
      //   PRINTF(LCD_PUTCHAR,"M.P.D    | %02.0f V",adc_mn_2);
      //   if(en_pressure_mn_adc) PRINTF(LCD_PUTCHAR,"%02.1fB",val_pressure);
      //   if(en_temp_mn_adc){
      //      PRINTF(LCD_PUTCHAR," %02.1f",val_temp);
      //      LCD_PUTCHAR(0xDF);
      //      LCD_PUTCHAR('C');
      //   }
      break;

   case 55:
      if ((Control_input == 1 || Control_input == 2) && volt_ChargeDC > 5)
      {
         PRINTF(LCD_PUTCHAR, "REMOTE START : %1u", counter_remote_start);
      }
      else
      {
         if (style_mod_ac == 1)
         {
            PRINTF(LCD_PUTCHAR, "AC: %02.0f|%02.0f|%02.0f", adc_pha1, adc_pha2, adc_pha3);
         }
         if (style_mod_ac == 0)
         {
            PRINTF(LCD_PUTCHAR, "AC:%02.0fV DC:%02.1fV", adc_pha1, get_adc_accu());
         }
      }
      //   PRINTF(LCD_PUTCHAR,"%02.1fV",volt_ChargeDC);
      //   if(Control_input==3) PRINTF(LCD_PUTCHAR,"%02.1fV",volt_ChargeDC);
      break;

   case 56:
      break;

   case 57:
      PRINTF(LCD_PUTCHAR, "M.P.D CO KHI");
      break;

   case 58:
      PRINTF(LCD_PUTCHAR, "%03Lu phut", val_printf);
      break;

   case 59:
      PRINTF(LCD_PUTCHAR, "%02Lu lan", val_printf);
      break;

   case 60:
      temp = val_printf / 3600;
      PRINTF(LCD_PUTCHAR, "%02Lu:", temp);
      long temp1 = (val_printf - temp * 3600) / 60;
      PRINTF(LCD_PUTCHAR, "%02Lu:", temp1);
      // temp=temp*60;
      temp = val_printf - temp * 3600 - temp1 * 60;
      PRINTF(LCD_PUTCHAR, "%02Lu", temp);
      break;

   case 61:
      PRINTF(LCD_PUTCHAR, "%02Lu giay", val_printf);
      break;

   case 62:
      PRINTF(LCD_PUTCHAR, "%02.0f", val_printf_1);
      LCD_PUTCHAR(0xDF);
      LCD_PUTCHAR('C');
      break;

   case 63:
      //   PRINTF(LCD_PUTCHAR,"%02.1f BAR",val_printf_1);
      break;

   case 64:
      PRINTF(LCD_PUTCHAR, "MPD KO RA NGUON!");
      break;

   case 65:
      PRINTF(LCD_PUTCHAR, "READING DATA !!!!");
      break;

   case 66:
      PRINTF(LCD_PUTCHAR, "%02u:%02u:%02u", timer_hour_fail_mn, timer_min_fail_mn, timer_sec_fail_mn);
      break;

   case 67:
      PRINTF(LCD_PUTCHAR, "REMOTE START!");
      break;

   case 68:
      PRINTF(LCD_PUTCHAR, "%s-%02d:%02d:%02d", list_thu[thu_ht], gio_ht, phut_ht, giay_ht);
      break;

   case 69:
      PRINTF(LCD_PUTCHAR, "<%s>-%02d:%02d:%02d", list_thu[thu_ht], gio_ht, phut_ht, giay_ht);
      break;

   case 70:
      PRINTF(LCD_PUTCHAR, "%s-<%02d>:%02d:%02d", list_thu[thu_ht], gio_ht, phut_ht, giay_ht);
      break;

   case 71:
      PRINTF(LCD_PUTCHAR, "%s-%02d:<%02d>:%02d", list_thu[thu_ht], gio_ht, phut_ht, giay_ht);
      break;

   case 72:
      PRINTF(LCD_PUTCHAR, "<%s>-%02d:%02d", list_thu[thu_test], gio_test, phut_test);
      break;

   case 73:
      PRINTF(LCD_PUTCHAR, "%s-<%02d>:%02d", list_thu[thu_test], gio_test, phut_test);
      break;

   case 74:
      PRINTF(LCD_PUTCHAR, "%s-%02d:<%02d>", list_thu[thu_test], gio_test, phut_test);
      break;

   case 75:
      PRINTF(LCD_PUTCHAR, "%02u Tuan", val_printf_2);
      break;

   case 76:
      PRINTF(LCD_PUTCHAR, "<%02d>:%02d - %02d:%02d", gio_save_from, phut_save_from, gio_save_to, phut_save_to);
      break;

   case 77:
      PRINTF(LCD_PUTCHAR, "%02d:<%02d> - %02d:%02d", gio_save_from, phut_save_from, gio_save_to, phut_save_to);
      break;

   case 78:
      PRINTF(LCD_PUTCHAR, "%02d:%02d - <%02d>:%02d", gio_save_from, phut_save_from, gio_save_to, phut_save_to);
      break;

   case 79:
      PRINTF(LCD_PUTCHAR, "%02d:%02d - %02d:<%02d>", gio_save_from, phut_save_from, gio_save_to, phut_save_to);
      break;
   case 80:
      PRINTF(LCD_PUTCHAR, "ACCU:%02.1fV", input_dc_low);
      break;
   case 81:
      PRINTF(LCD_PUTCHAR, "DELTA:%02.1fV", delta_dc);
      break;
   }
}

//=======================================
char key_scan(void)
{
   unsigned long bounce = 200;

   if (input(sw_mode) == 1)
   {
      while (bounce--)
         if (input(sw_mode) == 0)
            return 0x00;
      bounce = 1024;
      while (bounce--)
         if (input(sw_mode) == 0)
            return 0x01;
      return 0x01;
   }

   if (input(sw_up) == 1)
   {
      while (bounce--)
         if (input(sw_up) == 0)
            return 0x00;
      bounce = 128;
      while (bounce--)
         if (input(sw_up) == 0)
            return 0x02;
      return 0x02;
   }

   if (input(sw_down) == 1)
   {
      while (bounce--)
         if (input(sw_down) == 0)
            return 0x00;
      bounce = 128;
      while (bounce--)
         if (input(sw_down) == 0)
            return 0x03;
      return 0x03;
   }

   if (input(sw_exit) == 1)
   {
      while (bounce--)
         if (input(sw_exit) == 0)
            return 0x00;
      bounce = 256;
      while (bounce--)
         if (input(sw_exit) == 0)
            return 0x04;
      return 0x04;
   }
   return 0x00;
}

//=========================
void process_menu(void)
{
   refresh_menu = 1;
   switch (mode)
   {
   case 1:
      if (strlen(str_temp) == strlen(password))
      {
         if (strcmp(password, str_temp) == 0)
         {
            mode++;
            time_reset_password = 20; // 20   phut
         }
      }
      if (strlen(str_temp) == strlen(passwordadmin))
      {
         if (strcmp(passwordadmin, str_temp) == 0)
         {
            mode++;
            flag_admin = 1;
         }
      }
      val_sch_1 = 0;
      sch_1 = str_temp;
      *sch_1 = 0;
      break;

   default:
      if (mode_sub == 0)
      {
         if (++mode > 8)
            mode = 0, flag_admin = 0;
         switch (mode)
         {
         case 1:
            if (time_reset_password != 0)
               mode = 2;
            break;

         case 5:
            if (flag_admin == 0)
               mode = 6;
            break;
         }
      }
      if (mode_sub != 0)
         mode_sub = 0, mode_sub_1 = 0;
      break;
   }
}

//=========================
void process_up(void)
{
   // press_button=1;
   switch (mode)
   {
   case 0: // mang hinh chinh
      switch (view_test_progam)
      {
      case 1: // mang hinh test
         if (++val_string_run_loop > 11)
            val_string_run_loop = 0;
         break;

      default:
         switch (counter_reset)
         {
         default:
            counter_reset++;
            break;

         case 3:
            defaul_data();
            write_ram_ds1307();
            write_data_ee();
            Hash_Full();
            counter_reset = 0;
            break;
         }
         break;
      }
      break;

   case 1: // nhap mat khau
      sch_2 = val_number_defaul;
      if (++val_sch_2 > 10)
         val_sch_2 = 0;
      sch_2 = sch_2 + val_sch_2;
      sch_1 = sch_1 + val_sch_1;
      *sch_1++ = *sch_2;
      *sch_1 = 0;
      break;

   case 2: // cai dat NGUONG dien luoi
           //  flag_save_data=1;   //cai dat gia tri he thong
      // press_button=1;
      waitingData = 1;
      switch (mode_sub)
      {
      default:
         waitingData = 0;
         break;

      case 1:
         style_mod_ac = 1;
         break;

      case 2:
         level_set_ac_fail = 0;
         break;

      case 3: // NGUONG TREN DIEN AP AC
         if (++ac_vol_max > 250)
            ac_vol_max = 235;
         break;

      case 4: // NGUONG DUOI DIEN AP AC
         if (++ac_vol_min > 200)
            ac_vol_min = 160;
         break;

      case 5: // THOI GIAN ON DINH DIEN AP DONG KHOI DONG TU CAP NGUON
         if (++val_tg_on_dinh_ac > 240)
            val_tg_on_dinh_ac = 30; // 30giay -> 4phut
         break;

      case 6:
         if (val_counter_ac_fail < 10)
            val_counter_ac_fail++;
         break;
      }
      break;

   case 3: // cai dat NGUONG may no
           //  flag_save_data=1;   //cai dat gia tri he thong
      // press_button=1;
      waitingData = 1;
      switch (mode_sub)
      {
      default:
         waitingData = 0;
         break;

      case 1: // NGUONG TREN DIEN AP MN
         if (++mn_vol_max > 254)
            mn_vol_max = 220;
         break;

      case 2: // NGUONG DUOI DIEN AP MN
         if (++mn_vol_min > 200)
            mn_vol_min = 160;
         break;

      case 3: // SO LAN KHOI DONG CHO PHEP
         if (++val_counter_start > 4)
            val_counter_start = 2; // tu 2 đến 4 lần
         break;

      case 4: // THOI GIAN CHAY MAY NO LIEN TUC
         if (++val_tg_run_on > 24)
            val_tg_run_on = 1; // tu 3 -24 giờ
         break;

      case 5: // thoi gian suoi may no
         if (++val_tg_preheat > 240)
            val_tg_preheat = 1; // tu 1 -10 phút
         break;

      case 6: // thoi gian nhan start khoi dong may no
         if (++val_tg_press_start > 60)
            val_tg_press_start = 5; // tu 2 -5 giây
         break;

      case 7: // thoi gian giu air
         if (++val_tg_air > 5)
            val_tg_air = 2;
         break;

      case 8: // khoan cach giua cac lan nhan start
         if (++val_tg_start_start > 240)
            val_tg_start_start = 10; // tu 5 -10 giây
         break;

      case 9: // thoi gian nhan stop may phat dien thu cong
         if (++val_tg_press_stop > 60)
            val_tg_press_stop = 2;
         break;

      case 10: // thoi gian cho on dinh dien ap
         if (++val_tg_on_dinh_mn > 240)
            val_tg_on_dinh_mn = 30; // tu 5 -10 giây
         break;

      case 11: // thoi gian lam mat may truoc khi stop
         if (++val_tg_off_mn > 10)
            val_tg_off_mn = 1; // tu 1 -10 PHUT
         break;

      case 12:
         if (++val_tg_giainhiet < 5)
            val_tg_giainhiet = 5;
         break;

      case 13: // CHU KY QUET
         if (val_counter_mn_fail < 7)
            val_counter_mn_fail++;
         break;
      }
      break;

   case 4: // cai dat tiet kiem nang luong
           //  flag_save_data=1;   //cai dat gia tri he thong
      // press_button=1;
      waitingData = 1;
      switch (mode_sub)
      {
      default:
         waitingData = 0;
         break;

      case 1: // lua chon
         if (++energy_save > 4)
            energy_save = 4;
         break;

      case 2: // thoi gian tiet kiem nang luong
         if (++val_timer_delay_run_mn > 255)
            val_timer_delay_run_mn = 1;
         break;

      case 3:
         if (++gio_save_from > 23)
            gio_save_from = 12;
         break;

      case 4:
         if (++phut_save_from > 59)
            phut_save_from = 0;
         break;

      case 5:
         if (++gio_save_to > 12)
            gio_save_to = 0;
         break;

      case 6:
         if (++phut_save_to > 59)
            phut_save_to = 0;
         break;
      case 7:
         input_dc_low += 0.1;
         if (input_dc_low > 60)
            input_dc_low = 40;
         break;
      case 8:
         delta_dc += 0.1;
         if (delta_dc > 1)
            delta_dc = 0;
         break;
      }
      break;

   case 5: // cai dat cam bien
      // press_button=1;
      waitingData = 1;
      switch (mode_sub)
      {
      default:
         waitingData = 0;
         break;

      case 1: // cam bien nhot on/off
         en_pressure_mn = 1;
         break;

      case 2: // cam bien nuoc on/off
         en_temp_mn = 1;
         break;

      case 3: // INPUT: // KO SU DUNG / REMOTE START / REMOTE + ACCU / ACCU MAX
         if (++Control_input > 3)
            Control_input = 0;
         break;

      case 4:
         volt_Protect_Accu = volt_Protect_Accu + 0.1;
         if (volt_Protect_Accu > 25)
            volt_Protect_Accu = 13.8;
         break;

      case 5:                          // cam bien nhot adc /su dung/ ko dung
         if (++en_pressure_mn_adc > 0) // TODO: Quan trong, tam thoi bo tinh nang nhot adc, khoa menu chi chon dc KO SU DUNG. Ve sau muon dung thi chinh tu 0 len 2
            en_pressure_mn_adc = 0;
         switch (en_pressure_mn_adc)
         {
         case 1: // vdo 10bar
            list_dien_tro_ap_suat[0] = 10;
            list_dien_tro_ap_suat[1] = 31;
            list_dien_tro_ap_suat[2] = 71;
            list_dien_tro_ap_suat[3] = 107;
            list_dien_tro_ap_suat[4] = 140;
            list_dien_tro_ap_suat[5] = 184;
            break;

         case 2: // vdo 5bar
            list_dien_tro_ap_suat[0] = 10;
            list_dien_tro_ap_suat[1] = 48;
            list_dien_tro_ap_suat[2] = 82;
            list_dien_tro_ap_suat[3] = 116;
            list_dien_tro_ap_suat[4] = 151;
            list_dien_tro_ap_suat[5] = 184;
            break;
         }
         break;

      case 6: // gia tri adc cam bien nhot
         list_dien_tro_ap_suat[mode_sub_1]++;
         break;

      case 7: // cam bien nhiet do adc /su dung/ ko dung
         if (++en_temp_mn_adc > 0)
            en_temp_mn_adc = 0;
         switch (en_temp_mn_adc)
         {
         case 1: // vdo 120 do
            list_dien_tro_nhiet_do[0] = 134;
            list_dien_tro_nhiet_do[1] = 97;
            list_dien_tro_nhiet_do[2] = 70;
            list_dien_tro_nhiet_do[3] = 51;
            list_dien_tro_nhiet_do[4] = 38;
            list_dien_tro_nhiet_do[5] = 33;
            list_dien_tro_nhiet_do[6] = 29;
            list_dien_tro_nhiet_do[7] = 25;
            list_dien_tro_nhiet_do[8] = 22;
            list_dien_tro_nhiet_do[9] = 19;
            list_dien_tro_nhiet_do[10] = 17;
            break;

         case 2: // vdo 150 do
            list_dien_tro_nhiet_do[0] = 221;
            list_dien_tro_nhiet_do[1] = 155;
            list_dien_tro_nhiet_do[2] = 112;
            list_dien_tro_nhiet_do[3] = 82;
            list_dien_tro_nhiet_do[4] = 61;
            list_dien_tro_nhiet_do[5] = 54;
            list_dien_tro_nhiet_do[6] = 47;
            list_dien_tro_nhiet_do[7] = 41;
            list_dien_tro_nhiet_do[8] = 36;
            list_dien_tro_nhiet_do[9] = 32;
            list_dien_tro_nhiet_do[10] = 28;
            break;
         }
         break;

      case 8: // gia tri adc cam nhiet do nuoc
         list_dien_tro_nhiet_do[mode_sub_1]++;
         break;

      case 9: // gia tri an toan cam bien nhot
         if (++val_pressure_max > 10)
            val_pressure_max = 1;
         break;

      case 10: // gia tri an toan cam bien nuoc
         if (++val_temp_max > 130)
            val_temp_max = 100;
         break;

      case 11: // bat đau kiem tra cam bien sau khoan thoi gian
         if (++time_check_sensor > val_tg_on_dinh_mn - 10)
            time_check_sensor = val_tg_on_dinh_mn - 10;
         break;
      }
      break;

   case 6: // cai dat thoi gian
      waitingData = 1;
      switch (mode_sub)
      {
      default:
         waitingData = 0;
         break;

         // case 1: //"C.DAT NGAY GIO",   //REALTIME

         // break;

      case 2: //"C.DAT NGAY GIO",
         if (++thu_ht > 6)
            thu_ht = 0;
         PCF8583_set_datetime();
         waitingData = 0;
         break;

      case 3: //"C.DAT NGAY GIO",
         if (++gio_ht > 23)
            gio_ht = 0;
         PCF8583_set_datetime();
         waitingData = 0;
         break;

      case 4: //"C.DAT NGAY GIO",
         if (++phut_ht > 59)
            phut_ht = 0;
         PCF8583_set_datetime();
         waitingData = 0;
         break;

      case 5: //"THOI GIAN TEST", //SET THU
         if (++thu_test > 6)
            thu_test = 0;
         // press_button=1;
         break;

      case 6: //"THOI GIAN TEST", //SET GIO
         if (++gio_test > 23)
            gio_test = 0;
         // press_button=1;
         break;

      case 7: //"THOI GIAN TEST", //SET PHUT
         if (++phut_test > 59)
            phut_test = 0;
         // press_button=1;
         break;

      case 8: // CHU KY TEST
         chu_ky_test++;
         // press_button=1;
         break;

      case 9: // CHU KY HIEN TAI
         if (++chu_ky_hien_tai > chu_ky_test)
            chu_ky_hien_tai = 0;
         break;

      case 10: //"TEST MAY NO",   //YES/NO
         if (ac_vol_fail == 0)
            val_test_mn = 1; // co dien luoi moi cho test
         tg_run_test = 240;  // test trong 4 phut
         mode_sub = 0;
         mode = 0;
         break;
      }
      break;

   case 7: // xem thang thai canh bao
      //   flag_save_data=1;   //cai dat gia tri he thong
      switch (mode_sub)
      {
      case 0:
         enterview();
         break;

      case 1: // SO LAN MAT DIEN

         break;

      case 2: // THOI GIAN CHAY MAY PHAT DIEN

         break;

      case 3:

         break;

      case 4: // XOA LOG
         tong_gio_chay_mn = 0;
         tong_phut_chay_mn = 0;
         error_code = 0;
         counter_ac_fail = 0;
         flag_save_tg_chay_mn = 1;
         en_led_fail_mn = 0;
         mode_sub = 0;
         mode = 0;
         // press_button=1;
         break;
      }
      break;

   case 8: // gian thi mat dinh
      switch (mode_sub)
      {
      case 0:

         break;

      case 1:

         break;

      case 2:
         // defaul_data();
         // press_button=1;
         if (flag_admin)
            defaul_admin();
         defaul_data();
         write_ram_ds1307();
         write_data_ee();
         Hash_Full();
         mode_sub = 0;
         mode = 0;
         break;
      }
      break;

   case 9:
      view_test_progam = 1;
      break;
   }
}

//=========================
void process_down(void)
{
   // press_button=1;
   switch (mode)
   {
   case 0: // mang hinh chinh
      switch (counter_view_debug)
      {
      default:
         counter_view_debug++;
         break;

      case 3:
         refresh_menu = 1;
         mode = 9;
         counter_view_debug = 0;
         break;
      }
      break;

   case 1: // nhap mat khau
      sch_2 = val_number_defaul;
      if (--val_sch_2 > 10)
         val_sch_2 = 10;
      sch_2 = sch_2 + val_sch_2;
      sch_1 = sch_1 + val_sch_1;
      *sch_1++ = *sch_2;
      *sch_1 = 0;
      break;

   case 2: // cai dat NGUONG dien luoi
           //  flag_save_data=1;   //cai dat gia tri he thong
      // press_button=1;
      waitingData = 1;
      switch (mode_sub)
      {
      default:
         waitingData = 0;
         break;

      case 1:
         style_mod_ac = 0;
         break;

      case 2:
         level_set_ac_fail = 1;
         break;

      case 3: // NGUONG TREN DIEN AP AC
         if (--ac_vol_max < 235)
            ac_vol_max = 250;
         break;

      case 4: // NGUONG DUOI DIEN AP AC
         if (--ac_vol_min < 160)
            ac_vol_min = 200;
         break;

      case 5: // THOI GIAN ON DINH DIEN AP DONG KHOI DONG TU CAP NGUON
         if (--val_tg_on_dinh_ac < 30)
            val_tg_on_dinh_ac = 240; // 30giay -> 2phut
         break;

      case 6:
         if (val_counter_ac_fail > 1)
            val_counter_ac_fail--;
         break;
      }
      break;

   case 3: // cai dat NGUONG may no
           //  flag_save_data=1;   //cai dat gia tri he thong
      // press_button=1;
      waitingData = 1;
      switch (mode_sub)
      {
      default:
         waitingData = 0;
         break;

      case 1: // NGUONG TREN DIEN AP MN
         if (--mn_vol_max < 220)
            mn_vol_max = 254;
         break;

      case 2: // NGUONG DUOI DIEN AP MN
         if (--mn_vol_min < 160)
            mn_vol_min = 200;
         break;

      case 3: // SO LAN KHOI DONG CHO PHEP
         if (--val_counter_start < 2)
            val_counter_start = 4; // tu 2 đến 4 lần
         break;

      case 4: // THOI GIAN CHAY MAY NO LIEN TUC
         if (--val_tg_run_on < 1)
            val_tg_run_on = 24; // tu 4 -8 giờ
         break;

      case 5: // thoi gian suoi may no
         if (--val_tg_preheat < 1)
            val_tg_preheat = 240; // tu 1 -10 phút
         break;

      case 6: // thoi gian nhan start khoi dong may no
         if (--val_tg_press_start < 5)
            val_tg_press_start = 60; // tu 2 -5 giây
         break;

      case 7: // thoi gian giu air
         if (--val_tg_air < 2)
            val_tg_air = 5;
         break;

      case 8: // khoan cach giua cac lan nhan start
         if (--val_tg_start_start < 10)
            val_tg_start_start = 240; // tu 1 -10 giây
         break;

      case 9: // thoi gian nhan stop may phat dien thu cong
         if (--val_tg_press_stop < 2)
            val_tg_press_stop = 60;
         break;

      case 10: // thoi gian cho on dinh dien ap
         if (--val_tg_on_dinh_mn < 30)
            val_tg_on_dinh_mn = 240; // tu 5 -10 giây
         break;

      case 11: // thoi gian lam mat may truoc khi stop
         if (--val_tg_off_mn < 1)
            val_tg_off_mn = 10; // tu 1 -10 PHUT
         break;

      case 12: // thoi gian lam mat truoc khi mpd co the chay tiep
         if (--val_tg_giainhiet < 5)
            val_tg_giainhiet = 255;
         break;

      case 13:
         if (val_counter_mn_fail > 1)
            val_counter_mn_fail--;
         break;
      }
      break;

   case 4: // cai dat NGUONG accu phong dai
           //  flag_save_data=1;   //cai dat gia tri he thong
      // press_button=1;
      waitingData = 1;
      switch (mode_sub)
      {
         // case 0:
      default:
         waitingData = 0;
         break;

      case 1: // lua chon
         if (--energy_save > 4)
            energy_save = 0;
         break;

      case 2: // thoi gian tiet kiem nang luong
         if (--val_timer_delay_run_mn < 1)
            val_timer_delay_run_mn = 255;
         break;

      case 3:
         if (--gio_save_from < 12)
            gio_save_from = 23;
         break;

      case 4:
         if (--phut_save_from > 59)
            phut_save_from = 59;
         break;

      case 5:
         if (--gio_save_to > 12)
            gio_save_to = 12;
         break;

      case 6:
         if (--phut_save_to > 59)
            phut_save_to = 59;
         break;
      case 7:
         input_dc_low -= 0.1;
         if (input_dc_low < 40)
         {
            input_dc_low = 60;
         }
         break;
      case 8:
         delta_dc -= 0.1;
         if (delta_dc < 0)
         {
            delta_dc = 1;
         }
         break;
      }
      break;

   case 5: //
      // press_button=1;
      waitingData = 1;
      switch (mode_sub)
      {
      default:
         waitingData = 0;
         break;

      case 1: // cam bien nhot on/off
         en_pressure_mn = 0;
         break;

      case 2: // cam bien nuoc on/off
         en_temp_mn = 0;
         break;

      case 3: // INPUT: // KO SU DUNG / REMOTE START / REMOTE + ACCU / ACCU MAX
         if (--Control_input > 3)
            Control_input = 3;
         break;

      case 4:
         volt_Protect_Accu = volt_Protect_Accu - 0.1;
         if (volt_Protect_Accu < 13.8)
            volt_Protect_Accu = 25;
         break;

      case 5: // cam bien nhot adc /su dung/ ko dung
         if (--en_pressure_mn_adc > 2)
            en_pressure_mn_adc = 0;
         switch (en_pressure_mn_adc)
         {
         case 1: // vdo 10bar
            list_dien_tro_ap_suat[0] = 10;
            list_dien_tro_ap_suat[1] = 31;
            list_dien_tro_ap_suat[2] = 71;
            list_dien_tro_ap_suat[3] = 107;
            list_dien_tro_ap_suat[4] = 140;
            list_dien_tro_ap_suat[5] = 184;
            break;

         case 2: // vdo 5bar
            list_dien_tro_ap_suat[0] = 10;
            list_dien_tro_ap_suat[1] = 48;
            list_dien_tro_ap_suat[2] = 82;
            list_dien_tro_ap_suat[3] = 116;
            list_dien_tro_ap_suat[4] = 151;
            list_dien_tro_ap_suat[5] = 184;
            break;
         }
         break;

      case 6: // gia tri adc cam bien nhot
         list_dien_tro_ap_suat[mode_sub_1]--;
         break;

      case 7: // cam bien nhiet do adc /su dung/ ko dung
         if (--en_temp_mn_adc > 0)
            en_temp_mn_adc = 0;
         switch (en_temp_mn_adc)
         {
         case 1: // vdo 120 do
            list_dien_tro_nhiet_do[0] = 134;
            list_dien_tro_nhiet_do[1] = 97;
            list_dien_tro_nhiet_do[2] = 70;
            list_dien_tro_nhiet_do[3] = 51;
            list_dien_tro_nhiet_do[4] = 38;
            list_dien_tro_nhiet_do[5] = 33;
            list_dien_tro_nhiet_do[6] = 29;
            list_dien_tro_nhiet_do[7] = 25;
            break;

         case 2: // vdo 150 do
            list_dien_tro_nhiet_do[0] = 221;
            list_dien_tro_nhiet_do[1] = 155;
            list_dien_tro_nhiet_do[2] = 112;
            list_dien_tro_nhiet_do[3] = 82;
            list_dien_tro_nhiet_do[4] = 61;
            list_dien_tro_nhiet_do[5] = 54;
            list_dien_tro_nhiet_do[6] = 47;
            list_dien_tro_nhiet_do[7] = 41;
            break;
         }
         break;

      case 8: // gia tri adc cam nhiet do nuoc
         list_dien_tro_nhiet_do[mode_sub_1]--;
         break;

      case 9: // gia tri an toan cam bien nhot
         if (--val_pressure_max < 1)
            val_pressure_max = 10;
         break;

      case 10: // gia tri an toan cam bien nuoc
         if (--val_temp_max < 100)
            val_temp_max = 130;
         break;

      case 11: // bat đau kiem tra cam bien sau khoan thoi gian
         if (--time_check_sensor < 10)
            time_check_sensor = val_tg_on_dinh_mn - 10;
         break;
      }
      break;

   case 6:
      waitingData = 1;
      switch (mode_sub)
      {
      default:
         waitingData = 0;
         break;

         // case 1: //"C.DAT NGAY GIO",   //REALTIME

         // break;

      case 2: //"C.DAT NGAY GIO",
         if (--thu_ht > 6)
            thu_ht = 6;
         PCF8583_set_datetime();
         waitingData = 0;
         break;

      case 3: //"C.DAT NGAY GIO",
         if (--gio_ht > 23)
            gio_ht = 23;
         PCF8583_set_datetime();
         waitingData = 0;
         break;

      case 4: //"C.DAT NGAY GIO",
         if (--phut_ht > 59)
            phut_ht = 59;
         PCF8583_set_datetime();
         waitingData = 0;
         break;

      case 5: //"THOI GIAN TEST", //SET THU
         if (--thu_test > 6)
            thu_test = 6;
         break;

      case 6: //"THOI GIAN TEST", //SET GIO
         if (--gio_test > 23)
            gio_test = 23;
         break;

      case 7: //"THOI GIAN TEST", //SET PHUT
         if (--phut_test > 59)
            phut_test = 59;
         break;

      case 8: // CHU KY TEST
         chu_ky_test--;
         break;

      case 9: // CHU KY HIEN TAI
         if (--chu_ky_hien_tai > chu_ky_test)
            chu_ky_hien_tai = 0;
         break;

      case 10: //"TEST MAY NO",   //YES/NO

         break;
      }
      break;

   case 7: // xem thang thai canh bao
      switch (mode_sub)
      {
      case 0:
         enterview();
         break;

      case 1: // SO LAN MAT DIEN

         break;

      case 2: // THOI GIAN CHAY MAY PHAT DIEN

         break;

      case 3: // XOA LOG

         break;

      case 4:
         mode_sub = 0;
         mode = 0;
         break;
      }
      break;

   case 8: // gian thi mat dinh
      switch (mode_sub)
      {
      case 0:

         break;

      case 2:
         mode_sub = 0;
         mode = 0;
         pause_clock_reset = 1;
         break;
      }
      break;

   case 9:
      view_test_progam = 0;
      break;
   }
}

//=========================
void process_exit(void)
{
   char val_null;

   refresh_menu_sub = 1;
   val_sch_2 = 0;

   switch (mode)
   {
   case 0: // mang hinh chinh
      time_reset_password = 0;
      break;

   case 1: // nhap mat khau
      sch_1 = sch_1 + val_sch_1;
      val_null = *sch_1;
      if (val_null != 0 && val_null != 0XFF)
      {
         if (++val_sch_1 > 16)
            val_sch_1 = 0;
         sch_1++;
         *sch_1++ = 0XFF;
         *sch_1 = 0;
      }
      break;

   case 2: //
      if (++mode_sub > 6)
         mode_sub = 1;

      switch (flag_admin)
      {
      default: // cho xem tat ca cai dat

         break;

      case 0: // gioi han cai tat
         switch (mode_sub)
         {
         case 1:
            mode_sub = 3;
            break;

         case 6:
            mode_sub = 3;
            break;
         }
         break;
      }

      break;

   case 3: //
      if (++mode_sub > 13)
         mode_sub = 1;
      switch (flag_admin)
      {
      default: // cho xem tat ca cai dat

         break;

      case 0: // gioi han cai tat
         switch (mode_sub)
         {
         case 13:
            mode_sub = 1;
            break;
         }
         break;
      }
      break;

   case 4: //
      if (++mode_sub > 8)
         mode_sub = 1;

      switch (energy_save)
      {
      case 0: // cup dien chay luon
         mode_sub = 1;
         break;

      case 1: // phong accu
         if (mode_sub < 7 && mode_sub > 1)
            mode_sub = 7;
         break;

      case 2: // tri hoan theo thoi gian dinh san
         if (mode_sub > 2)
            mode_sub = 1;
         break;

      case 3: // tri hoan theo khung gio
         if (mode_sub == 2)
            mode_sub = 3;
         if (mode_sub > 6)
            mode_sub = 1;
         break;

      case 4:
         if (mode_sub > 6)
            mode_sub = 1;
         break;
      }
      break;

   case 5:
      //   if(++mode_sub>5) mode_sub=1;
      switch (mode_sub)
      {
      default:
         mode_sub = 1;
         break;

      case 1: // cam bien nhot on/off
         mode_sub = 2;
         break;

      case 2: // cam bien nuoc on/off
         mode_sub = 3;
         break;

      case 3: // INPUT: // KO SU DUNG / REMOTE START / REMOTE + ACCU / ACCU MAX
         mode_sub = 4;
         if (Control_input == 0)
            mode_sub = 5;
         if (Control_input == 1)
            mode_sub = 5;
         break;

      case 4:
         mode_sub = 5;
         break;

      case 5: // cam bien nhot adc /su dung/ ko dung
         mode_sub = 7;
         if (en_pressure_mn_adc)
            mode_sub = 6;
         break;

      case 6: // gia tri adc cam bien nhot
         if (++mode_sub_1 > 5)
         {
            mode_sub_1 = 0;
            mode_sub = 7;
         }
         break;

      case 7: // cam bien nhiet do adc /su dung/ ko dung
         mode_sub = 9;
         if (en_temp_mn_adc)
            mode_sub = 8;
         break;

      case 8: // gia tri adc cam nhiet do nuoc
         if (++mode_sub_1 > 10)
         {
            mode_sub_1 = 0;
            mode_sub = 9;
         }
         break;

      case 9: // gia tri an toan cam bien nhot
         mode_sub = 10;
         break;

      case 10: // gia tri an toan cam bien nuoc
         mode_sub = 11;
         break;

      case 11: // bat đau kiem tra cam bien sau khoan thoi gian
         mode_sub = 1;
         break;
      }
      break;

   case 6: //
      if (++mode_sub > 10)
         mode_sub = 1;
      break;

   case 7: // xem log
      switch (flag_admin)
      {
      default: // cho xem tat ca cai dat
         if (++mode_sub > 4)
            mode_sub = 1;
         break;

      case 0: // gioi han cai tat
         if (++mode_sub > 3)
            mode_sub = 1;
         break;
      }
      // if(++mode_sub>4) mode_sub=1;
      break;

   case 8: //
      if (++mode_sub > 2)
         mode_sub = 1;
      break;
   }
}

//=========================
void defaul_admin(void)
{
   style_mod_ac = 0;
   level_set_ac_fail = 0;
   en_pressure_mn = 0;
   en_temp_mn = 0;
   Control_input = 3;
   volt_Protect_Accu = 16;
   en_temp_mn_adc = 0;
   en_pressure_mn_adc = 0;
   // TEST MPD
   tong_gio_chay_mn = 0;
   tong_phut_chay_mn = 0;
   counter_ac_fail = 0;
   error_code = 0;
   chu_ky_hien_tai = 0;
}

void defaul_data(void)
{
   // 220vac
   ac_vol_max = 250;
   ac_vol_min = 160;
   val_tg_on_dinh_ac = 120;
   val_counter_ac_fail = 5;

   // ac mn
   mn_vol_max = 240;
   mn_vol_min = 160;
   val_counter_start = 4;
   val_tg_run_on = 3; // 24 DAT
   val_tg_preheat = 10;
   val_tg_press_start = 5;
   val_tg_air = 2;
   val_tg_start_start = 60;
   val_tg_on_dinh_mn = 60;
   val_tg_off_mn = 1;
   val_tg_giainhiet = 60; // 30 DAT //TIMER tam dung
   val_tg_press_stop = 5;

   val_counter_mn_fail = 5;
   time_check_sensor = 20;
   // tiet kiem nang luong
   energy_save = 0;
   val_timer_delay_run_mn = 60; // 5 DAT

   //==========
   gio_save_from = 23;
   phut_save_from = 0;
   gio_save_to = 5;
   phut_save_to = 0;
   //==========

   input_dc_low = DC_LOW_LVL_1_MD;
   delta_dc = DC_LOW_DELTA_MD;
   //==========

   val_pressure_max = 2;
   val_temp_max = 100;
   flag_zero_delay_run_mn = 0;
   switch (en_pressure_mn_adc)
   {
   case 1: // vdo 10bar
      list_dien_tro_ap_suat[0] = 10;
      list_dien_tro_ap_suat[1] = 31;
      list_dien_tro_ap_suat[2] = 71;
      list_dien_tro_ap_suat[3] = 107;
      list_dien_tro_ap_suat[4] = 140;
      list_dien_tro_ap_suat[5] = 184;
      break;

   case 2: // vdo 5bar
      list_dien_tro_ap_suat[0] = 10;
      list_dien_tro_ap_suat[1] = 48;
      list_dien_tro_ap_suat[2] = 82;
      list_dien_tro_ap_suat[3] = 116;
      list_dien_tro_ap_suat[4] = 151;
      list_dien_tro_ap_suat[5] = 184;
      break;
   }

   switch (en_temp_mn_adc)
   {
   case 1: // vdo 120 do
      list_dien_tro_nhiet_do[0] = 134;
      list_dien_tro_nhiet_do[1] = 97;
      list_dien_tro_nhiet_do[2] = 70;
      list_dien_tro_nhiet_do[3] = 51;
      list_dien_tro_nhiet_do[4] = 38;
      list_dien_tro_nhiet_do[5] = 33;
      list_dien_tro_nhiet_do[6] = 29;
      list_dien_tro_nhiet_do[7] = 25;
      break;

   case 2: // vdo 150 do
      list_dien_tro_nhiet_do[0] = 221;
      list_dien_tro_nhiet_do[1] = 155;
      list_dien_tro_nhiet_do[2] = 112;
      list_dien_tro_nhiet_do[3] = 82;
      list_dien_tro_nhiet_do[4] = 61;
      list_dien_tro_nhiet_do[5] = 54;
      list_dien_tro_nhiet_do[6] = 47;
      list_dien_tro_nhiet_do[7] = 41;
      break;
   }

   thu_test = 0;
   gio_test = 8;
   phut_test = 0;

   chu_ky_test = 4;
}

//=================================
void check_full(void)
{

   if (style_mod_ac > 1)
   {
      style_mod_ac = 0;
      waitingData = 1;
   }

   if (level_set_ac_fail > 1)
   {
      level_set_ac_fail = 0;
      waitingData = 1;
   }

   if (en_pressure_mn > 1)
   {
      en_pressure_mn = 0;
      waitingData = 1;
   }

   if (en_temp_mn > 1)
   {
      en_temp_mn = 0;
      waitingData = 1;
   }

   if (Control_input > 3)
   {
      Control_input = 3;
      waitingData = 1;
   }

   if (volt_Protect_Accu > 25 || volt_Protect_Accu < 13.8)
   {
      volt_Protect_Accu = 16;
      waitingData = 1;
   }

   if (en_temp_mn_adc > 2)
   {
      en_temp_mn_adc = 0;
      waitingData = 1;
   }

   if (en_pressure_mn_adc > 2)
   {
      en_pressure_mn_adc = 0;
      waitingData = 1;
   }

   // TEST MPD
   //  tong_gio_chay_mn=0;
   if (tong_phut_chay_mn > 59)
   {
      tong_phut_chay_mn = 0;
      waitingData = 1;
   }

   // counter_ac_fail=0;
   if (error_code > 7)
   {
      error_code = 0;
      waitingData = 1;
   }
   // chu_ky_hien_tai=0;

   if (ac_vol_max > 250 || ac_vol_max < 235)
   {
      ac_vol_max = 250;
      waitingData = 1;
   }

   if (ac_vol_min > 200 || ac_vol_min < 160)
   {
      ac_vol_min = 160;
      waitingData = 1;
   }

   if (val_tg_on_dinh_ac > 240 || val_tg_on_dinh_ac < 30)
   {
      val_tg_on_dinh_ac = 120;
      waitingData = 1;
   }

   if (val_counter_ac_fail > 10 || val_counter_ac_fail < 1)
   {
      val_counter_ac_fail = 5;
      waitingData = 1;
   }

   // ac mn
   if (mn_vol_max < 220)
   {
      mn_vol_max = 240;
      waitingData = 1;
   }

   if (mn_vol_min > 200 || mn_vol_min < 160)
   {
      mn_vol_min = 160;
      waitingData = 1;
   }

   if (val_counter_start > 4 || val_counter_start < 2)
   {
      val_counter_start = 4;
      waitingData = 1;
   }

   if (val_tg_run_on > 24 || val_tg_run_on < 1)
   {
      val_tg_run_on = 24;
      waitingData = 1;
   }

   if (val_tg_preheat > 240 || val_tg_preheat < 10)
   {
      val_tg_preheat = 10;
      waitingData = 1;
   }

   if (val_tg_press_start > 60 || val_tg_press_start < 5)
   {
      val_tg_press_start = 5;
      waitingData = 1;
   }

   if (val_tg_air > 5 || val_tg_air < 2)
   {
      val_tg_air = 2;
      waitingData = 1;
   }

   if (val_tg_start_start > 240 || val_tg_start_start < 10)
   {
      val_tg_start_start = 60;
      waitingData = 1;
   }

   if (val_tg_on_dinh_mn > 240 || val_tg_on_dinh_mn < 30)
   {
      val_tg_on_dinh_mn = 60;
      waitingData = 1;
   }

   if (val_tg_off_mn > 10 || val_tg_off_mn < 1)
   {
      val_tg_off_mn = 1;
      waitingData = 1;
   }

   // if(val_tg_giainhiet>60 || val_tg_giainhiet<5){
   if (val_tg_giainhiet < 5)
   {
      val_tg_giainhiet = 30;
      waitingData = 1;
   }

   if (val_tg_press_stop > 60 || val_tg_press_stop < 2)
   {
      val_tg_press_stop = 5;
      waitingData = 1;
   }

   if (val_counter_mn_fail > 7 || val_counter_mn_fail < 1)
   {
      val_counter_mn_fail = 5;
      waitingData = 1;
   }

   if (time_check_sensor > 60 || time_check_sensor < 10)
   {
      time_check_sensor = 20;
      waitingData = 1;
   }

   // tiet kiem nang luong
   if (energy_save > 4)
   {
      energy_save = 0;
      waitingData = 1;
   }

   if (val_timer_delay_run_mn > 255 || val_timer_delay_run_mn < 1)
   {
      val_timer_delay_run_mn = 10;
      waitingData = 1;
   }

   //======
   if (gio_save_from > 23 || gio_save_from < 12)
   {
      gio_save_from = 23;
      waitingData = 1;
   }
   if (phut_save_from > 59)
   {
      phut_save_from = 0;
      waitingData = 1;
   }

   if (gio_save_to > 12)
   {
      gio_save_to = 6;
      waitingData = 1;
   }
   if (phut_save_to > 59)
   {
      phut_save_to = 0;
      waitingData = 1;
   }
   //=============

   if (val_pressure_max > 10 || val_pressure_max < 1)
   {
      val_pressure_max = 2;
      waitingData = 1;
   }

   if (val_temp_max > 130 || val_temp_max < 100)
   {
      val_temp_max = 100;
      waitingData = 1;
   }

   if (flag_zero_delay_run_mn > 1)
   {
      flag_zero_delay_run_mn = 0;
      waitingData = 1;
   }

   if (thu_test > 6)
   {
      thu_test = 0;
      waitingData = 1;
   }

   if (gio_test > 24)
   {
      gio_test = 8;
      waitingData = 1;
   }

   if (phut_test > 59)
   {
      phut_test = 0;
      waitingData = 1;
   }

   if (chu_ky_test < 1)
   {
      chu_ky_test = 4;
      waitingData = 1;
   }
}

void read_ram_ds1307(void)
{

   //=================
   // data tren eeprom
   char eedata_val_tg_air = ree(ee_val_tg_air);
   eerom_Hash_Data = eerom_Hash_Data + eedata_val_tg_air; //*

   char eedata_counter_ac_fail = ree(ee_counter_ac_fail);
   eerom_Hash_Data = eerom_Hash_Data + eedata_counter_ac_fail; //*

   char eedata_error_code = ree(ee_error_code);
   eerom_Hash_Data = eerom_Hash_Data + eedata_error_code; //*

   unsigned long eedata_tong_gio_chay_mn = make16(read_eeprom(ee_tong_gio_chay_mn + 1), read_eeprom(ee_tong_gio_chay_mn));
   eerom_Hash_Data = eerom_Hash_Data + eedata_tong_gio_chay_mn; //*

   char eedata_tong_phut_chay_mn = ree(ee_tong_phut_chay_mn);
   eerom_Hash_Data = eerom_Hash_Data + eedata_tong_phut_chay_mn; //*

   char eedata_val_counter_ac_fail = ree(ee_val_counter_ac_fail);
   eerom_Hash_Data = eerom_Hash_Data + eedata_val_counter_ac_fail; //*

   char eedata_val_counter_mn_fail = ree(ee_val_counter_mn_fail);
   eerom_Hash_Data = eerom_Hash_Data + eedata_val_counter_mn_fail; //*

   char eedata_energy_save = ree(ee_energy_save);
   eerom_Hash_Data = eerom_Hash_Data + eedata_energy_save; //*

   char eedata_level_set_ac_fail = ree(ee_level_set_ac_fail);
   eerom_Hash_Data = eerom_Hash_Data + eedata_level_set_ac_fail; //*

   // 16bit
   unsigned long eedata_ac_vol_max = make16(read_eeprom(ee_ac_vol_max + 1), read_eeprom(ee_ac_vol_max));
   eerom_Hash_Data = eerom_Hash_Data + eedata_ac_vol_max; //*

   char eedata_ac_vol_min = ree(ee_ac_vol_min);
   eerom_Hash_Data = eerom_Hash_Data + eedata_ac_vol_min; //*

   char eedata_val_tg_on_dinh_ac = ree(ee_val_tg_on_dinh_ac);
   eerom_Hash_Data = eerom_Hash_Data + eedata_val_tg_on_dinh_ac; //*

   char eedata_mn_vol_max = ree(ee_mn_vol_max);
   eerom_Hash_Data = eerom_Hash_Data + eedata_mn_vol_max; //*

   char eedata_mn_vol_min = ree(ee_mn_vol_min);
   eerom_Hash_Data = eerom_Hash_Data + eedata_mn_vol_min; //*

   char eedata_val_counter_start = ree(ee_val_counter_start);
   eerom_Hash_Data = eerom_Hash_Data + eedata_val_counter_start; //*

   char eedata_val_tg_run_on = ree(ee_val_tg_run_on);
   eerom_Hash_Data = eerom_Hash_Data + eedata_val_tg_run_on; //*

   char eedata_val_tg_preheat = ree(ee_val_tg_preheat);
   eerom_Hash_Data = eerom_Hash_Data + eedata_val_tg_preheat; //*

   char eedata_val_tg_press_start = ree(ee_val_tg_press_start);
   eerom_Hash_Data = eerom_Hash_Data + eedata_val_tg_press_start; //*

   char eedata_val_tg_on_dinh_mn = ree(ee_val_tg_on_dinh_mn);
   eerom_Hash_Data = eerom_Hash_Data + eedata_val_tg_on_dinh_mn; //*

   char eedata_val_tg_off_mn = ree(ee_val_tg_off_mn);
   eerom_Hash_Data = eerom_Hash_Data + eedata_val_tg_off_mn; //*

   char eedata_val_tg_giainhiet = ree(ee_val_tg_giainhiet);
   eerom_Hash_Data = eerom_Hash_Data + eedata_val_tg_giainhiet; //*

   char eedata_en_temp_mn = ree(ee_en_temp_mn);
   eerom_Hash_Data = eerom_Hash_Data + eedata_en_temp_mn; //*

   char eedata_en_pressure_mn = ree(ee_en_pressure_mn);
   eerom_Hash_Data = eerom_Hash_Data + eedata_en_pressure_mn; //*

   char eedata_val_timer_delay_run_mn = ree(ee_val_timer_delay_run_mn);
   eerom_Hash_Data = eerom_Hash_Data + eedata_val_timer_delay_run_mn; //*

   char eedata_style_mod_ac = ree(ee_style_mod_ac);
   eerom_Hash_Data = eerom_Hash_Data + eedata_style_mod_ac; //*

   char eedata_flag_zero_delay_run_ac = ree(ee_flag_zero_delay_run_ac);
   eerom_Hash_Data = eerom_Hash_Data + eedata_flag_zero_delay_run_ac; //*

   char eedata_flag_zero_delay_run_mn = ree(ee_flag_zero_delay_run_mn);
   eerom_Hash_Data = eerom_Hash_Data + eedata_flag_zero_delay_run_mn; //*

   char eedata_val_tg_start_start = ree(ee_val_tg_start_start);
   eerom_Hash_Data = eerom_Hash_Data + eedata_val_tg_start_start; //*

   char eedata_val_tg_press_stop = ree(ee_val_tg_press_stop);
   eerom_Hash_Data = eerom_Hash_Data + eedata_val_tg_press_stop; //*

   char eedata_en_temp_mn_adc = ree(ee_en_temp_adc_mn);
   eerom_Hash_Data = eerom_Hash_Data + eedata_en_temp_mn_adc; //*

   char eedata_en_pressure_mn_adc = ree(ee_en_pressure_adc_mn);
   eerom_Hash_Data = eerom_Hash_Data + eedata_en_pressure_mn_adc; //*

   unsigned char eedata_list_dien_tro_ap_suat[6] = {};

   eedata_list_dien_tro_ap_suat[0] = ree(ee_list_resistor_pressure);
   eerom_Hash_Data = eerom_Hash_Data + eedata_list_dien_tro_ap_suat[0]; //*

   eedata_list_dien_tro_ap_suat[1] = ree(ee_list_resistor_pressure + 1);
   eerom_Hash_Data = eerom_Hash_Data + eedata_list_dien_tro_ap_suat[1]; //*

   eedata_list_dien_tro_ap_suat[2] = ree(ee_list_resistor_pressure + 2);
   eerom_Hash_Data = eerom_Hash_Data + eedata_list_dien_tro_ap_suat[2]; //*

   eedata_list_dien_tro_ap_suat[3] = ree(ee_list_resistor_pressure + 3);
   eerom_Hash_Data = eerom_Hash_Data + eedata_list_dien_tro_ap_suat[3]; //*

   eedata_list_dien_tro_ap_suat[4] = ree(ee_list_resistor_pressure + 4);
   eerom_Hash_Data = eerom_Hash_Data + eedata_list_dien_tro_ap_suat[4]; //*

   eedata_list_dien_tro_ap_suat[5] = ree(ee_list_resistor_pressure + 5);
   eerom_Hash_Data = eerom_Hash_Data + eedata_list_dien_tro_ap_suat[5]; //*

   unsigned char eedata_list_dien_tro_nhiet_do[11] = {};
   eedata_list_dien_tro_nhiet_do[0] = ree(ee_list_resistor_temp);
   eerom_Hash_Data = eerom_Hash_Data + eedata_list_dien_tro_nhiet_do[0]; //*

   eedata_list_dien_tro_nhiet_do[1] = ree(ee_list_resistor_temp + 1);
   eerom_Hash_Data = eerom_Hash_Data + eedata_list_dien_tro_nhiet_do[1]; //*

   eedata_list_dien_tro_nhiet_do[2] = ree(ee_list_resistor_temp + 2);
   eerom_Hash_Data = eerom_Hash_Data + eedata_list_dien_tro_nhiet_do[2]; //*

   eedata_list_dien_tro_nhiet_do[3] = ree(ee_list_resistor_temp + 3);
   eerom_Hash_Data = eerom_Hash_Data + eedata_list_dien_tro_nhiet_do[3]; //*

   eedata_list_dien_tro_nhiet_do[4] = ree(ee_list_resistor_temp + 4);
   eerom_Hash_Data = eerom_Hash_Data + eedata_list_dien_tro_nhiet_do[4]; //*

   eedata_list_dien_tro_nhiet_do[5] = ree(ee_list_resistor_temp + 5);
   eerom_Hash_Data = eerom_Hash_Data + eedata_list_dien_tro_nhiet_do[5]; //*

   eedata_list_dien_tro_nhiet_do[6] = ree(ee_list_resistor_temp + 6);
   eerom_Hash_Data = eerom_Hash_Data + eedata_list_dien_tro_nhiet_do[6]; //*

   eedata_list_dien_tro_nhiet_do[7] = ree(ee_list_resistor_temp + 7);
   eerom_Hash_Data = eerom_Hash_Data + eedata_list_dien_tro_nhiet_do[7]; //*

   eedata_list_dien_tro_nhiet_do[8] = ree(ee_list_resistor_temp + 8);
   eerom_Hash_Data = eerom_Hash_Data + eedata_list_dien_tro_nhiet_do[8]; //*

   eedata_list_dien_tro_nhiet_do[9] = ree(ee_list_resistor_temp + 9);
   eerom_Hash_Data = eerom_Hash_Data + eedata_list_dien_tro_nhiet_do[9]; //*

   eedata_list_dien_tro_nhiet_do[10] = ree(ee_list_resistor_temp + 10);
   eerom_Hash_Data = eerom_Hash_Data + eedata_list_dien_tro_nhiet_do[10]; //*

   char eedata_val_pressure_max = ree(ee_pressure_adc_max);
   eerom_Hash_Data = eerom_Hash_Data + eedata_val_pressure_max; //*

   char eedata_val_temp_max = ree(ee_temp_adc_max);
   eerom_Hash_Data = eerom_Hash_Data + eedata_val_temp_max; //*

   char eedata_time_check_sensor = ree(ee_time_check_sensor);
   eerom_Hash_Data = eerom_Hash_Data + eedata_time_check_sensor; //*

   char eedata_thu_test = ree(ee_thu_test);
   eerom_Hash_Data = eerom_Hash_Data + eedata_thu_test; //*

   char eedata_gio_test = ree(ee_gio_test);
   eerom_Hash_Data = eerom_Hash_Data + eedata_gio_test; //*

   char eedata_phut_test = ree(ee_phut_test);
   eerom_Hash_Data = eerom_Hash_Data + eedata_phut_test; //*

   char eedata_chu_ky_test = ree(ee_chu_ky_test);
   eerom_Hash_Data = eerom_Hash_Data + eedata_chu_ky_test; //*

   char eedata_chu_ky_hien_tai = ree(ee_chu_ky_hien_tai);
   eerom_Hash_Data = eerom_Hash_Data + eedata_chu_ky_hien_tai; //*

   char eedata_Control_input = ree(ee_Control_input);
   eerom_Hash_Data = eerom_Hash_Data + eedata_Control_input; //*

   char eedata_volt_Protect_Accu = ree(ee_volt_Protect_Accu);
   eerom_Hash_Data = eerom_Hash_Data + eedata_volt_Protect_Accu; //*

   eerom_Cert_Save = make16(read_eeprom(ee_Cert_Data + 1), read_eeprom(ee_Cert_Data));

   eerom_Hash_Data = eerom_Hash_Data + eerom_Cert_Save; //*

   char eedata_gio_save_from = ree(ee_Hour_Save_From);
   eerom_Hash_Data = eerom_Hash_Data + eedata_gio_save_from; //*

   char eedata_phut_save_from = ree(ee_Min_Save_From);
   eerom_Hash_Data = eerom_Hash_Data + eedata_phut_save_from; //*

   char eedata_gio_save_to = ree(ee_Hour_Save_To);
   eerom_Hash_Data = eerom_Hash_Data + eedata_gio_save_to; //*

   char eedata_phut_save_to = ree(ee_Min_Save_To);
   eerom_Hash_Data = eerom_Hash_Data + eedata_phut_save_to; //*

   eerom_Hash_Save = make16(read_eeprom(ee_Hash_Data + 1), read_eeprom(ee_Hash_Data));
   //====================================================================================

   char ram_val_tg_air = PCF8583_read_byte(ds1307_val_tg_air);
   ram_Hash_Data = ram_Hash_Data + ram_val_tg_air; //*

   char ram_counter_ac_fail = PCF8583_read_byte(ds1307_counter_ac_fail);
   ram_Hash_Data = ram_Hash_Data + ram_counter_ac_fail; //*

   char ram_error_code = PCF8583_read_byte(ds1307_error_code);
   ram_Hash_Data = ram_Hash_Data + ram_error_code; //*

   unsigned long ram_tong_gio_chay_mn = make16(PCF8583_read_byte(ds1307_tong_gio_chay_mn + 1), PCF8583_read_byte(ds1307_tong_gio_chay_mn));
   ram_Hash_Data = ram_Hash_Data + ram_tong_gio_chay_mn; //*

   char ram_tong_phut_chay_mn = PCF8583_read_byte(ds1307_tong_phut_chay_mn);
   ram_Hash_Data = ram_Hash_Data + ram_tong_phut_chay_mn; //*

   char ram_val_counter_ac_fail = PCF8583_read_byte(ds1307_val_counter_ac_fail);
   ram_Hash_Data = ram_Hash_Data + ram_val_counter_ac_fail; //*

   char ram_val_counter_mn_fail = PCF8583_read_byte(ds1307_val_counter_mn_fail);
   ram_Hash_Data = ram_Hash_Data + ram_val_counter_mn_fail; //*

   char ram_energy_save = PCF8583_read_byte(ds1307_energy_save);
   ram_Hash_Data = ram_Hash_Data + ram_energy_save; //*

   char ram_level_set_ac_fail = PCF8583_read_byte(ds1307_level_set_ac_fail);
   ram_Hash_Data = ram_Hash_Data + ram_level_set_ac_fail; //*

   // 16bit
   unsigned long ram_ac_vol_max = make16(PCF8583_read_byte(ds1307_ac_vol_max + 1), PCF8583_read_byte(ds1307_ac_vol_max));
   ram_Hash_Data = ram_Hash_Data + ram_ac_vol_max; //*

   char ram_ac_vol_min = PCF8583_read_byte(ds1307_ac_vol_min);
   ram_Hash_Data = ram_Hash_Data + ram_ac_vol_min; //*

   char ram_val_tg_on_dinh_ac = PCF8583_read_byte(ds1307_val_tg_on_dinh_ac);
   ram_Hash_Data = ram_Hash_Data + ram_val_tg_on_dinh_ac; //*

   char ram_mn_vol_max = PCF8583_read_byte(ds1307_mn_vol_max);
   ram_Hash_Data = ram_Hash_Data + ram_mn_vol_max; //*

   char ram_mn_vol_min = PCF8583_read_byte(ds1307_mn_vol_min);
   ram_Hash_Data = ram_Hash_Data + ram_mn_vol_min; //*

   char ram_val_counter_start = PCF8583_read_byte(ds1307_val_counter_start);
   ram_Hash_Data = ram_Hash_Data + ram_val_counter_start; //*

   char ram_val_tg_run_on = PCF8583_read_byte(ds1307_val_tg_run_on);
   ram_Hash_Data = ram_Hash_Data + ram_val_tg_run_on; //*

   char ram_val_tg_preheat = PCF8583_read_byte(ds1307_val_tg_preheat);
   ram_Hash_Data = ram_Hash_Data + ram_val_tg_preheat; //*

   char ram_val_tg_press_start = PCF8583_read_byte(ds1307_val_tg_press_start);
   ram_Hash_Data = ram_Hash_Data + ram_val_tg_press_start; //*

   char ram_val_tg_on_dinh_mn = PCF8583_read_byte(ds1307_val_tg_on_dinh_mn);
   ram_Hash_Data = ram_Hash_Data + ram_val_tg_on_dinh_mn; //*

   char ram_val_tg_off_mn = PCF8583_read_byte(ds1307_val_tg_off_mn);
   ram_Hash_Data = ram_Hash_Data + ram_val_tg_off_mn; //*

   char ram_val_tg_giainhiet = PCF8583_read_byte(ds1307_val_tg_giainhiet);
   ram_Hash_Data = ram_Hash_Data + ram_val_tg_giainhiet; //*

   char ram_en_temp_mn = PCF8583_read_byte(ds1307_en_temp_mn);
   ram_Hash_Data = ram_Hash_Data + ram_en_temp_mn; //*

   char ram_en_pressure_mn = PCF8583_read_byte(ds1307_en_pressure_mn);
   ram_Hash_Data = ram_Hash_Data + ram_en_pressure_mn; //*

   char ram_val_timer_delay_run_mn = PCF8583_read_byte(ds1307_val_timer_delay_run_mn);
   ram_Hash_Data = ram_Hash_Data + ram_val_timer_delay_run_mn; //*

   char ram_style_mod_ac = PCF8583_read_byte(ds1307_style_mod_ac);
   ram_Hash_Data = ram_Hash_Data + ram_style_mod_ac; //*

   char ram_flag_zero_delay_run_ac = PCF8583_read_byte(ds1307_flag_zero_delay_run_ac);
   ram_Hash_Data = ram_Hash_Data + ram_flag_zero_delay_run_ac; //*

   char ram_flag_zero_delay_run_mn = PCF8583_read_byte(ds1307_flag_zero_delay_run_mn);
   ram_Hash_Data = ram_Hash_Data + ram_flag_zero_delay_run_mn; //*

   char ram_val_tg_start_start = PCF8583_read_byte(ds1307_val_tg_start_start);
   ram_Hash_Data = ram_Hash_Data + ram_val_tg_start_start; //*

   char ram_val_tg_press_stop = PCF8583_read_byte(ds1307_val_tg_press_stop);
   ram_Hash_Data = ram_Hash_Data + ram_val_tg_press_stop; //*

   char ram_en_temp_mn_adc = PCF8583_read_byte(ds1307_en_temp_adc_mn);
   ram_Hash_Data = ram_Hash_Data + ram_en_temp_mn_adc; //*

   char ram_en_pressure_mn_adc = PCF8583_read_byte(ds1307_en_pressure_adc_mn);
   ram_Hash_Data = ram_Hash_Data + ram_en_pressure_mn_adc; //*

   unsigned char ram_list_dien_tro_ap_suat[6] = {};
   ram_list_dien_tro_ap_suat[0] = PCF8583_read_byte(ds1307_list_resistor_pressure);
   ram_Hash_Data = ram_Hash_Data + ram_list_dien_tro_ap_suat[0]; //*

   ram_list_dien_tro_ap_suat[1] = PCF8583_read_byte(ds1307_list_resistor_pressure + 1);
   ram_Hash_Data = ram_Hash_Data + ram_list_dien_tro_ap_suat[1]; //*

   ram_list_dien_tro_ap_suat[2] = PCF8583_read_byte(ds1307_list_resistor_pressure + 2);
   ram_Hash_Data = ram_Hash_Data + ram_list_dien_tro_ap_suat[2]; //*

   ram_list_dien_tro_ap_suat[3] = PCF8583_read_byte(ds1307_list_resistor_pressure + 3);
   ram_Hash_Data = ram_Hash_Data + ram_list_dien_tro_ap_suat[3]; //*

   ram_list_dien_tro_ap_suat[4] = PCF8583_read_byte(ds1307_list_resistor_pressure + 4);
   ram_Hash_Data = ram_Hash_Data + ram_list_dien_tro_ap_suat[4]; //*

   ram_list_dien_tro_ap_suat[5] = PCF8583_read_byte(ds1307_list_resistor_pressure + 5);
   ram_Hash_Data = ram_Hash_Data + ram_list_dien_tro_ap_suat[5]; //*

   unsigned char ram_list_dien_tro_nhiet_do[11] = {};
   ram_list_dien_tro_nhiet_do[0] = PCF8583_read_byte(ds1307_list_resistor_temp);
   ram_Hash_Data = ram_Hash_Data + ram_list_dien_tro_nhiet_do[0]; //*

   ram_list_dien_tro_nhiet_do[1] = PCF8583_read_byte(ds1307_list_resistor_temp + 1);
   ram_Hash_Data = ram_Hash_Data + ram_list_dien_tro_nhiet_do[1]; //*

   ram_list_dien_tro_nhiet_do[2] = PCF8583_read_byte(ds1307_list_resistor_temp + 2);
   ram_Hash_Data = ram_Hash_Data + ram_list_dien_tro_nhiet_do[2]; //*

   ram_list_dien_tro_nhiet_do[3] = PCF8583_read_byte(ds1307_list_resistor_temp + 3);
   ram_Hash_Data = ram_Hash_Data + ram_list_dien_tro_nhiet_do[3]; //*

   ram_list_dien_tro_nhiet_do[4] = PCF8583_read_byte(ds1307_list_resistor_temp + 4);
   ram_Hash_Data = ram_Hash_Data + ram_list_dien_tro_nhiet_do[4]; //*

   ram_list_dien_tro_nhiet_do[5] = PCF8583_read_byte(ds1307_list_resistor_temp + 5);
   ram_Hash_Data = ram_Hash_Data + ram_list_dien_tro_nhiet_do[5]; //*

   ram_list_dien_tro_nhiet_do[6] = PCF8583_read_byte(ds1307_list_resistor_temp + 6);
   ram_Hash_Data = ram_Hash_Data + ram_list_dien_tro_nhiet_do[6]; //*

   ram_list_dien_tro_nhiet_do[7] = PCF8583_read_byte(ds1307_list_resistor_temp + 7);
   ram_Hash_Data = ram_Hash_Data + ram_list_dien_tro_nhiet_do[7]; //*

   ram_list_dien_tro_nhiet_do[8] = PCF8583_read_byte(ds1307_list_resistor_temp + 8);
   ram_Hash_Data = ram_Hash_Data + ram_list_dien_tro_nhiet_do[8]; //*

   ram_list_dien_tro_nhiet_do[9] = PCF8583_read_byte(ds1307_list_resistor_temp + 9);
   ram_Hash_Data = ram_Hash_Data + ram_list_dien_tro_nhiet_do[9]; //*

   ram_list_dien_tro_nhiet_do[10] = PCF8583_read_byte(ds1307_list_resistor_temp + 10);
   ram_Hash_Data = ram_Hash_Data + ram_list_dien_tro_nhiet_do[10]; //*

   char ram_val_pressure_max = PCF8583_read_byte(ds1307_pressure_adc_max);
   ram_Hash_Data = ram_Hash_Data + ram_val_pressure_max; //*

   char ram_val_temp_max = PCF8583_read_byte(ds1307_temp_adc_max);
   ram_Hash_Data = ram_Hash_Data + ram_val_temp_max; //*

   char ram_time_check_sensor = PCF8583_read_byte(ds1307_time_check_sensor);
   ram_Hash_Data = ram_Hash_Data + ram_time_check_sensor; //*

   char ram_thu_test = PCF8583_read_byte(ds1307_thu_test);
   ram_Hash_Data = ram_Hash_Data + ram_thu_test; //*

   char ram_gio_test = PCF8583_read_byte(ds1307_gio_test);
   ram_Hash_Data = ram_Hash_Data + ram_gio_test; //*

   char ram_phut_test = PCF8583_read_byte(ds1307_phut_test);
   ram_Hash_Data = ram_Hash_Data + ram_phut_test; //*

   char ram_chu_ky_test = PCF8583_read_byte(ds1307_chu_ky_test);
   ram_Hash_Data = ram_Hash_Data + ram_chu_ky_test; //*

   char ram_chu_ky_hien_tai = PCF8583_read_byte(ds1307_chu_ky_hien_tai);
   ram_Hash_Data = ram_Hash_Data + ram_chu_ky_hien_tai; //*

   char ram_Control_input = PCF8583_read_byte(ds1307_Control_input);
   ram_Hash_Data = ram_Hash_Data + ram_Control_input; //*

   char ram_volt_Protect_Accu = PCF8583_read_byte(ds1307_volt_Protect_Accu);
   ram_Hash_Data = ram_Hash_Data + ram_volt_Protect_Accu; //*

   ram_Cert_Save = make16(PCF8583_read_byte(ds1307_Cert_Data + 1), PCF8583_read_byte(ds1307_Cert_Data));

   ram_Hash_Data = ram_Hash_Data + ram_Cert_Save; //*

   //=======
   char ram_gio_save_from = PCF8583_read_byte(ds1307_Hour_Save_From);
   ram_Hash_Data = ram_Hash_Data + ram_gio_save_from; //*

   char ram_phut_save_from = PCF8583_read_byte(ds1307_Min_Save_From);
   ram_Hash_Data = ram_Hash_Data + ram_phut_save_from; //*

   char ram_gio_save_to = PCF8583_read_byte(ds1307_Hour_Save_To);
   ram_Hash_Data = ram_Hash_Data + ram_gio_save_to; //*

   char ram_phut_save_to = PCF8583_read_byte(ds1307_Min_Save_To);
   ram_Hash_Data = ram_Hash_Data + ram_phut_save_to; //*
                                                     //=======

   ram_Hash_Save = make16(PCF8583_read_byte(ds1307_Hash_Data + 1), PCF8583_read_byte(ds1307_Hash_Data));

   if (ram_Hash_Save == ram_Hash_Data && ram_Cert_Save == Cert_Data)
   {
      val_tg_air = ram_val_tg_air;                   //*
      counter_ac_fail = ram_counter_ac_fail;         //*
      error_code = ram_error_code;                   //*
      tong_gio_chay_mn = ram_tong_gio_chay_mn;       //*
      tong_phut_chay_mn = ram_tong_phut_chay_mn;     //*
      val_counter_ac_fail = ram_val_counter_ac_fail; //*
      val_counter_mn_fail = ram_val_counter_mn_fail; //*
      energy_save = ram_energy_save;                 //*
      level_set_ac_fail = ram_level_set_ac_fail;     //*

      ac_vol_max = ram_ac_vol_max;                                 //*
      ac_vol_min = ram_ac_vol_min;                                 //*
      val_tg_on_dinh_ac = ram_val_tg_on_dinh_ac;                   //*
      mn_vol_max = ram_mn_vol_max;                                 //*
      mn_vol_min = ram_mn_vol_min;                                 //*
      val_counter_start = ram_val_counter_start;                   //*
      val_tg_run_on = ram_val_tg_run_on;                           //*
      val_tg_preheat = ram_val_tg_preheat;                         //*
      val_tg_press_start = ram_val_tg_press_start;                 //*
      val_tg_on_dinh_mn = ram_val_tg_on_dinh_mn;                   //*
      val_tg_off_mn = ram_val_tg_off_mn;                           //*
      val_tg_giainhiet = ram_val_tg_giainhiet;                     //*
      en_temp_mn = ram_en_temp_mn;                                 //*
      en_pressure_mn = ram_en_pressure_mn;                         //*
      val_timer_delay_run_mn = ram_val_timer_delay_run_mn;         //*
      style_mod_ac = ram_style_mod_ac;                             //*
      flag_zero_delay_run_ac = ram_flag_zero_delay_run_ac;         //*
      flag_zero_delay_run_mn = ram_flag_zero_delay_run_mn;         //*
      val_tg_start_start = ram_val_tg_start_start;                 //*
      val_tg_press_stop = ram_val_tg_press_stop;                   //*
      en_temp_mn_adc = ram_en_temp_mn_adc;                         //*
      en_pressure_mn_adc = ram_en_pressure_mn_adc;                 //*
      list_dien_tro_ap_suat[0] = ram_list_dien_tro_ap_suat[0];     //*
      list_dien_tro_ap_suat[1] = ram_list_dien_tro_ap_suat[1];     //*
      list_dien_tro_ap_suat[2] = ram_list_dien_tro_ap_suat[2];     //*
      list_dien_tro_ap_suat[3] = ram_list_dien_tro_ap_suat[3];     //*
      list_dien_tro_ap_suat[4] = ram_list_dien_tro_ap_suat[4];     //*
      list_dien_tro_ap_suat[5] = ram_list_dien_tro_ap_suat[5];     //*
      list_dien_tro_nhiet_do[0] = ram_list_dien_tro_nhiet_do[0];   //*
      list_dien_tro_nhiet_do[1] = ram_list_dien_tro_nhiet_do[1];   //*
      list_dien_tro_nhiet_do[2] = ram_list_dien_tro_nhiet_do[2];   //*
      list_dien_tro_nhiet_do[3] = ram_list_dien_tro_nhiet_do[3];   //*
      list_dien_tro_nhiet_do[4] = ram_list_dien_tro_nhiet_do[4];   //*
      list_dien_tro_nhiet_do[5] = ram_list_dien_tro_nhiet_do[5];   //*
      list_dien_tro_nhiet_do[6] = ram_list_dien_tro_nhiet_do[6];   //*
      list_dien_tro_nhiet_do[7] = ram_list_dien_tro_nhiet_do[7];   //*
      list_dien_tro_nhiet_do[8] = ram_list_dien_tro_nhiet_do[8];   //*
      list_dien_tro_nhiet_do[9] = ram_list_dien_tro_nhiet_do[9];   //*
      list_dien_tro_nhiet_do[10] = ram_list_dien_tro_nhiet_do[10]; //*

      val_pressure_max = ram_val_pressure_max;   //*
      val_temp_max = ram_val_temp_max;           //*
      time_check_sensor = ram_time_check_sensor; //*
      thu_test = ram_thu_test;                   //*
      gio_test = ram_gio_test;                   //*
      phut_test = ram_phut_test;                 //*
      chu_ky_test = ram_chu_ky_test;             //*
      chu_ky_hien_tai = ram_chu_ky_hien_tai;     //*
      Control_input = ram_Control_input;         //*

      volt_Protect_Accu = ram_volt_Protect_Accu / 10; //*

      //==========
      gio_save_from = ram_gio_save_from;
      phut_save_from = ram_phut_save_from;
      gio_save_to = ram_gio_save_to;
      phut_save_to = ram_phut_save_to;
      //==========

      write_data_ee();
      Hash_Full();
   }
   else if (eerom_Hash_Save == eerom_Hash_Data && eerom_Cert_Save == Cert_Data)
   {
      val_tg_air = eedata_val_tg_air;                   //*
      counter_ac_fail = eedata_counter_ac_fail;         //*
      error_code = eedata_error_code;                   //*
      tong_gio_chay_mn = eedata_tong_gio_chay_mn;       //*
      tong_phut_chay_mn = eedata_tong_phut_chay_mn;     //*
      val_counter_ac_fail = eedata_val_counter_ac_fail; //*
      val_counter_mn_fail = eedata_val_counter_mn_fail; //*
      energy_save = eedata_energy_save;                 //*
      level_set_ac_fail = eedata_level_set_ac_fail;     //*

      ac_vol_max = eedata_ac_vol_max;                                 //*
      ac_vol_min = eedata_ac_vol_min;                                 //*
      val_tg_on_dinh_ac = eedata_val_tg_on_dinh_ac;                   //*
      mn_vol_max = eedata_mn_vol_max;                                 //*
      mn_vol_min = eedata_mn_vol_min;                                 //*
      val_counter_start = eedata_val_counter_start;                   //*
      val_tg_run_on = eedata_val_tg_run_on;                           //*
      val_tg_preheat = eedata_val_tg_preheat;                         //*
      val_tg_press_start = eedata_val_tg_press_start;                 //*
      val_tg_on_dinh_mn = eedata_val_tg_on_dinh_mn;                   //*
      val_tg_off_mn = eedata_val_tg_off_mn;                           //*
      val_tg_giainhiet = eedata_val_tg_giainhiet;                     //*
      en_temp_mn = eedata_en_temp_mn;                                 //*
      en_pressure_mn = eedata_en_pressure_mn;                         //*
      val_timer_delay_run_mn = eedata_val_timer_delay_run_mn;         //*
      style_mod_ac = eedata_style_mod_ac;                             //*
      flag_zero_delay_run_ac = eedata_flag_zero_delay_run_ac;         //*
      flag_zero_delay_run_mn = eedata_flag_zero_delay_run_mn;         //*
      val_tg_start_start = eedata_val_tg_start_start;                 //*
      val_tg_press_stop = eedata_val_tg_press_stop;                   //*
      en_temp_mn_adc = eedata_en_temp_mn_adc;                         //*
      en_pressure_mn_adc = eedata_en_pressure_mn_adc;                 //*
      list_dien_tro_ap_suat[0] = eedata_list_dien_tro_ap_suat[0];     //*
      list_dien_tro_ap_suat[1] = eedata_list_dien_tro_ap_suat[1];     //*
      list_dien_tro_ap_suat[2] = eedata_list_dien_tro_ap_suat[2];     //*
      list_dien_tro_ap_suat[3] = eedata_list_dien_tro_ap_suat[3];     //*
      list_dien_tro_ap_suat[4] = eedata_list_dien_tro_ap_suat[4];     //*
      list_dien_tro_ap_suat[5] = eedata_list_dien_tro_ap_suat[5];     //*
      list_dien_tro_nhiet_do[0] = eedata_list_dien_tro_nhiet_do[0];   //*
      list_dien_tro_nhiet_do[1] = eedata_list_dien_tro_nhiet_do[1];   //*
      list_dien_tro_nhiet_do[2] = eedata_list_dien_tro_nhiet_do[2];   //*
      list_dien_tro_nhiet_do[3] = eedata_list_dien_tro_nhiet_do[3];   //*
      list_dien_tro_nhiet_do[4] = eedata_list_dien_tro_nhiet_do[4];   //*
      list_dien_tro_nhiet_do[5] = eedata_list_dien_tro_nhiet_do[5];   //*
      list_dien_tro_nhiet_do[6] = eedata_list_dien_tro_nhiet_do[6];   //*
      list_dien_tro_nhiet_do[7] = eedata_list_dien_tro_nhiet_do[7];   //*
      list_dien_tro_nhiet_do[8] = eedata_list_dien_tro_nhiet_do[8];   //*
      list_dien_tro_nhiet_do[9] = eedata_list_dien_tro_nhiet_do[9];   //*
      list_dien_tro_nhiet_do[10] = eedata_list_dien_tro_nhiet_do[10]; //*

      val_pressure_max = eedata_val_pressure_max;   //*
      val_temp_max = eedata_val_temp_max;           //*
      time_check_sensor = eedata_time_check_sensor; //*
      thu_test = eedata_thu_test;                   //*
      gio_test = eedata_gio_test;                   //*
      phut_test = eedata_phut_test;                 //*
      chu_ky_test = eedata_chu_ky_test;             //*
      chu_ky_hien_tai = eedata_chu_ky_hien_tai;     //*
      Control_input = eedata_Control_input;         //*

      volt_Protect_Accu = eedata_volt_Protect_Accu / 10; //*

      //==========
      gio_save_from = eedata_gio_save_from;
      phut_save_from = eedata_phut_save_from;
      gio_save_to = eedata_gio_save_to;
      phut_save_to = eedata_phut_save_to;
      //==========

      write_ram_ds1307();
      Hash_Full();
   }
   else
   { // ((ram_Hash_Save!=ram_Hash_Data || ram_Cert_Save!=3107) && (eerom_Hash_Save!=eerom_Hash_Data || eerom_Cert_Save!=3107)){
      defaul_admin();
      defaul_data();
      write_ram_ds1307();
      write_data_ee();
      Hash_Full();
   }
}

void write_ram_ds1307(void)
{
   int temp = 0;

   PCF8583_write_byte(ds1307_counter_ac_fail, counter_ac_fail);
   PCF8583_write_byte(ds1307_error_code, error_code);
   // 16bit
   PCF8583_write_byte(ds1307_tong_gio_chay_mn, make8(tong_gio_chay_mn, 0));
   PCF8583_write_byte(ds1307_tong_gio_chay_mn + 1, make8(tong_gio_chay_mn, 1));

   PCF8583_write_byte(ds1307_tong_phut_chay_mn, tong_phut_chay_mn);
   PCF8583_write_byte(ds1307_energy_save, energy_save);
   PCF8583_write_byte(ds1307_level_set_ac_fail, level_set_ac_fail);
   // 16bit
   PCF8583_write_byte(ds1307_ac_vol_max, make8(ac_vol_max, 0));
   PCF8583_write_byte(ds1307_ac_vol_max + 1, make8(ac_vol_max, 1));

   PCF8583_write_byte(ds1307_ac_vol_min, ac_vol_min);
   PCF8583_write_byte(ds1307_val_tg_on_dinh_ac, val_tg_on_dinh_ac);
   PCF8583_write_byte(ds1307_mn_vol_max, mn_vol_max);
   PCF8583_write_byte(ds1307_mn_vol_min, mn_vol_min);
   PCF8583_write_byte(ds1307_val_counter_start, val_counter_start);
   PCF8583_write_byte(ds1307_val_tg_run_on, val_tg_run_on);
   PCF8583_write_byte(ds1307_val_tg_preheat, val_tg_preheat);
   PCF8583_write_byte(ds1307_val_tg_press_start, val_tg_press_start);
   PCF8583_write_byte(ds1307_val_tg_on_dinh_mn, val_tg_on_dinh_mn);
   PCF8583_write_byte(ds1307_val_tg_off_mn, val_tg_off_mn);
   PCF8583_write_byte(ds1307_val_tg_giainhiet, val_tg_giainhiet);
   PCF8583_write_byte(ds1307_en_temp_mn, en_temp_mn);
   PCF8583_write_byte(ds1307_en_pressure_mn, en_pressure_mn);
   PCF8583_write_byte(ds1307_val_timer_delay_run_mn, val_timer_delay_run_mn);
   PCF8583_write_byte(ds1307_style_mod_ac, style_mod_ac);
   PCF8583_write_byte(ds1307_flag_zero_delay_run_ac, flag_zero_delay_run_ac);
   PCF8583_write_byte(ds1307_flag_zero_delay_run_mn, flag_zero_delay_run_mn);
   PCF8583_write_byte(ds1307_val_tg_start_start, val_tg_start_start);

   PCF8583_write_byte(ds1307_val_counter_ac_fail, val_counter_ac_fail);
   PCF8583_write_byte(ds1307_val_counter_mn_fail, val_counter_mn_fail);
   PCF8583_write_byte(ds1307_val_tg_press_stop, val_tg_press_stop);

   PCF8583_write_byte(ds1307_en_temp_adc_mn, en_temp_mn_adc);
   PCF8583_write_byte(ds1307_en_pressure_adc_mn, en_pressure_mn_adc);

   PCF8583_write_byte(ds1307_list_resistor_pressure, list_dien_tro_ap_suat[0]);
   PCF8583_write_byte(ds1307_list_resistor_pressure + 1, list_dien_tro_ap_suat[1]);
   PCF8583_write_byte(ds1307_list_resistor_pressure + 2, list_dien_tro_ap_suat[2]);
   PCF8583_write_byte(ds1307_list_resistor_pressure + 3, list_dien_tro_ap_suat[3]);
   PCF8583_write_byte(ds1307_list_resistor_pressure + 4, list_dien_tro_ap_suat[4]);
   PCF8583_write_byte(ds1307_list_resistor_pressure + 5, list_dien_tro_ap_suat[5]);

   PCF8583_write_byte(ds1307_list_resistor_temp, list_dien_tro_nhiet_do[0]);
   PCF8583_write_byte(ds1307_list_resistor_temp + 1, list_dien_tro_nhiet_do[1]);
   PCF8583_write_byte(ds1307_list_resistor_temp + 2, list_dien_tro_nhiet_do[2]);
   PCF8583_write_byte(ds1307_list_resistor_temp + 3, list_dien_tro_nhiet_do[3]);
   PCF8583_write_byte(ds1307_list_resistor_temp + 4, list_dien_tro_nhiet_do[4]);
   PCF8583_write_byte(ds1307_list_resistor_temp + 5, list_dien_tro_nhiet_do[5]);
   PCF8583_write_byte(ds1307_list_resistor_temp + 6, list_dien_tro_nhiet_do[6]);
   PCF8583_write_byte(ds1307_list_resistor_temp + 7, list_dien_tro_nhiet_do[7]);
   PCF8583_write_byte(ds1307_list_resistor_temp + 8, list_dien_tro_nhiet_do[8]);
   PCF8583_write_byte(ds1307_list_resistor_temp + 9, list_dien_tro_nhiet_do[9]);
   PCF8583_write_byte(ds1307_list_resistor_temp + 10, list_dien_tro_nhiet_do[10]);

   PCF8583_write_byte(ds1307_pressure_adc_max, val_pressure_max);
   PCF8583_write_byte(ds1307_temp_adc_max, val_temp_max);

   PCF8583_write_byte(ds1307_val_tg_air, val_tg_air);
   PCF8583_write_byte(ds1307_time_check_sensor, time_check_sensor);

   PCF8583_write_byte(ds1307_thu_test, thu_test);
   PCF8583_write_byte(ds1307_gio_test, gio_test);
   PCF8583_write_byte(ds1307_phut_test, phut_test);

   PCF8583_write_byte(ds1307_chu_ky_test, chu_ky_test);
   PCF8583_write_byte(ds1307_chu_ky_hien_tai, chu_ky_hien_tai);
   PCF8583_write_byte(ds1307_Control_input, Control_input);

   temp = volt_Protect_Accu * 10;
   PCF8583_write_byte(ds1307_volt_Protect_Accu, temp);

   //=======
   PCF8583_write_byte(ds1307_Hour_Save_From, gio_save_from);
   PCF8583_write_byte(ds1307_Min_Save_From, phut_save_from);
   PCF8583_write_byte(ds1307_Hour_Save_To, gio_save_to);
   PCF8583_write_byte(ds1307_Min_Save_To, phut_save_to);
   //=======
}

void write_data_ee(void)
{
   int temp = 0;

   wee(ee_counter_ac_fail, counter_ac_fail);
   wee(ee_error_code, error_code);
   // 16bit
   wee(ee_tong_gio_chay_mn, make8(tong_gio_chay_mn, 0));
   wee(ee_tong_gio_chay_mn + 1, make8(tong_gio_chay_mn, 1));

   wee(ee_tong_phut_chay_mn, tong_phut_chay_mn);
   wee(ee_energy_save, energy_save);
   wee(ee_level_set_ac_fail, level_set_ac_fail);
   // 16bit
   wee(ee_ac_vol_max, make8(ac_vol_max, 0));
   wee(ee_ac_vol_max + 1, make8(ac_vol_max, 1));

   wee(ee_ac_vol_min, ac_vol_min);
   wee(ee_val_tg_on_dinh_ac, val_tg_on_dinh_ac);
   wee(ee_mn_vol_max, mn_vol_max);
   wee(ee_mn_vol_min, mn_vol_min);
   wee(ee_val_counter_start, val_counter_start);
   wee(ee_val_tg_run_on, val_tg_run_on);
   wee(ee_val_tg_preheat, val_tg_preheat);
   wee(ee_val_tg_press_start, val_tg_press_start);
   wee(ee_val_tg_on_dinh_mn, val_tg_on_dinh_mn);
   wee(ee_val_tg_off_mn, val_tg_off_mn);
   wee(ee_val_tg_giainhiet, val_tg_giainhiet);
   wee(ee_en_temp_mn, en_temp_mn);
   wee(ee_en_pressure_mn, en_pressure_mn);
   wee(ee_val_timer_delay_run_mn, val_timer_delay_run_mn);
   wee(ee_style_mod_ac, style_mod_ac);
   wee(ee_flag_zero_delay_run_ac, flag_zero_delay_run_ac);
   wee(ee_flag_zero_delay_run_mn, flag_zero_delay_run_mn);
   wee(ee_val_tg_start_start, val_tg_start_start);

   wee(ee_val_counter_ac_fail, val_counter_ac_fail);
   wee(ee_val_counter_mn_fail, val_counter_mn_fail);
   wee(ee_val_tg_press_stop, val_tg_press_stop);

   wee(ee_en_temp_adc_mn, en_temp_mn_adc);
   wee(ee_en_pressure_adc_mn, en_pressure_mn_adc);

   wee(ee_list_resistor_pressure, list_dien_tro_ap_suat[0]);
   wee(ee_list_resistor_pressure + 1, list_dien_tro_ap_suat[1]);
   wee(ee_list_resistor_pressure + 2, list_dien_tro_ap_suat[2]);
   wee(ee_list_resistor_pressure + 3, list_dien_tro_ap_suat[3]);
   wee(ee_list_resistor_pressure + 4, list_dien_tro_ap_suat[4]);
   wee(ee_list_resistor_pressure + 5, list_dien_tro_ap_suat[5]);

   wee(ee_list_resistor_temp, list_dien_tro_nhiet_do[0]);
   wee(ee_list_resistor_temp + 1, list_dien_tro_nhiet_do[1]);
   wee(ee_list_resistor_temp + 2, list_dien_tro_nhiet_do[2]);
   wee(ee_list_resistor_temp + 3, list_dien_tro_nhiet_do[3]);
   wee(ee_list_resistor_temp + 4, list_dien_tro_nhiet_do[4]);
   wee(ee_list_resistor_temp + 5, list_dien_tro_nhiet_do[5]);
   wee(ee_list_resistor_temp + 6, list_dien_tro_nhiet_do[6]);
   wee(ee_list_resistor_temp + 7, list_dien_tro_nhiet_do[7]);
   wee(ee_list_resistor_temp + 8, list_dien_tro_nhiet_do[8]);
   wee(ee_list_resistor_temp + 9, list_dien_tro_nhiet_do[9]);
   wee(ee_list_resistor_temp + 10, list_dien_tro_nhiet_do[10]);

   wee(ee_pressure_adc_max, val_pressure_max);
   wee(ee_temp_adc_max, val_temp_max);

   wee(ee_val_tg_air, val_tg_air);
   wee(ee_time_check_sensor, time_check_sensor);

   wee(ee_thu_test, thu_test);
   wee(ee_gio_test, gio_test);
   wee(ee_phut_test, phut_test);

   wee(ee_chu_ky_test, chu_ky_test);
   wee(ee_chu_ky_hien_tai, chu_ky_hien_tai);
   wee(ee_Control_input, Control_input);

   temp = volt_Protect_Accu * 10;
   wee(ee_volt_Protect_Accu, temp);

   //=======
   wee(ee_Hour_Save_From, gio_save_from);
   wee(ee_Min_Save_From, phut_save_from);
   wee(ee_Hour_Save_To, gio_save_to);
   wee(ee_Min_Save_To, phut_save_to);
   //=======
}

void Hash_Full(void)
{
   Hash_Data = 0;

   Hash_Data = Hash_Data + val_tg_air; //*

   Hash_Data = Hash_Data + counter_ac_fail; //*

   Hash_Data = Hash_Data + error_code; //*

   Hash_Data = Hash_Data + tong_gio_chay_mn; //*

   Hash_Data = Hash_Data + tong_phut_chay_mn; //*

   Hash_Data = Hash_Data + val_counter_ac_fail; //*

   Hash_Data = Hash_Data + val_counter_mn_fail; //*

   Hash_Data = Hash_Data + energy_save; //*

   Hash_Data = Hash_Data + level_set_ac_fail; //*

   Hash_Data = Hash_Data + ac_vol_max; //*

   Hash_Data = Hash_Data + ac_vol_min; //*

   Hash_Data = Hash_Data + val_tg_on_dinh_ac; //*

   Hash_Data = Hash_Data + mn_vol_max; //*

   Hash_Data = Hash_Data + mn_vol_min; //*

   Hash_Data = Hash_Data + val_counter_start; //*

   Hash_Data = Hash_Data + val_tg_run_on; //*

   Hash_Data = Hash_Data + val_tg_preheat; //*

   Hash_Data = Hash_Data + val_tg_press_start; //*

   Hash_Data = Hash_Data + val_tg_on_dinh_mn; //*

   Hash_Data = Hash_Data + val_tg_off_mn; //*

   Hash_Data = Hash_Data + val_tg_giainhiet; //*

   Hash_Data = Hash_Data + en_temp_mn; //*

   Hash_Data = Hash_Data + en_pressure_mn; //*

   Hash_Data = Hash_Data + val_timer_delay_run_mn; //*

   Hash_Data = Hash_Data + style_mod_ac; //*

   Hash_Data = Hash_Data + flag_zero_delay_run_ac; //*

   Hash_Data = Hash_Data + flag_zero_delay_run_mn; //*

   Hash_Data = Hash_Data + val_tg_start_start; //*

   Hash_Data = Hash_Data + val_tg_press_stop; //*

   Hash_Data = Hash_Data + en_temp_mn_adc; //*

   Hash_Data = Hash_Data + en_pressure_mn_adc; //*

   Hash_Data = Hash_Data + list_dien_tro_ap_suat[0]; //*

   Hash_Data = Hash_Data + list_dien_tro_ap_suat[1]; //*

   Hash_Data = Hash_Data + list_dien_tro_ap_suat[2]; //*

   Hash_Data = Hash_Data + list_dien_tro_ap_suat[3]; //*

   Hash_Data = Hash_Data + list_dien_tro_ap_suat[4]; //*

   Hash_Data = Hash_Data + list_dien_tro_ap_suat[5]; //*

   Hash_Data = Hash_Data + list_dien_tro_nhiet_do[0]; //*

   Hash_Data = Hash_Data + list_dien_tro_nhiet_do[1]; //*

   Hash_Data = Hash_Data + list_dien_tro_nhiet_do[2]; //*

   Hash_Data = Hash_Data + list_dien_tro_nhiet_do[3]; //*

   Hash_Data = Hash_Data + list_dien_tro_nhiet_do[4]; //*

   Hash_Data = Hash_Data + list_dien_tro_nhiet_do[5]; //*

   Hash_Data = Hash_Data + list_dien_tro_nhiet_do[6]; //*

   Hash_Data = Hash_Data + list_dien_tro_nhiet_do[7]; //*

   Hash_Data = Hash_Data + list_dien_tro_nhiet_do[8]; //*

   Hash_Data = Hash_Data + list_dien_tro_nhiet_do[9]; //*

   Hash_Data = Hash_Data + list_dien_tro_nhiet_do[10]; //*

   Hash_Data = Hash_Data + val_pressure_max; //*

   Hash_Data = Hash_Data + val_temp_max; //*

   Hash_Data = Hash_Data + time_check_sensor; //*

   Hash_Data = Hash_Data + thu_test; //*

   Hash_Data = Hash_Data + gio_test; //*

   Hash_Data = Hash_Data + phut_test; //*

   Hash_Data = Hash_Data + chu_ky_test; //*

   Hash_Data = Hash_Data + chu_ky_hien_tai; //*

   Hash_Data = Hash_Data + Control_input; //*

   Hash_Data = Hash_Data + volt_Protect_Accu * 10; //*

   // long temp1=3107;
   Hash_Data = Hash_Data + Cert_Data;

   //==========
   Hash_Data = Hash_Data + gio_save_from;
   Hash_Data = Hash_Data + phut_save_from;
   Hash_Data = Hash_Data + gio_save_to;
   Hash_Data = Hash_Data + phut_save_to;
   //==========

   // 16bit
   PCF8583_write_byte(ds1307_Hash_Data, make8(Hash_Data, 0));
   PCF8583_write_byte(ds1307_Hash_Data + 1, make8(Hash_Data, 1));

   wee(ee_Hash_Data, make8(Hash_Data, 0));
   wee(ee_Hash_Data + 1, make8(Hash_Data, 1));

   // 16bit
   PCF8583_write_byte(ds1307_Cert_Data, make8(Cert_Data, 0));
   PCF8583_write_byte(ds1307_Cert_Data + 1, make8(Cert_Data, 1));

   wee(ee_Cert_Data, make8(Cert_Data, 0));
   wee(ee_Cert_Data + 1, make8(Cert_Data, 1));

   waitingData = 0;
}

//============================
void auto_run(void)
{
   val_progam = 0;

   temptest = (long)gio_test * 60 + (long)phut_test;
   tempnow = (long)gio_ht * 60 + (long)phut_ht;

   // long   tempfrom=0,tempto=0,tempnow=0;
   tempfrom = (long)gio_save_from * 60 + (long)phut_save_from;
   tempto = (long)gio_save_to * 60 + (long)phut_save_to;
   // tempnow    =   (long)gio_ht*60            +   (long)phut_ht;

   if (thu_test == thu_ht)
   {
      if (tempnow >= temptest && flag_switch == 0)
      {
         flag_switch = 1;

         if (++chu_ky_hien_tai >= chu_ky_test)
         {
            chu_ky_hien_tai = 0;
            val_test_mn = 1;
            tg_run_test = 240; // test trong 4 phut
         }
         waitingData = 1;
         // PCF8583_write_byte(ds1307_chu_ky_hien_tai,chu_ky_hien_tai);
         // wee(ee_chu_ky_hien_tai,chu_ky_hien_tai);
         // Hash_Full();
      }
   }
   else
      flag_switch = 0;

   if (val_test_mn == 1)
      val_progam = 0b10000000;

   if (ac_vol_fail == 0)
   { // co dien luoi
      switch (energy_save)
      {
      case 0: // cup dien chay luon
         timer_delay_run_mn = 0;
         break;
      case 1:                    // phong accu
         flag_do_phong_accu = 0; // cho phep do phong accu
         break;
      case 2: // tri hoan theo thoi gian dinh san
         timer_delay_run_mn = val_timer_delay_run_mn;
         break;

      case 3: // tri hoan theo khung gio
         if (tempnow >= tempfrom)
         { // che do tiet kiem nang luong
            timer_delay_run_mn = (24 * 60) - tempfrom + tempto;
         }
         else if (tempnow < tempto)
         {
            timer_delay_run_mn = tempto - tempnow;
         }
         else
         {
            timer_delay_run_mn = 0;
         }
         break;

      case 4: // tri hoan va khung gio
         if (tempnow >= tempfrom)
         { // che do tiet kiem nang luong
            timer_delay_run_mn = MAX((24 * 60) - tempfrom + tempto, val_timer_delay_run_mn);
         }
         else if (tempnow < tempto)
         {
            timer_delay_run_mn = MAX(tempto - tempnow, val_timer_delay_run_mn);
         }
         else
         {
            timer_delay_run_mn = val_timer_delay_run_mn;
         }
         break;
      }

      timer_delay_run_mn = timer_delay_run_mn * 60;

      // khi chuyen tu trang thai mat dien sang co dien thi cho phep chay thoi gian delay trong che do tiet kiem dau may no
      if (flag_zero_delay_run_mn == 0 || flag_zero_delay_run_mn > 1)
      {
         flag_zero_delay_run_mn = 1;
         waitingData = 1;
         // PCF8583_write_byte(ds1307_flag_zero_delay_run_mn,flag_zero_delay_run_mn);
         // wee(ee_flag_zero_delay_run_mn,flag_zero_delay_run_mn);
         // Hash_Full();
      }
   }

   if (ac_vol_fail == 1)
   { // mat dien moi xet cac gia tri nay
      // 1
      val_progam = val_progam | 0b01000000; // trang thai MAT dien luoi;
      flag_zero_delay_run_ac = 1;           // delay 2 phut truoc khi dong dien ac
      waitingData = 1;
      // PCF8583_write_byte(ds1307_flag_zero_delay_run_ac,flag_zero_delay_run_ac);
      // wee(ee_flag_zero_delay_run_ac,flag_zero_delay_run_ac);
      // Hash_Full();
      // 2
      switch (energy_save)
      {
      case 0: // cup dien chay luon
         val_progam = val_progam | 0b00110000;
         break;

      case 1:
         // Phong Accu
         val_progam = val_progam | 0b00100000;
         float adc_phong_accu = !flag_do_phong_accu ? get_adc_accu() : input_dc_low - delta_dc;
         if (adc_phong_accu <= DC_LOW_LVL_2)
         {
            output_high(OUT_ACCU_ERROR);
            flag_accu_error = 1;
         }
         if (adc_phong_accu <= input_dc_low - delta_dc)
         {
            val_progam = val_progam | 0b00010000;
            flag_do_phong_accu = 1;
            if (flag_zero_delay_run_mn >= 1)
            {
               flag_zero_delay_run_mn = 0;
               waitingData = 1;
            }
         }
         break;
      case 2: // tri hoan theo thoi gian dinh san
      case 3:
      case 4:
         val_progam = val_progam | 0b00100000;

         if (timer_delay_run_mn == 0)
         {
            val_progam = val_progam | 0b00010000;
            if (flag_zero_delay_run_mn >= 1)
            {
               flag_zero_delay_run_mn = 0;
               waitingData = 1;
               // PCF8583_write_byte(ds1307_flag_zero_delay_run_mn,flag_zero_delay_run_mn);
               // wee(ee_flag_zero_delay_run_mn,flag_zero_delay_run_mn);
               // Hash_Full();
            }
            // write_ram_ds1307();
         }
         break;
      }
   }

   if (remote_start)
   {
      val_progam = 0b10000001;
      //   switch(val_remote_start){
      //      default: //khong su dung

      //      break;

      //      case 1: //remote co tai
      //         val_progam = 0b10000001;
      //      break;
      //   }
   }

   // dem so lan mat dien
   if (ac_vol_fail == 0)
      back_ac_flag_fail = 0;
   if (back_ac_flag_fail != ac_vol_fail)
   {
      back_ac_flag_fail = ac_vol_fail;
      counter_ac_fail++;

      waitingData = 1;
   }

   /*
      //tu dong (0)
         //trang thái có dien (0)
         //trang thái mat dien (64)
            |-chay may phat (48)
            |-tri hoan thoi gian (32)
      //test may no (128)
         //trang thái có dien (0)
         //trang thái mat dien (64)
            |-chay may phat (48)
            |-tri hoan thoi gian (32)
      //remote start (129)

      //---------------tu dong----------------------
         0: //co dien luoi
         96: //tri hoan thoi gian
         112: //chay may no
      //---------------test may no------------------
         128: //test may no/dang co dien luoi
         224: //xoa chuong trinh test may no
         240: //xoa chuong trinh test may no
      //---------------remote start-----------------
         129: //remote start
   */
   // 0      {{"BINH THUONG"},
   // 1      {"K.DONG THAT BAI"},
   // 2      {"MAT NGUON"},
   // 3      {"D.AP QUA CAO"},
   // 4      {"D.AP QUA THAP"},
   // 5      {"AP XUAT NHOT"},
   // 6      {"N.DO QUA CAO"},

   if (val_progam_old != val_progam)
   {
      process_kdt_ac = 0;
      process_kdt_mn = 0;
      val_progam_old = val_progam;
      timer_backlight = 240;
   }

   // DIEN LUOI=======================================================================
   switch (val_progam)
   {
      //---------------tu dong----------------------
   case 0:   // co dien luoi
   case 128: // test may no/dang co dien luoi
      switch (process_kdt_ac)
      {
      case 0:
         process_kdt_ac = 1;

         tg_on_dinh_ac = val_tg_on_dinh_ac;
         if (flag_zero_delay_run_ac == 0)
            goto enable_out_cb_1;
         if (en_out_ac == 1)
            goto enable_out_cb_1;
         break;

      case 1:
         if (tg_on_dinh_ac == 0)
         {
            process_kdt_ac = 2;
            flag_zero_delay_run_ac = 0; // delay 2 phut truoc khi dong dien ac

            waitingData = 1;
         }
         break;

      case 2:
      enable_out_cb_1:
         process_kdt_ac = 2;
         en_out_ac = 1;
         break;
      }
      break;

   default:
      en_out_ac = 0;
      break;
   }

   // MAY NO=====================================================================================
   switch (val_progam)
   {
      //---------------tu dong----------------------
   case 0: // co dien luoi
      switch (process_kdt_mn)
      {
      default:
         if (mn_vol_fail == 0)
            process_kdt_mn = 1; // may nỏ đang chay
         if (mn_vol_fail == 1)
            process_kdt_mn = 3; // may nỏ khong chay

         tg_off_mn = val_tg_off_mn;
         tg_off_mn = tg_off_mn * 60;
         en_out_mn = 0;   // ngat khoi dong tu
         en_start_mn = 0; // tat may no
         en_stop_mn = 0;  // tat may no
         en_preheat_mn = 0;
         break;

      case 1: //
         if ((tg_off_mn == 0) || (mn_vol_fail == 1))
         {
            process_kdt_mn = 2;
            en_fuel_mn = 0; // nhat nhien lieu cap cho mn
            OUT_FUEL_MN_OFF();

            tg_press_stop = val_tg_press_stop;
            en_stop_mn = 1;
            OUT_STOP_MN_ON();
         }

         en_out_mn = 0;   // ngat khoi dong tu
         en_start_mn = 0; // tat may no
         en_preheat_mn = 0;
         break;

      case 2: // nhan stop may no
         if (tg_press_stop == 0)
         {                  // het thoi gian nhan nut
            en_stop_mn = 0; // tat may no
            OUT_STOP_MN_OFF();
            process_kdt_mn = 3;
         }
         break;

      case 3:             //
         en_out_mn = 0;   // ngat khoi dong tu
         en_start_mn = 0; // tat may no
         en_stop_mn = 0;  // tat may no
         en_preheat_mn = 0;
         en_fuel_mn = 0; // nhat nhien lieu cap cho mn
         en_air_mn = 0;
         break;
      }
      break;

   case 96: // tri hoan thoi gian
      en_out_mn = 0;
      en_start_mn = 0;
      en_fuel_mn = 0;  // nhien lieu cap cho mn
      en_start_mn = 0; // tat may no
      en_stop_mn = 0;  // tat may no
      en_preheat_mn = 0;
      en_air_mn = 0;

      if (adc_mn_2 > 50)
      { // dang co dien   //co nguon mn
         timer_delay_run_mn = 0;
      }

      if (flag_zero_delay_run_mn == 0)
      { // da chay het thoi gian delay tiet kiem dau mn
         timer_delay_run_mn = 0;
      }
      break;

   case 112: // chay may no
      switch (process_kdt_mn)
      {
      default:
         tg_run_on = val_tg_run_on;
         tg_phut_run_on = 0;

         counter_start = val_counter_start;

         timer_min_fail_mn = 0;
         timer_hour_fail_mn = 0;

         if (adc_mn_2 > 50)
         { // dang co dien
            if (en_out_mn == 0)
               process_kdt_mn = 1; // kiem tra 10s
            else
               process_kdt_mn = 3; // tiep tuc chay chuong trinh hien tai

            tg_on_dinh_mn = val_tg_on_dinh_mn;
            en_fuel_mn = 1;    // cap nguon tro lai truoc khi start lai may no
            en_start_mn = 0;   // tat may no
            en_stop_mn = 0;    // tat may no
            en_preheat_mn = 0; // khong kich suoi
            en_air_mn = 0;     // khong cap air
            counter_mn_fail = 0;
         }

         if (adc_mn_2 < 50)
         { // dang co dien
            process_kdt_mn = 4;
            en_fuel_mn = 0;    // tat nhien lieu cap cho mn
            en_start_mn = 0;   // tat may no
            en_stop_mn = 0;    // tat may no
            en_preheat_mn = 0; // khong kich suoi
            en_air_mn = 0;     // khong cap air
         }
         break;

      case 1:               // kiêm tra dien ap may no có tren 50v!
         en_fuel_mn = 1;    // cap nguon tro lai
         en_start_mn = 0;   // tat may no
         en_stop_mn = 0;    // tat may no
         en_preheat_mn = 0; // khong kich suoi
         en_air_mn = 0;     // khong cap air

         if (tg_on_dinh_mn < (val_tg_on_dinh_mn - time_check_sensor))
            process_kdt_mn = 2; // may nỏ đang chay

         if (adc_mn_2 < 50)
         {                     // may no khong ra nguon
            en_fuel_mn = 0;    // tat nhien lieu cap cho mn
            en_start_mn = 0;   // tat may no
            en_stop_mn = 1;    // tat may no
            tg_press_stop = 5; //
            en_preheat_mn = 0; // khong kich suoi
            en_air_mn = 0;     // khong cap air

            mn_vol_fail = 1;
            counter_mn_fail = 5;
            switch (counter_start)
            {
            default:
               process_kdt_mn = 8;                  // may nỏ chưa chay
               tg_start_start = val_tg_start_start; // nap thoi gian start<->start
               break;

            case 0:
               process_kdt_mn = 9; // het so lan khoi dong
               error_code = 1;
               waitingData = 1;
               // PCF8583_write_byte(ds1307_error_code,error_code);
               // wee(ee_error_code,error_code);
               // Hash_Full();
               // write_ram_ds1307();
               en_led_fail_mn = 1;
               break;
            }
         }
         break;

      case 2: // kiem tra dien ap may no co nằm trong ngưởng cho phep
         en_out_mn = 0;
         en_fuel_mn = 1;    // nhien lieu cap cho mn
         en_start_mn = 0;   // tat may no
         en_stop_mn = 0;    // tat may no
         en_preheat_mn = 0; // khong kich suoi
         en_air_mn = 0;

         if (tg_on_dinh_mn == 0)
            process_kdt_mn = 3;

         if (fail_pressure_mn == 1 || fail_pressure_mn_adc == 1)
         {
            process_kdt_mn = 15;
            en_fuel_mn = 0;
            OUT_FUEL_MN_OFF();
            tg_press_stop = 5;
            en_stop_mn = 1;
            OUT_STOP_MN_ON();
            error_code = 5;

            waitingData = 1;
         }

         if (fail_temp_mn == 1 || fail_temp_mn_adc == 1)
         {
            process_kdt_mn = 16;
            en_fuel_mn = 0;
            OUT_FUEL_MN_OFF();
            tg_press_stop = 5;
            en_stop_mn = 1;
            OUT_STOP_MN_ON();
            error_code = 6;

            waitingData = 1;
         }

         if (fail_ChargeDC == 1)
         {
            process_kdt_mn = 19; // sac qua cao
            en_fuel_mn = 0;
            OUT_FUEL_MN_OFF();
            tg_press_stop = 5;
            en_stop_mn = 1;
            OUT_STOP_MN_ON();
            error_code = 7;

            waitingData = 1;
         }

         if (mn_vol_fail == 1)
         { // mat nguon   / kiem tra roi vao trang thai gi
            if (adc_mn_2 > mn_vol_max)
               process_kdt_mn = 18, error_code = 3;
            ; // qua ap
            if ((adc_mn_2 > 50) && (adc_mn_2 < mn_vol_min))
               process_kdt_mn = 17, error_code = 4;
            ; // duoi ap
            if (adc_mn_2 < 50)
               process_kdt_mn = 14, error_code = 2;
            ; // khong ra nguon

            waitingData = 1;

            en_fuel_mn = 0;
            OUT_FUEL_MN_OFF();
            tg_press_stop = 5;
            en_stop_mn = 1;
            OUT_STOP_MN_ON();
         }
         break;

      case 3:           // chay đên khi het thoi gian cai dat
         en_out_mn = 1; // dong khoi dong tu cap NGUONG cho dai
         if (tg_run_on == 0 && tg_phut_run_on == 0)
         {
            process_kdt_mn = 10;    // nghi de lam mat may nổ
            en_out_mn = 0;          //
            flag_do_phong_accu = 0; // cho phep do phong accu
         }
         //==============
         switch (energy_save)
         {
         case 0: // cup dien chay luon
         case 1: // phong accu
         case 2: // tri hoan theo thoi gian dinh san
            break;

         case 3: // tri hoan theo khung gio
         case 4: // tri hoan va khung gio
            if (tempnow >= tempfrom)
            { // che do tiet kiem nang luong
               timer_save_oil_mn = (24 * 60) - tempfrom + tempto;
               process_kdt_mn = 20; // nghi de lam mat may nổ
               en_out_mn = 0;       //
            }
            else if (tempnow < tempto)
            {
               timer_save_oil_mn = tempto - tempnow;
               process_kdt_mn = 20; // nghi de lam mat may nổ
               en_out_mn = 0;       //
            }
            else
            {
               timer_save_oil_mn = 0;
               en_out_mn = 1; // dong khoi dong tu cap NGUONG cho dai
            }
            timer_save_oil_mn = timer_save_oil_mn * 60;
            break;
         }
         //==============

         // may nỏ bi mat nguon, tat may luon
         if (mn_vol_fail == 1)
         {
            if (adc_mn_2 > mn_vol_max)
               process_kdt_mn = 18, error_code = 3; // qua ap
            if ((adc_mn_2 > 50) && (adc_mn_2 < mn_vol_min))
               process_kdt_mn = 17, error_code = 4; // duoi ap
            if (adc_mn_2 < 50)
               process_kdt_mn = 14, error_code = 2; // khong ra nguon

            // PCF8583_write_byte(ds1307_error_code,error_code);
            // wee(ee_error_code,error_code);
            // Hash_Full();
            waitingData = 1;

            en_out_mn = 0;     // ngat tai ra
            en_fuel_mn = 0;    // nhien lieu cap cho mn
            en_start_mn = 0;   // tat may no
            en_stop_mn = 1;    // tat may no
            en_preheat_mn = 0; // khong kich suoi
            tg_press_stop = 5;
            en_led_fail_mn = 1; // bao fail may no
         }

         if (fail_pressure_mn == 1 || fail_pressure_mn_adc == 1)
         {
            process_kdt_mn = 15;
            en_fuel_mn = 0;
            OUT_FUEL_MN_OFF();
            tg_press_stop = 5;
            en_stop_mn = 1;
            OUT_STOP_MN_ON();
            error_code = 5;

            waitingData = 1;
            // PCF8583_write_byte(ds1307_error_code,error_code);
            // wee(ee_error_code,error_code);
            // Hash_Full();
         }

         if (fail_temp_mn == 1 || fail_temp_mn_adc == 1)
         {
            process_kdt_mn = 16;
            en_fuel_mn = 0;
            OUT_FUEL_MN_OFF();
            tg_press_stop = 5;
            en_stop_mn = 1;
            OUT_STOP_MN_ON();
            error_code = 6;
            waitingData = 1;
            // PCF8583_write_byte(ds1307_error_code,error_code);
            // wee(ee_error_code,error_code);
            // Hash_Full();
         }

         if (fail_ChargeDC == 1)
         {
            process_kdt_mn = 19; // sac qua cao
            en_fuel_mn = 0;
            OUT_FUEL_MN_OFF();
            tg_press_stop = 5;
            en_stop_mn = 1;
            OUT_STOP_MN_ON();
            error_code = 7;

            waitingData = 1;
            // PCF8583_write_byte(ds1307_error_code,error_code);
            // wee(ee_error_code,error_code);
            // Hash_Full();
         }
         break;

      //==============================================================================
      case 4: // suoi may no
         process_kdt_mn = 5;
         en_out_mn = 0;
         en_fuel_mn = 1;    // nhien lieu cap cho mn
         en_preheat_mn = 1; // suoi nong may no
         en_stop_mn = 0;    // tat may no
         en_air_mn = 0;     // khong cap air

         tg_preheat = val_tg_preheat; // thoi gian suoi may

      case 5: // ket thuc suoi may no
         if (tg_preheat == 0)
         {
            process_kdt_mn = 6;
            en_preheat_mn = 0; // ngat suoi
         }

         if (adc_mn_2 > 50)
         {
            process_kdt_mn = 1;
            en_preheat_mn = 0; // suoi nong may no
            en_start_mn = 0;   // tat may no
            en_stop_mn = 0;    // tat may no
            en_air_mn = 0;     // khong cap air

            mn_vol_fail = 0;
            counter_mn_fail = 0;
            // kiem tra gia tri
            tg_on_dinh_mn = val_tg_on_dinh_mn;
         }
         break;

      case 6:             // khoi dong may no
         en_start_mn = 1; // nhan start
         en_air_mn = 1;   // on air
         tg_press_start = val_tg_press_start;
         tg_air = val_tg_air;
         counter_start--; // moi lan nhan start tru bot di 1
         process_kdt_mn = 7;

      case 7: // nha start khi co nguon hoac het thoi gian
         if (tg_air == 0)
         {
            en_air_mn = 0; // khong cap air
            OUT_AIR_MN_OFF();
         }

         if (tg_press_start == 0)
         {
            en_preheat_mn = 0; // khong kich suoi
            en_air_mn = 0;     // khong cap air
            en_start_mn = 0;   // khong nhan start, may no chua chay
            OUT_START_MN_OFF();
            en_fuel_mn = 0;
            OUT_FUEL_MN_OFF();

            tg_press_stop = 5;
            en_stop_mn = 1;
            OUT_STOP_MN_ON();

            switch (counter_start)
            {
            default:
               process_kdt_mn = 8;                  // may nỏ chưa chay
               tg_start_start = val_tg_start_start; // nap thoi gian start<->start
               break;

            case 0:
               process_kdt_mn = 9; // het so lan khoi dong
               error_code = 1;

               // PCF8583_write_byte(ds1307_error_code,error_code);
               // wee(ee_error_code,error_code);
               // Hash_Full();
               waitingData = 1;
               en_led_fail_mn = 1;
               break;
            }
         }

         if (adc_mn_2 > 50)
         {
            process_kdt_mn = 1;
            en_preheat_mn = 0; // suoi nong may no
            en_start_mn = 0;
            OUT_START_MN_OFF();
            en_air_mn = 0;
            OUT_AIR_MN_OFF();
            mn_vol_fail = 0;
            counter_mn_fail = 0;
            // kiem tra gia tri
            tg_on_dinh_mn = val_tg_on_dinh_mn;
         }
         break;

      case 8: // trì hoản trước khi nhan lại start
         // quay lai khoi dong may no
         if (tg_start_start == 0)
            process_kdt_mn = 6;
         // cap nguon tro lai truoc khi start lai may no
         if (tg_start_start <= val_tg_preheat)
         {
            en_fuel_mn = 1;
         }

         if (tg_press_stop == 0)
         { // tat may no bang nut stop
            en_stop_mn = 0;
            OUT_STOP_MN_OFF();
         }

         if (adc_mn_2 > 50)
         {
            process_kdt_mn = 1;
            en_preheat_mn = 0; // suoi nong may no
            en_start_mn = 0;
            OUT_START_MN_OFF();
            en_air_mn = 0;
            OUT_AIR_MN_OFF();
            mn_vol_fail = 0;
            counter_mn_fail = 0;
            // kiem tra gia tri
            tg_on_dinh_mn = val_tg_on_dinh_mn;
         }
         break;

      case 9: // may no fail, khoi dong that bai
         en_start_mn = 0;
         en_fuel_mn = 0; // nhien lieu cap cho mn
         en_air_mn = 0;
         en_preheat_mn = 0; // suoi nong may no

         if (tg_press_stop == 0)
         { // tat may no bang nut stop
            en_stop_mn = 0;
            OUT_STOP_MN_OFF();
         }

         if (adc_mn_2 > 50)
         {
            process_kdt_mn = 1;
            en_preheat_mn = 0; // suoi nong may no
            en_start_mn = 0;
            en_air_mn = 0;
            mn_vol_fail = 0;
            counter_mn_fail = 0;
            // kiem tra gia tri
            tg_on_dinh_mn = val_tg_on_dinh_mn;
         }
         break;

      case 10: // het thoi gian chay/ lam mat roi ngat may no
         process_kdt_mn = 11;
         tg_off_mn = val_tg_off_mn;
         tg_off_mn = tg_off_mn * 60;
         en_out_mn = 0;

      case 11:
         if (tg_off_mn == 0)
         { // het thoi gian lam mat
            process_kdt_mn = 12;
            en_out_mn = 0;
            en_fuel_mn = 0;  // nhien lieu cap cho mn
            en_start_mn = 0; // tat may no

            tg_press_stop = val_tg_press_stop;
            en_stop_mn = 1;
            OUT_STOP_MN_ON();

            en_fuel_mn = 0; // nhien lieu cap cho mn
            OUT_FUEL_MN_OFF();
         }

         en_out_mn = 0;
         tg_giainhiet = val_tg_giainhiet;
         break;

      case 12:
         if (tg_press_stop == 0)
         {
            en_stop_mn = 0; // tat may no
            OUT_STOP_MN_OFF();
            en_air_mn = 0;
            OUT_AIR_MN_OFF();
            process_kdt_mn = 13;
         }

         if (adc_mn_2 < 50)
         {                  // mat nguon mn roi
            en_stop_mn = 0; // tat may no
            OUT_STOP_MN_OFF();

            en_air_mn = 0;
            OUT_AIR_MN_OFF();
            process_kdt_mn = 13;
         }
         break;

      case 13:
         if (tg_giainhiet == 0)
            process_kdt_mn = 0;
         en_out_mn = 0;
         en_fuel_mn = 0;  // nhien lieu cap cho mn
         en_start_mn = 0; // tat may no
         en_stop_mn = 0;  // tat may no
         en_preheat_mn = 0;
         en_air_mn = 0;
         break;

      case 14: // MAY NO MAT NGUON
      case 15: // thieu ap luc nhot
      case 16: // nhiet do nuoc qua cao
      case 17: // may no ra dien ap thap
      case 18: // may no ra dien qua ap
      case 19: // may no sac accu qua cao
         if (tg_press_stop == 0)
         {
            en_stop_mn = 0; // tat may no
            OUT_STOP_MN_OFF();
            en_air_mn = 0;
            OUT_AIR_MN_OFF();
         }

         en_out_mn = 0;
         en_fuel_mn = 0;  // nhien lieu cap cho mn
         en_start_mn = 0; // tat may no
         en_preheat_mn = 0;
         break;

         //=======================
      case 20: // het thoi gian chay/ lam mat roi ngat may no
         process_kdt_mn = 21;
         tg_off_mn = val_tg_off_mn;
         tg_off_mn = tg_off_mn * 60;
         en_out_mn = 0;

      case 21:
         if (tg_off_mn == 0)
         { // het thoi gian lam mat
            process_kdt_mn = 22;
            en_out_mn = 0;
            en_fuel_mn = 0;  // nhien lieu cap cho mn
            en_start_mn = 0; // tat may no

            tg_press_stop = val_tg_press_stop;
            en_stop_mn = 1;
            OUT_STOP_MN_ON();

            en_fuel_mn = 0; // nhien lieu cap cho mn
            OUT_FUEL_MN_OFF();
         }

         en_out_mn = 0;
         break;

      case 22:
         if (tg_press_stop == 0)
         {
            en_stop_mn = 0; // tat may no
            OUT_STOP_MN_OFF();
            en_air_mn = 0;
            OUT_AIR_MN_OFF();
            process_kdt_mn = 23;
         }

         if (adc_mn_2 < 50)
         {                  // mat nguon mn roi
            en_stop_mn = 0; // tat may no
            OUT_STOP_MN_OFF();

            en_air_mn = 0;
            OUT_AIR_MN_OFF();
            process_kdt_mn = 23;
         }
         break;

      case 23:
         //==============
         switch (energy_save)
         {
         case 0: // cup dien chay luon
         case 1: // phong accu
         case 2: // tri hoan theo thoi gian dinh san
            process_kdt_mn = 0;
            break;

         case 3: // tri hoan theo khung gio
         case 4: // tri hoan va khung gio
            if (timer_save_oil_mn == 0)
            { // che do tiet kiem nang luong
               process_kdt_mn = 0;
            }
            if (tempnow < tempfrom && tempnow > tempto)
            { // che do tiet kiem nang luong
               process_kdt_mn = 0;
            }
            break;
         }
         //==============

         en_out_mn = 0;
         en_fuel_mn = 0;  // nhien lieu cap cho mn
         en_start_mn = 0; // tat may no
         en_stop_mn = 0;  // tat may no
         en_preheat_mn = 0;
         en_air_mn = 0;
         break;
      }
      break;

      //---------------remote start-----------------
   case 129: // remote start
      switch (process_kdt_mn)
      {
      default:
         tg_run_on = val_tg_run_on;
         tg_phut_run_on = 0;

         counter_start = val_counter_start;

         timer_min_fail_mn = 0;
         timer_hour_fail_mn = 0;

         if (adc_mn_2 > 50)
         { // dang co dien
            if (en_out_mn == 0)
               process_kdt_mn = 1; // kiem tra 10s
            else
               process_kdt_mn = 3; // tiep tuc chay chuong trinh hien tai

            tg_on_dinh_mn = val_tg_on_dinh_mn;
            en_fuel_mn = 1;    // cap nguon tro lai truoc khi start lai may no
            en_start_mn = 0;   // tat may no
            en_stop_mn = 0;    // tat may no
            en_preheat_mn = 0; // khong kich suoi
            en_air_mn = 0;     // khong cap air
            counter_mn_fail = 0;
         }

         if (adc_mn_2 < 50)
         { // dang co dien
            process_kdt_mn = 4;
            en_fuel_mn = 0;    // tat nhien lieu cap cho mn
            en_start_mn = 0;   // tat may no
            en_stop_mn = 0;    // tat may no
            en_preheat_mn = 0; // khong kich suoi
            en_air_mn = 0;     // khong cap air
         }
         break;

      case 1:               // kiêm tra dien ap may no có tren 50v!
         en_fuel_mn = 1;    // cap nguon tro lai
         en_start_mn = 0;   // tat may no
         en_stop_mn = 0;    // tat may no
         en_preheat_mn = 0; // khong kich suoi
         en_air_mn = 0;     // khong cap air

         if (tg_on_dinh_mn < (val_tg_on_dinh_mn - time_check_sensor))
            process_kdt_mn = 2; // may nỏ đang chay

         if (adc_mn_2 < 50)
         {                     // may no khong ra nguon
            en_fuel_mn = 0;    // tat nhien lieu cap cho mn
            en_start_mn = 0;   // tat may no
            en_stop_mn = 1;    // tat may no
            tg_press_stop = 5; //
            en_preheat_mn = 0; // khong kich suoi
            en_air_mn = 0;     // khong cap air

            mn_vol_fail = 1;
            counter_mn_fail = 5;
            switch (counter_start)
            {
            default:
               process_kdt_mn = 8;                  // may nỏ chưa chay
               tg_start_start = val_tg_start_start; // nap thoi gian start<->start
               break;

            case 0:
               process_kdt_mn = 9; // het so lan khoi dong
               error_code = 1;
               waitingData = 1;
               // PCF8583_write_byte(ds1307_error_code,error_code);
               // wee(ee_error_code,error_code);
               // Hash_Full();
               // write_ram_ds1307();
               en_led_fail_mn = 1;
               break;
            }
         }
         break;

      case 2: // kiem tra dien ap may no co nằm trong ngưởng cho phep
         en_out_mn = 0;
         en_fuel_mn = 1;    // nhien lieu cap cho mn
         en_start_mn = 0;   // tat may no
         en_stop_mn = 0;    // tat may no
         en_preheat_mn = 0; // khong kich suoi
         en_air_mn = 0;

         if (tg_on_dinh_mn == 0)
            process_kdt_mn = 3;

         if (fail_pressure_mn == 1 || fail_pressure_mn_adc == 1)
         {
            process_kdt_mn = 15;
            en_fuel_mn = 0;
            OUT_FUEL_MN_OFF();
            tg_press_stop = 5;
            en_stop_mn = 1;
            OUT_STOP_MN_ON();
            error_code = 5;

            waitingData = 1;
            // PCF8583_write_byte(ds1307_error_code,error_code);
            // wee(ee_error_code,error_code);
            // Hash_Full();
         }

         if (fail_temp_mn == 1 || fail_temp_mn_adc == 1)
         {
            process_kdt_mn = 16;
            en_fuel_mn = 0;
            OUT_FUEL_MN_OFF();
            tg_press_stop = 5;
            en_stop_mn = 1;
            OUT_STOP_MN_ON();
            error_code = 6;

            waitingData = 1;
            // PCF8583_write_byte(ds1307_error_code,error_code);
            // wee(ee_error_code,error_code);
            // Hash_Full();
         }

         if (fail_ChargeDC == 1)
         {
            process_kdt_mn = 19; // sac qua cao
            en_fuel_mn = 0;
            OUT_FUEL_MN_OFF();
            tg_press_stop = 5;
            en_stop_mn = 1;
            OUT_STOP_MN_ON();
            error_code = 7;

            waitingData = 1;
            // Hash_Full();

            // PCF8583_write_byte(ds1307_error_code,error_code);
            // wee(ee_error_code,error_code);
         }

         if (mn_vol_fail == 1)
         { // mat nguon   / kiem tra roi vao trang thai gi
            if (adc_mn_2 > mn_vol_max)
               process_kdt_mn = 18, error_code = 3;
            ; // qua ap
            if ((adc_mn_2 > 50) && (adc_mn_2 < mn_vol_min))
               process_kdt_mn = 17, error_code = 4;
            ; // duoi ap
            if (adc_mn_2 < 50)
               process_kdt_mn = 14, error_code = 2;
            ; // khong ra nguon

            waitingData = 1;
            // PCF8583_write_byte(ds1307_error_code,error_code);
            // wee(ee_error_code,error_code);
            // Hash_Full();

            en_fuel_mn = 0;
            OUT_FUEL_MN_OFF();
            tg_press_stop = 5;
            en_stop_mn = 1;
            OUT_STOP_MN_ON();
         }
         break;

      case 3:           // chay đên khi het thoi gian cai dat
         en_out_mn = 1; // dong khoi dong tu cap NGUONG cho dai
         if (tg_run_on == 0 && tg_phut_run_on == 0)
         {
            process_kdt_mn = 10; // nghi de lam mat may nổ
            en_out_mn = 0;       //
         }

         // may nỏ bi mat nguon, tat may luon
         if (mn_vol_fail == 1)
         {
            if (adc_mn_2 > mn_vol_max)
               process_kdt_mn = 18, error_code = 3; // qua ap
            if ((adc_mn_2 > 50) && (adc_mn_2 < mn_vol_min))
               process_kdt_mn = 17, error_code = 4; // duoi ap
            if (adc_mn_2 < 50)
               process_kdt_mn = 14, error_code = 2; // khong ra nguon

            // PCF8583_write_byte(ds1307_error_code,error_code);
            // wee(ee_error_code,error_code);
            // Hash_Full();
            waitingData = 1;

            en_out_mn = 0;     // ngat tai ra
            en_fuel_mn = 0;    // nhien lieu cap cho mn
            en_start_mn = 0;   // tat may no
            en_stop_mn = 1;    // tat may no
            en_preheat_mn = 0; // khong kich suoi
            tg_press_stop = 5;
            en_led_fail_mn = 1; // bao fail may no
         }

         if (fail_pressure_mn == 1 || fail_pressure_mn_adc == 1)
         {
            process_kdt_mn = 15;
            en_fuel_mn = 0;
            OUT_FUEL_MN_OFF();
            tg_press_stop = 5;
            en_stop_mn = 1;
            OUT_STOP_MN_ON();
            error_code = 5;

            waitingData = 1;
            // PCF8583_write_byte(ds1307_error_code,error_code);
            // wee(ee_error_code,error_code);
            // Hash_Full();
         }

         if (fail_temp_mn == 1 || fail_temp_mn_adc == 1)
         {
            process_kdt_mn = 16;
            en_fuel_mn = 0;
            OUT_FUEL_MN_OFF();
            tg_press_stop = 5;
            en_stop_mn = 1;
            OUT_STOP_MN_ON();
            error_code = 6;
            waitingData = 1;
            // PCF8583_write_byte(ds1307_error_code,error_code);
            // wee(ee_error_code,error_code);
            // Hash_Full();
         }

         if (fail_ChargeDC == 1)
         {
            process_kdt_mn = 19; // sac qua cao
            en_fuel_mn = 0;
            OUT_FUEL_MN_OFF();
            tg_press_stop = 5;
            en_stop_mn = 1;
            OUT_STOP_MN_ON();
            error_code = 7;

            waitingData = 1;
            // PCF8583_write_byte(ds1307_error_code,error_code);
            // wee(ee_error_code,error_code);
            // Hash_Full();
         }
         break;

      //==============================================================================
      case 4: // suoi may no
         process_kdt_mn = 5;
         en_out_mn = 0;
         en_fuel_mn = 1;    // nhien lieu cap cho mn
         en_preheat_mn = 1; // suoi nong may no
         en_stop_mn = 0;    // tat may no
         en_air_mn = 0;     // khong cap air

         tg_preheat = val_tg_preheat; // thoi gian suoi may

      case 5: // ket thuc suoi may no
         if (tg_preheat == 0)
         {
            process_kdt_mn = 6;
            en_preheat_mn = 0; // ngat suoi
         }

         if (adc_mn_2 > 50)
         {
            process_kdt_mn = 1;
            en_preheat_mn = 0; // suoi nong may no
            en_start_mn = 0;   // tat may no
            en_stop_mn = 0;    // tat may no
            en_air_mn = 0;     // khong cap air

            mn_vol_fail = 0;
            counter_mn_fail = 0;
            // kiem tra gia tri
            tg_on_dinh_mn = val_tg_on_dinh_mn;
         }
         break;

      case 6:             // khoi dong may no
         en_start_mn = 1; // nhan start
         en_air_mn = 1;   // on air
         tg_press_start = val_tg_press_start;
         tg_air = val_tg_air;
         counter_start--; // moi lan nhan start tru bot di 1
         process_kdt_mn = 7;

      case 7: // nha start khi co nguon hoac het thoi gian
         if (tg_air == 0)
         {
            en_air_mn = 0; // khong cap air
            OUT_AIR_MN_OFF();
         }

         if (tg_press_start == 0)
         {
            en_preheat_mn = 0; // khong kich suoi
            en_air_mn = 0;     // khong cap air
            en_start_mn = 0;   // khong nhan start, may no chua chay
            OUT_START_MN_OFF();
            en_fuel_mn = 0;
            OUT_FUEL_MN_OFF();

            tg_press_stop = 5;
            en_stop_mn = 1;
            OUT_STOP_MN_ON();

            switch (counter_start)
            {
            default:
               process_kdt_mn = 8;                  // may nỏ chưa chay
               tg_start_start = val_tg_start_start; // nap thoi gian start<->start
               break;

            case 0:
               process_kdt_mn = 9; // het so lan khoi dong
               error_code = 1;

               // PCF8583_write_byte(ds1307_error_code,error_code);
               // wee(ee_error_code,error_code);
               // Hash_Full();
               waitingData = 1;
               en_led_fail_mn = 1;
               break;
            }
         }

         if (adc_mn_2 > 50)
         {
            process_kdt_mn = 1;
            en_preheat_mn = 0; // suoi nong may no
            en_start_mn = 0;
            OUT_START_MN_OFF();
            en_air_mn = 0;
            OUT_AIR_MN_OFF();
            mn_vol_fail = 0;
            counter_mn_fail = 0;
            // kiem tra gia tri
            tg_on_dinh_mn = val_tg_on_dinh_mn;
         }
         break;

      case 8: // trì hoản trước khi nhan lại start
         // quay lai khoi dong may no
         if (tg_start_start == 0)
            process_kdt_mn = 6;
         // cap nguon tro lai truoc khi start lai may no
         if (tg_start_start <= val_tg_preheat)
         {
            en_fuel_mn = 1;
         }

         if (tg_press_stop == 0)
         { // tat may no bang nut stop
            en_stop_mn = 0;
            OUT_STOP_MN_OFF();
         }

         if (adc_mn_2 > 50)
         {
            process_kdt_mn = 1;
            en_preheat_mn = 0; // suoi nong may no
            en_start_mn = 0;
            OUT_START_MN_OFF();
            en_air_mn = 0;
            OUT_AIR_MN_OFF();
            mn_vol_fail = 0;
            counter_mn_fail = 0;
            // kiem tra gia tri
            tg_on_dinh_mn = val_tg_on_dinh_mn;
         }
         break;

      case 9: // may no fail, khoi dong that bai
         en_start_mn = 0;
         en_fuel_mn = 0; // nhien lieu cap cho mn
         en_air_mn = 0;
         en_preheat_mn = 0; // suoi nong may no

         if (tg_press_stop == 0)
         { // tat may no bang nut stop
            en_stop_mn = 0;
            OUT_STOP_MN_OFF();
         }

         if (adc_mn_2 > 50)
         {
            process_kdt_mn = 1;
            en_preheat_mn = 0; // suoi nong may no
            en_start_mn = 0;
            en_air_mn = 0;
            mn_vol_fail = 0;
            counter_mn_fail = 0;
            // kiem tra gia tri
            tg_on_dinh_mn = val_tg_on_dinh_mn;
         }
         break;

      case 10: // het thoi gian chay/ lam mat roi ngat may no
         process_kdt_mn = 11;
         tg_off_mn = val_tg_off_mn;
         tg_off_mn = tg_off_mn * 60;
         en_out_mn = 0;

      case 11:
         if (tg_off_mn == 0)
         { // het thoi gian lam mat
            process_kdt_mn = 12;
            en_out_mn = 0;
            en_fuel_mn = 0;  // nhien lieu cap cho mn
            en_start_mn = 0; // tat may no

            tg_press_stop = val_tg_press_stop;
            en_stop_mn = 1;
            OUT_STOP_MN_ON();

            en_fuel_mn = 0; // nhien lieu cap cho mn
            OUT_FUEL_MN_OFF();
         }

         en_out_mn = 0;
         tg_giainhiet = val_tg_giainhiet;
         break;

      case 12:
         if (tg_press_stop == 0)
         {
            en_stop_mn = 0; // tat may no
            OUT_STOP_MN_OFF();
            en_air_mn = 0;
            OUT_AIR_MN_OFF();
            process_kdt_mn = 13;
         }

         if (adc_mn_2 < 50)
         {                  // mat nguon mn roi
            en_stop_mn = 0; // tat may no
            OUT_STOP_MN_OFF();

            en_air_mn = 0;
            OUT_AIR_MN_OFF();
            process_kdt_mn = 13;
         }
         break;

      case 13:
         if (tg_giainhiet == 0)
            process_kdt_mn = 0;

         en_out_mn = 0;
         en_fuel_mn = 0;  // nhien lieu cap cho mn
         en_start_mn = 0; // tat may no
         en_stop_mn = 0;  // tat may no
         en_preheat_mn = 0;
         en_air_mn = 0;
         break;

      case 14: // MAY NO MAT NGUON
      case 15: // thieu ap luc nhot
      case 16: // nhiet do nuoc qua cao
      case 17: // may no ra dien ap thap
      case 18: // may no ra dien qua ap
      case 19: // may no sac accu qua cao
         if (tg_press_stop == 0)
         {
            en_stop_mn = 0; // tat may no
            OUT_STOP_MN_OFF();
            en_air_mn = 0;
            OUT_AIR_MN_OFF();
         }

         en_out_mn = 0;
         en_fuel_mn = 0;  // nhien lieu cap cho mn
         en_start_mn = 0; // tat may no
         en_preheat_mn = 0;
         break;
      }
      break;
      //---------------test may no------------------
   case 128: // test may no/dang co dien luoi
      switch (process_kdt_mn)
      {
      default:
         en_out_mn = 0;
         // kiem tra gia tri
         counter_start = val_counter_start;

         if (adc_mn_2 > 50)
         {                      // dang co dien
            process_kdt_mn = 1; // kiem tra 10s
            tg_on_dinh_mn = val_tg_on_dinh_mn;
            en_fuel_mn = 1;    // cap nguon tro lai truoc khi start lai may no
            en_start_mn = 0;   // tat may no
            en_stop_mn = 0;    // tat may no
            en_preheat_mn = 0; // khong kich suoi
            en_air_mn = 0;     // khong cap air
            counter_mn_fail = 0;
         }

         if (adc_mn_2 < 50)
         {                      // may no khong co dien
            process_kdt_mn = 4; // start may no
            en_fuel_mn = 0;     // tat nhien lieu cap cho mn
            en_start_mn = 0;    // tat may no
            en_stop_mn = 0;     // tat may no
            en_preheat_mn = 0;  // khong kich suoi
            en_air_mn = 0;      // khong cap air
         }
         break;

      case 1:               // kiêm tra dien ap may no có tren 50v!
         en_fuel_mn = 1;    // cap nguon tro lai
         en_start_mn = 0;   // tat may no
         en_stop_mn = 0;    // tat may no
         en_preheat_mn = 0; // khong kich suoi
         en_air_mn = 0;     // khong cap air

         if (tg_on_dinh_mn < (val_tg_on_dinh_mn - time_check_sensor))
            process_kdt_mn = 2; // may nỏ đang chay

         if (adc_mn_2 < 50)
         {                  // may no khong ra nguon
            en_fuel_mn = 0; // tat nhien lieu cap cho mn
            OUT_FUEL_MN_OFF();
            en_start_mn = 0;   // tat may no
            en_stop_mn = 1;    // tat may no
            tg_press_stop = 5; //
            en_preheat_mn = 0; // khong kich suoi
            en_air_mn = 0;     // khong cap air

            mn_vol_fail = 1;
            counter_mn_fail = 1;
            switch (counter_start)
            {
            default:
               process_kdt_mn = 8;                  // may nỏ chưa chay
               tg_start_start = val_tg_start_start; // nap thoi gian start<->start
               break;

            case 0:
               process_kdt_mn = 9; // het so lan khoi dong
               error_code = 1;

               // PCF8583_write_byte(ds1307_error_code,error_code);
               // wee(ee_error_code,error_code);
               // Hash_Full();
               waitingData = 1;
               en_led_fail_mn = 1;
               tg_run_test = 10;
               break;
            }
         }
         break;

      case 2: // kiem tra dien ap may no co nằm trong ngưởng cho phep
         en_out_mn = 0;
         en_fuel_mn = 1;    // nhien lieu cap cho mn
         en_start_mn = 0;   // tat may no
         en_stop_mn = 0;    // tat may no
         en_preheat_mn = 0; // khong kich suoi
         en_air_mn = 0;

         if (tg_run_test < 10)
         {
            process_kdt_mn = 3; // het thoi gian test may
            en_fuel_mn = 0;
            OUT_FUEL_MN_OFF();
            tg_press_stop = 5;
            en_stop_mn = 1;
            OUT_STOP_MN_ON();
         }

         if (fail_pressure_mn == 1 || fail_pressure_mn_adc == 1)
         {
            process_kdt_mn = 15; // loi ap xuat nhot
            tg_run_test = 20;
            en_fuel_mn = 0;
            OUT_FUEL_MN_OFF();
            tg_press_stop = 5;
            en_stop_mn = 1;
            OUT_STOP_MN_ON();
            error_code = 5;

            // PCF8583_write_byte(ds1307_error_code,error_code);
            // wee(ee_error_code,error_code);
            // Hash_Full();
            waitingData = 1;
         }

         if (fail_temp_mn == 1 || fail_temp_mn_adc == 1)
         {
            process_kdt_mn = 16; // loi nhiet do
            tg_run_test = 20;
            en_fuel_mn = 0;
            OUT_FUEL_MN_OFF();
            tg_press_stop = 5;
            en_stop_mn = 1;
            OUT_STOP_MN_ON();
            error_code = 6;

            // PCF8583_write_byte(ds1307_error_code,error_code);
            // wee(ee_error_code,error_code);
            // Hash_Full();
            waitingData = 1;
         }

         if (fail_temp_mn == 1 || fail_temp_mn_adc == 1)
         {
            process_kdt_mn = 16; // loi nhiet do
            tg_run_test = 20;
            en_fuel_mn = 0;
            OUT_FUEL_MN_OFF();
            tg_press_stop = 5;
            en_stop_mn = 1;
            OUT_STOP_MN_ON();
            error_code = 6;

            // PCF8583_write_byte(ds1307_error_code,error_code);
            // wee(ee_error_code,error_code);
            // Hash_Full();
            waitingData = 1;
         }

         if (mn_vol_fail == 1)
         { // dien ap ngoai nguon cho phep
            tg_run_test = 20;
            if (adc_mn_2 > mn_vol_max)
               process_kdt_mn = 18, error_code = 3; // qua ap
            if ((adc_mn_2 > 50) && (adc_mn_2 < mn_vol_min))
               process_kdt_mn = 17, error_code = 4; // duoi ap
            if (adc_mn_2 < 50)
               process_kdt_mn = 14, error_code = 2; // khong ra nguon

            // PCF8583_write_byte(ds1307_error_code,error_code);
            // wee(ee_error_code,error_code);
            // Hash_Full();
            waitingData = 1;

            en_fuel_mn = 0;
            OUT_FUEL_MN_OFF();
            tg_press_stop = 5;
            en_stop_mn = 1;
            OUT_STOP_MN_ON();
         }

         if (fail_ChargeDC == 1)
         {
            process_kdt_mn = 19; // sac qua cao
            en_fuel_mn = 0;
            OUT_FUEL_MN_OFF();
            tg_press_stop = 5;
            en_stop_mn = 1;
            OUT_STOP_MN_ON();
            error_code = 7;

            // PCF8583_write_byte(ds1307_error_code,error_code);
            // wee(ee_error_code,error_code);
            // Hash_Full();
            waitingData = 1;
         }
         break;

      case 3: // tat may cho het thoi gian test may
         if (tg_press_stop == 0)
         {
            en_stop_mn = 0; // tat may no
            OUT_STOP_MN_OFF();

            en_air_mn = 0;
            OUT_AIR_MN_OFF();
         }

         en_out_mn = 0;
         en_fuel_mn = 0;  // nhien lieu cap cho mn
         en_start_mn = 0; // tat may no
         en_preheat_mn = 0;
         break;

      //==============================================================================
      case 4: // suoi may no
         process_kdt_mn = 5;
         en_out_mn = 0;
         en_fuel_mn = 1;    // nhien lieu cap cho mn
         en_preheat_mn = 1; // suoi nong may no
         en_stop_mn = 0;    // tat may no
         en_air_mn = 0;     // khong cap air

         tg_preheat = val_tg_preheat; // thoi gian suoi may

      case 5: // ket thuc suoi may no
         if (tg_preheat == 0)
         {
            process_kdt_mn = 6;
            en_preheat_mn = 0; // ngat suoi
         }

         if (adc_mn_2 > 50)
         {
            process_kdt_mn = 1;
            en_preheat_mn = 0; // suoi nong may no
            en_start_mn = 0;   // tat may no
            en_stop_mn = 0;    // tat may no
            en_air_mn = 0;     // khong cap air

            mn_vol_fail = 0;
            counter_mn_fail = 0;
            // kiem tra gia tri
            tg_on_dinh_mn = val_tg_on_dinh_mn;
         }
         break;

      case 6:             // khoi dong may no
         en_start_mn = 1; // nhan start
         en_air_mn = 1;   // on air
         tg_press_start = val_tg_press_start;
         tg_air = val_tg_air;
         counter_start--; // moi lan nhan start tru bot di 1
         process_kdt_mn = 7;

      case 7: // nha start khi co nguon hoac het thoi gian
         if (tg_air == 0)
         {
            en_air_mn = 0; // khong cap air
            OUT_AIR_MN_OFF();
         }
         if (tg_press_start == 0)
         {
            en_preheat_mn = 0; // khong kich suoi
            en_air_mn = 0;     // khong cap air
            en_start_mn = 0;   // khong nhan start, may no chua chay
            OUT_START_MN_OFF();
            en_fuel_mn = 0;
            OUT_FUEL_MN_OFF();

            tg_press_stop = 5;
            en_stop_mn = 1;
            OUT_STOP_MN_ON();

            switch (counter_start)
            {
            default:
               process_kdt_mn = 8;                  // may nỏ chưa chay
               tg_start_start = val_tg_start_start; // nap thoi gian start<->start
               break;

            case 0:
               process_kdt_mn = 9; // het so lan khoi dong
               error_code = 1;
               // write_ram_ds1307();

               // PCF8583_write_byte(ds1307_error_code,error_code);
               // wee(ee_error_code,error_code);
               // Hash_Full();
               waitingData = 1;
               en_led_fail_mn = 1;
               break;
            }
         }

         if (adc_mn_2 > 50)
         {
            process_kdt_mn = 1;
            en_preheat_mn = 0; // suoi nong may no
            en_start_mn = 0;
            OUT_START_MN_OFF();
            en_air_mn = 0;
            OUT_AIR_MN_OFF();
            mn_vol_fail = 0;
            counter_mn_fail = 0;
            // kiem tra gia tri
            tg_on_dinh_mn = val_tg_on_dinh_mn;
         }
         break;

      case 8: // trì hoản trước khi nhan lại start
         // quay lai khoi dong may no
         if (tg_start_start == 0)
            process_kdt_mn = 6;
         // cap nguon tro lai truoc khi start lai may no
         if (tg_start_start <= val_tg_preheat)
         {
            en_fuel_mn = 1;
         }

         if (tg_press_stop == 0)
         { // tat may no bang nut stop
            en_stop_mn = 0;
            OUT_STOP_MN_OFF();
         }

         if (adc_mn_2 > 50)
         {
            process_kdt_mn = 1;
            en_preheat_mn = 0; // suoi nong may no
            en_start_mn = 0;
            OUT_START_MN_OFF();
            en_air_mn = 0;
            OUT_AIR_MN_OFF();

            mn_vol_fail = 0;
            counter_mn_fail = 0;
            // kiem tra gia tri
            tg_on_dinh_mn = val_tg_on_dinh_mn;
         }
         break;

      case 9: // may no fail, khoi dong that bai
         en_start_mn = 0;
         en_fuel_mn = 0; // nhien lieu cap cho mn
         en_air_mn = 0;
         en_preheat_mn = 0; // suoi nong may no

         if (tg_press_stop == 0)
         { // tat may no bang nut stop
            en_stop_mn = 0;
            OUT_STOP_MN_OFF();
         }
         break;

      case 14: // MAY NO MAT NGUON
      case 15: // thieu ap luc nhot
      case 16: // nhiet do nuoc qua cao
      case 17: // may no ra dien ap thap
      case 18: // may no ra dien qua ap
      case 19: // may no sac accu qua cao
         if (tg_press_stop == 0)
         {
            en_stop_mn = 0; // tat may no
            OUT_STOP_MN_OFF();

            en_air_mn = 0;
            OUT_AIR_MN_OFF();
         }

         en_out_mn = 0;
         en_fuel_mn = 0;  // nhien lieu cap cho mn
         en_start_mn = 0; // tat may no
         en_preheat_mn = 0;
         break;
      }
      break;

   case 224: // xoa chuong trinh test may no
   case 240: // xoa chuong trinh test may no
      val_test_mn = 0;
      break;
   }
}

void disable_reset(void)
{
   if (pause_clock_reset == 0)
   {
      output_high(clock_reset);
      delay_ms(8);
      output_low(clock_reset);
      delay_ms(1);
      output_high(clock_reset);
      delay_ms(8);
      output_low(clock_reset);
      delay_ms(1);
      output_high(clock_reset);
      delay_ms(8);
      output_low(clock_reset);
      delay_ms(1);
   }
}

#int_timer0
void interrupt_timer0()
{
   clear_interrupt(INT_TIMER0);
   set_timer0(62536); // 500us => 65536 - (0.0005/(4/24000000))

   switch (pwm_lcd)
   {
   case 0:
      backligh_on();
      break;

   case 1:
      if (timer_backlight == 0)
         backligh_off();

   case 8:
      if (timer_backlight < 120)
         backligh_off();
      break;
   }

   if (++pwm_lcd > 10)
      pwm_lcd = 0;

   if (++counter_timer0 > 500)
   { // timer 1s
      counter_timer0 = 0;

      en_led_status = !en_led_status;

      if (timer_exit != 0)
         timer_exit--;

      if (timer_backlight != 0)
         timer_backlight--;

      if (tg_on_dinh_ac != 0)
         tg_on_dinh_ac--;

      if (tg_preheat != 0)
         tg_preheat--;

      if (tg_press_start != 0)
         tg_press_start--;

      if (tg_start_start != 0)
         tg_start_start--;

      if (tg_on_dinh_mn != 0)
         tg_on_dinh_mn--;

      if (pause_read_adc != 0)
         pause_read_adc--;

      if (tg_press_stop != 0)
         tg_press_stop--;

      if (tg_air != 0)
         tg_air--;

      // dem thoi gian may no khoi dong that bai cho viet hien thi thoi gian
      switch (val_progam)
      {
      case 112: // chay may no
                //---------------remote start-----------------
      case 129: // remote start

         switch (process_kdt_mn)
         {
         default:
            timer_hour_fail_mn = 0;
            timer_min_fail_mn = 0;
            break;

         case 9:  // may no fail, khoi dong that bai
         case 14: // MAY NO MAT NGUON
         case 15: // thieu ap luc nhot
         case 16: // nhiet do nuoc qua cao
         case 17: // may no ra dien ap thap
         case 18: // may no ra dien qua ap
         case 19: // may no sac accu qua cao
            if (++timer_sec_fail_mn > 59)
            {
               timer_sec_fail_mn = 0;
               if (++timer_min_fail_mn > 59)
               {
                  timer_min_fail_mn = 0;
                  timer_hour_fail_mn++;
               }
            }
            break;
         }
         break;
      }

      if (++flag_refresh_display > 10)
      {
         flag_refresh_display = 0;
         loop_not_display = 2;
      }

      if (tg_off_mn != 0)
         tg_off_mn--;

      if (tg_run_test != 0)
         tg_run_test--;
      if (tg_run_test == 0)
      {
         val_test_mn = 0; // het thoi gian test khong tai
      }

      if (timer_delay_run_mn != 0)
         timer_delay_run_mn--; // delay tri hoan chay may no ko theo khung gio
      if (timer_save_oil_mn != 0)
         timer_save_oil_mn--; // delay tri hoan chay may no theo khung gio

      if (--flag_timer_1s > 59)
      { // timer 1 phut
         flag_timer_1s = 59;

         // bo dem thoi gian chay cua may no
         if (mn_vol_fail == 0)
         {
            if (tg_run_on != 0 || tg_phut_run_on != 0)
            {
               if (--tg_phut_run_on > 59)
               {
                  tg_phut_run_on = 59;
                  if (tg_run_on != 0)
                     tg_run_on--;
               }
               //===========================
               if (++tong_phut_chay_mn > 59)
               {
                  tong_phut_chay_mn = 0;
                  tong_gio_chay_mn++;
               }
            }
            // if (waitingData==0) {
            waitingData = 1;

            // PCF8583_write_byte(ds1307_tong_gio_chay_mn,make8(tong_gio_chay_mn,0));
            // PCF8583_write_byte(ds1307_tong_gio_chay_mn+1,make8(tong_gio_chay_mn,1));
            // PCF8583_write_byte(ds1307_tong_phut_chay_mn,tong_phut_chay_mn);

            // wee(ee_tong_gio_chay_mn,make8(tong_gio_chay_mn,0));
            // wee(ee_tong_gio_chay_mn+1,make8(tong_gio_chay_mn,1));
            // wee(ee_tong_phut_chay_mn,tong_phut_chay_mn);

            // Hash_Full();
            // }
         }

         // thoi gian giai nhiet cho may no
         if (tg_giainhiet != 0)
            tg_giainhiet--;
         // thoi gian reset nhap mat khau
         if (time_reset_password != 0)
            time_reset_password--;

         // nhan nut up mot luc reset ve mat dinh
         counter_reset = 0;
         counter_view_debug = 0;
         counter_emergenry = 0;
      }
   }

   //   enable_interrupts(INT_TIMER0);
}
