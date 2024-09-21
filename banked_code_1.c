//=============================
// タイトル画面
//=============================

#include "SMSlib.h"
#include "MBMlib.h"
#include "PSGlib.h"
#include "common.h"
#include "banked_code.h"
#include "assets.h"

enum GAME_MODE title (void) __banked {
    SMS_VDPturnOffFeature(VDPFEATURE_LEFTCOLBLANK);  // 左１タイル
    
    // BGスクロールの初期化
    SMS_setBGScrollX(0);
    SMS_setBGScrollY(0);

    // 画像データをVRAMに書き込み
    SMS_mapROMBank(title__tiles__bin_bank);
    SMS_loadTiles (
        title__tiles__bin,
        0,
        title__tiles__bin_size
    );

    // タイルマップデータをVRAMに書き込み
    SMS_mapROMBank(title__tilemap__bin_bank);
    SMS_loadTileMap (
        0,
        0,
        title__tilemap__bin,
        title__tilemap__bin_size
    );

    // PSG
    setSMSMapROMBank(bgm_psg_bank);
    psg_bank = bgm_psg_bank;
    PSGPlay(bgm_psg);
    // MBM
    setSMSMapROMBank(TEST_MBM_bank);
    mbm_bank = TEST_MBM_bank;
    MBMPlay(TEST_MBM);

    // BGMの設定
    SMS_enableLineInterrupt();
    
    // パレットの設定
    SMS_mapROMBank(title__palette__bin_bank);
    SMS_loadBGPalette(title__palette__bin);

    SMS_displayOn(); 

    for (;;){
        SMS_waitForVBlank();

        SMS_copySpritestoSAT(); // SMS_waitForVBlank()の直後に実行するようにする

        // PSGを再生
        //SMS_mapROMBank(bgm_psg_bank);
        //PSGFrame();

        // Ⅰボタンを押したら、ゲーム画面へ
        if ( SMS_getKeysPressed() & PORT_A_KEY_1 ) {
            break;
        }

        //SMS_mapROMBank(ok_psg_bank);
        //PSGSFXFrame();

        //if ( SMS_getKeysPressed() & PORT_A_KEY_1 ) {
            // Ⅰボタンを押したら、効果音
        //    setSMSMapROMBank(ok_psg_bank);
        //    PSGSFXPlay( ok_psg, SFX_CHANNELS2AND3 );
            //sfx_bank = 1;
        //}
    }

    //PSGSFXStop();
    //PSGStop();

    return GAME;
}
