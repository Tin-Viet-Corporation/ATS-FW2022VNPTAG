#ifndef EEPROM_H
#define EEPROM_H

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

#define ee_input_dc_low ee_Min_Save_To + 1          // 2byte
#define ee_delta_dc ee_input_dc_low + 2             // 2byte
#define ee_flag_accu_error_save_log ee_delta_dc + 2 // 1byte

#define ee_flag_switch ee_flag_accu_error_save_log + 1 // 1byte

#endif