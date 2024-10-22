#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SHIFT 3
char* caesar_decrypt(char* data, size_t length, int shift) {
    for (size_t i = 0; i < length; i++) {
        if (data[i] >= 'A' && data[i] <= 'Z') {
            data[i] = 'A' + (data[i] - 'A' - shift + 26) % 26;
        } else if (data[i] >= 'a' && data[i] <= 'z') {
            data[i] = 'a' + (data[i] - 'a' - shift + 26) % 26;
        }
    }
    return data;
}

const char *env_vars[] = {
    "DSS_QDPH=hqfubswhqy",
    "DSS_HQY=orfdo",
    "DSS_NHB=edvh64:Oba1HsvIg9nhA0WDdHhtU0pWd460RuZTxY3dpx9wwnX=",
    "DSS_GHEXJ=wuxh",
    "DSS_XUO=kwws://hqfubswhqy.whvw",
    "ORJ_FKDQQHO=vwdfn",
    "ORJ_GHSUHFDWLRQV_FKDQQHO=qxoo",
    "ORJ_OHYHO=ghexj",
    "GE_FRQQHFWLRQ=pbvto",
    "GE_KRVW=127.0.0.1",
    "GE_SRUW=3306",
    "GE_GDWDEDVH=hqfubswhqy",
    "GE_XVHUQDPH=urrw",
    "GE_SDVVZRUG=sdvvzrug",
    "EURDGFDVW_GULYHU=orj",
    "FDFKH_GULYHU=iloh",
    "ILOHVBVWHP_GLVN=orfdo",
    "TXHXH_FRQQHFWLRQ=vbqf",
    "VHVVLRQ_GULYHU=iloh",
    "VHVVLRQ_OLIHWLPH=120",
    "PHPFDFKHG_KRVW=127.0.0.1",
    "UHGLV_KRVW=127.0.0.1",
    "UHGLV_SDVVZRUG=qxoo",
    "UHGLV_SRUW=6379",
    "PDLO_PDLOHU=vpws",
    "PDLO_KRVW=pdloslw",
    "PDLO_SRUW=1025",
    "PDLO_XVHUQDPH=qxoo",
    "PDLO_SDVVZRUG=qxoo",
    "PDLO_HQFUBSWLRQ=qxoo",
    "PDLO_IURP_DGGUHVV=khoor@hadpsoh.frp",
    "PDLO_IURP_QDPH=\"hqfubswhqy\"",
    "DZV_DFFHVV_NHB_LG=",
    "DZV_VHFUHW_DFFHVV_NHB=",
    "DZV_GHIDXOW_UHJLRQ=xv-hdvw-1",
    "DZV_EXFNHW=",
    "DZV_XVH_SDWK_VWBOH_HQGSRLQW=idovh",
    "SXVKHU_DSS_LG=",
    "SXVKHU_DSS_NHB=",
    "SXVKHU_DSS_VHFUHW=",
    "SXVKHU_KRVW=",
    "SXVKHU_SRUW=443",
    "SXVKHU_VFKHPH=kwwsv",
    "SXVKHU_DSS_FOXVWHU=pw1",
    "YLWH_DSS_QDPH=\"hqfubswhqy\"",
    "YLWH_SXVKHU_DSS_NHB=\"\"",
    "YLWH_SXVKHU_KRVW=\"\"",
    "YLWH_SXVKHU_SRUW=\"443\"",
    "YLWH_SXVKHU_VFKHPH=\"kwwsv\"",
    "YLWH_SXVKHU_DSS_FOXVWHU=\"pw1\"",
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
        caesar_decrypt(decrypted_key, strlen(decrypted_key), SHIFT);
        if (strcmp(decrypted_key, key) == 0) {
            strncpy(decrypted_value, env_value + 1, sizeof(decrypted_value));
            caesar_decrypt(decrypted_value, strlen(decrypted_value), SHIFT);
            return decrypted_value;
        }
    }
    return NULL;
}

