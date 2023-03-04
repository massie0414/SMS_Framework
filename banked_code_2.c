//============================================
// ゲーム処理
//============================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "SMSlib.h"
#include "PSGlib.h"
#include "common.h"
#include "banked_code.h"
#include "assets.h"


enum GAME_MODE game () __banked {

    SMS_VDPturnOnFeature(VDPFEATURE_LEFTCOLBLANK);  // 左１タイル非表示

    unsigned char playerX = 100;
    unsigned char playerY = 100;

    unsigned char scrollX = 0;
    unsigned char scrollY = 0;

    // 背景データのタイルをVRAMに書き込み
    SMS_mapROMBank(tile__tiles__bin_bank);
    SMS_loadTiles (
        tile__tiles__bin,
        0x00,
        tile__tiles__bin_size
    );

    // 背景のタイルマップデータをVRAMに書き込み
    
    unsigned char tmp_tilemap[8];
    for (unsigned char y = 0; y < 12; y++) {    // TODO 最大値はマップの大きさを入れる
        for (unsigned char x = 0; x < 16; x++) {    // TODO 最大値はマップの大きさを入れる

            SMS_mapROMBank(map01_bin_bank);
            unsigned char tmpIndex = map01_bin[x+y*16]; // TODO 16のところはマップの大きさ

            tmpIndex *= 8;

            SMS_mapROMBank(tile__tilemap__bin_bank);
            tmp_tilemap[0] = tile__tilemap__bin[tmpIndex+0];
            tmp_tilemap[1] = tile__tilemap__bin[tmpIndex+1];
            tmp_tilemap[2] = tile__tilemap__bin[tmpIndex+2];
            tmp_tilemap[3] = tile__tilemap__bin[tmpIndex+3];
            tmp_tilemap[4] = tile__tilemap__bin[tmpIndex+4];
            tmp_tilemap[5] = tile__tilemap__bin[tmpIndex+5];
            tmp_tilemap[6] = tile__tilemap__bin[tmpIndex+6];
            tmp_tilemap[7] = tile__tilemap__bin[tmpIndex+7];
            
            SMS_loadTileMapArea (
                x*2,    // 16ドットずつ入れるので、２倍にしています
                y*2,    // 16ドットずつ入れるので、２倍にしています
                tmp_tilemap,
                2,
                2
            );
        }
    }


    // スプライトデータの書き込み
    SMS_mapROMBank(character__tiles__bin_bank);
    SMS_loadTiles (
        character__tiles__bin,
        0x100,
        character__tiles__bin_size
    );

    // 背景データのパレット
    SMS_mapROMBank(tile__tiles__bin_bank);
    SMS_loadBGPalette(tile__palette__bin);

    // スプライトデータのパレット
    SMS_mapROMBank(character__tiles__bin_bank);
    SMS_loadSpritePalette(character__palette__bin);

    for (;;){

        SMS_waitForVBlank();

        PSGFrame();
        PSGSFXFrame();

        if ( SMS_getKeysPressed() & PORT_A_KEY_1 ) {
            // Ⅰボタンを押したら、効果音
            SMS_mapROMBank(ok_psg_bank);
            PSGSFXPlay( ok_psg, SFX_CHANNEL3 );
        }

        if ( SMS_getKeysPressed() & PORT_A_KEY_2 ) {
            // Ⅱボタンを押したら
        }

        // SMS_getKeysHeld() ←押しっぱなし
        // SMS_getKeysReleased() ←離したとき

        // キャラクターの移動
        unsigned char kp = SMS_getKeysStatus();
        if ( kp & PORT_A_KEY_UP ) {
            // 上
            playerY--;
        }
        if ( kp & PORT_A_KEY_DOWN ) {
            // 下
            playerY++;
        }
        if ( kp & PORT_A_KEY_LEFT ) {
            // 左
            playerX--;
        }
        if ( kp & PORT_A_KEY_RIGHT ) {
            // 右
            playerX++;
        }

        // 背景の移動
        scrollX--;

        // スプライトの描画
        SMS_initSprites();
        SMS_addSprite (playerX+0, playerY+0, 0);    // 左上のスプライト
        SMS_addSprite (playerX+8, playerY+0, 1);    // 右上のスプライト
        SMS_addSprite (playerX+0, playerY+8, 2);    // 左下のスプライト
        SMS_addSprite (playerX+8, playerY+8, 3);    // 右下のスプライト
        SMS_copySpritestoSAT();

        // 背景のスクロール
        SMS_setBGScrollX(scrollX);
        SMS_setBGScrollY(scrollY);
    }

    return TITLE;
}
