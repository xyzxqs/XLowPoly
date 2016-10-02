package io.github.xyzxqs.apps.xlowpoly;

import android.animation.ObjectAnimator;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.AsyncTask;
import android.os.Bundle;
import android.view.View;
import android.view.animation.LinearInterpolator;
import android.widget.CheckBox;
import android.widget.CompoundButton;
import android.widget.ImageView;
import android.widget.RadioButton;
import android.widget.SeekBar;
import android.widget.TextView;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.Menu;
import android.view.MenuItem;

import io.github.xyzxqs.xlowpoly.LowPoly;

public class MainActivity extends AppCompatActivity {


    final private static int SEEKBAR_ANIMATION_DURATION = 30000;
    final private static int SEEKBAR_STOP_CHANGE_DELTA = 5;

    private Bitmap mImageBitmap;
    private ImageView imageView;
    private int mLastProgress = 0;

    private SeekBar seekBar1;
    private SeekBar seekBar2;
    private TextView textView1;
    private TextView textView2;

    private CheckBox isFill;

    private boolean showLowPoly = true;
    private boolean full = true;

    private static final String TAG = "MainActivity";


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        seekBar1 = (SeekBar) findViewById(R.id.seekbar1);
        seekBar2 = (SeekBar) findViewById(R.id.seekbar2);
        setSupportActionBar(toolbar);

        imageView = (ImageView) findViewById(R.id.iv);
        textView1 = (TextView) findViewById(R.id.text1);
        textView2 = (TextView) findViewById(R.id.text2);

        RadioButton lowPolyRB = (RadioButton) findViewById(R.id.low_poly);
        RadioButton sandPaintingRB = (RadioButton) findViewById(R.id.sand_painting);
        isFill = (CheckBox) findViewById(R.id.fill_checkbox);

        lowPolyRB.setOnCheckedChangeListener(onCheckedChangeListener);
        sandPaintingRB.setOnCheckedChangeListener(onCheckedChangeListener);
        isFill.setOnCheckedChangeListener(onCheckedChangeListener);


        BitmapFactory.Options options = new BitmapFactory.Options();
        options.inSampleSize = 4;
        mImageBitmap = BitmapFactory.decodeResource(getResources(), R.drawable.meizhi, options);

        imageView.setImageBitmap(mImageBitmap);
        textView1.setOnClickListener(listener);
        textView2.setOnClickListener(listener);
//        invokeExcute();


        seekBar1.setOnSeekBarChangeListener(changeListener);
        seekBar2.setOnSeekBarChangeListener(changeListener);
    }

    View.OnClickListener listener = (v) -> imageView.setImageBitmap(mImageBitmap);

    private SeekBar.OnSeekBarChangeListener changeListener = new SeekBar.OnSeekBarChangeListener() {
        @Override
        public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
            if (Math.abs(seekBar.getProgress() - mLastProgress) > SEEKBAR_STOP_CHANGE_DELTA) {
                invokeExcute();
            }
        }

        @Override
        public void onStartTrackingTouch(SeekBar seekBar) {

        }

        @Override
        public void onStopTrackingTouch(SeekBar seekBar) {
            invokeExcute();
        }
    };

    private CompoundButton.OnCheckedChangeListener onCheckedChangeListener = (buttonView, isChecked) -> {

        switch (buttonView.getId()) {
            case R.id.fill_checkbox:
                full = isChecked;
                invokeExcute();
                break;
            case R.id.low_poly:
                float a = seekBar1.getProgress() / (float) seekBar1.getMax();
                if (isChecked) {
                    isFill.setVisibility(View.VISIBLE);
                    showLowPoly = true;
                    seekBar1.setMax(1500);
                    seekBar1.setProgress((int) (1500 * a));
                } else {
                    isFill.setVisibility(View.GONE);
                    showLowPoly = false;
                    seekBar1.setMax(20000);
                    seekBar1.setProgress((int) (20000 * a));
                }
                invokeExcute();
                break;
            case R.id.sand_painting:
                break;
        }
    };


    private boolean isProess = false;

    public void invokeExcute() {
        mLastProgress = seekBar1.getProgress();
        if (!isProess) {
            PixelizeImageAsyncTask asyncPixelateTask = new PixelizeImageAsyncTask();
            float alpha = seekBar1.getProgress() /*/ PROGRESS_TO_PIXELIZATION_FACTOR*/;
            int thre = seekBar2.getProgress();
            textView1.setText(String.format("点数：%s", alpha));
            textView2.setText(String.format("阈值：%s", thre));
            asyncPixelateTask.execute(alpha, thre, mImageBitmap, showLowPoly);
        }
    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    private boolean isAlpha = true;

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            ObjectAnimator animator = ObjectAnimator.ofInt(isAlpha ? seekBar1 : seekBar2, "progress", 0,
                    isAlpha ? seekBar1.getMax() : seekBar2.getMax());
            isAlpha = !isAlpha;
            animator.setInterpolator(new LinearInterpolator());
            animator.setDuration(SEEKBAR_ANIMATION_DURATION);
            animator.start();
            return true;
        }

        return super.onOptionsItemSelected(item);
    }


    private class PixelizeImageAsyncTask extends AsyncTask<Object, Void, Bitmap> {

        @Override
        protected Bitmap doInBackground(Object... params) {
            float pixelizationFactor = (float) params[0];
            int thre = (int) params[1];
            Bitmap originalBitmap = (Bitmap) params[2];
            boolean lowPoly = (boolean) params[3];
            return LowPoly.generate(originalBitmap, thre, pixelizationFactor, lowPoly, full);
        }

        @Override
        protected void onPostExecute(Bitmap result) {
            imageView.setImageBitmap(result);
            isProess = false;
        }

        @Override
        protected void onPreExecute() {

            isProess = true;
        }

        @Override
        protected void onProgressUpdate(Void... values) {

        }
    }

}
