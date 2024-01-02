#ifndef RAM_H
#define RAM_H

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

#define ds1307_input_dc_low ds1307_Min_Save_To + 1          // 2byte
#define ds1307_delta_dc ds1307_input_dc_low + 2             // 2byte
#define ds1307_flag_accu_error_save_log ds1307_delta_dc + 2 // 1byte

// bit cuoi cung ff
#endif