//
// Created by Administrator on 2020/1/16.
//
#include "log.h"


/*
void MD5_Check(char *src) {
    char buff[3] = {'\0'};
    char hex[33] = {'\0'};
    unsigned char digest[MD5_DIGEST_LENGTH];

    MD5_CTX ctx;
    MD5_Init(&ctx);
    MD5_Update(&ctx, src, strlen(src));
    MD5_Final(digest, &ctx);

    strcpy(hex, "");
    for (int i = 0; i != sizeof(digest); i++) {
        sprintf(buff, "%02x", digest[i]);
        strcat(hex, buff);
    }
    if (strcmp(hex, "c8b5cf87aea796a187828b706504ca4b") == 0) {
        LOGI("SigCheckLog:MD5->验证通过 %s", hex);
    } else
        LOGI("SigCheckLog:MD5->验证失败 %s", hex);
}

//提取签名公钥
int Openssl_Verify(const unsigned char *signature_msg, unsigned int length) {
    //DER编码转换为PKCS7结构体
    PKCS7 *p7 = d2i_PKCS7(NULL, &signature_msg, length);
    if (p7 == NULL) {
        printf("error.\n");
        return 0;
    }

    //获得签名者信息stack
    STACK_OF(PKCS7_SIGNER_INFO) *sk = PKCS7_get_signer_info(p7);
    //获得签名者个数，可以有多个签名者
    int signCount = sk_PKCS7_SIGNER_INFO_num(sk);

    for (int i = 0; i < signCount; i++) {
        //获得签名者信息
        PKCS7_SIGNER_INFO *signInfo = sk_PKCS7_SIGNER_INFO_value(sk, i);
        //获得签名者证书
        X509 *cert = PKCS7_cert_from_signer_info(p7, signInfo);
        char *pubKey = (char *) cert->cert_info->key->public_key->data;
//        LOGI("SigCheckLog:  %s\n",pubKey);
        MD5_Check(pubKey);
        X509_free(cert);
    }
    return 1;
}
 */


