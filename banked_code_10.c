#include "SMSlib.h"
#include "common.h"
#include "banked_code.h"
#include "assets.h"

void setSMSMapROMBank(unsigned char bank) __banked {
    last_bank = bank;
    SMS_mapROMBank(bank);
}
