/*
Jika menggunakan Code::Blocks sebagai editor:
untuk optimasi supaya file hex hasil kompilasi menjadi kecil (fungsi yang tidak dipanggil tidak dimasukkan ke dalam
file hex), maka dilakukan pengaturan proses compile dan linker program sbb:
1. copy option berikut pada compiler setting    (Menu Settings,Compiler, Compiler settings, Other options:)
   -ffunction-sections
2. copy option berikut pada linker setting      (Menu Settings,Compiler, Linker settings, Other linker options:)
   -Wl,-gc-sections
*/

#include "myModule.h"                   // edit module yang akan digunakan pada file ini
#include "../AdRoiT_Files/mySystem.h"

int main(void)
{   SystemInit();       // inisialisasi sistem (wajib bagi semua project)
                        // detail dari  modul yang diaktifkan pada setiap project bisa dilihat pada file "myModule.h"
    // untuk mengaktifkan IMU, maka set opsi UseIMU = 1
    // opsi tersebut dapat dilihat pada file "myModule.h" (pada baris 31)
    // selanjutnya pada bagian ImuFilter, pilih opsi DMP
    // selain itu dapat dilih opsi untuk orientasi sudut 0 dari board AdRoiT memalui opsi PosisiBoard (TEGAK atau TIDUR)

    // program komputasi IMU dapat dilihat pada file "myIMU_DMP.h"

    imu.setDMPEnabled(true);
    imu.resetFIFO();
    imu.Start();
    uint8_t LastMode = 100; // nilai selain 0-15
    while(1)
    {
        if(MODE!=LastMode)
        {   LastMode = MODE;
            lcd.Hapus();
            switch (MODE)
            {   case    0: lcd.TulisKiri(0,">Roll Pitch Yaw ");   break;
                case    1: lcd.TulisKiri(0,">Data Quaternion");   break;
                case    2: lcd.TulisKiri(0,">Data Gyroscope ");   break;
                case    3: lcd.TulisKiri(0,">D.Accelerometer");   break;
            }
            buzzer.Nada1();
            lcd.HapusKanan(0);
        }
        if(MODE==0)
        {   lcd.GotoXY(0,0);    lcd.Tulis(0,"Sudut :");

            lcd.GotoXY(8,0);    lcd.Data('R');
            lcd.Float(imu.getRoll()*RAD2DEG,3);     lcd.Data(' ');
            if(imu.getRoll()*RAD2DEG < 2 && imu.getRoll()*RAD2DEG > -2){
                servo.Servo1(90);
            } else if(imu.getRoll()*RAD2DEG > 2){
                servo.Servo1(90 - imu.getRoll()*RAD2DEG);
            } else if(imu.getRoll()*RAD2DEG < -2){
                servo.Servo1(90 - imu.getRoll()*RAD2DEG);
            } else if(imu.getRoll()*RAD2DEG > 90 && imu.getRoll()*RAD2DEG < -90){

            }

            lcd.GotoXY(0,1);    lcd.Data('P');
            lcd.Float(imu.getPitch()*RAD2DEG,3);    lcd.Data(' ');
             if(imu.getPitch()*RAD2DEG < 2 && imu.getPitch()*RAD2DEG > -2){
                servo.Servo1(90);
            } else if(imu.getPitch()*RAD2DEG > 2){
                servo.Servo1(90 - imu.getPitch()*RAD2DEG);
            } else if(imu.getPitch()*RAD2DEG < -2){
                servo.Servo1(90 - imu.getPitch()*RAD2DEG);
            } else if(imu.getPitch()*RAD2DEG > 90 && imu.getPitch()*RAD2DEG < -90){

            }

            lcd.GotoXY(8,1);    lcd.Data('Y');
            lcd.Float(imu.getYaw()*RAD2DEG,3);      lcd.Data(' ');
        }
        else if(MODE==1)
        {   lcd.GotoXY(0,0);    lcd.Data('W');
            lcd.Float(imu.q.w,3);   lcd.Data(' ');

            lcd.GotoXY(8,0);    lcd.Data('X');
            lcd.Float(imu.q.x,3);   lcd.Data(' ');

            lcd.GotoXY(0,1);    lcd.Data('Y');
            lcd.Float(imu.q.y,3);   lcd.Data(' ');

            lcd.GotoXY(8,1);    lcd.Data('Z');
            lcd.Float(imu.q.z,3);   lcd.Data(' ');
        }
        else if(MODE==2)
        {   lcd.Tulis(0,"GyroData:X");
            lcd.Angka5(imu.Gx); lcd.Data(' ');

            lcd.GotoXY(1,1);    lcd.Data('Y');
            lcd.Angka5(imu.Gy); lcd.Data(' ');

            lcd.GotoXY(9,1);    lcd.Data('Z');
            lcd.Angka5(imu.Gz); lcd.Data(' ');

        }
        else if(MODE==3)
        {   lcd.Tulis(0,"Acc.Data:X");
            lcd.Angka5(imu.Ax); lcd.Data(' ');

            lcd.GotoXY(1,1);    lcd.Data('Y');
            lcd.Angka5(imu.Ay); lcd.Data(' ');

            lcd.GotoXY(9,1);    lcd.Data('Z');
            lcd.Angka5(imu.Az); lcd.Data(' ');
        }

        adc.CekBatere();
        _delay_ms(10);
    }
}
