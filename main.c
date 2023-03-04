#include "SMSlib.h"
#include "common.h"
#include "banked_code.h"

// グローバル変数
unsigned char psg_bank = 0;
unsigned char sfx_bank = 0;

void main (void)
{
    /* Clear VRAM */
    //SMS_VRAMmemsetW(0, 0x0000, 16384);

    //SMS_VDPturnOnFeature(VDPFEATURE_EXTRAHEIGHT);  // Display Mode 5

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
