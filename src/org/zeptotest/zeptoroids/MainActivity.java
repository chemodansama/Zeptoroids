package org.zeptotest.zeptoroids;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.app.Activity;
import android.content.Context;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.view.MotionEvent;
import android.view.SurfaceHolder;
import android.view.View;
import android.view.View.OnTouchListener;
import android.view.Window;
import android.view.WindowManager;

public class MainActivity extends Activity implements OnTouchListener {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        
        this.requestWindowFeature(Window.FEATURE_NO_TITLE);
        this.getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, 
                                  WindowManager.LayoutParams.FLAG_FULLSCREEN);
        
        mGLView = new ZrSurfaceView(this);
        setContentView(mGLView);
        mGLView.setOnTouchListener(this);
    }

    @Override
    protected void onPause() {
        super.onPause();
        mGLView.onPause();
    }

    @Override
    protected void onResume() {
        super.onResume();
        mGLView.onResume();
    }
    
    private GLSurfaceView mGLView;

    static {
        System.loadLibrary("Zeptoroids");
    }
    
    private static native void nativePointerDown(int pointerId, float x, float y);
    private static native void nativePointerUp(int pointerId);
    private static native void nativePointerDone();

    @Override
    public boolean onTouch(View v, MotionEvent ev) {
        final int action = ev.getAction();
        switch (action & MotionEvent.ACTION_MASK) {
            case MotionEvent.ACTION_DOWN: {
                final float x = ev.getX();
                final float y = ev.getY();
                int pointerId = ev.getPointerId(0);
                nativePointerDown(pointerId, x, y);
                break;
            }
            
            case MotionEvent.ACTION_POINTER_DOWN: {
                final int pointerIndex = (action & MotionEvent.ACTION_POINTER_INDEX_MASK) >> MotionEvent.ACTION_POINTER_INDEX_SHIFT;
                final int pointerId = ev.getPointerId(pointerIndex);
                final float x = ev.getX(pointerIndex);
                final float y = ev.getY(pointerIndex);
                nativePointerDown(pointerId, x, y);
                break;
            }
    
            case MotionEvent.ACTION_UP: {
                nativePointerDone();
                break;
            }
    
            case MotionEvent.ACTION_CANCEL: {
                nativePointerDone();
                break;
            }
            
            case MotionEvent.ACTION_POINTER_UP: {
                final int pointerIndex = (action & MotionEvent.ACTION_POINTER_INDEX_MASK) >> MotionEvent.ACTION_POINTER_INDEX_SHIFT;
                final int pointerId = ev.getPointerId(pointerIndex);
                nativePointerUp(pointerId);
                break;
            }
        }

        return true;
    }    
}

class ZrSurfaceView extends GLSurfaceView {
    public ZrSurfaceView(Context context) {
        super(context);
        mRenderer = new ZrRenderer();
        setRenderer(mRenderer);        
    }

    @Override
    public boolean onTouchEvent(final MotionEvent event) {
        if (event.getAction() == MotionEvent.ACTION_DOWN) {
            nativeTogglePauseResume();
        }
        return true;
    }

    @Override
    public void onPause() {
        super.onPause();
        nativePause();
    }

    @Override
    public void onResume() {
        super.onResume();
        nativeResume();
    }

    private final ZrRenderer mRenderer;

    private static native void nativePause();
    private static native void nativeResume();
    private static native void nativeTogglePauseResume();
}

class ZrRenderer implements GLSurfaceView.Renderer, SurfaceHolder.Callback {
    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        nativeInit();
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int w, int h) {
        nativeResize(w, h);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        nativeRender();
    }

    private static native void nativeInit();
    private static native void nativeResize(int w, int h);
    private static native void nativeRender();
    private static native void nativeDone();

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int width,
            int height) {
    }

    @Override
    public void surfaceCreated(SurfaceHolder holder) {
    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {
        nativeDone();
    }
}
