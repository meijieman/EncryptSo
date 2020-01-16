//
// Created by Administrator on 2020/1/16.
//

#include "zip_util.h"
//#include "./zip/zip.h"


#include "log.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>


//解压apk
void uncompress_apk(const char *mpath, const char *fname) {
    int i = 0;

    LOGI("unzip");

/*    struct zip *apkArchive = zip_open(mpath, 0, NULL);

    struct zip_stat fstat;
    zip_stat_init(&fstat);
    struct zip_file *file = zip_fopen(apkArchive, fname, 0);
    if (!file) {
        return;
    }
    zip_stat(apkArchive, fname, 0, &fstat);
    LOGI("File %i:%s Size1: %llu Size2: %llu", i, fstat.name, fstat.size, fstat.comp_size);
    unsigned char *buffer = (unsigned char *) malloc(fstat.size);
    zip_fread(file, buffer, fstat.size);
//    Openssl_Verify(buffer, fstat.size);
    free(buffer);
    zip_fclose(file);
    zip_close(apkArchive);*/
}