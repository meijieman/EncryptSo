package com.lzpd.encryptso;

import android.content.Context;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.pm.Signature;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    private static final String TAG = "MainActivity";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        TextView tv = findViewById(R.id.sample_text);

        String signature = getSignature(this, getPackageName());
        Log.i(TAG, "sign " + signature);
        Log.i(TAG, "md5 " + MD5Util.getMD5String(signature));

        JNI jni = new JNI();

        findViewById(R.id.btn_auth).setOnClickListener(v -> {

            String authKey = jni.getAuthKey(this);

            tv.setText(authKey);
        });

        findViewById(R.id.btn_version).setOnClickListener(v -> {
            Toast.makeText(this, JNI.getVer(), Toast.LENGTH_SHORT).show();
        });


    }

    /**
     * 获取指定包名的签名字符串
     *
     * @param context
     * @return
     */
    public static String getSignature(Context context, String pkgname) {
        try {
            PackageInfo packageInfo = context.getPackageManager().getPackageInfo(pkgname, PackageManager.GET_SIGNATURES);
            Signature[] signatures = packageInfo.signatures;
            return signatures[0].toCharsString();
        } catch (PackageManager.NameNotFoundException e) {
            e.printStackTrace();
        }

        return null;

    }
}
