package com.henryrenyz.creflect;

import org.jetbrains.annotations.NotNull;
import org.jetbrains.annotations.Nullable;

import java.io.*;
import java.lang.reflect.*;
import java.math.BigInteger;
import java.net.URLClassLoader;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Objects;

@SuppressWarnings("unused")
public final class ReflectLibImpl implements ReflectLibInterface {

    ReflectLibImpl() {}

    /**
     * Call a method using given Method object and params.
     * Same to {@code Method.invoke()} but a lot faster.
     * This method doesn't throw any exception explicitly.
     * But I still recommended you to handle them.
     *
     * This method bypasses all the security checks, so
     * {@code setAccessible()} is unnecessarily needed.
     *
     * @param mth the method to call
     * @param member the member of class, given {@code null}
     *               if it's a static method.
     * @param params the parameters.
     *
     * @exception IllegalArgumentException  if the method is an
     *              instance method and the specified object argument
     *              is not an instance of the class or interface
     *              declaring the underlying method (or of a subclass
     *              or implementor thereof); if the number of actual
     *              and formal parameters differ; if an unwrapping
     *              conversion for primitive arguments fails; or if,
     *              after possible unwrapping, a parameter value
     *              cannot be converted to the corresponding formal
     *              parameter type by a method invocation conversion.
     * @exception RuntimeException  with actual exception in cause if the
     *              underlying constructor throws an exception.
     * @exception NullPointerException      if the specified object is null
     *              and the method is an instance method.
     * @exception ExceptionInInitializerError if the initialization
     *              provoked by this method fails.
     * @return the result of dispatching the method represented by
     *              this object on {@code member} with parameters
     */
    public @Nullable Object invoke(@NotNull Method mth, @Nullable Object member, Object... params) {
        switch (mth.getReturnType().getName()) {
            case "int":
                return callMethodInt0(mth, member, params);
            case "short":
                return callMethodShort0(mth, member, params);
            case "byte":
                return callMethodByte0(mth, member, params);
            case "long":
                return callMethodLong0(mth, member, params);
            case "float":
                return callMethodFloat0(mth, member, params);
            case "double":
                return callMethodDouble0(mth, member, params);
            case "boolean":
                return callMethodBoolean0(mth, member, params);
            case "char":
                return callMethodChar0(mth, member, params);
            case "void":
                callMethodVoid0(mth, member, params);
                return null;
            default:
                return callMethodObject0(mth, member, params);
        }
    }

    /**
     * Call a method that returns int using given Method object and params.
     * Same to {@code ReflectUtil.invoke()} but faster.
     * This method doesn't throw any exception explicitly.
     * But I still recommended you to handle them.
     *
     * This method bypasses all the security checks, so
     * {@code setAccessible()} is unnecessarily needed.
     *
     * @param mth the int method to call
     * @param member the member of class, given {@code null}
     *               if it's a static method.
     * @param params the parameters.
     *
     * @exception IllegalArgumentException  if the method is an
     *              instance method and the specified object argument
     *              is not an instance of the class or interface
     *              declaring the underlying method (or of a subclass
     *              or implementor thereof); if the number of actual
     *              and formal parameters differ; if an unwrapping
     *              conversion for primitive arguments fails; or if,
     *              after possible unwrapping, a parameter value
     *              cannot be converted to the corresponding formal
     *              parameter type by a method invocation conversion.
     * @exception RuntimeException  with actual exception in cause if the
     *              underlying constructor throws an exception.
     * @exception NullPointerException      if the specified object is null
     *              and the method is an instance method.
     * @exception ExceptionInInitializerError if the initialization
     *              provoked by this method fails.
     * @exception NoSuchMethodError     if the Method given does not return
     *              primitive int.
     * @return the result of dispatching the method represented by
     *              this object on {@code member} with parameters
     */
    public int invokeInt(@NotNull Method mth, @Nullable Object member, Object... params) {
        if (mth.getReturnType() != int.class)
            throw new NoSuchMethodError("Method does not return int!");
        return callMethodInt0(mth, member, params);
    }

    /**
     * Call a method that returns short using given Method object and params.
     * Same to {@code ReflectUtil.invoke()} but faster.
     * This method doesn't throw any exception explicitly.
     * But I still recommended you to handle them.
     *
     * This method bypasses all the security checks, so
     * {@code setAccessible()} is unnecessarily needed.
     *
     * @param mth the short method to call
     * @param member the member of class, given {@code null}
     *               if it's a static method.
     * @param params the parameters.
     *
     * @exception IllegalArgumentException  if the method is an
     *              instance method and the specified object argument
     *              is not an instance of the class or interface
     *              declaring the underlying method (or of a subclass
     *              or implementor thereof); if the number of actual
     *              and formal parameters differ; if an unwrapping
     *              conversion for primitive arguments fails; or if,
     *              after possible unwrapping, a parameter value
     *              cannot be converted to the corresponding formal
     *              parameter type by a method invocation conversion.
     * @exception RuntimeException  with actual exception in cause if the
     *              underlying constructor throws an exception.
     * @exception NullPointerException      if the specified object is null
     *              and the method is an instance method.
     * @exception ExceptionInInitializerError if the initialization
     *              provoked by this method fails.
     * @exception NoSuchMethodError     if the Method given does not return
     *              primitive short.
     * @return the result of dispatching the method represented by
     *              this object on {@code member} with parameters
     */
    public short invokeShort(@NotNull Method mth, @Nullable Object member, Object... params) {
        if (mth.getReturnType() != short.class)
            throw new NoSuchMethodError("Method does not return short!");
        return callMethodShort0(mth, member, params);
    }

    /**
     * Call a method that returns byte using given Method object and params.
     * Same to {@code ReflectUtil.invoke()} but faster.
     * This method doesn't throw any exception explicitly.
     * But I still recommended you to handle them.
     *
     * This method bypasses all the security checks, so
     * {@code setAccessible()} is unnecessarily needed.
     *
     * @param mth the byte method to call
     * @param member the member of class, given {@code null}
     *               if it's a static method.
     * @param params the parameters.
     *
     * @exception IllegalArgumentException  if the method is an
     *              instance method and the specified object argument
     *              is not an instance of the class or interface
     *              declaring the underlying method (or of a subclass
     *              or implementor thereof); if the number of actual
     *              and formal parameters differ; if an unwrapping
     *              conversion for primitive arguments fails; or if,
     *              after possible unwrapping, a parameter value
     *              cannot be converted to the corresponding formal
     *              parameter type by a method invocation conversion.
     * @exception RuntimeException  with actual exception in cause if the
     *              underlying constructor throws an exception.
     * @exception NullPointerException      if the specified object is null
     *              and the method is an instance method.
     * @exception ExceptionInInitializerError if the initialization
     *              provoked by this method fails.
     * @exception NoSuchMethodError     if the Method given does not return
     *              primitive byte.
     * @return the result of dispatching the method represented by
     *              this object on {@code member} with parameters
     */
    public byte invokeByte(@NotNull Method mth, @Nullable Object member, Object... params) {
        if (mth.getReturnType() != byte.class)
            throw new NoSuchMethodError("Method does not return byte!");
        return callMethodByte0(mth, member, params);
    }

    /**
     * Call a method that returns long using given Method object and params.
     * Same to {@code ReflectUtil.invoke()} but faster.
     * This method doesn't throw any exception explicitly.
     * But I still recommended you to handle them.
     *
     * This method bypasses all the security checks, so
     * {@code setAccessible()} is unnecessarily needed.
     *
     * @param mth the long method to call
     * @param member the member of class, given {@code null}
     *               if it's a static method.
     * @param params the parameters.
     *
     * @exception IllegalArgumentException  if the method is an
     *              instance method and the specified object argument
     *              is not an instance of the class or interface
     *              declaring the underlying method (or of a subclass
     *              or implementor thereof); if the number of actual
     *              and formal parameters differ; if an unwrapping
     *              conversion for primitive arguments fails; or if,
     *              after possible unwrapping, a parameter value
     *              cannot be converted to the corresponding formal
     *              parameter type by a method invocation conversion.
     * @exception RuntimeException  with actual exception in cause if the
     *              underlying constructor throws an exception.
     * @exception NullPointerException      if the specified object is null
     *              and the method is an instance method.
     * @exception ExceptionInInitializerError if the initialization
     *              provoked by this method fails.
     * @exception NoSuchMethodError     if the Method given does not return
     *              primitive long.
     * @return the result of dispatching the method represented by
     *              this object on {@code member} with parameters
     */
    public long invokeLong(@NotNull Method mth, @Nullable Object member, Object... params) {
        if (mth.getReturnType() != long.class)
            throw new NoSuchMethodError("Method does not return long!");
        return callMethodLong0(mth, member, params);
    }

    /**
     * Call a method that returns float using given Method object and params.
     * Same to {@code ReflectUtil.invoke()} but faster.
     * This method doesn't throw any exception explicitly.
     * But I still recommended you to handle them.
     *
     * This method bypasses all the security checks, so
     * {@code setAccessible()} is unnecessarily needed.
     *
     * @param mth the float method to call
     * @param member the member of class, given {@code null}
     *               if it's a static method.
     * @param params the parameters.
     *
     * @exception IllegalArgumentException  if the method is an
     *              instance method and the specified object argument
     *              is not an instance of the class or interface
     *              declaring the underlying method (or of a subclass
     *              or implementor thereof); if the number of actual
     *              and formal parameters differ; if an unwrapping
     *              conversion for primitive arguments fails; or if,
     *              after possible unwrapping, a parameter value
     *              cannot be converted to the corresponding formal
     *              parameter type by a method invocation conversion.
     * @exception RuntimeException  with actual exception in cause if the
     *              underlying constructor throws an exception.
     * @exception NullPointerException      if the specified object is null
     *              and the method is an instance method.
     * @exception ExceptionInInitializerError if the initialization
     *              provoked by this method fails.
     * @exception NoSuchMethodError     if the Method given does not return
     *              primitive float.
     * @return the result of dispatching the method represented by
     *              this object on {@code member} with parameters
     */
    public float invokeFloat(@NotNull Method mth, @Nullable Object member, Object... params) {
        if (mth.getReturnType() != float.class)
            throw new NoSuchMethodError("Method does not return float!");
        return callMethodFloat0(mth, member, params);
    }

    /**
     * Call a method that returns double using given Method object and params.
     * Same to {@code ReflectUtil.invoke()} but faster.
     * This method doesn't throw any exception explicitly.
     * But I still recommended you to handle them.
     *
     * This method bypasses all the security checks, so
     * {@code setAccessible()} is unnecessarily needed.
     *
     * @param mth the double method to call
     * @param member the member of class, given {@code null}
     *               if it's a static method.
     * @param params the parameters.
     *
     * @exception IllegalArgumentException  if the method is an
     *              instance method and the specified object argument
     *              is not an instance of the class or interface
     *              declaring the underlying method (or of a subclass
     *              or implementor thereof); if the number of actual
     *              and formal parameters differ; if an unwrapping
     *              conversion for primitive arguments fails; or if,
     *              after possible unwrapping, a parameter value
     *              cannot be converted to the corresponding formal
     *              parameter type by a method invocation conversion.
     * @exception RuntimeException  with actual exception in cause if the
     *              underlying constructor throws an exception.
     * @exception NullPointerException      if the specified object is null
     *              and the method is an instance method.
     * @exception ExceptionInInitializerError if the initialization
     *              provoked by this method fails.
     * @exception NoSuchMethodError     if the Method given does not return
     *              primitive double.
     * @return the result of dispatching the method represented by
     *              this object on {@code member} with parameters
     */
    public double invokeDouble(@NotNull Method mth, @Nullable Object member, Object... params) {
        if (mth.getReturnType() != double.class)
            throw new NoSuchMethodError("Method does not return double!");
        return callMethodDouble0(mth, member, params);
    }

    /**
     * Call a method that returns boolean using given Method object and params.
     * Same to {@code ReflectUtil.invoke()} but faster.
     * This method doesn't throw any exception explicitly.
     * But I still recommended you to handle them.
     *
     * This method bypasses all the security checks, so
     * {@code setAccessible()} is unnecessarily needed.
     *
     * @param mth the boolean method to call
     * @param member the member of class, given {@code null}
     *               if it's a static method.
     * @param params the parameters.
     *
     * @exception IllegalArgumentException  if the method is an
     *              instance method and the specified object argument
     *              is not an instance of the class or interface
     *              declaring the underlying method (or of a subclass
     *              or implementor thereof); if the number of actual
     *              and formal parameters differ; if an unwrapping
     *              conversion for primitive arguments fails; or if,
     *              after possible unwrapping, a parameter value
     *              cannot be converted to the corresponding formal
     *              parameter type by a method invocation conversion.
     * @exception RuntimeException  with actual exception in cause if the
     *              underlying constructor throws an exception.
     * @exception NullPointerException      if the specified object is null
     *              and the method is an instance method.
     * @exception ExceptionInInitializerError if the initialization
     *              provoked by this method fails.
     * @exception NoSuchMethodError     if the Method given does not return
     *              primitive boolean.
     * @return the result of dispatching the method represented by
     *              this object on {@code member} with parameters
     */
    public boolean invokeBoolean(@NotNull Method mth, @Nullable Object member, Object... params) {
        if (mth.getReturnType() != boolean.class)
            throw new NoSuchMethodError("Method does not return boolean!");
        return callMethodBoolean0(mth, member, params);
    }

    /**
     * Call a method that returns char using given Method object and params.
     * Same to {@code ReflectUtil.invoke()} but faster.
     * This method doesn't throw any exception explicitly.
     * But I still recommended you to handle them.
     *
     * This method bypasses all the security checks, so
     * {@code setAccessible()} is unnecessarily needed.
     *
     * @param mth the char method to call
     * @param member the member of class, given {@code null}
     *               if it's a static method.
     * @param params the parameters.
     *
     * @exception IllegalArgumentException  if the method is an
     *              instance method and the specified object argument
     *              is not an instance of the class or interface
     *              declaring the underlying method (or of a subclass
     *              or implementor thereof); if the number of actual
     *              and formal parameters differ; if an unwrapping
     *              conversion for primitive arguments fails; or if,
     *              after possible unwrapping, a parameter value
     *              cannot be converted to the corresponding formal
     *              parameter type by a method invocation conversion.
     * @exception RuntimeException  with actual exception in cause if the
     *              underlying constructor throws an exception.
     * @exception NullPointerException      if the specified object is null
     *              and the method is an instance method.
     * @exception ExceptionInInitializerError if the initialization
     *              provoked by this method fails.
     * @exception NoSuchMethodError     if the Method given does not return
     *              primitive char.
     * @return the result of dispatching the method represented by
     *              this object on {@code member} with parameters
     */
    public char invokeChar(@NotNull Method mth, @Nullable Object member, Object... params) {
        if (mth.getReturnType() != char.class)
            throw new NoSuchMethodError("Method does not return char!");
        return callMethodChar0(mth, member, params);
    }

    // Native Methods
    private static native Object    callMethodObject0 (Method mth, Object member, Object... params);
    private static native int       callMethodInt0    (Method mth, Object member, Object... params);
    private static native short     callMethodShort0  (Method mth, Object member, Object... params);
    private static native byte      callMethodByte0   (Method mth, Object member, Object... params);
    private static native long      callMethodLong0   (Method mth, Object member, Object... params);
    private static native float     callMethodFloat0  (Method mth, Object member, Object... params);
    private static native double    callMethodDouble0 (Method mth, Object member, Object... params);
    private static native boolean   callMethodBoolean0(Method mth, Object member, Object... params);
    private static native char      callMethodChar0   (Method mth, Object member, Object... params);
    private static native void      callMethodVoid0   (Method mth, Object member, Object... params);





    /**
     * Get a value using a field object.
     * Same to {@code Field.set()} but faster.
     * Doesn't throw ant exception explicitly, but recommended
     * to handle them as well.
     *
     * This method bypasses all the security checks so
     * {@code setAccessible()} is unnecessarily needed.
     *
     * @param field the field to get.
     * @param member the member to which the field belongs, pass
     *               {@code null} if it's a static field.
     *
     * @exception IllegalArgumentException  if the specified object is not an
     *              instance of the class or interface declaring the underlying
     *              field (or a subclass or implementor thereof),
     *              or if an unwrapping conversion fails.
     * @exception NullPointerException      if the specified object is null
     *              and the field is an instance field.
     * @exception ExceptionInInitializerError if the initialization provoked
     *              by this method fails.
     */
    public @Nullable Object getField(@NotNull Field field, @Nullable Object member) {
        switch (field.getType().getName()) {
            case "int":
                return getFieldInt0(field, member);
            case "short":
                return getFieldShort0(field, member);
            case "byte":
                return getFieldByte0(field, member);
            case "long":
                return getFieldLong0(field, member);
            case "float":
                return getFieldFloat0(field, member);
            case "double":
                return getFieldDouble0(field, member);
            case "boolean":
                return getFieldBoolean0(field, member);
            default:
                return getFieldObject0(field, member);
        }
    }

    /**
     * Get a int value using a field object.
     * Same to {@code ReflectUtil.getField()} but faster.
     * Doesn't throw ant exception explicitly, but recommended
     * to handle them as well.
     *
     * This method bypasses all the security checks so
     * {@code setAccessible()} is unnecessarily needed.
     *
     * @param field the int field to get.
     * @param member the member to which the field belongs, pass
     *               {@code null} if it's a static field.
     *
     * @exception IllegalArgumentException  if the specified object is not an
     *              instance of the class or interface declaring the underlying
     *              field (or a subclass or implementor thereof),
     *              or if an unwrapping conversion fails.
     * @exception NullPointerException      if the specified object is null
     *              and the field is an instance field.
     * @exception ExceptionInInitializerError if the initialization provoked
     *              by this method fails.
     * @exception NoSuchMethodError         if the given field is not a primitive
     *              int field.
     */
    public int getFieldInt(@NotNull Field field, @Nullable Object member) {
        if (field.getType() != int.class)
            throw new NoSuchMethodError("Field type is not int!");
        return getFieldInt0(field, member);
    }

    /**
     * Get a short value using a field object.
     * Same to {@code ReflectUtil.getField()} but faster.
     * Doesn't throw ant exception explicitly, but recommended
     * to handle them as well.
     *
     * This method bypasses all the security checks so
     * {@code setAccessible()} is unnecessarily needed.
     *
     * @param field the short field to get.
     * @param member the member to which the field belongs, pass
     *               {@code null} if it's a static field.
     *
     * @exception IllegalArgumentException  if the specified object is not an
     *              instance of the class or interface declaring the underlying
     *              field (or a subclass or implementor thereof),
     *              or if an unwrapping conversion fails.
     * @exception NullPointerException      if the specified object is null
     *              and the field is an instance field.
     * @exception ExceptionInInitializerError if the initialization provoked
     *              by this method fails.
     * @exception NoSuchMethodError         if the given field is not a primitive
     *              short field.
     */
    public short getFieldShort(@NotNull Field field, @Nullable Object member) {
        if (field.getType() != short.class)
            throw new NoSuchMethodError("Field type is not short!");
        return getFieldShort0(field, member);
    }

    /**
     * Get a byte value using a field object.
     * Same to {@code ReflectUtil.getField()} but faster.
     * Doesn't throw ant exception explicitly, but recommended
     * to handle them as well.
     *
     * This method bypasses all the security checks so
     * {@code setAccessible()} is unnecessarily needed.
     *
     * @param field the byte field to get.
     * @param member the member to which the field belongs, pass
     *               {@code null} if it's a static field.
     *
     * @exception IllegalArgumentException  if the specified object is not an
     *              instance of the class or interface declaring the underlying
     *              field (or a subclass or implementor thereof),
     *              or if an unwrapping conversion fails.
     * @exception NullPointerException      if the specified object is null
     *              and the field is an instance field.
     * @exception ExceptionInInitializerError if the initialization provoked
     *              by this method fails.
     * @exception NoSuchMethodError         if the given field is not a primitive
     *              byte field.
     */
    public byte getFieldByte(@NotNull Field field, @Nullable Object member) {
        if (field.getType() != byte.class)
            throw new NoSuchMethodError("Field type is not byte!");
        return getFieldByte0(field, member);
    }

    /**
     * Get a long value using a field object.
     * Same to {@code ReflectUtil.getField()} but faster.
     * Doesn't throw ant exception explicitly, but recommended
     * to handle them as well.
     *
     * This method bypasses all the security checks so
     * {@code setAccessible()} is unnecessarily needed.
     *
     * @param field the long field to get.
     * @param member the member to which the field belongs, pass
     *               {@code null} if it's a static field.
     *
     * @exception IllegalArgumentException  if the specified object is not an
     *              instance of the class or interface declaring the underlying
     *              field (or a subclass or implementor thereof),
     *              or if an unwrapping conversion fails.
     * @exception NullPointerException      if the specified object is null
     *              and the field is an instance field.
     * @exception ExceptionInInitializerError if the initialization provoked
     *              by this method fails.
     * @exception NoSuchMethodError         if the given field is not a primitive
     *              long field.
     */
    public long getFieldLong(@NotNull Field field, @Nullable Object member) {
        if (field.getType() != long.class)
            throw new NoSuchMethodError("Field type is not long!");
        return getFieldLong0(field, member);
    }

    /**
     * Get a float value using a field object.
     * Same to {@code ReflectUtil.getField()} but faster.
     * Doesn't throw ant exception explicitly, but recommended
     * to handle them as well.
     *
     * This method bypasses all the security checks so
     * {@code setAccessible()} is unnecessarily needed.
     *
     * @param field the float field to get.
     * @param member the member to which the field belongs, pass
     *               {@code null} if it's a static field.
     *
     * @exception IllegalArgumentException  if the specified object is not an
     *              instance of the class or interface declaring the underlying
     *              field (or a subclass or implementor thereof),
     *              or if an unwrapping conversion fails.
     * @exception NullPointerException      if the specified object is null
     *              and the field is an instance field.
     * @exception ExceptionInInitializerError if the initialization provoked
     *              by this method fails.
     * @exception NoSuchMethodError         if the given field is not a primitive
     *              float field.
     */
    public float getFieldFloat(@NotNull Field field, @Nullable Object member) {
        if (field.getType() != float.class)
            throw new NoSuchMethodError("Field type is not float!");
        return getFieldFloat0(field, member);
    }

    /**
     * Get a double value using a field object.
     * Same to {@code ReflectUtil.getField()} but faster.
     * Doesn't throw ant exception explicitly, but recommended
     * to handle them as well.
     *
     * This method bypasses all the security checks so
     * {@code setAccessible()} is unnecessarily needed.
     *
     * @param field the double field to get.
     * @param member the member to which the field belongs, pass
     *               {@code null} if it's a static field.
     *
     * @exception IllegalArgumentException  if the specified object is not an
     *              instance of the class or interface declaring the underlying
     *              field (or a subclass or implementor thereof),
     *              or if an unwrapping conversion fails.
     * @exception NullPointerException      if the specified object is null
     *              and the field is an instance field.
     * @exception ExceptionInInitializerError if the initialization provoked
     *              by this method fails.
     * @exception NoSuchMethodError         if the given field is not a primitive
     *              double field.
     */
    public double getFieldDouble(@NotNull Field field, @Nullable Object member) {
        if (field.getType() != double.class)
            throw new NoSuchMethodError("Field type is not double!");
        return getFieldDouble0(field, member);
    }

    /**
     * Get a boolean value using a field object.
     * Same to {@code ReflectUtil.getField()} but faster.
     * Doesn't throw ant exception explicitly, but recommended
     * to handle them as well.
     *
     * This method bypasses all the security checks so
     * {@code setAccessible()} is unnecessarily needed.
     *
     * @param field the boolean field to get.
     * @param member the member to which the field belongs, pass
     *               {@code null} if it's a static field.
     *
     * @exception IllegalArgumentException  if the specified object is not an
     *              instance of the class or interface declaring the underlying
     *              field (or a subclass or implementor thereof),
     *              or if an unwrapping conversion fails.
     * @exception NullPointerException      if the specified object is null
     *              and the field is an instance field.
     * @exception ExceptionInInitializerError if the initialization provoked
     *              by this method fails.
     * @exception NoSuchMethodError         if the given field is not a primitive
     *              boolean field.
     */
    public boolean getFieldBoolean(@NotNull Field field, @Nullable Object member) {
        if (field.getType() != boolean.class)
            throw new NoSuchMethodError("Field type is not boolean!");
        return getFieldBoolean0(field, member);
    }

    /**
     * Get a char value using a field object.
     * Same to {@code ReflectUtil.getField()} but faster.
     * Doesn't throw ant exception explicitly, but recommended
     * to handle them as well.
     *
     * This method bypasses all the security checks so
     * {@code setAccessible()} is unnecessarily needed.
     *
     * @param field the char field to get.
     * @param member the member to which the field belongs, pass
     *               {@code null} if it's a static field.
     *
     * @exception IllegalArgumentException  if the specified object is not an
     *              instance of the class or interface declaring the underlying
     *              field (or a subclass or implementor thereof),
     *              or if an unwrapping conversion fails.
     * @exception NullPointerException      if the specified object is null
     *              and the field is an instance field.
     * @exception ExceptionInInitializerError if the initialization provoked
     *              by this method fails.
     * @exception NoSuchMethodError         if the given field is not a primitive
     *              char field.
     */
    public char getFieldChar(@NotNull Field field, @Nullable Object member) {
        if (field.getType() != char.class)
            throw new NoSuchMethodError("Field type is not char!");
        return getFieldChar0(field, member);
    }

    // Native Methods
    private static native Object    getFieldObject0   (Field field, Object member);
    private static native int       getFieldInt0      (Field field, Object member);
    private static native short     getFieldShort0    (Field field, Object member);
    private static native byte      getFieldByte0     (Field field, Object member);
    private static native long      getFieldLong0     (Field field, Object member);
    private static native float     getFieldFloat0    (Field field, Object member);
    private static native double    getFieldDouble0   (Field field, Object member);
    private static native boolean   getFieldBoolean0  (Field field, Object member);
    private static native char      getFieldChar0     (Field field, Object member);


    /**
     * Set a field to given value using a field object.
     * Same to {@code Field.set()} but faster.
     * Doesn't throw ant exception explicitly, but recommended
     * to handle them as well.
     *
     * This method bypasses all the security checks so
     * {@code setAccessible()} is unnecessarily needed.
     *
     * @param field the field to modify.
     * @param member the member to which the field belongs, pass
     *               {@code null} if it's a static field.
     * @param value the value to set, if the target field is a
     *              primitive and value is given null, then it
     *              will be set to 0 or false (boolean).
     *
     * @exception IllegalArgumentException  if the specified object is not an
     *              instance of the class or interface declaring the underlying
     *              field (or a subclass or implementor thereof),
     *              or if an unwrapping conversion fails.
     * @exception NullPointerException      if the specified object is null
     *              and the field is an instance field.
     * @exception ExceptionInInitializerError if the initialization provoked
     *              by this method fails.
     */
    public void setField(@NotNull Field field, @Nullable Object member, @Nullable Object value) {
        switch (field.getType().getName()) {
            case "int":
                setFieldInt0(field, member, (int) (value == null ? 0 : value));
                break;
            case "short":
                setFieldShort0(field, member, (short) (value == null ? 0 : value));
                break;
            case "byte":
                setFieldByte0(field, member, (byte) (value == null ? 0 : value));
                break;
            case "long":
                setFieldLong0(field, member, (long) (value == null ? 0 : value));
                break;
            case "float":
                setFieldFloat0(field, member, (float) (value == null ? 0 : value));
                break;
            case "double":
                setFieldDouble0(field, member, (double) (value == null ? 0 : value));
                break;
            case "boolean":
                setFieldBoolean0(field, member, (boolean) (value == null ? false : value));
                break;
            case "char":
                setFieldChar0(field, member, (char) (value == null ? 0 : value));
                break;
            default:
                setFieldObject0(field, member, value);
        }
    }

    /**
     * Set a int field to given value using a field object.
     * Same to {@code ReflectUtil.setField()} but faster.
     * Doesn't throw ant exception explicitly, but recommended
     * to handle them as well.
     *
     * This method bypasses all the security checks so
     * {@code setAccessible()} is unnecessarily needed.
     *
     * @param field the int field to modify.
     * @param member the member to which the field belongs, pass
     *               {@code null} if it's a static field.
     * @param value the int value to set.
     *
     * @exception IllegalArgumentException  if the specified object is not an
     *              instance of the class or interface declaring the underlying
     *              field (or a subclass or implementor thereof),
     *              or if an unwrapping conversion fails.
     * @exception NullPointerException      if the specified object is null
     *              and the field is an instance field.
     * @exception ExceptionInInitializerError if the initialization provoked
     *              by this method fails.
     * @exception NoSuchMethodError         if the given field is not a primitive
     *              int field.
     */
    public void setFieldInt(@NotNull Field field, @Nullable Object member, int value) {
        if (field.getType() != int.class)
            throw new NoSuchMethodError("Field type is not int!");
        setFieldInt0(field, member, value);
    }

    /**
     * Set a short field to given value using a field object.
     * Same to {@code ReflectUtil.setField()} but faster.
     * Doesn't throw ant exception explicitly, but recommended
     * to handle them as well.
     *
     * This method bypasses all the security checks so
     * {@code setAccessible()} is unnecessarily needed.
     *
     * @param field the short field to modify.
     * @param member the member to which the field belongs, pass
     *               {@code null} if it's a static field.
     * @param value the short value to set.
     *
     * @exception IllegalArgumentException  if the specified object is not an
     *              instance of the class or interface declaring the underlying
     *              field (or a subclass or implementor thereof),
     *              or if an unwrapping conversion fails.
     * @exception NullPointerException      if the specified object is null
     *              and the field is an instance field.
     * @exception ExceptionInInitializerError if the initialization provoked
     *              by this method fails.
     * @exception NoSuchMethodError         if the given field is not a primitive
     *              short field.
     */
    public void setFieldShort(@NotNull Field field, @Nullable Object member, short value) {
        if (field.getType() != short.class)
            throw new NoSuchMethodError("Field type is not short!");
        setFieldShort0(field, member, value);
    }

    /**
     * Set a byte field to given value using a field object.
     * Same to {@code ReflectUtil.setField()} but faster.
     * Doesn't throw ant exception explicitly, but recommended
     * to handle them as well.
     *
     * This method bypasses all the security checks so
     * {@code setAccessible()} is unnecessarily needed.
     *
     * @param field the byte field to modify.
     * @param member the member to which the field belongs, pass
     *               {@code null} if it's a static field.
     * @param value the byte value to set.
     *
     * @exception IllegalArgumentException  if the specified object is not an
     *              instance of the class or interface declaring the underlying
     *              field (or a subclass or implementor thereof),
     *              or if an unwrapping conversion fails.
     * @exception NullPointerException      if the specified object is null
     *              and the field is an instance field.
     * @exception ExceptionInInitializerError if the initialization provoked
     *              by this method fails.
     * @exception NoSuchMethodError         if the given field is not a primitive
     *              byte field.
     */
    public void setFieldByte(@NotNull Field field, @Nullable Object member, byte value) {
        if (field.getType() != byte.class)
            throw new NoSuchMethodError("Field type is not byte!");
        setFieldByte0(field, member, value);
    }

    /**
     * Set a long field to given value using a field object.
     * Same to {@code ReflectUtil.setField()} but faster.
     * Doesn't throw ant exception explicitly, but recommended
     * to handle them as well.
     *
     * This method bypasses all the security checks so
     * {@code setAccessible()} is unnecessarily needed.
     *
     * @param field the long field to modify.
     * @param member the member to which the field belongs, pass
     *               {@code null} if it's a static field.
     * @param value the long value to set.
     *
     * @exception IllegalArgumentException  if the specified object is not an
     *              instance of the class or interface declaring the underlying
     *              field (or a subclass or implementor thereof),
     *              or if an unwrapping conversion fails.
     * @exception NullPointerException      if the specified object is null
     *              and the field is an instance field.
     * @exception ExceptionInInitializerError if the initialization provoked
     *              by this method fails.
     * @exception NoSuchMethodError         if the given field is not a primitive
     *              long field.
     */
    public void setFieldLong(@NotNull Field field, @Nullable Object member, long value) {
        if (field.getType() != long.class)
            throw new NoSuchMethodError("Field type is not long!");
        setFieldLong0(field, member, value);
    }

    /**
     * Set a float field to given value using a field object.
     * Same to {@code ReflectUtil.setField()} but faster.
     * Doesn't throw ant exception explicitly, but recommended
     * to handle them as well.
     *
     * This method bypasses all the security checks so
     * {@code setAccessible()} is unnecessarily needed.
     *
     * @param field the float field to modify.
     * @param member the member to which the field belongs, pass
     *               {@code null} if it's a static field.
     * @param value the float value to set.
     *
     * @exception IllegalArgumentException  if the specified object is not an
     *              instance of the class or interface declaring the underlying
     *              field (or a subclass or implementor thereof),
     *              or if an unwrapping conversion fails.
     * @exception NullPointerException      if the specified object is null
     *              and the field is an instance field.
     * @exception ExceptionInInitializerError if the initialization provoked
     *              by this method fails.
     * @exception NoSuchMethodError         if the given field is not a primitive
     *              float field.
     */
    public void setFieldFloat(@NotNull Field field, @Nullable Object member, float value) {
        if (field.getType() != float.class)
            throw new NoSuchMethodError("Field type is not float!");
        setFieldFloat0(field, member, value);
    }

    /**
     * Set a double field to given value using a field object.
     * Same to {@code ReflectUtil.setField()} but faster.
     * Doesn't throw ant exception explicitly, but recommended
     * to handle them as well.
     *
     * This method bypasses all the security checks so
     * {@code setAccessible()} is unnecessarily needed.
     *
     * @param field the double field to modify.
     * @param member the member to which the field belongs, pass
     *               {@code null} if it's a static field.
     * @param value the double value to set.
     *
     * @exception IllegalArgumentException  if the specified object is not an
     *              instance of the class or interface declaring the underlying
     *              field (or a subclass or implementor thereof),
     *              or if an unwrapping conversion fails.
     * @exception NullPointerException      if the specified object is null
     *              and the field is an instance field.
     * @exception ExceptionInInitializerError if the initialization provoked
     *              by this method fails.
     * @exception NoSuchMethodError         if the given field is not a primitive
     *              double field.
     */
    public void setFieldDouble(@NotNull Field field, @Nullable Object member, double value) {
        if (field.getType() != double.class)
            throw new NoSuchMethodError("Field type is not double!");
        setFieldDouble0(field, member, value);
    }

    /**
     * Set a boolean field to given value using a field object.
     * Same to {@code ReflectUtil.setField()} but faster.
     * Doesn't throw ant exception explicitly, but recommended
     * to handle them as well.
     *
     * This method bypasses all the security checks so
     * {@code setAccessible()} is unnecessarily needed.
     *
     * @param field the boolean field to modify.
     * @param member the member to which the field belongs, pass
     *               {@code null} if it's a static field.
     * @param value the boolean value to set.
     *
     * @exception IllegalArgumentException  if the specified object is not an
     *              instance of the class or interface declaring the underlying
     *              field (or a subclass or implementor thereof),
     *              or if an unwrapping conversion fails.
     * @exception NullPointerException      if the specified object is null
     *              and the field is an instance field.
     * @exception ExceptionInInitializerError if the initialization provoked
     *              by this method fails.
     * @exception NoSuchMethodError         if the given field is not a primitive
     *              boolean field.
     */
    public void setFieldBoolean(@NotNull Field field, @Nullable Object member, boolean value) {
        if (field.getType() != boolean.class)
            throw new NoSuchMethodError("Field type is not boolean!");
        setFieldBoolean0(field, member, value);
    }

    /**
     * Set a char field to given value using a field object.
     * Same to {@code ReflectUtil.setField()} but faster.
     * Doesn't throw ant exception explicitly, but recommended
     * to handle them as well.
     *
     * This method bypasses all the security checks so
     * {@code setAccessible()} is unnecessarily needed.
     *
     * @param field the char field to modify.
     * @param member the member to which the field belongs, pass
     *               {@code null} if it's a static field.
     * @param value the char value to set.
     *
     * @exception IllegalArgumentException  if the specified object is not an
     *              instance of the class or interface declaring the underlying
     *              field (or a subclass or implementor thereof),
     *              or if an unwrapping conversion fails.
     * @exception NullPointerException      if the specified object is null
     *              and the field is an instance field.
     * @exception ExceptionInInitializerError if the initialization provoked
     *              by this method fails.
     * @exception NoSuchMethodError         if the given field is not a primitive
     *              char field.
     */
    public void setFieldChar(@NotNull Field field, @Nullable Object member, char value) {
        if (field.getType() != char.class)
            throw new NoSuchMethodError("Field type is not char!");
        setFieldChar0(field, member, value);
    }


    // Native Methods
    private static native void      setFieldObject0   (Field field, Object member, Object value);
    private static native void      setFieldInt0      (Field field, Object member, int value);
    private static native void      setFieldShort0    (Field field, Object member, short value);
    private static native void      setFieldByte0     (Field field, Object member, byte value);
    private static native void      setFieldLong0     (Field field, Object member, long value);
    private static native void      setFieldFloat0    (Field field, Object member, float value);
    private static native void      setFieldDouble0   (Field field, Object member, double value);
    private static native void      setFieldBoolean0  (Field field, Object member, boolean value);
    private static native void      setFieldChar0     (Field field, Object member, char value);





    private static Method     Class_privateGetDeclaredConstructors;
    private static Method     Class_privateGetDeclaredMethods;
    private static Method     Class_privateGetDeclaredFields;

    /**
     * Faster get class constructors with native reflection lib
     * Be note that the constructors it returns is original one,
     * not a copy, so everything you modified on it will directly
     * affect program's proper functioning.
     *
     * @param clazz the class to find constructors
     * @param publicOnly whether to get public constructor only
     * @return constructor array
     */
    public @NotNull Constructor<?>[] getConstructors(Class<?> clazz, boolean publicOnly) {
        return ((Constructor<?>[]) Objects.requireNonNull(invoke(Class_privateGetDeclaredConstructors, clazz, publicOnly))).clone();
    }

    /** Same to {@code getConstructors()} */
    public @NotNull Field[] getFields(Class<?> clazz, boolean publicOnly) {
        return ((Field[]) Objects.requireNonNull(invoke(Class_privateGetDeclaredFields, clazz, publicOnly))).clone();
    }

    /** Same to {@code getConstructors()} */
    public @NotNull Method[] getMethods(Class<?> clazz, boolean publicOnly) {
        return ((Method[]) Objects.requireNonNull(invoke(Class_privateGetDeclaredMethods, clazz, publicOnly))).clone();
    }







    private static Class<?> toWrapper(Class<?> primitive) {
        switch (primitive.getName()) {
            case "int":
                return Integer.class;
            case "short":
                return Short.class;
            case "byte":
                return Byte.class;
            case "char":
                return Character.class;
            case "long":
                return Long.class;
            case "float":
                return Float.class;
            case "double":
                return Double.class;
            case "boolean":
                return Boolean.class;
            default:
                return primitive;
        }
    }

    /**
     * Construct a new object using given constructor.
     * Same to {@code Constructor.newInstance()} but faster.
     * Also, this method doesn't throw any reflection exception
     * explicitly, so you don't need to handle exceptions using
     * try-catch, but it's recommended to handle however.
     *
     * This method bypasses any security checks, so
     * {@code setAccessibly()} is not necessarily needed.
     *
     * @param constructor the constructor to use
     * @param params the parameters
     *
     * @exception IllegalArgumentException  if the number of actual
     *              and formal parameters differ; if an unwrapping
     *              conversion for primitive arguments fails; or if,
     *              after possible unwrapping, a parameter value
     *              cannot be converted to the corresponding formal
     *              parameter type by a method invocation conversion; if
     *              this constructor pertains to an enum type.
     * @exception InstantiationException    if the class that declares the
     *              underlying constructor represents an abstract class.
     * @exception RuntimeException with actual exception in cause if the
     *              underlying constructor throws an exception.
     * @exception ExceptionInInitializerError if the initialization provoked
     *              by this method fails.
     * @return a new object created by calling this constructor
     */
    @SuppressWarnings("unchecked")
    public <T> @NotNull T newInstance(@NotNull Constructor<T> constructor, Object... params) {
        return (T) newInstance0(constructor, params);
    }

    /**
     * Construct a new object by finding valid constructor
     * in a given class.
     * It's faster than normal method using
     * {@code Class.getDeclaredConstructors()}
     * Also, this method doesn't throw any reflection exception
     * explicitly, so you don't need to handle exceptions using
     * try-catch, but it's recommended to handle however.
     *
     * @param clazz the class to find valid constructor
     * @param params the parameters
     *
     * @exception IllegalArgumentException  if the number of actual
     *              and formal parameters differ; if an unwrapping
     *              conversion for primitive arguments fails; or if,
     *              after possible unwrapping, a parameter value
     *              cannot be converted to the corresponding formal
     *              parameter type by a method invocation conversion; if
     *              this constructor pertains to an enum type.
     * @exception InstantiationException    if the class that declares the
     *              underlying constructor represents an abstract class.
     * @exception RuntimeException with actual exception in cause if the
     *              underlying constructor throws an exception.
     * @exception ExceptionInInitializerError if the initialization provoked
     *              by this method fails.
     * @exception NoSuchMethodError     if no valid constructor found for given
     *              params.
     * @return a new object created by calling this constructor
     */
    @SuppressWarnings("unchecked")
    public <T> @NotNull T newInstance(@NotNull Class<T> clazz, Object... params) {
        // Get params class list
        Class<?>[] paramsList = new Class[params.length];
        for (int i = 0; i < params.length; i++) {
            paramsList[i] = params[i] == null ? Void.class : params[i].getClass();
        }

        //Find constructor
        Outer:
        for (Constructor<?> c : clazz.getDeclaredConstructors()/*getConstructors(clazz, false)*/) {
            if (c.getParameterCount() == params.length) {
                Class<?>[] expected = c.getParameterTypes();
                assert expected != null;
                for (int i = 0; i < params.length; i++) {
                    if (!paramsList[i].isAssignableFrom(toWrapper(expected[i])))
                        continue Outer;
                }
                return (T) newInstance0(c, params);
            }
        }
        throw new NoSuchMethodError("No constructor found with this signature!");
    }

    /**
     * Create a new object without constructor.
     * This method bypass any security checks, which could be used
     * to instantiate any class that registered on JVM, including
     * some "not instantiable" class that could cause some problems.
     *
     * @param clazz the instance's class
     *
     * @return an instance with no data at all
     */
    @SuppressWarnings("unchecked")
    public <T> @NotNull T allocInstance(Class<T> clazz) {
        return (T) allocInstance0(clazz);
    }

    // Native Methods
    private static native Object newInstance0(Constructor<?> constructor, Object... params);
    private static native Object allocInstance0(Class<?> clazz);


    // Native library initialization,
    // it has a switch in lib to make sure this will not run twice.
    private static native boolean   refUtilInit0();



    void init(File dll) {
        if (!System.getProperties().getProperty("os.name").toUpperCase().contains("WINDOWS")) {
            throw new RuntimeException("This is is for Windows only!");
        }

        try {
            Class_privateGetDeclaredConstructors = Class.class.getDeclaredMethod("privateGetDeclaredConstructors", boolean.class);
            Class_privateGetDeclaredMethods = Class.class.getDeclaredMethod("privateGetDeclaredMethods", boolean.class);
            Class_privateGetDeclaredFields = Class.class.getDeclaredMethod("privateGetDeclaredFields", boolean.class);
        } catch (NoSuchMethodException e) {
            throw new RuntimeException(e);
        }

        System.load(dll.getAbsolutePath());
        if (!refUtilInit0()) {
            throw new UnsatisfiedLinkError("Failed to init dynamic link library for ReflectUtil!");
        }
    }
}
