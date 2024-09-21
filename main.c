#include "SMSlib.h"
#include "MBMlib.h"
#include "common.h"
#include "banked_code.h"
#include "assets.h"

// グローバル変数
unsigned char psg_bank = 0;
unsigned char mbm_bank = 0;
unsigned char sfx_bank = 0;
unsigned char last_bank = 0;

unsigned char isFm = 0;

void upSound () {
    //SMS_disableLineInterrupt();

    if (isFm == 1){
        SMS_mapROMBank(mbm_bank);
        MBMFrame();
        //SMS_mapROMBank(psg_bank);   // ここは過去のバンクを登録しないので、SMS_mapROMBank()のまま
        //PSGFrame();
    }
    else {
        SMS_mapROMBank(psg_bank);   // ここは過去のバンクを登録しないので、SMS_mapROMBank()のまま
        PSGFrame();
    }

    if (sfx_bank == 0) {
        // SEが設定されていない場合、0でくるので、処理しない
    }
    else {
        SMS_mapROMBank(sfx_bank);
        PSGSFXFrame();
    }

    // バンクを元に戻す
    SMS_mapROMBank(last_bank);

    //SMS_waitForVBlank();
    //SMS_enableLineInterrupt();
    //SMS_waitForVBlank();
}

void main (void)
{
    /* Clear VRAM */
    //SMS_VRAMmemsetW(0, 0x0000, 16384);

    //SMS_VDPturnOnFeature(VDPFEATURE_EXTRAHEIGHT);  // Display Mode 5

    SMS_disableLineInterrupt();
    SMS_setLineInterruptHandler(upSound);
    SMS_setLineCounter(0xBF);  // 0x60ぐらいからそれほど変わらない？ようなのですが、いったん最大値の0xBFにしています（推測ですが、96/192=1フレームに1回なので、0x60～0xC0は同じようなもの）

    if (SMS_GetFMAudioCapabilities()){
        SMS_EnableAudio (SMS_ENABLE_AUDIO_FM_ONLY);
        isFm = 1;
    }
    else {
        SMS_EnableAudio (SMS_ENABLE_AUDIO_PSG_ONLY);
        isFm = 0;
    }

    enum GAME_MODE gameMode;
    gameMode = TITLE;
     
    for (;;){

        switch(gameMode){
        case TITLE:
            gameMode = title();
            break;
        case GAME:
            gameMode = game();
            break;
        default:
            break;
        }
    }
}

//SMS_EMBED_SEGA_ROM_HEADER(9999,0);  // Info: SEGA header found, checksum updated
//SMS_EMBED_SEGA_ROM_HEADER_16KB(9999,0); // Info: SEGA header found, checksum updated
//SMS_EMBED_SDSC_HEADER_AUTO_DATE(1,0,"raphnet","first test","A first test. If you can compile this, you're good to go");
//SMS_EMBED_SDSC_HEADER_AUTO_DATE_16KB(1,0,"raphnet","first test","A first test. If you can compile this, you're good to go");
