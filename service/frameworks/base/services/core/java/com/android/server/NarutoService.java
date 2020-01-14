package com.android.server;

import android.app.INarutoManager;
import android.content.Context;
import android.os.RemoteException;
import android.util.Slog;

public class NarutoService extends INarutoManager.Stub {

    private final String TAG = "NarutoService";


    private Context mContext;

    public NarutoService() {
		NarutoInit();
    }

    public NarutoService(Context mContext) {
        this.mContext = mContext;
    }

    @Override
    public String get() throws RemoteException {
		String result = NarutoGet();
        Slog.d(TAG, "get from service " + result);
        return result;
    }

    @Override
    public void set(String str) throws RemoteException {
        Slog.d(TAG, "set from manager: " + str);
		NarutoSet(str);
    }

	private static native void NarutoInit();
	private static native String NarutoGet();
	private static native void NarutoSet(String str);
}
