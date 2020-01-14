package android.app;

import android.content.Context;
import android.os.RemoteException;
import android.util.Slog;
import android.os.ServiceManager;
import android.app.INarutoManager;

public class NarutoManager {
    private final String TAG = "NarutoManager";

    private INarutoManager mService;

	public NarutoManager() {
		mService = INarutoManager.Stub.asInterface(ServiceManager.getService("naruto_service"));
		
		if (mService == null) {
			Slog.e(TAG, "naruto service get failed");
		}
	}

    public String get() {
        if (mService != null) {

            try {
                return mService.get();
            } catch (RemoteException e) {
                Slog.e(TAG, "RemoteException " + e);

                return  null;
            }
        }

        return null;
    }

    public void set(String str) {

        if (mService != null) {
            try {
                mService.set(str);
            } catch (RemoteException e) {
                Slog.e(TAG, "RemoteException " + e);
            }
        }

    }

}
