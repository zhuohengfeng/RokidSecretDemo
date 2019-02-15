package com.rokid.rokidsecretdemo;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        TextView tv = findViewById(R.id.sample_text);

        // e.g. 输入设备的sn号和seed
        String sn = "601091847330038";
        String seed = "NZUNwyiLdxv0Ut2ItrHwVfLCAlu7zM";
        String secret = getRokidSecret(sn, seed);
        tv.setText("sn: " + sn +
                "\nseed: " + seed +
                "\nseed: "+secret); //"正确的值为: 260EB4D4583B5BBA91DEF14150109A39";
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String getRokidSecret(String sn, String seed);
}
