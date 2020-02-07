package com.example.agcs;

import android.annotation.SuppressLint;
import android.os.Bundle;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;
import io.github.controlwear.virtual.joystick.android.Joystick;

public class MainActivity extends AppCompatActivity {

    private TextView txtvStrength;
    private TextView txtvAngle;
    private TextView txtvCoordinate;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);


        txtvStrength = (TextView) findViewById(R.id.txtvStrength);
        txtvAngle = (TextView) findViewById(R.id.txtvAngle);
        txtvCoordinate = findViewById(R.id.txtvCoordinate);

        final Joystick joystick_left = (Joystick) findViewById(R.id.joystick_left);
        joystick_left.setOnMoveListener(new Joystick.OnMoveListener() {
            @SuppressLint("DefaultLocale")
            @Override
            public void onMove(int angle, int strength) {
                txtvAngle.setText(angle + "°");
                txtvStrength.setText(strength + "%");
                txtvCoordinate.setText(
                        String.format("x:%03d y:%03d",
                                joystick_left.getNormalizedX(),
                                joystick_left.getNormalizedY())
                );
            }
        });
    }

}
