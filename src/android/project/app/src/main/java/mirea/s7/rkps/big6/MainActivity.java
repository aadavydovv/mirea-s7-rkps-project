package mirea.s7.rkps.big6;

import static android.os.SystemClock.sleep;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.os.Handler;
import android.view.KeyEvent;
import android.view.View;
import android.view.inputmethod.EditorInfo;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.ScrollView;
import android.widget.TextView;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class MainActivity extends AppCompatActivity {

    Handler mHandler;
    String mOutfile;
    String mInfile;

    void processInfile(String line) {
        try {
            FileWriter fw = new FileWriter(mInfile);
            BufferedWriter bw = new BufferedWriter(fw);
            bw.write(line);
            bw.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    void processOutfile() {
        Path path = Paths.get(mOutfile);
        long lines = 0;
        try {
            lines = Files.lines(path).count();
        } catch (IOException e) {
            e.printStackTrace();
        }

        File file = new File(mOutfile);
        StringBuilder text = new StringBuilder();

        try {
            String line;
            BufferedReader br = new BufferedReader(new FileReader(file));

            int counter = 0;
            while ((line = br.readLine()) != null) {
                text.append(line);
                text.append('\n');
                counter += 1;
                if (counter == lines) {
                    break;
                }
            }
            br.close();
        } catch (IOException ignored) {
        }

        String finalStr = text.toString();
        TextView tv = findViewById(R.id.textView);
        ScrollView sv = findViewById(R.id.scrollView);
        mHandler.post(new Runnable() {
            @Override
            public void run() {
                tv.setText(finalStr);
                sv.fullScroll(ScrollView.FOCUS_DOWN);
            }

        });
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mHandler = new Handler();

        File dir = getFilesDir();
        if (!dir.exists()) {
            dir.mkdir();
        }

        mOutfile = this.getFilesDir() + "/out";
        mInfile = this.getFilesDir() + "/in";

        File outfile = new File(mOutfile);
        try {
            outfile.delete();
            outfile.createNewFile();
        } catch (IOException e) {
            e.printStackTrace();
        }

        File infile = new File(mInfile);
        try {
            infile.delete();
            infile.createNewFile();
        } catch (IOException e) {
            e.printStackTrace();
        }

        new Thread(new Runnable() {
            @Override
            public void run() {
                main(mOutfile, mInfile);
            }
        }).start();

        new Thread(new Runnable() {
            @Override
            public void run() {
                while (true) {
                    processOutfile();
                    sleep(100);
                }
            }
        }).start();

        final EditText editText = (EditText) findViewById(R.id.editText);
        editText.setOnEditorActionListener(new TextView.OnEditorActionListener() {
            @Override
            public boolean onEditorAction(TextView v, int actionId, KeyEvent event) {
                boolean handled = false;
                if (actionId == EditorInfo.IME_ACTION_SEND) {
                    String text = editText.getText().toString();
                    processInfile(text);
                    editText.setText(null);
                    handled = true;
                }
                return handled;
            }
        });
    }

    public native Boolean main(String jOutfile, String jInfile);

    static {
        System.loadLibrary("big6");
    }
}