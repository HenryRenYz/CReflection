package com.henryrenyz.creflect;

import org.jetbrains.annotations.NotNull;
import org.jetbrains.annotations.Nullable;

import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.lang.reflect.Constructor;
import java.lang.reflect.Field;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.net.URL;
import java.net.URLClassLoader;

public interface ReflectLibInterface {

    /** Get reflection lib instance, access to all methods in this interface */
    static ReflectLibInterface getImpl() {
        return LibLoader.theLib;
    }

    class LibLoader extends URLClassLoader {

        private static ReflectLibInterface theLib;
        private static URLClassLoader loader;

        LibLoader(URL[] urls, ClassLoader parent) {
            super(urls, parent);
        }

        @SuppressWarnings("unchecked")
        Class<? extends ReflectLibInterface> getLibClass() throws IOException {
            URL url = getParent().getResource("com/henryrenyz/creflect/ReflectLibImpl.class");
            assert url != null;
            InputStream is = url.openStream();
            byte[] data = new byte[is.available()];
            int len = is.read(data);
            return (Class<ReflectLibInterface>) defineClass("com.henryrenyz.creflect.ReflectLibImpl", data, 0, len);
        }
    }

    /** Call this method on server start */
    static void loadLib(File dll) throws IOException {
        ClassLoader parent = ReflectLibInterface.class.getClassLoader();
        URL url = parent.getResource("com/henryrenyz/creflect/ReflectLibImpl.class");
        LibLoader loader = new LibLoader(new URL[]{url}, parent);
        Class<? extends ReflectLibInterface> cls = loader.getLibClass();
        LibLoader.loader = loader;
        try {
            Method init = cls.getDeclaredMethod("init", File.class);
            init.setAccessible(true);
            init.invoke(null, dll);
            Constructor<? extends ReflectLibInterface> c = cls.getDeclaredConstructor();
            c.setAccessible(true);
            LibLoader.theLib = c.newInstance();
        } catch (IllegalAccessException | InvocationTargetException | NoSuchMethodException | InstantiationException e) {
            e.printStackTrace();
        }
    }

    /** Call this method on server reload */
    static void unloadLib() {
        LibLoader.loader = null;
        LibLoader.theLib = null;
        System.gc();
    }

    @Nullable Object invoke(@NotNull Method mth, @Nullable Object member, Object... params);

    int invokeInt(@NotNull Method mth, @Nullable Object member, Object... params);

    short invokeShort(@NotNull Method mth, @Nullable Object member, Object... params);

    byte invokeByte(@NotNull Method mth, @Nullable Object member, Object... params);

    long invokeLong(@NotNull Method mth, @Nullable Object member, Object... params);

    float invokeFloat(@NotNull Method mth, @Nullable Object member, Object... params);

    double invokeDouble(@NotNull Method mth, @Nullable Object member, Object... params);

    boolean invokeBoolean(@NotNull Method mth, @Nullable Object member, Object... params);

    char invokeChar(@NotNull Method mth, @Nullable Object member, Object... params);



    @Nullable Object getField(@NotNull Field field, @Nullable Object member);

    int getFieldInt(@NotNull Field field, @Nullable Object member);

    short getFieldShort(@NotNull Field field, @Nullable Object member);

    byte getFieldByte(@NotNull Field field, @Nullable Object member);

    long getFieldLong(@NotNull Field field, @Nullable Object member);

    float getFieldFloat(@NotNull Field field, @Nullable Object member);

    double getFieldDouble(@NotNull Field field, @Nullable Object member);

    boolean getFieldBoolean(@NotNull Field field, @Nullable Object member);

    char getFieldChar(@NotNull Field field, @Nullable Object member);


    
    void setField(@NotNull Field field, @Nullable Object member, @Nullable Object value);

    void setFieldInt(@NotNull Field field, @Nullable Object member, int value);

    void setFieldShort(@NotNull Field field, @Nullable Object member, short value);

    void setFieldByte(@NotNull Field field, @Nullable Object member, byte value);

    void setFieldLong(@NotNull Field field, @Nullable Object member, long value);

    void setFieldFloat(@NotNull Field field, @Nullable Object member, float value);

    void setFieldDouble(@NotNull Field field, @Nullable Object member, double value);

    void setFieldBoolean(@NotNull Field field, @Nullable Object member, boolean value);

    void setFieldChar(@NotNull Field field, @Nullable Object member, char value);


    
    @NotNull Constructor<?>[] getConstructors(Class<?> clazz, boolean publicOnly);

    @NotNull Field[] getFields(Class<?> clazz, boolean publicOnly);

    @NotNull Method[] getMethods(Class<?> clazz, boolean publicOnly);



    <T> @NotNull T newInstance(@NotNull Constructor<T> constructor, Object... params);

    <T> @NotNull T newInstance(@NotNull Class<T> clazz, Object... params);
    
}
