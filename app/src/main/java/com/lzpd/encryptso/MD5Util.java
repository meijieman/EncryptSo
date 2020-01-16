package com.lzpd.encryptso;

import java.security.MessageDigest;

public class MD5Util {

    private MD5Util() {
    }

    public static final String getMD5String(String s) {
        return s == null ? null : getMD5String(s.getBytes());
    }

    public static final String getMD5String(byte[] dataBytes) {
        return dataBytes == null ? null : getMD5String(dataBytes, 0, dataBytes.length);
    }

    public static final String getMD5String(byte[] dataBytes, int offset, int len) {
        if (dataBytes == null) {
            return null;
        } else {
            try {
                MessageDigest mdInst = MessageDigest.getInstance("MD5");
                mdInst.update(dataBytes, offset, len);
                byte[] md = mdInst.digest();
                StringBuffer sb = new StringBuffer();

                for(int i = 0; i < md.length; ++i) {
                    int val = md[i] & 255;
                    if (val < 16) {
                        sb.append("0");
                    }

                    sb.append(Integer.toHexString(val));
                }

                return sb.toString();
            } catch (Exception var8) {
                return null;
            }
        }
    }
}

