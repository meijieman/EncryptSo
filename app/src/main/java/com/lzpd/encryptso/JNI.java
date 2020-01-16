package com.lzpd.encryptso;

import android.content.Context;

/**
 * Desc: TODO
 * <p>
 * Author: meijie
 * PackageName: PACKAGE_NAME
 * ProjectName: EncryptSo
 * Date: 2020/1/16 15:59
 */
public class JNI {

    static{
        System.loadLibrary("native-lib");
    }

    /**
     * 获取api 调用授权 key
     * @param context 应用签名信息，防止http 接口  授权 key 被盗用
     * @return
     */
    public native String getAuthKey(Context context);

    /**
     * 获取 so 文件版本
     *
     * @return
     */
    public native static String getVer();
}
