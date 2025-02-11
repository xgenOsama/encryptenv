#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SHIFT 3
char* decrypt(char* data, size_t length, int shift) {
    for (size_t i = 0; i < length; i++) {
        if (data[i] >= 'A' && data[i] <= 'Z') {
            data[i] = 'A' + (data[i] - 'A' - shift + 26) % 26;
        } else if (data[i] >= 'a' && data[i] <= 'z') {
            data[i] = 'a' + (data[i] - 'a' - shift + 26) % 26;
        } else if (data[i] >= '0' && data[i] <= '9') {
            data[i] = '0' + (data[i] - '0' - shift + 10) % 10;
        } else if (data[i] == '*') {
            data[i] = '.';
        }
    }
    return data;
}

const char *env_vars[] = {
    "DSS_QDPH=hqfubswhqy",
    "DSS_HQY=orfdo",
    "DSS_NHB=edvh97:Oba4HsvIg2nhA3WDdHhtU3pWd793RuZTxY6dpx2wwnX=",
    "DSS_GHEXJ=wuxh",
    "DSS_XUO=kwws://hqfubswhqy*whvw",
    "ORJ_FKDQQHO=vwdfn",
    "ORJ_GHSUHFDWLRQV_FKDQQHO=qxoo",
    "ORJ_OHYHO=ghexj",
    "GE_FRQQHFWLRQ=pbvto",
    "GE_KRVW=450*3*3*4",
    "GE_SRUW=6639",
    "GE_GDWDEDVH=hqfubswhqy",
    "GE_XVHUQDPH=urrw",
    "GE_SDVVZRUG=sdvvzrug",
    "EURDGFDVW_GULYHU=orj",
    "FDFKH_GULYHU=iloh",
    "ILOHVBVWHP_GLVN=orfdo",
    "TXHXH_FRQQHFWLRQ=vbqf",
    "VHVVLRQ_GULYHU=iloh",
    "VHVVLRQ_OLIHWLPH=453",
    "PHPFDFKHG_KRVW=450*3*3*4",
    "UHGLV_KRVW=450*3*3*4",
    "UHGLV_SDVVZRUG=qxoo",
    "UHGLV_SRUW=9602",
    "PDLO_PDLOHU=vpws",
    "PDLO_KRVW=pdloslw",
    "PDLO_SRUW=4358",
    "PDLO_XVHUQDPH=qxoo",
    "PDLO_SDVVZRUG=qxoo",
    "PDLO_HQFUBSWLRQ=qxoo",
    "PDLO_IURP_DGGUHVV=khoor@hadpsoh*frp",
    "PDLO_IURP_QDPH=\"${DSS_QDPH}\"",
    "DZV_DFFHVV_NHB_LG=qxoo",
    "DZV_VHFUHW_DFFHVV_NHB=qxoo",
    "DZV_GHIDXOW_UHJLRQ=xv-hdvw-4",
    "DZV_EXFNHW=qxoo",
    "DZV_XVH_SDWK_VWBOH_HQGSRLQW=idovh",
    "SXVKHU_DSS_LG=qxoo",
    "SXVKHU_DSS_NHB=qxoo",
    "SXVKHU_DSS_VHFUHW=qxoo",
    "SXVKHU_KRVW=qxoo",
    "SXVKHU_SRUW=776",
    "SXVKHU_VFKHPH=kwwsv",
    "SXVKHU_DSS_FOXVWHU=pw4",
    "YLWH_DSS_QDPH=\"${DSS_QDPH}\"",
    "YLWH_SXVKHU_DSS_NHB=\"${SXVKHU_DSS_NHB}\"",
    "YLWH_SXVKHU_KRVW=\"${SXVKHU_KRVW}\"",
    "YLWH_SXVKHU_SRUW=\"${SXVKHU_SRUW}\"",
    "YLWH_SXVKHU_VFKHPH=\"${SXVKHU_VFKHPH}\"",
    "YLWH_SXVKHU_DSS_FOXVWHU=\"${SXVKHU_DSS_FOXVWHU}\"",
};

const char* get_env_value(const char *key) {
    static char decrypted_key[256];
    static char decrypted_value[256];
    for (int i = 0; i < 50; i++) {
        const char *env = env_vars[i];
        const char *env_value = strchr(env, '=');
        if (env_value == NULL) continue;
        strncpy(decrypted_key, env, env_value - env);
        decrypted_key[env_value - env] = '\0';
        decrypt(decrypted_key, strlen(decrypted_key), SHIFT);
        if (strcmp(decrypted_key, key) == 0) {
            strncpy(decrypted_value, env_value + 1, sizeof(decrypted_value));
            decrypt(decrypted_value, strlen(decrypted_value), SHIFT);
            return decrypted_value;
        }
    }
    return NULL; // Not found
}
