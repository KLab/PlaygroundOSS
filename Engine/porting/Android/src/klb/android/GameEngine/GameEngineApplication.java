package klb.android.GameEngine;

import android.app.Application;
import klb.android.GameEngine.prngfix.PRNGFixes;

public class GameEngineApplication extends Application {

    @Override
    public void onCreate() {
        super.onCreate();

        PRNGFixes.apply();
    }

}
