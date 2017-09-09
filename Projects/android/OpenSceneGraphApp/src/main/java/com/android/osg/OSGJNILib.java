/*
 * Copyright (C) 2007 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.android.osg;

import android.content.Context;

import java.io.File;
import java.io.FileOutputStream;
import java.io.InputStream;

// Wrapper for native library

public class OSGJNILib {

    static {
        System.loadLibrary("openscenegraph-native" + (BuildConfig.DEBUG ? "d" : ""));
    }

    protected static void setupResources(Context context) {
        // Get absolute path to internal storage.
        File dir = context.getFilesDir();
        String path = dir.getAbsolutePath();
        // Check if 'box.osgt' already exists.
        String modelPath = path + "/box.osgt";
        File model = new File(modelPath);
        // Copy 'box.ogst' from 'res/raw', if it does not exist.
        try {
            if (!model.exists()) {
                // Note: this only works for small files,
                // because we read the whole file into memory.
                InputStream is = context.getResources().openRawResource(R.raw.box);
                byte[] buffer = new byte[is.available()];
                is.read(buffer);
                FileOutputStream os = new FileOutputStream(model);
                os.write(buffer);
            }
            OSGJNILib.loadModel(modelPath);
        } catch (Exception e) {
            // Do nothing.
        }
    }

    public static native void init(int width, int height);
    public static native void step();

    public static native void loadModel(String modelPath);
    public static native void moveMouse(float x, float y);
    public static native void pressMouse(boolean down, float x, float y);
}
